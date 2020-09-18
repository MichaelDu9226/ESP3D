#include "main_ui.h"
#include "sdcard_ui.h"
#include "basic_ui.h"
#include "../../core/debug_esp3d.h"
//#include "../../include/esp3d_config.h"

lv_obj_t *main_screen;
static lv_obj_t *screen;

void basic_button_event_cb(lv_obj_t *btn, lv_event_t event)
{
    if (event == LV_EVENT_CLICKED)
    {
        log_esp3d("basic_button Clicked");
        if (screen != nullptr)
        {
            lv_obj_del(screen);
        }
        show_basic_ui(main_screen);
    }
}

void sdcard_button_event_cb(lv_obj_t *btn, lv_event_t event)
{
    if (event == LV_EVENT_CLICKED)
    {
        log_esp3d("sdcard_button Clicked");
        if (screen != nullptr)
        {
            lv_obj_del(screen);
        }
        show_sdcard_ui(main_screen);
    }
}

void draw_button_event_cb(lv_obj_t *btn, lv_event_t event)
{
    if (event == LV_EVENT_CLICKED)
    {
        //log_esp3d("draw_button Clicked");
    }
}

static void emergency_button_event_cb(lv_obj_t *btn, lv_event_t event)
{
    if (event == LV_EVENT_CLICKED)
    {
        //log_esp3d("emergency_button Clicked");
    }
}

static void main_button_event_cb(lv_obj_t *btn, lv_event_t event)
{
    if (event == LV_EVENT_CLICKED)
    {
        //log_esp3d("main_button Clicked");
    }
}

static void return_button_event_cb(lv_obj_t *btn, lv_event_t event)
{
    if (event == LV_EVENT_CLICKED)
    {
        //log_esp3d("return_button Clicked");
    }
}

void show_main_ui(lv_obj_t *esp_lv_screen)
{
    //main window
    screen = lv_obj_create(esp_lv_screen, NULL);
    main_screen = esp_lv_screen;
    lv_obj_set_pos(screen, 0, 30);
    lv_obj_set_size(screen, 320, 480 - (1 * 30));
    lv_obj_set_style(screen, &lv_style_scr);

    //main_screen = screen;
    lv_obj_t *basic_button = lv_btn_create(screen, NULL);
    lv_obj_set_pos(basic_button, 20, 40);
    lv_obj_set_size(basic_button, 80, 80);
    //lv_obj_t * basic_image = lv_img_create(btn, NULL);
    //lv_img_set_src(basic_image, &basic_image);
    //lv_obj_align (basic_image, btn, LV_ALIGN_IN_TOP_MID, 0, 0);
    lv_obj_set_event_cb(basic_button, basic_button_event_cb);
    lv_obj_t *basic_button_label = lv_label_create(basic_button, NULL);
    lv_label_set_text(basic_button_label, "Basic");

    lv_obj_t *sdcard_button = lv_btn_create(screen, NULL);
    lv_obj_set_pos(sdcard_button, 120, 40);
    lv_obj_set_size(sdcard_button, 80, 80);
    lv_obj_set_event_cb(sdcard_button, sdcard_button_event_cb);
    lv_obj_t *sdcard_button_label = lv_label_create(sdcard_button, NULL);
    lv_label_set_text(sdcard_button_label, "SDCard");
/*
    lv_obj_t *draw_button = lv_btn_create(screen, NULL);
    lv_obj_set_pos(draw_button, 220, 40);
    lv_obj_set_size(draw_button, 80, 80);
    lv_obj_set_event_cb(draw_button, draw_button_event_cb);
    lv_obj_t *draw_button_label = lv_label_create(draw_button, NULL);
    lv_label_set_text(draw_button_label, "draw");
*/
    lv_obj_t * line = lv_line_create(screen, NULL);
    static const lv_point_t line_p[] = {{0, 375}, {320, 375}};
    lv_line_set_points(line, line_p, 2);

    lv_obj_t *emergency_button = lv_btn_create(screen, NULL);
    lv_obj_set_pos(emergency_button, 20, 380);
    lv_obj_set_size(emergency_button, 80, 60);
    lv_obj_set_event_cb(emergency_button, emergency_button_event_cb);
    lv_obj_t *emergency_button_label = lv_label_create(emergency_button, NULL);
    lv_label_set_text(emergency_button_label, "E Stop");

    lv_obj_t *main_button = lv_btn_create(screen, NULL);
    lv_obj_set_pos(main_button, 120, 380);
    lv_obj_set_size(main_button, 80, 60);
    lv_obj_set_event_cb(main_button, main_button_event_cb);
    lv_obj_t *main_button_label = lv_label_create(main_button, NULL);
    lv_label_set_text(main_button_label, "Main");

    lv_obj_t *return_button = lv_btn_create(screen, NULL);
    lv_obj_set_pos(return_button, 220, 380);
    lv_obj_set_size(return_button, 80, 60);
    lv_obj_set_event_cb(return_button, return_button_event_cb);
    lv_obj_t *return_button_label = lv_label_create(return_button, NULL);
    lv_label_set_text(return_button_label, "Return");
}