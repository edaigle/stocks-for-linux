#include <gtk/gtk.h>

#include "sfl-app.h"
#include "sfl-app-window.h"
#include "sfl-stock-view.h"

struct _SFLAppWindow
{
  GtkApplicationWindow parent;
  
  GtkWidget *stack;
};

G_DEFINE_TYPE (SFLAppWindow, sfl_app_window, GTK_TYPE_APPLICATION_WINDOW)

static void
sfl_app_window_init (SFLAppWindow *win)
{
  gtk_widget_init_template (GTK_WIDGET (win));
}


static void
sfl_app_window_finalize (GObject *object)
{
  G_OBJECT_CLASS (sfl_app_window_parent_class)->finalize (object);
}

static void
sfl_app_window_class_init (SFLAppWindowClass *class)
{
  gtk_widget_class_set_template_from_resource (GTK_WIDGET_CLASS (class), SFL_WINDOW_UI_PATH);

  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), SFLAppWindow, stack);
  
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
  SFLStockView *view;
  gchar *ticker;

  ticker = g_file_get_basename (file);

  view = sfl_stock_view_new ();
  sfl_stock_view_set_symbol (view, ticker);
  sfl_stock_view_update (view);

  gtk_stack_add_titled (GTK_STACK (win->stack), GTK_WIDGET (view), ticker, ticker);
}
