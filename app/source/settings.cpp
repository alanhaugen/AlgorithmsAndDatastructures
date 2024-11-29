#include "settings.h"

Settings::Settings(){}

Settings::Settings(bool isMenu_)
{
    if(isMenu_)
    {
        isOpen = true;
    }

    createBackground();
    if(isMenu_)
    {
        BackGround->scaleY = 0.6;
        *BackGround->matrix.y += 170;
    }

    if(isMenu_ != true)
    {
        createClosePopUp();
        openPopUp = new Sprite("data/Cog.png", renderer->windowWidth - 90, 10, 2, 2, glm::vec2(0.5, 0));
        hoverText = new Text("Settings", 0, 0, 0.7, 0.7, glm::vec2(0.5, 0));
    }

    //Fullscreen/Windowed
    fullscreenText = new Text("Fullscreen", 0, 0, 1, 1, glm::vec2(1, 0.5));

    fullscreenChecked = new Sprite("data/CheckboxChecked.png", renderer->windowWidth / 2 - 215, renderer->windowHeight / 2 - 125, 0.25, 0.25, glm::vec2(0, 0.5));
    fullscreenUnchecked = new Sprite("data/CheckboxEmpty.png", renderer->windowWidth / 2 - 215, renderer->windowHeight / 2 - 125, 0.25, 0.25, glm::vec2(0, 0.5));

    if(isMenu_ == true)
    {
        *fullscreenChecked->matrix.y += 40;
        *fullscreenUnchecked->matrix.y += 40;
    }

    *fullscreenText->matrix.y = *fullscreenUnchecked->matrix.y;
    *fullscreenText->matrix.x = *fullscreenUnchecked->matrix.x - 50;

    //SFX Audio
    audioText = new Text("SFX volume", 0, renderer->windowHeight / 2 - 25, 1, 1, glm::vec2(1, 0.5));

    Sprite* rangeSlider = new Sprite(
        "data/ButtonBASE-Rectangle.png", 0, renderer->windowHeight / 2 - 25, 1, 0.1, glm::vec2(0, 0.5)
        );
    *rangeSlider->matrix.x = renderer->windowWidth / 2 - rangeSlider->width * rangeSlider->scaleX / 2;

    Sprite* rangeButton = new Sprite("data/CheckboxEmpty.png", 0, 0, 0.2, 0.2, glm::vec2(0.5, 0.5));

    if(isMenu_ == true)
    {
        *rangeSlider->matrix.y += 40;
        *audioText->matrix.y += 40;
    }

    *audioText->matrix.x = *rangeSlider->matrix.x - 10;

    Audio = new RangeInput(rangeButton, rangeSlider, 0.0f, 2.0f, audio->audioVolume);



    //Music Audio
    musicAudioText = new Text("Music volume", 0, renderer->windowHeight / 2 + 75, 1, 1, glm::vec2(1, 0.5));


    Sprite* musicRangeSlider = new Sprite (
        "data/ButtonBASE-Rectangle.png", 0, renderer->windowHeight / 2 + 75, 1, 0.1, glm::vec2(0, 0.5)
        );

    *musicRangeSlider->matrix.x = renderer->windowWidth / 2 - musicRangeSlider->width * musicRangeSlider->scaleX / 2;

    Sprite* musicRangeButton = new Sprite("data/CheckboxEmpty.png", 0, 0, 0.2, 0.2, glm::vec2(0.5, 0.5));

    if(isMenu_ == true)
    {
        *musicRangeSlider->matrix.y += 40;
        *musicAudioText->matrix.y += 40;
    }

    *musicAudioText->matrix.x = *musicRangeSlider->matrix.x - 10;

    musicAudio = new RangeInput(musicRangeButton, musicRangeSlider, 0.0f, 2.0f, audio->audioVolumeMusic);


    if(hoverText != nullptr && openPopUp != nullptr)
    {
        *hoverText->matrix.x = *openPopUp->matrix.x;
        *hoverText->matrix.y = *openPopUp->matrix.y + 70;
    }
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

        musicAudioText->Update();
        audio->audioVolumeMusic = musicAudio->Update(input.Mouse.x, input.Mouse.y, input.Mouse.Down);
    }
}

