//============================================================================
// Name        : CircularBuffer.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

#define BUFFER_SIZE 8

struct SensorBuffer {
    int data[BUFFER_SIZE];
    int* writePtr;
    int* readPtr;
    int count;
};

void initBuffer(SensorBuffer* buf)
{

};

bool writeSensorValue(SensorBuffer* buf, int value)
{
	bool val;
	return val;
};

bool readSensorValue(SensorBuffer* buf, int* outValue)
{
	bool val;
	return val;
};

void printBufferStatus(const SensorBuffer* buf)
{

};


