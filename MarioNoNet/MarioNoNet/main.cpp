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


/* ����� ���������, ���������� ���������� ��� �������� ��������, � ����� ����������� �������� �� ���������:
x,y - ���������� ��������� �� ���������;
u_x, u_y - �������� ��������� �� ��� x � ��� y �������������
ground - ����������, ������������, ��������� �������� �� ����� ��� ���
������� move - �������, ����������� �������� ���������, ������ � ���������� ���������
*/
class MainPerson
{
public:
	float x, y, u_x, u_y;
	bool ground;
	
	/*��� ��� ������������ ������ ������� move �������� ��� ���� � ��������� � ������, � ������ ������������ �� ���������*/
	void move(float time) {
		x += u_x * time; //����������� �� x
		if (!ground) u_y = u_y + 0.0012 * time; //��������� �������
		y += u_y * time;//����������� �� y

		ground = false;

		if (y > 352) {      //��������� ����, ������ ������� ����
			y = 352;
			u_y = 0;
			ground = true;
		}
		
	}

};


//�������, ��� ������� ���� �� ������ �� 64 �������, ��� ���������� ����
int BackgroungSpritesQuantity(int WindowSideSize) {
	WindowSideSize = WindowSideSize / 64;
	return WindowSideSize;
}


//������� �������
int main()
{

	Music music;
	music.openFromFile("C:\\Users\\andry\\Desktop\\Mario_no_net\\���.ogg");
	music.play(); //������������ ������
	music.setLoop(true); //��������� �������, ����� �����������
	music.setVolume(30); //��������� ��������� ������

	SoundBuffer shootBuffer;//����� ��� �����
	shootBuffer.loadFromFile("C:\\Users\\andry\\Desktop\\Mario_no_net\\������.ogg");//�������� �����
	Sound shoot(shootBuffer);//������� �����

	SoundBuffer shootBuffer1;//����� ��� �����
	shootBuffer1.loadFromFile("C:\\Users\\andry\\Desktop\\Mario_no_net\\����.ogg");//�������� �����
	Sound shoot1(shootBuffer1);//������� �����

	MainPerson PMan; //����������-��������
	/*��������� ��������� ���������, �������� � �����*/
	PMan.u_x = 0;
	PMan.u_y = 0;
	PMan.x = 50;
	PMan.y = 150;

	TXTR texture;
	texture.txtr(); //������� ���� �������
	
	int W_Length = 624, W_Width = 432; //���������� ��� ������� ����

	bool Rotation = 1; //��������������� ���������� ��� ��������������� ��������
	
	Clock clock; // �����

	float frame = 0; // �����

	float frame2 = 0; // ��������������� ���������� ������

	bool Ground = false; //��������������� ��������� ��� 


	//���������� ��� ������������ ������������� �������� ��� ������ �����
	String MapLVL[13] = { // S - ��������� ������
	"         ",          // N - ���������1
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


	RenderWindow LVLwindow(VideoMode(W_Length, W_Width), "Mario_no_net"); //�������� ������� ������ RenderWindow, � ������� ������������ 2d �������

	//�������� ������� ������
	Sprite Conft;
	Conft.setTexture(texture.Confetti);
	
	//C������� ������ �������� �����
	Sprite PinkMan;
	PinkMan.setTexture(texture.PinkManStop);
	PinkMan.setTextureRect(IntRect(0, 0, 32, 32));
	
	//�������� ������� �������� ����
	Sprite Background;
	Background.setTexture(texture.MainSceneBrown);

	//�������� ������� ������ �����
	Sprite TaleMap;
	TaleMap.setTexture(texture.TaleWall);
	TaleMap.setTextureRect(IntRect(0, 64, 48, 48));

	//�������� ������� ���������
	Sprite Platform;
	Platform.setTexture(texture.TaleWall);
	Platform.setTextureRect(IntRect(96, 64, 48, 48));

	//�������� ������� ������
	Sprite Start;
	Start.setTexture(texture.StartN);
	

	//����, ���������� ���� ���� �������
	while (LVLwindow.isOpen())
	{
		/*���� � ����� � ������(������, �� ����� ������). ��� ����, �� "------------" ���� ������*/
		float time = clock.getElapsedTime().asMilliseconds(); //����������, ����������� ����� � ���������� ����
		clock.restart(); //������� ���������� �����

		frame += 0.02*time; //������� ������
		/*------------*/

		frame2 += 0.005*time; //�������������� ������� ������

		/*������� ��� ����� ������ �������� �����*/
		if (int(frame2) % 5 == 0) Conft.setTextureRect(IntRect(0, 0, 16, 16));
		if (int(frame2) % 5 == 1) Conft.setTextureRect(IntRect(16, 0, 16, 16));
		if (int(frame2) % 5 == 2) Conft.setTextureRect(IntRect(32, 0, 16, 16));
		if (int(frame2) % 5 == 3) Conft.setTextureRect(IntRect(48, 0, 16, 16));
		if (int(frame2) % 5 == 4) Conft.setTextureRect(IntRect(64, 0, 16, 16));

		Event event; // ���������� ���� "������� � ����"
		while (LVLwindow.pollEvent(event)) //����� pollEvent(event) ���������� �������, ������������ � ����
		{
			if (event.type == Event::Closed) //�������� ����
				LVLwindow.close();
		}

		//������� ��� �������� �����
		if (frame > 11) frame = frame - 11;
		PinkMan.setTexture(texture.PinkManStop);
		if (Rotation)
			PinkMan.setTextureRect(IntRect(0 + 32 * int(frame), 0, 32, 32));
		else PinkMan.setTextureRect(IntRect(32 + 32 * int(frame), 0, -32, 32));


		//Keyboard::isKeyPressed - ��������� ������� "������� �������"
		if (Keyboard::isKeyPressed(Keyboard::A)) {
			///PinkMan.move(-0.2*time, 0);
			PMan.u_x = -0.2; //�������� ������������� �������� �������� �� x

			Rotation = 0; //��������� ��������

			//�������� �������� �����
			if (frame > 12) frame = frame -12;
			PinkMan.setTexture(texture.PinkManRun);
			PinkMan.setTextureRect(IntRect(32 + 32 * int(frame), 0, -32, 32));
		}

		if (Keyboard::isKeyPressed(Keyboard::D)) {
			///PinkMan.move(0.2*time, 0);
			PMan.u_x = 0.2; //�������� ������������� �������� �������� �� x

			Rotation = 1;//��������� ��������
		
			//�������� �������� ������
			if (frame > 12) frame = frame - 12;
			PinkMan.setTexture(texture.PinkManRun);
			PinkMan.setTextureRect(IntRect(0 + 32 * int(frame), 0, 32, 32));
		}

		

		if (Keyboard::isKeyPressed(Keyboard::W)) {

			if (PMan.ground) { //������� ������: ���� ���� �� �����, ����� �������
				shoot.play(); //������������ ����� ������
				PMan.u_y = -0.5;// ��������� �������� �������� �� y
				PMan.ground = false;
			}
		
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
				Conft.setPosition(i * 48, k * 48);
				if (MapLVL[i][k] == 'N') LVLwindow.draw(Platform);
				if (MapLVL[i][k] == 'S') LVLwindow.draw(Start);
				if (MapLVL[i][k] == 'C') LVLwindow.draw(Conft);
			};
		}
		
		PMan.move(time); //������ ������� ������������
		PinkMan.setPosition(PMan.x, PMan.y); //����������� ���������
		PMan.u_x = 0; 

		/*������������ ������������ � ���������
		���������� ��������, ��������� �������� ���� �� ��������� � �������
		��� ���� ������� ������*/
		for (int i = PMan.x / 48; i < (PMan.x + 32) / 48; i++) {
			for (int k = PMan.y / 48; k < (PMan.y + 32) / 48; k++) {
				if (MapLVL[i][k] == 'N') //�������� ������������ � ����������
				{
					{

						if (PMan.u_x > 0) PMan.x = i * 48 - 32;
						if (PMan.u_x < 0) PMan.x = i * 48 + 32;

						if (PMan.u_y > 0) { PMan.y = k * 48 - 32;  PMan.u_y = 0;   PMan.ground = true; }
						if (PMan.u_y < 0) { PMan.y = k * 48 + 32;   PMan.u_y = 0; }
					}
				}
				if (MapLVL[i][k] == 'C') //�������� ������������ � �������
				{
					shoot1.play(); //������������ ����� ����� ������
					MapLVL[i][k] = ' ';
				}
			}
		}

		LVLwindow.draw(PinkMan); //��������� ���������
		LVLwindow.display(); //���������� ����
	}

	return 0;
}