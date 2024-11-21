#ifndef RULEBOOK_H
#define RULEBOOK_H

#include "core/components/sprite.h"
#include LikedList.h

class Rulebook : public Component
{
public:

    LinkedList<Sprite*> Page;
    Page.Append(new sprite());


};



#endif // RULEBOOK_H
