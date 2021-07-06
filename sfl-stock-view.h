#ifndef __SFLSTOCKVIEW_H
#define __SFLSTOCKVIEW_H

#include <gtk/gtk.h>
#include "sfl-app.h"

#include "sfl-symbol.h"


#define SFL_TYPE_STOCK_VIEW (sfl_stock_view_get_type ())
G_DECLARE_FINAL_TYPE (SFLStockView, sfl_stock_view, SFL, STOCK_VIEW, GtkBox)

#define SFL_STOCK_VIEW_UI_PATH "/home/ericdaigle/Projects/stocks-for-linux/sfl-stock-view.ui" //TODO: permanent path

#define SFL_STOCK_VIEW_NAME_MARKUP "<span font=\"%d\" weight=\"bold\">%s</span>"
#define SFL_STOCK_VIEW_INDUSTRY_MARKUP "<span font=\"%d\" weight=\"light\">%s</span>"
#define SFL_STOCK_VIEW_WEBSITE_MARKUP "<span font=\"%d\"><a href=\"%s\">%s</a></span>"
#define SFL_STOCK_VIEW_PRICE_MARKUP "<span font=\"%d\" weight=\"bold\">%.2f</span>"
#define SFL_STOCK_VIEW_CHANGE_MARKUP "<span font=\"%d\">Today: <span foreground=\"%s\" weight=\"bold\">%s %.2f (%.2f\%)</span></span>"
#define SFL_STOCK_VIEW_HIGH_MARKUP "<span font=\"%d\">High: <span weight=\"bold\">%.2f</span></span>"
#define SFL_STOCK_VIEW_LOW_MARKUP "<span font=\"%d\">Low: <span weight=\"bold\">%.2f</span></span>"
#define SFL_STOCK_VIEW_OPEN_MARKUP "<span font=\"%d\">Open: <span weight=\"bold\">%.2f</span></span>"
#define SFL_STOCK_VIEW_LAST_CLOSE_MARKUP "<span font=\"%d\">Last Close: <span weight=\"bold\">%.2f</span></span>"
#define SFL_STOCK_VIEW_CAP_MARKUP "<span font=\"%d\">Market Cap: <span weight=\"bold\">%.2f</span></span>"
#define SFL_STOCK_VIEW_YIELD_MARKUP "<span font=\"%d\">Yield: <span weight=\"bold\">%.2f %s</span></span>"
#define SFL_STOCK_VIEW_PE_MARKUP "<span font=\"%d\">PE Ratio: <span weight=\"bold\">%.2f</span></span>"
#define SFL_STOCK_VIEW_FTW_MARKUP "<span font=\"%d\">52 Week High/Low: <span weight=\"bold\">%.2f / %.2f</span></span>"


SFLStockView       *sfl_stock_view_new          (void);
void                sfl_stock_view_set_symbol (SFLStockView *view, gchar *ticker);
void                sfl_stock_view_refresh (SFLStockView *view);
void                sfl_stock_view_update (SFLStockView *view);


#endif /* __SFLSTOCKVIEW_H */
