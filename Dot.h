//
// Created by zapad on 04.09.2018.
//

#ifndef NEATEXAMPLE_DOT_H
#define NEATEXAMPLE_DOT_H

#include "SFML/Graphics.hpp"
#include "Brain.h"
#include "Simulation.h"

class Simulation;

class Dot{

public:
    static int sNumberOfDots;

    Dot();
    ~Dot();
    sf::CircleShape getTheDot() { return theDot;}
    bool update();
    float calculateFitness();
    void setSimulation(Simulation *simulation);
    bool isDead();
    bool reachedGoal() {return mReachedGoal;}
    void createBaby(Dot *parent);
    Brain* getBrain() {return &mBrain;}
    void mutateTheBrain();
    void setBest(bool best);
    bool isBest() {return mBestDot;}
    void kill() {mDead = true;}
    sf::CircleShape* getCircleShape() {return &theDot;}

private:
    Simulation *pSimulation;

    sf::CircleShape theDot;
    sf::Vector2f mPosition;
    sf::Vector2f mVelocity;
    sf::Vector2f mAcceleration;
    bool mDead;
    bool mReachedGoal;
    bool mBestDot;

    Brain mBrain;
    float mFitness;

    void move();
    float getDistanceToGoal();
};


#endif //NEATEXAMPLE_DOT_H
