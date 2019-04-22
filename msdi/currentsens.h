/*Texas A&M University
**Electronic Systems Engineering Technology
**ESET 420 Capstone II
**Author: Jonathan Noland
**File: adcproj.h
**------------------------------------------------------------------------------
**This file contains the definitions and includes neccessary to use ADC and current sensprs
*/

#ifndef __CURRENTSENS_H__
#define __CURRENTSENS_H__

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>



/*
**API
*/

/*Function Name: init_current
**Description: Setup ADC0 for current samplings
**Parameters: void
**            
**Returns: Void
*/

void init_current(void);


/*Function Name: current_sample
**Description: Get voltage readings sample for conversion to current readings
**Parameters: pointer to array for holding results
**            
**Returns: Void
*/

void current_sample(uint32_t adc_val[]);

/*Function Name: sample_process
**Description: Process voltage readings to produce current results
**Parameters: Pointer to array with samples, pointer to array for holding results
**            
**Returns: Void
*/

void sample_process(uint32_t adc_val[], results[]);