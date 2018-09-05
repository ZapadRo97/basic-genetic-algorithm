//
// Created by zapad on 04.09.2018.
//

#ifndef NEATEXAMPLE_BRAIN_H
#define NEATEXAMPLE_BRAIN_H

#include "SFML/Graphics.hpp"

class Brain {
public:
    static int sNumberOfBrains;

    Brain(int size);
    ~Brain();
    Brain(const Brain &brain);
    Brain& operator=(const Brain &brain);

    bool getNextStep(sf::Vector2f &vector);
    int getStepNumber() {return mStep;}
    void mutate();

private:
    int mStep;
    int mSize;
    std::vector<sf::Vector2f> mArrDirections;

    void randomize();
};


#endif //NEATEXAMPLE_BRAIN_H
