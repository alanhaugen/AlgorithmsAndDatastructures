#ifndef RANGEINPUT_H
#define RANGEINPUT_H

#include <core/application.h>

class RangeInput
{
public:

    Sprite* Slider;
    Sprite* Button;

    int lastX;
    int lastY;

    float Value;
    float min;
    float max;

    bool pressedLastUpdate = false;

    float Update(int x, int y);

    RangeInput(Sprite* Button_, Sprite* Slider_, float min_, float max_, float Value_);
    RangeInput();
};

#endif // RANGEINPUT_H
