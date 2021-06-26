#include <gtk/gtk.h>

#include "sfl-app.h"
#include "sfl-app-window.h"

struct _SFLAppWindow
{
  GtkApplicationWindow parent;

  GtkWidget *name_label;
  GtkWidget *website_label;
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
  char      *website_string;
  char      *price_string;
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

  win->name_string = g_markup_printf_escaped ("<span font=\"%d\">%s - %s</span>", 14, win->symbol->name, win->symbol->industry); // TODO: put strings in header file
  gtk_label_set_markup ( GTK_LABEL (win->name_label), win->name_string);

  win->website_string = g_markup_printf_escaped ("<span font=\"%d\">%s</span>", 14, win->symbol->website);
  gtk_label_set_markup ( GTK_LABEL (win->website_label), win->website_string);

  win->price_string = g_markup_printf_escaped ("<span font=\"%d\">%.2f</span>", 36, win->symbol->current_price);
  gtk_label_set_markup ( GTK_LABEL (win->price_label), win->price_string);
}

//TODO: Finalizers
