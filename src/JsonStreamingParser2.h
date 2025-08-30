#ifndef JSON_STREAMING_PARSER2_H
#define JSON_STREAMING_PARSER2_H

#include <Arduino.h>
#include "JsonHandler.h"

#define STATE_START_DOCUMENT     0
#define STATE_DONE               -1
#define STATE_IN_ARRAY           1
#define STATE_IN_OBJECT          2
#define STATE_END_KEY            3
#define STATE_AFTER_KEY          4
#define STATE_IN_STRING          5
#define STATE_START_ESCAPE       6
#define STATE_UNICODE            7
#define STATE_IN_NUMBER          8
#define STATE_IN_TRUE            9
#define STATE_IN_FALSE           10
#define STATE_IN_NULL            11
#define STATE_AFTER_VALUE        12
#define STATE_UNICODE_SURROGATE  13

#define STACK_OBJECT             0
#define STACK_ARRAY              1
#define STACK_KEY                2
#define STACK_STRING             3

#ifndef JSON_PARSER_BUFFER_MAX_LENGTH
#define JSON_PARSER_BUFFER_MAX_LENGTH  256
#endif

#ifndef JSON_PARSER_STACK_MAX_DEPTH
#define JSON_PARSER_STACK_MAX_DEPTH    20
#endif

#ifndef JSON_PARSER_PATH_MAX_DEPTH
#define JSON_PARSER_PATH_MAX_DEPTH     20
#endif

class JsonStreamingParser {
  private:

    int state;
    int stack[JSON_PARSER_STACK_MAX_DEPTH];
    int stackPos = 0;
    
    ElementValue elementValue;
    ElementPath path;
    
    JsonHandler* myHandler;

    boolean doEmitWhitespace = false;
	
    // fixed length buffer array to prepare for c code
    char buffer[JSON_PARSER_BUFFER_MAX_LENGTH];
    int bufferPos = 0;

    char unicodeEscapeBuffer[10];
    int unicodeEscapeBufferPos = 0;

    char unicodeBuffer[10];
    int unicodeBufferPos = 0;

    int characterCounter = 0;

    int unicodeHighSurrogate = 0;

    // Error handling
    bool hasError = false;
    const char* errorMessage = nullptr;

    void increaseBufferPointer();

    void endString();

    void endArray();

    void startValue(char c);

    void startKey();

    void processEscapeCharacters(char c);

    boolean isDigit(char c);

    boolean isHexCharacter(char c);

    char convertCodepointToCharacter(int num);

    void endUnicodeCharacter(int codepoint);

    void startNumber(char c);

    void startString();

    void startObject();

    void startArray();

    void endNull();

    void endFalse();

    void endTrue();

    void endDocument();

    int convertDecimalBufferToInt(char myArray[], int length);

    void endNumber();

    void endUnicodeSurrogateInterstitial();

    boolean doesCharArrayContain(char myArray[], int length, char c);

    int getHexArrayAsDecimal(char hexArray[], int length);

    void processUnicodeCharacter(char c);

    void endObject();

  public:
    JsonStreamingParser();
    void parse(char c);
    void setHandler(JsonHandler* handler);
    void reset();
    
    // Error handling methods
    bool hasParseError() const { return hasError; }
    const char* getErrorMessage() const { return errorMessage; }
    void clearError() { hasError = false; errorMessage = nullptr; }
    
    // Buffer status methods
    int getBufferPosition() const { return bufferPos; }
    int getMaxBufferSize() const { return JSON_PARSER_BUFFER_MAX_LENGTH; }
    int getStackDepth() const { return stackPos; }
    int getCharacterCount() const { return characterCounter; }
};

#endif // JSON_STREAMING_PARSER2_H
