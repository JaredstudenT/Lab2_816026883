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

#include "time.h"

static const char *TAG = "main";
 
#define GPIO_OUTPUT_IO_0    0
//THe ON-board LED is not used, instead an additional LED 
#define GPIO_OUTPUT_PIN_SEL  (1ULL<<GPIO_OUTPUT_IO_0) 

#define PRIORITY_MAXIMUM 3
#define PRIORITY_MEDIUM 3
#define PRIORITY_MINIMUM 3
//The priorities are all set to the same

static void priority_example_task_one();

static void priority_example_task_two();

static void priority_example_task_three();

SemaphoreHandle_t xMutex;

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

    xMutex = xSemaphoreCreateMutex();
    
    if( xMutex != NULL )
    {
        xTaskCreate(priority_example_task_one, "priority_example_task_one", 2048, NULL, PRIORITY_MAXIMUM, NULL);
        xTaskCreate(priority_example_task_two, "priority_example_task_two", 2048, NULL, PRIORITY_MEDIUM, NULL);
        xTaskCreate(priority_example_task_three, "priority_example_task_three", 2048, NULL, PRIORITY_MINIMUM, NULL);
     }

    //vTaskStartScheduler();
}

//////////////////////////////////////////////////////////////////////////////////////////

static void active_delay()
{
    for(int i=0;i<7000000;i++)
    {
        if(i%1000000==0)
        {
            printf(".");
        }
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////

static void priority_example_task_one()
{
    while(1)
    {
        while(1)
        {
            if( xSemaphoreTake( xMutex, ( TickType_t ) 10 ) == pdTRUE )
            {
                printf("LED Turn ON \n");
                gpio_set_level(GPIO_OUTPUT_IO_0, 1);
                xSemaphoreGive( xMutex );
                break;
            }
        }

        active_delay();
        vTaskDelay(1000 / portTICK_RATE_MS);

    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////
static void priority_example_task_two()
{
    while(1)
    {
        while(1)
        {
            if( xSemaphoreTake( xMutex, ( TickType_t ) 10 ) == pdTRUE )
            {
                printf("LED Turn OFF \n");
                gpio_set_level(GPIO_OUTPUT_IO_0, 0);
                xSemaphoreGive( xMutex );
                break;
            }
        }

        active_delay();
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}

static void priority_example_task_three()
{
    while(1)
    {
        ESP_LOGI(TAG, "Status Message");
        printf("\n");
        
        vTaskDelay(1000 / portTICK_RATE_MS);
        
    }
}

