#ifndef GAMESETTINGSMENU_H
#define GAMESETTINGSMENU_H

#include "popup.h"
#include "gamesettings.h"

class GameSettingsMenu : public PopUp
{
public:
    GameSettingsMenu();

    Sprite* CreateNewSettings;
    GameSettings* CurrentSettings;
    int index = 0;
    Text* GameSettingsNumber = nullptr;
    void Update() override;
};

#endif // GAMESETTINGSMENU_H
