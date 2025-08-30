#include "ArduinoStreamParser.h"

size_t ArduinoStreamParser::write(uint8_t data) 
{
	parse(data);

	return 1;
}

size_t ArduinoStreamParser::write(const uint8_t *buffer, size_t size)
{
	for (unsigned int i = 0; i < size; i++) {
		parse(buffer[i]);
	}
	//parse(data);
		
	return size;
}

int ArduinoStreamParser::available() {
	
    return 1;
}

int ArduinoStreamParser::read() {
	
    return 0;
}

int ArduinoStreamParser::peek() {
	
    return 0;
}

void ArduinoStreamParser::flush() {
	
  
}