#include <core/application.h>
#include "mainmenu.h"
#include "board.h"

int main(int argc, char **argv)
{
    Application application(argc, argv);
    application.AddScene(new mainmenu());
    application.AddScene(new board());

    return application.Exec();
}
