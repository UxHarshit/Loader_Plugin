//
// Created by hurri on 25-07-2021.
//
#pragma once
#include <map>
#include <stdio.h>
#include <vector>
#include <string>
#ifndef GLPLUGIN_STRUCT_H
#define GLPLUGIN_STRUCT_H
enum Style{
    FILL =0,
    STROKE = 1,
    FILL_AND_STROKE = 2

};
struct vector2{
    float x,y;
};
struct vector3{
    float x,y,z;
};
struct vector4{
    float x,y,z,w;
};
#endif //GLPLUGIN_STRUCT_H
