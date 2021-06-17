#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

/*Класс для кранения и доступа ко всем текстурам, которые используются и могут использоваться. Удобство при создании карты*/
/* !Описание каждой текстуры, чтобы не забыть!
TaleWall - стенка карты
MainScene<N> - задний фон N-ого цвета
PinkMan<K> - cостояния персонажа PinkMan
Confetti - просто разноцветный квдратик
StartN - стартовый флажок
*/

class TXTR {
public:
	Texture TaleWall, PinkManFall, PinkManStop, PinkManRun, PinkManJump, PinkManDoubleJump, 
		NinjaFrogFall, NinjaFrogStop, NinjaFrogRun, NinjaFrogJump, NinjaFrogDoubleJump,
		MaskDudeFall, MaskDudeStop, MaskDudeRun, MaskDudeJump, MaskDudeDoubleJump,
		VirtualGuyFall, VirtualGuyStop, VirtualGuyRun, VirtualGuyJump, VirtualGuyDoubleJump,
		MainSceneBrown, MainSceneBlue, MainSceneGray, MainSceneGreen,
		MainScenePink, MainScenePurple, MainSceneYellow, StartN, Confetti;
	void txtr() {
		
		MainSceneBrown.loadFromFile("C:\\Users\\andry\\Desktop\\Mario_no_net\\Free\\Background\\Brown.png");
		MainSceneBlue.loadFromFile("C:\\Users\\andry\\Desktop\\Mario_no_net\\Free\\Background\\Blue.png");
		MainSceneGray.loadFromFile("C:\\Users\\andry\\Desktop\\Mario_no_net\\Free\\Background\\Gray.png");
		MainSceneGreen.loadFromFile("C:\\Users\\andry\\Desktop\\Mario_no_net\\Free\\Background\\Green.png");
		MainScenePink.loadFromFile("C:\\Users\\andry\\Desktop\\Mario_no_net\\Free\\Background\\Pink.png");
		MainScenePurple.loadFromFile("C:\\Users\\andry\\Desktop\\Mario_no_net\\Free\\Background\\Purple.png");
		MainSceneYellow.loadFromFile("C:\\Users\\andry\\Desktop\\Mario_no_net\\Free\\Background\\Yellow.png");


		TaleWall.loadFromFile("C:\\Users\\andry\\Desktop\\Mario_no_net\\Free\\Terrain\\Terrain (16x16).png");


		NinjaFrogFall.loadFromFile("C:\\Users\\andry\\Desktop\\Mario_no_net\\Free\\Ninja Frog\\Fall (32x32).png");
		NinjaFrogStop.loadFromFile("C:\\Users\\andry\\Desktop\\Mario_no_net\\Free\\Ninja Frog\\Idle (32x32).png");
		NinjaFrogRun.loadFromFile("C:\\Users\\andry\\Desktop\\Mario_no_net\\Free\\Ninja Frog\\Run (32x32).png");
		NinjaFrogJump.loadFromFile("C:\\Users\\andry\\Desktop\\Mario_no_net\\Free\\Ninja Frog\\Jump (32x32).png");
		NinjaFrogDoubleJump.loadFromFile("C:\\Users\\andry\\Desktop\\Mario_no_net\\Free\\Ninja Frog\\Double Jump (32x32).png");

		PinkManFall.loadFromFile("C:\\Users\\andry\\Desktop\\Mario_no_net\\Free\\Pink Man\\Fall.png");
		PinkManStop.loadFromFile("C:\\Users\\andry\\Desktop\\Mario_no_net\\Free\\Pink Man\\Idle (32x32).png");
		PinkManRun.loadFromFile("C:\\Users\\andry\\Desktop\\Mario_no_net\\Free\\Pink Man\\Run (32x32).png");
		PinkManJump.loadFromFile("C:\\Users\\andry\\Desktop\\Mario_no_net\\Free\\Pink Man\\Jump (32x32).png");
		PinkManDoubleJump.loadFromFile("C:\\Users\\andry\\Desktop\\Mario_no_net\\Free\\Pink Man\\Double Jump (32x32).png");

		MaskDudeFall.loadFromFile("C:\\Users\\andry\\Desktop\\Mario_no_net\\Free\\Mask Dude\\Fall (32x32).png");
		MaskDudeStop.loadFromFile("C:\\Users\\andry\\Desktop\\Mario_no_net\\Free\\Mask Dude\\Idle (32x32).png");
		MaskDudeRun.loadFromFile("C:\\Users\\andry\\Desktop\\Mario_no_net\\Free\\Mask Dude\\Run (32x32).png");
		MaskDudeJump.loadFromFile("C:\\Users\\andry\\Desktop\\Mario_no_net\\Free\\Mask Dude\\Jump (32x32).png");
		MaskDudeDoubleJump.loadFromFile("C:\\Users\\andry\\Desktop\\Mario_no_net\\Free\\Mask Dude\\Double Jump (32x32).png");

		VirtualGuyFall.loadFromFile("C:\\Users\\andry\\Desktop\\Mario_no_net\\Free\\Virtual Guy\\Fall (32x32).png");
		VirtualGuyStop.loadFromFile("C:\\Users\\andry\\Desktop\\Mario_no_net\\Free\\Virtual Guy\\Idle (32x32).png");
		VirtualGuyRun.loadFromFile("C:\\Users\\andry\\Desktop\\Mario_no_net\\Free\\Virtual Guy\\Run (32x32).png");
		VirtualGuyJump.loadFromFile("C:\\Users\\andry\\Desktop\\Mario_no_net\\Free\\Virtual Guy\\Jump (32x32).png");
		VirtualGuyDoubleJump.loadFromFile("C:\\Users\\andry\\Desktop\\Mario_no_net\\Free\\Virtual Guy\\Double Jump (32x32).png");


		StartN.loadFromFile("C:\\Users\\andry\\Desktop\\Mario_no_net\\Free\\Items\\Checkpoints\\Start\\Start (idle).png");
		Confetti.loadFromFile("C:\\Users\\andry\\Desktop\\Mario_no_net\\Free\\Other\\Confetti (16x16).png");
	}

};


