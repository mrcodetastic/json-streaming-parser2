# HTTP/HTTPS Stream Parser

An enhanced example whereby we connect to a HTTPS JSON feed (web server) directly and use the Arduino HTTPClient class to send the received data directly to the parser as a 'Stream' interface.

* This sketch connects to a webserver and starts streaming a LARGE json file... so the speed of parsing is dependant on your Arduino device CPU and the speed of your WiFi internet.
* The size of the JSON file could be unlimited - but the time taken to parse will also increase.
 
Fast, efficient and doesn't require the JSON to be saved to memory as a String and then parsed character by character.

```
[SETUP] WAIT 4...
[SETUP] WAIT 3...
[SETUP] WAIT 2...
[SETUP] WAIT 1...
Starting.........
Heap free:51664  
Stack free:2320  
Connecting.........
Connected, IP address: 192.168.8.106
Heap free:50552
Stack free:2304
Setup JSON Streaming Parser.        
Heap free:50552
Stack free:2304
Making HTTPS Connection.
Heap free:50512
Stack free:2304
[HTTP] GET... code: 200
Heap free:48128
Stack free:2088
Got payload response of length: -1
Parsing JSON...
Heap free:48128
Stack free:2088
500 JSON objects parsed
We found John!
[501].first_name': "John"
[501].last_name': "Smith"
[501].email': "johhny.smith.asdadasda@gmail.com"
[501].gender': "Male"
[501].ip_address': "127.0.0.1"
1000 JSON objects parsed
1500 JSON objects parsed
2000 JSON objects parsed
2500 JSON objects parsed

(Parsing will continue until 50000 objects are parsed... about 2MB of Json)

```
