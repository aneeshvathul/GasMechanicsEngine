#include "CollisionState.hpp"

CollisionState::CollisionState(){
    frame = 10368000;
    first = -1;
    second = -1;
}

CollisionState::CollisionState(int f, int i1, int i2){
    frame = f;
    first = i1;
    second = i2;
}

int CollisionState::getFrame(){
    return frame;
}

int CollisionState::getFirst(){
    return first;
}

int CollisionState::getSecond(){
    return second;
}

void CollisionState::setFrame(int f){
    frame = f;
}

void CollisionState::setFirst(int i1){
    first = i1;
}

void CollisionState::setSecond(int i2){
    second = i2;
}

void CollisionState::setState(int f, int i1, int i2){
    frame = f;
    first = i1;
    second = i2;
}