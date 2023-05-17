#include "main.h"
#include <cmath>
#include "rc.h"

COLORREF get_color(HWND parent, COLORREF cur) {
	COLORREF custom_colors[16]{ 0 };
	CHOOSECOLOR cc{ sizeof CHOOSECOLOR };
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;
	cc.hwndOwner = parent;
	cc.lpCustColors = custom_colors;
	cc.rgbResult = cur;
	if (::ChooseColor(&cc))
		cur = cc.rgbResult;
	return cur;
}

int number_dialog::idd() const {
	return IDD_NUMBER;
}
bool number_dialog::on_init_dialog() {
	set_int(IDC_EDIT1, num);
	return true;
}
bool number_dialog::on_ok() {
	try {
		num = get_int(IDC_EDIT1);
	}
	catch (std::exception) {
		return false;
	}
	return true;
}


void main_window::on_command(int id){
	switch(id){
		case ID_COLOR:
			color = get_color(*this, color);
			break;

		case ID_NUMBER: {
			number_dialog nd;
			nd.num = number;
			if (nd.do_modal(::GetModuleHandle(NULL), *this) == IDOK) {
			number = nd.num;
			}
		}
			break;

		case ID_EXIT: 
			DestroyWindow(*this); 
			break;
	}
	::InvalidateRect(*this, 0, true);
}

void main_window::on_paint(HDC hdc) {
	RECT rc; ::GetClientRect(*this, &rc);
	draw_circles(hdc, rc);
	
}

void main_window::draw_circles(HDC hdc, RECT rc) {
	pen p(color, 1, PS_NULL);
	sel_obj sp(hdc, p);
	brush b(color);
	sel_obj sb(hdc, b);
	SetROP2(hdc, R2_NOTXORPEN);
	int centerX = rc.right / 2;
	int centerY = rc.bottom / 2;
	int circleRadius = rc.bottom / 4;

	double angleStep = 360. / number ;
	for (int i = 0; i < number; i++) {
		int x = centerX + circleRadius * cos(i * angleStep * 3.14159265 / 180);
		int y = centerY - circleRadius * sin(i * angleStep * 3.14159265 / 180);
		Ellipse(hdc, x - circleRadius, y - circleRadius, x + circleRadius, y + circleRadius);
	}
}

void main_window::on_destroy(){
	::PostQuitMessage(0);
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	vsite::nwp::application app;
	main_window wnd;
	wnd.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, _T("NWP"), (int)LoadMenu(instance, MAKEINTRESOURCE(IDM_MAIN)));
	return app.run();
}
