#include <core/application.h>
#include "mainmenu.h"
#include "autochess.h"
#include "replayscene.h"
#include "replaynew.h"

bool isTwoPlayer;
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
