#include <gtk/gtk.h>

#include "sfl-app.h"
#include "sfl-app-window.h"
#include "sfl-stock-view.h"

struct _SFLAppWindow
{
  GtkApplicationWindow parent;

  GtkWidget *add_button;
  GtkWidget *refresh_button;
  GtkWidget *stack;
};

G_DEFINE_TYPE (SFLAppWindow, sfl_app_window, GTK_TYPE_APPLICATION_WINDOW)

// TODO: handle failure
static void
add_stock_dialog_cb (GtkDialog *dialog,
		     int response_id,
		     gpointer data)
{
  SFLAppWindow *win;
  SFLStockView *new_view;

  GtkWidget *child;
  GtkEntryBuffer *buffer;
  const gchar *ticker;

  if (response_id != GTK_RESPONSE_YES)
    return;

  //TODO: explain this clusterfuck
  child = GTK_WIDGET (gtk_dialog_get_content_area (dialog));
  child = gtk_widget_get_first_child (child);
  for (child = gtk_widget_get_first_child (child);
       child != NULL;
       child = gtk_widget_get_next_sibling (child))
    {
      if (GTK_IS_ENTRY (child)) {
	buffer = gtk_entry_get_buffer (GTK_ENTRY (child));
	ticker = gtk_entry_buffer_get_text (buffer);
      }
    }

  win = SFL_APP_WINDOW (data);
    
  new_view = sfl_stock_view_new ();
  if (sfl_stock_view_set_symbol (new_view, ticker)) {
    sfl_stock_view_update (new_view);

    gtk_stack_add_titled (GTK_STACK (win->stack), GTK_WIDGET (new_view), ticker, ticker);
    gtk_stack_set_visible_child_name (GTK_STACK (win->stack), ticker);
  } 

  gtk_window_destroy (GTK_WINDOW (dialog));
}

static void
add_button_cb (GtkWidget *widget,
		 gpointer data)
{
  GtkWidget *win;
  
  GtkWidget *add_dialog;
  GtkWidget *content;
  GtkWidget *vbox;
  GtkWidget *add_label;
  GtkWidget *add_entry;
  GtkDialogFlags flags;

  gchar *ticker;
  SFLStockView *new_view;

  win = GTK_WIDGET (data);

  flags = GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT | GTK_DIALOG_USE_HEADER_BAR;
  add_dialog = gtk_dialog_new_with_buttons ("New Stock",
					    GTK_WINDOW (win),
					    flags,
					    "Add",
					    GTK_RESPONSE_YES,
					    NULL);

  g_signal_connect (add_dialog,
		    "response",
		    G_CALLBACK (add_stock_dialog_cb),
		    win);

  content = gtk_dialog_get_content_area (GTK_DIALOG (add_dialog));
  gtk_widget_set_margin_start (content, 12);
  gtk_widget_set_margin_top (content, 12);
  gtk_widget_set_margin_end (content, 12);
  gtk_widget_set_margin_bottom (content, 12);
  gtk_widget_set_halign (content, GTK_ALIGN_CENTER);

  add_label = gtk_label_new ("");
  gtk_label_set_markup (GTK_LABEL (add_label), "<span font=\"14\">Ticker Symbol:</span>"); //TODO: put in header

  add_entry = gtk_entry_new ();
  gtk_entry_set_placeholder_text (GTK_ENTRY (add_entry), "Ex: TSLA");

  vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 12);
  gtk_box_append (GTK_BOX (vbox), add_label);
  gtk_box_append (GTK_BOX (vbox), add_entry);


  gtk_box_append (GTK_BOX (content), vbox);
  
  gtk_widget_show (add_dialog);
}

static void
refresh_button_cb (GtkWidget *widget,
		   gpointer data)
{
  SFLAppWindow *win;
  SFLStockView *view;

  win = SFL_APP_WINDOW (data);
  view = SFL_STOCK_VIEW (gtk_stack_get_visible_child ( GTK_STACK (win->stack)));

  if (view)
    sfl_stock_view_refresh (view);
}

static void
sfl_app_window_init (SFLAppWindow *win)
{
  gtk_widget_init_template (GTK_WIDGET (win));

  g_signal_connect (win->refresh_button, "clicked",
		    G_CALLBACK (refresh_button_cb), win);
  g_signal_connect (win->add_button, "clicked",
		    G_CALLBACK (add_button_cb), win);
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

  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), SFLAppWindow, add_button);
  gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), SFLAppWindow, refresh_button);
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
