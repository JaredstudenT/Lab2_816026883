/* gpio example
   This example code is in the Public Domain (or CC0 licensed, at your option.)
   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "driver/gpio.h"

#include "esp_log.h"
#include "esp_system.h"
#include "semphr.h"

static const char *TAG = "main";
 

#define GPIO_OUTPUT_IO_0    0
#define GPIO_OUTPUT_PIN_SEL  (1ULL<<GPIO_OUTPUT_IO_0) 

#define GPIO_INPUT_IO_0     2
#define GPIO_INPUT_PIN_SEL  (1ULL<<GPIO_INPUT_IO_0) 

#define PRIORITY_MAXIMUM 7
#define PRIORITY_MEDIUM 3
#define PRIORITY_MINIMUM 1


static void priority_example_task_one()

static void priority_example_task_two();

static void priority_example_task_three();

//static xQueueHandle gpio_evt_queue = NULL;

//static void gpio_isr_handler(void *arg)
//{
//    uint32_t gpio_num = (uint32_t) arg;
//    xQueueSendFromISR(gpio_evt_queue, &gpio_num, NULL);
//    
//}

//static void gpio_task_example(void *arg)
//{
//    uint32_t io_num;
//
//    for (;;) {
//        if (xQueueReceive(gpio_evt_queue, &io_num, portMAX_DELAY)) {
//            ESP_LOGI(TAG, "GPIO[%d] intr, val: %d\n", io_num, gpio_get_level(io_num));
//        }
//   }
//}


xSemaphoreHandle xMutex;

void app_main(void)
{
    gpio_config_t io_conf;
    //disable interrupt
    //io_conf.intr_type = GPIO_INTR_DISABLE;
    //set as output mode
    io_conf.mode = GPIO_MODE_OUTPUT;
    //bit mask of the pins that you want to set,e.g.GPIO15/16
    io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
    //disable pull-down mode
    io_conf.pull_down_en = 0;
    //disable pull-up mode
    io_conf.pull_up_en = 0;
    //configure GPIO with the given settings
    gpio_config(&io_conf);

    //interrupt of rising edge
    //io_conf.intr_type = GPIO_INTR_NEGEDGE;
    //bit mask of the pins, use GPIO4/5 here
    //io_conf.pin_bit_mask = GPIO_INPUT_PIN_SEL;
    //set as input mode
    //io_conf.mode = GPIO_MODE_INPUT;
    //enable pull-up mode
    //io_conf.pull_up_en = 1;
    //gpio_config(&io_conf);

    //change gpio intrrupt type for one pin
    //gpio_set_intr_type(GPIO_INPUT_IO_0, GPIO_INTR_NEGEDGE);


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////CREATE mutex////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    xMutex = xSemaphoreCreateMutex();

    if( xMutex != NULL )
    {
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////CREATE mutex////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////CREATE TASK 1////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        xTaskCreate(priority_example_task_one, "priority_example_task_one", 2048, NULL, PRIORITY_MAXIMUM, NULL);
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////CREATE TASK 1////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////CREATE TASK 2////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        xTaskCreate(priority_example_task_two, "priority_example_task_two", 2048, NULL, PRIORITY_MEDIUM, NULL);
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////CREATE TASK 2////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////CREATE TASK 3////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        xTaskCreate(priority_example_task_three, "priority_example_task_three", 2048, NULL, PRIORITY_MINIMUM, NULL);
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////CREATE TASK 3////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        
    }


    //int cnt = 0;

    //while (1) {
    //    ESP_LOGI(TAG, "cnt: %d\n", cnt++);
    //    vTaskDelay(1000 / portTICK_RATE_MS);
    //    gpio_set_level(GPIO_OUTPUT_IO_0, cnt % 2);
    //    printf(" HELLO 816026883 \n");
    //    //added in an output comment to ensure the program is working
    //    //gpio_set_level(GPIO_OUTPUT_IO_1, cnt % 2);
    //}
}


static void priority_example_task_one()
{
    if( xMutex != NULL )
    {
        if( xSemaphoreTake( xMutex, ( TickType_t ) 10 ) == pdTRUE )
        {
            gpio_set_level(GPIO_OUTPUT_IO_0, 1);
            xSemaphoreGive( xMutex );
        }
    }

    printf("start active delay");
    for(int i=0;i<500;i++)
    {   
        i=i+1;
        i=i-1;
        if(i==250)
        {
            printf("Middle of active delay");
        }
    }
    printf("end active delay");


    vTaskDelay(1000);
}


//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
static void priority_example_task_two()
{
    if( xMutex != NULL )
    {
        if( xSemaphoreTake( xMutex, ( TickType_t ) 10 ) == pdTRUE )
        {
            gpio_set_level(GPIO_OUTPUT_IO_0, 0);
            xSemaphoreGive( xMutex );
        }
    }
    printf("start active delay");
    for(int i=0;i<500;i++)
    {   
        i=i+1;
        i=i-1;
        if(i==250)
        {
            printf("Middle of active delay");
        }
    }
    printf("end active delay");

    vTaskDelay(1000);
}

static void priority_example_task_three()
{
    //printf("Status message  ");
    ESP_LOGI(TAG, "Status message  ");
    vTaskDelay(1000);    
}

//SemaphoreHandle_t xMutex;

void createMutex( void * pvParameters )
{
   /* Create a mutex type semaphore. */
   xMutex = xSemaphoreCreateMutex();

   if( xMutex != NULL )
   {
       /* The semaphore was created successfully and
       can be used. */
   }
}