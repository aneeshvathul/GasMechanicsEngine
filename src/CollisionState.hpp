#pragma once
#include "CircleBody.hpp"

class CollisionState{

    private:
        int frame;
        int first;
        int second;

    public:
        CollisionState();
        CollisionState(int f, int i1, int i2);
        int getFrame();
        int getFirst();
        int getSecond();
        void setFrame(int f);
        void setFirst(int i1);
        void setSecond(int i2);
        void setState(int f, int i1, int i2);

};