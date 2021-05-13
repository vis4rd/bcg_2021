#include <wx/wx.h>
#include "GUIMyFrame1.h"
// UWAGA: TO JEST JEDYNY PLIK, KTORY NALEZY EDYTOWAC **************************

int scaleToScreen(float value);
float maxValue(float d[100][3], int n);
float minValue(float d[100][3], int n);
float approxShepard(float d[100][3], int N, float x, float y);
void drawPoints(wxMemoryDC& dc, int N, float points[100][3]);

void GUIMyFrame1::DrawMap(int N, float d[100][3], bool Contour, int MappingType, int NoLevels, bool ShowPoints)
{
 wxMemoryDC memDC;
 memDC.SelectObject(MemoryBitmap);
 memDC.SetBackground(*wxWHITE_BRUSH);
 memDC.Clear();
    
 // demo.....
 memDC.SetPen(*wxBLACK_PEN);
 memDC.SetBrush(*wxTRANSPARENT_BRUSH);

 unsigned char* pixels = image.GetData();

 auto **valueGrid = new float*[500];
 for(int i = 0; i < 500; i++)
 	valueGrid[i] = new float [500];

 for(int i = 0; i < 500; i++)
 {
 	for(int j = 0; j < 500; j++)
 	{
 		float value = approxShepard(d, N, (j/100.f) - 2.5f, (-i/100.f) + 2.5f);
 		valueGrid[i][j] = value;
 	}
 }

 float fmax = maxValue(d, N);
 float fmin = minValue(d, N);
    
 if(MappingType)
 {
 	for(int i = 0; i < 500; i++)
 	{
 		for(int j = 0; j < 500; j++)
 		{
 			float normz = (valueGrid[i][j] - fmin) / (fmax - fmin);
 			switch(MappingType)
 			{
 				case 1:
 				{
 					pixels[500 * 3 * i + 3 * j] = static_cast<unsigned char>((1- normz) * 255);
 					pixels[500 * 3 * i + 3 * j + 1] = 0;
 					pixels[500 * 3 * i + 3 * j + 2] = static_cast<unsigned char>(normz * 255);
 					break;
 				}
 				case 2:
 				{
 					pixels[500 * 3 * i + 3 * j] = static_cast<unsigned char>(255 * (normz < 0.5f ? (1.f - 2*normz) : 0.f));
 					pixels[500 * 3 * i + 3 * j + 1] = static_cast<unsigned char>(255 * (normz < 0.5f ? 2*normz : 2*(1.f - normz)));
 					pixels[500 * 3 * i + 3 * j + 2] = static_cast<unsigned char>(255 * (normz < 0.5f ? 0.f : 0.5f*normz));
 					break;
 				}
 				case 3:
 				{
 					pixels[500 * 3 * i + 3 * j] = static_cast<unsigned char>(normz * 255);
 					pixels[500 * 3 * i + 3 * j + 1] = static_cast<unsigned char>(normz * 255);
 					pixels[500 * 3 * i + 3 * j + 2] = static_cast<unsigned char>(normz * 255);
 					break;
 				}
 				default: break;
 			}
 		}
 	}

 	wxBitmap bmap(image, 24);
 	memDC.DrawBitmap(bmap, 0, 0);
 }

 if(Contour)
 {
 	int code = 0;
 	for(int n = 0; n < NoLevels; n++)
 	{
 		float threshold = (n + 1.f) * (fmax - fmin) / (NoLevels + 1.f) + fmin;
 		for(int y = 0; y < 499; y++)
 		{
 			for(int x = 0; x < 499; x++)
 			{
 				code = 0;
 				if(valueGrid[y+1][x] < threshold)
 					code++;
 				if(valueGrid[y+1][x+1] < threshold)
 					code += 2;
 				if(valueGrid[y][x+1] < threshold)
 					code += 4;
 				if(valueGrid[y][x] < threshold)
 					code += 8;

 				switch(code)
 				{
 					case 1:
 					{
 						memDC.DrawPoint(x, y);
 						memDC.DrawPoint(x + 1, y + 1);
 						memDC.DrawPoint(x + 1, y);
 						break;
 					}
 					case 2:
 					{
 						memDC.DrawPoint(x, y);
 						memDC.DrawPoint(x + 1, y);
 						memDC.DrawPoint(x, y + 1);
 						break;
 					}
 					case 3:
 					{
 						memDC.DrawPoint(x, y);
 						memDC.DrawPoint(x + 1, y);
 						break;
 					}
 					case 4:
 					{
 						memDC.DrawPoint(x, y);
 						memDC.DrawPoint(x + 1, y + 1);
 						memDC.DrawPoint(x, y + 1);
 						break;
 					}
 					case 5:
 					{
 						memDC.DrawPoint(x, y);
 						memDC.DrawPoint(x, y + 1);
 						break;
 					}
 					case 6:
 					{
 						memDC.DrawPoint(x, y);
 						memDC.DrawPoint(x, y + 1);
 						break;
 					}
 					case 7: memDC.DrawPoint(x, y); break;
 					case 8:
 					{
 						memDC.DrawPoint(x + 1, y);
 						memDC.DrawPoint(x + 1, y + 1);
 						memDC.DrawPoint(x, y + 1);
 						break;
 					}
 					case 9:
 					{
 						memDC.DrawPoint(x + 1, y);
 						memDC.DrawPoint(x + 1, y + 1);
 						break;
 					}
 					case 10:
 					{
 						memDC.DrawPoint(x + 1, y);
 						memDC.DrawPoint(x, y + 1);
 						break;
 					}
 					case 11: memDC.DrawPoint(x + 1, y); break;
 					case 12:
 					{
 						memDC.DrawPoint(x, y + 1);
 						memDC.DrawPoint(x + 1, y + 1);
 						break;
 					}
 					case 13: memDC.DrawPoint(x + 1, y + 1); break;
 					case 14: memDC.DrawPoint(x, y + 1); break;
 					default: break;
 				}
 			}
 		}
 	}
 }

 if(ShowPoints)
 	drawPoints(memDC, N, d);

 for(int i = 0; i < 500; i++)
 	delete[] valueGrid[i];
 delete[] valueGrid;
      
}

int scaleToScreen(float value)
{
	return static_cast<int>(100.0 * value + 250.0);
}

float maxValue(float d[100][3], int n)
{
	float result = d[0][2];
	for(int i = 0; i < n; i++)
		if(result < d[i][2])
			result = d[i][2];
	return result;
}

float minValue(float d[100][3], int n)
{
	float result = d[0][2];
	for(int i = 0; i < n; i++)
		if(result > d[i][2])
			result = d[i][2];
	return result;
}

float approxShepard(float d[100][3], int N, float x, float y)
{
	float dm = 0.f;
	float nm = 0.f;
	for(int i = 0; i < N; i++)
	{
		float wdm = ((x - d[i][0]) * (x - d[i][0])) + 
					((y - d[i][1]) * (y - d[i][1]));
		float weight = 1.f / wdm;

		dm += weight;
		nm += weight * d[i][2];
	}
	return nm / dm;
}

void drawPoints(wxMemoryDC& dc, int N, float points[100][3])
{
	wxPoint center;
	int radius = 3;
	for(int i = 0; i < N; i++)
	{
		center.x = points[i][0] * 100 + 250;
		center.y = points[i][1] * 100 + 250;
		dc.DrawLine(center.x - radius, 500 - center.y, center.x + radius + 1, 500 - center.y);
		dc.DrawLine(center.x, 500 - center.y + radius, center.x, 500 - center.y - radius - 1);
	}
}