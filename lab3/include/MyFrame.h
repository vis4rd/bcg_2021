#pragma once

#include <wx/wxprec.h>
#include <wx/colordlg.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <iostream>

enum
{
	ID_WXBUTTON1 = 		(1<<3)|1,
	ID_WXCHECKBOX1 = 	(1<<3)|2,
	ID_WXSCROLLBAR1 = 	(1<<3)|3,
	ID_WXGAUGE1 = 		(1<<3)|4,
	ID_WXBUTTON2 =		(1<<3)|5,
	ID_WXTEXTCTRL1 =	(1<<3)|6,
	ID_WXCHOICE1 =		(1<<3)|7,
	ID_WXPANEL1 =		(1<<3)|8
};

class MyFrame : public wxFrame
{
public:
    MyFrame();

private:
	bool drawBanana;
	wxColor starColor;

	wxButton *WxButton1;
	void WxButton1_Click(wxCommandEvent &event);

	wxCheckBox *WxCheckBox1;
	void WxCheckBox1_Click(wxCommandEvent &event);

	wxScrollBar *WxScrollBar1;
	void WxScrollBar1_Scroll(wxScrollEvent &event);

	wxGauge *WxGauge1;

	wxButton *WxButton2;
	void WxButton2_Click(wxCommandEvent &event);

	wxTextCtrl *WxTextCtrl1;
	wxString text1;
	void WxTextCtrl1_Updated(wxCommandEvent &event);

	wxChoice *WxChoice1;
	void WxChoice1_Chosen(wxCommandEvent &event);

	wxPanel *WxPanel1;
	void WxPanel1_Draw();
	void OnUpdateUI(wxCommandEvent &event);

	int bananaPos;

	wxImage MyImage;
	wxBitmap MyBitmap;
};