#pragma once
#include <random>
#include <utility>
#include <SFML/Graphics/Color.hpp>

class Utils{

    private:
        static const inline std::vector<sf::Color> colors = {
            sf::Color::Red,
            sf::Color::Green,
            sf::Color::Blue,
            sf::Color::Yellow,
            sf::Color::Magenta,
            sf::Color::Cyan,
        };

    public:
        static long double getRandomDouble(long double min, long double max);
        static const sf::Color& getRandomColor();

};