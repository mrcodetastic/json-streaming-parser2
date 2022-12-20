#include "ArduinoStreamParser.h"

size_t ArudinoStreamParser::write(uint8_t data) 
{
	parse(data);

	return 1;
}

size_t ArudinoStreamParser::write(const uint8_t *buffer, size_t size)
{
	for (unsigned int i = 0; i < size; i++) {
		parse(buffer[i]);
	}
	//parse(data);
		
	return size;
}

int ArudinoStreamParser::available() {
	
    return 1;
}

int ArudinoStreamParser::read() {
	
    return 0;
}

int ArudinoStreamParser::peek() {
	
    return 0;
}

void ArudinoStreamParser::flush() {
	
  
}