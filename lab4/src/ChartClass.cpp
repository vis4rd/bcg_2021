#include <wx/dc.h>
#include <memory>
#include <cmath>

#include "../include/ChartClass.h"
#include "../include/vecmat.h"

ChartClass::ChartClass(std::shared_ptr<ConfigClass> c)
{
    cfg= std::move(c);
    x_step=200;
}

void ChartClass::Set_Range()
{
 double xmin=9999.9,xmax=-9999.9,ymin=9999.9,ymax=-9999.9;
 double x,y,step;
 int i;

 xmin=cfg->Get_x_start();
 xmax=cfg->Get_x_stop();

 step=(cfg->Get_x_stop()-cfg->Get_x_start())/(double)x_step;
 x=cfg->Get_x_start();

 for (i=0;i<=x_step;i++)
  {
   y=GetFunctionValue(x);
   if (y>ymax) ymax=y;
   if (y<ymin) ymin=y;
   x=x+step;
  }

 y_min=ymin;
 y_max=ymax;
 x_min=xmin;
 x_max=xmax;
}


double ChartClass::GetFunctionValue(double x)
{
 if (cfg->Get_F_type()==1) return x*x;
 if (cfg->Get_F_type()==2) return 0.5*exp(4*x-3*x*x);
 return x+sin(x*4.0);
}

double ChartClass::Get_Y_min()
{
    Set_Range();
    return y_min;
}

double ChartClass::Get_Y_max()
{
    Set_Range();
    return y_max;
}

Matrix ChartClass::getRotationMatrix(int w, int h)
{
	Matrix rotation;

	const double angle = this->cfg->Get_Alpha();
	const double cosinus = std::cos(angle * M_PI / -180.0);
	const double sinus = std::sin(angle * M_PI / -180.0);

	rotation.data[0][0] = cosinus;
	rotation.data[1][1] = cosinus;
	rotation.data[0][1] = sinus;
	rotation.data[1][0] = -sinus;

	if(this->cfg->RotateScreenCenter())//obracamy wokol srodka ekranu
	{
		rotation.data[0][2] = (w / 2.0) * (1 - cosinus) + (h / 2.0) * (-sinus);
		rotation.data[1][2] = (w / 2.0) * sinus + (h / 2.0) * (1 - cosinus);
	}
	else//uwzglednienie przesuniecia
	{
		Matrix scale = this->getScaleMatrix(w, h);
		rotation.data[0][2] = scale.data[0][2] * (1 - cosinus) + scale.data[1][2] * (-sinus);
		rotation.data[1][2] = scale.data[0][2] * sinus + scale.data[1][2] * (1 - cosinus);
	}
	return rotation;
}

Matrix ChartClass::getScaleMatrix(int w, int h)
{
	Matrix scale;

	scale.data[0][0] = (w - 20.0) / (this->cfg->Get_x1() - this->cfg->Get_x0());
	scale.data[1][1] = (h - 20.0) / (this->cfg->Get_y1() - this->cfg->Get_y0());
	scale.data[0][2] = 10.0 - (scale.data[0][0] * this->cfg->Get_x0());
	scale.data[1][2] = 10.0 - (scale.data[1][1] * this->cfg->Get_y0());

	return scale;
}

Matrix ChartClass::getTranslationMatrix()
{
	Matrix trans;

	trans.data[0][0] = 1.0;
	trans.data[1][1] = 1.0;
	trans.data[0][2] = this->cfg->Get_dX();
	trans.data[1][2] = -this->cfg->Get_dY();

	return trans;
}

void ChartClass::drawText(	wxDC *dc,
							Matrix transform,
							wxString text,
							double x,
							double y,
							int h)
{
	Vector rotation;
	rotation.Set(x, y);
	rotation = transform * rotation;

	dc->DrawRotatedText(text,
						static_cast<int>(rotation.GetX()),
						static_cast<int>(h - rotation.GetY()),
						this->cfg->Get_Alpha());
}

void ChartClass::drawAxes(wxDC *dc, Matrix transform, int w, int h)
{
	this->transformLine(dc, transform, this->x_min, 0, this->x_max, 0, w, h); // X
	const double dX = 1.0 + static_cast<int>( (this->cfg->Get_x1() - this->cfg->Get_x0()) / 10.0 );
	//double diff = (cfg->Get_x1() - cfg->Get_x0()) / 4.0;

	for(double x = this->x_min; x < this->x_max; x += (dX / 2.0))
	{
		if(x == 0.0 || x >= 2.0)
			continue;
		this->transformLine(dc, transform, x, -0.05, x, 0.05, w, h);
		this->drawText(dc, transform, _(std::to_string(x)), x-0.001, -0.1, h);
	}

	this->transformLine(dc, transform, this->cfg->Get_x_stop(), 0, this->cfg->Get_x_stop() - 0.05, 0.05, w, h);

	this->transformLine(dc, transform, 0, this->y_min, 0, this->y_max, w, h); // Y
	const double dY = 1.0 + static_cast<int>( (this->cfg->Get_y1() - this->cfg->Get_y0()) / 20.0 );

	for(double y = this->y_min; y < this->y_max; y += (dY))
	{
		if(y == 0.0 || y >= 2.0)
			continue;
		this->transformLine(dc, transform, -0.05, y, 0.05, y, w, h);
		this->drawText(dc, transform, _(std::to_string(y)), 0.1, y-0.001, h);
	}

	this->transformLine(dc, transform, 0, this->y_max, 0.05, this->y_max-0.05, w, h);
}

void ChartClass::transformLine(	wxDC *dc,
								Matrix t,
								double x1,
								double y1,
								double x2,
								double y2,
								int w,
								int h)
{
	Vector start, stop;
	start.Set(x1, y1);
	stop.Set(x2, y2);

	start = t * start;
	stop = t * stop;

	dc->DrawLine(start.GetX(), h-start.GetY(), stop.GetX(), h-stop.GetY());
}

void ChartClass::Draw(wxDC *dc, int w, int h)
{
	this->Set_Range();

	dc->SetBackground(wxBrush(RGB(255, 255, 255)));
	dc->Clear();
	dc->SetPen(wxPen(RGB(255, 0, 0)));
	dc->DrawRectangle(10, 10, w - 20, h - 20);

	dc->SetClippingRegion(wxRect(10, 10, w - 20, h - 20));
	dc->SetFont(*wxSMALL_FONT);
	dc->SetPen(wxPen(RGB(0, 0, 255)));
	Matrix trans;
	if(this->cfg->RotateScreenCenter())
		trans = getRotationMatrix(w, h) * 
				getTranslationMatrix() * 
				getScaleMatrix(w, h);
	else
		trans = getTranslationMatrix() *
				getRotationMatrix(w, h) *
				getScaleMatrix(w, h);

	this->drawAxes(dc, trans, w, h);
	dc->SetPen(wxPen(RGB(0, 255, 0)));
	const double dX = (this->cfg->Get_x1() - this->cfg->Get_x0()) / this->x_step;
	for(double x = this->cfg->Get_x_start(); x < this->cfg->Get_x_stop(); x += dX)
		this->transformLine(dc,
							trans,
							x,
							this->GetFunctionValue(x),
							x + dX,
							this->GetFunctionValue(x + dX),
							w,
							h);
}