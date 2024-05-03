/*
gcc -o getIdleTime src/main.c -Wall -std=c17 -lXss -lX11 
clang -o scrnsvr src/main.c -Wall -std=c17 -lXss -lX11 -Oz
https://www.x.org/releases/X11R7.6/doc/libX11/specs/libX11/libX11.html
*/

#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>

#include "./lib.c"

int main(void) {
  char * id = getenv("DISPLAY");
  if (id == NULL) {
    id = ":0.0";
  }
  Display *dpy = XOpenDisplay(id);
  if (dpy == NULL) {
    fprintf(stderr, "couldn't open display!\n");
    return 1;
  }

  XScreenSaverInfo *info = XScreenSaverAllocInfo();
  if (info == NULL) {
    fprintf(stderr, "couldn't allocate screen saver info!\n");
    XCloseDisplay(dpy);
    return 1;
  }

  for (;;) {
    if (check_timer(dpy, info) != 0) {
      fprintf(stderr, "timer check did not return successfully\n");
      XFree(info);
      XCloseDisplay(dpy);
      return 1;
    } else {
      sleep(5);
    }
  }

  XFree(info);
  XCloseDisplay(dpy);

  return(0);
}
