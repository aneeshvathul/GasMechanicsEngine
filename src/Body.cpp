#include "Body.hpp"

Body::Body(float initialX, float initialY){
    float initialMass = Utils::getRandomFloat(0.5f, 5.f);
    const sf::Color& initialColor = Utils::getRandomColor();
    float initialXV = Utils::getRandomFloat(-120.f, 120.f);
    float initialYV = Utils::getRandomFloat(-120.f, 120.f);
    float initialXA = 0.f;
    float initialYA = 0.f;
    
    setMass(initialMass);
    setColor(initialColor);
    setX(initialX);
    setY(initialY);
    setVelocityX(initialXV);
    setVelocityY(initialYV);
    setAccelerationX(initialXA);
    setAccelerationY(initialYA);   
}

float Body::getMass(){
    return mass;
}

const sf::Color& Body::getColor(){
    return color;
}

float Body::getX(){
    return position.first;
}

float Body::getY(){
    return position.second;
}

float Body::getVelocityX(){
    return velocity.first;
}

float Body::getVelocityY(){
    return velocity.second;
}

float Body::getAccelerationX(){
    return acceleration.first;
}

float Body::getAccelerationY(){
    return acceleration.second;
}

void Body::setMass(float m){
    mass = m;
}

void Body::setColor(const sf::Color& c){
    color = c;
}

void Body::setX(float x){
    position.first = x;
}

void Body::setY(float y){
    position.second = y;
}

void Body::setVelocityX(float vx){
    velocity.first = vx;
}

void Body::setVelocityY(float vy){
    velocity.second = vy;
}

void Body::setAccelerationX(float ax){
    acceleration.first = ax;
}

void Body::setAccelerationY(float ay){
    acceleration.second = ay;
}

std::string Body::toString() const{
    return "Mass: " + std::to_string(mass) + ", VX: " + std::to_string(velocity.first) + ", VY: " + std::to_string(velocity.second);
}

