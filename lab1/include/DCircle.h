#pragma once

#include "DShape.h"

class DCircle : public DShape
{
public:
	DCircle(sf::Vector2f pos, sf::Color outlineColor = sf::Color::White, sf::Color fillColor = sf::Color::Transparent)
	: DShape(pos, outlineColor, fillColor)
	{
		this->shape.setPosition(pos);
		this->shape.setRadius(1.f);
		this->shape.setOrigin(sf::Vector2f(0.5f, 0.5f));
		this->shape.setFillColor(fillColor);
		this->shape.setOutlineColor(outlineColor);
		this->shape.setOutlineThickness(-1.f);
	}
	~DCircle(){}

	inline void setSize(const sf::Vector2f size)
	{
		this->shape.setRadius(size.x > size.y ? size.x : size.y);
		this->shape.setOrigin(sf::Vector2f(1.f, 1.f)*this->shape.getRadius());
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
	sf::CircleShape shape;
};