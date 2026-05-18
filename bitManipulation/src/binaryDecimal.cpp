
#include <iostream>
using namespace std;
#include <string>

string dec2Bin(int num) {

	string res = "";
	
	while(num != 1)
	{
		if(num % 2 == 1)
			res+= '1';
		else 
			res+= '0';
	    
	    num = num/2;	
	
	}
	
	// res = reverse(res);
	
	return res;
}




int bin2Dec(string bNum)
{
	int res = 0;
	int numSize = bNum.length();
	int pwr = 1;
	
	for(int i = 0; i < numSize; i++)
	{
		res = res + (bNum[i] * pwr);
		pwr = pwr * 2;		
	}	
	
	return res;
}






