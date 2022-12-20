#include "Game.h"


//init
void Game::initwindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(1280, 720), " SUCCESS");
    this->window->setFramerateLimit(60);
    this->window->setMouseCursorVisible(false);

}

//constructors / destructors
Game::Game()
{
    this->initwindow();
}

Game::~Game()
{
    delete this->window;
}



void Game::Bullet()
{
    this->bullet.setFillColor(sf::Color::Red);
    this->bullet.setRadius(10.f);

    this->Vbullet.push_back(sf::CircleShape(this->bullet));
    
}

void Game::Enemy()
{
    this->enemy.setFillColor(sf::Color::Blue);
    this->enemy.setSize(sf::Vector2f(50.f, 50.f));

    this->Venemies.push_back(sf::RectangleShape(this->enemy)); \
        this->enemyspawntimer = 0;
}

void Game::Player()
{
    this->player.setFillColor(sf::Color::White);
    this->player.setRadius(50.f);
    this->player.setPosition(0, this->window->getSize().y / 2 - this->player.getRadius());
    
    this->shoottimer = 0;

}


void Game::attackcolor() //shoot and position player
{
    this->placeforshoot = sf::Vector2f(this->player.getPosition().x + this->player.getRadius(), this->player.getPosition().y + this->player.getRadius());
    this->player.setPosition(this->player.getPosition().x, sf::Mouse::getPosition(*this->window).y);

    if (this->shoottimer<15)
    {
        this->shoottimer++;
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->shoottimer >= 15) {

        this->bullet.setPosition(this->placeforshoot); 
        this->Vbullet.push_back(sf::CircleShape(this->bullet));
        
        this->shoottimer = 0;
    }

    for (size_t i = 0; i < this->Vbullet.size(); i++)
    {
        this->Vbullet[i].move(10.f,0.f);

        if (this->Vbullet[i].getPosition().x > this->window->getSize().x)
        {
            this->Vbullet.erase(this->Vbullet.begin()+i);
        }

    }
}

void Game::Enemies() 
{
    //ENEMIES
		if(this->enemyspawntimer < 20)
			this->enemyspawntimer++;

		if (this->enemyspawntimer >= 20)
		{
			this->enemy.setPosition(this->window->getSize().x, (rand() % int(this->window->getSize().y - this->enemy.getSize().y)));
			this->Venemies.push_back(sf::RectangleShape(this->enemy));

			this->enemyspawntimer = 0;
		}

		for (size_t i = 0; i < this->Venemies.size(); i++)
		{
			this->Venemies[i].move(-5.f, 0.f);

			if (this->Venemies[i].getPosition().x > this->window->getSize().x)
				this->Venemies.erase(this->Venemies.begin() + i);
		}

		

}

void Game::collision()
{
    //Collision bullet to enemy
		if (!this->Venemies.empty() && !this->Vbullet.empty())
		{
			for (size_t i = 0; i < this->Vbullet.size(); i++)
			{
				for (size_t k = 0; k < this->Venemies.size(); k++)
				{
					if (this->Vbullet[i].getGlobalBounds().intersects(this->Venemies [k].getGlobalBounds()))
					{
						this->Vbullet.erase(this->Vbullet.begin() + i);
						this->Venemies.erase(this->Venemies.begin() + k);
						break;
					}
				}
			}
		}


}

void Game::updateSFMLEvents()
{

    while (this->window->pollEvent(this->sfevent))
    {
        if (this->sfevent.type == sf::Event::Closed)
            this->window->close();

    }

    this->attackcolor();
    this->Enemies();
    this->collision();
}

void Game::update()
{
    
    this->updateSFMLEvents();
    
}

void Game::render()
{

    this->window->clear(sf::Color::Black);
    this->window->draw(this->player);

    for (size_t i = 0; i < this->Venemies.size(); i++)
    {
        this->window->draw(this->Venemies[i]);
    }
    for (size_t i = 0; i < this->Vbullet.size(); i++)
    {
        this->window->draw(this->Vbullet[i]);
    }

    this->window->display();    

}


void Game::run()
{
    this->Bullet();
    this->Enemy();
    this->Player();

    while (this->window->isOpen())
    {

        this->update();
        this->render();
    }
}



