#ifndef POPUP_H
#define POPUP_H

#include <core/application.h>

class PopUp : public IScene
{
public:
    Text* hoverText = nullptr;
    Sprite* openPopUp = nullptr;
    Sprite* closePopUp = nullptr;
    Sprite* BackGround;
    bool isOpen = false;
    bool canOpen = true;
    virtual void Update();
    void open();
    void close();
    void createBackground();
    void createClosePopUp();

    void Init();

    PopUp();
};

#endif // POPUP_H
