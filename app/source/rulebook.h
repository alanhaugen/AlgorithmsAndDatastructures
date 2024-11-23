#ifndef RULEBOOK_H
#define RULEBOOK_H

#include "core/components/sprite.h"

class Rulebook : public Component
{

#include <core/containers/array.h>

public:
    Sprite* closePopUp = nullptr;
    Sprite* leftArrow;
    Sprite* rightArrow;
    Sprite* BackGround;
    Array<Sprite*> Pages;
    unsigned int index = 0;
    bool isOpen = false;
    bool isMenu = false;
    void Update();

    Rulebook(bool isMenu_ = false);
};



#endif // RULEBOOK_H
