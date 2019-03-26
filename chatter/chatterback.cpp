#include <stdbool.h>
#include <stdint.h>
// TivaC specific includes
extern "C"
{
  #include <driverlib/sysctl.h>
  #include <driverlib/gpio.h>
  #include <inc/hw_memmap.h>
  #include <inc/hw_types.h>
  #include <driverlib/debug.h>
  #include <driverlib/adc.h>
}
// ROS includes
#include <ros.h>
#include <std_msgs/Float32.h>

// ROS nodehandle
ros::NodeHandle nh;

std_msgs::Float32 temp_msg;
ros::Publisher pub_temp("chatter", &temp_msg);



int main(void)
{
  


  // ROS nodehandle initialization and topic registration
  nh.initNode();
  nh.advertise(pub_temp);

  while (1)
  {
		uint32_t ui32Value;
	 
		//
		// Enable the ADC0 module.
		//
		SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
		//
		// Wait for the ADC0 module to be ready.
		//
		while(!SysCtlPeripheralReady(SYSCTL_PERIPH_ADC0))
		{
		}
		//
		// Enable the first sample sequencer to capture the value of channel 0 when
		// the processor trigger occurs.
		//
		ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_PROCESSOR, 0);
		ADCSequenceStepConfigure(ADC0_BASE, 0, 0,
		ADC_CTL_IE | ADC_CTL_END | ADC_CTL_CH0);
		ADCSequenceEnable(ADC0_BASE, 0);
		//
		// Trigger the sample sequence.
		//
		ADCProcessorTrigger(ADC0_BASE, 0);
		//
		// Wait until the sample sequence has completed.
		//
		while(!ADCIntStatus(ADC0_BASE, 0, false))
		{
		}
		//
		// Read the value from the ADC.
		//
		ADCSequenceDataGet(ADC0_BASE, 0, &ui32Value);
 
		int current = (3300/4095) * ui32Value;
	

	   
    // Publish message to be transmitted.
    temp_msg.data = temperature;
    pub_temp.publish(&temp_msg);

    // Handle all communications and callbacks.
    nh.spinOnce();

    // Delay for a bit.
    nh.getHardware()->delay(100);
	
	
  }
}
