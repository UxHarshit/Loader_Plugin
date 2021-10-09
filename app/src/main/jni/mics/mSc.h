//
// Created by hurri on 23-09-2021.
//

#ifndef GLPLUGIN_MSC_H
#define GLPLUGIN_MSC_H
using namespace std;
class Vector2 {
public:
    float x;
    float y;
    Vector2(){
        this->x =0;
        this->y = 0;
    }
    Vector2(float x,float y){
        this->x=x;
        this->y=y;
    }
    static Vector2 Zero(){
        return Vector2(0.0f,0.0f);
    }
    bool operator!=(const Vector2 &src) const{
        return (src.x != x) || (src.y!=y);
    }
    Vector2 &operator +=(const Vector2 &v){
        x += v.x;
        y += v.y;
        return *this;
    }
    Vector2 &operator -=(const Vector2 &v){
        x -= v.x;
        y -= v.y;
        return *this;
    }
};
#endif //GLPLUGIN_MSC_H
