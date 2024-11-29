#include "popup.h"

PopUp::PopUp()
{
    createBackground();
}

void PopUp::Update()
{
    if(isOpen)
    {
        BackGround->Update();

        if(closePopUp != nullptr)
        {
            closePopUp->Update();
            if(closePopUp->IsPressed() == true)
            {
                close();
            }
        }
    }
    if(openPopUp != nullptr)
    {
        openPopUp->Update();
        if(openPopUp->IsPressed() == true)
        {
            open();
        }
    }

    if (isOpen == false)
    {
        if (hoverText != nullptr && openPopUp != nullptr && openPopUp->IsHoveredOver() && canOpen)
        {
            hoverText->Update();
        }
    }
}

void PopUp::open()
{
    if(canOpen == false)
    {
        return;
    }
    isOpen = true;
}

void PopUp::close()
{
    isOpen = false;
}

void PopUp::createBackground()
{
    BackGround = new Sprite(
        "data/SettingsMenuBackground.png",
        renderer->windowWidth / 2, 50,
        1, 1,
        glm::vec2(0.5, 0)
        );
}

void PopUp::createClosePopUp()
{
    closePopUp = new Sprite("data/B_Close.png", renderer->windowWidth / 2, renderer->windowHeight - 90, 0.7, 0.7, glm::vec2(0.5, 1));
}

void PopUp::Init()
{
}
