#include "settings.h"

extern float audioSetting;

Settings::Settings()
{

    createBackground();
    createClosePopUp();
    openPopUp = new Sprite("data/Cog.png", renderer->windowWidth - 50, 20, 2, 2, glm::vec2(0.5, 0));
    hoverText = new Text("Settings", 0, 0, 0.7, 0.7, glm::vec2(0.5, 0));

    Sprite* rangeSlider = new Sprite(
        "data/ButtonBASE-Rectangle.png", 0, renderer->windowHeight/2, 1, 0.1, glm::vec2(0, 0.5)
        );
    *rangeSlider->matrix.x = renderer->windowWidth / 2 - rangeSlider->width * rangeSlider->scaleX / 2;
    Sprite* rangeButton = new Sprite("data/CheckboxEmpty.png", 0, 0, 0.2, 0.2, glm::vec2(0.5, 0.5));
    Audio = new RangeInput(rangeButton, rangeSlider, 0, 100, 50);

    *hoverText->matrix.x = *openPopUp->matrix.x;
    *hoverText->matrix.y = *openPopUp->matrix.y + 70;
}

void Settings::Update()
{
    PopUp::Update();

    if(isOpen)
    {
        audioSetting = Audio->Update(input.Mouse.x, input.Mouse.y, input.Mouse.Down);
    }
}

