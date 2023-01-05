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

enum Progress {
	START,
	ONGOING,
	END,
	SHOW_HOWTOPLAY
};

enum ButtonType {
	GAMESTART,
	HOWTOPLAY,
	BACK,
};

struct Apple
{
	RectangleShape sprite;
	int num;			//��� �ȿ� ���ִ� ����
	int is_clicked;		//Ŭ���Ǿ��� �ִ���
	int is_cleared;		//�̹� ������ �������
	int idx;			//����� �ε���
	int score;			//����
};

struct Button {
	RectangleShape sprite;
	enum ButtonType type;
	Texture texture;
};

int main(void)
{
	enum Progress progress;
	progress = START;

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

	/* background */
	RectangleShape background_stripe;
	Texture background_start_texture;
	background_start_texture.loadFromFile("./resources/images/background_start.png");
	Texture background_ongoing_texture;
	background_ongoing_texture.loadFromFile("./resources/images/background_ongoing.png");
	Texture background_end_texture;
	background_end_texture.loadFromFile("./resources/images/background_end.png");
	Texture background_show_texture;
	background_show_texture.loadFromFile("./resources/images/background_show_howtoplay.png");
	background_stripe.setPosition(0, 0);
	background_stripe.setSize(Vector2f(W_WIDTH, W_HEIGHT));
	background_stripe.setTexture(&background_start_texture);

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
		if (i % 9 == 0) //9��° ������� �ٳ���
			enter += 90;
		apples[i].sprite.setPosition(90 + (i % 9) * A_WIDTH, enter);
	}

	/* Button */
	struct Button btn[3];
	//���� ��ư
	btn[0].texture.loadFromFile("./resources/images/game_start.png");
	btn[0].type = GAMESTART;
	//���� ���� ��ư
	btn[1].texture.loadFromFile("./resources/images/show_howtoplay.png");
	btn[1].type = HOWTOPLAY;
	//�ڷΰ���
	btn[2].texture.loadFromFile("./resources/images/back.png");
	btn[2].type = BACK;
	for (int i = 0; i < 3; i++)
	{
		btn[i].sprite.setPosition(200 + i * 320, 500);
		btn[i].sprite.setSize(Vector2f(300, 300));
		btn[i].sprite.setTexture(&btn[i].texture);
	}
	btn[2].sprite.setSize(Vector2f(600, 200));

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
				switch (progress)
				{
				case 0:
				{
					for (int i = 0; i < 2; i++)
					{
						//��ư�� Ŭ���ߴٸ�
						if (btn[i].sprite.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y))
						{
							switch (btn[i].type)
							{
							case GAMESTART:
								progress = ONGOING;
								break;
							case HOWTOPLAY:
								progress = SHOW_HOWTOPLAY;
								break;
							}
						}
					}
				}//case 0
				case 1:
				{
					if (event.mouseButton.button == Mouse::Left)
					{
						click_sound.play();
						for (int i = 0; i < A_AMOUNT; i++)
						{
							//����� Ŭ���ߴٸ�
							if (apples[i].sprite.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y))
							{
								apples[i].sprite.setFillColor(Color::Red);
								apples[i].is_clicked = 1;
								judge += apples[i].num;
								++click_cnt;
							}
						}

					}//if
				}
				case 3:
				{
					if (btn[2].sprite.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y))
					{
						progress = START;
					}
					break;
				}
				}//case 3
				default:
					break;
				}//switch
			}//switch
		//while
		switch (progress) {
		//���� ����
		// TODO : ���� ���� �κ� �����ϱ�
		case 0:
			window.clear();
			background_stripe.setTexture(&background_start_texture);
			window.draw(background_stripe);
			window.draw(btn[0].sprite);
			window.draw(btn[1].sprite);
			break;
		//���� ���� ��
		case 1:
		{
			background_stripe.setTexture(&background_ongoing_texture);
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
				progress = END;
			}
			window.draw(text);
			
		}
			break;
		//���� ����
		case 2:
		{
			background_stripe.setTexture(&background_end_texture);

			window.draw(background_stripe);

			sprintf_s(info, "SCORE : %d", score);
			text.setString(info);
			text.setPosition(400, 600);
			window.draw(text);

			if (Keyboard::isKeyPressed(Keyboard::Space))
			{
				progress = START;
			}
			break;
		}
		//SHOW_HOWTOPLAY
		case 3: 
		{
			window.clear();
			background_stripe.setTexture(&background_show_texture);
			window.draw(background_stripe);

			btn[2].sprite.setPosition(200, 800);
			window.draw(btn[2].sprite);

		}
		break;
		}//switch
		window.display();
	}

	return 0;
}