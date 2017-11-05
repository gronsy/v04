#include "nwpwin.h"

class Static :public Window {
protected:
	std::string ClassName()override { return "Static"; }
};

class MainWindow : public Window
{
	Static shp;
	POINT cords;
protected:
	void OnLButtonDown(POINT p) {
		if (!shp)
			shp.Create(*this, WS_CHILD | WS_VISIBLE | SS_CENTER, "x", 0, p.x, p.y, 20, 20);

		cords = p;

		SetWindowPos(shp, 0, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	}
	void OnKeyUp(int vk) {
		if (!shp) {
			MessageBox(*this, "Ship isn't set", "Not set", MB_ICONWARNING);
			return;
		}

		SetWindowLong(shp, GWL_STYLE, WS_VISIBLE | SS_CENTER | WS_CHILD);
		SetWindowPos(shp, 0, cords.x, cords.y, 20, 20, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER);
	}
	void OnKeyDown(int vk) {
		if (!shp) {
			MessageBox(*this, "Ship isn't set", "Not set", MB_ICONWARNING);
			return;
		}

		RECT wnd;
		GetClientRect(*this, &wnd);
		int mov = GetAsyncKeyState(VK_CONTROL) ? 20 : 1;;

		switch (vk) {
		case VK_LEFT:
			if (!cords.x)
				break;
			else if (cords.x < 20)
				mov = cords.x;

			cords.x -= mov;
			break;
		case VK_RIGHT: {
			int dif = wnd.right-cords.x-20;
			if (!dif)
				break;
			else if (dif<20&&mov==20)
				mov = dif;
			
			cords.x += mov;
			break;
		}
		case VK_DOWN: {
			int dif = wnd.bottom - cords.y-20;
			if (!dif)
				break;
			else if (dif < 20 && mov == 20)
				mov = dif;

			cords.y += mov;
			break;
		}
		case VK_UP:
			if (!cords.y)
				break;
			else if (cords.y < 20)
				mov = cords.y;

			cords.y -= mov;
			break;
		}

		SetWindowLong(shp, GWL_STYLE, WS_BORDER | WS_VISIBLE | SS_CENTER | WS_CHILD);
		SetWindowPos(shp, 0, cords.x, cords.y, 20, 20, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER);
	}
	void OnDestroy() {
		::PostQuitMessage(0);
	}
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.Run();
}