#pragma once
#include "Body.hpp"
#include <SFML/Graphics/CircleShape.hpp>

class CircleBody: public Body{

    private:
        sf::CircleShape shape;

    public:
        CircleBody(float initialX, float initialY);
        
        sf::CircleShape& getShape();
        float getDistance(CircleBody& other);
        float getDistance(float x, float y);
        bool isCollidingWith(CircleBody& other);
        void elasticCollide(CircleBody& other);
        void resolvePenetration(CircleBody& other);

        std::string toString() const override;

};