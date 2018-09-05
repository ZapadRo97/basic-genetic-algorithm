//
// Created by zapad on 04.09.2018.
//

#include "Brain.h"
#include <random>
#include <functional>

#include <iostream>

const float  PI_F=3.14159265358979f;

int Brain::sNumberOfBrains = 0;

Brain::Brain(int size) {
    mStep = 0;
    mSize = size;
    mArrDirections.resize(size);
    randomize();
    sNumberOfBrains++;
}

Brain::~Brain() {
    sNumberOfBrains--;
}


void Brain::randomize() {
    std::uniform_real_distribution<float> randomAngleRange(0, 2*PI_F);
    std::random_device rd;
    std::mt19937 randomNumbers(rd());

    for(int i = 0; i < mSize; i++) {
        float randomAngle = randomAngleRange(randomNumbers);
        mArrDirections[i].x = sin(randomAngle);
        mArrDirections[i].y = cos(randomAngle);
    }

}

bool Brain::getNextStep(sf::Vector2f &vector) {

    if(mStep == mSize)
        return false;

    if(mStep < mSize) {
        vector = mArrDirections[mStep];
        mStep++;
    }

    return true;
}


void Brain::mutate() {

    std::uniform_real_distribution<float> randomAngleRange(0, 2*PI_F);
    std::uniform_real_distribution<float> randomMutation(0, 1);
    std::random_device rd;
    std::mt19937 randomNumbers(rd());

    float mutationRate = 0.01;
    for(int i = 0; i < mSize; i++) {
        float rand = randomMutation(randomNumbers);
        if(rand < mutationRate) {
            float randomAngle = randomAngleRange(randomNumbers);
            mArrDirections[i].x = sin(randomAngle);
            mArrDirections[i].y = cos(randomAngle);
        }
    }


}

Brain::Brain(const Brain &brain) {
    mSize = brain.mSize;
    mStep = 0;
    mArrDirections = brain.mArrDirections;
}

Brain &Brain::operator=(const Brain &brain) {
    mSize = brain.mSize;
    mStep = 0;
    mArrDirections = brain.mArrDirections;
    return *this;
}
