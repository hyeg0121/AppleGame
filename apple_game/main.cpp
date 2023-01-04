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
	int is_cleared;		//�̹� ������ �������
	int idx;			//����� �ε���
	int score;			//����
};

enum Progress {
	START,
	ONGOING,
	END
};

int main(void)
{
	enum Progress progress;
	progress = ONGOING;

	/* window*/
	RenderWindow window(VideoMode(W_WIDTH, W_HEIGHT), "AppleGame");
	window.setFramerateLimit(60);

	/* mouse */
	Vector2i mouse_pos;

	/* variable */
	srand(time(0));
	long start_time;
	long spent_time;
	int is_gameover = 0;	//���ӿ��� ����
	int score = 0;		//���� ���ھ�
	int click_cnt = 0;		//�޺� ȿ���� �ֱ� ���� Ŭ�� Ƚ��
	int judge = 0;			//���ڰ� 10�� �Ǵ��� �Ǵ��ϴ� ����

	/* Font */
	Font font;
	font.loadFromFile("c:/Windows/Fonts/ENCOBK.ttf");

	/* Text */
	Text text;
	text.setCharacterSize(30);
	text.setPosition(100, 20);
	text.setFillColor(Color::White);
	text.setOutlineThickness(3);
	text.setOutlineColor(Color::Black);
	text.setFont(font);
	char info[100];

	/* Sound */
	SoundBuffer click_sb;
	click_sb.loadFromFile("./resources/sounds/click.ogg");
	Sound click_sound;
	click_sound.setBuffer(click_sb);
	click_sound.setVolume(70);

	/* gameover */
	RectangleShape gameover_stripe;
	Texture gameover_texture;
	gameover_texture.loadFromFile("./resources/images/gameover.png");
	gameover_stripe.setPosition(150, 150);
	gameover_stripe.setSize(Vector2f(700, 700));
	gameover_stripe.setTexture(&gameover_texture);

	/* background */
	RectangleShape background_stripe;
	Texture background_texture;
	background_texture.loadFromFile("./resources/images/background.png");
	background_stripe.setPosition(0, 0);
	background_stripe.setSize(Vector2f(W_WIDTH, W_HEIGHT));
	background_stripe.setTexture(&background_texture);

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
		apples[i].is_cleared = 0;
		apples[i].num = rand() % 9 + 1;
		apples[i].score = 10;

		//sprite
		apples[i].sprite.setTexture(&apple_texture[apples[i].num - 1]);
		apples[i].sprite.setSize(Vector2f(A_WIDTH, A_HEIGHT));
		if (i % 9 == 0) //10��° ������� �ٳ���
			enter += 90;
		apples[i].sprite.setPosition(90 + (i % 9) * A_WIDTH, enter);
	}
	
	start_time = clock();

	/* ���α׷� ���� �� */
	while (window.isOpen())
	{
		switch (progress) {
		case 0:
			break;
		//���� ���� ��
		case 1:
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
						for (int i = 0; i < A_AMOUNT; i++)
						{
							//����� Ŭ���ߴٸ�
							if (apples[i].sprite.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y))
							{
								apples[i].sprite.setFillColor(Color::Red);
								apples[i].is_clicked = 1;
								judge += apples[i].num;
								++click_cnt;
								click_sound.play();
							}
						}
					}
				default:
					break;
				}
			}

			/* apple update */
			//���� ���� ����� Ŭ�� �� ���� 
			if (judge == 10)
			{
				for (int i = 0; i < A_AMOUNT; i++)
				{
					if (apples[i].is_clicked)
					{
						apples[i].is_cleared = 1;
						apples[i].is_clicked = 0;
					}
					score += apples[i].score * click_cnt;
				}
				judge = 0;
				click_cnt = 0;
			}
			else if (judge > 10) {
				for (int i = 0; i < A_AMOUNT; i++)
				{
					apples[i].is_clicked = 0;
					apples[i].sprite.setFillColor(Color::White);
				}
				judge = 0;
				click_cnt = 0;
			}

			/* gameover */
			if (TIME_LIMIT - spent_time / 1000 <= 0)
			{
				is_gameover = 1;
			}

			/* info update */
			sprintf_s(info, "TIME : %2d\nSCORE : %d", TIME_LIMIT - spent_time / 1000, score);
			text.setString(info);

			/* draw */
			window.clear(Color::White);
			window.draw(background_stripe);

			for (int i = 0; i < A_AMOUNT; i++)
			{
				if (apples[i].is_cleared == 0)
					window.draw(apples[i].sprite);
			}

			if (is_gameover)
			{
				window.draw(gameover_stripe);
				sprintf_s(info, "SCORE : %d", score);
				text.setString(info);
				text.setPosition(400, 600);

			}
			window.draw(text);
			window.display();
		}
			break;
		case 2:
			break;
		}
		
	}

	return 0;
}