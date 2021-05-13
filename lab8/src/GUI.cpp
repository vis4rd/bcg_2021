#include "GUI.h"

GUI::GUI()
: 
MyFrame::MyFrame(nullptr)
{
	m_panel1->SetBackgroundColour(wxColor(*wxBLACK));
	wxImage::AddHandler(new wxJPEGHandler);
}

void GUI::LoadImageOnButtonClick(wxCommandEvent& event)
{
	wxImage::AddHandler(new wxJPEGHandler);
	wxFileDialog *loadDialog = new wxFileDialog(this, _("Choose a file"), _(""), _(""), _("JPEG files (.jpg)| *.jpg"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if(loadDialog->ShowModal() == wxID_OK)
	{
		FIBITMAP *dib = FreeImage_Load(FIF_JPEG, loadDialog->GetPath(), JPEG_DEFAULT);
		wxString metadata = "";
		metadata << "Rozmiar obrazka: " << FreeImage_GetWidth(dib)
				<< "*" << FreeImage_GetHeight(dib) << "\r\n" 
				<< "EXIF INFO: \r\n";
		
		if(FreeImage_GetMetadataCount(FIMD_EXIF_MAIN, dib))//jesli liczba informacji > 0
		{
			FITAG *tag = NULL;
			FIMETADATA *mdhandle = FreeImage_FindFirstMetadata(FIMD_EXIF_MAIN, dib, &tag);//uzyskanie listy metadat
			if(mdhandle)
			{
				do
				{//wypisywanie
					metadata << FreeImage_GetTagKey(tag) << ": " << FreeImage_TagToString(FIMD_EXIF_MAIN, tag) << "\r\n";
				}while (FreeImage_FindNextMetadata(mdhandle, &tag));
			}
			FreeImage_FindCloseMetadata(mdhandle);
		}
		FreeImage_Unload(dib);

		this->imgOrg.LoadFile(loadDialog->GetPath(), wxBITMAP_TYPE_JPEG);
		this->imgCopy = this->imgOrg.Copy();
		m_textCtrl1->Clear();
		m_textCtrl1->AppendText(metadata);
	}
}

void GUI::CensorshipOnButtonClick(wxCommandEvent& event)
{
	if(this->imgOrg.Ok())
	{
		this->imgCopy = this->imgOrg.Copy();

		const int height = 0.15 * this->imgCopy.GetHeight();
		const int width = 0.15 * this->imgCopy.GetWidth();
		const int x_0 = 0.57 * this->imgCopy.GetWidth();
		const int y_0 = 0.02 * this->imgCopy.GetHeight();

		cimg_library::CImg<unsigned char> cImage(width, height, 1, 3);
		for(int i = 0; i < width; i++)
		{
			for(int j = 0; j < height; j++)
			{
				cImage(i, j, 0) = this->imgCopy.GetRed(x_0 + i, y_0 + j);
				cImage(i, j, 1) = this->imgCopy.GetGreen(x_0 + i, y_0 + j);
				cImage(i, j, 2) = this->imgCopy.GetBlue(x_0 + i, y_0 + j);
			}
		}
		cImage.blur(3);
		for(int i = 0; i < width; i++) 
			for(int j = 0; j < height; j++) 
				this->imgCopy.SetRGB(x_0 + i, y_0 + j, cImage(i, j, 0), cImage(i, j, 1), cImage(i, j, 2));
	}
}

void GUI::ErodeOnButtonClick(wxCommandEvent& event)
{
	if(this->imgOrg.Ok())
	{
		this->imgCopy = this->imgOrg.Copy();
		auto height = this->imgCopy.GetHeight();
		auto width = this->imgCopy.GetWidth();

		cimg_library::CImg<unsigned char> cImage(width, height, 1, 3);
		for(int i = 0; i < width; i++)
		{
			for(int j = 0; j < height; j++)
			{
				cImage(i, j, 0) = this->imgCopy.GetRed(i, j);
				cImage(i, j, 1) = this->imgCopy.GetGreen(i, j);
				cImage(i, j, 2) = this->imgCopy.GetBlue(i, j);
			}
		}

		cImage.erode(6);
		for(int i = 0; i < width; i++)
			for(int j = 0; j < height; j++)
				this->imgCopy.SetRGB(i, j, cImage(i, j, 0), cImage(i, j, 1), cImage(i, j, 2));

	}
}

void GUI::AnimationOnCheckBox(wxCommandEvent& event)
{
	if(this->imgOrg.IsOk() && Animation->IsChecked())
	{
		const int height = this->imgOrg.GetSize().y;
		const int width = this->imgOrg.GetSize().x;

		cimg_library::CImg<float> copy(width, height, 1, 3);
		for(int i = 0; i < width; i++)//przejscie z wxWidgets na CImg
		{
			for(int j = 0; j < height; j++)
			{
				copy(i, j, 0) = this->imgOrg.GetRed(i, j);
				copy(i, j, 1) = this->imgOrg.GetGreen(i, j);
				copy(i, j, 2) = this->imgOrg.GetBlue(i, j);
			}
		}
		float spec[3] = { 1.0f, 1.0f, 1.0f };

		cimg_library::CImg<float> gauss;
		cimg_library::CImg<float> gauss2;
		cimg_library::CImg<float> tmp;
		float* CImgData;
		unsigned char newData[width * height * 3];
		for(int i = 59; i >= 0; i--)
		{
			gauss = cimg_library::CImg<float>(width, height, 1, 3);
			gauss2 = cimg_library::CImg<float>(width, height, 1, 3);
			tmp = copy;
			CImgData = tmp.data();

			gauss.draw_gaussian(
				(width / 2) + (width * 0.4) * cos(i * M_PI / 60.f),
				(height / 2) + (height * 0.4) * sin(i * M_PI / 60.f),
				120.0f,
				spec,
				1.0f);
			gauss2.draw_gaussian(
				(width / 2) + (width * 0.4) * cos((i + 60.f) * M_PI / 60.f),
				(height / 2) + (height * 0.4) * sin((i + 60.f) * M_PI / 60.f),
				120.0f,
				spec,
				1.0f);
			gauss += gauss2;
			tmp.mul(gauss);

			for(int y = 0; y < height; y++)
			{
				for(int x = 0; x < width; x++)
				{
					int wyx = (width * y) + x;
					newData[3 * wyx] = CImgData[wyx];
					newData[3 * wyx + 1] = CImgData[width * height + wyx];
					newData[3 * wyx + 2] = CImgData[width * height * 2 + wyx];
				}
			}
			wxImage animationFrame(width, height, newData, true);
			this->animationFrames[i] = wxBitmap(animationFrame);
		}
	}
}

void GUI::refresh(wxClientDC &dc)
{
	static unsigned frame_index;
	static unsigned tick_delay;
  	wxBufferedDC buffDC(&dc);
	if(this->imgOrg.Ok())
	{
		if(Animation->IsChecked() && this->animationFrames.size() > 0)
		{
			buffDC.DrawBitmap(this->animationFrames[frame_index], 0, 0);
			tick_delay = (tick_delay + 1) % 8;
			if(tick_delay >= 7)
				frame_index = (frame_index + 1) % 60;
			Update();
			RefreshRect(wxRect(1, 1, 1, 1), false);
		}
		else
		{
			this->imgCopy.Rescale(dc.GetSize().x, dc.GetSize().y);
			wxBitmap bitmap(this->imgCopy);
			buffDC.DrawBitmap(bitmap, 0, 0);
		}
	}
}

void GUI::MyFrameOnUpdateUI(wxUpdateUIEvent& event)
{
	wxClientDC dc(m_panel1);
	refresh(dc);
}