#ifndef REPLAYSCENE_H
#define REPLAYSCENE_H
#include "autochess.h"

class ReplayScene : public Autochess
{
public:
    unsigned int index = 0;
    Sprite* leftArrow;
    Sprite* rightArrow;
    ReplayScene();
    void NextMove();
    void LastMove();
    void Init();
    void Update();
    void UpdateAfterPhysics();
    int MovesLeft;
};

#endif // REPLAYSCENE_H
