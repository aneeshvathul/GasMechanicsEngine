#pragma once
#include "CircleBody.hpp"

class CollisionState{

    private:
        int frame;
        CircleBody* first;
        CircleBody* second;

    public:
        CollisionState(int f, CircleBody* p1, CircleBody* p2);
        int getFrame() const;
        CircleBody* getFirst() const;
        CircleBody* getSecond() const;

};