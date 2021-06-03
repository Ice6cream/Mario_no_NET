#include <SFML/Graphics.hpp>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <map>
#include "Player.h" 
using namespace sf;
using namespace std;



//�������, ��������� ��� ���������� ���� ��������
int BackgroungSpritesQuantity(int WindowSideSize) {
	WindowSideSize = WindowSideSize / 64;
	return WindowSideSize;
}

//������� �������
int main()
{
	int W_Length = 624, W_Width = 432; //���������� ��� ������� ����

	bool Rotation = 1; //��������������� ���������� ��� ��������������� ��������
	
	Clock clock; // �����

	float frame = 0; // �����

	bool Ground = 1; //��������������� ��������� ��� 

	//���������� ��� ������������ ������������� ��������
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


	RenderWindow LVLwindow(VideoMode(W_Length, W_Width), "Mario_no_net"); //�������� ������� ������ RenderWindow, � ������� ������������ 2d �������

	Texture PinkManFall; // �������� ������� ������
	PinkManFall.loadFromFile("C:\\Users\\andry\\Desktop\\Mario_no_net\\Free\\Pink Man\\Fall.png");
	
	//C������� ������ �������� �����
	Texture PinkManStop;
	PinkManStop.loadFromFile("C:\\Users\\andry\\Desktop\\Mario_no_net\\Free\\Pink Man\\Idle (32x32).png");
	Texture PinkManRun;
	PinkManRun.loadFromFile("C:\\Users\\andry\\Desktop\\Mario_no_net\\Free\\Pink Man\\Run (32x32).png");
	Sprite PinkMan;
	PinkMan.setTexture(PinkManStop);
	PinkMan.setTextureRect(IntRect(0, 0, 32, 32));
	
	//�������� ������� �������� ����
	Texture MainScene;
	MainScene.loadFromFile("C:\\Users\\andry\\Desktop\\Mario_no_net\\Free\\Background\\Brown.png");
	Sprite Background;
	Background.setTexture(MainScene);

	//�������� ������� ������ �����
	Texture TaleWall;
	TaleWall.loadFromFile("C:\\Users\\andry\\Desktop\\Mario_no_net\\Free\\Terrain\\Terrain (16x16).png");
	Sprite TaleMap;
	TaleMap.setTexture(TaleWall);
	TaleMap.setTextureRect(IntRect(0, 64, 48, 48));

	//�������� ������� ���������
	Texture TalePlat;
	TalePlat.loadFromFile("C:\\Users\\andry\\Desktop\\Mario_no_net\\Free\\Terrain\\Terrain (16x16).png");
	Sprite Platform;
	Platform.setTexture(TalePlat);
	Platform.setTextureRect(IntRect(96, 64, 48, 48));

	//�������� ������� ������
	Texture StartN;
	StartN.loadFromFile("C:\\Users\\andry\\Desktop\\Mario_no_net\\Free\\Items\\Checkpoints\\Start\\Start (idle).png");
	Sprite Start;
	Start.setTexture(StartN);
	
	PinkMan.setPosition(50, 200); //��������� ������ ������

	//����, ���������� ���� ���� �������
	while (LVLwindow.isOpen())
	{
		float time = clock.getElapsedTime().asMilliseconds(); //����������, ����������� ����� � ���������� ����
		clock.restart(); //������� ���������� �����

		Event event;
		while (LVLwindow.pollEvent(event)) //����� pollEvent(event) ���������� �������, ������������ � ����
		{
			if (event.type == Event::Closed) //�������� ����
				LVLwindow.close();
		}
			
		//������� ��� �������� �����
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

		//Keyboard::isKeyPressed - ��������� ������� "������� �������"
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

		LVLwindow.clear(); //�������� ����

		//��������� ���������� ���� 
		for (int i = 0; i < BackgroungSpritesQuantity(W_Length); i++) {
			for (int k = 0; k < BackgroungSpritesQuantity(W_Width); k++) {
				Background.setPosition(i * 64, k * 64);
				LVLwindow.draw(Background);
				};
				
				
				
		}

		//��������� ������ ����
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
		
		LVLwindow.draw(PinkMan); //��������� ���������
		LVLwindow.display(); //���������� ����
	}

	return 0;
}