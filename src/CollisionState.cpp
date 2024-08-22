#include "CollisionState.hpp"


CollisionState::CollisionState(int f, CircleBody* p1, CircleBody* p2){
    frame = f;
    first = p1;
    second = p2;
}

int CollisionState::getFrame() const{
    return frame;
}

CircleBody* CollisionState::getFirst() const{
    return first;
}

CircleBody* CollisionState::getSecond() const{
    return second;
}
