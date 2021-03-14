#include "Menu.h"

unsigned Menu::shapeChoice = 0u;
unsigned Menu::state = DrawState::IDLE;
sf::Font *Menu::font = nullptr;
sf::Text Menu::lineText = sf::Text();
sf::Text Menu::rectText = sf::Text();
sf::Text Menu::filledRectText = sf::Text();
sf::Text Menu::circleText = sf::Text();
sf::Text Menu::screenshotText = sf::Text();
sf::Text Menu::readFileText = sf::Text();
sf::VertexArray *Menu::lowerLine = nullptr;
std::list<sf::RectangleShape *> Menu::rects = {};
std::list<sf::CircleShape *> Menu::circles = {};
std::list<sf::VertexArray *> Menu::lines = {};
sf::Color Menu::outlineColor = sf::Color::Red;
sf::Color Menu::fillColor = sf::Color::White;

void Menu::init()
{
	Menu::font = new sf::Font;
	Menu::font->loadFromFile("../resources/consola.ttf");

	int size = 15;
	sf::Color color = sf::Color::White;

	Menu::lineText.setFont(*Menu::font);
	Menu::rectText.setFont(*Menu::font);
	Menu::filledRectText.setFont(*Menu::font);
	Menu::circleText.setFont(*Menu::font);
	Menu::screenshotText.setFont(*Menu::font);
	Menu::readFileText.setFont(*Menu::font);

	Menu::lineText.setCharacterSize(size);
	Menu::rectText.setCharacterSize(size);
	Menu::filledRectText.setCharacterSize(size);
	Menu::circleText.setCharacterSize(size);
	Menu::screenshotText.setCharacterSize(size);
	Menu::readFileText.setCharacterSize(size);

	Menu::lineText.setFillColor(color);
	Menu::rectText.setFillColor(color);
	Menu::filledRectText.setFillColor(color);
	Menu::circleText.setFillColor(color);
	Menu::screenshotText.setFillColor(color);
	Menu::readFileText.setFillColor(color);

	Menu::lineText.setString("<L> Linia");
	Menu::rectText.setString("<R> Prostokat");
	Menu::filledRectText.setString("<A> Wypelniony Prostokat");
	Menu::circleText.setString("<C> Okrag");
	Menu::screenshotText.setString("<W> Zapis Do Pliku");
	Menu::readFileText.setString("<O> Wczytanie Z Pliku");

	Menu::lineText.setPosition(sf::Vector2f(30.f, 410.f));
	Menu::rectText.setPosition(sf::Vector2f(30.f, 430.f));
	Menu::filledRectText.setPosition(sf::Vector2f(30.f, 450.f));
	Menu::circleText.setPosition(sf::Vector2f(250.f, 410.f));
	Menu::screenshotText.setPosition(sf::Vector2f(250.f, 430.f));
	Menu::readFileText.setPosition(sf::Vector2f(250.f, 450.f));

	Menu::lowerLine = new sf::VertexArray(sf::Lines, 2);
	sf::Vertex temp;
	temp.color = color;
	temp.position = sf::Vector2f(0.f, 405.f);
	Menu::lowerLine->append(temp);
	temp.position = sf::Vector2f(640.f, 405.f);
	Menu::lowerLine->append(temp);
}

void Menu::updateInput(sf::Event &event, const sf::Vector2i &mousePos)
{
	if(event.type == sf::Event::EventType::KeyPressed and event.key.code == sf::Keyboard::Key::L)
    {
    	//wybor linii
    	Menu::shapeChoice = ShapeType::LINE;
    }
    if(event.type == sf::Event::EventType::KeyPressed and event.key.code == sf::Keyboard::Key::R)
    {
    	//wybor prostokata
    	Menu::shapeChoice = ShapeType::RECT;
    	std::cout << "Wybrano Prostokat" << std::endl;
    }
    if(event.type == sf::Event::EventType::KeyPressed and event.key.code == sf::Keyboard::Key::A)
    {
    	//wybor wypelnionego prostokata
    	Menu::shapeChoice = ShapeType::FRECT;
    }
    if(event.type == sf::Event::EventType::KeyPressed and event.key.code == sf::Keyboard::Key::C)
    {
    	//wybor okregu
    	Menu::shapeChoice = ShapeType::CIRCLE;
    }
    if(event.type == sf::Event::EventType::KeyPressed and event.key.code == sf::Keyboard::Key::W)
    {
    	//screenshot	
    }
    if(event.type == sf::Event::EventType::KeyPressed and event.key.code == sf::Keyboard::Key::O)
	{
		//wczytanie z pliku	
	}
	if(event.type == sf::Event::EventType::MouseButtonPressed and event.mouseButton.button == sf::Mouse::Button::Left)
	{
	
	}
}//method

void Menu::update(const float &deltaTime, const sf::Vector2i &mousePos)
{

}

void Menu::render(sf::RenderTarget *target)
{
	target->draw(Menu::lineText);
	target->draw(Menu::rectText);
	target->draw(Menu::filledRectText);
	target->draw(Menu::circleText);
	target->draw(Menu::screenshotText);
	target->draw(Menu::readFileText);
	target->draw(*Menu::lowerLine);

	for(auto &i : Menu::rects)
		target->draw(*i);

	for(auto &i : Menu::circles)
		target->draw(*i);

	for(auto &i : Menu::lines)
		target->draw(*i);

}