/*
 * HTTP Client POST Request
 * Copyright (c) 2018, circuits4you.com
 * All rights reserved.
 * https://circuits4you.com 
 * Connects to WiFi HotSpot. */

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

/* Set these to your desired credentials. */
const char *ssid = "Test";  //ENTER YOUR WIFI SETTINGS
const char *password = "qwerty00000";

//Web/Server address to read/write from 
const char *host = "192.168.1.101";   //https://circuits4you.com website or IP address of server

//=======================================================================
//                    Power on setup
//=======================================================================

void setup() {
  delay(1000);
  Serial.begin(115200);
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
}

//=======================================================================
//                    Main Program Loop
//=======================================================================



void loop() {
  HTTPClient http;    //Declare object of class HTTPClient
  Serial.println("Connection Started, Lets start");
  //smoke
  /*String ADCSmoke,station1, SmokePostData;
  int adcSmoke=analogRead(A0); //Read Analog value of SMOKE
  Serial.print("SMOKE sensor Value is : ");
  Serial.print("   ");
  Serial.println(adcSmoke);
  ADCSmoke = String(adcSmoke);   //String to interger conversion
  station1 = "A";  */
  
  //ldr
  Serial.println("Connection Started, Lets start");
  String ADCLdr,station2,LdrPostData;
  int adcLdr=analogRead(A0);  //Read Analog value of LDR
  Serial.print("LDR sensor Value is : ");
  Serial.print("   ");
  Serial.println(adcLdr);
  ADCLdr = String(adcLdr);   //String to interger conversion
  station2 = "B"; //identify Ldr val in database  

  //Post Data
  //smoke
  /*SmokePostData = "status=" + ADCSmoke + "&station=" + station1 ; */
  
  //ldr
  LdrPostData = "status=" + ADCLdr + "&station=" + station2; 
  
  http.begin("http://192.168.1.101/Final/sensorpastdata.php");              //Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header
  
  //smoke
  /*int httpCode1 = http.POST(SmokePostData);   //Send the request
  String payload1 = http.getString();    //Get the response payload */
  //ldr
  int httpCode2 = http.POST(LdrPostData);   //Send the request
  String payload2 = http.getString();    //Get the response payload 
  
//  Serial.println(httpCode2);   //Print HTTP return code
//  Serial.println(payload2);    //Print request response payload
//  Serial.println(httpCode1);   //Print HTTP return code
//  Serial.println(payload1);    //Print request response payload
  
  
  http.end();  //Close connection
  Serial.println("Connection stopped, Lets start again");
  
  delay(5000);  //Post Data at every 5 seconds
}
