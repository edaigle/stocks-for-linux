#include <gtk/gtk.h>

#include "sfl-app.h"

int main (int argc, char *argv[])
{
  
  return g_application_run (G_APPLICATION (sfl_app_new ()), argc, argv);
}
