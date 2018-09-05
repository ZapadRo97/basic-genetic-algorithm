//
// Created by zapad on 04.09.2018.
//

#ifndef NEATEXAMPLE_POPULATION_H
#define NEATEXAMPLE_POPULATION_H


#include "Dot.h"

class Simulation;
class Dot;

class Population {
public:
    Population(Simulation*, int size);
    ~Population();
    void show(sf::RenderWindow *window);
    void update();

    void calculateFitness();
    void calculateFitnessSum();
    void naturalSelection();
    void mutate();
    Dot* selectParent();
    bool allDotsAreDead();

    int getGeneration() {return mGeneration;}
    int getSize() {return mSize;}
    int getSuccessfulDots() {return mSuccessfulDots;}

private:
    Simulation *pSimulation;
    float mFitnessSum;

    Dot *mArrDots;
    int mSize;

    int mBestDot;
    int mGeneration;
    int mMinSteps;
    int mSuccessfulDots;

    void setSimulationToDots();
    void setBestDot();
};


#endif //NEATEXAMPLE_POPULATION_H
