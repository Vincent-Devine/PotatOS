#include <Application.hpp>

int main()
{
    Application app;
    if (!app.Init())
    {
        app.Destroy();
        return 1;
    }

    while (!app.WindowShouldClose())
    {
        app.Update(false);
        app.GetRHI().Render(app.GetEngine().GetCurrentScene());
        app.Render();
        app.DisplayGame();
    }

    app.Destroy();

    return 0;
}