#include "DCircle.h"

DCircle::DCircle(sf::Vector2f pos, float radius)
:
setting(0.0),
radius(radius),
texture(new sf::Texture()),
sprite(new sf::Sprite()),
colors(new sf::Uint8[16*this->radius*this->radius])
{
	this->texture->create(2 * this->radius, 2 * this->radius);
	this->sprite->setPosition(pos);
}

DCircle::~DCircle()
{
	delete[] this->colors;
	delete this->sprite;
	delete this->texture;
}

void DCircle::fillHSL()
{
	for (int i = 0; i < 2 * this->radius; i++)
	{
		for (int j = 0; j < 2 * this->radius; j++)
		{
			double i2 = i - this->radius;
			double j2 = this->radius - j;

			float angle = atan2(j2, i2);//kat phi w radianach (wspolrzednych biegunowych)

			if (angle < 0)
				angle += 2 * M_PI;

			float distance = sqrt(j2*j2 + i2*i2);//to jest w zasadzie odleglosc od punktu (0,0)

			if (distance <= this->radius)
			{
				float distFactor = distance / this->radius;//jak sie rozni promien okregu od odleglosci od (0,0)
				float angledeg = angle * 180.0 / M_PI;//kat phi w stopniach (konwersja radiany-stopnie)

				float check = (1 - fabs(2 * setting - 1)) * distFactor;
				float hexAlign = check * (1 - fabs(fmod(angledeg / 60, 2) - 1));
				float modifier = setting - (check / 2);
				float red, green, blue;
				//konwersja HSL-RGB

				if (angledeg < 60.0) { red = check; green = hexAlign; blue = 0; }
				else if (angledeg < 120.0) { red = hexAlign; green = check; blue = 0; }
				else if (angledeg < 180.0) { red = 0; green = check; blue = hexAlign; }
				else if (angledeg < 240.0) { red = 0; green = hexAlign; blue = check; }
				else if (angledeg < 300.0) { red = hexAlign; green = 0; blue = check; }
				else { red = check; green = 0; blue = hexAlign; }

				sf::Color newColor = sf::Color((red + modifier) * 255,
											(green + modifier) * 255,
											(blue + modifier) * 255);

				this->colors[4 * (j * 2 * this->radius + i) + 0] = newColor.r;
				this->colors[4 * (j * 2 * this->radius + i) + 1] = newColor.g;
				this->colors[4 * (j * 2 * this->radius + i) + 2] = newColor.b;
				this->colors[4 * (j * 2 * this->radius + i) + 3] = 255;
			}
			else
			{
				for(int k = 0; k < 4; k++)
					this->colors[4 * (j * 2 * this->radius + i) + k] = 0;
			}
		}
	}
	this->texture->update(this->colors);
	this->sprite->setTexture(*this->texture);
}

void DCircle::fillHSV()
{
	for (int i = 0; i < 2 * this->radius; i++)
	{
		for (int j = 0; j < 2 * this->radius; j++)
		{
			double i2 = i - this->radius;
			double j2 = this->radius - j;

			float angle = atan2(j2, i2);

			if (angle < 0)
				angle += 2 * M_PI;

			float distance = sqrt(j2*j2 + i2*i2);

			if (distance <= this->radius)
			{
				float distFactor = distance / this->radius;
				float angledeg = angle * 180.0 / M_PI;

				float midColor = this->setting * distFactor;
				float hexAlign = midColor * (1 - fabs(fmod(angledeg / 60, 2) - 1));
				float modifier = this->setting - midColor;
				float red, green, blue;
				//konwersja HSV-RGB

				if (angledeg < 60.0) { red = midColor; green = hexAlign; blue = 0; }
				else if (angledeg < 120.0) { red = hexAlign; green = midColor; blue = 0; }
				else if (angledeg < 180.0) { red = 0; green = midColor; blue = hexAlign; }
				else if (angledeg < 240.0) { red = 0; green = hexAlign; blue = midColor; }
				else if (angledeg < 300.0) { red = hexAlign; green = 0; blue = midColor; }
				else { red = midColor; green = 0; blue = hexAlign; }

				sf::Color newColor = sf::Color((red + modifier) * 255,
												(green + modifier) * 255,
												(blue + modifier) * 255);
				this->colors[4 * (j * 2 * this->radius + i) + 0] = newColor.r;
				this->colors[4 * (j * 2 * this->radius + i) + 1] = newColor.g;
				this->colors[4 * (j * 2 * this->radius + i) + 2] = newColor.b;
				this->colors[4 * (j * 2 * this->radius + i) + 3] = 255;
			}
			else
			{
				for(int k = 0; k < 4; k++)
					this->colors[4 * (j * 2 * this->radius + i) + k] = 0;
			}
		}
	}
	this->texture->update(this->colors);
	this->sprite->setTexture(*this->texture);
}

void DCircle::fillCMY()
{
	for (int i = 0; i < 2 * this->radius; i++)
	{
		for (int j = 0; j < 2 * this->radius; j++)
		{
			double i2 = i - this->radius;
			double j2 = this->radius - j;

			float angle = atan2(j2, i2);

			if (angle < 0)
				angle += 2 * M_PI;

			float distance = sqrt(j2*j2 + i2*i2);

			if (distance <= this->radius)
			{
				float distFactor = distance / this->radius;
				//konwersja CMY-RGB
				sf::Color newColor = sf::Color((1 - (distFactor)) * 255,
											(1 - (angle / (2 * M_PI))) * 255,
											(1 - this->setting) * 255);
				this->colors[4 * (j * 2 * this->radius + i) + 0] = newColor.r;
				this->colors[4 * (j * 2 * this->radius + i) + 1] = newColor.g;
				this->colors[4 * (j * 2 * this->radius + i) + 2] = newColor.b;
				this->colors[4 * (j * 2 * this->radius + i) + 3] = 255;
			}
			else
			{
				for(int k = 0; k < 4; k++)
					this->colors[4 * (j * 2 * this->radius + i) + k] = 0;
			}
		}
	}
	this->texture->update(this->colors);
	this->sprite->setTexture(*this->texture);
}

void DCircle::fillRGB()
{
	for (int i = 0; i < 2 * this->radius; i++)
	{
		for (int j = 0; j < 2 * this->radius; j++)
		{
			double i2 = i - this->radius;
			double j2 = this->radius - j;

			float angle = atan2(j2, i2);

			if (angle < 0)
				angle += 2 * M_PI;

			float distance = sqrt(j2*j2 + i2*i2);

			if (distance <= this->radius)
			{
				float distFactor = distance / this->radius;
				//juz jest w RGB
				sf::Color newColor = sf::Color(distFactor * 255, 
											angle / (2 * M_PI) * 255,
											this->setting * 255);
				this->colors[4 * (j * 2 * this->radius + i) + 0] = newColor.r;
				this->colors[4 * (j * 2 * this->radius + i) + 1] = newColor.g;
				this->colors[4 * (j * 2 * this->radius + i) + 2] = newColor.b;
				this->colors[4 * (j * 2 * this->radius + i) + 3] = 255;
			}
			else
			{
				for(int k = 0; k < 4; k++)
					this->colors[4 * (j * 2 * this->radius + i) + k] = 0;
			}
		}
	}
	this->texture->update(this->colors);
	this->sprite->setTexture(*this->texture);
}

void DCircle::update(const double setting)
{
	this->setting = setting;
}

void DCircle::render(sf::RenderTarget *target) const
{
	target->draw(*this->sprite);
}