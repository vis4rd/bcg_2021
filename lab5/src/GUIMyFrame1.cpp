#include "GUIMyFrame1.h"
#include <vector>
#include <fstream>
#include "vecmat.h"

struct Point {
 float x, y, z;
 Point(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};

struct Color {
 int R, G, B;
 Color(int _R, int _G, int _B) : R(_R), G(_G), B(_B) {}
};

struct Segment {
 Point begin, end;
 Color color;
 Segment(Point _begin, Point _end, Color _color) : begin(_begin), end(_end), color(_color) {}
};

std::vector<Segment> data;

GUIMyFrame1::GUIMyFrame1( wxWindow* parent )
:
MyFrame1( parent )
{
 m_button_load_geometry->SetLabel(_("Wczytaj Geometrie"));
 m_staticText25->SetLabel(_("Obrot X:"));
 m_staticText27->SetLabel(_("Obrot Y:"));
 m_staticText29->SetLabel(_("Obrot Z:"));

 WxSB_TranslationX->SetRange(0, 200); WxSB_TranslationX->SetValue(100);
 WxSB_TranslationY->SetRange(0, 200); WxSB_TranslationY->SetValue(100);
 WxSB_TranslationZ->SetRange(0, 200); WxSB_TranslationZ->SetValue(100);

 WxSB_RotateX->SetRange(0, 360); WxSB_RotateX->SetValue(0);
 WxSB_RotateY->SetRange(0, 360); WxSB_RotateY->SetValue(0);
 WxSB_RotateZ->SetRange(0, 360); WxSB_RotateZ->SetValue(0);

 WxSB_ScaleX->SetRange(1, 200); WxSB_ScaleX->SetValue(100);
 WxSB_ScaleY->SetRange(1, 200); WxSB_ScaleY->SetValue(100);
 WxSB_ScaleZ->SetRange(1, 200); WxSB_ScaleZ->SetValue(100);
}

void GUIMyFrame1::WxPanel_Repaint( wxUpdateUIEvent& event )
{
 Repaint();
}

void GUIMyFrame1::m_button_load_geometry_click( wxCommandEvent& event )
{
 wxFileDialog WxOpenFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""), wxT("Geometry file (*.geo)|*.geo"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

 if (WxOpenFileDialog.ShowModal() == wxID_OK)
 {
  double x1, y1, z1, x2, y2, z2;
  int r, g, b;

  std::ifstream in(WxOpenFileDialog.GetPath().ToAscii());
  if (in.is_open())
  {
   data.clear();
   while (!in.eof())
   {
    in >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> r >> g >> b;
    data.push_back(Segment(Point(x1, y1, z1), Point(x2, y2, z2), Color(r, g, b)));
   }
   in.close();
  }
 }
}

void GUIMyFrame1::Scrolls_Updated( wxScrollEvent& event )
{
WxST_TranslationX->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationX->GetValue() - 100) / 50.0));
WxST_TranslationY->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationY->GetValue() - 100) / 50.0));
WxST_TranslationZ->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationZ->GetValue() - 100) / 50.0));

WxST_RotateX->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateX->GetValue()));
WxST_RotateY->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateY->GetValue()));
WxST_RotateZ->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateZ->GetValue()));

WxST_ScaleX->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleX->GetValue() / 100.0));
WxST_ScaleY->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleY->GetValue() / 100.0));
WxST_ScaleZ->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleZ->GetValue() / 100.0));


Repaint();
}


void GUIMyFrame1::Repaint()
{
  //przygotowanie macierzy przeksztalcen przed rysowaniem
  Matrix4 translationMatrix;
  for(int i = 0; i < 4; i++)
    for(int j = 0; j < 4; j++)
      translationMatrix.data[i][j] = (i==j) ? 1.0 : 0.0;
  translationMatrix.data[0][3] = (this->WxSB_TranslationX->GetValue() - 100.0) / 50.0;
  translationMatrix.data[1][3] = (this->WxSB_TranslationY->GetValue() - 100.0) / 50.0;
  translationMatrix.data[2][3] = (this->WxSB_TranslationZ->GetValue() - 100.0) / 50.0;

  Matrix4 XrotationMatrix;
  for(int i = 0; i < 4; i++)
    for(int j = 0; j < 4; j++)
      XrotationMatrix.data[i][j] = (i==j && (i == 0 || i == 3)) ? 1.0 : 0.0;
  const double angleX = this->WxSB_RotateX->GetValue() * 2.0 * M_PI / this->WxSB_RotateX->GetMax();
  XrotationMatrix.data[1][1] = std::cos(angleX);
  XrotationMatrix.data[1][2] = -std::sin(angleX);
  XrotationMatrix.data[2][1] = std::sin(angleX);
  XrotationMatrix.data[2][2] = std::cos(angleX);

  Matrix4 YrotationMatrix;
  for(int i = 0; i < 4; i++)
    for(int j = 0; j < 4; j++)
      YrotationMatrix.data[i][j] = (i==j && (i == 1 || i == 3)) ? 1.0 : 0.0;
  const double angleY = this->WxSB_RotateY->GetValue() * 2.0 * M_PI / this->WxSB_RotateY->GetMax();
  YrotationMatrix.data[0][0] = std::cos(angleY);
  YrotationMatrix.data[0][2] = std::sin(angleY);
  YrotationMatrix.data[2][0] = -std::sin(angleY);
  YrotationMatrix.data[2][2] = std::cos(angleY);

  Matrix4 ZrotationMatrix;
  for(int i = 0; i < 4; i++)
    for(int j = 0; j < 4; j++)
      ZrotationMatrix.data[i][j] = (i==j && (i == 2 || i == 3)) ? 1.0 : 0.0;
  const double angleZ = this->WxSB_RotateZ->GetValue() * 2.0 * M_PI / this->WxSB_RotateZ->GetMax();
  ZrotationMatrix.data[0][0] = std::cos(angleZ);
  ZrotationMatrix.data[0][1] = -std::sin(angleZ);
  ZrotationMatrix.data[1][0] = std::sin(angleZ);
  ZrotationMatrix.data[1][1] = std::cos(angleZ);

  Matrix4 scaleMatrix;
  for(int i = 0; i < 4; i++)
    for(int j = 0; j < 4; j++)
      scaleMatrix.data[i][j] = 0.0;
  scaleMatrix.data[0][0] = this->WxSB_ScaleX->GetValue() / 100.0;
  scaleMatrix.data[1][1] = this->WxSB_ScaleY->GetValue() / 100.0;
  scaleMatrix.data[2][2] = this->WxSB_ScaleZ->GetValue() / 100.0;
  scaleMatrix.data[3][3] = 1.0;

  //polaczenie przeksztalcen w jedno
  Matrix4 rotationMatrix = XrotationMatrix * YrotationMatrix * ZrotationMatrix;
  Matrix4 transformationMatrix = translationMatrix * rotationMatrix * scaleMatrix;
  Vector4 v1, v2;

  wxClientDC myDC(WxPanel);
  wxBufferedDC myBuff(&myDC);

  myBuff.SetBackground(wxColour(RGB(255, 255, 255)));
  myBuff.Clear();

  //petla iterujaca po wektorze segmentow data
  for(auto &it : data)
  {
    //przypisanie do wektora
    v1.Set(it.begin.x, it.begin.y, it.begin.z);
    v2.Set(it.end.x, it.end.y, it.end.z);

    v1 = transformationMatrix * v1;
    v2 = transformationMatrix * v2;

    //uzyskanie rozmiarow plotna, na ktorym wykoanywane jest rysowanie
    const double width = this->WxPanel->GetSize().GetX();
    const double height = this->WxPanel->GetSize().GetY();

    //rysowanie 
    myBuff.SetPen(wxPen(wxColour(it.color.R, it.color.G, it.color.B)));
    //wysrodkowanie obiektu na ekranie
    //
    //dzielenie przez |z|, poniewaz plaszczyzna na ktora rzutowany jest obraz 3D
    //ma fov = 90 (i jest to nasz ekran), czyli ta bardzo skomplikowana macierz z wykladu str 17 
    //w wielu miejscach zeruje wartosci
    //
    //de facto potrzebne nam sa tylko wysokosc i szerokosc okna w ktorym rysujemy
    myBuff.DrawLine((width/2.0) + ((width/2.0)*v1.GetX() / std::abs(1.0 + (v1.GetZ() / 2.0))),   //x1
                    (height/2.0) + ((height/2.0)*v1.GetY() / std::abs(1.0 + (v1.GetZ() / 2.0))), //y1
                    (width/2.0) + ((width/2.0)*v2.GetX() / std::abs(1.0 + (v2.GetZ() / 2.0))),   //x2
                    (height/2.0) + ((height/2.0)*v2.GetY() / std::abs(1.0 + (v2.GetZ() / 2.0))));//y2
  }
}