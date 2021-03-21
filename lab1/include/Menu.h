#pragma once

#include "DLine.h"

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
	ACTIVE
};

class Menu
{
public:
	static void init();
	static void terminate();

	static void updateInput(sf::Event &event, const sf::Vector2i &mousePos, sf::Window *window);
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
	static sf::Text exitText;
	static sf::Text foreText;
	static sf::Text backText;
	static sf::VertexArray *lowerLine;
	static sf::VertexArray *colorPanel1;
	static sf::VertexArray *colorPanel2;
	static sf::Texture tb;
	static sf::Sprite background;

	static std::list<DShape *> shapes;
	static sf::Color outlineColor;
	static sf::Color fillColor;
};