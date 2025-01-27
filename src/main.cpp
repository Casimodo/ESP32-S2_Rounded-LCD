#include <lvgl.h>
#include <TFT_eSPI.h>

LV_IMG_DECLARE(my_image);

// Configuration de l'écran
TFT_eSPI tft = TFT_eSPI();
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[LV_HOR_RES_MAX * 10];

// Callbacks pour LVGL
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, area->x2, area->y2);
    tft.pushColors((uint16_t *)&color_p->full, (area->x2 - area->x1 + 1) * (area->y2 - area->y1 + 1), true);
    tft.endWrite();
    lv_disp_flush_ready(disp);
}

void my_touch_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data) {
    uint16_t touchX, touchY;

    if (tft.getTouch(&touchX, &touchY)) {
        data->state = LV_INDEV_STATE_PR;
        data->point.x = touchX;
        data->point.y = touchY;
    } else {
        data->state = LV_INDEV_STATE_REL;
    }
}

// Écrans
static lv_obj_t *screen1, *screen2;

// Créer un graphique
void create_chart(lv_obj_t *parent) {
    lv_obj_t *chart = lv_chart_create(parent);
    lv_obj_set_size(chart, 200, 120);
    lv_obj_align(chart, LV_ALIGN_CENTER, 0, -20);
    lv_chart_series_t *ser = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);
    lv_chart_set_next_value(chart, ser, 10);
    lv_chart_set_next_value(chart, ser, 30);
    lv_chart_set_next_value(chart, ser, 20);
}

// Ajouter une image
void create_image(lv_obj_t *parent) {
    LV_IMG_DECLARE(my_image); // Charger l'image
    lv_obj_t *img = lv_img_create(parent);
    lv_img_set_src(img, &my_image);
    lv_obj_align(img, LV_ALIGN_CENTER, 0, 60);
}

void setup() {
    // Initialisation de LVGL et TFT
    lv_init();
    tft.begin();
    tft.setRotation(1);
    lv_disp_draw_buf_init(&draw_buf, buf, NULL, LV_HOR_RES_MAX * 10);

    // Configuration de l'affichage LVGL
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    disp_drv.hor_res = 240;
    disp_drv.ver_res = 240;
    lv_disp_drv_register(&disp_drv);

    // Configuration du tactile
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touch_read;
    lv_indev_drv_register(&indev_drv);

    // Écran 1 : Hello World
    screen1 = lv_obj_create(NULL);
    lv_obj_t *label = lv_label_create(screen1);
    lv_label_set_text(label, "Hello World!");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

    // Écran 2 : Graphique et image
    screen2 = lv_obj_create(NULL);
    create_chart(screen2);
    create_image(screen2);

    // Ajouter swipe entre les écrans
    lv_obj_t *swipe_group = lv_obj_create(NULL);
    lv_group_add_obj(swipe_group, screen1);
    lv_group_add_obj(swipe_group, screen2);

    // Afficher l'écran 1
    lv_scr_load(screen1);
}

void loop() {
    lv_timer_handler();
    delay(5);
}
