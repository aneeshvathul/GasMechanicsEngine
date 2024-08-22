#include "ClosedSystem.hpp"

ClosedSystem::ClosedSystem(int displayWidth, int displayHeight, float timeStep, float spawnClearance, float epsilon){
    this->displayWidth = displayWidth;
    this->displayHeight = displayHeight;
    this->timeStep = timeStep;
    this->spawnClearance = spawnClearance;
    this->epsilon = epsilon;

    frameCount = 0;
    stepTimeAccumulator = 0.f;
    systemTimeAccumulator = 0.f;
}

void ClosedSystem::run(){

    sf::RenderWindow window(sf::VideoMode(displayWidth, displayHeight), "Physics Engine 2D");

    bool drawBody = true;
    while (window.isOpen()){
        sf::Event event;

        while (window.pollEvent(event)){
            if (event.type == sf::Event::MouseButtonPressed && drawBody){
                createCircleBody(event.mouseButton.x, event.mouseButton.y);
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

bool ClosedSystem::createCircleBody(float x, float y){
    bool canDrawHere = true;
    if (x <= spawnClearance || x >= displayWidth - spawnClearance || y <= spawnClearance || y >= displayHeight - spawnClearance){
        canDrawHere = false;
    }
    else{
        for (CircleBody& circleBody : circleBodies){   
            if (circleBody.getDistance(x, y) <= circleBody.getShape().getRadius() + spawnClearance){
                canDrawHere = false;
                break;
            }
        }
    }
    if (canDrawHere){
        CircleBody newCircleBody(x, y);
        circleBodies.push_back(newCircleBody);
        setCollisionQueue();
    }
    return canDrawHere;
}

void::ClosedSystem::updateSystem(){
    
    if (circleBodies.size() > 0){
        float deltaTime = clock.restart().asSeconds();
        stepTimeAccumulator += deltaTime;
        systemTimeAccumulator += deltaTime;
        
        // Update motion every frame
        while (stepTimeAccumulator >= timeStep) {
            updateWallCollisions();
            // Check/update inter-body collision physics only at the time of collision
            if (circleBodies.size() > 1){
                while (!collisionQueue.empty() && frameCount >= collisionQueue.front().getFrame()){
                    CircleBody& circleBody1 = *collisionQueue.front().getFirst();
                    CircleBody& circleBody2 = *collisionQueue.front().getSecond();
                    circleBody1.elasticCollide(circleBody2);

                    collisionQueue.pop();
                }
                setCollisionQueue();
            }
            updateKinematics();
            stepTimeAccumulator -= timeStep;
            frameCount++;
        }
    }

}

void ClosedSystem::updateWallCollisions(){
    // Check collisions with walls
    for (int i = 0; i < circleBodies.size(); i++){
        CircleBody& circleBody = circleBodies[i];
        float x = circleBody.getX();
        float y = circleBody.getY();
        float r = circleBody.getShape().getRadius();
        if (x <= r){
            circleBody.setVelocityX(-circleBody.getVelocityX());
            circleBody.setX(r + epsilon);
            setCollisionQueue();
        }
        else if (x >= displayWidth - r){
            circleBody.setVelocityX(-circleBody.getVelocityX());
            circleBody.setX(displayWidth - r - epsilon);
            setCollisionQueue();
        }
        if (y <= r){
            circleBody.setVelocityY(-circleBody.getVelocityY());
            circleBody.setY(r + epsilon);
            setCollisionQueue();
        }
        else if (y >= displayHeight - r){
            circleBody.setVelocityY(-circleBody.getVelocityY());
            circleBody.setY(displayHeight - r - epsilon);
            setCollisionQueue();
        }

    }
}

void ClosedSystem::updateKinematics(){
    // Update kinematics of bodies
    for (int i = 0; i < circleBodies.size(); i++){
        CircleBody& circleBody = circleBodies[i];
        float radius = circleBody.getShape().getRadius();
        circleBody.setX(circleBody.getX() + circleBody.getVelocityX() * timeStep);
        circleBody.setY(circleBody.getY() + circleBody.getVelocityY() * timeStep);
        circleBody.getShape().setPosition(circleBody.getX() - radius, circleBody.getY() - radius);
    }
}

void ClosedSystem::setCollisionQueue(){
    // Check collisions between bodies via sweep-and-prune
    for (int i = 0; i < circleBodies.size() - 1; i++){
        if (circleBodies[i + 1] < circleBodies[i]){
            std::swap(circleBodies[i], circleBodies[i + 1]);
        }
    }
    int minFrame = 10368000;
    for (int i = 0; i < circleBodies.size() - 1; i++){
        CircleBody& circleBody1 = circleBodies[i];
        for (int j = i + 1; j < circleBodies.size() && circleBodies[j].getX() - circleBody1.getX() <= 10.f; j++){
            CircleBody& circleBody2 = circleBodies[j];
            if (circleBody1.isCollidingWith(circleBody2)){
                circleBody1.resolvePenetration(circleBody2);
                collisionQueue.push(CollisionState(frameCount, &circleBody1, &circleBody2)); 
            }
            else{
                float dx = circleBody2.getX() - circleBody1.getX();
                float dy = circleBody2.getY() - circleBody1.getY();
                float dvx = circleBody2.getVelocityX() - circleBody1.getVelocityX();
                float dvy = circleBody2.getVelocityY() - circleBody1.getVelocityY();
                float r1 = circleBody1.getShape().getRadius();
                float r2 = circleBody2.getShape().getRadius();

                float a = dvx * dvx + dvy * dvy;
                float b = 2 * (dx * dvx + dy * dvy);
                float c = dx * dx + dy * dy - (r1 + r2) * (r1 + r2);
                float discriminant = b * b - 4 * a * c;
                if (discriminant >= 0.f){
                    float t1 = (-b - std::sqrtf(discriminant)) / (2 * a);
                    float t2 = (-b + std::sqrtf(discriminant)) / (2 * a);
                    int f1 = (int) std::ceil(t1 / timeStep) + frameCount;
                    int f2 = (int) std::ceil(t2 / timeStep) + frameCount;
                    if (t1 > 0.f && f1 > 0){
                        if (f1 < minFrame){
                            collisionQueue = std::queue<CollisionState>();
                            collisionQueue.push(CollisionState(f1, &circleBody1, &circleBody2));
                            minFrame = f1;
                        }
                        else if (f1 == minFrame){
                            collisionQueue.push(CollisionState(f1, &circleBody1, &circleBody2));
                        }
                    }
                    else if (t2 > 0.f && f2 > 0){
                        if (f2 < minFrame){
                            collisionQueue = std::queue<CollisionState>();
                            collisionQueue.push(CollisionState(f2, &circleBody1, &circleBody2));
                            minFrame = f2;
                        }
                        else if (f2 == minFrame){
                            collisionQueue.push(CollisionState(f2, &circleBody1, &circleBody2));
                        }
                    }
                }
            }
        }
    }
}

float ClosedSystem::getSystemEnergy(){
    float totalEnergy = 0.f;
    for (CircleBody& circleBody : circleBodies){
        float vx = circleBody.getVelocityX();
        float vy = circleBody.getVelocityY();
        totalEnergy += 0.5 * circleBody.getMass() * (vx * vx + vy * vy);
    }
    return totalEnergy;
}

void ClosedSystem::printSystemMetrics(int frameCycle){
    if (frameCount % frameCycle == 0){
        float latency = systemTimeAccumulator - timeStep * frameCount;
        std::cout << "Latency: " << latency << " seconds" << std::endl;
    }
}

void ClosedSystem::stressTest(int numObjects){
    while (numObjects-- > 0){
        while (!createCircleBody(Utils::getRandomFloat(0.f, displayWidth), Utils::getRandomFloat(0.f, displayHeight))){
            continue;
        }
        setCollisionQueue();
    }
}
