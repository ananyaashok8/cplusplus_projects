/*
 * test.cpp
 *
 *  Created on: 19-Feb-2026
 *      Author: 91819
 */

#include "test.hpp"
#include <cstring>

void swap( char* a, char* b)
{
	if(a == b) return;

	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;

 	cout << *a << " and " << *b << endl;

}

void reverseTheString( char* val)
{
	char *start = val; // value at that address
	char *end = val + (strlen(val) - 1);

	char temp = '\0';


	while(start < end)
	{
		temp = *start;
	 	*start = *end;
	 	*end = temp;

	 	start++;
	 	end--;
	}

}



bool isPalindrome(char* val)
{
	bool isPal = true;

	char *start = val;
	char *end = val + (strlen(val) - 1);



	while(start < end)
	{

		if(*start != *end)
		{
			isPal = false;
			cout << "Oops!! Not a palindrome " << endl;
			break;
		}
		else
		{
			start++;
			end--;
		}
		cout <<"Yes, it is a palindrome " << endl;
	}

	return isPal;

}


void reverse(string &s, int start, int end)
{
	char temp = 0;


	while(start < end)
	{
		temp = s[start];
		s[start] = s[end];
		s[end] = temp;

		start++;
		end--;
	}

}



void reverseTheLine(string &str)
{

	int n = str.length();

	reverse(str, 0, n-1);


	int start = 0;

	for(int end = 0; end <=n; end++)
	{
		if((str[end] == ' ') || ( end == n))
		{
			reverse(str, start, end-1);
			start = end + 1;
		}
	}

	//cout << "Reversed line : " << str << endl;



}
