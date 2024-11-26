#ifndef SETTINGS_H
#define SETTINGS_H

#include "popup.h"

class Settings : public PopUp
{
public:


    Sprite* FullscreenHighlight;
    Sprite* WindowedHighlight;
    Sprite* Windowed;
    Sprite* Fullscreen;

    void Update() override;


    Settings();
};

#endif // SETTINGS_H
