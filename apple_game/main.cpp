#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

using namespace sf;

const int W_WIDTH = 1000, W_HEIGHT = 1000;	//�������� ũ��
const int A_WIDTH = 25, A_HEIGHT = 25;		//����� ũ��
const int A_AMOUNT = 49;					//����� ���� 

struct Apples
{
	RectangleShape sprite;
	int num;			//��� �ȿ� ���ִ� ����
	int is_clicked;		//Ŭ���Ǿ��� �ִ���
	int idx;			//����� �ε���
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