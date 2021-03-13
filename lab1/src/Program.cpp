#include "Program.h"

Program::Program()
{
	this->initWindow();
}

Program::~Program()
{
	if(this->window)
		delete this->window;

    std::cout <<"Ending Application" << std::endl;
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
        Menu::updateInput(this->event);
    }
}

void Program::update()
{
	this->updateDeltaTime();
	this->updateSFMLEvents();	
}

void Program::render()
{
	this->window->clear();
  
    //contents

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