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

#ifdef WIN32
#include <windows.h>

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
            PSTR lpCmdLine, int nCmdShow)
#else
int main(int argc, char **argv)
#endif
{
    Application application(argc, argv);
    application.AddScene(new Mainmenu());
    application.AddScene(new Autochess());
    application.AddScene(new ReplayScene());

    return application.Exec();
}
