#pragma once
#include "Body.hpp"
#include <SFML/Graphics/CircleShape.hpp>

class CircleBody: public Body{

    private:
        sf::CircleShape shape;

    public:
        CircleBody(long double initialX, long double initialY);
        
        sf::CircleShape& getShape();
        long double getDistance(CircleBody& other);
        bool isCollidingWith(CircleBody& other);

};