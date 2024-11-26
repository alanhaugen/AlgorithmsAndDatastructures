#include "settings.h"

extern bool isFullscreen;

Settings::Settings()
{

    createBackground();
    createClosePopUp();
    openPopUp = new Sprite("data/Cog.png", renderer->windowWidth - 75, 10, 2, 2, glm::vec2(0.5, 0));
    hoverText = new Text("Settings", 0, 0, 0.7, 0.7, glm::vec2(0.5, 0));

    //Fullscreen/Windowed
    fullscreenText = new Text("Fullscreen", 0, 0, 1, 1, glm::vec2(1, 0.5));

    fullscreenChecked = new Sprite("data/CheckboxChecked.png", renderer->windowWidth / 2, renderer->windowHeight / 2 - 50, 0.25, 0.25, glm::vec2(0, 0.5));
    fullscreenUnchecked = new Sprite("data/CheckboxEmpty.png", renderer->windowWidth / 2, renderer->windowHeight / 2 - 50, 0.25, 0.25, glm::vec2(0, 0.5));

    *fullscreenText->matrix.y = *fullscreenUnchecked->matrix.y;
    *fullscreenText->matrix.x = *fullscreenUnchecked->matrix.x - 186;

    //Audio
    audioText = new Text("Audio", 0, renderer->windowHeight / 2, 1, 1, glm::vec2(1, 0.5));

    Sprite* rangeSlider = new Sprite(
        "data/ButtonBASE-Rectangle.png", 0, renderer->windowHeight / 2, 1, 0.1, glm::vec2(0, 0.5)
        );
    *rangeSlider->matrix.x = renderer->windowWidth / 2 - rangeSlider->width * rangeSlider->scaleX / 2;

    Sprite* rangeButton = new Sprite("data/CheckboxEmpty.png", 0, 0, 0.2, 0.2, glm::vec2(0.5, 0.5));

    Audio = new RangeInput(rangeButton, rangeSlider, 0.0f, 2.0f, audio->audioVolume);

    *audioText->matrix.x = *rangeSlider->matrix.x - 10;



    *hoverText->matrix.x = *openPopUp->matrix.x;
    *hoverText->matrix.y = *openPopUp->matrix.y + 70;
}

void Settings::Update()
{
    PopUp::Update();

    if(isOpen)
    {
        //Fullscreen
        fullscreenText->Update();
        if(Locator::renderer->fullscreen == true)
        {
            fullscreenChecked->Update();

            if(fullscreenChecked->IsPressed() == true)
            {
                Locator::renderer->Windowed();
            }
        }
        else
        {
            fullscreenUnchecked->Update();

            if(fullscreenUnchecked->IsPressed() == true)
            {
                Locator::renderer->Fullscreen();
            }
        }

        //Audio
        audioText->Update();
        audio->audioVolume = Audio->Update(input.Mouse.x, input.Mouse.y, input.Mouse.Down);
    }
}

