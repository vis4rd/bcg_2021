#include "include/DCircle.h"

int main()
{
	sf::Clock clock;
	unsigned int FPS = 0 , frame_counter = 0;

	sf::RenderWindow window(sf::VideoMode(1280, 720), "GFK Lab 02", sf::Style::Titlebar | sf::Style::Close);
	Panel satPanel(sf::Vector2f(1000.f, 100.f), sf::Vector2f(50.f, 400.f));

	sf::RectangleShape background(sf::Vector2f(1280.f, 720.f));
	background.setPosition(sf::Vector2f(0.f, 0.f));
	background.setFillColor(sf::Color::White);

	sf::Font font;
	font.loadFromFile("../resources/consola.ttf");
	sf::Text fpsCount("FPS: ", font, 15);
	fpsCount.setFillColor(sf::Color::Black);
	fpsCount.setPosition(sf::Vector2f(1000.f, 510.f));
	sf::Text value("VALUE: ", font, 15);
	value.setFillColor(sf::Color::Black);
	value.setPosition(sf::Vector2f(1000.f, 535.f));
	sf::Text hslText("HSL", font, 15);
	hslText.setFillColor(sf::Color::Black);
	hslText.setPosition(sf::Vector2f(100.f, 100.f));
	sf::Text hsvText("HSV", font, 15);
	hsvText.setFillColor(sf::Color::Black);
	hsvText.setPosition(sf::Vector2f(400.f, 100.f));
	sf::Text cmyText("CMY", font, 15);
	cmyText.setFillColor(sf::Color::Black);
	cmyText.setPosition(sf::Vector2f(100.f, 400.f));
	sf::Text rgbText("RGB", font, 15);
	rgbText.setFillColor(sf::Color::Black);
	rgbText.setPosition(sf::Vector2f(400.f, 400.f));
	sf::Text lvalText("L=0.0", font, 15);
	lvalText.setFillColor(sf::Color::Black);
	lvalText.setPosition(sf::Vector2f(340.f, 340.f));
	sf::Text vvalText("V=0.0", font, 15);
	vvalText.setFillColor(sf::Color::Black);
	vvalText.setPosition(sf::Vector2f(640.f, 340.f));
	sf::Text yvalText("Y=0%", font, 15);
	yvalText.setFillColor(sf::Color::Black);
	yvalText.setPosition(sf::Vector2f(340.f, 640.f));
	sf::Text bvalText("B=0", font, 15);
	bvalText.setFillColor(sf::Color::Black);
	bvalText.setPosition(sf::Vector2f(640.f, 640.f));

	DCircle HSL(sf::Vector2f(100.f, 100.f), 120.f);
	HSL.fillHSL();

	DCircle HSV(sf::Vector2f(400.f, 100.f), 120.f);
	HSV.fillHSV();

	DCircle CMY(sf::Vector2f(100.f, 400.f), 120.f);
	CMY.fillCMY();

	DCircle RGB(sf::Vector2f(400.f, 400.f), 120.f);
	RGB.fillRGB();

	//inicjalizacja 
	clock.restart().asMilliseconds();
	while (window.isOpen())
	{
		sf::Event event;
		window.clear(sf::Color::White);

		while (window.pollEvent(event))
		{
		// zdarzenia
			if(event.type == sf::Event::Closed) 
				window.close();

			satPanel.update(sf::Mouse::getPosition(window), &event);
			value.setString("VALUE: "+std::to_string(satPanel.getSetting()));
			HSL.update(satPanel.getSetting());
			HSL.fillHSL();
			HSV.update(satPanel.getSetting());
			HSV.fillHSV();
			CMY.update(satPanel.getSetting());
			CMY.fillCMY();
			RGB.update(satPanel.getSetting());
			RGB.fillRGB();
			lvalText.setString("L="+std::to_string(satPanel.getSetting()));
			vvalText.setString("V="+std::to_string(satPanel.getSetting()));
			yvalText.setString("Y="+std::to_string(static_cast<int>(satPanel.getSetting()*100.0))+"%");
			bvalText.setString("B="+std::to_string(static_cast<int>(satPanel.getSetting()*255.0)));
		}
		//tu wyrysować wszystko na ekran
		window.draw(background);
		satPanel.render(&window);
		window.draw(value);
		HSL.render(&window);
		HSV.render(&window);
		CMY.render(&window);
		RGB.render(&window);
		window.draw(hslText);
		window.draw(hsvText);
		window.draw(cmyText);
		window.draw(rgbText);
		window.draw(lvalText);
		window.draw(vvalText);
		window.draw(yvalText);
		window.draw(bvalText);

		//tu wypisać na ekran wartość FPS
		window.draw(fpsCount);
		if (clock.getElapsedTime().asSeconds() >= 1.0f)
		{
			FPS = (unsigned int)((float)frame_counter / clock.getElapsedTime().asSeconds());
			fpsCount.setString("FPS: "+std::to_string(FPS));
			clock.restart();
			frame_counter = 0;
		}
		frame_counter++;

		window.display();
	}
	return 0;
}