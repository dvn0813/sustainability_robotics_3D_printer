/**
 * @file    lcdprint_u8g.cpp
 * @brief   LCD print api for u8glib
 * @author  Yunhui Fu (yhfudev@gmail.com)
 * @version 1.0
 * @date    2016-08-19
 * @copyright GPL/BSD
 */

#include "../../inc/MarlinConfigPre.h"

#if HAS_MARLINUI_U8GLIB

#include "marlinui_DOGM.h"

#include "../marlinui.h"
#include "../../MarlinCore.h"

#include "../utf8.h"
#include "u8g_fontutf8.h"
#include "../lcdprint.h"

int lcd_glyph_height() { return u8g_GetFontBBXHeight(u8g.getU8g()); }

void lcd_moveto(const lcd_uint_t col, const lcd_uint_t row) { u8g.setPrintPos(col, row); }

void lcd_put_int(const int i) { u8g.print(i); }

// return < 0 on error
// return the number of pixels advanced
int lcd_put_lchar_max(const lchar_t &c, const pixel_len_t max_length) {
  if (c < 256) {
    u8g.print((char)c);
    return u8g_GetFontBBXWidth(u8g.getU8g());
  }
  u8g_uint_t x = u8g.getPrintCol(), y = u8g.getPrintRow(),
           ret = uxg_DrawLchar(u8g.getU8g(), x, y, c, max_length);
  u8g.setPrintPos(x + ret, y);
  return ret;
}

/**
 * @return output width in pixels
 */
int lcd_put_u8str_max(const char * utf8_str, const pixel_len_t max_length) {
  u8g_uint_t x = u8g.getPrintCol(), y = u8g.getPrintRow(),
           ret = uxg_DrawUtf8Str(u8g.getU8g(), x, y, utf8_str, max_length);
  u8g.setPrintPos(x + ret, y);
  return ret;
}

/**
 * @return output width in pixels
 */
int lcd_put_u8str_max_P(PGM_P utf8_pstr, const pixel_len_t max_length) {
  u8g_uint_t x = u8g.getPrintCol(), y = u8g.getPrintRow(),
           ret = uxg_DrawUtf8StrP(u8g.getU8g(), x, y, utf8_pstr, max_length);
  u8g.setPrintPos(x + ret, y);
  return ret;
}

#endif // HAS_MARLINUI_U8GLIB
