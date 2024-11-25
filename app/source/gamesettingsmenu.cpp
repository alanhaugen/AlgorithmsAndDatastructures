#include "gamesettingsmenu.h"
#include <core/containers/linkedlist.h>

extern LinkedList<GameSettings*> Presets;

void GameSettingsMenu::Update()
{
    PopUp::Update();



    if(GameSettingsNumber != nullptr)
    {
        delete GameSettingsNumber;
    }
    GameSettingsNumber = new Text("Game Settings " + String(index), renderer->windowWidth/2, 130, 1, 1, glm::vec2(0.5, 0));
    GameSettingsNumber->Update();

    CreateNewSettings->Update();

    if(CreateNewSettings->IsPressed() == true)
    {
        Presets.Append(new GameSettings());
        index++;
        Log(String(Presets.count));
    }
}

GameSettingsMenu::GameSettingsMenu() {
    if(Presets.Empty())
    {
        Presets.Append(new GameSettings());
    }
    createBackground();
    isOpen = true;

    CreateNewSettings = new Sprite("data/Rules-Page3.png", renderer->windowWidth/2, 160, 0.2, 0.2, glm::vec2(0.5, 0));

}
