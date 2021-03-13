#include "Menu.h"

void Menu::updateInput(sf::Event &event)
{
	if(event.type == sf::Event::EventType::KeyPressed and event.key.code == sf::Keyboard::Key::L)
    	{}//wybor linii
    if(event.type == sf::Event::EventType::KeyPressed and event.key.code == sf::Keyboard::Key::R)
    	{}//wybor prostokata
    if(event.type == sf::Event::EventType::KeyPressed and event.key.code == sf::Keyboard::Key::A)
    	{}//wybor wypelnionego prostokata
    if(event.type == sf::Event::EventType::KeyPressed and event.key.code == sf::Keyboard::Key::C)
    	{}//wybor okregu
    if(event.type == sf::Event::EventType::KeyPressed and event.key.code == sf::Keyboard::Key::W)
    	{}//screenshot
    if(event.type == sf::Event::EventType::KeyPressed and event.key.code == sf::Keyboard::Key::O)
		{}//wczytanie z pliku
}

void Menu::update(const float &deltaTime, const sf::Vector2i &mousePos)
{

}

void Menu::render(const sf::RenderTarget *target)
{

}