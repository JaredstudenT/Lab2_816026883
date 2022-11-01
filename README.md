#  Lab2

This lab is focused on schedulnig with priority in mind and evaluating  performance.

The following lists the answers for questions P1 and P2 in the lab

---

## P1 Answers

### /project/sdkconfig
This file contains hardware and micro controller specific definitions and configurations . This file specifies the baud rate and flashing frequency when writing to the board as well as other settings for flashing. 

### /project/build/include/sdkconfig.h

This file contains hardware specific defintions . Changing one of these definitions will 

### /sdk/components/freertos/port/esp8266/include/freertos/FreeRTOSConfig.h

This file contains SDK and hardware specific configuration. It specifies which functions from the SDK are available to be called within the code. If this file is changed to disable a function that is called within the code, there will be an error. On the other hand, if a function is disabled that is not called, there might be an increase in performance, memory utilization .

---
## P2 Answers

THe following provide debug info about the tasks.

#define INCLUDE_xTaskGetCurrentTaskHandle 1
#define INCLUDE_uxTaskGetStackHighWaterMark 1


#define configGENERATE_RUN_TIME_STATS           0
#define configUSE_TRACE_FACILITY                0
#define configUSE_STATS_FORMATTING_FUNCTIONS    0

#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()

#ifndef configENABLE_TASK_SNAPSHOT
#define configENABLE_TASK_SNAPSHOT          1
#endif