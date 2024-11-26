#include "rangeinput.h"
#include "cursor.h"

RangeInput::RangeInput() {}

RangeInput::RangeInput(Sprite *Button_, Sprite *Slider_, float min_, float max_, float Value_)
{
    Button = Button_;
    Slider = Slider_;
    min = min_;
    max = max_;
    Value = Value_;
}



float RangeInput::Update(int x, int y)
{
    Button->Update();
    Slider->Update();

    if(Button->IsPressed() == true)
    {
        if(pressedLastUpdate == true)
        {
            *Button->matrix.x += x - lastX;
        }

        lastY = y;
        lastX = x;
        pressedLastUpdate = true;
    }
    else
    {
        pressedLastUpdate = false;
    }

    return Value;
}
