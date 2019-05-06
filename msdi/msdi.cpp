/*Texas A&M University
**Electronic Systems Engineering Technology
**ESET 420 Capstone II
**Author: Jonathan Noland
**File: msdi.cpp
**------------------------------------------------------------------------------
**This is the primary file for use with the power monitoring system
*/


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
 #include "inc/hw_gpio.h"
 #include "driverlib/sysctl.h"
 #include "driverlib/rom.h"
 #include "driverlib/rom_map.h"
 #include "driverlib/gpio.h"
 #include "buttonalt.h"
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
rosserial_tivac_tutorials::Panel  left_msg;
rosserial_tivac_tutorials::Current  amp_msg;

//Setup ROS Publishers
ros::Publisher lpanel("panel", &left_msg);
ros::Publisher amp("Current", &amp_msg);

int main(void)
{
  //Create local variables
  uint32_t adc_val[3];
  float results[3];

  uint32_t button_state_left;
  uint32_t button_state_right;

  // ROS nodehandle initialization and topic registration
  nh.initNode();

  /* Wait for connection to establish:  */



 // nh.advertise(pub_raw);
  nh.advertise(lpanel);
  nh.advertise(amp);


  /* Wait for connection to establish:  */
  while (!nh.connected())
  {
    nh.spinOnce();
    nh.getHardware()->delay(10);
  }


  uint32_t pui32DataRx[NUM_SSI_DATA];


//Fill in message names
 char info[11] = "Left Panel";
 left_msg.panel_location.data = info;

 char sens[15] = "Current Sensor";
 amp_msg.sensor.data = sens;





  


  //Set system clock

  SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
                   SYSCTL_XTAL_16MHZ);


  //Initiate GPIO
  ButtonsInit();
  
  //ADC initiate for current sensors
  init_current();

   nh.getHardware()->delay(500);
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


     nh.getHardware()->delay(100);



    //Read Button Status Register

    ButtonsPoll(&button_state_left, &button_state_right);


    //Place Results in ROS message and send
    left_msg.btn1.data = button_state_left & BTN_ONE;
    left_msg.btn2.data = button_state_left & BTN_TWO;
    left_msg.btn3.data = button_state_left & BTN_THREE;
    left_msg.btn4.data = button_state_left & BTN_FOUR;
    left_msg.btn5.data = button_state_left & BTN_FIVE;
    left_msg.btn6.data = button_state_right & BTN_SIX;
    left_msg.btn7.data = button_state_right & BTN_SEVEN;
    left_msg.btn8.data = button_state_right & BTN_EIGHT;
    left_msg.btn9.data = button_state_right & BTN_NINE;
    left_msg.btn10.data = button_state_right & BTN_TEN;

    lpanel.publish(&left_msg);

    nh.spinOnce();

    nh.getHardware()->delay(100);   


     
    }
     

}







