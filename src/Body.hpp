#pragma once
#include <utility>
#include <cmath>
#include "Utils.hpp"
#include <SFML/Graphics/Color.hpp>

class Body{

    private:
        float mass;
        sf::Color color;
        std::pair<float, float> position;
        std::pair<float, float> velocity;
        std::pair<float, float> acceleration;

    public:
        Body(float initialX, float initialY);

        float getMass();
        const sf::Color& getColor();

        float getX();
        float getY();
        float getVelocityX();
        float getVelocityY();
        float getAccelerationX();
        float getAccelerationY();
        void setMass(float m);
        void setColor(const sf::Color& c);
        void setX(float x);
        void setY(float y);
        void setVelocityX(float vx);
        void setVelocityY(float vy);
        void setAccelerationX(float ax);
        void setAccelerationY(float ay);

        virtual std::string toString() const;

};