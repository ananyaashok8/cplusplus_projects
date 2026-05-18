/*
 * pointer.cpp
 *
 *  Created on: 15-Feb-2026
 *      Author: 91819
 */

#include <iostream>
using namespace std;
#include <string>
#include <cstring>
#include "pointer.h"

void testPointer()
{
	int* ptr = 0; // initializing a pointer of type void to 0
	int var = 8;
	void* ptr1 = NULL;
	ptr = &var; // simple assignment of address where var is stored is copied into the pointer

	*ptr = 10;
	cout << " Int pointer: " << *ptr << " -> " << &ptr << endl; // prints !!!Hello
	cout <<  " Null pointer: addrerss -> " << &ptr1 << endl;

	// allocation on heap
	char* buffer = new char[8];
	memset(buffer,'a',8);
	buffer[0] = '1';

	cout << " char pointer: buffer" << " -> " << (char)buffer[0] << " -> "<< &buffer << endl; // prints !!!Hello

	delete[] buffer; // heap memory needs to be deleted manually

}



