#include <core/application.h>
#include "mainmenu.h"
#include "autochess.h"

int main(int argc, char **argv)
{
    Application application(argc, argv);
    application.AddScene(new mainmenu());
    application.AddScene(new autochess());

    return application.Exec();
}
