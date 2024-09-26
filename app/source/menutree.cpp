#include "menutree.h"

MenuTree::MenuTree(Menu* firstMenu)
{
    root = firstMenu;
    activeMenu = root;
}

void MenuTree::Update()
{
    activeMenu->Update();
}

void MenuTree::UpdateAfterPhysics()
{
};
