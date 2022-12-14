#include "WinProcesses.hpp"
#include "WinClasses.hpp"
#include "SupportiveFunctions.hpp"

int APIENTRY _tWinMain (HINSTANCE This, HINSTANCE Prev,  LPTSTR cmd,   int mode){
    LPWSTR *argv;
    int argc;
    argv = CommandLineToArgvW(GetCommandLineW(), &argc);
    MainWindow hWnd;
    hWnd.init_window(WinName, WndProc);
    hWnd.create_win_class(This, hWnd.window_name, hWnd.window_proc, hWnd.window_class);
    std::string a;
    MainWindow *ptr_hWnd = &hWnd;
    hWnd.window_d = hWnd.create_window(WinName, _T("Application"), WS_OVERLAPPEDWINDOW  | WS_CLIPCHILDREN,  CW_USEDEFAULT,  CW_USEDEFAULT, 
                                        CW_USEDEFAULT, CW_USEDEFAULT, HWND_DESKTOP, This, ptr_hWnd);
    if (argc > 1){
        std::string inp = CW2A (argv[1]);
        inp = CW2A (argv[2]);
        inp = CW2A (argv[3]);
        hWnd.cmd_input_file = CW2A (argv[1]);
        hWnd.cmd_output_file = CW2A (argv[3]);
        hWnd.cmd_iter_num = CW2A (argv[2]);
    }
    MENUITEMINFO mii_system;
    add_menu_to_main(hWnd, mii_system);
    hWnd.show_windows(SW_MAXIMIZE, hWnd.window_d);
    hWnd.update_window(hWnd.window_d);
    
    MSG msg;
    while(GetMessage(&msg, NULL, 0, 0)) { 
        TranslateMessage(&msg);// Функция трансляции кодов нажатой клавиши 
        DispatchMessage(&msg); // Посылает сообщение функции 
    } 
    return 0; 
}
