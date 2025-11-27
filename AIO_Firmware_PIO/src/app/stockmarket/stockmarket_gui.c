#include "stockmarket_gui.h"

#include "lvgl.h"

LV_FONT_DECLARE(lv_font_ibmplex_115);
LV_FONT_DECLARE(ch_font20);

static lv_obj_t *stockmarket_gui = NULL;

static lv_obj_t *nowQuoLabel = NULL;

static lv_style_t default_style;
static lv_style_t numberBig_style;
static lv_style_t chFont_style;

// static lv_img_decoder_dsc_t img_dc_dsc; // 图片解码器

LV_FONT_DECLARE(lv_font_montserrat_40);
LV_IMG_DECLARE(bilibili_logo_ico);

LV_IMG_DECLARE(imgbtn_green);
LV_IMG_DECLARE(imgbtn_blue);

void stockmarket_gui_init(void)
{
    lv_style_init(&default_style);
    lv_style_set_bg_color(&default_style, lv_color_hex(0x000000));

    // 大号橙色数字样式（参考纪念日app）
    lv_style_init(&numberBig_style);
    lv_style_set_text_opa(&numberBig_style, LV_OPA_COVER);
    lv_style_set_text_color(&numberBig_style, lv_color_hex(0xffa500)); // 橙色
    lv_style_set_text_font(&numberBig_style, &lv_font_ibmplex_115);  // 适中字体

    lv_style_init(&chFont_style);
    lv_style_set_text_opa(&chFont_style, LV_OPA_COVER);
    lv_style_set_text_color(&chFont_style, lv_color_hex(0xffffff));
    lv_style_set_text_font(&chFont_style, &ch_font20);
}

void display_stockmarket_init(void)
{
    lv_obj_t *act_obj = lv_scr_act(); // 获取当前活动页
    if (act_obj == stockmarket_gui)
        return;

    stockmarket_gui_del(); // 清空对象
    lv_obj_clean(act_obj); // 清空此前页面

    stockmarket_gui = lv_obj_create(NULL);
    lv_obj_add_style(stockmarket_gui, &default_style, LV_STATE_DEFAULT);

    // 当前价格标签（大号橙色数字）
    nowQuoLabel = lv_label_create(stockmarket_gui);
    lv_obj_add_style(nowQuoLabel, &numberBig_style, LV_STATE_DEFAULT);
    lv_label_set_recolor(nowQuoLabel, true);
    lv_label_set_text_fmt(nowQuoLabel, "0.00");
    lv_obj_align(nowQuoLabel, LV_ALIGN_CENTER, 0, 0);

    lv_scr_load(stockmarket_gui);
}

/*
 * 其他函数请根据需要添加
 */

void display_stockmarket(struct StockMarket stockInfo, lv_scr_load_anim_t anim_type)
{
    display_stockmarket_init();

    // 显示股票价格乘以1000，使用大号橙色数字
    lv_label_set_text_fmt(nowQuoLabel, "#ffa500 %.0f#", stockInfo.NowQuo * 1000);
}

void stockmarket_gui_del(void)
{
    if (NULL != stockmarket_gui)
    {
        lv_obj_clean(stockmarket_gui);
        stockmarket_gui = NULL;
        nowQuoLabel = NULL;
    }

    // 手动清除样式，防止内存泄漏
    // lv_style_reset(&default_style);
    // lv_style_reset(&numberBig_style);
    // lv_style_reset(&chFont_style);
}