#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>

#define FIREBASE_HOST "lights-out-ecee4.firebaseio.com" //--> URL address of your Firebase Realtime Database.
#define FIREBASE_AUTH "H40bVf80vIYu3xpE1zFUU3fpiiuyetgWDtKY6xlK" //--> Your firebase database secret code.

#define ON_Board_LED 2  //--> Defining an On Board LED, used for indicators when the process of connecting to a wifi router

#define LED_D8 15 //--> Defines an LED Pin. D8 = GPIO15

//----------------------------------------SSID and Password of your WiFi router.
const char* ssid = "Redmi Note 9 Pro"; //--> Your wifi name or SSID.
const char* password = "lele1234"; //--> Your wifi password.
//----------------------------------------

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(500);
  
  WiFi.begin(ssid, password); //--> Connect to your WiFi router
  Serial.println("");
    
  pinMode(ON_Board_LED,OUTPUT); //--> On Board LED port Direction output
  digitalWrite(ON_Board_LED, HIGH); //--> Turn off Led On Board

  pinMode(LED_D8,OUTPUT); //--> LED port Direction output
  digitalWrite(LED_D8, LOW); //--> Turn off Led

  //----------------------------------------Wait for connection
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    //----------------------------------------Make the On Board Flashing LED on the process of connecting to the wifi router.
    digitalWrite(ON_Board_LED, LOW);
    delay(250);
    digitalWrite(ON_Board_LED, HIGH);
    delay(250);
    //----------------------------------------
  }
  //----------------------------------------
  digitalWrite(ON_Board_LED, HIGH); //--> Turn off the On Board LED when it is connected to the wifi router.
  //----------------------------------------If successfully connected to the wifi router, the IP Address that will be visited is displayed in the serial monitor
  Serial.println("");
  Serial.print("Successfully connected to : ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  //----------------------------------------

  //----------------------------------------Firebase Realtime Database Configuration.
  Firebase.begin("lights-out-ecee4.firebaseio.com", "H40bVf80vIYu3xpE1zFUU3fpiiuyetgWDtKY6xlK");
  //----------------------------------------
}

void loop() {
  // put your main code here, to run repeatedly:

  //----------------------------------------Get data from the Firebase Realtime Database.
  String getData = Firebase.getString("LEDStat");
    //Firebase.setString("LEDStat", "OFF");              
  // Conditions for handling errors.
  if (Firebase.failed()) {
      Serial.print("Getting /Stat failed :");
      Serial.println(Firebase.error()); 
      delay(500); 
      return;
  }
  //----------------------------------------

  //----------------------------------------Conditions for turning off or turning on the LED.
    
  if (getData == "on") {
    digitalWrite(LED_D8, HIGH);
    Serial.println("LED On");
    Serial.println();
  }

  if (getData == "off") {
    digitalWrite(LED_D8, LOW);
    Serial.println("LED off");
    Serial.println();
  }
  //----------------------------------------
  
  delay(3000);
}
