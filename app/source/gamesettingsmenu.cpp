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
        Presets.Append(new GameSettings(2000, 40));
        Presets.Append(new GameSettings(500, 7));
    }

    createBackground();
    isOpen = true;

    GameSettingsNumber = new Text("Game Settings " + String(index), renderer->windowWidth/2, 130, 1, 1, glm::vec2(0.5, 0));

    GoldNumber = new Text("Gold: " + String(Gold), renderer->windowWidth/2, 310, 1, 1, glm::vec2(0.5, 0));
    RoundNumber = new Text("Rounds: " + String(Rounds), renderer->windowWidth/2, 410, 1, 1, glm::vec2(0.5, 0));

    AddGold = new Sprite("data/arrow.png", renderer->windowWidth/2 + 300, 300, 0.7, 0.7, glm::vec2(0.5, 0));
    ReduceGold = new Sprite("data/arrow.png", renderer->windowWidth/2 - 300, 300, 0.7, 0.7, glm::vec2(0.5, 0));
    ReduceGold->FlipHorizontal();
    AddRounds = new Sprite("data/arrow.png", renderer->windowWidth/2 + 300, 410, 0.7, 0.7, glm::vec2(0.5, 0));
    ReduceRounds =  new Sprite("data/arrow.png", renderer->windowWidth/2 - 300, 410, 0.7, 0.7, glm::vec2(0.5, 0));
    ReduceRounds->FlipHorizontal();
    AddPresett = new Sprite("data/arrow.png", renderer->windowWidth/2 + 160, 180, 0.7, 0.7, glm::vec2(0.5, 0));
    ReducePresett =  new Sprite("data/arrow.png", renderer->windowWidth/2 - 160, 180, 0.7, 0.7, glm::vec2(0.5, 0));
    ReducePresett->FlipHorizontal();
}

void GameSettingsMenu::UpdateNumbers()
{
    delete GoldNumber;
    delete RoundNumber;
    delete GameSettingsNumber;

    LinkedList<GameSettings*>::Iterator iterator = Presets.Begin();

    for (int i = 0; iterator != NULL; ++iterator)
    {
        if (index == i)
        {
            Gold = (*iterator)->Gold;
            Rounds = (*iterator)->Rounds;

            break;
        }

        i++;
    }

    GoldNumber  = new Text("Gold: " + String(Gold), renderer->windowWidth/2, 310, 1, 1, glm::vec2(0.5, 0));
    RoundNumber = new Text("Rounds: " + String(Rounds), renderer->windowWidth/2, 410, 1, 1, glm::vec2(0.5, 0));
    GameSettingsNumber = new Text("Game Settings " + String(index), renderer->windowWidth/2, 130, 1, 1, glm::vec2(0.5, 0));
}

void GameSettingsMenu::AddPreset()
{
    Presets.Append(new GameSettings());
    numberOfSettings++;

    index = numberOfSettings;

    Log(String(Presets.count));

    UpdateNumbers();
}

void GameSettingsMenu::Update()
{
    PopUp::Update();

    if(AddGold->IsPressed() == true)
    {
        Gold += 10;

        LinkedList<GameSettings*>::Iterator iterator = Presets.Begin();

        for (int i = 0; iterator != NULL; ++iterator)
        {
            if (index == i)
            {
                (*iterator)->Gold = Gold;
                break;
            }

            i++;
        }

        if (GoldNumber != nullptr)
        {
            delete GoldNumber;
        }

        GoldNumber = new Text("Gold: " + String(Gold), renderer->windowWidth/2, 310, 1, 1, glm::vec2(0.5, 0));

    }
    if(ReduceGold->IsPressed())
    {
        Gold -= 10;

        LinkedList<GameSettings*>::Iterator iterator = Presets.Begin();

        for (int i = 0; iterator != NULL; ++iterator)
        {
            if (index == i)
            {
                (*iterator)->Gold = Gold;
                break;
            }

            i++;
        }

        if (GoldNumber != nullptr)
        {
            delete GoldNumber;
        }

        GoldNumber = new Text("Gold: " + String(Gold), renderer->windowWidth/2, 310, 1, 1, glm::vec2(0.5, 0));

    }

    if(AddRounds->IsPressed() == true)
    {
        Rounds += 1;

        LinkedList<GameSettings*>::Iterator iterator = Presets.Begin();

        for (int i = 0; iterator != NULL; ++iterator)
        {
            if (index == i)
            {
                (*iterator)->Rounds = Rounds;
                break;
            }

            i++;
        }

        if (RoundNumber != nullptr)
        {
            delete RoundNumber;
        }

        RoundNumber = new Text("Rounds: " + String(Rounds), renderer->windowWidth/2, 410, 1, 1, glm::vec2(0.5, 0));

    }

    if(ReduceRounds->IsPressed())
    {
        Rounds -= 1;

        LinkedList<GameSettings*>::Iterator iterator = Presets.Begin();

        for (int i = 0; iterator != NULL; ++iterator)
        {
            if (index == i)
            {
                (*iterator)->Rounds = Rounds;
                break;
            }

            i++;
        }

        if (RoundNumber != nullptr)
        {
            delete RoundNumber;
        }

        RoundNumber = new Text("Rounds: " + String(Rounds), renderer->windowWidth/2, 410, 1, 1, glm::vec2(0.5, 0));

    }

    if(AddPresett->IsPressed())
    {
        if (index == numberOfSettings)
        {
            AddPreset();
        }
        else
        {
            index++;
        }

        UpdateNumbers();
    }

    if (ReducePresett->IsPressed())
    {
        if (index > 0)
        {
            index--;
            UpdateNumbers();
        }
    }

    GameSettingsNumber->Update();
    GoldNumber->Update();
    AddGold->Update();
    ReduceGold->Update();
    RoundNumber->Update();
    AddRounds->Update();
    ReduceRounds->Update();
    AddPresett->Update();
    ReducePresett->Update();
}

void GameSettingsMenu::UpdateAfterPhysics()
{
}
