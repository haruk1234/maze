#include <windows.h>
#include <iostream>
#include <chrono>
#include "3d.h"
#include "../../maze.h"

tdDraw tddraw;
tdDrawObject showobject;
std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
std::chrono::system_clock::time_point end = std::chrono::system_clock::now();



void move(double);
std::array<double,2> rotate2d(std::array<double,2>,double);
void paintscreen(HWND);
tdDrawObject getmaze3d();

std::vector<std::vector<unsigned char>> flmove;

struct MazeOption {
    bool wall = true;
};

MazeOption option;
tdDrawPolygon arraytopoly(std::array<int,12> a) {
    return {
		{(double)a[0],(double)a[1],(double)a[2]},
		{(double)a[3],(double)a[4],(double)a[5]},
		{(double)a[6],(double)a[7],(double)a[8]},
		{(unsigned char)a[9],(unsigned char)a[10],(unsigned char)a[11]}
		};
}

LRESULT CALLBACK WndProc(HWND hwnd , UINT msg , WPARAM wp , LPARAM lp) {
	TCHAR tcStr[128];

	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	// case WM_KEYDOWN:
	// 	//std::cout << "\033[2K\033[1G" << "keydown " << wp << std::endl;
	// 	bool a;
	// 	switch (wp)
	// 	{
	// 		case 87:
	// 			move(0.1);
	// 		break;
	// 		case 83:
	// 			move(-0.1);
	// 		break;
	// 		case 68:
	// 			tddraw.camangle[0]+=0.1;
	// 		break;
	// 		case 65:
	// 			tddraw.camangle[0]-=0.1;
	// 		break;
	// 		default:
	// 		break;
	// 	}
	// 	return 0;
	case WM_CREATE:
   		std::cout << "Neknaj 3D Maze Desktop" << std::endl;
		showobject = getmaze3d();
		tddraw.setObj(showobject);
		tddraw.setCamera({1.5,1.5,0.7},{45*(pi/180),0*(pi/180)});
		return 0;
	case WM_PAINT:
		paintscreen(hwnd);
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





std::array<double,2> rotate2d(std::array<double,2> pos,double r) {
	double cosr = std::cos(r);
	double sinr = std::sin(r);
	double x = pos[0]*cosr-pos[1]*sinr;
    double y = pos[0]*sinr+pos[1]*cosr;
	return {x,y};
}
tdDrawObject getmaze3d() {
	Maze maze(15,15);
	flmove = maze.maze;
	tdDrawObject m3d = {};
	int x = maze.size[0];int y = maze.size[1];
	for (int ly=0;ly<y;ly++) {
		for (int lx=0;lx<x;lx++) {
			if (maze.maze[ly][lx]==0) {
				if (option.wall) {
					m3d.insert(m3d.end(),arraytopoly({lx,ly,1,lx+1,ly,1,lx+1,ly+1,1,255,255,255}));
					m3d.insert(m3d.end(),arraytopoly({lx,ly+1,1,lx,ly,1,lx+1,ly+1,1,255,255,255}));
					if (!(lx>0&&maze.maze[ly][lx-1]==0)) {
						m3d.insert(m3d.end(),arraytopoly({lx,ly,0,lx,ly,1,lx,ly+1,0,255,255,255}));
						m3d.insert(m3d.end(),arraytopoly({lx,ly,1,lx,ly+1,1,lx,ly+1,0,255,255,255}));
					}
					if (!(ly<y-1&&maze.maze[ly+1][lx]==0)) {
						m3d.insert(m3d.end(),arraytopoly({lx,ly+1,0,lx,ly+1,1,lx+1,ly+1,1,255,255,255}));
						m3d.insert(m3d.end(),arraytopoly({lx+1,ly+1,0,lx,ly+1,0,lx+1,ly+1,1,255,255,255}));
					}
                    if (!(lx<x-1&&maze.maze[ly][lx+1]==0)) {
						m3d.insert(m3d.end(),arraytopoly({lx+1,ly+1,0,lx+1,ly,1,lx+1,ly+1,1,255,255,255}));
						m3d.insert(m3d.end(),arraytopoly({lx+1,ly,0,lx+1,ly,1,lx+1,ly+1,0,255,255,255}));
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
void paintscreen(HWND hwnd) {
	{
		if (GetKeyState(0x57)<0) {
    		//std::cout << std::endl << "w" << std::endl;
			move(0.05);
		}
		if (GetKeyState(0x41)<0) {
    		//std::cout << std::endl << "a" << std::endl;
			tddraw.camangle[0]-=0.05;
		}
		if (GetKeyState(0x53)<0) {
    		//std::cout << std::endl << "s" << std::endl;
			move(-0.05);
		}
		if (GetKeyState(0x44)<0) {
    		//std::cout << std::endl << "d" << std::endl;
			tddraw.camangle[0]+=0.05;
		}
	}
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;
	static BITMAPINFO bmpInfo;
	GetClientRect(hwnd, &rect);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;
	bmpInfo.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
	bmpInfo.bmiHeader.biWidth=width;
	bmpInfo.bmiHeader.biHeight=height;
	bmpInfo.bmiHeader.biPlanes=1;
	bmpInfo.bmiHeader.biBitCount=32;
	bmpInfo.bmiHeader.biCompression=BI_RGB;
	unsigned char* lpPixel = new unsigned char [width*height*4];
	tddraw.getImg(lpPixel,width,height);
    hdc=BeginPaint(hwnd,&ps);
	{ // 3d
		// {
		// 	end = std::chrono::system_clock::now();
		// 	int msec = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		// 	std::cout << "\033[2K\033[1G" << "f" << tddraw.frame << " ms" << msec << " fps" << (double)1000/msec;
		// 	start = std::chrono::system_clock::now();
		// }
		SetDIBitsToDevice(hdc,0,0,width,height,0,0,0,height,lpPixel,&bmpInfo,DIB_RGB_COLORS);
	}
	delete[] lpPixel;
    InvalidateRect(hwnd,NULL,FALSE);
	return;
}
void move(double length) {
	std::array<double,2> los = rotate2d({0,length},-tddraw.camangle[0]);
	double bfx = tddraw.campos[0];
	double bfy = tddraw.campos[1];
	tddraw.campos[0] += los[0];
	tddraw.campos[1] += los[1];
	double cx = tddraw.campos[0];
	double cy = tddraw.campos[1];
	if (cy<flmove.size()&&bfx<flmove[0].size()&&flmove[std::floor(cy)][std::floor(bfx)]==0) {
		tddraw.campos[1] = bfy;
	}
	if (bfy<flmove.size()&&cx<flmove[0].size()&&flmove[std::floor(bfy)][std::floor(cx)]==0) {
		tddraw.campos[0] = bfx;
	}
	// if (std::floor(tddraw.campos[0])==maze.goal[0]&&std::floor(tddraw.campos[1])==maze.goal[1]) {
	// 	//startgoal();
	// }
}