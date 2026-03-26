#include "Application.h"

int main()
{
    Application app("Pathfinder", 640, 480);

    if (app.init() == false)
    {
        return 1;
    }
    
    app.run();

    app.cleanup();

    return 0;
}
