#  Lab2

This lab is focused on scheduling with priority of tasks in mind and evaluating performance with the mutexes/semaphores.

This repository uses branches to answer each question. The main branch may be ignored and only the branches "question1" , "question2" and "question3" may be considered for the corresponding question in the lab. All versions of the README contain the answer to P1 and P2.

---
##Question 2 answer

When the priority of the tasks were changed , the resource controlled by the MUtex behaved differently and certain tasks were executed with higher prefernce than others. This was seen especially when the task to turn the LED on was given highest priority and the LED remained ON most of the time. On the other hand, when the task that turns the LED off is given highest priority , the LED remains off for the majority of the time .
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


#define configGENERATE_RUN_TIME_STATS           1
#define configUSE_TRACE_FACILITY                1
#define configUSE_STATS_FORMATTING_FUNCTIONS    1

#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()

#ifndef configENABLE_TASK_SNAPSHOT
#define configENABLE_TASK_SNAPSHOT          1
#endif

