#include <ESP8266WiFi.h>
 
const char* ssid = "Test";
const char* password = "qwerty00000";
 
int ledPin = 13; // GPIO13
WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Verbindet sich mit folgendem WLAN: ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi verbunden!");
 
  // Start the server
  server.begin();
  Serial.println("Server startet");
 
  // Print the IP address
  Serial.print("Benutze diese URL in deinem Browser: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
  return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
  int value = LOW;
  if (request.indexOf("/LED=ON") != -1)  {
    digitalWrite(ledPin, HIGH);
    value = HIGH;
  }
  if (request.indexOf("/LED=OFF") != -1)  {
    digitalWrite(ledPin, LOW);
    value = LOW;
  }
 
// Set ledPin according to the request
//digitalWrite(ledPin, value);
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("Led pin ist gerade: ");
 
  if(value == HIGH) {
    client.print("An");
  } else {
    client.print("Aus");
  }


// Tasten im Browser klein
  client.println("<br><br>");
  client.println("<a href=\"/LED=ON\"\"><button>An </button></a>");
  client.println("<a href=\"/LED=OFF\"\"><button>Aus </button></a><br />");  
  client.println("</html>");

  
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}
 
