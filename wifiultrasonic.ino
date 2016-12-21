#include <Debug.h>
#include <JSN270.h>
#include <Arduino.h>
#include <SoftwareSerial.h>

#define SSID      "AJOU1111"      // your wifi network SSID
#define KEY       "87654321"      // your wifi network password
#define AUTH       "WPA2"       // your wifi network security (NONE, WEP, WPA, WPA2)

#define USE_DHCP_IP 1

#if !USE_DHCP_IP
#define MY_IP          "192.168.1.133"
#define SUBNET         "255.255.255.0"
#define GATEWAY        "192.168.1.254"
#endif

#define HOST_IP        "52.79.54.169"
#define REMOTE_PORT    500
#define PROTOCOL       "TCP"
//#define at+send  = "1"
SoftwareSerial mySerial(3, 2); // RX, TX
 
JSN270 JSN270(&mySerial);

//////////////////////////////////////////////////////////////////////////////
const int trigPin = 9;
const int echoPin = 10;
int flag =0;
///////////////아두이노 핀 선언/////////////////


void setup() {
   char c;

   mySerial.begin(9600);
   Serial.begin(9600);

   Serial.println("--------- JSN270 TCP Client with WPA2 Test --------");

   // wait for initilization of JSN270
   delay(5000);
   //JSN270.reset();
   delay(1000);

   //JSN270.prompt();
   JSN270.sendCommand("at+ver\r");
   delay(5);
   while(JSN270.receive((uint8_t *)&c, 1, 1000) > 0) {
      Serial.print((char)c);
   }
   delay(1000);

#if USE_DHCP_IP
   JSN270.dynamicIP();
#else
   JSN270.staticIP(MY_IP, SUBNET, GATEWAY);
#endif    
    
   if (JSN270.join(SSID, KEY, AUTH)) {
      Serial.println("WiFi connect to " SSID);
   }
   else {
      Serial.println("Failed WiFi connect to " SSID);
      Serial.println("Restart System");

      return;
   }
   delay(1000);

   JSN270.sendCommand("at+wstat\r");
   delay(5);
   while(JSN270.receive((uint8_t *)&c, 1, 1000) > 0) {
      Serial.print((char)c);
   }
   delay(1000);        

   JSN270.sendCommand("at+nstat\r");
   delay(5);
   while(JSN270.receive((uint8_t *)&c, 1, 1000) > 0) {
      Serial.print((char)c);
   }
   delay(1000);

   if (!JSN270.client(HOST_IP, REMOTE_PORT, PROTOCOL)) {
      Serial.println("Failed connect to " HOST_IP);
      Serial.println("Restart System");
   } else {
      Serial.println("Socket connect to " HOST_IP);
      delay(2000);
      
      // Enter data mode
      JSN270.sendCommand("at+exit\r");
      delay(5);
   }
}

void loop() {
// establish variables for duration of the ping, 
  // and the distance result in inches and centimeters:
  long duration, inches, cm;
  
  

  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);
  delay(400);
//////////////////////초음파 센서 //////////////////////////
  
   if(JSN270.available()) {

  if(cm <= 13 && flag ==0)
     {
        JSN270.sendCommand("1");
        flag=1;
         if(Serial.available()) {
    
      JSN270.print((char)Serial.read());
   
   }
        }

      else if(cm >13 && flag ==1)
      {
        JSN270.sendCommand("2");
      flag = 0;
      
       if(Serial.available()) {
    
      JSN270.print((char)Serial.read());
   
   }
      }
   
}

long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
