#include "Panel.h"

Panel::Panel(sf::Vector2f pos, sf::Vector2f size)
{
	this->body = new sf::VertexArray(sf::Quads);

	sf::Vertex temp(pos, sf::Color::Black);
	this->body->append(temp);
	temp.position = sf::Vector2f(pos.x+size.x, pos.y);
	this->body->append(temp);
	temp.position = pos+size;
	temp.color = sf::Color::White;
	this->body->append(temp);
	temp.position = sf::Vector2f(pos.x, pos.y+size.y);
	this->body->append(temp);

	this->cursor = new sf::VertexArray(sf::Lines);
	temp.position = pos - sf::Vector2f(10.f, 0.f);
	temp.color = sf::Color::Black;
	this->cursor->append(temp);
	temp.position = pos - sf::Vector2f(2.f, 0.f);
	this->cursor->append(temp);

	this->box.setPosition(pos);
	this->box.setSize(size);
	this->box.setFillColor(sf::Color::Transparent);
	this->box.setOutlineColor(sf::Color::Black);
	this->box.setOutlineThickness(1.f);

	this->setting = 0.0;
}

Panel::~Panel()
{
	if(this->body)
		delete this->body;
	if(this->cursor)
		delete this->cursor;
}

void Panel::update(sf::Vector2i mousePos, sf::Event *event)
{
	if(this->box.getGlobalBounds().contains(sf::Vector2f(mousePos.x, mousePos.y)))
	{
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2f where = (sf::Vector2f(mousePos.x, mousePos.y) - this->box.getPosition());
			this->setting = static_cast<double>(where.y/this->box.getSize().y);
			this->setCursorPosition(where.y);
		}
	}
}

void Panel::render(sf::RenderTarget *target) const
{
	target->draw(this->box);
	target->draw(*this->body);
	target->draw(*this->cursor);
}

void Panel::setCursorPosition(float localY)
{
	(*this->cursor)[0].position.y = this->box.getPosition().y+localY;
	(*this->cursor)[1].position.y = this->box.getPosition().y+localY;
}