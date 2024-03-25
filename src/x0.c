#include <stdio.h>
#include <X11/Xos.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

int main() {
    Display *dpy;
    int scr;
    Window win;
    XSetWindowAttributes xswa;
    char *xservname=NULL;
    //char *title="非ASCII文字は表示されずなぜかaになる…どうすればいい？";
    char *title="MyApp";

    if ((dpy=XOpenDisplay(xservname)) == NULL) {
        fprintf(stderr,"can not open %s\n",XDisplayName(xservname));
        exit(-1);
    }
    scr = DefaultScreen(dpy);
    xswa.background_pixel = BlackPixel(dpy,scr);
    xswa.border_pixel = WhitePixel(dpy,scr);
    xswa.event_mask = ExposureMask;
    win = XCreateWindow(dpy,RootWindow(dpy,scr),0,0,320,240,1,
                        CopyFromParent,CopyFromParent,CopyFromParent,
                        CWBackPixel | CWBorderPixel | CWEventMask, &xswa);
    XStoreName(dpy, win, title);
    XMapWindow(dpy,win);
    for (;;) {
        XEvent ev;
        XNextEvent(dpy,&ev);
        switch (ev.type) {
          case Expose:
            XClearWindow(dpy,win);
            break;
          default:
            printf("unknown event %d\n",ev.type);
            break;
        }
    }
}
