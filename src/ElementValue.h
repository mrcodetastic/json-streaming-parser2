#ifndef ELEMENT_VALUE_H
#define ELEMENT_VALUE_H

#include <Arduino.h>

union Variant {
  bool boolValue;
  float numValue;
  const char* stringValue;
};

struct ElementValue {
  private:
    static const int Type_Null = 0;
    static const int Type_Int = 1;
    static const int Type_Float = 2;
    static const int Type_String = 3;
    static const int Type_Bool = 4;

    Variant data;
    int type;

  public:
    ElementValue with(float value) {
      data.numValue = value;
      type = Type_Float;
      return *this;
    }

    ElementValue with(long value) {
      data.numValue = value;
      type = Type_Int;
      return *this;
    }
    
    ElementValue with(bool value) {
      data.boolValue = value;
      type = Type_Bool;
      return *this;
    }

    ElementValue with(const char* value) {
      data.stringValue = value;
      type = Type_String;
      return *this;
    }

    ElementValue with() {
      type = Type_Null;
      return *this;
    }
    
    bool getBool() {
      return data.boolValue;
    }

    const char* getString() {
      return data.stringValue;
    }

    float getFloat() {
      return data.numValue;
    }

    long getInt() {
      return (long)data.numValue;
    }

    bool isInt() {
      return type == Type_Int;
    }

    bool isFloat() {
      return type == Type_Float;
    }

    bool isString() {
      return type == Type_String;
    }

    bool isBool() {
      return type == Type_Bool;
    }

    bool isNull() {
      return type == Type_Null;
    }
    
    char* toString(char* buffer, size_t bufferSize = 50) {
      if (buffer == nullptr || bufferSize == 0) {
        return buffer;
      }
      
      if(isInt()) {
        snprintf(buffer, bufferSize, "%ld", getInt()); // long int
      } else if(isFloat()) {
        snprintf(buffer, bufferSize, "%f", getFloat());
      } else if(isString()) {
        snprintf(buffer, bufferSize, "\"%s\"", getString()); // Note: This adds "'s (quote symbols) either side of the actual string value.
      } else if(isBool()) {
        strncpy(buffer, getBool() ? "true" : "false", bufferSize - 1);
        buffer[bufferSize - 1] = '\0';
      } else if(isNull()) {
        strncpy(buffer, "null", bufferSize - 1);
        buffer[bufferSize - 1] = '\0';
      } else {
        strncpy(buffer, "?", bufferSize - 1);
        buffer[bufferSize - 1] = '\0';
      }
      return buffer;
    }
};

#endif // ELEMENT_VALUE_H