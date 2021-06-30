#include <gtk/gtk.h>

#include "sfl-app.h"
#include "sfl-stock-view.h"

struct _SFLStockView
{
  GtkBox parent;
  GtkWidget *name_label;
  GtkWidget *website_label;
  GtkWidget *industry_label;
  GtkWidget *price_label;
  GtkWidget *change_label;
  GtkWidget *high_label;
  GtkWidget *low_label;
  GtkWidget *open_label;
  GtkWidget *last_close_label;
  GtkWidget *cap_label;
  GtkWidget *yield_label;
  GtkWidget *pe_label;
  GtkWidget *ftw_label;

  SFLSymbol *symbol;
  
  gchar      *name_string;
  gchar      *industry_string;
  gchar      *website_string;
  gchar      *price_string;
  gchar      *change_string;
  gchar      *high_string;
  gchar      *low_string;
  gchar      *open_string;
  gchar      *last_close_string;
  gchar      *cap_string;
  gchar      *yield_string;
  gchar      *pe_string;
  gchar      *ftw_string;
};

G_DEFINE_TYPE (SFLStockView, sfl_stock_view, GTK_TYPE_BOX)

static void
sfl_stock_view_init (SFLStockView *view)
{
  gtk_widget_init_template (GTK_WIDGET (view));
}


static void
sfl_stock_view_finalize (GObject *object)
{
  SFLStockView *view;

  view = SFL_STOCK_VIEW (object);

  sfl_symbol_destroy (view->symbol);

  g_free (view->name_string);
  g_free (view->industry_string);
  g_free (view->website_string);
  g_free (view->price_string);
  g_free (view->change_string);
  g_free (view->high_string);
  g_free (view->low_string);
  g_free (view->open_string);
  g_free (view->last_close_string);
  g_free (view->cap_string);
  g_free (view->yield_string);
  g_free (view->pe_string);
  g_free (view->ftw_string);

  G_OBJECT_CLASS (sfl_stock_view_parent_class)->finalize (object);
}

static void
sfl_stock_view_class_init (SFLStockViewClass *class)
{
  gtk_widget_class_set_template_from_resource (GTK_WIDGET_CLASS (class), SFL_STOCK_VIEW_UI_PATH);

  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), SFLStockView, name_label);
  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), SFLStockView, industry_label);
  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), SFLStockView, website_label);
  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), SFLStockView, price_label);
  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), SFLStockView, change_label);
  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), SFLStockView, high_label);
  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), SFLStockView, low_label);
  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), SFLStockView, open_label);
  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), SFLStockView, last_close_label);
  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), SFLStockView, cap_label);
  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), SFLStockView, yield_label);
  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), SFLStockView, pe_label);
  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), SFLStockView, ftw_label);

  G_OBJECT_CLASS (class)->finalize = sfl_stock_view_finalize;
}

SFLStockView *
sfl_stock_view_new (void)
{
  return g_object_new (SFL_TYPE_STOCK_VIEW, NULL);
}

void sfl_stock_view_set_symbol (SFLStockView *view, gchar *ticker)
{
  // TODO: fail if invalid ticker
  view->symbol = sfl_symbol_new (ticker);
}

void
sfl_stock_view_update (SFLStockView *view)
{
  // TODO: fail if no symbol set

  view->name_string = g_markup_printf_escaped (SFL_STOCK_VIEW_NAME_MARKUP, 14, view->symbol->name);
  gtk_label_set_markup ( GTK_LABEL (view->name_label), view->name_string);

  view->industry_string = g_markup_printf_escaped (SFL_STOCK_VIEW_INDUSTRY_MARKUP, 14, view->symbol->industry);
  gtk_label_set_markup ( GTK_LABEL (view->industry_label), view->industry_string);

  view->website_string = g_markup_printf_escaped (SFL_STOCK_VIEW_WEBSITE_MARKUP, 14, view->symbol->website, view->symbol->website);
  gtk_label_set_markup ( GTK_LABEL (view->website_label), view->website_string);

  view->price_string = g_markup_printf_escaped (SFL_STOCK_VIEW_PRICE_MARKUP, 36, view->symbol->current_price);
  gtk_label_set_markup ( GTK_LABEL (view->price_label), view->price_string);

  gchar *arrow;
  double change = view->symbol->current_price - view->symbol->last_close_price;
  double change_percentage = (change/view->symbol->last_close_price)*100;
  char *colour;
  if (change >= 0) {
    arrow = "▲";
    colour = "green";
  } else {
    arrow = "▼";
    colour = "red";
  }
  view->change_string = g_markup_printf_escaped (SFL_STOCK_VIEW_CHANGE_MARKUP, 12, colour, arrow, change, ABS (change_percentage));
  gtk_label_set_markup ( GTK_LABEL (view->change_label), view->change_string);

  view->high_string = g_markup_printf_escaped (SFL_STOCK_VIEW_HIGH_MARKUP, 12, view->symbol->daily_high);
  gtk_label_set_markup ( GTK_LABEL (view->high_label), view->high_string);

  view->low_string = g_markup_printf_escaped (SFL_STOCK_VIEW_LOW_MARKUP, 12, view->symbol->daily_low);
  gtk_label_set_markup ( GTK_LABEL (view->low_label), view->low_string);

  view->open_string = g_markup_printf_escaped (SFL_STOCK_VIEW_OPEN_MARKUP, 12, view->symbol->open_price);
  gtk_label_set_markup ( GTK_LABEL (view->open_label), view->open_string);

  view->last_close_string = g_markup_printf_escaped (SFL_STOCK_VIEW_LAST_CLOSE_MARKUP, 12, view->symbol->last_close_price);
  gtk_label_set_markup ( GTK_LABEL (view->last_close_label), view->last_close_string);

  view->cap_string = g_markup_printf_escaped (SFL_STOCK_VIEW_CAP_MARKUP, 12, view->symbol->market_cap);
  gtk_label_set_markup ( GTK_LABEL (view->cap_label), view->cap_string);

  view->yield_string = g_markup_printf_escaped (SFL_STOCK_VIEW_YIELD_MARKUP, 12, view->symbol->dividend_yield, "%"); //ugly concat hack
  gtk_label_set_markup ( GTK_LABEL (view->yield_label), view->yield_string);

  view->pe_string = g_markup_printf_escaped (SFL_STOCK_VIEW_PE_MARKUP, 12, view->symbol->price_earnings);
  gtk_label_set_markup ( GTK_LABEL (view->pe_label), view->pe_string);

  view->ftw_string = g_markup_printf_escaped (SFL_STOCK_VIEW_FTW_MARKUP, 12, view->symbol->ftw_high, view->symbol->ftw_low);
  gtk_label_set_markup ( GTK_LABEL (view->ftw_label), view->ftw_string);
  // TODO: use FTWdate, timestamp

  
}
  
