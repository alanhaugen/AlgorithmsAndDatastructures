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
}

void PopUp::open()
{
    isOpen = true;
}

void PopUp::close()
{
    isOpen = false;
}

void PopUp::createBackground()
{
    BackGround = new Sprite(
        "data/stdPopUp.png",
        renderer->windowWidth / 2, 100,
        1, 1,
        glm::vec2(0.5, 0)
        );
}

void PopUp::createClosePopUp()
{
    closePopUp = new Sprite("data/Button-Back.png", renderer->windowWidth / 2, renderer->windowHeight - 30, 0.7, 0.7, glm::vec2(0.5, 1));
}

void PopUp::Init()
{
}
