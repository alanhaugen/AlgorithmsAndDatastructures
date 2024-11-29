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

    Text* musicAudioText;
    RangeInput* musicAudio;


    void Update() override;


    Settings();
    Settings(bool isMenu_);
};

#endif // SETTINGS_H
