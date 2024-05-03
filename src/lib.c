/* https://www.x.org/releases/X11R7.6/doc/libX11/specs/libX11/libX11.html */

//#include <X11/X.h>
#include <X11/Xlib.h>
//#include <X11/extensions/saver.h>
#include <X11/extensions/scrnsaver.h>
//#include <stdio.h>
#include <unistd.h>


int check_timer(Display *dpy, XScreenSaverInfo *info) {
  XScreenSaverQueryInfo(dpy, DefaultRootWindow(dpy), info);

  //printf("state: %d idle time: %lums\n", info->state, info->idle);
  if (info->state == ScreenSaverDisabled && info->idle >  10 * 60 * 1000) {
    XForceScreenSaver(dpy, ScreenSaverActive);
  }

  return 0;
}
