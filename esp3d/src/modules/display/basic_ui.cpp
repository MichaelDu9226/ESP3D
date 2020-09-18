#include "basic_ui.h"
#include "main_ui.h"
#include "../../core/debug_esp3d.h"
#include "../gcode_host/gcode_host.h"

static lv_obj_t *main_screen;
static lv_obj_t *screen;

static void emergency_button_event_cb(lv_obj_t *btn, lv_event_t event)
{
    if (event == LV_EVENT_CLICKED)
    {
        log_esp3d("emergency_button Clicked");
    }
}

static void main_button_event_cb(lv_obj_t *btn, lv_event_t event)
{
    if (event == LV_EVENT_CLICKED)
    {
        log_esp3d("main_button Clicked");
        if (screen != nullptr)
        {
            lv_obj_del(screen);
        }
        show_main_ui(main_screen);
    }
}

static void return_button_event_cb(lv_obj_t *btn, lv_event_t event)
{
    if (event == LV_EVENT_CLICKED)
    {
        log_esp3d("return_button Clicked");
        if (screen != nullptr)
        {
            lv_obj_del(screen);
        }
        show_main_ui(main_screen);
    }
}

static void return_button_event_cb1(lv_obj_t *btn, lv_event_t event)
{
    if (event == LV_EVENT_CLICKED)
    {
        log_esp3d("return_button1 Clicked");
        if (screen != nullptr)
        {
            lv_obj_del(screen);
        }
        show_main_ui(main_screen);
    }
}

static void z_plus_button_event_cb(lv_obj_t *btn, lv_event_t event)
{
    if (event == LV_EVENT_CLICKED)
    {
        log_esp3d("z_plus_button Clicked");
        esp3d_gcode_host.sendCommand("G91\n");
        esp3d_gcode_host.sendCommand("G0 F1500 Z5\n");
        esp3d_gcode_host.sendCommand("G90\n");
    }
}

static void z_minus_button_event_cb(lv_obj_t *btn, lv_event_t event)
{
    if (event == LV_EVENT_CLICKED)
    {
        log_esp3d("z_minus_button Clicked");
        esp3d_gcode_host.sendCommand("G91\n");
        esp3d_gcode_host.sendCommand("G0 F1500 Z-5\n");
        esp3d_gcode_host.sendCommand("G90\n");
    }
}

static void y_plus_button_event_cb(lv_obj_t *btn, lv_event_t event)
{
    if (event == LV_EVENT_CLICKED)
    {
        log_esp3d("y_plus_button Clicked");
        esp3d_gcode_host.sendCommand("G91\n");
        esp3d_gcode_host.sendCommand("G0 F1500 Y5\n");
        esp3d_gcode_host.sendCommand("G90\n");
    }
}

static void y_minus_button_event_cb(lv_obj_t *btn, lv_event_t event)
{
    if (event == LV_EVENT_CLICKED)
    {
        log_esp3d("y_minus_button Clicked");
        esp3d_gcode_host.sendCommand("G91\n");
        esp3d_gcode_host.sendCommand("G0 F1500 Y-5\n");
        esp3d_gcode_host.sendCommand("G90\n");
    }
}

static void x_plus_button_event_cb(lv_obj_t *btn, lv_event_t event)
{
    if (event == LV_EVENT_CLICKED)
    {
        log_esp3d("x_plus_button Clicked");
        esp3d_gcode_host.sendCommand("G91\n");
        esp3d_gcode_host.sendCommand("G0 F1500 X5\n");
        esp3d_gcode_host.sendCommand("G90\n");
    }
}

static void x_minus_button_event_cb(lv_obj_t *btn, lv_event_t event)
{
    if (event == LV_EVENT_CLICKED)
    {
        log_esp3d("x_minus_button Clicked");
        esp3d_gcode_host.sendCommand("G91\n");
        esp3d_gcode_host.sendCommand("G0 F1500 X-5\n");
        esp3d_gcode_host.sendCommand("G90\n");
    }
}

static void home_button_event_cb(lv_obj_t *btn, lv_event_t event)
{
    if (event == LV_EVENT_CLICKED)
    {
        log_esp3d("home_button Clicked");
        esp3d_gcode_host.sendCommand("M1112\n");
    }
}

static void reset_button_event_cb(lv_obj_t *btn, lv_event_t event)
{
    if (event == LV_EVENT_CLICKED)
    {
        log_esp3d("reset_button Clicked");
        esp3d_gcode_host.sendCommand("M1111\n");
    }
}

static void set_workorigin_button_event_cb(lv_obj_t *btn, lv_event_t event)
{
    if (event == LV_EVENT_CLICKED)
    {
        log_esp3d("set_workorigin_button Clicked");
        esp3d_gcode_host.sendCommand("G92 X0 Y0 Z0 E0\n");
    }
}

void show_basic_ui(lv_obj_t *esp_lv_screen)
{
    main_screen = esp_lv_screen;
    screen = lv_obj_create(esp_lv_screen, NULL);
    lv_obj_set_pos(screen, 0, 30);
    lv_obj_set_size(screen, 320, 480 - (1 * 30));
    lv_obj_set_style(screen, &lv_style_scr);

    //Z+
    lv_obj_t *z_plus_button = lv_btn_create(screen, NULL);
    lv_obj_set_pos(z_plus_button, 17, 5);
    lv_obj_set_size(z_plus_button, 85, 85);
    lv_obj_set_event_cb(z_plus_button, z_plus_button_event_cb);
    lv_obj_t *z_plus_button_label = lv_label_create(z_plus_button, NULL);
    lv_label_set_text(z_plus_button_label, "Z+");

    //Y+
    lv_obj_t *y_plus_button = lv_btn_create(screen, NULL);
    lv_obj_set_pos(y_plus_button, 117, 5);
    lv_obj_set_size(y_plus_button, 85, 85);
    lv_obj_set_event_cb(y_plus_button, y_plus_button_event_cb);
    lv_obj_t *y_plus_button_label = lv_label_create(y_plus_button, NULL);
    lv_label_set_text(y_plus_button_label, "Y+");

    //Z-
    lv_obj_t *z_minus_button = lv_btn_create(screen, NULL);
    lv_obj_set_pos(z_minus_button, 217, 5);
    lv_obj_set_size(z_minus_button, 85, 85);
    lv_obj_set_event_cb(z_minus_button, z_minus_button_event_cb);
    lv_obj_t *z_minus_button_label = lv_label_create(z_minus_button, NULL);
    lv_label_set_text(z_minus_button_label, "Z-");

    //X-
    lv_obj_t *x_minus_button = lv_btn_create(screen, NULL);
    lv_obj_set_pos(x_minus_button, 17, 100);
    lv_obj_set_size(x_minus_button, 85, 85);
    lv_obj_set_event_cb(x_minus_button, x_minus_button_event_cb);
    lv_obj_t *x_minus_button_label = lv_label_create(x_minus_button, NULL);
    lv_label_set_text(x_minus_button_label, "X-");

    //HOME
    lv_obj_t *home_button = lv_btn_create(screen, NULL);
    lv_obj_set_pos(home_button, 117, 100);
    lv_obj_set_size(home_button, 85, 85);
    lv_obj_set_event_cb(home_button, home_button_event_cb);
    lv_obj_t *home_button_label = lv_label_create(home_button, NULL);
    lv_label_set_text(home_button_label, "HOME");

    //X+
    lv_obj_t *x_plus_button = lv_btn_create(screen, NULL);
    lv_obj_set_pos(x_plus_button, 217, 100);
    lv_obj_set_size(x_plus_button, 85, 85);
    lv_obj_set_event_cb(x_plus_button, x_plus_button_event_cb);
    lv_obj_t *x_plus_button_label = lv_label_create(x_plus_button, NULL);
    lv_label_set_text(x_plus_button_label, "X+");

    //Y-
    lv_obj_t *y_minus_button = lv_btn_create(screen, NULL);
    lv_obj_set_pos(y_minus_button, 117, 195);
    lv_obj_set_size(y_minus_button, 85, 85);
    lv_obj_set_event_cb(y_minus_button, y_minus_button_event_cb);
    lv_obj_t *y_minus_button_label = lv_label_create(y_minus_button, NULL);
    lv_label_set_text(y_minus_button_label, "Y-");

    //Reset
    lv_obj_t *reset_button = lv_btn_create(screen, NULL);
    lv_obj_set_pos(reset_button, 15, 285);
    lv_obj_set_size(reset_button, 135, 80);
    lv_obj_set_event_cb(reset_button, reset_button_event_cb);
    lv_obj_t *reset_button_label = lv_label_create(reset_button, NULL);
    lv_label_set_text(reset_button_label, "Reset");

    //Set WorkOrigin
    lv_obj_t *set_workorigin_button = lv_btn_create(screen, NULL);
    lv_obj_set_pos(set_workorigin_button, 170, 285);
    lv_obj_set_size(set_workorigin_button, 135, 80);
    lv_obj_set_event_cb(set_workorigin_button, set_workorigin_button_event_cb);
    lv_obj_t *set_workorigin_button_label = lv_label_create(set_workorigin_button, NULL);
    lv_label_set_text(set_workorigin_button_label, "    Set\r\nWorkOrigin");

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
    lv_obj_set_event_cb(return_button, return_button_event_cb1);
    lv_obj_t *return_button_label = lv_label_create(return_button, NULL);
    lv_label_set_text(return_button_label, "Return");
}