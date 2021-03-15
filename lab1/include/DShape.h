#pragma once

#include "pch.h"

class DShape
{
public:
	DShape(sf::Vector2f pos, sf::Color outlineColor, sf::Color fillColor) {};
	virtual ~DShape() {}

	virtual void setSize(const sf::Vector2f size) = 0;
	virtual const sf::Vector2f &getCenter() const = 0;
	virtual void render(sf::RenderTarget *target) = 0;
private:
	
};