#include <windows.h>
#include <tchar.h>
#include "nwpdlg.h"
#include <map>
#include <stdexcept>

namespace vsite::nwp {

int CALLBACK dialog::proc(HWND hw, UINT msg, WPARAM wp, LPARAM lp)
{
	static std::map<HWND, dialog*> wmap;
	if(msg == WM_INITDIALOG)
	{
		dialog* pd = reinterpret_cast<dialog*>(lp);
		pd->hw = hw;
		wmap[hw] = pd; 
		return pd->on_init_dialog();
	}
	dialog* pd = wmap[hw];
	if(msg == WM_COMMAND)
	{
		if(LOWORD(wp) == IDOK && pd->on_ok())
			return ::EndDialog(hw, IDOK);
		if(LOWORD(wp) == IDCANCEL)
		{
			pd->on_cancel();
			return ::EndDialog(hw, IDCANCEL);
		}
		return pd->on_command(LOWORD(wp), HIWORD(wp));
	}
	if(msg == WM_DESTROY)
		wmap.erase(hw);
	return 0;
}

int dialog::do_modal(HINSTANCE hInst, HWND parent)
{
	return ::DialogBoxParam(hInst, MAKEINTRESOURCE(idd()), parent, proc, 
		reinterpret_cast<LPARAM>(this));
}

void dialog::set_int(int idCtrl, int val)
{
	::SetDlgItemInt(*this, idCtrl, val, true);
}

int dialog::get_int(int idCtrl)
{
	BOOL b;
	int n = ::GetDlgItemInt(*this, idCtrl, &b, true);
	if(!b) throw std::runtime_error("not a number");
	return n;
}

void dialog::set_text(int idCtrl, const tstring& s){
	::SetDlgItemText(*this, idCtrl, s.c_str());
}

tstring dialog::get_text(int idCtrl){
    TCHAR s[512];
	::GetDlgItemText(*this, idCtrl, s, 512);
	return tstring(s);
}

void dialog::set_real(int idCtrl, double d){
	::SetDlgItemText(*this, idCtrl, std::to_tstring(d).c_str());
}

double dialog::get_real(int idCtrl){
	TCHAR s[16], *c;
	::GetDlgItemText(*this, idCtrl, s, 16);
	double n = _tcstod(s, &c);
	if(c == s) throw std::runtime_error("not a number");
	return n;
}

} // namespace
