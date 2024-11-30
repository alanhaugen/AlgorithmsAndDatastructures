#ifndef GAMESETTINGSMENU_H
#define GAMESETTINGSMENU_H

#include "popup.h"
#include "gamesettings.h"

class GameSettingsMenu : public PopUp
{
public:
    GameSettingsMenu();

    Sprite* CreateNewSettings;
    Sprite*  AddGold;
    Sprite*  ReduceGold;
    Sprite* AddRounds;
    Sprite* ReduceRounds;
    GameSettings* CurrentSettings;
    int index = 0;

    Text* GoldNumber = nullptr;
    Text* RoundNumber = nullptr;
    Text* GameSettingsNumber = nullptr;
    void Update() override;
};

#endif // GAMESETTINGSMENU_H
