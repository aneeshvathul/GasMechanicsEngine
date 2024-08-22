#include "CircleBody.hpp"

CircleBody::CircleBody(float initialX, float initialY) : Body(initialX, initialY){
    float radius = std::sqrtf(150.f * getMass());
    shape.setRadius(radius);
    shape.setPosition(initialX - radius, initialY - radius);
    shape.setFillColor(getColor());
}

sf::CircleShape& CircleBody::getShape(){
    return shape;
}

float CircleBody::getDistance(CircleBody& other){
    return std::sqrtf((getX() - other.getX()) * (getX() - other.getX()) + (getY() - other.getY()) * (getY() - other.getY()));
}

float CircleBody::getDistance(float x, float y){
    return std::sqrtf((getX() - x) * (getX() - x) + (getY() - y) * (getY() - y));
}

bool CircleBody::isCollidingWith(CircleBody& other){
    return getDistance(other) < std::abs(shape.getRadius() + other.getShape().getRadius());
}

void CircleBody::elasticCollide(CircleBody& other){
    float m1 = getMass();
    float m2 = other.getMass();
    float x1 = getX();
    float x2 = other.getX();
    float y1 = getY();
    float y2 = other.getY();
    float v1x = getVelocityX();
    float v2x = other.getVelocityX();
    float v1y = getVelocityY();
    float v2y = other.getVelocityY();
    float energyBefore1 = m1 * (v1x * v1x + v1y * v1y);
    float energyBefore2 = m2 * (v2x * v2x + v2y * v2y);
    float energyBeforeTotal = energyBefore1 + energyBefore2;

    // Collide bodies
    float coeffBase = ((v1x - v2x) * (x1 - x2) + (v1y - v2y) * (y1 - y2)) / ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    float coeff1 = (2 * m2) / (m1 + m2) * coeffBase;
    float coeff2 = (2 * m1) / (m1 + m2) * coeffBase;
    setVelocityX(v1x - coeff1 * (x1 - x2));
    setVelocityY(v1y - coeff1 * (y1 - y2));
    other.setVelocityX(v2x - coeff1 * (x2 - x1));
    other.setVelocityY(v2y - coeff1 * (y2 - y1));

    // Redistribute energy
    float energyAfter1 = m1 * (getVelocityX() * getVelocityX() + getVelocityY() * getVelocityY());
    float energyAfter2 = m2 * (other.getVelocityX() * other.getVelocityX() + other.getVelocityY() * other.getVelocityY());
    float energyAfterTotal = energyAfter1 + energyAfter2;
    float newEnergyAfter1 = energyAfter1 / energyAfterTotal * energyBeforeTotal;
    float newEnergyAfter2 = energyAfter2 / energyAfterTotal * energyBeforeTotal;
    float vMag1a = std::sqrtf(getVelocityX() * getVelocityX() + getVelocityY() * getVelocityY());
    float vMag2a = std::sqrtf(other.getVelocityX() * other.getVelocityX() + other.getVelocityY() * other.getVelocityY());
    float vMag1b = std::sqrtf(newEnergyAfter1 / m1);
    float vMag2b = std::sqrtf(newEnergyAfter2 / m2);
    setVelocityX(getVelocityX() * vMag1b / vMag1a);
    setVelocityY(getVelocityY() * vMag1b / vMag1a);
    other.setVelocityX(other.getVelocityX() * vMag2b / vMag2a);
    other.setVelocityY(other.getVelocityY() * vMag2b / vMag2a);

    // Correction factor
    setX(getX() + getVelocityX() / 120.f);
    setY(getY() + getVelocityY() / 120.f);
    other.setX(other.getX() + other.getVelocityX() / 120.f);
    other.setY(other.getY() + other.getVelocityY() / 120.f);
}

void CircleBody::resolvePenetration(CircleBody& other){
    float dx = other.getX() - getX();
    float dy = other.getY() - getY();
    float mag = getDistance(other);
    float diff = shape.getRadius() + other.getShape().getRadius() - mag;
    float coeff = diff / (2 * mag);
    setX(getX() - coeff * dx);
    setY(getY() - coeff * dy);
    other.setX(other.getX() + coeff * dx);
    other.setY(other.getY() + coeff * dy);
}

std::string CircleBody::toString() const{
    return Body::toString() + ", Radius: " + std::to_string(shape.getRadius());
}