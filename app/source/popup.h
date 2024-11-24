#ifndef POPUP_H
#define POPUP_H

#include <core/application.h>

class PopUp
{
public:

    Sprite* openPopUp;
    Sprite* closePopUp;
    Sprite* BackGround;
    bool isOpen = false;
    void Update();
    void open();
    void close();

    PopUp();
};

#endif // POPUP_H
