/*Texas A&M University
**Electronic Systems Engineering Technology
**ESET 420 Capstone II
**Author: Jonathan Noland
**File: msdi.c
**------------------------------------------------------------------------------
**This file contains the functions to use the TIC-10024-Q1 
*/

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/ssi.h"
#include "msdi.h"

// ROS includes
#include <ros.h>
#include <std_msgs/UInt32.h>
#include "rosserial_tivac_tutorials/Panel.h"

/*
**Private Functions
*/

/*TIVA specific SPI transfer function
**Parameters:
**send_data: Read write bit set,the register, data, and parity bit to be sent.
**rcv_data: Pointer to data to be stored before it is parsed
**Returns status
 */
//static msdi_status_t MSDI_DATA_TRANSFER(
static void MSDI_DATA_TRANSFER(
	 uint32_t send_data[], uint32_t rcv_data[]);

/*Function: MSDI_WRITE
**Prepares data to be sent
**Parameters:
**          Register name data is to be written to
**          Register setting 
*/
static void MSDI_WRITE(uint32_t ui32Register,uint32_t uiSetting,uint32_t pui32DataRx[]);

/*Function: MSDI_READ
**Reads data from register
**Parameters:
**          ui32Register: Register name data is to be read from
**          ui32DataRx: Pointer to data received storage
*/
static uint32_t MSDI_READ(uint32_t ui32Register,uint32_t pui32DataRx[]);

/*Function Name: MSDI_PARITY
**Description: Checks raw data for odd parity
**Parameters: raw data to be checked
**Returns: 0 if parity bit doesn't need to be set, 1 if parity bit needs to be set
*/
static msdi_parity_t MSDI_PARITY(uint32_t raw_val);



/*
**Private Functions Code
*/

/*Function Name: MSDI_DATA_TRANSFER
**Description: This function transfers the upper and lower 32 bits of data while simultaneously reading MISO bits
*/
static void MSDI_DATA_TRANSFER(
	uint32_t send_data[], uint32_t  rcv_data[])
{
//msdi_status_t status = MSDI_STATUS_SUCCESS;

//CS low
    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, 0);

//Send and recieve data at the same time
//for(ui32Index = 0; ui32Index < NUM_SSI_DATA; ui32Index++)
//  SSIDataPut(SSI0_BASE, ui32DataTx[ui32Index]);
    SSIDataPut(SSI0_BASE, send_data[0]);
    SSIDataGet(SSI0_BASE, &rcv_data[0]);
    while(SSIBusy(SSI0_BASE))
    {
    }

//}
    SSIDataPut(SSI0_BASE, send_data[1]);
    SSIDataGet(SSI0_BASE,&rcv_data[1]);
    while(SSIBusy(SSI0_BASE))
    {
    }
//}

 //cs high
    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, GPIO_PIN_3);

 //   return MSDI_STATUS_SUCCESS;
}

/*Function Name: MSDI_WRITE
**Description: Prepares data to be sent to write to a register
*/
static void MSDI_WRITE(uint32_t ui32Register,uint32_t ui32Setting, uint32_t pui32DataRx[])
{
    uint32_t ui32DataTx[NUM_SSI_DATA];
   // uint32_t pui32DataRx[NUM_SSI_DATA];

    uint32_t raw_val = (MSDI_REG_RW_W | (ui32Register<<1) | (ui32Setting<<1));

    msdi_parity_t status = MSDI_PARITY(raw_val);

    if (status == SET_PARITY_BIT)
    {
        raw_val = raw_val | SET_PARITY_BIT_MASK;

    }

    ui32DataTx[0] = raw_val>>16;
    ui32DataTx[1] = raw_val & LOWER_TRANSFER_MASK;

    MSDI_DATA_TRANSFER(ui32DataTx,pui32DataRx);//possible issue with ui32DataRx
    
}

/*Function Name: MSDI_WRITE
**Description: Prepares data to be sent to write to a register
*/
static uint32_t MSDI_READ(uint32_t ui32Register,uint32_t pui32DataRx[])//changed from void to uin32_t for testing//
{
    uint32_t ui32DataTx[NUM_SSI_DATA];
   // uint32_t pui32DataRx[NUM_SSI_DATA];

    uint32_t raw_val = MSDI_REG_R_MASK & (ui32Register<<1);

    msdi_parity_t status = MSDI_PARITY(raw_val);

    if (status == SET_PARITY_BIT)
    {
        raw_val = raw_val | SET_PARITY_BIT_MASK;

    }

    ui32DataTx[0] = raw_val>>16;
    ui32DataTx[1] = raw_val & LOWER_TRANSFER_MASK;

    MSDI_DATA_TRANSFER(ui32DataTx,pui32DataRx);//possible issue with pui32DataRx

    return raw_val;
    
}


/*Function Name: MSDI_PARITY
**Description: Checks raw data to see if the parity bit needs to be set
*/
static msdi_parity_t MSDI_PARITY(uint32_t raw_val)
{
    //unsigned int v = 0x11011000; // 32-bit word
    raw_val ^= raw_val >> 1;
    raw_val ^= raw_val >> 2;
    raw_val = (raw_val & 0x11111111U) * 0x11111111U;
    unsigned int x = (raw_val >> 28) & 1;
    
    if(x==1)
    {
        return LEAVE_PARITY_BIT;
    }
    else if (x==0)
    {
        return SET_PARITY_BIT;
    }   

}


/*
**Public Functions
*/
/*Function Name: SSI_Init
**Description: Setup the SSI for use with msdi
**Parameters: Pointer to msdi spi configuration
**            
**Returns: Void
*/

void SSI_Init(msdi_spi_t* const spiConfig)
{
    //Enable Peripherals
    SysCtlPeripheralEnable(spiConfig->ui32SysCtlSSI);
    SysCtlPeripheralEnable(spiConfig->ui32SysCtlGPIO);

    while(!SysCtlPeripheralReady(spiConfig->ui32SysCtlGPIO))
    {
    }

    //Configure Pins for SPI
    GPIOPinConfigure(spiConfig->ui32PinCLK);
    GPIOPinConfigure(spiConfig->ui32PinRX);
    GPIOPinConfigure(spiConfig->ui32PinTX);

    /* Set pin types
    **Direct Control used for CS to allow 32 bit transfers */
    GPIOPinTypeGPIOOutput(spiConfig->ui32GPIOBase,spiConfig->ui32PinFSS);
    GPIOPinTypeSSI(spiConfig->ui32GPIOBase, 
                    spiConfig->ui32GPIOPinCLK | spiConfig->ui32GPIOPinRX | spiConfig->ui32GPIOPinTX);

    SSIConfigSetExpClk(spiConfig->ui32SSIBASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_1,
                       SSI_MODE_MASTER, 2000000, 16);
    
    //Enable SSI
    SSIEnable(spiConfig->ui32SSIBASE);

    //CS Set High
    GPIOPinWrite(spiConfig->ui32GPIOBase, spiConfig->ui32PinFSS, spiConfig->ui32PinFSS);

    while(!SysCtlPeripheralReady(spiConfig->ui32SysCtlGPIO))
    {
    }

    return;

}

/*Function Name: MSDI_Init
**Description: Setup MSDI SPI, Register Settings, Panel struct info goes into
**Parameters: choice is a value to determine which SPI is being used
**            msdi_info is a pointer to msdi instance
**            panel is a pointer to ROS message for MSDI
**            
**Returns: Void
*/
void MSDI_Init(msdi_spi_choice_t choice, msdi_var_t* msdi_info, Panel* panel)
{
    if (choice == SPI0)
    {
        msdi_info->spi_settings = {SYSCTL_PERIPH_SSI0, SYSCTL_PERIPH_GPIOA, SSI0_BASE, GPIO_PA2_SSI0CLK,
                GPIO_PA4_SSI0RX, GPIO_PA5_SSI0TX, GPIO_PORTA_BASE, GPIO_PIN_3, GPIO_PIN_2,
                GPIO_PIN_4, GPIO_PIN_5};
    }
    else if (choice == SPI1)
    {
        msdi_info->spi_settings = {SYSCTL_PERIPH_SSI0, SYSCTL_PERIPH_GPIOA, SSI0_BASE, GPIO_PA2_SSI0CLK,
                GPIO_PA4_SSI0RX, GPIO_PA5_SSI0TX, GPIO_PORTA_BASE, GPIO_PIN_3, GPIO_PIN_2,
                GPIO_PIN_4, GPIO_PIN_5};
    }

    msdi_info->Panel = panel;

    msdi_info.reg_settings = 0;

    SSI_Init(&(msdi_info->spi_settings));
}




/*Function Name: TEST_FUNC
**Description: Test function to see if files can build, and if data can be returned
*/
uint32_t TEST_FUNC(uint32_t ui32Register,uint32_t pui32DataRx[])
{
    uint32_t rslt = MSDI_READ(ui32Register, pui32DataRx);

    return rslt;
}



/*Function Name: TEST_FUNC_TWO
**Description: Test function to see if files can build, and if data can be returned
*/
uint32_t TEST_FUNC_TWO(uint32_t ui32Register,uint32_t pui32DataRx[])
{
    uint32_t enable = 0x00F0000F;
    MSDI_WRITE(IN_EN, enable, pui32DataRx);

    uint32_t cfig = 0x00000800;

    MSDI_WRITE(CONFIG, cfig, pui32DataRx);
    
    uint32_t rslt = MSDI_READ(ui32Register, pui32DataRx);

    return rslt;
}
