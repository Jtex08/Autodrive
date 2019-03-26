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



	uint32_t ui32ADC0Value[4];
	volatile uint32_t ui32TempAvg;
	volatile uint32_t ui32TempValueC; 
	volatile uint32_t ui32TempValueF; 
	// Enable the ADC0 module.
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
	ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_PROCESSOR, 0);
	ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_TS);
	ADCSequenceStepConfigure(ADC0_BASE, 1, 1, ADC_CTL_TS);
	ADCSequenceStepConfigure(ADC0_BASE, 1, 2, ADC_CTL_TS);
	ADCSequenceStepConfigure(ADC0_BASE,1,3,ADC_CTL_TS|ADC_CTL_IE|ADC_CTL_END);
	ADCSequenceEnable(ADC0_BASE, 1);
	
	
	while(1)
	{
        	ADCIntClear(ADC0_BASE, 1);
		ADCProcessorTrigger(ADC0_BASE, 1); 
		while(!ADCIntStatus(ADC0_BASE, 1, false))
		{
		}
	ADCSequenceDataGet(ADC0_BASE, 1, ui32ADC0Value);
	ui32TempAvg = (ui32ADC0Value[0] + ui32ADC0Value[1] + ui32ADC0Value[2] + ui32ADC0Value[3] + 2)/4;
	ui32TempValueC = (1475 - ((2475 * ui32TempAvg)) / 4096)/10;
	ui32TempValueF = ((ui32TempValueC * 9) + 160) / 5; 
   	 // Publish message to be transmitted.
    	temp_msg.data = ui32TempValueF;
    	pub_temp.publish(&temp_msg);

   	// Handle all communications and callbacks.
   	nh.spinOnce();

   	// Delay for a bit.
    	nh.getHardware()->delay(100);
	}
}


