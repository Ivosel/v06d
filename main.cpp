#include "main.h"
#include <cmath>
#include "rc.h"

int number_dialog::idd() const {
	return IDD_NUMBER;
}
bool number_dialog::on_init_dialog() {
	return true;
}
bool number_dialog::on_ok() {
	return true;
}

void main_window::on_paint(HDC hdc) {
}

void main_window::on_command(int id){
	switch(id){
		case ID_COLOR: 
			break;
		case ID_NUMBER: 
			break;
		case ID_EXIT: 
			DestroyWindow(*this); 
			break;
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
