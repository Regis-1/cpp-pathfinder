#include "Application.h"

int main()
{
    Application app("Pathfinder", 1024, 768);

    if (app.init() == false)
    {
        return 1;
    }
    
    app.run();

    app.cleanup();

    return 0;
}
