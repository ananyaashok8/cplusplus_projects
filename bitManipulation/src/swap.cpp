/*
 * swap.cpp
 *
 *  Created on: 13-Feb-2026
 *      Author: 91819
 */

void swap(int a , int b)
{
	// without using third variable
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;

}






