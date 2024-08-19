#pragma once
#include <utility>
#include <iostream>
#include <cmath>
#include "Utils.hpp"
#include <SFML/Graphics/Color.hpp>

class Body{

    private:
        long double mass;
        sf::Color color;
        std::pair<long double, long double> position;
        std::pair<long double, long double> velocity;
        std::pair<long double, long double> acceleration;

    public:
        Body(long double initialX, long double initialY);

        long double getMass();
        const sf::Color& getColor();

        long double getX();
        long double getY();
        long double getVelocityX();
        long double getVelocityY();
        long double getAccelerationX();
        long double getAccelerationY();
        void setMass(long double m);
        void setColor(const sf::Color& c);
        void setX(long double x);
        void setY(long double y);
        void setVelocityX(long double xv);
        void setVelocityY(long double yv);
        void setAccelerationX(long double xa);
        void setAccelerationY(long double ya);

};