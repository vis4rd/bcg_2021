#include "GUIMyFrame1.h"

GUIMyFrame1::GUIMyFrame1( wxWindow* parent )
:
MyFrame1( parent )
{
 m_staticText1->SetLabel(_(L"Jasno\u015B\u0107"));
 m_b_threshold->SetLabel(_(L"Pr\u00F3g 128"));
 this->SetBackgroundColour(wxColor(192, 192, 192));
 m_scrolledWindow->SetScrollbars(25, 25, 52, 40);
 m_scrolledWindow->SetBackgroundColour(wxColor(192, 192, 192));
}

void GUIMyFrame1::m_scrolledWindow_update( wxUpdateUIEvent& event )
{
 Repaint();
}

void GUIMyFrame1::m_b_grayscale_click( wxCommandEvent& event )
{
 this->Img_Cpy = this->Img_Org.Copy().ConvertToGreyscale();
 this->Refresh();
}

void GUIMyFrame1::m_b_blur_click( wxCommandEvent& event )
{
 this->Img_Cpy = this->Img_Org.Copy().Blur(5);
 this->Refresh();
}

void GUIMyFrame1::m_b_mirror_click( wxCommandEvent& event )
{
 this->Img_Cpy = this->Img_Org.Copy().Mirror();
 this->Refresh();
}

void GUIMyFrame1::m_b_replace_click( wxCommandEvent& event )
{
 this->Img_Cpy = this->Img_Org.Copy();
 this->Img_Cpy.Replace(254, 0, 0, 0, 0, 255);
 this->Refresh();
}

void GUIMyFrame1::m_b_rescale_click( wxCommandEvent& event )
{
 this->Img_Cpy = this->Img_Org.Copy().Rescale(320, 240);
 this->Refresh();
}

void GUIMyFrame1::m_b_rotate_click( wxCommandEvent& event )
{
 this->Img_Cpy = this->Img_Org.Copy().Rotate(30.0 * M_PI / 180.0, wxPoint(this->Img_Org.GetWidth() / 2.0, this->Img_Org.GetHeight() / 2.0));
 this->Refresh();
}

void GUIMyFrame1::m_b_rotate_hue_click( wxCommandEvent& event )
{
 this->Img_Cpy = this->Img_Org.Copy();
 this->Img_Cpy.RotateHue(0.5);
 this->Refresh();
}

void GUIMyFrame1::m_b_mask_click( wxCommandEvent& event )
{
 this->Img_Cpy = this->Img_Org.Copy();
 this->Img_Cpy.SetMaskFromImage(this->Img_Mask, 0, 0, 0);
 this->Refresh();
}

void GUIMyFrame1::m_s_brightness_scroll( wxScrollEvent& event )
{
// Tutaj, w reakcji na zmiane polozenia suwaka, wywolywana jest funkcja
// Brightness(...), ktora zmienia jasnosc. W tym miejscu nic nie
// zmieniamy. Do uzupelnienia pozostaje funkcja Brightness(...)
Brightness(m_s_brightness->GetValue() - 100);
Repaint();
}

void GUIMyFrame1::m_s_contrast_scroll( wxScrollEvent& event )
{
// Tutaj, w reakcji na zmiane polozenia suwaka, wywolywana jest funkcja
// Contrast(...), ktora zmienia kontrast. W tym miejscu nic nie
// zmieniamy. Do uzupelnienia pozostaje funkcja Contrast(...)
Contrast(m_s_contrast->GetValue() - 100);
Repaint();
}

void GUIMyFrame1::m_b_prewitt_click( wxCommandEvent& event )
{
	int mwidth = this->Img_Cpy.GetWidth();
	int mheight = this->Img_Cpy.GetHeight();

	this->Img_Cpy = this->Img_Org.Copy();
	auto pix = this->Img_Cpy.GetData();
	auto pix2 = new unsigned char[mwidth * mheight * 3];
	std::copy(pix, pix+(mwidth * mheight * 3), pix2);

	int factor;
	for(int h = 1; h < mheight - 1; h++) //h = height
	{
		for(int w = 1; w < mwidth - 1; w++) // w = width
		{
			for(int color = 0; color < 3; color++)
			{
				factor = 0;
				//factor +-= pixels[ (red | green | blue)
				//			+ row_index * row_size * number_of_colors 
				//			+ column_index * number_of_colors ]

				// to match prewitt's vertical operator:
				//
				// -1 0 1
				// -1 T 1
				// -1 0 1
				//
				// where T = target pixel of calculation

				//left column
				factor -= pix2[color + (h - 1) * mwidth * 3 + (w - 1) * 3];
				factor -= pix2[color + (h) * mwidth * 3 + (w - 1) * 3];
				factor -= pix2[color + (h + 1) * mwidth * 3 + (w - 1) * 3];

				//right column
				factor += pix2[color + (h - 1) * mwidth * 3 + (w + 1) * 3];
				factor += pix2[color + (h) * mwidth * 3 + (w + 1) * 3];
				factor += pix2[color + (h + 1) * mwidth * 3 + (w + 1) * 3];

				//target pixel
				pix[color + h * mwidth * 3 + w * 3] = static_cast<unsigned char>(std::fabs(factor) / 3.0);
			}
		}
	}
	delete[] pix2;
}

void GUIMyFrame1::m_b_threshold_click( wxCommandEvent& event )
{
	this->Img_Cpy = this->Img_Org.Copy();
	auto pix = this->Img_Cpy.GetData();

	int cond = 0;
	for(auto it = pix; cond < this->Img_Cpy.GetWidth() * this->Img_Cpy.GetHeight() * 3; it++, cond++)
		if(*it < 128)
			*it = 0;
		else
			*it = 255;
}


void GUIMyFrame1::Contrast(int value)
{
 this->Img_Cpy = this->Img_Org.Copy();
 auto pix = this->Img_Cpy.GetData();
 
 auto contrast = value * 2.55;
 double factor = (259.0 * (contrast + 255)) / (255 * (259 - contrast));

 int cond = 0;
 for(auto it = pix; cond < this->Img_Cpy.GetWidth() * this->Img_Cpy.GetHeight() * 3; it++, cond++)
 {
 	int temp = static_cast<int>(factor * (*it - 128.0) + 128.0);
 	if(temp > 255)
 		temp = 255;
 	if(temp < 0)
 		temp = 0;
 	*it = static_cast<unsigned char>(temp);
 }
}

void GUIMyFrame1::Repaint()
{
 wxBitmap bitmap(Img_Cpy);          // Tworzymy tymczasowa bitmape na podstawie Img_Cpy
 wxClientDC dc(m_scrolledWindow);   // Pobieramy kontekst okna
 m_scrolledWindow->DoPrepareDC(dc); // Musimy wywolac w przypadku wxScrolledWindow, zeby suwaki prawidlowo dzialaly
 dc.DrawBitmap(bitmap, 0, 0, true); // Rysujemy bitmape na kontekscie urzadzenia
}

void GUIMyFrame1::Brightness(int value)
{
 this->Img_Cpy = this->Img_Org.Copy();
 auto pix = this->Img_Cpy.GetData();

 int cond = 0;
 for(auto it = pix; cond < this->Img_Cpy.GetWidth() * this->Img_Cpy.GetHeight() * 3; it++, cond++)
 {
 	int temp = *it + value;
 	if(temp > 255)
 		temp = 255;
 	if(temp < 0)
 		temp = 0;
 	*it = static_cast<unsigned char>(temp);
 }
}