#include <cassert>
#include <Application.hpp>
#include "Editor.hpp"

int main()
{
    Application app;
    if (!app.Init())
    {
        app.Destroy();
        return 1;
    }

    UI::Editor editor(app.GetEngine(), app.GetRHI(), app.GetWindow(), app.GetInputManager());
    editor.Init();

    while(!app.WindowShouldClose())
    {
        app.Update();
        editor.Update();
        
        editor.Render();
        app.Render();
    }

    editor.Destroy();
    app.Destroy();

    return 0;
}
