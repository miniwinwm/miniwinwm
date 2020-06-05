#include <windows.h>
#include <stdbool.h>
#include "miniwin.h"
#include "camlib.h"
#include "gcc_camlib.h"

#define WINDOW_START_LOCATION_X		100
#define WINDOW_START_LOCATION_Y		100

HWND hwnd;
bool mouse_down = false;
SHORT mx;
SHORT my;

static gcc_camlib_t gcc_cam_lib;

static VOID MouseEventProc(LPARAM lp);
static LRESULT CALLBACK WindowProc(HWND window, UINT msg, WPARAM wp, LPARAM lp);

void camlib_init(void)
{
	gcc_cam_lib = gcc_camlib_init();
}

uint16_t *get_frame(void)
{
	return gcc_camlib_get_frame(gcc_cam_lib);
}

void capture(void)
{
	gcc_camlib_capture(gcc_cam_lib);
}

static VOID MouseEventProc(LPARAM lp)
{
    POINTS mouse_point;

    mouse_point = MAKEPOINTS(lp);
	mx = mouse_point.x;
	my = mouse_point.y;

	if (mx < 0)
	{
		mx = 0;
	}

	if (my < 0)
	{
		my = 0;
	}

	if (mx > MW_ROOT_WIDTH - 1)
	{
		mx = MW_ROOT_WIDTH - 1;
	}

	if (my > MW_ROOT_HEIGHT - 1)
	{
		my = MW_ROOT_HEIGHT - 1;
	}
}

static LRESULT CALLBACK WindowProc(HWND window, UINT msg, WPARAM wp, LPARAM lp)
{
    switch(msg)
    {
	case WM_CREATE:
		camlib_init();
		break;

	case WM_DESTROY:
		gcc_camlib_destroy(gcc_cam_lib);
		PostQuitMessage(0);
		exit(0);

	case WM_LBUTTONDOWN:
		mouse_down = true;
		MouseEventProc(lp);
		break;

	case WM_MOUSEMOVE:
		MouseEventProc(lp);
		break;

	case WM_LBUTTONUP:
		mouse_down = false;
		break;

	case WM_SETFOCUS:
		mw_paint_all();
		break;

    default:
        return DefWindowProc(window, msg, wp, lp);
    }

    return 0;
}

void app_init(void)
{
    const char* const miniwin_class = "miniwin_class";
    WNDCLASSEX wndclass = {sizeof(WNDCLASSEX), CS_DBLCLKS, WindowProc,
                            0, 0, GetModuleHandle(0), LoadIcon(0,IDI_APPLICATION),
                            LoadCursor(0,IDC_ARROW), (HBRUSH)COLOR_WINDOW+1,
                            0, miniwin_class, LoadIcon(0,IDI_APPLICATION)};
    RegisterClassEx(&wndclass);

    RECT r = {WINDOW_START_LOCATION_X,
    		WINDOW_START_LOCATION_Y,
			WINDOW_START_LOCATION_X + MW_ROOT_WIDTH,
			WINDOW_START_LOCATION_Y + MW_ROOT_HEIGHT};
   AdjustWindowRectEx(&r, WS_OVERLAPPEDWINDOW, FALSE, 0);

	hwnd = CreateWindow(miniwin_class, "MiniWin Sim",
			   WS_OVERLAPPEDWINDOW | WS_CAPTION, r.left, r.top,
			   r.right - r.left, r.bottom - r.top, 0, 0, GetModuleHandle(0), 0);

	ShowWindow(hwnd, SW_SHOWDEFAULT);
}

void app_main_loop_process(void)
{
    MSG msg;

    while(PeekMessageA(&msg, hwnd, 0, 0, PM_NOREMOVE))
    {
		GetMessage(&msg, 0, 0, 0);
		DispatchMessage(&msg);
    }
}
