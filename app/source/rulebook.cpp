#include <core/application.h>
#include "rulebook.h"

Rulebook::Rulebook(bool isMenu_)
{
    isMenu = isMenu_;

    if(isMenu == true)
    {
        isOpen = true;
        openPopUp = nullptr;
        closePopUp = nullptr;
    }
    else
    {
        closePopUp = new Sprite("data/Button-Back.png", renderer->windowWidth / 2, renderer->windowHeight - 30, 0.7, 0.7, glm::vec2(0.5, 1));
        openPopUp = new Sprite("data/SPRITE-RulebookPNG.png", 10, renderer->windowHeight - 10, 1.2, 1.2, glm::vec2(0, 1));
    }

    leftArrow  = new Sprite("data/Rulebook-Arrow.png", 50, renderer->windowHeight / 2, 1, 1, glm::vec2(0, 0.5));
    rightArrow = new Sprite("data/Rulebook-Arrow.png", renderer->windowWidth - 50, renderer->windowHeight / 2, 1, 1, glm::vec2(1, 0.5));
    rightArrow->FlipHorizontal();
    BackGround = new Sprite("data/stdPopUp.png", renderer->windowWidth / 2, 100, 1, 1, glm::vec2(0.5, 0));

    //I don't like this ...  :(
    Pages.Add(new Sprite("data/Rules-Page0.png", renderer->windowWidth / 2, renderer->windowHeight / 2, 1, 1, glm::vec2(0.5,0.5)));
    Pages.Add(new Sprite("data/Rules-Page1.png", renderer->windowWidth / 2, renderer->windowHeight / 2, 1, 1, glm::vec2(0.5,0.5)));
    Pages.Add(new Sprite("data/Rules-Page2.png", renderer->windowWidth / 2, renderer->windowHeight / 2, 1, 1, glm::vec2(0.5,0.5)));
    Pages.Add(new Sprite("data/Rules-Page3.png", renderer->windowWidth / 2, renderer->windowHeight / 2, 1, 1, glm::vec2(0.5,0.5)));
    Pages.Add(new Sprite("data/Rules-Page4.png", renderer->windowWidth / 2, renderer->windowHeight / 2, 1, 1, glm::vec2(0.5,0.5)));
    Pages.Add(new Sprite("data/Rules-Page5.png", renderer->windowWidth / 2, renderer->windowHeight / 2, 1, 1, glm::vec2(0.5,0.5)));
    Pages.Add(new Sprite("data/Rules-Page6.png", renderer->windowWidth / 2, renderer->windowHeight / 2, 1, 1, glm::vec2(0.5,0.5)));
    Pages.Add(new Sprite("data/Rules-Page7.png", renderer->windowWidth / 2, renderer->windowHeight / 2, 1, 1, glm::vec2(0.5,0.5)));

}

void Rulebook::Update()
{

    if(isOpen)
    {
        if(index != 0)
        {
            leftArrow->Update();
        }

        if(index != Pages.Size() - 1)
        {
            rightArrow->Update();
        }

        if(leftArrow->IsPressed() == true && index > 0)
        {
            index--;
        }

        if(rightArrow->IsPressed() == true && index + 1 < Pages.Size())
        {
            index++;
        }

        if(closePopUp != nullptr)
        {
            closePopUp->Update();
            if(closePopUp->IsPressed() == true)
            {
                isOpen = false;
            }
        }

        BackGround->Update();
        Pages[index]->Update();
    }

    if(isMenu == false)
    {
        openPopUp->Update();
        if(openPopUp->IsPressed() == true)
        {
            open();
        }
    }
}

void Rulebook::open()
{
    isOpen = true;
}
