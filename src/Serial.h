#pragma once

#include <Windows.h>

class Serial
{
public:
	Serial(const char* portName);
	~Serial();

	DWORD Read(char* buffer, unsigned int bytesToRead);
	bool IsInitialized() const { return initialized; }
private:
	HANDLE hSerial;
	COMSTAT status;
	DWORD errors;

	bool initialized;
};

