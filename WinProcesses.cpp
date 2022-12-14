
#include "WinProcesses.hpp"
#include "WinClasses.hpp"
#include "SupportiveFunctions.hpp"

#ifndef WINPROCESSESDEF
#define WINPROCESSESDEF

TCHAR ChildClassName[] = _T("WinChild");
TCHAR WinName[] = _T("MainFrame");
TCHAR RName[] = _T("RulesFrame");
TCHAR PName[] = _T("PlayFrame");
TCHAR BName[] = _T("button");
TCHAR GName[] = _T("GamePlayFrame");
TCHAR ChName[] = _T("ChildFrame");

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
   
   static HWND PlayButton, ExitButton;
   static HINSTANCE hInst;
   static MainWindow SuppMenu;
   static MainWindow* ptr_MainMenu;

    switch (message) { 
        case WM_CREATE: {
            SuppMenu.init_window(PName, WndProc_2);
            SuppMenu.create_win_class(hInst, SuppMenu.window_name, SuppMenu.window_proc, SuppMenu.window_class);
            
            get_window_description(&ptr_MainMenu, lParam, hInst, hWnd);
            ptr_MainMenu->CreateButton(hInst, lParam, PlayButton, hWnd, BName, _T("PLAY"), PLAY_BUTTON);
            ptr_MainMenu->CreateButton(hInst, lParam, ExitButton, hWnd, BName, _T("EXIT"), RULES_BUTTON);
            break; }
        case WM_DESTROY: {
            PostQuitMessage(0); 
            break; }
        case WM_SIZE: {
            ptr_MainMenu->size_x = LOWORD(lParam); 
            ptr_MainMenu->size_y = HIWORD(lParam); 
            ptr_MainMenu->move_window(PlayButton, (ptr_MainMenu->size_x/2 - 250), (ptr_MainMenu->size_y/2 - 15 - 40), 500, 30, TRUE);
            ptr_MainMenu->move_window(ExitButton, (ptr_MainMenu->size_x/2 - 250), (ptr_MainMenu->size_y/2 - 15 + 40), 500, 30, TRUE);
            break; }
        case WM_COMMAND: {
            MainWindow* ptr_SuppMenu = &SuppMenu;
            int l = LOWORD(wParam);
            int h = HIWORD(wParam);
            int tub_pressed = wParam;
            if (tub_pressed == TUB_PRESSED) l = MENU_EXIT;
            switch_lparam_MainMenu(l, &ptr_MainMenu, hWnd, &SuppMenu, &ptr_SuppMenu, hInst);
            break; }
        case WM_CHAR: if ((TCHAR) wParam == VK_ESCAPE) SendMessage(hWnd, WM_COMMAND, TUB_PRESSED, 0);
        default: break;
        } 
    return DefWindowProc(hWnd, message, wParam, lParam); 
}

LRESULT CALLBACK WndProc_2(HWND hWnd_2, UINT message, WPARAM wParam, LPARAM lParam){
    static HWND DownloadButton, ReadyButton, ReturnButton, OfflineButton; 
    static MainWindow* ptr_SuppMenu;
    static HINSTANCE hInst;
    static RECT st, st_t;
    static GamePlayWindow Field;
    switch(message){
        case WM_CREATE:
            {
            Field.init_window(GName, WndProc_3);
            Field.create_win_class(hInst, Field.window_name, Field.window_proc, Field.window_class);
            get_window_description(&ptr_SuppMenu, lParam, hInst, hWnd_2);
            ptr_SuppMenu->CreateAllButtons(hInst, lParam, &DownloadButton, &ReadyButton, &ReturnButton, &OfflineButton);
            break;
            }
        case WM_SIZE:
            {
            ptr_SuppMenu->size_x = LOWORD(lParam); //˜˜˜˜˜˜
            ptr_SuppMenu->size_y = HIWORD(lParam); //˜˜˜˜˜˜
            ptr_SuppMenu->SetButtonsPosition(&DownloadButton, &ReadyButton, &ReturnButton, &OfflineButton);
            break;
            }
        case WM_COMMAND:
            {
            GamePlayWindow* ptr_Field = &Field;
            char ready_universe[] = "C:\\Users\\davyd\\Desktop\\forAPI.txt";
            int l = LOWORD(wParam);
            int h = HIWORD(wParam);
            switch_lparam_SuppMenu(&ptr_Field, &Field, &ptr_SuppMenu, ready_universe, l, hInst, hWnd_2);
            break;
            }
        default: break;
    } 
    return DefWindowProc(hWnd_2, message, wParam, lParam);
}

LRESULT CALLBACK WndProc_3(HWND hWnd_3, UINT message, WPARAM wParam, LPARAM lParam){
    static int iteration = 0;
    static HINSTANCE hInst;
    static HWND DumpButton, TickButton, ReturnButton, HelpButton, ExistButton, NewButton, Return_To_Game_Button;
    static GameField child;
    static GamePlayWindow* ptr_Field;
    static OPENFILENAME file;
    static TCHAR name[256] = _T("");
    static char* buff = nullptr;
    static RECT st, st_t, st_t1;
    static std::string output;
    set_file_settings(&file, hInst, name);
    static char* text;
    static int flag = 0, size_out;

    switch(message){
        case WM_CREATE:
            {
            child.init_window(ChName, WndProc_ch);
            child.create_win_class(hInst, child.window_name, child.window_proc, child.window_class);
            get_window_description(&ptr_Field, lParam, hInst, hWnd_3);
            choose_file_to_open(&ptr_Field, &buff, &file, name, &child);
            GameField* ptr_child = &child;
            ptr_Field->CreateAllButtons(hInst, lParam, &DumpButton, &TickButton, &ReturnButton, &HelpButton, &ExistButton, &NewButton, &Return_To_Game_Button);
            if (ptr_Field->size != -1) child.window_d = child.create_window(ChName, _T("Child"), WS_CHILD | WS_BORDER, 0, 0, 1302, 722, hWnd_3, hInst, ptr_child);
            break;
            }
        case WM_SIZE:
            {
            ptr_Field->size_x = LOWORD(lParam); //˜˜˜˜˜˜
            ptr_Field->size_y = HIWORD(lParam); //˜˜˜˜˜˜ 
            ptr_Field->SetButtonsPosition(&DumpButton, &TickButton, &ReturnButton, &HelpButton, &ExistButton, &NewButton, &Return_To_Game_Button);
            ptr_Field->game_field = &child;

            int res = 0;
            if (ptr_Field->size != -1) res = ptr_Field->read_buffer(buff, ptr_Field->size);
            ptr_Field->check_buff_reading(res, &child);
            check_cmd_input(&ptr_Field);
            break;
            }
        case WM_PAINT:
            {
            ptr_Field->print_all_info(flag, &Return_To_Game_Button, wParam, &st, &st_t, text, &st_t1, size_out, iteration);
            break;
            }
        case WM_COMMAND:
            {
            int offline = wParam;
            int l = LOWORD(wParam);
            int h = HIWORD(wParam);
            if (offline == OFFLINE_MODE){
                ptr_Field->calculate_offline_mode(iteration, lParam);
                break;
            }
            switch_lparam_Field(l, &ptr_Field, iteration, &text, flag, &DumpButton, &TickButton, &ReturnButton, 
                                &HelpButton, &ExistButton, &NewButton, &Return_To_Game_Button, &file, name);
            break;
            }
        case WM_CHAR:
            {
            display_file_name(flag, size_out, &text, &ptr_Field, wParam, &DumpButton, &TickButton, &ReturnButton, &HelpButton);
            break;
            }
        case WM_DESTROY:
            {
            ptr_Field->file_name = nullptr;
            break;
            }
        default: break;
    }
   return DefWindowProc(hWnd_3, message, wParam, lParam);
}

LRESULT CALLBACK WndProc_ch(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
    static GameField* ptr_child;
    static int type, left, top, size;
    static HINSTANCE hInst;
    static HDC hdc;
    PAINTSTRUCT ps;
    static int* cells_info;
    int index = 0;

    switch(message){
        case WM_SIZE:
            left = LOWORD(lParam); 
            top = HIWORD(lParam);
            break;
        case CHANGE_MATRIX_FOR_ITER: {
            ptr_child = (GameField*) wParam;
            for (int i = 0; i < lParam; i++) ptr_child->change_condition();
            break; }
        case REDRAW:
            size = lParam;
            ptr_child = (GameField*) wParam;
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        case CHANGE_MATRIX:
            ptr_child = (GameField*) wParam;
            ptr_child->change_condition();
            break;
        case WM_PAINT: {
            hdc = BeginPaint(hWnd, &ps);
            print_lattice(&hdc, &ps);
            print_matrix(&ptr_child, &hdc);
            EndPaint(hWnd, &ps); }
        case WM_LBUTTONDOWN: create_alive_unit(&ptr_child, lParam);
        default:
            return DefWindowProc(hWnd, message, wParam, lParam); break;
    }
    return 0;
}

#endif