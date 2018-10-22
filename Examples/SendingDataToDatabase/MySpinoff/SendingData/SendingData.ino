//#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
const char* ssid     = "sebi";
const char* password = "9172321736";
ESP8266WebServer server(80);
WiFiClient client;
MDNSResponder mdns; //multicast Domain Name System
String p_name="";
String p_age="";
 
//float humidity, temp_f;  // Values read from sensor
String webPage = "";

//int gpio0_pin = 13;
//int gpio2_pin = 14;
//int f =0;
// Generally, you should use "unsigned long" for variables that hold time
//unsigned long previousMillis = 0;        // will store last temp was read
//const long interval = 2000;              // interval at which to read sensor
 

 
void setup(void)
{
//  webPage += "<h1>ESP8266 Web Server</h1><p>Socket #1 <a href=\"socket1On\"><button>ON</button></a>&nbsp;<a href=\"socket1Off\"><button>OFF</button></a></p>";
//  webPage += "<p>Socket #2 <a href=\"socket2On\"><button>ON</button></a>&nbsp;<a href=\"socket2Off\"><button>OFF</button></a></p>";
  webPage+="<h1>Hello now connected to web server.<h1>";
// preparing GPIOs
//  pinMode(gpio0_pin, OUTPUT);
//  digitalWrite(gpio0_pin, LOW);
//  pinMode(gpio2_pin, OUTPUT);
//  digitalWrite(gpio2_pin, LOW);
  
  Serial.begin(115200);  //baude rate .... Serial connection from ESP-01 via 3.3v console cable
  delay(1000);
 Serial.println("Hii ");
 /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
would try to act as both a client and an access-point and could cause
network-issues with your other WiFi-devices on your WiFi-network. */
WiFi.mode(WIFI_STA);
  // Connect to WiFi network
  WiFi.begin(ssid, password);
  Serial.print("\n\r \n\rWorking to connect");
 
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }
 server.on("/", [](){
    server.send(200, "text/html", webPage);
  });
//  server.on("/socket1On", [](){
//    server.send(200, "text/html", webPage);
//    digitalWrite(gpio0_pin, HIGH);
//    delay(1000);
//  });
//  server.on("/socket1Off", [](){
//    server.send(200, "text/html", webPage);
//    digitalWrite(gpio0_pin, LOW);
//    delay(1000); 
//  });
//  server.on("/socket2On", [](){
//    server.send(200, "text/html", webPage);
//    digitalWrite(gpio2_pin, HIGH);
//    delay(1000);
//  });
//  server.on("/socket2Off", [](){
//    server.send(200, "text/html", webPage);
//    digitalWrite(gpio2_pin, LOW);
//    delay(1000); 
//  });
  server.begin();
  Serial.println("HTTP server started");
  delay(10000);
  
  
}
 
void loop(void)
{
  // Wait a few seconds between measurements.
  delay(100);
  Serial.println("Enter name:-");
  if(Serial.available()>0)
  p_name=Serial.read();
  Serial.println("Enter age:-");
  if(Serial.available()>0)
  p_age=Serial.read();
    server.handleClient();
//    if ( f <3 ){Serial.println("\nStarting connection to server..."); }
  if (client.connect("192.168.0.105", 80)) {
if (p_name!="" and p_age!="") {
//   if ( f <3 ){Serial.println("connected to server");}
    
    client.print("GET /write_data.php?"); // This
    client.print("p_name="); // This
    client.print(p_name); // And this is what we did in the testing section above. We are making a GET request just like we would from our browser but now with live data from the sensor
    client.print("&p_age=");
    client.print(p_age);
    client.println(" HTTP/1.1"); // Part of the GET request
    client.println("Host: 127.0.0.1"); // IMPORTANT: If you are using XAMPP you will have to find out the IP address of your computer and put it here 
    client.println("Connection: close"); // Part of the GET request telling the server that we are over transmitting the message
    client.println(); // Empty line
    client.println(); // Empty line
    client.stop();    // Closing connection to server
    }
  }
    else {
    // If Arduino can't connect to the server (your computer or web page)
    Serial.println("--> connection failed\n");
  }
    p_name="";
    p_age="";
  //delay(10000); 
} 



