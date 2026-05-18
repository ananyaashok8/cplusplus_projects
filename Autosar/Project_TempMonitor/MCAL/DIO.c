/* MCAL Layer for DIO Driver*/


#include "Dio.h"

/* Function API to Read a channel*/
Dio_LevelType Dio_ReadChannel( Dio_ChannelType ChnnelId)
{
	// Assuming Channel 10 is mapped to port 2.0
	if(ChnnelId == 10)
	{
		unsigned int ReadVal = 0;
		ReadVal = P2IN & BIT0;
		
		if(ReadVal == 0x00)
			return (STD_LOW);
		else 
			return (STD_HIGH);
	}
	// Continues for the other channels
}


/* Function API to Write to a port*/
Dio_LevelType Dio_WriteChannel( Dio_ChannelType ChannelId, Dio_LevelType level)
{
	// Assuming Channel 10 is mapped to port 2.0
	if(ChnnelId == 10)
	{
		if(level == STD_LOW	) {
			P2OUT &= ~BIT0;		// Code to set PIN LOW	
		}
		else {
			P2OUT |= ~BIT0; 	// Code to set PIN HIGH	
		}
	
	}
	// Continues for the other channels

}