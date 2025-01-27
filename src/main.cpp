#include <lvgl.h>
#include <LovyanGFX.hpp>

// Configuration de LovyanGFX pour votre écran
class LGFX : public lgfx::LGFX_Device {
    lgfx::Panel_ST7789 panel; // Contrôleur de l'écran
    lgfx::Bus_SPI bus;        // Bus SPI

public:
    LGFX() {
        auto cfg = bus.config();
        cfg.spi_host = SPI3_HOST;
        cfg.spi_mode = 0;
        cfg.freq_write = 40000000;   // Fréquence SPI
        cfg.pin_sclk = 36;          // Pin CLK
        cfg.pin_mosi = 35;          // Pin MOSI
        cfg.pin_miso = -1;          // Non utilisé
        cfg.pin_dc = 37;            // Pin Data/Command
        bus.config(cfg);
        panel.setBus(&bus);

        auto panel_cfg = panel.config();
        panel_cfg.pin_cs = 34;      // Pin CS
        panel_cfg.pin_rst = 38;     // Pin Reset
        panel_cfg.pin_busy = -1;    // Non utilisé
        panel_cfg.panel_width = 240;  // Largeur
        panel_cfg.panel_height = 240; // Hauteur
        panel_cfg.offset_x = 0;
        panel_cfg.offset_y = 0;
        panel.config(panel_cfg);

        setPanel(&panel);
    }
};

LGFX lcd;
#define BYTES_PER_PIXEL (LV_COLOR_FORMAT_GET_SIZE(LV_COLOR_FORMAT_RGB565))
/* Declare buffer for 1/10 screen size; BYTES_PER_PIXEL will be 2 for RGB565. */
static uint8_t buf1[LV_HOR_RES_MAX * LV_VER_RES_MAX / 10 * BYTES_PER_PIXEL];

void setup() {
    // Initialisation de l'écran
    lcd.init();
    lcd.setRotation(0);

    // Initialisation de LVGL
    lv_init();
    lv_display_t * display1 = lv_display_create(LV_HOR_RES_MAX, LV_VER_RES_MAX);
    /* Set display buffer for display `display1`. */
    lv_display_set_buffers(display1, buf1, NULL, sizeof(buf1), LV_DISPLAY_RENDER_MODE_PARTIAL);

    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = 240;
    disp_drv.ver_res = 240;
    disp_drv.flush_cb = [](lv_disp_drv_t* drv, const lv_area_t* area, lv_color_t* color_p) {
        lcd.startWrite();
        lcd.setAddrWindow(area->x1, area->y1, area->x2 - area->x1 + 1, area->y2 - area->y1 + 1);

        // Conversion des pixels
        uint16_t* buf = (uint16_t*)color_p;
        lcd.pushPixels(buf, (area->x2 - area->x1 + 1) * (area->y2 - area->y1 + 1));
        
        lcd.endWrite();
        lv_disp_flush_ready(drv);
    };
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    // Création du label "Hello World"
    lv_obj_t* label = lv_label_create(lv_scr_act());
    lv_label_set_text(label, "Hello World");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0); // Centre le texte
}

void loop() {
    lv_timer_handler();  // Gestion de la boucle LVGL
    delay(5);            // Délai pour éviter une surcharge CPU
}
