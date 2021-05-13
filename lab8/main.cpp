#include <wx/wx.h>
#include <memory>

#include "GUI.h"

class MyApp : public wxApp
{
public:
	bool OnInit() override
	{
		wxFrame *mainFrame = new GUI();
		mainFrame->Show(true);
		SetTopWindow(mainFrame);
		return true;
	}
	int OnExit() override
	{
		return 0;
	}
};

IMPLEMENT_APP(MyApp)