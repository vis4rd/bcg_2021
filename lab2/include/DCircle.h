#pragma once

#include "Panel.h"

class DCircle
{
public:
	DCircle(sf::Vector2f pos, float radius = 120.f);
	~DCircle();

	void fillHSL();
	void fillHSV();
	void fillCMY();
	void fillRGB();
	
	void update(const double setting);
	void render(sf::RenderTarget *target) const;
private:
	double setting;
	int radius;
	sf::Texture *texture;
	sf::Sprite *sprite;
	sf::Uint8 *colors;
};