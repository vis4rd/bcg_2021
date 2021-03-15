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
sf::Text Menu::exitText = sf::Text();
sf::VertexArray *Menu::lowerLine = nullptr;
sf::VertexArray *Menu::colorPanel1 = nullptr;
sf::VertexArray *Menu::colorPanel2 = nullptr;
std::list<DShape *> Menu::shapes = {};
sf::Color Menu::outlineColor = sf::Color::Red;
sf::Color Menu::fillColor = sf::Color::Transparent;

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
	Menu::exitText.setFont(*Menu::font);

	Menu::lineText.setCharacterSize(size);
	Menu::rectText.setCharacterSize(size);
	Menu::filledRectText.setCharacterSize(size);
	Menu::circleText.setCharacterSize(size);
	Menu::screenshotText.setCharacterSize(size);
	Menu::readFileText.setCharacterSize(size);
	Menu::exitText.setCharacterSize(size);

	Menu::lineText.setFillColor(color);
	Menu::rectText.setFillColor(color);
	Menu::filledRectText.setFillColor(color);
	Menu::circleText.setFillColor(color);
	Menu::screenshotText.setFillColor(color);
	Menu::readFileText.setFillColor(color);
	Menu::exitText.setFillColor(color);

	Menu::lineText.setString("<L> Linia");
	Menu::rectText.setString("<R> Prostokat");
	Menu::filledRectText.setString("<A> Wypelniony Prostokat");
	Menu::circleText.setString("<C> Okrag");
	Menu::screenshotText.setString("<W> Zapis Do Pliku");
	Menu::readFileText.setString("<O> Wczytanie Z Pliku");
	Menu::exitText.setString("<Esc> Wyjscie");

	Menu::lineText.setPosition(sf::Vector2f(30.f, 410.f));
	Menu::rectText.setPosition(sf::Vector2f(30.f, 430.f));
	Menu::filledRectText.setPosition(sf::Vector2f(30.f, 450.f));
	Menu::circleText.setPosition(sf::Vector2f(250.f, 410.f));
	Menu::screenshotText.setPosition(sf::Vector2f(250.f, 430.f));
	Menu::readFileText.setPosition(sf::Vector2f(250.f, 450.f));
	Menu::exitText.setPosition(sf::Vector2f(470.f, 410.f));

	Menu::lowerLine = new sf::VertexArray(sf::Lines);
	sf::Vertex temp;
	temp.color = color;
	temp.position = sf::Vector2f(0.f, 405.f);
	Menu::lowerLine->append(temp);
	temp.position = sf::Vector2f(640.f, 405.f);
	Menu::lowerLine->append(temp);

	int red, green, blue;
	int *big, *mid, *small;
	int winX = 640;
	int part = 640* (2.f/3.f);
	Menu::colorPanel1 = new sf::VertexArray(sf::Points); //rect winXx30
	for(int i = 0; i <= winX; i++)
	{
		for(int j = 0; j <= 30; j++)
		{
			if(i < part)
			{
				red = 255 * ((float)i / part);
				green = 255 * ((float)(part - i) / part);
				blue = 0;
			}
			else
			{
				red = 255 * ((float)((winX - part) - (part - i)) / (winX - part));
				green = 0;
				blue = 255 * ((float)(i - part) / (winX - part) * 2.f);
			}
			

			if(red > green)
			{
				if(red > blue)
				{
					big = &red;
					if(green > blue)
					{
						mid = &green;
						small = &blue;
					}//rgb
					else
					{
						mid = &blue;
						small = &green;
					}//rbg
				}
				else
				{
					big = &blue;
					mid = &red;
					small = &green;
				}//brg
			}
			else
			{
				if(green > blue)
				{
					big = &green;
					if(blue > red)
					{
						mid = &blue;
						small = &red;
					}//gbr
					else
					{
						mid = &red;
						small = &blue;
					}//grb
				}
				else
				{
					big = &blue;
					mid = &green;
					small = &red;
				}//bgr
			}

			*small *= ((float)255/(*big));
			*mid *= ((float)255/(*big));
			*big = 255;

			temp.color = sf::Color(red, green, blue);
			temp.position = sf::Vector2f(float(i),float(j));
			Menu::colorPanel1->append(temp);
		}
	}
	
	Menu::colorPanel2 = new sf::VertexArray(sf::Points);
	for(int i = 0; i <= winX; i++)
	{
		for(int j = 0; j <= 30; j++)
		{
			if(i < part)
			{
				red = 0;
				green = 255 * ((float)(part - i) / part);
				blue = 255 * ((float)i / part);
			}
			else
			{
				red = 255 * ((float)(i - part) / (winX - part) * 2.f);
				green = 0;
				blue = 255 * ((float)((winX - part) - (part - i)) / (winX - part));
			}

			if(red > green)
			{
				if(red > blue)
				{
					big = &red;
					if(green > blue)
					{
						mid = &green;
						small = &blue;
					}//rgb
					else
					{
						mid = &blue;
						small = &green;
					}//rbg
				}
				else
				{
					big = &blue;
					mid = &red;
					small = &green;
				}//brg
			}
			else
			{
				if(green > blue)
				{
					big = &green;
					if(blue > red)
					{
						mid = &blue;
						small = &red;
					}//gbr
					else
					{
						mid = &red;
						small = &blue;
					}//grb
				}
				else
				{
					big = &blue;
					mid = &green;
					small = &red;
				}//bgr
			}

			*small *= ((float)255/(*big));
			*mid *= ((float)255/(*big));
			*big = 255;

			temp.color = sf::Color(red, green, blue);
			temp.position = sf::Vector2f(float(i),float(j+30));
			Menu::colorPanel2->append(temp);
		}
	}
}

void Menu::terminate()
{
	if(!Menu::shapes.empty())
		for(auto &it : Menu::shapes)
			delete it;
	Menu::shapes.clear();
	delete Menu::font;
}

void Menu::updateInput(sf::Event &event, const sf::Vector2i &mousePos, sf::Window *window)
{
	if(event.type == sf::Event::EventType::KeyPressed and event.key.code == sf::Keyboard::Key::L)
    {
    	//wybor linii
    	Menu::shapeChoice = ShapeType::LINE;
    	Menu::lineText.setFillColor(Menu::outlineColor);
    	std::cout << "Wybrano Linie" << std::endl;

    	Menu::rectText.setFillColor(sf::Color::White);
    	Menu::filledRectText.setFillColor(sf::Color::White);
    	Menu::circleText.setFillColor(sf::Color::White);
    }
    if(event.type == sf::Event::EventType::KeyPressed and event.key.code == sf::Keyboard::Key::R)
    {
    	//wybor prostokata
    	Menu::shapeChoice = ShapeType::RECT;
    	Menu::rectText.setFillColor(Menu::outlineColor);
    	std::cout << "Wybrano Prostokat" << std::endl;

    	Menu::lineText.setFillColor(sf::Color::White);
    	Menu::filledRectText.setFillColor(sf::Color::White);
    	Menu::circleText.setFillColor(sf::Color::White);
    }
    if(event.type == sf::Event::EventType::KeyPressed and event.key.code == sf::Keyboard::Key::A)
    {
    	//wybor wypelnionego prostokata
    	Menu::shapeChoice = ShapeType::FRECT;
    	Menu::filledRectText.setFillColor(Menu::outlineColor);
    	std::cout << "Wybrano Wypelniony Prostokat" << std::endl;

    	Menu::lineText.setFillColor(sf::Color::White);
    	Menu::rectText.setFillColor(sf::Color::White);
    	Menu::circleText.setFillColor(sf::Color::White);
    }
    if(event.type == sf::Event::EventType::KeyPressed and event.key.code == sf::Keyboard::Key::C)
    {
    	//wybor okregu
    	Menu::shapeChoice = ShapeType::CIRCLE;
    	Menu::circleText.setFillColor(Menu::outlineColor);
    	std::cout << "Wybrano Okrag" << std::endl;

    	Menu::lineText.setFillColor(sf::Color::White);
    	Menu::rectText.setFillColor(sf::Color::White);
    	Menu::filledRectText.setFillColor(sf::Color::White);
    }
    if(event.type == sf::Event::EventType::KeyPressed and event.key.code == sf::Keyboard::Key::W)
    {
    	//screenshot	
    	sf::Texture screenshot;
    	screenshot.create(640, 480);
    	screenshot.update(*window);
    	sf::Image output = screenshot.copyToImage();
    	output.saveToFile("screenshot.png");
    }
    if(event.type == sf::Event::EventType::KeyPressed and event.key.code == sf::Keyboard::Key::O)
	{
		//wczytanie z pliku	
	}
	if(event.type == sf::Event::EventType::MouseButtonPressed and event.mouseButton.button == sf::Mouse::Button::Left)
	{
		if(mousePos.y < 30)//wybor koloru 1
		{
			for(unsigned i = 0; i <= Menu::colorPanel1->getVertexCount(); i++)
			{
				if((*Menu::colorPanel1)[i].position.x == mousePos.x)
				{
					Menu::outlineColor = (*Menu::colorPanel1)[i].color;
					break;
				}
			}
			if(Menu::shapeChoice == ShapeType::LINE)
				Menu::lineText.setFillColor(Menu::outlineColor);
			if(Menu::shapeChoice == ShapeType::RECT)
				Menu::rectText.setFillColor(Menu::outlineColor);
			if(Menu::shapeChoice == ShapeType::FRECT)
				Menu::filledRectText.setFillColor(Menu::outlineColor);
			if(Menu::shapeChoice == ShapeType::CIRCLE)
				Menu::circleText.setFillColor(Menu::outlineColor);
			printf("Wybrano kolor1 (%d, %d, %d)\n", Menu::outlineColor.r, Menu::outlineColor.g, Menu::outlineColor.b);
		}
		else if(mousePos.y < 60)//wybor koloru 2
		{
			for(unsigned i = 0; i <= Menu::colorPanel1->getVertexCount(); i++)
			{
				if((*Menu::colorPanel2)[i].position.x == mousePos.x)
				{
					Menu::fillColor = (*Menu::colorPanel2)[i].color;
					break;
				}
			}
			printf("Wybrano kolor2 (%d, %d, %d)\n", Menu::fillColor.r, Menu::fillColor.g, Menu::fillColor.b);
		}
		else//rysowanie
		{
			if(Menu::state == DrawState::IDLE)//postawienie figury
			{
				if(Menu::shapeChoice == ShapeType::LINE)
					Menu::shapes.emplace_back(new DLine(sf::Vector2f(mousePos.x, mousePos.y), Menu::outlineColor));
				if(Menu::shapeChoice == ShapeType::RECT)
					Menu::shapes.emplace_back(new DRect(sf::Vector2f(mousePos.x, mousePos.y), Menu::outlineColor));
				if(Menu::shapeChoice == ShapeType::FRECT)
					Menu::shapes.emplace_back(new DRect(sf::Vector2f(mousePos.x, mousePos.y), Menu::outlineColor, Menu::fillColor));
				if(Menu::shapeChoice == ShapeType::CIRCLE)
					Menu::shapes.emplace_back(new DCircle(sf::Vector2f(mousePos.x, mousePos.y), Menu::outlineColor));
				Menu::state = DrawState::ACTIVE;
			}
			else//konczenie figury
				Menu::state = DrawState::IDLE;
		}
	}
}//method

void Menu::update(const float &deltaTime, const sf::Vector2i &mousePos)
{
	if(Menu::state == DrawState::ACTIVE)
	{
		sf::Vector2f center = Menu::shapes.back()->getCenter();
		Menu::shapes.back()->setSize(sf::Vector2f(mousePos.x - center.x, mousePos.y - center.y));
		if(Menu::lineText.getFillColor() != sf::Color::White)
			Menu::lineText.setFillColor(sf::Color::White);
		if(Menu::rectText.getFillColor() != sf::Color::White)
			Menu::rectText.setFillColor(sf::Color::White);
		if(Menu::filledRectText.getFillColor() != sf::Color::White)
			Menu::filledRectText.setFillColor(sf::Color::White);
		if(Menu::circleText.getFillColor() != sf::Color::White)
			Menu::circleText.setFillColor(sf::Color::White);
	}
}

void Menu::render(sf::RenderTarget *target)
{
	for(auto &i : Menu::shapes)
		i->render(target);

	target->draw(Menu::lineText);
	target->draw(Menu::rectText);
	target->draw(Menu::filledRectText);
	target->draw(Menu::circleText);
	target->draw(Menu::screenshotText);
	target->draw(Menu::readFileText);
	target->draw(Menu::exitText);
	target->draw(*Menu::lowerLine);
	target->draw(*Menu::colorPanel1);
	target->draw(*Menu::colorPanel2);
}