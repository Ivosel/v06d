#pragma once
#include <string>

typedef std::basic_string<TCHAR> tstring;
#ifdef UNICODE
#define to_tstring to_wstring
#else
#define to_tstring to_string
#endif

namespace vsite::nwp {

class dialog
{
	HWND hw;
public:
	static int CALLBACK proc(HWND hw, UINT msg, WPARAM wp, LPARAM lp);
	operator HWND() const { return hw; }
	int do_modal(HINSTANCE, HWND parent = 0);
protected:
//	operations
	void set_int(int id_ctrl, int val);
	int get_int(int id_ctrl); // throws std::runtime_error
	void set_text(int idCtrl, const tstring& val);
	tstring get_text(int idCtrl);
	void set_real(int idCtrl, double val); // throws std::runtime_error
	double get_real(int idCtrl);

//	overridables
	virtual int idd() const = 0;
	virtual bool on_init_dialog() { return false; }
	virtual bool on_command(int id, int code) { return false; }
	virtual bool on_ok() { return true; }
	virtual void on_cancel() { }
};

} // namespace
