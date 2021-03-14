void initIotHub() {

  // Om Esp32 inte är connected så ska det bli false och returnera tillbaka, annars är det true.
  
  if (!Esp32MQTTClient_Init((const uint8_t *) connectionString)) {
    _connected = false;
    return; // returnerar om värdet är false
    
   }
   
  _connected = true; // värdet är true när det är kopplat
 }
