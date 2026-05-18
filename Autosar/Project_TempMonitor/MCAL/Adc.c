/* MCAL Layer for ADC Driver*/

#included "Adc.h"

/* Function to start ADC Conversion */

void Adc_StartGroupConversion ( Adc_GroupType Group)
{
	If(Group == 1)
	{
		/* Write our code to start ADC */
		
	}
	
}

/* Function API to read ADC Group */

Std_ReturnType Adc_ReadGroup( Adc_GroupType Group, Adc_ValueGroupType* DataBufferPtr )
{
	unsigned int ADCValue;
	
	if(Group == 1)
	{
		ADCValue = SomeRegister;
		*DataBufferPtr = ADCValue; // Write back ADC Value
	}
		
		
}