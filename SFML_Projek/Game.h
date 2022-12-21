#pragma once

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <sstream>
#include"SFML/Audio.hpp"
#include"SFML/Network.hpp"
#include"SFML/System.hpp"
#include"SFML/Window.hpp"
#include"SFML/Graphics.hpp"

using namespace sf;

class Game
{

private:

	
	RenderWindow* window;
	Event sfevent;
	Sprite Sbackground;
	Texture backgroundtex;
	Music music;


	//player
	Sprite player;
	Texture playertex;
	Vector2f placeforshoot;
	Font fontscoreplayer;
	Text textscoreplayer;
	int HP;
	int score;
	int shoottimer;

	//enemy
	Sprite enemy;
	Texture enemytex;
	SoundBuffer buffdet;
	Sound sounddet;
	
	std::vector <Sprite> Venemies; 
	int enemyspawntimer;
	
	//bullet
	CircleShape bullet;
	std::vector <CircleShape> Vbullet;
	SoundBuffer buffsoundBullet;
	Sound soundShoot;


	//init
	void initwindow();

	//gameover
	Text textGameOVer;


public:

	//construtors / destructors
	Game();
	virtual ~Game();

	//UI
	void Background();
	void Music();

	//character ingame
	void Player();
	void Bullet();
	void Enemy();


	//function

	void attackcolor();
	void Enemies();
	void collision();
	void Score();

	void updateSFMLEvents();
	void update();
	void render();
	void run();
	void gameover();


};

