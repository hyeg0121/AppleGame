#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

using namespace sf;

const int W_WIDTH = 1000, W_HEIGHT = 1000;	//윈도우의 크기
const int A_WIDTH = 25, A_HEIGHT = 25;		//사과의 크기
const int A_AMOUNT = 49;					//사과의 개수 

struct Apples
{
	RectangleShape sprite;
	int num;			//사과 안에 써있는 숫자
	int is_clicked;		//클릭되어져 있는지
	int idx;			//사과의 인덱스
};

int main(void)
{
	/* window*/
	RenderWindow window(VideoMode(W_WIDTH, W_HEIGHT), "AppleGame");
	window.setFramerateLimit(60);

	/* mouse */
	Vector2i mouse_pos;

	/* apple */
	Texture apple_texture[9];
	char file_name[50];
	for (int i = 0; i < 9; i++)
	{
		sprintf_s(file_name, "./resources/images/apple%d.png", i + 1);
		apple_texture[i].loadFromFile(file_name);

	}
	/* 프로그램 실행 중 */
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
				//종료
			case Event::Closed:
				window.close();
				//마우스 좌클릭 
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