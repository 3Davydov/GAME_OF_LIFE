#include "WinProcesses.hpp"
#include "WinClasses.hpp"
#include "SupportiveFunctions.hpp"

int APIENTRY _tWinMain (HINSTANCE This, HINSTANCE Prev,  LPTSTR cmd,   int mode){

    const TCHAR WinName[] = _T("MainFrame"); 
    const int input_file = 1;
    const int iter_num = 2;
    const int output_file = 3;
    const int no_args = 1;
    
    LPWSTR *argv;
    int argc;
    argv = CommandLineToArgvW(GetCommandLineW(), &argc);
    Classes::MainWindow hWnd;
    hWnd.init_window(_T("MainFrame"), Processes::WndProc);
    hWnd.create_win_class(This);
    
    std::string a;
    Classes::MainWindow *ptr_hWnd = &hWnd;
   
    if (argc != no_args){
        std::string cmd_input_file = CW2A (argv[input_file]);
        std::string cmd_output_file = CW2A (argv[output_file]);
        std::string cmd_iter_num = CW2A (argv[iter_num]);
        hWnd.set_cmd_input_file(cmd_input_file);
        hWnd.set_cmd_output_file(cmd_output_file);
        hWnd.set_cmd_iter_num(cmd_iter_num);
    }
    HWND descriptor = hWnd.create_window(_T("MainFrame"), _T("Application"), WS_OVERLAPPEDWINDOW  | WS_CLIPCHILDREN,  CW_USEDEFAULT,  CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, HWND_DESKTOP, This, ptr_hWnd);
    hWnd.set_window_descriptor(descriptor);
    MENUITEMINFO mii_system;
    Supportive::add_menu_to_main(hWnd, mii_system);
    hWnd.show_windows(SW_MAXIMIZE, hWnd.get_window_despriptor());
    hWnd.update_window(hWnd.get_window_despriptor());
    
    MSG msg;
    while(GetMessage(&msg, NULL, NULL, NULL)) { 
        TranslateMessage(&msg); 
        DispatchMessage(&msg); 
    } 
    return 0; 
}