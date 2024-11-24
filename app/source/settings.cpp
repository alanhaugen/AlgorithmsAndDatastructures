#include "settings.h"

Settings::Settings()
{
    createBackground();
    createClosePopUp();
    openPopUp = new Sprite("data/Cog.png", renderer->windowWidth - 5, 5, 2, 2, glm::vec2(1, 0));
}

void Settings::Update()
{
    PopUp::Update();
}

