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
#include <std_msgs/UInt32.h>
#include "rosserial_tivac_tutorials/Panel.h"

// ROS nodehandle
ros::NodeHandle nh;

std_msgs::UInt32 raw_msg;
rosserial_tivac_tutorials::Panel  left_msg;
ros::Publisher pub_raw("raw_data", &raw_msg);
ros::Publisher lpanel("panel", &left_msg);

int main(void)
{
  


  // ROS nodehandle initialization and topic registration
  nh.initNode();
  nh.advertise(pub_raw);
  nh.advertise(lpanel);

//  uint32_t ui32DataTx[NUM_SSI_DATA];
//  uint32_t ui32Index;
  uint32_t pui32DataRx[NUM_SSI_DATA];

 // char info[11] = "Left Panel";
 // left_msg.panel_location.data = info;

  msdi_var_t pan_one;



  /*spiConfig = {SYSCTL_PERIPH_SSI0, SYSCTL_PERIPH_GPIOA, SSI0_BASE, GPIO_PA2_SSI0CLK,
                GPIO_PA4_SSI0RX, GPIO_PA5_SSI0TX, GPIO_PORTA_BASE, GPIO_PIN_3, GPIO_PIN_2,
                GPIO_PIN_4, GPIO_PIN_5}; */

  


  //Begin SPI setup

  SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
                   SYSCTL_XTAL_16MHZ);

  //SSI_Init(&spiConfig);

  MSDI_Init(SPI_0, &pan_one);

 // left_msg.panel_location.data = pan_one->location;

      nh.getHardware()->delay(500);
    uint32_t TFT = TEST_FUNC_TWO(IN_STAT_COMP, pui32DataRx);

     raw_msg.data = TFT;
     pub_raw.publish(&raw_msg);

     nh.spinOnce();
     
     // Delay for a bit.
     nh.getHardware()->delay(500);

     raw_msg.data = pui32DataRx[0];
     pub_raw.publish(&raw_msg);

     nh.spinOnce();
     
     // Delay for a bit.
     nh.getHardware()->delay(500);

     
     raw_msg.data = pui32DataRx[1];
     pub_raw.publish(&raw_msg);

     nh.spinOnce();
     
     // Delay for a bit.
     nh.getHardware()->delay(500);


    while(1)
    {

    uint32_t rslt = TEST_FUNC(IN_EN,pui32DataRx);

     raw_msg.data = rslt;
     pub_raw.publish(&raw_msg);

     nh.spinOnce();
     
     // Delay for a bit.
     nh.getHardware()->delay(500);

     raw_msg.data = pui32DataRx[0];
     pub_raw.publish(&raw_msg);

     nh.spinOnce();
     
     // Delay for a bit.
     nh.getHardware()->delay(500);

     
     raw_msg.data = pui32DataRx[1];
     pub_raw.publish(&raw_msg);

     nh.spinOnce();
     
     // Delay for a bit.
     nh.getHardware()->delay(500);


     
    }
     

}







