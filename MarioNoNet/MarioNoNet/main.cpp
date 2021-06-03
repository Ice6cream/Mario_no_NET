#include <SFML/Graphics.hpp>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <map>
#include "Player.h" 
using namespace sf;
using namespace std;



//Функция, созданная для заполнения окна плитками
int BackgroungSpritesQuantity(int WindowSideSize) {
	WindowSideSize = WindowSideSize / 64;
	return WindowSideSize;
}

//Главная функция
int main()
{
	int W_Length = 624, W_Width = 432; //Переменные для размера окна

	bool Rotation = 1; //Вспомогательная переменная для переворацивания анимации
	
	Clock clock; // Время

	float frame = 0; // Кадры

	bool Ground = 1; //Вспомогательная переменна для 

	//Переменная для расположения внутреигровых объектов
	String MapLVL[13] = {
	"         ",
	"      SN ",
	"       N ",
	"         ",
	"         ",
	"    NN   ",
	"     N   ",
	"     N   ",
	"         ",
	"         ",
	"         ",
	"         ",
	"         ",
	};


	RenderWindow LVLwindow(VideoMode(W_Length, W_Width), "Mario_no_net"); //Создание объекта класса RenderWindow, в котором отображается 2d графика

	Texture PinkManFall; // Тектрура падения игрока
	PinkManFall.loadFromFile("C:\\Users\\andry\\Desktop\\Mario_no_net\\Free\\Pink Man\\Fall.png");
	
	//Cоздание спрата главного героя
	Texture PinkManStop;
	PinkManStop.loadFromFile("C:\\Users\\andry\\Desktop\\Mario_no_net\\Free\\Pink Man\\Idle (32x32).png");
	Texture PinkManRun;
	PinkManRun.loadFromFile("C:\\Users\\andry\\Desktop\\Mario_no_net\\Free\\Pink Man\\Run (32x32).png");
	Sprite PinkMan;
	PinkMan.setTexture(PinkManStop);
	PinkMan.setTextureRect(IntRect(0, 0, 32, 32));
	
	//Создание спрайта главного меню
	Texture MainScene;
	MainScene.loadFromFile("C:\\Users\\andry\\Desktop\\Mario_no_net\\Free\\Background\\Brown.png");
	Sprite Background;
	Background.setTexture(MainScene);

	//Создание спрайта стенки карты
	Texture TaleWall;
	TaleWall.loadFromFile("C:\\Users\\andry\\Desktop\\Mario_no_net\\Free\\Terrain\\Terrain (16x16).png");
	Sprite TaleMap;
	TaleMap.setTexture(TaleWall);
	TaleMap.setTextureRect(IntRect(0, 64, 48, 48));

	//Создание спрайта платформы
	Texture TalePlat;
	TalePlat.loadFromFile("C:\\Users\\andry\\Desktop\\Mario_no_net\\Free\\Terrain\\Terrain (16x16).png");
	Sprite Platform;
	Platform.setTexture(TalePlat);
	Platform.setTextureRect(IntRect(96, 64, 48, 48));

	//Создание спрайта старта
	Texture StartN;
	StartN.loadFromFile("C:\\Users\\andry\\Desktop\\Mario_no_net\\Free\\Items\\Checkpoints\\Start\\Start (idle).png");
	Sprite Start;
	Start.setTexture(StartN);
	
	PinkMan.setPosition(50, 200); //установка спавна игрока

	//Цикл, работающий пока окно открыто
	while (LVLwindow.isOpen())
	{
		float time = clock.getElapsedTime().asMilliseconds(); //Переменная, считывающая время с последнего тика
		clock.restart(); //Рестарт переменной время

		Event event;
		while (LVLwindow.pollEvent(event)) //Метод pollEvent(event) перебирает собития, происходящие в окне
		{
			if (event.type == Event::Closed) //Закрытие окна
				LVLwindow.close();
		}
			
		//Условие для анимации покоя
		frame += 0.02*time;
		if (frame > 11) frame = frame - 11;
		PinkMan.setTexture(PinkManStop);
		if (Rotation)
		PinkMan.setTextureRect(IntRect(0 + 32 * int(frame), 0, 32, 32));
		else PinkMan.setTextureRect(IntRect(32 + 32 * int(frame), 0, -32, 32));

		//if () Ground = 0;
		//else Ground = 1;

		//if (Ground) {
		//	PinkMan.setTexture(PinkManFall);
		//	PinkMan.move(0, 0.1*time);
		//}

		//Keyboard::isKeyPressed - обработка события "нажатие клавиши"
		if (Keyboard::isKeyPressed(Keyboard::A)) {
			PinkMan.move(-0.2*time, 0);

			Rotation = 0;

			if (frame > 12) frame = frame -12;
			PinkMan.setTexture(PinkManRun);
			PinkMan.setTextureRect(IntRect(32 + 32 * int(frame), 0, -32, 32));
		}

		if (Keyboard::isKeyPressed(Keyboard::D)) {
			PinkMan.move(0.2*time, 0);

			Rotation = 1;
		
			if (frame > 12) frame = frame - 12;
			PinkMan.setTexture(PinkManRun);
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
				if (MapLVL[i][k] == 'N') LVLwindow.draw(Platform);
				if (MapLVL[i][k] == 'S') LVLwindow.draw(Start);
			};
		}
		
		LVLwindow.draw(PinkMan); //Отрисовка персонажа
		LVLwindow.display(); //Отричсовка окна
	}

	return 0;
}