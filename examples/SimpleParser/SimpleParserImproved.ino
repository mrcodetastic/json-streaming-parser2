/* 
 * Enhanced example of the JSON Stream Parser with improved error handling
 * and safety features added in version 2.1.0+
 */ 
#include "JsonStreamingParser2.h" 
#include "JsonHandler.h"
#include "SimpleHandler.h"

JsonStreamingParser parser;
SimpleHandler handler;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting JSON Stream Parser Example with Error Handling");
  Serial.print("Free heap: ");
  Serial.println(String(ESP.getFreeHeap()));

  // Set the custom handler
  parser.setHandler(&handler);
  
  // Test valid JSON
  Serial.println("\n=== Testing Valid JSON ===");
  char validJson[] = "{\"mykey\":100, \"b\":{\"c\":\"d\"}, \"array\":[1,2,3]}";
  parseJsonString(validJson, "Valid JSON");
  
  // Test invalid JSON (missing closing brace)
  Serial.println("\n=== Testing Invalid JSON (missing closing brace) ===");
  parser.reset(); // Reset parser state
  char invalidJson1[] = "{\"mykey\":100, \"b\":{\"c\":\"d\"";
  parseJsonString(invalidJson1, "Invalid JSON (missing brace)");
  
  // Test invalid JSON (invalid character)
  Serial.println("\n=== Testing Invalid JSON (invalid character) ===");
  parser.reset();
  char invalidJson2[] = "{\"mykey\":100, \"invalid\":@}";
  parseJsonString(invalidJson2, "Invalid JSON (bad character)");
  
  // Test very long string that would cause buffer overflow
  Serial.println("\n=== Testing Buffer Overflow Protection ===");
  parser.reset();
  String longJson = "{\"very_long_key\":\"";
  for(int i = 0; i < 300; i++) { // Create a string longer than buffer
    longJson += "a";
  }
  longJson += "\"}";
  parseJsonString(longJson.c_str(), "Buffer overflow test");

  Serial.println("\n=== All Tests Complete ===");
  Serial.print("Final free heap: ");
  Serial.println(String(ESP.getFreeHeap()));
}

void parseJsonString(const char* json, const char* testName) {
  Serial.print("Parsing: ");
  Serial.println(testName);
  
  int len = strlen(json);
  for (int i = 0; i < len; i++) {
    parser.parse(json[i]); // Parse character by character
    
    // Check for errors after each character
    if (parser.hasParseError()) {
      Serial.print("ERROR: ");
      Serial.println(parser.getErrorMessage());
      Serial.print("Error occurred at character position: ");
      Serial.println(parser.getCharacterCount());
      Serial.print("Current buffer position: ");
      Serial.println(parser.getBufferPosition());
      Serial.print("Current stack depth: ");
      Serial.println(parser.getStackDepth());
      break; // Stop parsing on error
    }
  }
  
  if (!parser.hasParseError()) {
    Serial.println("Parsing completed successfully!");
    Serial.println(handler.getMyKeyString());
  }
  
  Serial.println("--------------------------------");
}

void loop() {
  // put your main code here, to run repeatedly:
}
