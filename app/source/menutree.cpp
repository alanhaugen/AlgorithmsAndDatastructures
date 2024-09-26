#include "menutree.h"

MenuTree::MenuTree(Menu* firstMenu)
{
    root = firstMenu;
    activeMenu = root;
}

void MenuTree::Update()
{
    root->Update();
}

void MenuTree::UpdateAfterPhysics()
{
};
