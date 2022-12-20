/* 
 * An enhanced example where of the traditional JSON Stream Parser acts as a 'Streamable' interface
 * and takes the data directly from the WiFi receive buffers and begins parsing.
 *
 * Note: This sketch does nothing more than print to Serial how it views the received JSON.
 *       This sketch connects to a webserver and starts streaming a LARGE json file... so the speed
 *       of parsing is dependant on your Arduino device CPU and the speed of your WiFi internet.
 *       The size of the JSON file could be unlimited - but the time taken to parse will also increase.
 */
 
#define USE_HTTPS_MODE 1 

#include <WiFi.h>

  #ifdef USE_HTTPS_MODE
    #include <WiFiClientSecure.h>  
  #else
    #include <WiFiClient.h>                      
  #endif


#include <HTTPClient.h>  

#include "ExampleHandler.h"                 // Custom JSON document handler
#include <ArduinoStreamParser.h>            // <==== THE JSON Streaming Parser - Arduino STREAM WRAPPER


// IF not HTTPS
#ifndef USE_HTTPS_MODE
  WiFiClient client;
#endif  

HTTPClient http; // Used for both SSl and non-SSL connections


void printHeapFreeToSerial()
{
   Serial.print("Heap free:");
   Serial.println(String(ESP.getFreeHeap(), DEC));
}

void setup()
{
    Serial.begin(115200);
    Serial.println();

    for (uint8_t t = 4; t > 0; t--) {
      Serial.printf("[SETUP] WAIT %d...\n", t);
      Serial.flush();
      delay(500);
    }    

    WiFi.begin("<SSID>", "<PASSWORD>");
    
    Serial.print("Connecting");
    while (WiFi.status() != WL_CONNECTED)
    {
      delay(500);
      Serial.print(".");
    }
    Serial.println();
    
    Serial.print("Connected, IP address: ");
    Serial.println(WiFi.localIP());
    printHeapFreeToSerial();

  #ifdef USE_HTTPS_MODE
      std::unique_ptr<WiFiClientSecure>client(new WiFiClientSecure);
      client->setInsecure();
      printHeapFreeToSerial(); 
  #endif

    // 1. Create Parser and JSON Stream Handler
    ArudinoStreamParser parser;
    ExampleHandler custom_handler;
    
    // 2. Attach JSON Stream Handler
    parser.setHandler(&custom_handler); // Link to customer listener (parser to be honest)
    
    Serial.println("Setup JSON Streaming Parser.");
    printHeapFreeToSerial();    

    // Lets being
   #ifdef USE_HTTPS_MODE
    // http.begin(*client, "https://samples.openweathermap.org/data/2.5/forecast?q=London,us&appid=439d4b804bc8187953eb36d2a8c26a02");
    http.begin(*client, "https://tty.us.to/iot/bigjson.php");
   #else
    http.begin(client, "http://tty.us.to/iot/bigjson.php");
   #endif
    
    
    // start connection and send HTTP header
    Serial.println("Making HTTPS Connection.");
    printHeapFreeToSerial(); 
        
    int httpCode = http.GET();
    if (httpCode > 0) 
    {    
      
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);
      printHeapFreeToSerial();    
      
      // file found at server
      if (httpCode == HTTP_CODE_OK) 
      {
          Serial.print("Got payload response of length: "); Serial.println(http.getSize(), DEC);

          Serial.println("Parsing JSON...");
          printHeapFreeToSerial();

          // 3. Start parsing directly from http stream!
          http.writeToStream(&parser); 
      
          Serial.println("Completed Parsing.");
          printHeapFreeToSerial();   
        
      }
      
    } else {
       Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    
    http.end();
    
    Serial.println("Done.");    
    printHeapFreeToSerial();   
 
}


void loop() {
  // put your main code here, to run repeatedly:

}