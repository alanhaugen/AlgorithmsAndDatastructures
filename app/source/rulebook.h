#ifndef RULEBOOK_H
#define RULEBOOK_H

#include <core/application.h>

class Rulebook : public Component
{

#include <core/containers/array.h>

public:
    Sprite* openPopUp;
    Sprite* closePopUp;
    Sprite* leftArrow;
    Sprite* rightArrow;
    Sprite* BackGround;
    Array<Sprite*> Pages;
    unsigned int index = 0;
    bool isOpen = false;
    bool isMenu = false;
    void Update();
    void open();
    Rulebook(bool isMenu_ = false);
};



#endif // RULEBOOK_H
