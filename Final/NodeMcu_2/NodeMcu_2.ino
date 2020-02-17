
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

#define S3 D0
#define S2 D1
#define S1 D2
#define S0 D3
#define analogpin A0
#define SmokeLed D7
#define LdrLed D8
#define buzzer D4
/* Set these to your desired credentials. */
const char *ssid = "hotspot";  //ENTER YOUR WIFI SETTINGS
const char *password = "@hello123@";

//Web/Server address to read/write from 
const char *host = "192.168.1.102";   //https://circuits4you.com website or IP address of server

//=======================================================================
//                    Power on setup
//=======================================================================

void setup() {
  pinMode(analogpin, INPUT);
  pinMode(S0,OUTPUT);
  pinMode(S1,OUTPUT);
  pinMode(S2,OUTPUT);
  pinMode(S3,OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(SmokeLed, OUTPUT); 
  pinMode(LdrLed, OUTPUT);  
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
  //Serial.println("Connection Started, Lets start");
  //smoke
  digitalWrite(S0,LOW);
  digitalWrite(S1,LOW);
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  digitalWrite(buzzer, LOW);
  digitalWrite(SmokeLed, LOW);
  digitalWrite(LdrLed, LOW);
  String ADCSmoke,station1, SmokePostData;
  int adcSmoke=analogRead(analogpin); //Read Analog value of SMOKE
  
  Serial.print("SMOKE sensor Value is : ");
  Serial.print("   ");
  Serial.println(adcSmoke);
  if(adcSmoke>150)
  {
    digitalWrite(SmokeLed, HIGH);
    Serial.print("Smoke is High");
    //tone(buzzer, 3072, 50);
    beep(500);
    //digitalWrite(buzzer, HIGH);
  }
  else
  {
    digitalWrite(SmokeLed, LOW);
    Serial.print("Smoke is Low");
    digitalWrite(buzzer, LOW);
  }
  Serial.println();
  Serial.println();
  ADCSmoke = String(adcSmoke);   //String to interger conversion
  station1 = "A";
  
  //ldr
  //Serial.println("Connection Started, Lets start");
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  String ADCLdr,station2,LdrPostData;
  int adcLdr=analogRead(analogpin);  //Read Analog value of LDR
  Serial.print("LDR sensor Value is : ");
  Serial.print("   ");
  Serial.println(adcLdr);
  Serial.println();
  Serial.println();
  if(adcLdr<500)
  {
    digitalWrite(LdrLed, HIGH);
    Serial.print("Ldr light on");
  }
  else
  {
    digitalWrite(LdrLed, LOW);
    Serial.print("Ldr light off");
  }
  ADCLdr = String(adcLdr);   //String to interger conversion
  station2 = "B"; //identify Ldr val in database 

  //Post Data
  //smoke
  SmokePostData = "status=" + ADCSmoke + "&station=" + station1 ;
  
  //ldr
  LdrPostData = "status=" + ADCLdr + "&station=" + station2; 
  
  http.begin("http://192.168.1.102/Final/sensorpastdata.php");              //Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header
  
  //smoke
  int httpCode1 = http.POST(SmokePostData);   //Send the request
  String payload1 = http.getString();    //Get the response payload
  //ldr
  int httpCode2 = http.POST(LdrPostData);   //Send the request
  String payload2 = http.getString();    //Get the response payload 
  
//  Serial.println(httpCode2);   //Print HTTP return code
//  Serial.println(payload2);    //Print request response payload
//  Serial.println(httpCode1);   //Print HTTP return code
//  Serial.println(payload1);    //Print request response payload
  
  
  http.end();  //Close connection
  //Serial.println("Connection stopped, Lets start again");
  
  delay(5000);  //Post Data at every 5 seconds
}
void beep(unsigned char delayms) { //creating function
  analogWrite(buzzer, 500); //Setting pin to high
  delay(delayms); //Delaying
  analogWrite(buzzer ,0); //Setting pin to LOW
  delay(delayms); //Delaying
  }
