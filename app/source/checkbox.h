#ifndef CHECKBOX_H
#define CHECKBOX_H

#include <core/components/component.h>
#include <core/components/sprite.h>
#include <core/components/text.h>

class CheckBox : public Component
{
public:
    CheckBox(String imageUnselected, String imageSelected, String text, bool* option, int x, int y);
    CheckBox(String text, bool* option, int x, int y);

    void UpdatePlacement(float x, float y);
    void Update();
    void UpdateAfterPhysics();

    bool* origOption;
    bool toggled;

    Sprite* selected   = nullptr;
    Sprite* unSelected = nullptr;

    Text* textSprite = nullptr;
};

#endif // CHECKBOX_H
