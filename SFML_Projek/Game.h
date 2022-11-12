#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include"SFML/Audio.hpp"
#include"SFML/Network.hpp"
#include"SFML/System.hpp"
#include"SFML/Window.hpp"
#include"SFML/Graphics.hpp"



class Game
{

private:
	
	

	void initwindow();

public:
	
	//construtors / destructors
	Game();
	virtual ~Game();
	
	//function
	void updateSFMLEvents();
	void update();
	void render();
	void run();



};

#endif