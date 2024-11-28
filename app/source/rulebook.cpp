#include "rulebook.h"

Rulebook::Rulebook(bool isMenu_)
{
    createBackground();

    isMenu = isMenu_;

    if(isMenu == true)
    {
        isOpen = true;
        openPopUp = nullptr;
        closePopUp = nullptr;
    }
    else
    {
        openPopUp = new Sprite("data/SPRITE-RulebookPNG.png", 70, renderer->windowHeight - 10, 1.2, 1.2, glm::vec2(0.5, 1));
        createClosePopUp();

        hoverText = new Text("Rulebook", 0, 0, 0.7, 0.7, glm::vec2(0.5, 1));

        *hoverText->matrix.x = *openPopUp->matrix.x;
        *hoverText->matrix.y = *openPopUp->matrix.y - 70;
    }

    leftArrow  = new Sprite("data/B_ArrowLEFT.png", 250, renderer->windowHeight - 135, 1, 1, glm::vec2(0, 0.5));
    rightArrow = new Sprite("data/B_ArrowLEFT.png", renderer->windowWidth - 220, renderer->windowHeight - 135, 1, 1, glm::vec2(1, 0.5));
    rightArrow->FlipHorizontal();

    //I don't like this ...  :(
    Pages.Add(new Sprite("data/Rules-Page01.png", renderer->windowWidth / 2, renderer->windowHeight / 2, 0.8, 0.8, glm::vec2(0.5,0.5)));
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

    PopUp::Update();

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

        if((leftArrow->IsPressed() == true || input.Pressed(input.Key.LEFT)) && index > 0)
        {
            index--;
        }

        if((rightArrow->IsPressed() == true || input.Pressed(input.Key.RIGHT)) && index + 1 < Pages.Size())
        {
            index++;
        }
        Pages[index]->Update();
    }
}
