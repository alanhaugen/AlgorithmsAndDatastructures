#include "rangeinput.h"

RangeInput::RangeInput() {}

RangeInput::RangeInput(Sprite *Button_, Sprite *Slider_, float min_, float max_, float Value_)
{
    Button = Button_;
    Slider = Slider_;
    min = min_;
    max = max_;
    Value = Value_;

    float difference = max - min;
    float ValueRatio = Value / difference;

    *Button->matrix.y = *Slider->matrix.y;

    *Button->matrix.x = (ValueRatio * Slider->width *  Slider->scaleX) + *Slider->matrix.x;
}



float RangeInput::Update(int mouseX, int mouseY, bool mouseDown)
{
    if(pressedLastUpdate && mouseDown)
    {
        *Button->matrix.x += mouseX - *Button->matrix.x;
    }
    else if(Button->IsPressed() == true)
    {
        pressedLastUpdate = true;
    }
    else if(Slider->IsPressed() == true)
    {
        *Button->matrix.x += mouseX - *Button->matrix.x;
        pressedLastUpdate = true;
    }
    else
    {
        pressedLastUpdate = false;
    }

    if(*Button->matrix.x  < *Slider->matrix.x)
    {
        *Button->matrix.x = *Slider->matrix.x;
    }
    else if(*Button->matrix.x > *Slider->matrix.x + Slider->width * Slider->scaleX)
    {
        *Button->matrix.x = *Slider ->matrix.x + Slider->width * Slider->scaleX;
    }

    float ButtonPosRatio = (*Button->matrix.x - *Slider->matrix.x) / (Slider->width * Slider->scaleX);
    float difference = max - min;

    Value = ButtonPosRatio * difference + min;

    Button->Update();
    Slider->Update();

    return Value;
}
