#pragma once

#include "pch.h"

class Panel
{
public:
	Panel(sf::Vector2f pos, sf::Vector2f size);
	~Panel();
	
	inline const double &getSetting() const
	{
		return this->setting;
	}

	void update(sf::Vector2i mousePos, sf::Event *event);
	void render(sf::RenderTarget *target) const;

private:
	void setCursorPosition(float localY);

	sf::VertexArray *body;
	sf::VertexArray *cursor;
	sf::RectangleShape box;
	double setting;
};