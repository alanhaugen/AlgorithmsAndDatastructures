#ifndef menutree_H
#define menutree_H

#include <core/components/component.h>
#include <core/components/sprite.h>
#include <core/containers/array.h>
#include "menu.h"

class MenuTree : public Component
{
private:
    Menu* root;
    Menu* activeMenu;

public:
    MenuTree(Menu* firstMenu);

    void Update();
    void UpdateAfterPhysics();
};

#endif
