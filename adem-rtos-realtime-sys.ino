/* 
  file: adem-rtos-realtime-sys.ino
  author: nikobk
  created on: november 2, 2023
*/

// Use only core 1 for demo purposes
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

int delayMS = 1000;
bool verbose = false;

// Create a new task.
void runDemoTask(void *parameter) {
  // Our superloop.
  while(1) {
    // Use vTaskDelay instead of delay() as it is nonblocking and works on freeRTOS.
    // portTICK refers to one of the hardware ticktimers (clocks).
    vTaskDelay(delayMS / portTICK_PERIOD_MS);
    if (verbose) {
      Serial.println("<Task1>: Tick!");
    }
  }
}

// Try another task, consec. with Demo Task 1
void runDemoTaskTwo(void *parameter) {
  while(1) {
    vTaskDelay(delayMS / portTICK_PERIOD_MS);
    if (verbose) {
      Serial.println("<Task2>: Tick!");
    }
  }
}

void setup() {
  // I found this frequency to work on the ESP32 C3.
  Serial.begin(115200);

  // Make sure our task only runs on one of the cores.
  xTaskCreatePinnedToCore(
        runDemoTask,       // Function to be called for the task
        "Demo Task",       // Task Name
        1024,              // Stack size - 1kb (bytes in ESP32, words in vanilla freeRTOS)
        NULL,              // Parameter to pass to function
        1,                 // Task prioerity (0 to configMAX_PRIORITIES - 1)
        NULL,              // Task handle
        app_cpu);          // Run on one core for demo purposes (ESP32 only)

  xTaskCreatePinnedToCore(
        runDemoTaskTwo,
        "Demo Task Two",
        1024,
        NULL,
        1, // Ensure that both tasks run by sharing priority
        NULL,
        app_cpu);
}

void loop() {
  // put your main code here, to run repeatedly:
}