TaskHandle_t Task_A;
TaskHandle_t Task_B;

void TaskA(void *pvParameters){

   Serial.print("I am Task A and Im running on CORE_");
   Serial.println(xPortGetCoreID());
   vTaskDelay(pdMS_TO_TICKS(1000));
   vTaskDelete(Task_A);

}
void TaskB(void *pvParameters){
  
   Serial.print("I am Task B and Im running on CORE_");
   Serial.println(xPortGetCoreID());
   vTaskDelay(pdMS_TO_TICKS(1000));
   vTaskDelete(Task_B);

}
void setup(){
  Serial.begin(115200);

  xTaskCreatePinnedToCore(TaskA,    //Function pointer
                          "Task A", //Name of the function
                           10000,   //Stack size allocated
                           NULL,    //Pointer to the paramters
                           1,       //Priority
                           &Task_A, //Task handle
                           0);      //Core number
                           
  xTaskCreatePinnedToCore(TaskB,    //Function pointer
                          "Task B", //Name of the function
                           10000,   //Stack size allocated
                           NULL,    //Pointer to the paramters
                           1,       //Priority
                           &Task_B, //Task handle
                           1);      //Core number
  
}
void loop(){};
