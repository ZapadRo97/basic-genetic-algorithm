#include <cmath>

//
// Created by zapad on 04.09.2018.
//

#include <cmath>
#include <iostream>
#include "Dot.h"
#include "Simulation.h"

int Dot::sNumberOfDots = 0;

Dot::Dot() :mBrain(400) {

    mVelocity = sf::Vector2f(0, 0);
    mAcceleration = sf::Vector2f(0, 0);
    mPosition = sf::Vector2f(Simulation::sWidth/2.f, Simulation::sHeight-10);
    mDead = false;
    mReachedGoal = false;
    mFitness = 0;
    mBestDot = false;

    theDot.setPosition(mPosition);
    theDot.setRadius(4);

    sNumberOfDots++;
}

void Dot::move() {
    if(!mBrain.getNextStep(mAcceleration))
        mDead = true;

    if(mVelocity.x < 5 && mVelocity.y < 5)
        mVelocity += mAcceleration;
    mPosition += mVelocity;

    theDot.setPosition(mPosition);
}

bool Dot::update() {
    sf::FloatRect dotRect = theDot.getGlobalBounds();
    sf::FloatRect obstacleRect = pSimulation->getObstacleRect();
    if(!mDead && !mReachedGoal) {
        move();
        if(mPosition.x < 2 || mPosition.y < 2 ||
           mPosition.x > Simulation::sWidth -2 || mPosition.y > Simulation::sHeight -2) {
            mDead = true;
        } else if(getDistanceToGoal() < 5) {
            mReachedGoal = true;
            return true;
        } else if(dotRect.intersects(obstacleRect)) {
            mDead = true;
        }
    }

    return false;


}

float Dot::calculateFitness() {
    if(reachedGoal()) {
        mFitness = 1.0/16.0 + 10000.0/(float)(mBrain.getStepNumber() * mBrain.getStepNumber());
    }
    else {
        float distanceToGoal = getDistanceToGoal();
        mFitness = 1.0/(distanceToGoal*distanceToGoal);
        return mFitness;
    }

}

void Dot::setSimulation(Simulation *simulation) {
    this->pSimulation = simulation;
}

bool Dot::isDead() {
    return mDead;
}

float Dot::getDistanceToGoal() {
    sf::Vector2f goal = pSimulation->getGoal();
    float distanceX = mPosition.x - goal.x;
    float distanceY = mPosition.y - goal.y;
    float distanceToGoal = std::sqrt(distanceX*distanceX + distanceY*distanceY);
    return distanceToGoal;
}

void Dot::createBaby(Dot *parent) {
    mBrain = *(parent->getBrain());
}

void Dot::mutateTheBrain() {

    mBrain.mutate();

}

Dot::~Dot() {
    sNumberOfDots--;
}

void Dot::setBest(bool best) {
    mBestDot = best;
}

