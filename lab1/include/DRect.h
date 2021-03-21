#pragma once

#include "DCircle.h"

class DRect : public DShape
{
public:
	DRect(sf::Vector2f pos, sf::Color outlineColor = sf::Color::White, sf::Color fillColor = sf::Color::Transparent)
	: DShape(pos, outlineColor, fillColor)
	{
		this->shape.setPosition(pos);
		this->shape.setSize(sf::Vector2f(1.f, 1.f));
		this->shape.setFillColor(fillColor);
		this->shape.setOutlineColor(outlineColor);
		this->shape.setOutlineThickness(-1.f);
	}
	~DRect(){}

	inline void setSize(const sf::Vector2f size)
	{
		this->shape.setSize(size);
	}

	inline const sf::Vector2f &getCenter() const
	{
		return this->shape.getPosition();
	}

	inline void render(sf::RenderTarget *target)
	{
		target->draw(this->shape);
	}

private:
	sf::RectangleShape shape;
};