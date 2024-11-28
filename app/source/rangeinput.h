#ifndef RANGEINPUT_H
#define RANGEINPUT_H

#include <core/application.h>

class RangeInput
{
public:

    Sprite* Slider; //AnchorPoint should preferrably be 0, 0.5
    Sprite* Button; //AnchorPoint should preferrably be 0.5, 0.5

    float Value;
    float min;
    float max;

    bool pressedLastUpdate = false;

    float Update(int x, int y, bool mouseDown);

    RangeInput(Sprite* Button_, Sprite* Slider_, float min_, float max_, float Value_);
    RangeInput();
};

#endif // RANGEINPUT_H
