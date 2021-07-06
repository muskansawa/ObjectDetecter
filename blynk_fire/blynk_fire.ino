#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "ovRUOivWFXGlnenMw55q22Ft4mXPLNFQ";

#define FIREBASE_HOST "lights-out-ecee4.firebaseio.com" //--> URL address of your Firebase Realtime Database.
#define FIREBASE_AUTH "H40bVf80vIYu3xpE1zFUU3fpiiuyetgWDtKY6xlK" //--> Your firebase database secret code.

#define ON_Board_LED 2  //--> Defining an On Board LED, used for indicators when the process of connecting to a wifi router

#define LED_D8 15 //--> Defines an LED Pin. D8 = GPIO15

const int IrPin = 5; //pin D1 = GPIO5

//----------------------------------------SSID and Password of your WiFi router.
const char* ssid = "Redmi Note 9 Pro Max"; //--> Your wifi name or SSID.
const char* password = "be3kfje9gnt9e20"; //--> Your wifi password.
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

  pinMode(IrPin, INPUT);

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
  Blynk.begin(auth, ssid, password);
}

void loop() {
  // put your main code here, to run repeatedly:

  //----------------------------------------Get data from the Firebase Realtime Database.
  
   String getData = Firebase.getString("LEDStat");
    //Firebase.setString("LEDStat", "Off");              
  // Conditions for handling errors.
  if (Firebase.failed()) {
      Serial.print("Getting /Stat failed :");
      Serial.println(Firebase.error()); 
      delay(500); 
      return;
  }

  //-------------------------------------------to check value from sensor and send to firebase:

  int val = digitalRead(IrPin); // read input value 
  
   if (val == HIGH)// if the input is HIGH
   { 
      //note my sensor returns 1 when no object detected
      Serial.println("");
      Serial.print(val);
   } 
   else //object detected
   { 
     Serial.println("");
      Serial.print(val);
      String toggle ;
      if(getData == "on")
      {toggle = "off";}
      if(getData == "off")
      {toggle = "on";}
      Firebase.setString("LEDStat",toggle);  

       if (Firebase.failed()) {
      Serial.print("Getting /Stat failed :");
      Serial.println(Firebase.error()); 
      delay(500);   
      return;
      }
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
   Blynk.run();
  
  delay(3000);
}
