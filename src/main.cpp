#include "Serial.h"
#include <iostream>
#include <fstream>
#include <sstream>

int main() {
	std::cout << "Enter COM number: ";
	int portNumber;
	std::cin >> portNumber;
	std::stringstream ssPortName;
	ssPortName << "COM" << portNumber;

	size_t message_length = 0;
	std::cout << "Enter message lenght (max 512): ";
	std::cin >> message_length;
	if (message_length > 512) {
		std::cerr << "Wrong value\n";
		return -1;
	}

	Serial serial(ssPortName.str().c_str());
	if (!serial.IsInitialized())
		return -1;
	
	char buffer[513];

	std::ofstream log_file;
	log_file.open("log.txt", std::ios::app);
	if (!log_file.is_open()) {
		std::cerr << "Log file opening failure\n";
		return -1;
	}

	while (1) {
		DWORD bytesRead = serial.Read(buffer, 13);
		if (bytesRead) {
			buffer[message_length] = '\0';
			std::cout << "Recieved: " << buffer;
			log_file << buffer;
		}
	}
	log_file.close();

	return 0;
}