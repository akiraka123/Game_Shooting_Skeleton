#pragma once

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>

#include"SFML/Audio.hpp"
#include"SFML/Network.hpp"
#include"SFML/System.hpp"
#include"SFML/Window.hpp"
#include"SFML/Graphics.hpp"



class Game
{

private:
	
	//var
	sf::RenderWindow* window;
	sf::Event sfevent;

	//player
	sf::CircleShape player;
	sf::Vector2f placeforshoot;
	int shoottimer;
	int enemyspawntimer;

	//enemy
	sf::RectangleShape enemy;
	std::vector <sf::RectangleShape> Venemies;

	//bullet
	sf::CircleShape bullet;
	std::vector <sf::CircleShape> Vbullet;
	

	//init
	void initwindow();


public:
	
	//construtors / destructors
	Game();
	virtual ~Game();
	
	//character ingame
	void Player();
	void Bullet();
	void Enemy();
	

		//function
		
	void attackcolor();
	void Enemies(); 
	void collision();

	void updateSFMLEvents();
	void update();
	void render();
	void run();



};

