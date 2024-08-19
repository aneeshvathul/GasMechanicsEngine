#include "CircleBody.hpp"

CircleBody::CircleBody(long double initialX, long double initialY) : Body(initialX, initialY){
    long double radius = std::sqrtl(300.0 * getMass());
    shape.setRadius(radius);
    shape.setPosition(initialX - radius, initialY - radius);
    shape.setFillColor(getColor());
}

sf::CircleShape& CircleBody::getShape(){
    return shape;
}

long double CircleBody::getDistance(CircleBody& other){
    return std::sqrtl((getX() - other.getX()) * (getX() - other.getX()) + (getY() - other.getY()) * (getY() - other.getY()));
}

bool CircleBody::isCollidingWith(CircleBody& other){
    return getDistance(other) <= std::abs(shape.getRadius() + other.getShape().getRadius());
}