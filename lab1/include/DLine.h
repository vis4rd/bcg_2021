#pragma once

#include "DRect.h"

class DLine : public DShape
{
public:
	DLine(sf::Vector2f pos, sf::Color outlineColor = sf::Color::White)
	: DShape(pos, outlineColor, sf::Color::Transparent)
	{
		this->shape.setPrimitiveType(sf::Lines);
		sf::Vertex temp;
		temp.position = pos;
		temp.color = outlineColor;
		this->shape.append(temp);
		this->shape.append(temp);
	}
	~DLine(){}

	inline void setSize(const sf::Vector2f size)
	{
		this->shape[1].position = this->shape[0].position + size;
	}

	inline const sf::Vector2f &getCenter() const
	{
		return this->shape[0].position;
	}

	inline void render(sf::RenderTarget *target)
	{
		target->draw(this->shape);
	}

private:
	sf::VertexArray shape;
};