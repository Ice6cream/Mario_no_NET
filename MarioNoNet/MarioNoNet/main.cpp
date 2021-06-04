#include <SFML/Graphics.hpp>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <map>
#include "Player.h" 
#include "Texture.h" 

using namespace sf;
using namespace std;


//Функция, для деления окна на плитки по 64 пикселя, для заполнения фона
int BackgroungSpritesQuantity(int WindowSideSize) {
	WindowSideSize = WindowSideSize / 64;
	return WindowSideSize;
}

//Главная функция
int main()
{
	TXTR texture;
	texture.txtr();

	int W_Length = 624, W_Width = 432; //Переменные для размера окна

	bool Rotation = 1; //Вспомогательная переменная для переворацивания анимации
	
	Clock clock; // Время

	float frame = 0; // Кадры

	bool Ground = 1; //Вспомогательная переменна для 

	//Переменная для расположения внутреигровых объектов
	String MapLVL[13] = { // S - стартовый флажок
	"         ",          // N - платформа1
	"      SN ",		  // C - Confetti
	"       N ",
	"         ",
	"         ",
	"    NN   ",
	"     N   ",
	"     N   ",
	"         ",
	"  N  C   ",
	"  N      ",
	"         ",
	"         ",
	};


	RenderWindow LVLwindow(VideoMode(W_Length, W_Width), "Mario_no_net"); //Создание объекта класса RenderWindow, в котором отображается 2d графика

	//Sprite Confetti;
	//Confetti.setTexture(texture.Confetti);

	//Cоздание спрата главного героя
	Sprite PinkMan;
	PinkMan.setTexture(texture.PinkManStop);
	PinkMan.setTextureRect(IntRect(0, 0, 32, 32));
	
	//Создание спрайта главного меню
	Sprite Background;
	Background.setTexture(texture.MainSceneBrown);

	//Создание спрайта стенки карты
	Sprite TaleMap;
	TaleMap.setTexture(texture.TaleWall);
	TaleMap.setTextureRect(IntRect(0, 64, 48, 48));

	//Создание спрайта платформы
	Sprite Platform;
	Platform.setTexture(texture.TaleWall);
	Platform.setTextureRect(IntRect(96, 64, 48, 48));

	//Создание спрайта старта
	Sprite Start;
	Start.setTexture(texture.StartN);
	
	PinkMan.setPosition(50, 200); //установка спавна игрока

	//Цикл, работающий пока окно открыто
	while (LVLwindow.isOpen())
	{
		float time = clock.getElapsedTime().asMilliseconds(); //Переменная, считывающая время с последнего тика
		clock.restart(); //Рестарт переменной время

		frame += 0.02*time;


		Event event;
		while (LVLwindow.pollEvent(event)) //Метод pollEvent(event) перебирает собития, происходящие в окне
		{
			if (event.type == Event::Closed) //Закрытие окна
				LVLwindow.close();
		}

		//Условие для анимации покоя
		if (frame > 11) frame = frame - 11;
		PinkMan.setTexture(texture.PinkManStop);
		if (Rotation)
		PinkMan.setTextureRect(IntRect(0 + 32 * int(frame), 0, 32, 32));
		else PinkMan.setTextureRect(IntRect(32 + 32 * int(frame), 0, -32, 32));


		//Keyboard::isKeyPressed - обработка события "нажатие клавиши"
		if (Keyboard::isKeyPressed(Keyboard::A)) {
			PinkMan.move(-0.2*time, 0);

			Rotation = 0;

			if (frame > 12) frame = frame -12;
			PinkMan.setTexture(texture.PinkManRun);
			PinkMan.setTextureRect(IntRect(32 + 32 * int(frame), 0, -32, 32));
		}

		if (Keyboard::isKeyPressed(Keyboard::D)) {
			PinkMan.move(0.2*time, 0);

			Rotation = 1;
		
			if (frame > 12) frame = frame - 12;
			PinkMan.setTexture(texture.PinkManRun);
			PinkMan.setTextureRect(IntRect(0 + 32 * int(frame), 0, 32, 32));
		}

		if (Keyboard::isKeyPressed(Keyboard::W)) {
			PinkMan.move(0, -0.1*time);
		}

		LVLwindow.clear(); //Отчистка окна

		//установка бэкграунда окна 
		for (int i = 0; i < BackgroungSpritesQuantity(W_Length); i++) {
			for (int k = 0; k < BackgroungSpritesQuantity(W_Width); k++) {
				Background.setPosition(i * 64, k * 64);
				LVLwindow.draw(Background);
				};
				
				
				
		}

		//Установка стенок лвла
		for (int i = 0; i < W_Length / 48; i++) {
			for (int k = 0; k < W_Width / 48; k++) {
				TaleMap.setPosition(i * 48, k * 48);
				if (i == 0 || i == W_Length/48 -1 || k == 0 || k == W_Width/48 -1 ) LVLwindow.draw(TaleMap);
			};
		}

		for (int i = 0; i < 13; i++) {
			for (int k = 0; k < 9; k++) {
				Platform.setPosition(i * 48, k * 48);
				Start.setPosition(i * 48, k * 48);
				Confetti.setPosition(i * 48, k * 48);
				if (MapLVL[i][k] == 'N') LVLwindow.draw(Platform);
				if (MapLVL[i][k] == 'S') LVLwindow.draw(Start);
				if (MapLVL[i][k] == 'C') LVLwindow.draw(Confetti);
			};
		}
		
		LVLwindow.draw(PinkMan); //Отрисовка персонажа
		LVLwindow.display(); //Отричсовка окна
	}

	return 0;
}