#include "sdcard_ui.h"
#include "main_ui.h"
#include "../../core/debug_esp3d.h"

#include "../filesystem/esp_sd.h"
#include "../gcode_host/gcode_host.h"

typedef struct {
    char file_name[64]; /**< SSID of AP */
    int file_size;      /**< signal strength of AP */
} file_list_t;
static lv_obj_t *main_screen;
static lv_obj_t *screen;
static void list_gcode_file(const char* dir_prefix, file_list_t *file_list)
{
    String ptmp = "/gcode";
    if (ESP_SD::exists(ptmp.c_str())) {
        ESP_SDFile f = ESP_SD::open(ptmp.c_str(), ESP_FILE_READ);
        //Parse files
        ESP_SDFile sub = f.openNextFile();
        log_esp3d("list file1111");
        log_esp3d("<DIR> \t");
        if (f) {
            log_esp3d("needseparator");
            bool needseparator = false;
            log_esp3d("sub name:%s", (sub.name()));
            int count = 0;
            while (sub) {
                log_esp3d("sub");
                if (needseparator) {
                    //buffer2send+=",";
                } else {
                    //for next entry
                    needseparator=true;
                }
                //buffer2send+="{\"name\":\"";
                //buffer2send+=sub.name();
                log_esp3d("name:%s", (sub.name()));
                memcpy(file_list[count].file_name, sub.name(),strlen(sub.name()));
                count++;
                //buffer2send+="\",\"size\":\"";
                if (sub.isDirectory()) {
                    //buffer2send+="-1";
                } else {
                    //buffer2send+=ESP_SD::formatBytes(sub.size());
                }
                sub.close();
                sub = f.openNextFile();
                log_esp3d("sub done");
            }
            f.close();
        } else {
            log_esp3d("file error1");
            //if (status == "ok") {
                //status = "cannot open" + ptmp;
            //} else {
                //status += ", cannot open" + ptmp;
            //}
        }
    } else {
        log_esp3d("file error2");
        //if (status == "ok") {
            //status = ptmp + " does not exists!";
        //} else {
            //status += ", " + ptmp + " does not exists!";
        //}
    }
}

static void list_event(lv_obj_t * btn, lv_event_t e)
{
    if(e == LV_EVENT_CLICKED) {
        log_esp3d("%s\n", lv_list_get_btn_text(btn));
        //level_authenticate_type auth_level = AuthenticationService::authenticated_level();
        //ESP3DOutput  output(_webserver);
        //esp3d_gcode_host.processFile("/gcode/h.g", 1, ESP3DOutput);
        //esp3d_gcode_host.processSDFile("/sd/gcode/h.g");
        char file_name[64];
        //sprintf(file_name, "/sd/gcode/");
        //log_esp3d("file name1: %s", (char *)file_name);
        sprintf(file_name, "/sd/gcode/%s", lv_list_get_btn_text(btn));
        esp3d_gcode_host.processSDFile(file_name);
        log_esp3d("file name2: %s", (char *)file_name);
    }

}

/*Texts of the list elements*/
const char * txts[] = {"First", "Second", "Third", "Forth", "Fifth", NULL};

void emergency_button_event_cb(lv_obj_t * btn, lv_event_t event)
{
    if(event == LV_EVENT_CLICKED) {
        log_esp3d("emergency_button Clicked");
    }
}

void main_button_event_cb(lv_obj_t * btn, lv_event_t event)
{
    if(event == LV_EVENT_CLICKED) {
        log_esp3d("main_button Clicked");
        if (screen != nullptr)
        {
            lv_obj_del(screen);
        }
        show_main_ui(main_screen);
    }
}

void return_button_event_cb(lv_obj_t * btn, lv_event_t event)
{
    if(event == LV_EVENT_CLICKED) {
        log_esp3d("return_button Clicked");
        if (screen != nullptr)
        {
            lv_obj_del(screen);
        }
        show_main_ui(main_screen);
    }
}

void return_button_event_cb1(lv_obj_t * btn, lv_event_t event)
{
    if(event == LV_EVENT_CLICKED) {
        log_esp3d("return_button1 Clicked");
        if (screen != nullptr)
        {
            lv_obj_del(screen);
        }
        show_main_ui(main_screen);
    }
}

void show_sdcard_ui(lv_obj_t *esp_lv_screen){
    //static file_list_t *file_list       = NULL; 
    //file_list = malloc(30 * sizeof(*file_list));
	//memset(file_list, 0x0, 30 * sizeof(*file_list));
    static file_list_t file_list[10]; 
    list_gcode_file("/sdcard/gcode", file_list);

    //if(screen != nullptr) {
        //lv_obj_del(screen);
    //}
    main_screen = esp_lv_screen;
    screen = lv_obj_create(esp_lv_screen, NULL);
    lv_obj_set_pos(screen, 0,30);
    lv_obj_set_size(screen, 320, 480 - (1*30));
    lv_obj_set_style(screen, &lv_style_scr);

    //lv_obj_t * sdcard_ui = lv_obj_create(screen, NULL);

    /*Create a list*/
    lv_obj_t* list = lv_list_create(screen, NULL);
    lv_obj_set_size(list, LV_HOR_RES, LV_VER_RES-80);
    lv_obj_set_pos(list, 0, 0);

    /*Add buttons*/
    uint8_t i;
    for(i = 0; txts[i]; i++) {
        lv_obj_t * btn = lv_list_add_btn(list, LV_SYMBOL_FILE, (char *)file_list[i].file_name);
        log_esp3d("file name: %s", (char *)file_list[i].file_name);
        //lv_obj_t * btn = lv_list_add_btn(list, LV_SYMBOL_FILE, txts[i]);
        lv_obj_set_event_cb(btn, list_event);       /*Assign event function*/
        //lv_btn_set_toggle(btn, true);               /*Enable on/off states*/
    }

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