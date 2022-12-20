#ifndef http_json_stream_H
#define http_json_stream_H

#include "Print.h"
#include "Stream.h"
#include <Arduino.h>
#include "JsonStreamingParser2.h"

// Can set this to 1
#define CHARS_TO_PARSE_EACH_TIME 32

class ArudinoStreamParser: public Stream, public JsonStreamingParser  {
public:

    /** Clear the buffer */
    void clear(); 
    
    virtual size_t write(uint8_t);
    virtual size_t write(const uint8_t *buffer, size_t size);
    
    virtual int available();

    virtual int read();
    virtual int peek();
    virtual void flush();

    virtual int availableForWrite() { return CHARS_TO_PARSE_EACH_TIME; }    // 32 bytes at a go? Can set this to 1
    virtual bool outputCanTimeout () { return false; }


};


#endif
