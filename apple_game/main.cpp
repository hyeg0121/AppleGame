#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

using namespace sf;

const int W_WIDTH = 1000, W_HEIGHT = 1000;

int main(void)
{
	/* window*/
	RenderWindow window(VideoMode(W_WIDTH, W_HEIGHT), "AppleGame");
	window.setFramerateLimit(60);

	/* mouse */
	Vector2i mouse_pos;

	/* ���α׷� ���� �� */
	while (window.isOpen())
	{
		/* mouse update */
		mouse_pos = Mouse::getPosition(window);

		/* event */
		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				//����
			case Event::Closed:
				window.close();
				//���콺 ��Ŭ�� 
			case Event::MouseButtonPressed:
				if (event.mouseButton.button == Mouse::Left)
				{

				}
			default:
				break;
			}
		}

		window.clear(Color::White);

		window.display();
	}

	return 0;
}