#include <WiFi.h>        // Include the Wi-Fi library

const char* ssid = "EN20405236";   // The name of the Wi-Fi network 
const char* password = "ranasinghe" ; // The password of the Wi-Fi network
TaskHandle_t Task_A;
TaskHandle_t Task_B;
WiFiServer server(80);

void TaskA(void* pvParameters){
  Serial.print("Task A running on CORE_\n");
  Serial.print(xPortGetCoreID());
  
  WiFi.begin(ssid, password);             // Connect to the network 
  while (WiFi.status() != WL_CONNECTED);// Wait for the Wi-Fi to connect  
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());  
 
  xTaskCreatePinnedToCore(TaskB,
                          "Control 2 LEDS",
                          10000,
                          NULL,
                          1,
                          &Task_B,
                          1);
  vTaskDelete(Task_A); //deleting task
  
}

void TaskB(void * pvParameters){
  server.begin();  
  while(1) {    
    WiFiClient client = server.available();       
    if (client) {                             
      Serial.println("New Client.");          
      String currentLine = "";            
      
      while (client.connected()) {         
        if (client.available()) {           
          char c = client.read();             
          Serial.write(c); 
                            
          if (c == '\n') {                    
            if (currentLine.length() == 0) {
              client.println("HTTP/1.1 200 OK");
              client.println("Content-type:text/html");
              client.println();
              
              client.print("Click <a href=\"/H\">here</a> to turn the in built LED ON.<br>");
              client.print("Click <a href=\"/L\">here</a> to turn the in built LED OFF.<br>");           
              client.println();
              break;
            
            } else {   
              currentLine = "";
            }
          
          } else if (c != '\r') {  
            currentLine += c;      
          }
  
          if (currentLine.endsWith("GET /H")) {
            digitalWrite(LED_BUILTIN, HIGH);                
          }
          
          if (currentLine.endsWith("GET /L")) {
            digitalWrite(LED_BUILTIN, LOW);               
          }         
        }
      }      
      client.stop();
      Serial.println("Client Disconnected.");
    }
  }
  
}

void setup() {
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(10);
  pinMode(BUILTIN_LED , OUTPUT);
  xTaskCreatePinnedToCore(TaskA,
                          "Connect to the Network",
                          10000,
                          NULL,
                          1,
                          &Task_A,
                          0);                
}
void loop() {
  // put your main code here, to run repeatedly:

}
