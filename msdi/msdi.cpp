//Standard Library Includes
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// TivaC specific includes
extern "C"
{
 #include "inc/hw_memmap.h"
 #include "driverlib/gpio.h"
 #include "driverlib/pin_map.h"
 #include "driverlib/ssi.h"
 #include "driverlib/sysctl.h"
 #include <inc/hw_types.h>
 #include <driverlib/debug.h>
 #include "msdi.h"
}

// ROS includes
#include <ros.h>
#include <std_msgs/Int32.h>
#include "rosserial_tivac_tutorials/Panel.h"

// ROS nodehandle
ros::NodeHandle nh;

std_msgs::Int32 raw_msg;
rosserial_tivac_tutorials::Panel  left_msg;
ros::Publisher pub_raw("raw_data", &raw_msg);
ros::Publisher lpanel("panel", &left_msg);

int main(void)
{
  


  // ROS nodehandle initialization and topic registration
  nh.initNode();
  nh.advertise(pub_raw);
  nh.advertise(lpanel);

  char info[11] = "Left Panel";
  left_msg.panel_location.data = info;


  //Begin SPI setup

   SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
                   SYSCTL_XTAL_16MHZ);
    
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA))
    {
    }

    GPIOPinConfigure(GPIO_PA2_SSI0CLK);
    GPIOPinConfigure(GPIO_PA3_SSI0FSS);
    GPIOPinConfigure(GPIO_PA4_SSI0RX);
    GPIOPinConfigure(GPIO_PA5_SSI0TX);

    //If SSI0FSS fails to work switch to direct control
    //GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE,GPIO_PIN_3);

    //Set GPIO Pin type to SSI

    GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_4 | GPIO_PIN_3| GPIO_PIN_2);


    //Config SSI Clock for SSIO with Polarity and Phase 0
    SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0,
                       SSI_MODE_MASTER, 2000000, 16);

    //
    // Enable the SSI0 module.
    //
    SSIEnable(SSI0_BASE);

    /*Read Function
    Take register you want to read
    Shift left one
    Do parity check and set if needed
    Split data into two 16 bit words
    Transmit both words

    Get data in two 16 bit words

    Shift MSBs left 8 bits then or with LSBs for full 32 bit value.*/
    
