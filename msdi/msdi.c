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
static void MSDI_READ(uint32_t ui32Register,uint32_t pui32DataRx[]);

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
**TODO: Switch to passing pointer from msdi_var_t
*/
static void MSDI_DATA_TRANSFER(uint32_t send_data[], uint32_t  rcv_data[])
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

/*Function Name: MSDI_READ
**Description: Reads from a register
*/
static void MSDI_READ(uint32_t ui32Register,uint32_t pui32DataRx[])//changed from void to uin32_t for testing//
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

    return;
    
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

    return LEAVE_PARITY_BIT;

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
void MSDI_Init(msdi_var_t* msdi_info)
{
    if (msdi_info->device == MSDI0)
    {
        //Initalize MSDI settings
        msdi_info->spi_settings.ui32SysCtlSSI = SYSCTL_PERIPH_SSI0;
        msdi_info->spi_settings.ui32SysCtlGPIO = SYSCTL_PERIPH_GPIOA;
        msdi_info->spi_settings.ui32SSIBASE = SSI0_BASE;
        msdi_info->spi_settings.ui32PinCLK = GPIO_PA2_SSI0CLK;
        msdi_info->spi_settings.ui32PinRX = GPIO_PA4_SSI0RX;
        msdi_info->spi_settings.ui32PinTX = GPIO_PA5_SSI0TX;
        msdi_info->spi_settings.ui32GPIOBase = GPIO_PORTA_BASE;
        msdi_info->spi_settings.ui32PinFSS = GPIO_PIN_3;
        msdi_info->spi_settings.ui32GPIOPinCLK = GPIO_PIN_2;
        msdi_info->spi_settings.ui32GPIOPinRX = GPIO_PIN_4;
        msdi_info->spi_settings.ui32GPIOPinTX = GPIO_PIN_5;
        msdi_info->int_flag = 0;
        
       // strcpy(msdi_info->location, "Left Panel"); //TODO Test Fix )
    }
    else if (msdi_info->device == MSDI1)
    {
        msdi_info->spi_settings.ui32SysCtlSSI = SYSCTL_PERIPH_SSI0;
        msdi_info->spi_settings.ui32SysCtlGPIO = SYSCTL_PERIPH_GPIOA;
        msdi_info->spi_settings.ui32SSIBASE = SSI0_BASE;
        msdi_info->spi_settings.ui32PinCLK = GPIO_PA2_SSI0CLK;
        msdi_info->spi_settings.ui32PinRX = GPIO_PA4_SSI0RX;
        msdi_info->spi_settings.ui32PinTX = GPIO_PA5_SSI0TX;
        msdi_info->spi_settings.ui32GPIOBase = GPIO_PORTA_BASE;
        msdi_info->spi_settings.ui32PinFSS = GPIO_PIN_3;
        msdi_info->spi_settings.ui32GPIOPinCLK = GPIO_PIN_2;
        msdi_info->spi_settings.ui32GPIOPinRX = GPIO_PIN_4;
        msdi_info->spi_settings.ui32GPIOPinTX = GPIO_PIN_5;
        msdi_info->int_flag = 0;
        
        //strcpy(msdi_info.location, "Right Panel";
        
    }

 

    msdi_info->reg_settings.blank_set = 0;


    //Set up SPI 
    SSI_Init(&(msdi_info->spi_settings)); //REMEMBER

    //Initalize registers
    MSDI_REG_INI(msdi_info);
}

/*Function Name: MSDI_GET_BUTTON_STATUS
**Description: Get status of Buttons by reading the IN_STAT OR AN_STAT Registers
**Param: Takes in specific msdi, 
*/

void MSDI_GET_BUTTON_STATUS(msdi_var_t* msdi_info)
{
    uint32_t ui32DataRx[NUM_SSI_DATA];
    uint32_t recv_data;

    MSDI_READ(IN_STAT_COMP, ui32DataRx);
    recv_data = ((ui32DataRx[0]<<16) | ui32DataRx[1]);

    if((recv_data & MSDI_POR_STAT_MASK) == MSDI_POR_STAT_MASK)
    {
        MSDI_REG_INI(msdi_info);
    }

    msdi_info->button_data = ((recv_data & IN_STAT_MASK)>>1);

    return;




}


/*Function Name: TEST_FUNC
**Description: Test function to see if files can build, and if data can be returned

uint32_t TEST_FUNC(uint32_t ui32Register,uint32_t pui32DataRx[])
{
    uint32_t rslt = MSDI_READ(ui32Register, pui32DataRx);

    return rslt;
}

*/



/*Function Name: MSDI_REG_INI
**Description: Test function to see if files can build, and if data can be returned
*/
void MSDI_REG_INI(msdi_var_t* msdi_info)
{
    uint32_t pui32DataRx[NUM_SSI_DATA];
   // uint32_t enable = 0x00F0000F;
    MSDI_WRITE(IN_EN, 0x00F8001F, pui32DataRx); //Enable IN0-4 and IN19-23

    //uint32_t cfig = 0x00000800;

    MSDI_WRITE(CS_SELECT, 0x00000000, pui32DataRx);//Battery connected

    MSDI_WRITE(WC_CFG0, 0x00000049, pui32DataRx); //Wetting Current 1mA

    MSDI_WRITE(WC_CFG1, 0x00049200, pui32DataRx); //Wetting Current 1mA

    //MSDI_WRITE(WC_CFG0, 0x00000000, pui32DataRx);  //Wetting Current 0mA

    //MSDI_WRITE(WC_CFG1, 0x00000000, pui32DataRx); //Wetting Current 0mA

    MSDI_WRITE(MODE, 0x00000000, pui32DataRx);

    

   // MSDI_WRITE(THRES_CFG4, 0x00002A800, pui32DataRx); //Set THRES9 to ADC Val 170(0xAA)

    //MSDI_WRITE(CONFIG, 0x000004E4, pui32DataRx);
    MSDI_WRITE(THRES_COMP, 0x00000F0F, pui32DataRx);

    MSDI_WRITE(CONFIG, 0x00000CE4, pui32DataRx);
    MSDI_WRITE(INT_EN_CFG1,0x00000155, pui32DataRx);
    MSDI_WRITE(INT_EN_CFG0, 0x00554000, pui32DataRx);


    


    //Read INT_Stat To clear 
    MSDI_READ(INT_STAT, pui32DataRx);

    return;
}
