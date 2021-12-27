#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <X11/extensions/XTest.h>

int main()
{
    Display *display;
    Window window;
    Window root_window;
    Window win_ret;
    int pos_root_x;
    int pos_root_y;
    int pos_win_x;
    int pos_win_y;
    XEvent event;
    int s;
    int i;
    int step_x = 10;
    int step_y = 10;
 
    /* open connection with the server */
    display = XOpenDisplay(NULL);
    if (display == NULL)
    {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }
 
    s = DefaultScreen(display);
    root_window = RootWindow(display, s);
    /* create window */
    window = XCreateSimpleWindow(display, RootWindow(display, s), 10, 10, 200, 200, 1,
                           BlackPixel(display, s), WhitePixel(display, s));
 
    /* select kind of events we are interested in */
    XSelectInput(display, window, KeyPressMask | KeyReleaseMask );
 
    /* map (show) the window */
    XMapWindow(display, window);
 
    /* event loop */
    XWarpPointer(display, None, root_window, 0, 0, 0, 0, 500,500);
    step_x = 10;
    step_y = 10;
    while (1)
    {
        XNextEvent(display, &event);
 
        /* keyboard events */
        if (event.type == KeyPress)
        {
            //printf( "KeyPress: %x\n", event.xkey.keycode );

            /* exit on ESC key press */
            if ( event.xkey.keycode == 0x09 ) {
                break;
	    }
	    else if ( event.xkey.keycode == 0x50 ) {
		XQueryPointer(display, root_window,&win_ret,&win_ret,&pos_root_x,&pos_root_y,&pos_win_x,&pos_win_y, &i);
		XWarpPointer(display, None, root_window, 0, 0, 0, 0, pos_root_x, pos_root_y-step_y);
	    }
	    else if ( event.xkey.keycode == 0x58 || event.xkey.keycode == 0x54 ) {
		XQueryPointer(display, root_window,&win_ret,&win_ret,&pos_root_x,&pos_root_y,&pos_win_x,&pos_win_y, &i);
		XWarpPointer(display, None, root_window, 0, 0, 0, 0, pos_root_x, pos_root_y+step_y);
	    }
	    else if ( event.xkey.keycode == 0x53 ) {
		XQueryPointer(display, root_window,&win_ret,&win_ret,&pos_root_x,&pos_root_y,&pos_win_x,&pos_win_y, &i);
		XWarpPointer(display, None, root_window, 0, 0, 0, 0, pos_root_x-step_x, pos_root_y);
	    }
	    else if ( event.xkey.keycode == 0x55 ) {
		XQueryPointer(display, root_window,&win_ret,&win_ret,&pos_root_x,&pos_root_y,&pos_win_x,&pos_win_y, &i);
		XWarpPointer(display, None, root_window, 0, 0, 0, 0, pos_root_x+step_x, pos_root_y);
	    }
	    else if ( event.xkey.keycode == 0x5a ) {
		    /* LMB */
		XTestFakeButtonEvent(display, 1, True, CurrentTime);
		XTestFakeButtonEvent(display, 1, False, CurrentTime);
		/* get focus back to this window */
		XSetInputFocus(display, window, RevertToNone, CurrentTime);
	    }
	    else if ( event.xkey.keycode == 0x5b ) {
		    /* RMB */
		XTestFakeButtonEvent(display, 3, True, CurrentTime);
		XTestFakeButtonEvent(display, 3, False, CurrentTime);
		XSetInputFocus(display, window, RevertToNone, CurrentTime);
	    }
	    else if ( event.xkey.keycode == 0x68 ) {
		    /* MMB */
		XTestFakeButtonEvent(display, 2, True, CurrentTime);
		XTestFakeButtonEvent(display, 2, False, CurrentTime);
		XSetInputFocus(display, window, RevertToNone, CurrentTime);
	    }
	    else if ( event.xkey.keycode == 0x56 ) {
		step_x += 50;
		step_y += 50;	
	    }
	    else if ( event.xkey.keycode == 0x52 ) {
		step_x = (step_x - 50) < 0 ? 10 : step_x - 50;;
		step_y = (step_y - 50) < 0 ? 10 : step_y - 50;;
	    }
	    
        }
        else if (event.type == KeyRelease)
        {

        }
    }

    /* close connection to server */
    XCloseDisplay(display);
 
    return 0;
}
