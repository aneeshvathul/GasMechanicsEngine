#include "Forces.hpp"

void Forces::elasticCollide(CircleBody& circleBody1, CircleBody& circleBody2){
    long double m1 = circleBody1.getMass();
    long double m2 = circleBody2.getMass();
    long double x1 = circleBody1.getX();
    long double x2 = circleBody2.getX();
    long double y1 = circleBody1.getY();
    long double y2 = circleBody2.getY();
    long double v1x = circleBody1.getVelocityX();
    long double v2x = circleBody2.getVelocityX();
    long double v1y = circleBody1.getVelocityY();
    long double v2y = circleBody2.getVelocityY();
    long double coeff1 = (2 * m2) / (m1 + m2) * ((v1x - v2x) * (x1 - x2) + (v1y - v2y) * (y1 - y2)) / ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    long double coeff2 = (2 * m1) / (m1 + m2) * ((v2x - v1x) * (x2 - x1) + (v2y - v1y) * (y2 - y1)) / ((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    circleBody1.setVelocityX(v1x - coeff1 * (x1 - x2));
    circleBody1.setVelocityY(v1y - coeff1 * (y1 - y2));
    circleBody2.setVelocityX(v2x - coeff1 * (x2 - x1));
    circleBody2.setVelocityY(v2y - coeff1 * (y2 - y1));
}