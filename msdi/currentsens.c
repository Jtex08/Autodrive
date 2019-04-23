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
#include <driverlib/adc.h>
#include "msdi.h"
#include "currentsens.h"


/*Function Name: init_current
**Description: Setup ADC0 for current samplings
**Parameters: void
**            
**Returns: Void
*/
void init_current()
{
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

    SysCtlADCSpeedSet(SYSCTL_ADCSPEED_250KSPS); //ADC Sample Rate set to 250 Kilo Samples Per Second

    ADCHardwareOversampleConfigure(ADC0_BASE, 64); // Hardware averaging. ( 2, 4, 8 , 16, 32, 64 )
    //64 Samples are averaged here i.e, each sample will be a result of 64 averaged samples. Therefore, every result is a result of 64 x 4 = 256 samples.

    ADCSequenceDisable(ADC0_BASE, 1); //Before Configuring ADC Sequencer 1, it should be OFF

    ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_PROCESSOR, 0);
    //ADC Configured so that Processor Triggers the sequence and we want to use highest priority. ADC Sequencer 0 is Used.

    ADCSequenceStepConfigure(ADC0_BASE, 0, 0, ADC_CTL_CH0); //Sequencer Step 0: Samples Channel PE3
    ADCSequenceStepConfigure(ADC0_BASE, 0, 1, ADC_CTL_CH1); //Sequencer Step 1: Samples Channel PE2
    ADCSequenceStepConfigure(ADC0_BASE, 0, 2, ADC_CTL_CH2 | ADC_CTL_IE | ADC_CTL_END); //Sequencer Step 2: Samples Channel PE1, Interrupt enable, last step
    

    ADCSequenceEnable(ADC0_BASE, 0); //Enable ADC Sequence

    return;




}



/*Function Name: current_sample
**Description: Get voltage readings sample for conversion to current readings
**Parameters: pointer to array for holding results
**            
**Returns: Void
*/

void current_sample(uint32_t adc_val[])
{
    ADCIntClear(ADC0_BASE, 0); // Clear ADC Interrupt
    ADCProcessorTrigger(ADC0_BASE, 0); // Trigger ADC Interrupt

    while(!ADCIntStatus(ADC0_BASE, 0, false)) //Wait for interrupt Status flag to go off
    {
    }

    //Conversion Complete

    ADCSequenceDataGet(ADC0_BASE, 0, adc_val); //Put sample results into adc_val

    return;
}


/*Function Name: sample_process
**Description: Process voltage readings to produce current results
**Parameters: Pointer to array with samples, pointer to array for holding results
**            
**Returns: Void
*/


void sample_process(uint32_t adc_val[], float results[])
{
    float Vref = 1650;
    float temp;
    float sensitivity = 18.5; 
    

    //Process adc_val[0] for ring sensor


    //Process rest for board sensors
    //Need Sensitivity 

    //12 bit onboard adc-> 3.3V/4096 ~=.806 mV

    temp = .806 * adc_val[1];

    results[1] = (temp - Vref) * sensitivity;


}