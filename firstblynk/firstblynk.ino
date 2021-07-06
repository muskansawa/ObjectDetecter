#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "ovRUOivWFXGlnenMw55q22Ft4mXPLNFQ";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Redmi Note 9 Pro";
char pass[] = "lele1234";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);

}

void loop() {
  // put your main code here, to run repeatedly:
 Blynk.run();
}
