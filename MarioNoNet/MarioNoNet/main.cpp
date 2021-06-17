#include <SFML/Graphics.hpp>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <map>
#include "Texture.h" 
#include <SFML/Audio.hpp>

using namespace sf;
using namespace std;


/* Класс персонажа, содержащий переменные для описания движения, а также описывающий движение на плоскости:
x,y - координаты персонажа на плоскости;
u_x, u_y - проекции скоросоти на ось x и ось y соотвественно
ground - переменная, показывающая, находится персонаж на земле или нет
функция move - функция, описывающая движение персонажа, исходя и параметров скоростей
*/
class MainPerson
{
public:
	float x, y, u_x, u_y;
	bool ground;
	
	/*код для передвижения внутри функции move частично был взят и переделан с форума, а именно передвижение по вертикали*/
	void move(float time) {
		x += u_x * time; //Меремещение по x
		if (!ground) u_y = u_y + 0.0012 * time; //Описывает падение
		y += u_y * time;//Перемещение по y

		ground = false;

		if (y > 352) {      //Установка пола, нижней границы мира
			y = 352;
			u_y = 0;
			ground = true;
		}
		
	}

};


//Функция, для деления окна на плитки по 64 пикселя, для заполнения фона
int BackgroungSpritesQuantity(int WindowSideSize) {
	WindowSideSize = WindowSideSize / 64;
	return WindowSideSize;
}


//Главная функция
int main()
{

	Music music;
	music.openFromFile("C:\\Users\\andry\\Desktop\\Mario_no_net\\Фон.ogg");
	music.play(); //проигрывание музыки
	music.setLoop(true); //включение повтора, после прекращения
	music.setVolume(30); //установка громкости музыки

	SoundBuffer shootBuffer;//буфер для звука
	shootBuffer.loadFromFile("C:\\Users\\andry\\Desktop\\Mario_no_net\\Прыжок.ogg");//загрузка звука
	Sound shoot(shootBuffer);//создаем звука

	SoundBuffer shootBuffer1;//буфер для звука
	shootBuffer1.loadFromFile("C:\\Users\\andry\\Desktop\\Mario_no_net\\Сбор.ogg");//загрузка звука
	Sound shoot1(shootBuffer1);//создаем звука

	MainPerson PMan; //Переменная-персонаж
	/*Установка начальных парамеров, скорости и спавн*/
	PMan.u_x = 0;
	PMan.u_y = 0;
	PMan.x = 50;
	PMan.y = 150;

	TXTR texture;
	texture.txtr(); //Загрука всех текстур
	
	int W_Length = 624, W_Width = 432; //Переменные для размера окна

	bool Rotation = 1; //Вспомогательная переменная для переворацивания анимации
	
	Clock clock; // Время

	float frame = 0; // Кадры

	float frame2 = 0; // Вспомогательная переменная кадров

	bool Ground = false; //Вспомогательная переменна для 


	//Переменная для расположения внутреигровых объектов или просто карта
	String MapLVL[13] = { // S - стартовый флажок
	"         ",          // N - платформа1
	"      SN ",		  // C - Confetti
	"       N ",
	"   N     ",
	"         ",
	"         ",
	"     N   ",
	"     N   ",
	"    CN   ",
	"      N  ",
	"     N   ",
	"         ",
	"         ",
	};


	RenderWindow LVLwindow(VideoMode(W_Length, W_Width), "Mario_no_net"); //Создание объекта класса RenderWindow, в котором отображается 2d графика

	//Создание спрайта бонуса
	Sprite Conft;
	Conft.setTexture(texture.Confetti);
	
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
	

	//Цикл, работающий пока окно открыто
	while (LVLwindow.isOpen())
	{
		/*Идея с взята с форума(честно, не помню какого). Код ниже, до "------------" взят оттуда*/
		float time = clock.getElapsedTime().asMilliseconds(); //Переменная, считывающая время с последнего тика
		clock.restart(); //Рестарт переменной время

		frame += 0.02*time; //Счетчик кадров
		/*------------*/

		frame2 += 0.005*time; //Дополнительный счетчик кадров

		/*Условия для смены кадров анимации покоя*/
		if (int(frame2) % 5 == 0) Conft.setTextureRect(IntRect(0, 0, 16, 16));
		if (int(frame2) % 5 == 1) Conft.setTextureRect(IntRect(16, 0, 16, 16));
		if (int(frame2) % 5 == 2) Conft.setTextureRect(IntRect(32, 0, 16, 16));
		if (int(frame2) % 5 == 3) Conft.setTextureRect(IntRect(48, 0, 16, 16));
		if (int(frame2) % 5 == 4) Conft.setTextureRect(IntRect(64, 0, 16, 16));

		Event event; // переменная типа "событие в окне"
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
			///PinkMan.move(-0.2*time, 0);
			PMan.u_x = -0.2; //передача отрицательной проекции скорости по x

			Rotation = 0; //Установка поворота

			//Анимация движения влево
			if (frame > 12) frame = frame -12;
			PinkMan.setTexture(texture.PinkManRun);
			PinkMan.setTextureRect(IntRect(32 + 32 * int(frame), 0, -32, 32));
		}

		if (Keyboard::isKeyPressed(Keyboard::D)) {
			///PinkMan.move(0.2*time, 0);
			PMan.u_x = 0.2; //передача положительной проекции скорости по x

			Rotation = 1;//Установка поворота
		
			//Анимация движения вправо
			if (frame > 12) frame = frame - 12;
			PinkMan.setTexture(texture.PinkManRun);
			PinkMan.setTextureRect(IntRect(0 + 32 * int(frame), 0, 32, 32));
		}

		

		if (Keyboard::isKeyPressed(Keyboard::W)) {

			if (PMan.ground) { //условие прыжка: если перс на земле, можно прыгать
				shoot.play(); //проигрывание звука прыжка
				PMan.u_y = -0.5;// установка проекции скорости по y
				PMan.ground = false;
			}
		
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
				Conft.setPosition(i * 48, k * 48);
				if (MapLVL[i][k] == 'N') LVLwindow.draw(Platform);
				if (MapLVL[i][k] == 'S') LVLwindow.draw(Start);
				if (MapLVL[i][k] == 'C') LVLwindow.draw(Conft);
			};
		}
		
		PMan.move(time); //запуск функции передвижения
		PinkMan.setPosition(PMan.x, PMan.y); //перемещение персонажа
		PMan.u_x = 0; 

		/*Расчитывание столкновения с объектами
		Происходит проверка, находится персонаж хотя бы частитчно в клеткеб
		где есть игровой объект*/
		for (int i = PMan.x / 48; i < (PMan.x + 32) / 48; i++) {
			for (int k = PMan.y / 48; k < (PMan.y + 32) / 48; k++) {
				if (MapLVL[i][k] == 'N') //Проверка столкновения с платформой
				{
					{

						if (PMan.u_x > 0) PMan.x = i * 48 - 32;
						if (PMan.u_x < 0) PMan.x = i * 48 + 32;

						if (PMan.u_y > 0) { PMan.y = k * 48 - 32;  PMan.u_y = 0;   PMan.ground = true; }
						if (PMan.u_y < 0) { PMan.y = k * 48 + 32;   PMan.u_y = 0; }
					}
				}
				if (MapLVL[i][k] == 'C') //Проверка столкновения с бонусом
				{
					shoot1.play(); //Проигрывание звука сбора бонуса
					MapLVL[i][k] = ' ';
				}
			}
		}

		LVLwindow.draw(PinkMan); //Отрисовка персонажа
		LVLwindow.display(); //Отричсовка окна
	}

	return 0;
}