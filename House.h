// House.h
#ifndef HOUSE_H
#define HOUSE_H

#include "GameObject.h"

class House : public GameObject
{
protected:
    float x, y;

public:
    House(float px, float py);
};

class HouseType1 : public House
{
public:
    HouseType1(float px, float py);
    void draw() override;
};

class HouseType2 : public House
{
public:
    HouseType2(float px, float py);
    void draw() override;
};

#endif