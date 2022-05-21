
TaskHandle_t Task1;
TaskHandle_t Task2;

static int delay_ms = 0;
void TaskTwo(void * pvParamters){ 
  while(1){
      
      Serial.println("task 2 is running");
      digitalWrite(LED_BUILTIN , HIGH);
      vTaskDelay(pdMS_TO_TICKS(delay_ms));
      digitalWrite(LED_BUILTIN , LOW);
      vTaskDelay(pdMS_TO_TICKS(delay_ms));
  }
}
void TaskOne(void * pvParameters){  

    
    Serial.println("task 1 is running\n");  
    Serial.print("Enter the value of delay in ms: ");  
    while (!Serial.available()); 
    delay_ms = Serial.parseInt(); 
    Serial.println(delay_ms); 
        
    xTaskCreate(TaskTwo , "LED_BUILTIN blink with given delay" , 1024 , NULL , 1 , &Task2);
    vTaskDelete(Task1);

}

void setup() {
 
  Serial.begin(115200);
  pinMode(LED_BUILTIN , OUTPUT); 
 
  xTaskCreate(TaskOne , "Getting user input for delay" , 1024 , NULL , 2 , &Task1);
  
  
}

void loop() {
 
}
