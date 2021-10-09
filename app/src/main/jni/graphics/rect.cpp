//
// Created by hurri on 22-09-2021.
//

#include "rect.h"


int rect::getLeft() {
    return env->GetIntField(this->rectObj, this->leftId);
}

int rect::getRight(){
    return env->GetIntField(this->rectObj, this->rightId);
}

int rect::getTop(){
    return env->GetIntField(this->rectObj, this->topId);
}

int rect::getBottom(){
    return env->GetIntField(this->rectObj, this->bottomId);
}

int rect::getWidth() {
    return getRight() - getLeft();
}

int rect::getHeight() {
    return getBottom() - getTop();
}