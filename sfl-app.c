#include "sfl-app.h"
#include "sfl-app-window.h"

struct _SFLApp
{
  GtkApplication parent;
};

G_DEFINE_TYPE (SFLApp, sfl_app, GTK_TYPE_APPLICATION);

static void
sfl_app_init (SFLApp *app)
{
}

static void
sfl_app_finalize (GObject *object)
{
  G_OBJECT_CLASS (sfl_app_parent_class)->finalize (object);
}

static void
sfl_app_activate (GApplication *app)
{
  SFLAppWindow *win;

  win = sfl_app_window_new (SFL_APP (app));
  gtk_window_present (GTK_WINDOW (win));
}

static void
sfl_app_open (GApplication *app,
	      GFile **files,
	      int n_files,
	      const char *hint)
{
  GList *windows;
  SFLAppWindow *win;
  int i;

  windows = gtk_application_get_windows (GTK_APPLICATION (app));
  if (windows)
    win = SFL_APP_WINDOW (windows->data);
  else
    win = sfl_app_window_new (SFL_APP (app));

  for (i = 0; i < n_files; i++)
    sfl_app_window_open (win, files[i]);

  gtk_window_present (GTK_WINDOW (win));
} 

static void
sfl_app_class_init (SFLAppClass *class)
{
  G_APPLICATION_CLASS (class)->activate = sfl_app_activate;
  G_APPLICATION_CLASS (class)->open = sfl_app_open;

  G_OBJECT_CLASS (class)->finalize = sfl_app_finalize;
}

SFLApp *
sfl_app_new (void)
{
  return g_object_new (SFL_APP_TYPE, "application-id", "org.gtk.sflapp",
		       "flags", G_APPLICATION_HANDLES_OPEN, NULL);
}
