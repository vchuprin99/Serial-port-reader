#include "Serial.h"

#include <iostream>

Serial::Serial(const char* portName)
	: hSerial(0), status({0}), errors(0), initialized(false)
{
	hSerial = CreateFile(
		portName,
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (hSerial == INVALID_HANDLE_VALUE) {
		DWORD err = GetLastError();
		switch (err)
		{
		case ERROR_FILE_NOT_FOUND:
		{
			std::cerr << "Error: wrong port\n";
			break;
		}
		case ERROR_ACCESS_DENIED:
		{
			std::cerr << "Error: access denied, port may be already occupied\n";
			break;
		}

		default:
		{
			std::cerr << "Error, code - " << err;
			break;
		}
		}

		return;
	}
	DCB serialParams = { 0 };
	if (!GetCommState(hSerial, &serialParams)) {
		std::cerr << "GetCommState() failure\n";
		return;
	}
	serialParams.BaudRate = CBR_9600;
	serialParams.ByteSize = 8;
	serialParams.StopBits = ONESTOPBIT;
	serialParams.Parity = NOPARITY;
	serialParams.fDtrControl = DTR_CONTROL_ENABLE;
	if (!SetCommState(hSerial, &serialParams)) {
		std::cerr << "SetCommState() failure\n";
		return;

	}
	PurgeComm(hSerial, PURGE_RXCLEAR | PURGE_TXCLEAR);
	initialized = true;

	std::cout << "Successful connected to " << portName << "\n";
}

Serial::~Serial()
{
	CloseHandle(hSerial);
}

DWORD Serial::Read(char* buffer, unsigned int bytesToRead)
{
	if (initialized) {
		DWORD bytesRead;

		ClearCommError(hSerial, &errors, &status);
		if (status.cbInQue > 0) {
			if (status.cbInQue < bytesToRead) {
				return 0;
			}
			if (ReadFile(hSerial, buffer, bytesToRead, &bytesRead, NULL))
			{
				return bytesRead;
			}
		}
	}
	return 0;
}
