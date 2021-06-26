#include <gtk/gtk.h>

#include "sfl-app.h"
#include "sfl-app-window.h"

struct _SFLAppWindow
{
  GtkApplicationWindow parent;
  // TODO: stop all this from leaking
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
  char      *name_string;
  char      *industry_string;
  char      *website_string;
  char      *price_string;
  char      *change_string;
  char      *high_string;
  char      *low_string;
  char      *open_string;
  char      *last_close_string;
  char      *cap_string;
  char      *yield_string;
  char      *pe_string;
  char      *ftw_string;
};

G_DEFINE_TYPE (SFLAppWindow, sfl_app_window, GTK_TYPE_APPLICATION_WINDOW);

static void
sfl_app_window_init (SFLAppWindow *win)
{
  gtk_widget_init_template (GTK_WIDGET (win));
}

static void
sfl_app_window_class_init (SFLAppWindowClass *class)
{
  gtk_widget_class_set_template_from_resource (GTK_WIDGET_CLASS (class), "/home/ericdaigle/Projects/stocks-for-linux/builder.ui"); //TODO: permanent path

  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), SFLAppWindow, name_label);
  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), SFLAppWindow, industry_label);
  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), SFLAppWindow, website_label);
  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), SFLAppWindow, price_label);
  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), SFLAppWindow, change_label);
  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), SFLAppWindow, high_label);
  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), SFLAppWindow, low_label);
  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), SFLAppWindow, open_label);
  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), SFLAppWindow, last_close_label);
  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), SFLAppWindow, cap_label);
  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), SFLAppWindow, yield_label);
  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), SFLAppWindow, pe_label);
  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), SFLAppWindow, ftw_label);
}

SFLAppWindow *
sfl_app_window_new (SFLApp *app)
{
  return g_object_new (SFL_APP_WINDOW_TYPE, "application", app, NULL);
}

void
sfl_app_window_open (SFLAppWindow *win,
		     GFile *file)
{
  win->symbol = sfl_symbol_new (g_file_get_basename (file));

  win->name_string = g_markup_printf_escaped ("<span font=\"%d\" weight=\"bold\">%s</span>", 14, win->symbol->name); // TODO: put strings in header file
  gtk_label_set_markup ( GTK_LABEL (win->name_label), win->name_string);

  win->industry_string = g_markup_printf_escaped ("<span font=\"%d\" weight=\"light\">%s</span>", 14, win->symbol->industry); // TODO: put strings in header file
  gtk_label_set_markup ( GTK_LABEL (win->industry_label), win->industry_string);

  win->website_string = g_markup_printf_escaped ("<span font=\"%d\"><a href=\"%s\">%s</a></span>", 14, win->symbol->website, win->symbol->website);
  gtk_label_set_markup ( GTK_LABEL (win->website_label), win->website_string);

  win->price_string = g_markup_printf_escaped ("<span font=\"%d\" weight=\"bold\">%.2f</span>", 36, win->symbol->current_price);
  gtk_label_set_markup ( GTK_LABEL (win->price_label), win->price_string);

  double change = win->symbol->current_price - win->symbol->last_close_price;
  double change_percentage = (change/win->symbol->last_close_price)*100;
  char *colour;
  if (change >= 0) {
    colour = "green";
  } else {
    colour = "red";
  }
  win->change_string = g_markup_printf_escaped ("<span font=\"%d\">Today: <span foreground=\"%s\" weight=\"bold\">%.2f (%.2f\%)</span></span>", 12, colour, change, change_percentage);
  gtk_label_set_markup ( GTK_LABEL (win->change_label), win->change_string);

  win->high_string = g_markup_printf_escaped ("<span font=\"%d\">High: <span weight=\"bold\">%.2f</span></span>", 12, win->symbol->daily_high);
  gtk_label_set_markup ( GTK_LABEL (win->high_label), win->high_string);

  win->low_string = g_markup_printf_escaped ("<span font=\"%d\">Low: <span weight=\"bold\">%.2f</span></span>", 12, win->symbol->daily_low);
  gtk_label_set_markup ( GTK_LABEL (win->low_label), win->low_string);

  win->open_string = g_markup_printf_escaped ("<span font=\"%d\">Open: <span weight=\"bold\">%.2f</span></span>", 12, win->symbol->open_price);
  gtk_label_set_markup ( GTK_LABEL (win->open_label), win->open_string);

  win->last_close_string = g_markup_printf_escaped ("<span font=\"%d\">Last Close: <span weight=\"bold\">%.2f</span></span>", 12, win->symbol->last_close_price);
  gtk_label_set_markup ( GTK_LABEL (win->last_close_label), win->last_close_string);

  win->cap_string = g_markup_printf_escaped ("<span font=\"%d\">Market Cap: <span weight=\"bold\">%.2f</span></span>", 12, win->symbol->market_cap);
  gtk_label_set_markup ( GTK_LABEL (win->cap_label), win->cap_string);

  win->yield_string = g_markup_printf_escaped ("<span font=\"%d\">Yield: <span weight=\"bold\">%.2f</span></span>", 12, win->symbol->dividend_yield, "%"); //ugly concat hack
  gtk_label_set_markup ( GTK_LABEL (win->yield_label), win->yield_string);

  win->pe_string = g_markup_printf_escaped ("<span font=\"%d\">PE Ratio: <span weight=\"bold\">%.2f</span></span>", 12, win->symbol->price_earnings);
  gtk_label_set_markup ( GTK_LABEL (win->pe_label), win->pe_string);

  win->ftw_string = g_markup_printf_escaped ("<span font=\"%d\">52 Week High/Low: <span weight=\"bold\">%.2f / %.2f</span></span>", 12, win->symbol->ftw_high, win->symbol->ftw_low);
  gtk_label_set_markup ( GTK_LABEL (win->ftw_label), win->ftw_string);
  // TODO: use FTWdate, timestamp

  
}

//TODO: Finalizers
