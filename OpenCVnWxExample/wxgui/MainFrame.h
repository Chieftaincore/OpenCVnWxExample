#pragma once
#include <wx/wx.h>

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);
private:
	void OnButtonClicked(wxCommandEvent& evt);
	void OnHaarFrontButtonClicked(wxCommandEvent& evt);
	void OnHaarProfileButtonClicked(wxCommandEvent& evt);
	void OnHaarUpperBodyButtonClicked(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

