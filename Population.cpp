//
// Created by zapad on 04.09.2018.
//

#include <random>
#include <iostream>
#include "Population.h"

Population::Population(Simulation *simulation, int size) {
    pSimulation = simulation;

    mFitnessSum = 0.0f;
    mBestDot = 0;
    mSize = size;
    mArrDots = new Dot[size];
    mGeneration = 1;
    mMinSteps = 400;

    mSuccessfulDots = 0;

    setSimulationToDots();
}

Population::~Population() {
    delete[] mArrDots;
}

void Population::show(sf::RenderWindow *window) {
    for(int i = mSize-1; i >= 0; i--) {
        if(mArrDots[i].isBest())
            mArrDots->getCircleShape()->setFillColor(sf::Color::Green);
        window->draw(mArrDots[i].getTheDot());
    }
}

void Population::update() {
    for(int i = 0; i < mSize; i++) {
        if(mArrDots[i].getBrain()->getStepNumber() > mMinSteps){
            mArrDots[i].kill();
        } else {
            if(mArrDots[i].update())
                mSuccessfulDots++;
        }
    }
}

void Population::setSimulationToDots() {
    for(int i = 0; i < mSize; i++) {
        mArrDots[i].setSimulation(pSimulation);
    }
}

void Population::calculateFitness() {
    for(int i = 0; i < mSize; i++) {
        mArrDots[i].calculateFitness();
    }
}

bool Population::allDotsAreDead() {
    for(int i = 0; i < mSize; i++) {
        if(!mArrDots[i].isDead() && !mArrDots[i].reachedGoal())
            return false;
    }
    return true;
}

void Population::naturalSelection() {
    mSuccessfulDots = 0;
    Dot *arrDots = new Dot[mSize];
    setBestDot();
    for(int i = 0; i < mSize; i++) {
        arrDots[i].setSimulation(pSimulation);
    }
    arrDots[0].createBaby(&mArrDots[mBestDot]);
    arrDots[0].setBest(true);
    calculateFitnessSum();

    for(int i = 1; i < mSize; i++) {
        //select parent based on fitness
        Dot *parent = selectParent();

        //get baby from them
        arrDots[i].createBaby(parent);
    }


    for(int i = 0; i < mSize; i++) {
       mArrDots[i] = arrDots[i];
    }

    delete[] arrDots;
    mGeneration++;
}

Dot* Population::selectParent() {
    std::uniform_real_distribution<float> randomSumRange(0, mFitnessSum);
    std::random_device rd;
    std::mt19937 randomNumbers(rd());

    float randomSum = randomSumRange(randomNumbers);
    float runningSum = 0.0f;

    for(int i = 0; i < mSize; i++) {
        runningSum += mArrDots[i].calculateFitness();
        if(runningSum > randomSum) {
            return &mArrDots[i];
        }
    }

    //this should never happen
    return nullptr;
}

void Population::calculateFitnessSum() {
    mFitnessSum = 0.0f;
    for(int i = 0; i < mSize; i++) {
        mFitnessSum += mArrDots[i].calculateFitness();
    }
}

void Population::mutate() {
    for(int i = 1; i < mSize; i++) {
        mArrDots[i].mutateTheBrain();
    }

}

void Population::setBestDot() {
    float maxFitness = 0;
    int maxIndex = 0;

    for(int i = 0; i < mSize; i++) {
        float currentFitness = mArrDots[i].calculateFitness();
        if(currentFitness > maxFitness) {
            maxFitness = currentFitness;
            maxIndex = i;
        }
    }

    mBestDot = maxIndex;

    if(mArrDots[maxIndex].reachedGoal())
        mMinSteps = mArrDots[maxIndex].getBrain()->getStepNumber();
}


