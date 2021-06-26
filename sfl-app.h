#ifndef __SFLAPP_H
#define __SFLAPP_H

#include <gtk/gtk.h>

#define SFL_APP_TYPE (sfl_app_get_type ())
G_DECLARE_FINAL_TYPE (SFLApp, sfl_app, SFL, APP, GtkApplication)

SFLApp *sfl_app_new (void);

#endif
