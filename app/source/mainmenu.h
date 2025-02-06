#ifndef MAINMENU_H
#define MAINMENU_H

#include <core/x-platform/scene.h>
#include <core/components/sprite.h>
#include <core/components/camera.h>
#include <core/containers/stack.h>
#include <core/components/text.h>
#include "menu.h"
#include "cursor.h"
#include "rulebook.h"
#include "gamesettingsmenu.h"
#include "settings.h"

class Mainmenu : public IScene
{
public:

    GameSettingsMenu* gameSettings;
    Settings* settings;
    Menu* gameSettingsMenu;
    LinkedList<Text*> Timestamps;
    Rulebook* rules;
    Stack<Menu*> menus;
    Menu* settingsMenu;
    Menu* ruleMenu;
    Menu* replaysMenu;
    Sprite* title;
    Sprite* bg;
    Sprite* rulebook;
    Sprite* replayBG;
    Sprite* testPopUp;
    Cursor* cursor;
    Camera* cam;
    Text* cords;
    Mainmenu();

    void Init();
    void Update();
    void UpdateAfterPhysics();
};

#endif
