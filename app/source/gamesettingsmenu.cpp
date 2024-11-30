#include "gamesettingsmenu.h"
#include <core/containers/linkedlist.h>

extern LinkedList<GameSettings*> Presets;

extern int Gold;
extern int Rounds;
extern int RestockCost;
extern bool RestockEndTurn;
extern int RandomCardCost;
extern int PlacementsPerTurn;
extern int MovesPerTurn;

GameSettingsMenu::GameSettingsMenu()
{
    if (Presets.Empty())
    {
        Presets.Append(new GameSettings());
    }

    createBackground();
    isOpen = true;

    CreateNewSettings  = new Sprite("data/Rules-Page3.png", renderer->windowWidth/2, 160, 0.2, 0.2, glm::vec2(0.5, 0));
    GameSettingsNumber = new Text("Game Settings " + String(index), renderer->windowWidth/2, 130, 1, 1, glm::vec2(0.5, 0));

    GoldNumber = new Text("Gold: " + String(Gold), renderer->windowWidth/2, 310, 1, 1, glm::vec2(0.5, 0));
    RoundNumber = new Text("Rounds: " + String(Rounds), renderer->windowWidth/2, 410, 1, 1, glm::vec2(0.5, 0));

    AddGold = new Sprite("data/arrow.png", renderer->windowWidth/2 + 300, 300, 0.7, 0.7, glm::vec2(0.5, 0));
    ReduceGold = new Sprite("data/arrow.png", renderer->windowWidth/2 - 300, 300, 0.7, 0.7, glm::vec2(0.5, 0));
    ReduceGold->FlipHorizontal();
    AddRounds = new Sprite("data/arrow.png", renderer->windowWidth/2 + 300, 410, 0.7, 0.7, glm::vec2(0.5, 0));
    ReduceRounds =  new Sprite("data/arrow.png", renderer->windowWidth/2 - 300, 410, 0.7, 0.7, glm::vec2(0.5, 0));
    ReduceRounds->FlipHorizontal();
}

void GameSettingsMenu::Update()
{
    PopUp::Update();
    GameSettingsNumber->Update();
    GoldNumber->Update();
    CreateNewSettings->Update();
    AddGold->Update();
    ReduceGold->Update();
    RoundNumber->Update();
    AddRounds->Update();
    ReduceRounds->Update();
    if(CreateNewSettings->IsPressed() == true)
    {
        Presets.Append(new GameSettings());
        index++;

        Log(String(Presets.count));
        if (GameSettingsNumber != nullptr)
        {
            delete GameSettingsNumber;
        }

        GameSettingsNumber = new Text("Game Settings " + String(index), renderer->windowWidth/2, 130, 1, 1, glm::vec2(0.5, 0));

    }
    if(AddGold->IsPressed() == true)
    {
        Gold += 10;
        if (GoldNumber != nullptr)
        {
            delete GoldNumber;
        }

        GoldNumber = new Text("Gold: " + String(Gold), renderer->windowWidth/2, 310, 1, 1, glm::vec2(0.5, 0));

    }
    if(ReduceGold->IsPressed())
    {
        Gold -= 10;
        if (GoldNumber != nullptr)
        {
            delete GoldNumber;
        }

        GoldNumber = new Text("Gold: " + String(Gold), renderer->windowWidth/2, 310, 1, 1, glm::vec2(0.5, 0));

    }

    if(AddRounds->IsPressed() == true)
    {
        Rounds += 1;
        if (RoundNumber != nullptr)
        {
            delete RoundNumber;
        }

        RoundNumber = new Text("Rounds: " + String(Rounds), renderer->windowWidth/2, 410, 1, 1, glm::vec2(0.5, 0));

    }

    if(ReduceRounds->IsPressed())
    {
        Rounds -= 1;
        if (RoundNumber != nullptr)
        {
            delete RoundNumber;
        }

      RoundNumber = new Text("Rounds: " + String(Rounds), renderer->windowWidth/2, 410, 1, 1, glm::vec2(0.5, 0));

    }

}
