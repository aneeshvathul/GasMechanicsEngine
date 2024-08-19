#pragma once
#include <SFML/Graphics.hpp>
#include "CircleBody.hpp"
#include "Forces.hpp"

class ClosedSystem{

    private:
        int displayWidth;
        int displayHeight;
        long double timeStep;
        long double timeAccumulator;
        std::vector<CircleBody> circleBodies;
        sf::Clock clock;
        
        void updateSystem();
        void updatePhysics();
        void updateCollisions();
    
    public:
        ClosedSystem(int displayWidth, int displayHeight, long double timeStep);
        void run();
};