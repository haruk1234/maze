#include <windows.h>
#include <iostream>
#include "3d.h"
#include "../maze.h"

tdDraw tddraw;
tdDrawObject showobject;


struct MazeOption {
    bool wall = true;
};

Maze maze(150,150);
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

LRESULT CALLBACK WndProc(HWND hwnd , UINT msg , WPARAM wp , LPARAM lp) {
	HDC hdc;
	PAINTSTRUCT ps;

	RECT rect;
	
	static unsigned char* lpPixel;
	static BITMAPINFO bmpInfo;

	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_CREATE:
   		std::cout << "Neknaj 3D Maze Desktop" << std::endl;
		showobject = getmaze3d();
		tddraw.setObj(showobject);
		tddraw.setCamera({-5,-5,2},{45*(pi/180),0*(pi/180)});
		return 0;
	case WM_PAINT:
		GetClientRect(hwnd, &rect);
		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;
		// std::cout << width << " " << height << std::endl; // output window size

		bmpInfo.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
		bmpInfo.bmiHeader.biWidth=width;
		bmpInfo.bmiHeader.biHeight=height;
		bmpInfo.bmiHeader.biPlanes=1;
		bmpInfo.bmiHeader.biBitCount=32;
		bmpInfo.bmiHeader.biCompression=BI_RGB;
		hdc=BeginPaint(hwnd,&ps);
		{ // 3d
			lpPixel = tddraw.getImg(width,height);
			SetDIBitsToDevice(hdc,0,0,width,height,0,0,0,height,lpPixel,&bmpInfo,DIB_RGB_COLORS);
		}
		EndPaint(hwnd,&ps);
		delete[] lpPixel;
		return 0;
	}
	return DefWindowProc(hwnd,msg,wp,lp);
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,PSTR lpCmdLine,int nCmdShow) {
	HWND hwnd;
	MSG msg;
	WNDCLASS winc;

	winc.style = CS_HREDRAW | CS_VREDRAW;
	winc.lpfnWndProc = WndProc;
	winc.cbClsExtra	= winc.cbWndExtra	= 0;
	winc.hInstance = hInstance;
	winc.hIcon = LoadIcon(NULL , IDI_APPLICATION);
	winc.hCursor = LoadCursor(NULL , IDC_ARROW);
	winc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	winc.lpszMenuName = NULL;
	winc.lpszClassName = TEXT("app");

	if (!RegisterClass(&winc)) return -1;

	hwnd = CreateWindow(
		TEXT("app") , TEXT("Neknaj 3D Maze") ,
		WS_OVERLAPPEDWINDOW | WS_VISIBLE ,
		CW_USEDEFAULT , CW_USEDEFAULT ,
		500 , 400 , // window size
		NULL , NULL , hInstance , NULL
	);

	if (hwnd == NULL) return -1;

	while(GetMessage(&msg,NULL,0,0)) {DispatchMessage(&msg);}
	return msg.wParam;
}