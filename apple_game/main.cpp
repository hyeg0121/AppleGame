#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

using namespace sf;

const int W_WIDTH = 1000, W_HEIGHT = 1000;	//�������� ũ��
const int A_WIDTH = 90, A_HEIGHT = 90;		//����� ũ��
const int A_AMOUNT = 81;					//����� ���� 
const int TIME_LIMIT = 60;					//���ѽð�

struct Apple
{
	RectangleShape sprite;
	int num;			//��� �ȿ� ���ִ� ����
	int is_clicked;		//Ŭ���Ǿ��� �ִ���
	int idx;			//����� �ε���
	int score;			//����
};

int main(void)
{
	/* window*/
	RenderWindow window(VideoMode(W_WIDTH, W_HEIGHT), "AppleGame");
	window.setFramerateLimit(60);

	/* mouse */
	Vector2i mouse_pos;

	/* variable */
	srand(time(0));
	long start_time;
	long spent_time;
	int is_gameover; //���ӿ��� ����
	int score = 0;		 //���� ���ھ�

	/* Font */
	Font font;
	font.loadFromFile("c:/Windows/Fonts/arial.ttf");

	/* Text */
	Text text;
	text.setCharacterSize(30);
	text.setPosition(100, 20);
	text.setFillColor(Color::Red);
	text.setFont(font);
	char info[100];

	/* apple */
	//texture ����
	Texture apple_texture[9];
	char file_name[50];
	for (int i = 0; i < 9; i++)
	{
		sprintf_s(file_name, "./resources/images/apple%d.png", i + 1);
		apple_texture[i].loadFromFile(file_name);

	}
	
	struct Apple apples[A_AMOUNT];
	int enter = 90;
	for (int i = 0; i < A_AMOUNT; i++) 
	{
		apples[i].idx = 0;
		apples[i].is_clicked = 0;
		apples[i].num = rand() % 9 + 1;
		apples[i].score = 0;

		//sprite
		apples[i].sprite.setTexture(&apple_texture[apples[i].num - 1]);
		apples[i].sprite.setSize(Vector2f(A_WIDTH, A_HEIGHT));
		if (i % 9 == 0) //10��° ������� �ٳ���
			enter += 90;
		apples[i].sprite.setPosition(70 + (i % 9) * A_WIDTH, enter);
	}

	start_time = clock();

	/* ���α׷� ���� �� */
	while (window.isOpen())
	{
		/* mouse update */
		mouse_pos = Mouse::getPosition(window);

		/* time update */
		spent_time = clock() - start_time;

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

		/* info update */
		sprintf_s(info, "TIME : %2d\nSCORE : %d", TIME_LIMIT - spent_time / 1000, score);
		text.setString(info);
		printf("%s", info);

		window.clear(Color::White);

		window.draw(text);

		for (int i = 0; i < A_AMOUNT; i++)
		{
			window.draw(apples[i].sprite);
		}
		window.display();
	}

	return 0;
}