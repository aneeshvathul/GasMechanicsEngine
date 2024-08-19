#include "Body.hpp"

Body::Body(long double initialX, long double initialY){
    long double initialMass = Utils::getRandomDouble(0.5, 5.0);
    const sf::Color& initialColor = Utils::getRandomColor();
    long double initialXV = Utils::getRandomDouble(-200.0, 200.0);
    long double initialYV = Utils::getRandomDouble(-200.0, 200.0);
    long double initialXA = 0.0;
    long double initialYA = 0.0;
    
    setMass(initialMass);
    setColor(initialColor);
    setX(initialX);
    setY(initialY);
    setVelocityX(initialXV);
    setVelocityY(initialYV);
    setAccelerationX(initialXA);
    setAccelerationY(initialYA);   
}

long double Body::getMass(){
    return mass;
}

const sf::Color& Body::getColor(){
    return color;
}

long double Body::getX(){
    return position.first;
}

long double Body::getY(){
    return position.second;
}

long double Body::getVelocityX(){
    return velocity.first;
}

long double Body::getVelocityY(){
    return velocity.second;
}

long double Body::getAccelerationX(){
    return acceleration.first;
}

long double Body::getAccelerationY(){
    return acceleration.second;
}

void Body::setMass(long double m){
    mass = m;
}

void Body::setColor(const sf::Color& c){
    color = c;
}

void Body::setX(long double x){
    position.first = x;
}

void Body::setY(long double y){
    position.second = y;
}

void Body::setVelocityX(long double xv){
    velocity.first = xv;
}

void Body::setVelocityY(long double yv){
    velocity.second = yv;
}

void Body::setAccelerationX(long double xa){
    acceleration.first = xa;
}

void Body::setAccelerationY(long double ya){
    acceleration.second = ya;
}

