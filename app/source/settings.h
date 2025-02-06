#ifndef SETTINGS_H
#define SETTINGS_H

#include "popup.h"
#include "rangeinput.h"
#include "checkbox.h"

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

    CheckBox* experimentalCheckbox;


    void Update() override;
    void UpdateAfterPhysics();

    Settings();
    Settings(bool isMenu_);
};

#endif // SETTINGS_H
