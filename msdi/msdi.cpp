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
 #include "currentsens.h"
}

// ROS includes
#include <ros.h>
#include <std_msgs/UInt32.h>
#include "rosserial_tivac_tutorials/Panel.h"
#include "rosserial_tivac_tutorials/Current.h"

// ROS nodehandle
ros::NodeHandle nh;

//Create ROS Messages
std_msgs::UInt32 raw_msg;
rosserial_tivac_tutorials::Panel  left_msg;
rosserial_tivac_tutorials::Current  amp_msg;

//Setup ROS Publishers
ros::Publisher pub_raw("raw_data", &raw_msg);
ros::Publisher lpanel("panel", &left_msg);
ros::Publisher amp("Current", &amp_msg);

int main(void)
{
  //Create local variables
  uint32_t adc_val[3];
  uint32_t results[3];

  // ROS nodehandle initialization and topic registration
  nh.initNode();

  /* Wait for connection to establish:  Added for testing to ease connection process
  Untested as of 4202019

  while (!nh.connected())
  {
    nh.spinOnce();
    nh.getHardware()->delay(10);
  }

*/
  nh.advertise(pub_raw);
  nh.advertise(lpanel);
  nh.advertise(amp);


//  uint32_t ui32DataTx[NUM_SSI_DATA];
//  uint32_t ui32Index;
  uint32_t pui32DataRx[NUM_SSI_DATA];

 char info[11] = "Left Panel";
 left_msg.panel_location.data = info;

 char sens[15] = "Current Sensor";
 amp_msg.sensor.data = sens;


  //Create MSDI struct var
  msdi_var_t pan_one;

  //Initalize which device is being used 
  pan_one.device = MSDI0;



  


  //Set system clock

  SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
                   SYSCTL_XTAL_16MHZ);

  //Initiate SPI and MSDI

  MSDI_Init(&pan_one);
  
  //ADC initiate for current sensors
  init_current;


    while(1)
    {
      //Trigger ADC 
     current_sample(adc_val);

     //Process Results
     sample_process(adc_val, results);


    //Place Results in ROS message and send
     amp_msg.server.data = results[0];
     amp_msg.panelzero.data = results[1];
     amp_msg.panelone.data = results[2];

     amp.publish(&amp_msg);

     nh.spinOnce();


     nh.getHardware()->delay(50);

    //Read Button Status Register
     MSDI_GET_BUTTON_STATUS(&pan_one);

    //Store output  data for debug
     raw_msg.data = pan_one.button_data;
     pub_raw.publish(&raw_msg);

     nh.spinOnce();
     
     // Delay
     nh.getHardware()->delay(50);


    left_msg.btn1.data = ((pan_one.button_data & 0x00000001)==(0x00000001));
	  left_msg.btn2.data = ((pan_one.button_data & 0x00000002)==(0x00000002));
	  left_msg.btn3.data = ((pan_one.button_data & 0x00000004)==(0x00000004));
	  left_msg.btn4.data = ((pan_one.button_data & 0x00000008)==(0x00000008));
    left_msg.btn5.data = ((pan_one.button_data & 0x00000010)==(0x00000010));
    left_msg.btn6.data = ((pan_one.button_data & 0x00080000)==(0x00080000));
    left_msg.btn7.data = ((pan_one.button_data & 0x00100000)==(0x00100000));
    left_msg.btn8.data = ((pan_one.button_data & 0x00200000)==(0x00200000));
    left_msg.btn9.data = ((pan_one.button_data & 0x00400000)==(0x00400000));
    left_msg.btn10.data =((pan_one.button_data & 0x00800000)==(0x00800000));

    lpanel.publish(&left_msg);

    nh.spinOnce();

    nh.getHardware()->delay(50);   


     
    }
     

}







