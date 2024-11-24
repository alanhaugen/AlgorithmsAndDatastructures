#include "settings.h"

Settings::Settings()
{

    createBackground();
    createClosePopUp();
    openPopUp = new Sprite("data/Cog.png", renderer->windowWidth - 50, 20, 2, 2, glm::vec2(0.5, 0));
    hoverText = new Text("Settings", 0, 0, 0.7, 0.7, glm::vec2(0.5, 0));

    *hoverText->matrix.x = *openPopUp->matrix.x;
    *hoverText->matrix.y = *openPopUp->matrix.y + 70;

}

void Settings::Update()
{
    PopUp::Update();
}

