#ifndef SETTINGS_H
#define SETTINGS_H

#include "popup.h"
#include "rangeinput.h"

class Settings : public PopUp
{
public:
    Text* fullscreenText;
    Sprite* fullscreenUnchecked;
    Sprite* fullscreenChecked;
    Text* audioText;
    RangeInput* Audio;


    void Update() override;


    Settings();
};

#endif // SETTINGS_H
