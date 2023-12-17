#include "draw.h"
#include "BMP.h"
#include "X11/X.h"
#include "X11/Xlib.h"
#include <stdio.h>
#include <stdlib.h>

Display *display;
Screen screen;
XGCValues gcv;
GC gc;

Window createWindow(Display *display, int x, int y, int w, int h) {
  return XCreateSimpleWindow(display, DefaultRootWindow(display), x, y, w, h, 2,
                             0xffbbff, 0xffffff);
}

void draw(BMP *img) {
  display = XOpenDisplay(NULL);
  Window win = createWindow(display, 100, 200, img->img.width, img->img.height);
  XSelectInput(display, win,
               ExposureMask | KeyPressMask | EnterWindowMask | LeaveWindowMask |
                   ButtonPressMask);

  XMapWindow(display, win);
  gc = XCreateGC(display, win, GCForeground, &gcv);

  XEvent *ev;
  XNextEvent(display, ev);
  while (True) {

    switch (ev->type) {
    case Expose:
      for (int i = 0; i < img->img.width; i += 1) {
        for (int j = 0; j < img->img.height; j += 1) {
          gcv.foreground = img->data[j * img->img.width + i];
          XChangeGC(display, gc, GCForeground, &gcv);
          // XFillRectangle(display, win, gc, i, j, 1, 1);
          XDrawPoint(display, win, gc, i, j);
        }
      }
      // XFlush(display);

      break;
    }
  }
}
void draw2(BMP *img) {
  Display *display = XOpenDisplay(NULL);
  Window win = createWindow(display, 100, 200, img->img.width, img->img.height);
  XSelectInput(display, win,
               ExposureMask | KeyPressMask | EnterWindowMask | LeaveWindowMask |
                   ButtonPressMask);
  XMapWindow(display, win);

  XGCValues gcv;
  GC gc = XCreateGC(display, win, 0, &gcv);

  XImage *ximage =
      XCreateImage(display, DefaultVisual(display, 0), DefaultDepth(display, 0),
                   ZPixmap, 0, (char *)img->data, img->img.width,
                   img->img.height, 32, img->img.width * sizeof(int));
  XEvent *ev;
  XNextEvent(display, ev);
  while (True) {
    switch (ev->type) {
    case Expose:
      XPutImage(display, win, gc, ximage, 0, 0, 0, 0, img->img.width,
                img->img.height);
      XFlush(display);
    }
  }

  XFreeGC(display, gc);
  XCloseDisplay(display);
}

int main(int argc, const char **argv) {
  int w, h;
  if (argc < 3) {
    fprintf(stderr, "\t[EE] chose a file and its format to open\n\texample : "
                    "./draw file BMP\n");
    exit(EXIT_FAILURE);
  }

  BMP *img = img_open(argv[1], argv[2]);
  // img_print(img);
  get_size(img, &w, &h);
  printf("with is %d, height = %d\n", w, h);
  draw2(img);
  return 0;
}