void initSerial() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("Serial Initialized.");
  
}

void initWifi() {
  WiFi.begin(ssid, pass);
  while(WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
  Serial.println("WiFi Initialized.");
}

void initDHT(){
  dht.begin();
  Serial.println("DHT Initialized.");
   
}

//void initTime(){
  
  
    
  //void unsigned long getTime() {
  //time_t now;
  //struct tm timeinfo;
 // if (!getLocalTime(&timeinfo)) {
   // Serial.println("Failed to obtain time");
   // return(0);
  //}
  //time(&now);
  //return now;
//}


  
  //configTime(7200, 0, "pool.ntp.org", "time.nist.gov");
   // while (true)
    //{
     //epochTime = time(NULL);

     //if (epochTime <= 28800){ 
         //delay(2000);
    // }
     //else {
        //Serial.printf("Fetched NTP epoch time is: %lu.\r\n", epochTime);
        //break;
     //}
    //}

  //}
  
//void initDHT(){
  //dht.begin();
  //Serial.println("DHT Initialized.");
   
//}
