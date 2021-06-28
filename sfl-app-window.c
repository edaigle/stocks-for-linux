#include <gtk/gtk.h>

#include "sfl-app.h"
#include "sfl-app-window.h"

struct _SFLAppWindow
{
  GtkApplicationWindow parent;
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

G_DEFINE_TYPE (SFLAppWindow, sfl_app_window, GTK_TYPE_APPLICATION_WINDOW);

static void
sfl_app_window_init (SFLAppWindow *win)
{
  gtk_widget_init_template (GTK_WIDGET (win));
}


static void
sfl_app_window_finalize (GObject *object)
{
  SFLAppWindow *win;

  win = SFL_APP_WINDOW (object);

  sfl_symbol_destroy (win->symbol);

  g_free (win->name_string);
  g_free (win->industry_string);
  g_free (win->website_string);
  g_free (win->price_string);
  g_free (win->change_string);
  g_free (win->high_string);
  g_free (win->low_string);
  g_free (win->open_string);
  g_free (win->last_close_string);
  g_free (win->cap_string);
  g_free (win->yield_string);
  g_free (win->pe_string);
  g_free (win->ftw_string);

  G_OBJECT_CLASS (sfl_app_window_parent_class)->finalize (object);
}

static void
sfl_app_window_class_init (SFLAppWindowClass *class)
{
  gtk_widget_class_set_template_from_resource (GTK_WIDGET_CLASS (class), SFL_WINDOW_UI_PATH);

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

  G_OBJECT_CLASS (class)->finalize = sfl_app_window_finalize;
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

  win->name_string = g_markup_printf_escaped (SFL_WINDOW_NAME_MARKUP, 14, win->symbol->name);
  gtk_label_set_markup ( GTK_LABEL (win->name_label), win->name_string);

  win->industry_string = g_markup_printf_escaped (SFL_WINDOW_INDUSTRY_MARKUP, 14, win->symbol->industry);
  gtk_label_set_markup ( GTK_LABEL (win->industry_label), win->industry_string);

  win->website_string = g_markup_printf_escaped (SFL_WINDOW_WEBSITE_MARKUP, 14, win->symbol->website, win->symbol->website);
  gtk_label_set_markup ( GTK_LABEL (win->website_label), win->website_string);

  win->price_string = g_markup_printf_escaped (SFL_WINDOW_PRICE_MARKUP, 36, win->symbol->current_price);
  gtk_label_set_markup ( GTK_LABEL (win->price_label), win->price_string);

  gchar *arrow;
  double change = win->symbol->current_price - win->symbol->last_close_price;
  double change_percentage = (change/win->symbol->last_close_price)*100;
  char *colour;
  if (change >= 0) {
    arrow = "▲";
    colour = "green";
  } else {
    arrow = "▼";
    colour = "red";
  }
  win->change_string = g_markup_printf_escaped (SFL_WINDOW_CHANGE_MARKUP, 12, colour, arrow, change, ABS (change_percentage));
  gtk_label_set_markup ( GTK_LABEL (win->change_label), win->change_string);

  win->high_string = g_markup_printf_escaped (SFL_WINDOW_HIGH_MARKUP, 12, win->symbol->daily_high);
  gtk_label_set_markup ( GTK_LABEL (win->high_label), win->high_string);

  win->low_string = g_markup_printf_escaped (SFL_WINDOW_LOW_MARKUP, 12, win->symbol->daily_low);
  gtk_label_set_markup ( GTK_LABEL (win->low_label), win->low_string);

  win->open_string = g_markup_printf_escaped (SFL_WINDOW_OPEN_MARKUP, 12, win->symbol->open_price);
  gtk_label_set_markup ( GTK_LABEL (win->open_label), win->open_string);

  win->last_close_string = g_markup_printf_escaped (SFL_WINDOW_LAST_CLOSE_MARKUP, 12, win->symbol->last_close_price);
  gtk_label_set_markup ( GTK_LABEL (win->last_close_label), win->last_close_string);

  win->cap_string = g_markup_printf_escaped (SFL_WINDOW_CAP_MARKUP, 12, win->symbol->market_cap);
  gtk_label_set_markup ( GTK_LABEL (win->cap_label), win->cap_string);

  win->yield_string = g_markup_printf_escaped (SFL_WINDOW_YIELD_MARKUP, 12, win->symbol->dividend_yield, "%"); //ugly concat hack
  gtk_label_set_markup ( GTK_LABEL (win->yield_label), win->yield_string);

  win->pe_string = g_markup_printf_escaped (SFL_WINDOW_PE_MARKUP, 12, win->symbol->price_earnings);
  gtk_label_set_markup ( GTK_LABEL (win->pe_label), win->pe_string);

  win->ftw_string = g_markup_printf_escaped (SFL_WINDOW_FTW_MARKUP, 12, win->symbol->ftw_high, win->symbol->ftw_low);
  gtk_label_set_markup ( GTK_LABEL (win->ftw_label), win->ftw_string);
  // TODO: use FTWdate, timestamp

  
}
  
