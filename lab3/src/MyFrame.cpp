#include "MyFrame.h"

MyFrame::MyFrame()
	:
	wxFrame(NULL, wxID_ANY, "GFK Lab03")
{
	SetIcon(wxNullIcon);
	SetSize(0, 0, 900, 500);
	this->SetAutoLayout(true);

	this->drawBanana = false;

	wxBoxSizer *WxBoxSizerMain = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *WxBoxSizerLeft = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *WxBoxSizerRight = new wxBoxSizer(wxVERTICAL);

	WxButton1 = new wxButton(	this, 
								ID_WXBUTTON1,
								_("Zapis do pliku"),
								wxPoint(30, 10),
								wxSize(100, 30),
								0,
								wxDefaultValidator,
								_("WxButton1"));

	WxCheckBox1 = new wxCheckBox(	this,
									ID_WXCHECKBOX1,
									_("Banan!"),
									wxPoint(30, 65),
									wxSize(105, 19),
									0,
									wxDefaultValidator,
									_("WxCheckBox1"));

	WxScrollBar1 = new wxScrollBar(	this,
									ID_WXSCROLLBAR1,
									wxPoint(30, 100),
									wxSize(149, 20),
									wxSB_HORIZONTAL,
									wxDefaultValidator,
									_("WxScrollBar1"));
 	WxScrollBar1->SetScrollbar(0, 20, 149, 19);
 	WxScrollBar1->Enable(false);

 	WxGauge1 = new wxGauge(	this,
 							ID_WXGAUGE1,
 							170,
 							wxPoint(30, 130),
 							wxSize(149, 20),
 							wxGA_SMOOTH,
 							wxDefaultValidator,
 							_("WxGauge1"));

 	WxButton2 = new wxButton(	this, 
								ID_WXBUTTON2,
								_("Kolor"),
								wxPoint(30, 160),
								wxSize(100, 30),
								0,
								wxDefaultValidator,
								_("WxButton2"));

 	WxTextCtrl1 = new wxTextCtrl(	this,
	 								ID_WXTEXTCTRL1,
	 								_("Tekst"),
	 								wxPoint(30, 200),
	 								wxSize(131, 20),
	 								0,
	 								wxDefaultValidator,
	 								_("WxTextCtrl1"));
 	this->text1 = _("Tekst");

 	wxString array[] = { _("Slonce"), _("Ksiezyc"), _("Gwiazdka") };
 	WxChoice1 = new wxChoice(	this,
 								ID_WXCHOICE1,
 								wxPoint(30, 230),
 								wxSize(131, 20),
 								wxArrayString(3, array),
 								0,
 								wxDefaultValidator,
 								_("WxChoice1"));
 	WxChoice1->SetSelection(2);

 	WxPanel1 = new wxPanel(	this,
 							ID_WXPANEL1,
 							wxPoint(0, 0),
 							wxSize(300, 300),
 							0,
 							_("WxPanel1"));

 	WxBoxSizerLeft->Add(WxPanel1, 1, wxEXPAND | wxALL, 5);
 	WxBoxSizerRight->Add(WxButton1, 0, wxALIGN_CENTER | wxALL, 5);
 	WxBoxSizerRight->Add(WxCheckBox1, 0, wxALIGN_CENTER | wxALL, 5);
 	WxBoxSizerRight->Add(WxScrollBar1, 1, wxALIGN_CENTER | wxALL, 5);
 	WxBoxSizerRight->Add(WxGauge1, 1, wxALIGN_CENTER | wxALL, 5);
 	WxBoxSizerRight->Add(WxButton2, 0, wxALIGN_CENTER | wxALL, 5);
 	WxBoxSizerRight->Add(WxTextCtrl1, 0, wxALIGN_CENTER | wxALL, 5);
 	WxBoxSizerRight->Add(WxChoice1, 0, wxALIGN_CENTER | wxALL, 5);
 	WxBoxSizerMain->Add(WxBoxSizerLeft, 1, wxEXPAND | wxALL, 5);
 	WxBoxSizerMain->Add(WxBoxSizerRight, 0, wxALL, 5);
	this->SetSizer(WxBoxSizerMain);
	WxBoxSizerMain->Fit(this);
	this->SetMinSize(this->GetSize());
	Center();
	WxPanel1_Draw();

	Bind(wxEVT_BUTTON, &MyFrame::WxButton1_Click, this, ID_WXBUTTON1);
	Bind(wxEVT_CHECKBOX, &MyFrame::WxCheckBox1_Click, this, ID_WXCHECKBOX1);
	Bind(wxEVT_SCROLL_THUMBTRACK, &MyFrame::WxScrollBar1_Scroll, this, ID_WXSCROLLBAR1);
	Bind(wxEVT_BUTTON, &MyFrame::WxButton2_Click, this, ID_WXBUTTON2);
	Bind(wxEVT_TEXT, &MyFrame::WxTextCtrl1_Updated, this, ID_WXTEXTCTRL1);
	Bind(wxEVT_CHOICE, &MyFrame::WxChoice1_Chosen, this, ID_WXCHOICE1);
	Bind(wxEVT_UPDATE_UI, &MyFrame::OnUpdateUI, this, ID_WXPANEL1);

	MyImage.AddHandler(new wxPNGHandler);
	MyImage.AddHandler(new wxJPEGHandler);
}

void MyFrame::WxButton1_Click(wxCommandEvent &event)
{
	wxClientDC MyDC(this->WxPanel1);
	wxImage::AddHandler(new wxJPEGHandler);

	wxString path;
	wxFileDialog WxOpenFileDialog1(this, _("Choose file"), _(""), _(""), _("*.png"), wxFD_SAVE);
	
	if(WxOpenFileDialog1.ShowModal() == wxID_OK) {
		// Refresh();
		
		path = WxOpenFileDialog1.GetPath();

		wxSize size = WxPanel1->GetVirtualSize();
		wxBitmap bitmapToSave(size);

		wxMemoryDC memory;
		memory.SelectObject(bitmapToSave);
		memory.Blit(0, 0, size.GetX(), size.GetY(), &MyDC, 0, 0, wxCOPY, true);

		wxImage imageToSave = bitmapToSave.ConvertToImage();
		imageToSave.SaveFile(path, wxBITMAP_TYPE_JPEG);
	}
	else
		wxLogError(_("Nie mozna zapisac obrazka"));
}

void MyFrame::WxCheckBox1_Click(wxCommandEvent &event)
{
	this->drawBanana = !this->drawBanana;
	if(this->drawBanana == true)
	{
		std::cout << "Banan: widoczny" << std::endl;
		if(!MyImage.IsOk())
		{
			if(!MyImage.LoadFile(_("banan.png"), wxBITMAP_TYPE_PNG))
			{
				//wxLogError(_("Nie mozna zaladowac obrazka"));
				wxFileDialog WxOpenFileDialog1(this, _("Choose banana"), _(""), _(""), _("*.png"), wxFD_OPEN);
				if(WxOpenFileDialog1.ShowModal() == wxID_OK)
					MyImage.LoadFile(WxOpenFileDialog1.GetPath(), wxBITMAP_TYPE_PNG);
			}
		}
		MyBitmap = wxBitmap(MyImage);
	}
	else
	{
		std::cout << "Banan: niewidzialny" << std::endl;
	}

	WxScrollBar1->Enable(this->drawBanana);
}

void MyFrame::WxScrollBar1_Scroll(wxScrollEvent &event)
{
	this->WxGauge1->SetValue(static_cast<int>(((double)this->WxScrollBar1->GetThumbPosition()/this->WxScrollBar1->GetRange())*200.0));
	this->bananaPos = event.GetPosition();
	this->WxPanel1_Draw();
}

void MyFrame::WxButton2_Click(wxCommandEvent &event)
{
	wxColourDialog colorPrompt(this);
	if (colorPrompt.ShowModal() == wxID_OK)
		this->starColor = colorPrompt.GetColourData().GetColour();
	//wxMessageDialog(NULL, "Wcisnieto przycisk", "Uwaga", wxOK).ShowModal();
}

void MyFrame::WxTextCtrl1_Updated(wxCommandEvent &event)
{
	if(this->text1 != WxTextCtrl1)
		this->text1 = WxTextCtrl1->GetLineText(0);
}

void MyFrame::WxChoice1_Chosen(wxCommandEvent &event)
{
	switch(WxChoice1->GetCurrentSelection())
	{
		case 0: std::cout << "Slonce" << std::endl;	break;
		case 1: std::cout << "Ksiezyc" << std::endl; break;
		case 2: std::cout << "Gwiazdka" << std::endl; break;
		default: break;
	}
}

void MyFrame::WxPanel1_Draw()
{
	WxPanel1->Refresh();
	WxPanel1->Update();
	wxClientDC MyDC(this->WxPanel1);
	wxPoint my_center = wxPoint(WxPanel1->GetSize().GetX()/2, WxPanel1->GetSize().GetY()/2);
	MyDC.SetDeviceOrigin(my_center.x, my_center.y);
	MyDC.SetPen(wxPen(wxColor(0,0,0), 1));
	MyDC.DrawCircle(wxPoint(0, -20), 20); //head
	MyDC.DrawLine(wxPoint(0, 0), wxPoint(0, 80)); //body
	MyDC.DrawLine(wxPoint(0, 80), wxPoint(40, 120)); //right leg
	MyDC.DrawLine(wxPoint(0, 80), wxPoint(-40, 120)); //left leg
	MyDC.DrawLine(wxPoint(0, 0), wxPoint(40, 40)); //right arm
	MyDC.DrawLine(wxPoint(0, 0), wxPoint(-40, 40 - this->bananaPos/2)); //left arm
	MyDC.DrawCircle(wxPoint(-8, -24), 3);
	MyDC.DrawCircle(wxPoint(8, -24), 3);
	if(this->drawBanana == true)
	{
		MyDC.DrawBitmap(MyBitmap, wxPoint(-60, 20 - this->bananaPos/2)); //banana
		MyDC.DrawEllipticArc(-13, -21, 26, 15, 180, 0); // :)
	}
	else
		MyDC.DrawEllipticArc(-13, -17, 26, 15, 0, 180); //:(

	MyDC.DrawText(this->text1, wxPoint(-100, 100));
	MyDC.SetFont(wxFont(40, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, _("Tahoma")));
	MyDC.DrawRotatedText(this->text1, wxPoint(40, 80), 70.0);

	wxPoint star[6] = {	wxPoint(-80, -70),
						wxPoint(-30, -70),
						wxPoint(-70, -30),
						wxPoint(-55, -90),
						wxPoint(-40, -30) };
	switch(WxChoice1->GetCurrentSelection())
	{
		case 0: MyDC.SetBrush(wxBrush(wxColor(255, 255, 0), wxBRUSHSTYLE_SOLID));
				MyDC.SetPen(wxPen(wxColor(255, 255 ,0), 1));
				MyDC.DrawCircle(wxPoint(-60, -60), 30); //sun
				break;
		case 1: MyDC.SetBrush(wxBrush(wxColor(200, 200, 200), wxBRUSHSTYLE_SOLID));
				MyDC.SetPen(wxPen(wxColor(200, 200, 200), 1));
				MyDC.DrawCircle(wxPoint(-60, -60), 30); //moon body
				MyDC.SetBrush(wxBrush(wxColor(240, 240, 240), wxBRUSHSTYLE_SOLID));
				MyDC.SetPen(wxPen(wxColor(240, 240, 240), 1));
				MyDC.DrawCircle(wxPoint(-90, -90), 50); //moon cut
				MyDC.SetBrush(wxBrush(wxColor(0, 0, 0), wxBRUSHSTYLE_SOLID));
				MyDC.SetPen(wxPen(wxColor(0, 0, 0), 1));
				MyDC.DrawCircle(wxPoint(-44, -60), 2); //moon eye
				MyDC.DrawLine(wxPoint(-60, -50), wxPoint(-52, -46)); //moon smile
				break;
		case 2: MyDC.SetBrush(wxBrush(this->starColor, wxBRUSHSTYLE_SOLID));
				MyDC.SetPen(wxPen(this->starColor, 1));
				MyDC.DrawPolygon(5, star, wxWINDING_RULE); //star
				break;
		default: break;
	}
	
}

void MyFrame::OnUpdateUI(wxCommandEvent &event)
{
	WxPanel1_Draw();
}
