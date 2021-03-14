#include <WiFi.h>  

// Deklarerar upp och startar WiFi Uppkopplingen 
void initWiFi(char* ssid, char* pass) {
  // startup kommando
  WiFi.begin(ssid, pass);

  // While sats som anger att när WiFi status inte är kopplat så är det en fördröjning på 0,5 sek plus en utsrkift.
  while (WiFi.status() !=WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    
  }
  // Skriver ut IP adressen till konsollen
  Serial.println("");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
}
