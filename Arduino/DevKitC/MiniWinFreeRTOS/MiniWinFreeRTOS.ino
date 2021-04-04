#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "src/miniwin.h"

/* queue handles */
QueueHandle_t gyro_x_queue;
QueueHandle_t gyro_y_queue;
QueueHandle_t gyro_z_queue;

/* thread tasks */
static TaskHandle_t main_task_handle;
static TaskHandle_t miniwin_task_handle;
static TaskHandle_t gyro_task_handle;

/* thread synchronization */
static SemaphoreHandle_t semaphore_handle;

/**
 * Thread function of main thread
 *
 * @param parameters Thread parameters, if any
 */
static void main_thread(void *parameters);

/**
 * Thread function to run window manager
 *
 * @param parameters Thread parameters, if any
 */
static void miniwin_thread(void *parameters);

/**
 * Thread function to run gyro sensor
 *
 * @param parameters Thread parameters, if any
 */
static void gyro_thread(void *parameters);

/**
 * Function to simulate reading a gyro
 *
 * @return pointer to array of 3 floats
 */
static float *app_get_gyro_readings(void);

static float *app_get_gyro_readings(void)
{
  static float gyro_angles[3] = {0.0f, 0.0f, 0.0f};
  
  gyro_angles[0] += 0.3f;
  gyro_angles[1] += 0.5f;
  gyro_angles[2] += 0.7f;
  
  return gyro_angles;
}

static void main_thread(void *parameters)
{
  Serial.begin(115200);
  static bool toggle;
  
  while (true)
  {
    vTaskDelay(100U);

    toggle = ! toggle;

    if (toggle)
    {
      Serial.print("On\n");
    }
    else
    {
      Serial.print("Off\n");
    }
  }
}

static void gyro_thread(void *parameters)
{
  static uint8_t reading_counter = 0U;
  TickType_t xLastWakeTime;
  float *gyro_readings;

  /* wait until window manager is started */
  while (!mw_is_init_complete())
  {
    vTaskDelay(100);
  }

  xLastWakeTime = xTaskGetTickCount();
  while (true)
  {
    if (xSemaphoreTake(semaphore_handle, (TickType_t)10) == 0)
    {
      continue;
    }
    gyro_readings = app_get_gyro_readings();

    /* the next line cannot be made MISRA compliant because of the FreeRTOS API */
    (void)xSemaphoreGive(semaphore_handle);

    /* only send 1 in every 10 readings to window */
    reading_counter++;
    if (reading_counter == 10U)
    {
      reading_counter = 0U;

      (void)xQueueSend(gyro_x_queue, ((const void *)(&gyro_readings[0])), (TickType_t)0);
      (void)xQueueSend(gyro_y_queue, ((const void *)(&gyro_readings[1])), (TickType_t)0);
      (void)xQueueSend(gyro_z_queue, ((const void *)(&gyro_readings[2])), (TickType_t)0);      
    }

    /* pause thread until next reading */
    vTaskDelayUntil(&xLastWakeTime, 100U);
  }
}

static void miniwin_thread(void *parameters)
{
  /* initialize miniwin */
  mw_init();

  while (true)
  {
      /* do miniwin message processing */
    if (xSemaphoreTake(semaphore_handle, (TickType_t)10) == 0)
    {
      vTaskDelay(10U);
      continue;
    }

    (void)mw_process_message();

    (void)xSemaphoreGive(semaphore_handle);
    vTaskDelay(10U);
  }
}

void setup() 
{
  /* initialise the queues to send gyro reading data from gyro thread to gyro windows */
  gyro_x_queue = xQueueCreate((UBaseType_t)1,(UBaseType_t)sizeof(float));
  gyro_y_queue = xQueueCreate((UBaseType_t)1,(UBaseType_t)sizeof(float));
  gyro_z_queue = xQueueCreate((UBaseType_t)1,(UBaseType_t)sizeof(float));

  /* initialize the mutex */
  semaphore_handle = xSemaphoreCreateMutex();

  /* create the led task */
  (void)xTaskCreate(main_thread, "MAIN", 1024U, NULL, 1, &main_task_handle);

  /* create the gyro task */
  (void)xTaskCreate(gyro_thread, "GYRO", 1024U, NULL, 2, &gyro_task_handle);

  /* create the miniwin task */
  (void)xTaskCreate(miniwin_thread, "MINIWIN", 2048U, NULL, 1, &miniwin_task_handle);
}

void loop() 
{ 
  /* nothing to do here, all done in threads */
}
