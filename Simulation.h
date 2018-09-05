//
// Created by zapad on 04.09.2018.
//

#ifndef NEATEXAMPLE_SIMULATION_H
#define NEATEXAMPLE_SIMULATION_H


#include <SFML/Graphics.hpp>
#include "Dot.h"
#include "Population.h"

class Population;

class Simulation {

public:
    void run();
    Simulation();
    ~Simulation();

    static const int sWidth = 640;
    static const int sHeight = 480;

    sf::Vector2f getGoal();
    sf::FloatRect getObstacleRect();

private:
    void processEvents();
    void update(sf::Time);
    void render();

private:
    sf::RenderWindow mWindow;
    const sf::Time timePerFrame;

private: //today a dot, but tomorrow, a population
    Population *pBigNation;
    sf::CircleShape mGoal;
    sf::RectangleShape mObstacle;

    int mCurrentGeneration;
    int mSuccessfulPeople;
    sf::Font mFont;
};


#endif //NEATEXAMPLE_SIMULATION_H
