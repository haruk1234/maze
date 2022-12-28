#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include "3d.h"
#include "../maze.h"


tdDraw tddraw;
tdDrawObject showobject;


struct MazeOption {
    bool wall = true;
};

Maze maze(15,15);
MazeOption option;
tdDrawPolygon arraytopoly(std::array<int,12> a) {
    return {{a[0],a[1],a[2]},{a[3],a[4],a[5]},{a[6],a[7],a[8]},{(unsigned char)a[9],(unsigned char)a[10],(unsigned char)a[11]}};
}
tdDrawObject getmaze3d() {
	tdDrawObject m3d = {};
	int x = maze.size[0];int y = maze.size[1];
	for (int ly=0;ly<y;ly++) {
		for (int lx=0;lx<x;lx++) {
			if (maze.maze[ly][lx]==0) {
				if (option.wall) {
					// m3d.insert(m3d.end(),arraytopoly({lx,ly,1,lx+1,ly,1,lx+1,ly+1,1,255,255,255}));
					// m3d.insert(m3d.end(),arraytopoly({lx,ly+1,1,lx,ly,1,lx+1,ly+1,1,255,255,255}));
					if (!(lx>0&&maze.maze[ly][lx-1]==0)) {
						m3d.insert(m3d.end(),arraytopoly({lx,ly,0,lx,ly,1,lx,ly+1,0,255,255,255}));
						m3d.insert(m3d.end(),arraytopoly({lx,ly,1,lx,ly+1,1,lx,ly+1,0,255,255,255}));
					}
					if (!(ly<y-1&&maze.maze[ly+1][lx]==0)) {
						m3d.insert(m3d.end(),arraytopoly({lx,ly+1,0,lx,ly+1,1,lx+1,ly+1,1,255,255,255}));
						m3d.insert(m3d.end(),arraytopoly({lx+1,ly+1,0,lx,ly+1,0,lx+1,ly+1,1,255,255,255}));
					}
                    if (!(lx<x-1&&maze.maze[ly][lx+1]==0)) {
						m3d.insert(m3d.end(),arraytopoly({lx+1,ly+1,0,lx+1,ly+1,1,lx+1,ly,1,255,255,255}));
						m3d.insert(m3d.end(),arraytopoly({lx+1,ly,0,lx+1,ly+1,0,lx+1,ly,1,255,255,255}));
					}
					if (!(ly>0&&maze.maze[ly-1][lx]==0)) {
						m3d.insert(m3d.end(),arraytopoly({lx+1,ly,0,lx+1,ly,1,lx,ly,1,255,255,255}));
						m3d.insert(m3d.end(),arraytopoly({lx,ly,0,lx+1,ly,0,lx,ly,1,255,255,255}));
					}
				}
			}
			else {
				m3d.insert(m3d.end(),arraytopoly({lx,ly,0,lx+1,ly,0,lx+1,ly+1,0,255,255,255}));
				m3d.insert(m3d.end(),arraytopoly({lx,ly+1,0,lx,ly,0,lx+1,ly+1,0,255,255,255}));
			}
		}
	}
    std::cout << m3d.size() << " polygons generated" << std::endl;
	return m3d;
}

XImage *get3dImg(Display *display, Visual *visual, unsigned char *image, int width, int height)
{
	unsigned char* lpPixel = tddraw.getImg(width,height);
    return XCreateImage(display, visual, DefaultDepth(display,DefaultScreen(display)), ZPixmap, 0, (char*)lpPixel, width, height, 32, 0);
}
void paint(Display*d,Window w,int screen,GC gc){

	unsigned int width, height;
	unsigned int dummy;
	XGetGeometry( d, w, (Window*)&dummy, (int*)&dummy, (int*)&dummy, &width, &height, &dummy, &dummy );

    XImage *ximage;
    Visual *visual=DefaultVisual(d, 0);

    ximage=get3dImg(d, visual, 0, width, height);
    XSelectInput(d, w, ButtonPressMask|ExposureMask);
    XMapWindow(d, w);
    XPutImage(d, w, DefaultGC(d, 0), ximage, 0, 0, 0, 0, width, height);

	XFlush( d );
}

int main(){

    showobject = getmaze3d();
    tddraw.setObj(showobject);
    tddraw.setCamera({-5,-5,2},{45*(pi/180),0*(pi/180)});




	Display	*d;
	Window	w;
	int screen;
	XSetWindowAttributes attr;
	GC gc;
	
	d = XOpenDisplay( NULL );
	screen=DefaultScreen(d);

	w = XCreateSimpleWindow( d, RootWindow(d,screen),
						0, 0, 500, 400,// Window Size
						1,BlackPixel(d,screen),
						WhitePixel(d,screen));

	attr.backing_store = WhenMapped;
	XChangeWindowAttributes( d, w, CWBackingStore, &attr); 

	XStoreName(d, w, "Neknaj 3D Maze");
	XSetIconName(d, w, "Neknaj 3D Maze");

	gc = XCreateGC( d, RootWindow( d,screen ), 0, 0); 


	XEvent event;
	XSelectInput( d, w,ButtonPressMask | ExposureMask); 

	Atom atom1,atom2;
	atom1 = XInternAtom(d, "WM_PROTOCOLS", False);
	XSetWMProtocols(d, w, &atom2,1);

	XMapWindow( d, w );
	XFlush( d );


	while(1){
		XNextEvent( d, &event );
		switch(event.type){
			case ButtonPress:
                break;
			case Expose:
				paint(d,w,screen,gc);
				break;
			case ClientMessage:
    			break;
			default:
				break;
		}
	}
    return 0;
}
