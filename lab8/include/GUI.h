#pragma once

#include "MyFrame.h"

#include <array>
#include <string>
#include <cmath>

#include <wx/dcbuffer.h>
#include <wx/window.h>
#include <wx/filedlg.h>

#include "../include/FreeImage.h"
#include "../include/CImg.h"

class GUI : public MyFrame
{
public:
	GUI();
	void refresh(wxClientDC &dc);

private:
	void LoadImageOnButtonClick(wxCommandEvent& event) override;
	void CensorshipOnButtonClick(wxCommandEvent& event) override;
	void ErodeOnButtonClick(wxCommandEvent& event) override;
	void AnimationOnCheckBox(wxCommandEvent& event) override;
	void MyFrameOnUpdateUI(wxUpdateUIEvent& event) override;

	wxImage imgCopy;
	wxImage imgOrg;
	std::array<wxBitmap, 60> animationFrames;
};