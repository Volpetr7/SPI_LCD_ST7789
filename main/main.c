#include "main.h"

//------------------------------------------------
//static const char *TAG = "ST7789";
//------------------------------------------------
TFT_t dev;
//------------------------------------------------
#define DISP_HOR_RES    240         /*Set the horizontal resolution in pixels*/
#define DISP_VER_RES    240         /*Set the vertical resolution in pixels*/

/*A variable to hold the drivers. Must be static or global.*/
static lv_disp_drv_t disp_drv;

/*A static or global variable to store the buffers*/
static lv_disp_draw_buf_t disp_buf;

/*Static or global buffer(s). The second buffer is optional*/
static lv_color_t buf_1[DISP_HOR_RES * 10];
//static lv_color_t buf_2[DISP_HOR_RES * 10];

static void my_disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p) {

    if (area->x2 < 0 || area->y2 < 0 || area->x1 > 240 || area->y1 > 240) {
        lv_disp_flush_ready(disp_drv);
        return;
    }

    int16_t w = lv_area_get_width(area);
    int16_t h = lv_area_get_height(area);

    int16_t x1 = area->x1;
    int16_t y1 = area->y1;

    // Створюємо масив кольорів для виведення на екран
    uint16_t *colors = (uint16_t *)malloc(sizeof(uint16_t) * w);


    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            colors[x] = color_p[x].full;
        }
        lcdDrawMultiPixels(&dev, x1, y1 + y, w, colors);
        color_p += w;
    }

    free(colors);
    lv_disp_flush_ready(disp_drv);
}

static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p){

    if(area->x2 < 0)return;
    if(area->y2 < 0)return;
    if(area->x1 > 240)return;
    if(area->y1 > 240)return;


    int indx=0;
    for(int y=area->y1; y<=area->y2; y++){
        for(int x=area->x1; x<=area->x2; x++){
            lcdDrawPixel(&dev,x, y, color_p->full);
            color_p++;
            indx++;
        }
    }

     lv_disp_flush_ready(disp_drv);
}


static void lv_drv_init(void){

    /*Initialize `disp_buf` with the buffer(s). With only one buffer use NULL instead buf_2 */
    lv_disp_draw_buf_init(&disp_buf, buf_1, NULL, DISP_HOR_RES*10);

    lv_disp_drv_init(&disp_drv);            /*Basic initialization*/

    disp_drv.draw_buf = &disp_buf;          /*Set an initialized buffer*/
    disp_drv.flush_cb = my_disp_flush;      /*Set a flush callback to draw to the display*/
    disp_drv.hor_res = DISP_HOR_RES;        /*Set the horizontal resolution in pixels*/
    disp_drv.ver_res = DISP_VER_RES;         /*Set the vertical resolution in pixels*/

    lv_disp_drv_register(&disp_drv); /*Register the driver and save the created display objects*/
}

//------------------------------------------------
/* USER CODE END Header_lv_timer */
void LVTIMER(void* arg)
{
  /* USER CODE BEGIN lv_timer */
  /* Infinite loop */
  for(;;)
  {
      lv_timer_handler();
      vTaskDelay(10 / portTICK_PERIOD_MS);
  }
  /* USER CODE END lv_timer */
}

/* USER CODE BEGIN Header_lv_tick */
/**
* @brief Function implementing the LVGL_Tick thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_lv_tick */
void LVTICK(void* arg)
{
  /* USER CODE BEGIN lv_tick */
  /* Infinite loop */
  for(;;)
  {
     lv_tick_inc(1);
     vTaskDelay(1 / portTICK_PERIOD_MS);
  }
  /* USER CODE END lv_tick */
}

/**
 * @brief Simple Button Screen containing two labels and two buttons
 * @param  None
 */
// Private Variables
static uint8_t button_counter = 0;
static lv_obj_t * count_label;

// Private Function Declarations



void lv_button_demo(void)
{
  lv_obj_t * label;

  lv_obj_t * btn1 = lv_btn_create(lv_scr_act());

  lv_obj_align(btn1, LV_ALIGN_CENTER, 0, -10);

  label = lv_label_create(btn1);
  lv_label_set_text(label, "Button");
  lv_obj_center(label);

  count_label = lv_label_create(lv_scr_act());
  lv_obj_align(count_label, LV_ALIGN_CENTER, 0, -60);
  lv_label_set_text(count_label, "CountS: 0");

  lv_obj_t * btn2 = lv_btn_create(lv_scr_act());
  lv_obj_align(btn2, LV_ALIGN_CENTER, 0, 40);
  lv_obj_add_flag(btn2, LV_OBJ_FLAG_CHECKABLE);
  lv_obj_set_height(btn2, LV_SIZE_CONTENT);

  label = lv_label_create(btn2);
  lv_label_set_text(label, "ToGgle");
  lv_obj_center(label);

  for(;;)
    {
        lv_timer_handler();
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}
//------------------------------------------------

void app_main(void)
{


   spi_master_init(&dev, CONFIG_PIN_NUM_MOSI, CONFIG_PIN_NUM_CLK, CONFIG_PIN_NUM_CS, CONFIG_PIN_NUM_DC, CONFIG_PIN_NUM_RESET, CONFIG_PIN_NUM_BLK);

   lv_init();
   lv_drv_init();
   lcdInit(&dev, CONFIG_WIDTH, CONFIG_HEIGHT, CONFIG_OFFSETX, CONFIG_OFFSETY);
   //lcdFillScreen(&dev, GREEN);

   xTaskCreate(lv_button_demo, "vLCDTask", 1024*8, NULL, 2, NULL);
   xTaskCreate(LVTICK, "LVTICK", 1024*8, NULL, 2, NULL);
   xTaskCreate(LVTIMER, "LVTIMER", 1024*8, NULL, 2, NULL);

   //ui_init();


   while (1) {
               vTaskDelay(10 / portTICK_PERIOD_MS);
             }
}
