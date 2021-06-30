#ifndef __SFLAPPWIN_H
#define __SFLAPPWIN_H

#include <gtk/gtk.h>
#include "sfl-app.h"

#define SFL_APP_WINDOW_TYPE (sfl_app_window_get_type ())
G_DECLARE_FINAL_TYPE (SFLAppWindow, sfl_app_window, SFL, APP_WINDOW, GtkApplicationWindow)

#define SFL_WINDOW_UI_PATH "/home/ericdaigle/Projects/stocks-for-linux/sfl-app-window.ui" //TODO: permanent path

SFLAppWindow       *sfl_app_window_new          (SFLApp *app);
void                sfl_app_window_open         (SFLAppWindow *win,
                                                 GFile *file);


#endif /* __SFLAPPWIN_H */
