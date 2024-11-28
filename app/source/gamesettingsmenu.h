#ifndef GAMESETTINGSMENU_H
#define GAMESETTINGSMENU_H

#include "popup.h"
#include "gamesettings.h"

class GameSettingsMenu : public PopUp
{
public:

    Sprite* CreateNewSettings;
    Sprite*  AddGold;
    GameSettings* CurrentSettings;
    int index = 0;
    Text* GameSettingsNumber = nullptr;
    void Update() override;

    GameSettingsMenu();
};

#endif // GAMESETTINGSMENU_H
