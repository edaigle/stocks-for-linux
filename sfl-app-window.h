#ifndef __SFLAPPWIN_H
#define __SFLAPPWIN_H

#include <gtk/gtk.h>
#include "sfl-app.h"

#include "sfl-symbol.h"


#define SFL_APP_WINDOW_TYPE (sfl_app_window_get_type ())
G_DECLARE_FINAL_TYPE (SFLAppWindow, sfl_app_window, SFL, APP_WINDOW, GtkApplicationWindow)

#define SFL_WINDOW_UI_PATH "/home/ericdaigle/Projects/stocks-for-linux/builder.ui" //TODO: permanent path

#define SFL_WINDOW_NAME_MARKUP "<span font=\"%d\" weight=\"bold\">%s</span>"
#define SFL_WINDOW_INDUSTRY_MARKUP "<span font=\"%d\" weight=\"light\">%s</span>"
#define SFL_WINDOW_WEBSITE_MARKUP "<span font=\"%d\"><a href=\"%s\">%s</a></span>"
#define SFL_WINDOW_PRICE_MARKUP "<span font=\"%d\" weight=\"bold\">%.2f</span>"
#define SFL_WINDOW_CHANGE_MARKUP "<span font=\"%d\">Today: <span foreground=\"%s\" weight=\"bold\">%s %.2f (%.2f\%)</span></span>"
#define SFL_WINDOW_HIGH_MARKUP "<span font=\"%d\">High: <span weight=\"bold\">%.2f</span></span>"
#define SFL_WINDOW_LOW_MARKUP "<span font=\"%d\">High: <span weight=\"bold\">%.2f</span></span>"
#define SFL_WINDOW_OPEN_MARKUP "<span font=\"%d\">Open: <span weight=\"bold\">%.2f</span></span>"
#define SFL_WINDOW_LAST_CLOSE_MARKUP "<span font=\"%d\">Last Close: <span weight=\"bold\">%.2f</span></span>"
#define SFL_WINDOW_CAP_MARKUP "<span font=\"%d\">Market Cap: <span weight=\"bold\">%.2f</span></span>"
#define SFL_WINDOW_YIELD_MARKUP "<span font=\"%d\">Yield: <span weight=\"bold\">%.2f %s</span></span>"
#define SFL_WINDOW_PE_MARKUP "<span font=\"%d\">PE Ratio: <span weight=\"bold\">%.2f</span></span>"
#define SFL_WINDOW_FTW_MARKUP "<span font=\"%d\">52 Week High/Low: <span weight=\"bold\">%.2f / %.2f</span></span>"


SFLAppWindow       *sfl_app_window_new          (SFLApp *app);
void                sfl_app_window_open         (SFLAppWindow *win,
                                                 GFile *file);


#endif /* __SFLAPPWIN_H */
