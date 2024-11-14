#include <core/application.h>
#include "mainmenu.h"
#include "autochess.h"
#include "replayscene.h"
#include "replaynew.h"

bool isTwoPlayer = false;
bool vsAI = false;
bool isFirstPlaythrough = true;
LinkedList<Move> replay;
LinkedList<ReplayNew> replays;

int main(int argc, char **argv)
{
    Application application(argc, argv);
    application.AddScene(new Mainmenu());
    application.AddScene(new Autochess());
    application.AddScene(new ReplayScene());

    return application.Exec();
}
