#include <Windows.h>
#include "../NelLib/window.h"

int APIENTRY WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ INT)
{
    createWindow("Coding Ocean", 1920 / 2, 1080 / 2);

    while (!quit()) {
        if (escKeyPressed()) {
            closeWindow();
        }

        Sleep(1);
    }

    return 0;
}
