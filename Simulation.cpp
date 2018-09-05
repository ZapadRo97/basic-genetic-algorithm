//
// Created by zapad on 04.09.2018.
//

#include <iostream>
#include "Simulation.h"


Simulation::Simulation() :mWindow(sf::VideoMode(sWidth, sHeight), "SFML Application"),
                          timePerFrame(sf::seconds(1.f / 60.f)),
                          mGoal(4){
    pBigNation = new Population(this, 100);
    mCurrentGeneration = 1;
    mSuccessfulPeople = 0;

    if (!mFont.loadFromFile("fonts/arial.ttf"))
    {
        std::cout<<"Could not load font" << std::endl;
    }
}



void Simulation::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen())
    {
        sf::Time updateTime = clock.restart();
        timeSinceLastUpdate += updateTime;
        while (timeSinceLastUpdate > timePerFrame)
        {
            timeSinceLastUpdate -= timePerFrame;
            processEvents();
            update(timePerFrame);
        }
        render();
    }
}

void Simulation::processEvents()
{
    sf::Event event{};
    while (mWindow.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                mWindow.close();
                break;
            default:
                break;
        }
    }
}

void Simulation::render()
{
    mWindow.clear();

    sf::Text generationText;
    generationText.setPosition(20, 400);
    generationText.setFont(mFont);

    sf::Text successfulText;
    successfulText.setPosition(20, 425);
    successfulText.setFont(mFont);


    std::string text, text2;
    text = "Generation: ";
    text = text + std::to_string(mCurrentGeneration);
    text2 = "Successful dots (last gen): ";
    text2 = text2 + std::to_string(mSuccessfulPeople);


    generationText.setString(sf::String(text));
    generationText.setCharacterSize(24);

    successfulText.setString(sf::String(text2));
    successfulText.setCharacterSize(24);

    mGoal.setPosition(320, 10);
    mGoal.setFillColor(sf::Color::Red);

    mObstacle.setPosition(185,200);
    mObstacle.setSize(sf::Vector2f(270, 10));
    mObstacle.setFillColor(sf::Color::Blue);

    mWindow.draw(mGoal);
    mWindow.draw(mObstacle);

    mWindow.draw(generationText);
    mWindow.draw(successfulText);


    if(pBigNation->getSize() != 0) {
        pBigNation->show(&mWindow);
    }


    mWindow.display();
}

sf::FloatRect Simulation::getObstacleRect() {
    return mObstacle.getGlobalBounds();
}

void Simulation::update(sf::Time deltaTime)
{
    if(pBigNation->allDotsAreDead()) {
        //sf::Time t1 = sf::seconds(1.0f);
        //sf::sleep(t1);

        mSuccessfulPeople = pBigNation->getSuccessfulDots();

        //genetic algorithm
        pBigNation->calculateFitness();
        pBigNation->naturalSelection();
        pBigNation->mutate();

        mCurrentGeneration = pBigNation->getGeneration();
    }
    else {
        pBigNation->update();
    }

}

Simulation::~Simulation() {
    delete pBigNation;
}

sf::Vector2f Simulation::getGoal() {
    return mGoal.getPosition();
}
