#ifndef GAMESETTINGSMENU_H
#define GAMESETTINGSMENU_H

#include "popup.h"
#include "gamesettings.h"

class GameSettingsMenu : public PopUp
{
public:
    GameSettingsMenu();

    Sprite*  AddGold;
    Sprite*  ReduceGold;
    Sprite* AddRounds;
    Sprite* ReduceRounds;
    GameSettings* CurrentSettings;
    Sprite* ReducePresett;
    Sprite* AddPresett;
    int index = 0;
    int numberOfSettings = 0;

    Text* GoldNumber = nullptr;
    Text* RoundNumber = nullptr;
    Text* GameSettingsNumber = nullptr;

    void UpdateNumbers();
    void AddPreset();
    void Update(float dt);
    void UpdateAfterPhysics();
};

#endif // GAMESETTINGSMENU_H
