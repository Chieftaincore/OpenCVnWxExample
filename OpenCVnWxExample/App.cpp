#include "App.h"
#include "wxgui/MainFrame.h"
#include <wx/wx.h>

wxIMPLEMENT_APP(App);

bool App::OnInit() {
	MainFrame* mainframe = new MainFrame("Ana Çerçeve");

	return true;
}

