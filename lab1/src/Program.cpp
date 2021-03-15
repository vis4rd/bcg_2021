#include "Program.h"

Program::Program()
{
	this->initWindow();
    Menu::init();
}

Program::~Program()
{
	if(this->window)
		delete this->window;
}


void Program::initWindow()
{
    sf::VideoMode window_bounds(640, 480);

    this->window = new sf::RenderWindow(window_bounds, "GFK Lab1", sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(30);
    this->window->setVerticalSyncEnabled(false);
}

void Program::updateDeltaTime()
{
	this->deltaTime = this->dtClock.restart().asSeconds();
}

void Program::updateSFMLEvents()
{
	while(this->window->pollEvent(this->event))
    {
    	if(this->event.type == sf::Event::Closed)
    		this->window->close();
        if(this->event.type == sf::Event::EventType::KeyPressed and this->event.key.code == sf::Keyboard::Key::Escape)
            this->window->close();
        Menu::updateInput(this->event, sf::Mouse::getPosition(*this->window));
    }
}

void Program::update()
{
	this->updateDeltaTime();
	this->updateSFMLEvents();
    Menu::update(this->deltaTime, sf::Mouse::getPosition(*this->window));	
}

void Program::render()
{
	this->window->clear();
    ////
    Menu::render(this->window);
    ////
    this->window->display();
}

void Program::run()
{
	while(this->window->isOpen())
    {
        this->update();
        this->render();
    }
}