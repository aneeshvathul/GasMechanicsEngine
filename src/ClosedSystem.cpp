#include "ClosedSystem.hpp"

ClosedSystem::ClosedSystem(int displayWidth, int displayHeight, long double timeStep){
    this->displayWidth = displayWidth;
    this->displayHeight = displayHeight;
    this->timeStep = timeStep;
}

void ClosedSystem::run(){

    sf::RenderWindow window(sf::VideoMode(displayWidth, displayHeight), "Physics Engine 2D");

    bool drawBody = true;
    while (window.isOpen()){
        sf::Event event;

        while (window.pollEvent(event)){
            if (event.type == sf::Event::MouseButtonPressed && drawBody){
                CircleBody circleBody(event.mouseButton.x, event.mouseButton.y);
                circleBodies.push_back(circleBody);
                drawBody = false;
            }
            
            else if (event.type == sf::Event::MouseButtonReleased && !drawBody){
                drawBody = true;
            }

            else if (event.type == sf::Event::Closed){
                window.close();
            }
        }

        updateSystem();
        
        // Update display to match the system
        window.clear();
        for (CircleBody circleBody : circleBodies){
            window.draw(circleBody.getShape());
        }
        window.display();
    }
}

void::ClosedSystem::updateSystem(){
    // Update physics on a time step
    long double deltaTime = clock.restart().asSeconds();
    timeAccumulator += deltaTime;
    while (timeAccumulator >= timeStep) {
        updatePhysics();
        timeAccumulator -= timeStep;
    }
}

void ClosedSystem::updatePhysics(){
    updateCollisions();
    // Update kinematics of bodies
    for (int i = 0; i < circleBodies.size(); i++){
        CircleBody& circleBody = circleBodies[i];
        long double radius = circleBody.getShape().getRadius();
        circleBody.setX(circleBody.getX() + circleBody.getVelocityX() * timeStep);
        circleBody.setY(circleBody.getY() + circleBody.getVelocityY() * timeStep);
        circleBody.getShape().setPosition(circleBody.getX() - radius, circleBody.getY() - radius);
    }
}

void ClosedSystem::updateCollisions(){
    // Check collisions with walls
    for (int i = 0; i < circleBodies.size(); i++){
        CircleBody& circleBody = circleBodies[i];
        long double x = circleBody.getX();
        long double y = circleBody.getY();
        long double radius = circleBody.getShape().getRadius();
        if (x <= radius || x >= displayWidth - radius){
            circleBody.setVelocityX(-circleBody.getVelocityX());
        }
        if (y <= radius || y >= displayHeight - radius){
            circleBody.setVelocityY(-circleBody.getVelocityY());
        }
    }
    // Check collisions between circular bodies
    if (circleBodies.size() > 1){
        for (int i = 0; i < circleBodies.size() - 1; i++){
            for (int j = i + 1; j < circleBodies.size(); j++){
                CircleBody& circleBody1 = circleBodies[i];
                CircleBody& circleBody2 = circleBodies[j];
                if (circleBody1.isCollidingWith(circleBody2)){
                    // long double energyBefore = circleBody1.getMass() * (circleBody1.getVelocityX() * circleBody1.getVelocityX() 
                    // + circleBody1.getVelocityY() * circleBody1.getVelocityY()) + circleBody2.getMass() * (circleBody2.getVelocityX() * circleBody2.getVelocityX() 
                    // + circleBody2.getVelocityY() * circleBody2.getVelocityY());
                    Forces::elasticCollide(circleBody1, circleBody2);
                    // long double energyAfter = circleBody1.getMass() * (circleBody1.getVelocityX() * circleBody1.getVelocityX() 
                    // + circleBody1.getVelocityY() * circleBody1.getVelocityY()) + circleBody2.getMass() * (circleBody2.getVelocityX() * circleBody2.getVelocityX() 
                    // + circleBody2.getVelocityY() * circleBody2.getVelocityY());
                    // std::cout << energyBefore << " " << energyAfter << std::endl;
                }
            }
        }
    }
}
