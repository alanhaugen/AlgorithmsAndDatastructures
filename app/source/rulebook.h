#ifndef RULEBOOK_H
#define RULEBOOK_H

#include "popup.h"

class Rulebook : public PopUp
{

public:
    Sprite* leftArrow;
    Sprite* rightArrow;
    Array<Sprite*> Pages;
    unsigned int index = 0;
    bool isMenu = false;
    void Update() override;
    void UpdateAfterPhysics();

    Rulebook(bool isMenu_ = false);
};



#endif // RULEBOOK_H
