#include <cstdlib>
#include <iostream>

#include "Application.h"

int main(int argC, char* argV[])
{
#if _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //enables leak detection
    _CrtSetBreakAlloc(185); //Will automatically cause break point on allocationm with matching Id
#endif

    Application* app = new Application(800, 420, "Path");

    const int state = app->Run();

    delete app;

    return state;
}