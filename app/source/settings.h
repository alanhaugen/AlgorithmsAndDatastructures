#ifndef SETTINGS_H
#define SETTINGS_H

#include "popup.h"
#include "rangeinput.h"

class Settings : public PopUp
{
public:

    RangeInput* Audio;
    Sprite* FullscreenHighlight;
    Sprite* WindowedHighlight;
    Sprite* Windowed;
    Sprite* Fullscreen;

    void Update() override;


    Settings();
};

#endif // SETTINGS_H
