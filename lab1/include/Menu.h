#pragma once

#include "pch.h"

enum ShapeType
{
	LINE = 0,
	RECT,
	FRECT,
	CIRCLE
};

enum DrawState
{
	IDLE = 0,
	LIN,
	REC,
	FREC,
	CIRC
};

class Menu
{
public:
	static void init();

	static void updateInput(sf::Event &event, const sf::Vector2i &mousePos);
	static void update(const float &deltaTime, const sf::Vector2i &mousePos);
	static void render(sf::RenderTarget *target);	

private:
	static unsigned shapeChoice;
	static unsigned state;

	static sf::Font *font;
	static sf::Text lineText;
	static sf::Text rectText;
	static sf::Text filledRectText;
	static sf::Text circleText;
	static sf::Text screenshotText;
	static sf::Text readFileText;
	static sf::VertexArray *lowerLine;
	static sf::VertexArray *colorPanel1;
	static sf::VertexArray *colorPanel2;

	static std::list<sf::RectangleShape *> rects;
	static std::list<sf::CircleShape *> circles;
	static std::list<sf::VertexArray *> lines;
	static sf::Color outlineColor;
	static sf::Color fillColor;
};