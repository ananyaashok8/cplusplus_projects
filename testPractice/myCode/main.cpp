// Standard (system) header files
#include <iostream>
#include <cstdlib>
// Add more standard header files as required

#include "test.hpp"
#include <string>

using namespace std;

// Add your project's header files here
// #include "CFraction.h"

// Main program
int main ()
{
    // TODO: Add your program code here
	cout << "testPractice started." << endl << endl;

	char str[] = "madam2";

	reverseTheString(str);

	cout << "Reversed string is : " << str << endl;

	isPalindrome(str);

	char a = '7';
	char b = '6';

	swap(&a,&b);

	string l1 = "My name is Khan";
	reverseTheLine(l1);

	cout << "Reversed line is : " << l1 << endl;

	return 0;
}
