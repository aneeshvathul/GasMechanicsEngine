#pragma once
#include <iostream>
#include <cmath>
#include <queue>
#include <SFML/Graphics.hpp>
#include "CircleBody.hpp"
#include "CollisionState.hpp"

class ClosedSystem{

    private:
        int displayWidth;
        int displayHeight;
        int frameCount;
        float timeStep;
        float spawnClearance;
        float stepTimeAccumulator;
        float systemTimeAccumulator;
        float epsilon;
        std::vector<CircleBody> circleBodies;
        sf::Clock clock;
        std::queue<CollisionState> collisionQueue;
        
        void createCircleBody(float x, float y);
        void updateSystem();
        void updateKinematics();
        void updateWallCollisions();
        float getSystemEnergy();
        void setCollisionQueue();
        void printSystemMetrics(int frameCycle);
    
    public:
        ClosedSystem(int displayWidth, int displayHeight, float timeStep, float spawnClearance, float epsilon);
        void run();
};