#include "Game.h"


//init
void Game::initwindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(1280, 720), " SUCCESS");
    this->window->setFramerateLimit(60);
    this->window->setMouseCursorVisible(true);

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
    this->bullet.setRadius(7.5f);

    this->Vbullet.push_back(sf::CircleShape(this->bullet));

}

void Game::Enemy()
{
    this->enemytex.loadFromFile("TEXTURE/walk/go_1.png");
    this->enemy.setTexture(this->enemytex);
    this->enemy.scale(0.5f, 0.5f);


    this->Venemies.push_back(sf::Sprite(this->enemy)); 
        this->enemyspawntimer = 0;
}

void Game::Player()
{
    this->playertex.loadFromFile("TEXTURE/1.png");
    this->player.setTexture(this->playertex);
    this->player.scale(1.4f, 1.4f);
    this->player.setPosition(0, this->window->getSize().y / 2 - this->player.getLocalBounds().height);

    
    //init
    
    if (this->fontscoreplayer.loadFromFile("FONT/Infinite Beyond Italic 400.ttf"))
        {
            std::cout << "font not found" << std::endl;
        }
    this->textscoreplayer.setFont(this->fontscoreplayer);
    this->textscoreplayer.setCharacterSize(24);
    this->textscoreplayer.setPosition(this->window->getSize().x / 2, 10.f);
    
    
   /* this->temp = this->score;
    this->ss << "SCORE PLAYER : " << this->temp;
    this->textscoreplayer.setString(this->ss.str());*/
    this->HP = 5;
    this->score = -1;
    this->shoottimer = 0;

}


void Game::attackcolor() //shoot and moveplayer
{
    this->placeforshoot = sf::Vector2f(this->player.getPosition().x + this->player.getGlobalBounds().width * 3 / 4, this->player.getPosition().y + this->player.getLocalBounds().height / 2 - 8.f);
    this->player.setPosition(this->player.getPosition().x, sf::Mouse::getPosition(*this->window).y);

    if (this->shoottimer < 15)
    {
        this->shoottimer++;
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->shoottimer >= 15) {
        //bullet
        this->bullet.setPosition(this->placeforshoot);
        this->Vbullet.push_back(sf::CircleShape(this->bullet));

        this->shoottimer = 0;
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        //sound effect bullet
        this->buffsoundBullet.loadFromFile("Music/sound/pistol1.ogg");
        this->soundShoot.setBuffer(this->buffsoundBullet);
        this->soundShoot.play();
    }
    for (size_t i = 0; i < this->Vbullet.size(); i++)
    {
        this->Vbullet[i].move(10.f, 0.f);

        if (this->Vbullet[i].getPosition().x > this->window->getSize().x)
        {
            this->Vbullet.erase(this->Vbullet.begin() + i);
        }

    }
}

void Game::Enemies()
{
    //ENEMIES
    if (this->enemyspawntimer < 45)
        this->enemyspawntimer++;

    if (this->enemyspawntimer >= 45)
    {
        this->enemy.setPosition(this->window->getSize().x, (rand() % int(this->window->getSize().y - this->enemy.getGlobalBounds().height)));
        this->Venemies.push_back(sf::Sprite(this->enemy));

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
                if (this->Vbullet[i].getGlobalBounds().intersects(this->Venemies[k].getGlobalBounds()))
                {
                    this->buffdet.loadFromFile("Music/sound/1death.ogg");
                    this->sounddet.setBuffer(this->buffdet);
                    this->sounddet.play();
                    
                    this->Vbullet.erase(this->Vbullet.begin() + i);
                    this->Venemies.erase(this->Venemies.begin() + k);
                    this->score++;
                    break;
                }
            }
        }
    }

    //collision player 
            // collision top
    if (this->player.getPosition().y < 0.f)
    {
        this->player.setPosition(this->player.getPosition().x, 0.f);
    }
            // collision bot
    if (this->player.getPosition().y + this->player.getGlobalBounds().height > 720.f)
    {
        this->player.setPosition(this->player.getPosition().x, 720.f - this->player.getGlobalBounds().height);
    }
            //collision enemy and player
    if (!this->Venemies.empty()) {
        for (size_t i = 0; i < this->Venemies.size(); i++)
        {
            if (this->player.getGlobalBounds().intersects(this->Venemies[i].getGlobalBounds()))
            {
                
                this->HP-=1;
                this->Venemies.erase(this->Venemies.begin() + i);
                break;
            }
        }
    }
}

void Game::Background()
{
    if (!this->backgroundtex.loadFromFile("TEXTURE/background.jpg"))
    {
       std::cout << "error background"<<std::endl;
    }
    this->Sbackground.setTexture(this->backgroundtex);
    this->Sbackground.scale(0.5f, 0.5f);
}

void Game::Music() {

    if (!this->music.openFromFile("Music/bgm.ogg"))
    {
        std::cout << "error music" << std::endl;
    }
    
    music.play();
}

void Game::Score()
{
    std::stringstream ss;
    int temp = this->score;
    ss << "SCORE PLAYER : " << temp;
    this->textscoreplayer.setString(ss.str());
}

void Game::gameover()
{
    this->textGameOVer.setFont(this->fontscoreplayer);
    this->textGameOVer.setCharacterSize(24);
    this->textGameOVer.setPosition(this->window->getSize().x / 2, this->window->getSize().y / 2);
    this->textGameOVer.setString("GAME OVERRRRR UIIII");
    
    while (this->window->pollEvent(this->sfevent))
    {
        if (this->sfevent.type == sf::Event::Closed)
            this->window->close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            this->window->close();
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

    this->Score();
    this->attackcolor();
    this->Enemies();
    this->collision();

}

void Game::update()
{
    
    if (this->HP <= 0)
    {
        this->gameover();
        
    }
    else { 

        this->updateSFMLEvents();
        
    
    }
}

void Game::render()
{
    this->window->clear();
    this->window->draw(this->Sbackground);
    
    this->window->draw(this->player);

    for (size_t i = 0; i < this->Venemies.size(); i++)
    {
        this->window->draw(this->Venemies[i]);
    }
    for (size_t i = 0; i < this->Vbullet.size(); i++)
    {
        this->window->draw(this->Vbullet[i]);
    }
    this->window->draw(this->textscoreplayer);
    this->window->draw(this->textGameOVer);
    this->window->display();

}



void Game::run()
{
    this->Background();
    this->Music();
    this->Bullet();
    this->Enemy();
    this->Player();
    while (this->window->isOpen())
    {

        this->update();
        this->render();
    }
}