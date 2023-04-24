#include "nwpwin.h"
#include "nwpdlg.h"

class number_dialog : public vsite::nwp::dialog {
protected:
	int idd() const override;
	bool on_init_dialog() override;
	bool on_ok() override;
public:
	int num;
};

class main_window : public vsite::nwp::window {
	COLORREF color{RGB(0,0,0)};
	int number{9};
protected:
	void on_paint(HDC hdc) override;
	void on_command(int id) override;
	void on_destroy() override;
	void draw_circles(HDC hdc, RECT rc);
};

class pen {
	HPEN h;
public:
	pen(COLORREF color, int width = 1, int style = PS_SOLID) :
		h(::CreatePen(style, width, color)) {}
	~pen() { ::DeleteObject(h); }
	operator HPEN() { return h; }
};

class brush {
	HBRUSH h;
public:
	brush(COLORREF color, int hatch = -1) :
		h(hatch >= 0 ? CreateHatchBrush(hatch, color) : ::CreateSolidBrush(color)) {}
	~brush() { ::DeleteObject(h); }
	operator HBRUSH() { return h; }
};

class sel_obj {
	HDC hdc;
	HGDIOBJ hOld;
public:
	sel_obj(HDC hdc, HGDIOBJ hObj) :
		hdc(hdc), hOld(::SelectObject(hdc, hObj)) { }
	~sel_obj() { ::SelectObject(hdc, hOld); }
};
