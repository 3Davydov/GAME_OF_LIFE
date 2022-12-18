#include "SupportiveFunctions.hpp"
#include "WinClasses.hpp"
#include "WinProcesses.hpp"

#pragma once

namespace Supportive{

    const TCHAR ChildClassName[] = _T("WinChild");
    const TCHAR WinName[] = _T("MainFrame");
    const TCHAR RName[] = _T("RulesFrame");
    const TCHAR PName[] = _T("PlayFrame");
    const TCHAR BName[] = _T("button");
    const TCHAR GName[] = _T("GamePlayFrame");
    const TCHAR ChName[] = _T("ChildFrame");
    const int min_allowed_symbol = 34;
    const int max_allowed_symbol = 125;
    const int convert_to_int = 48;
    const char carriage_rollback = '\r';
    const int alive = 1;
    const int dead = 0;
    const int menu_white = 1003;
    const int menu_green = 1002;
    const int menu_exit = 1000;
    const int choose_random = 1006;
    const int choose_file = 1007;
    const int choose_exit = 1008;
    const int choose_offline = 1009;
    const int rules_button = 100;
    const int play_button = 101;
    const int choose_dump = 1010;
    const int choose_tick = 1011;
    const int choose__exit = 1012;
    const int choose_help = 1013;
    const int exist_file = 1015;
    const int new_file = 1016;
    const int return_to_game = 1020;
    const int offline_mode = 3000;
    const int change_matrix = WM_USER + 101;
    const int wrong_format = 2;

    void add_new_symbol(int& size, char wParam, char* text, Classes::GamePlayWindow* ptr_hWnd_3){
        switch ((TCHAR)wParam){
            case VK_BACK:
                if (size > 0) size--;
                break;
            default:
                if ((int) wParam >= min_allowed_symbol && (int) wParam <= max_allowed_symbol && (TCHAR) wParam != VK_RETURN){
                    text[size] = (char) wParam;
                    size++;
                }
                break;
        }
        ptr_hWnd_3->redraw_window(ptr_hWnd_3->window_d, TRUE);
    }

    std::string to_str(int num){
        std::string str_num = "";
        while (num > 0){
            str_num += (char)(num % 10) + convert_to_int;
            num /= 10;
        }
        std::reverse(str_num.begin(), str_num.end());
        if (str_num.size() == 0) str_num += "0";
        return str_num;
    }

    std::string set_output(Classes::GamePlayWindow* ptr_hWnd_3){
        std::string output = "Univerce name: " + ptr_hWnd_3->game_field->univerce_name;
        output += "    Rules:  B";
        for (unsigned int i = 0; i < ptr_hWnd_3->game_field->birth_needed.size(); i++) output += (char) ptr_hWnd_3->game_field->birth_needed[i];
        output += "/S";
        for (unsigned int i = 0; i < ptr_hWnd_3->game_field->survival_needed.size(); i++) output += (char) ptr_hWnd_3->game_field->survival_needed[i];
        output += "    Current iteration: ";
        return output;
    }

    void dump_file(std::ofstream& out, Classes::GamePlayWindow* ptr_hWnd_3){
        out << "#N " << ptr_hWnd_3->game_field->univerce_name << carriage_rollback << "#S " << ptr_hWnd_3->game_field->size_x << " " << ptr_hWnd_3->game_field->size_y << carriage_rollback << "#R B";

        for (unsigned int i = 0; i < ptr_hWnd_3->game_field->birth_needed.size(); i++) out << ptr_hWnd_3->game_field->birth_needed[i];

        out << "/S";

        for (unsigned int i = 0; i < ptr_hWnd_3->game_field->survival_needed.size(); i++) out << ptr_hWnd_3->game_field->survival_needed[i];

        for (int i = 0; i < ptr_hWnd_3->game_field->size_x; i++){
            for (int j = 0; j < ptr_hWnd_3->game_field->size_y; j++){
                if (ptr_hWnd_3->game_field->matrix[i][j] == alive) 
                        out << carriage_rollback << -ptr_hWnd_3->game_field->size_x/2 + i <<  " " << ptr_hWnd_3->game_field->size_y/2 - j;
            }
        }
    }

    void print_help_info(RECT st, HDC hdc){
        std::string to_window = "DUMP - save the universe to a file. You can select an existing file, or create a new one";
        st.top = 100;
        st.bottom = 150;
        DrawText(hdc, (LPCSTR) to_window.c_str(), to_window.length(), &st, DT_NOCLIP | DT_CENTER);
        st.top = 160;
        st.bottom = 210;
        to_window = "TICK - calculate the state of the field in one iteration";
        DrawText(hdc, (LPCSTR) to_window.c_str(), to_window.length(), &st, DT_NOCLIP | DT_CENTER);
    }

    void add_menu_to_main(Classes::MainWindow& hWnd, MENUITEMINFO& mii_system){
        mii_system.cbSize = sizeof(MENUITEMINFO);
        mii_system.fMask = MIIM_STRING | MIIM_ID;
        mii_system.wID = menu_white;
        mii_system.dwTypeData = "White";

        HMENU hMainMenu = CreateMenu();
        HMENU hPopMenuFile = CreatePopupMenu();
        HMENU hPopMenuFile1 = CreatePopupMenu();
        HMENU hPopMenuFile2 = CreatePopupMenu();
        AppendMenu(hMainMenu, MF_STRING, menu_exit, _T("Exit"));
        AppendMenu(hMainMenu, MF_STRING | MF_POPUP, (UINT)hPopMenuFile, _T("Settings"));
        AppendMenu(hPopMenuFile, MF_STRING | MF_POPUP, (UINT)hPopMenuFile1, _T("Background style"));
        AppendMenu(hPopMenuFile1, MF_STRING, menu_green, _T("Green"));
        InsertMenuItem(hPopMenuFile1, (UINT)hPopMenuFile2, FALSE, &mii_system);
        SetMenu(hWnd.get_window_despriptor(), hMainMenu);
        SetMenu(hWnd.get_window_despriptor(), hPopMenuFile);
    }

    void get_window_description(Classes::MainWindow** ptr_window, LPARAM info, HINSTANCE hInst, HWND window){
        hInst = ((LPCREATESTRUCT)info)->hInstance;
        SetWindowLongPtr(window, GWLP_USERDATA, (LONG)((LPCREATESTRUCT)info)->lpCreateParams);
        *ptr_window = (Classes::MainWindow*)GetWindowLongPtr(window, GWLP_USERDATA);
        (*ptr_window)->set_window_descriptor(window);        
    }

    void get_window_description(Classes::GamePlayWindow** ptr_window, LPARAM info, HINSTANCE hInst, HWND window){
        hInst = ((LPCREATESTRUCT)info)->hInstance;
        SetWindowLongPtr(window, GWLP_USERDATA, (LONG)((LPCREATESTRUCT)info)->lpCreateParams);
        *ptr_window = (Classes::GamePlayWindow*)GetWindowLongPtr(window, GWLP_USERDATA);
        (*ptr_window)->window_d = window;
    }

    void switch_lparam_MainMenu(LPARAM message, Classes::MainWindow** ptr_window, HWND hWnd, Classes::MainWindow* next_window, Classes::MainWindow** ptr_next_window, HINSTANCE hInst){
        switch(message){
            case menu_green: {
                HBRUSH greenBrush = CreateSolidBrush(RGB(40,80,0));
                (*ptr_window)->redraw_window((*ptr_window)->get_window_despriptor(), TRUE);
                SetClassLong(hWnd,GCLP_HBRBACKGROUND,(LONG)greenBrush);
                break; }
            case menu_white: {
                HBRUSH whiteBrush = CreateSolidBrush(RGB(255,255,255));
                (*ptr_window)->redraw_window((*ptr_window)->get_window_despriptor(), TRUE);
                SetClassLong(hWnd,GCLP_HBRBACKGROUND,(LONG)whiteBrush);
                break; }
            case menu_exit: {
                if (MessageBox(hWnd, _T("Really exit?"), _T("Think twice"), MB_OKCANCEL) == IDOK){
                    (*ptr_window)->destroy_window((*ptr_window)->get_window_despriptor());
                }
                break; }
            case rules_button: {
                (*ptr_window)->destroy_window((*ptr_window)->get_window_despriptor());
                break; }
            case play_button: {
                (*next_window).set_cmd_input_file((*ptr_window)->get_cmd_input_file());
                (*next_window).set_cmd_output_file((*ptr_window)->get_cmd_output_file());
                (*next_window).set_cmd_iter_num((*ptr_window)->get_cmd_iter_num());
                HWND descrp = (*next_window).create_window(PName, _T("Play"), WS_OVERLAPPEDWINDOW, 0, 0, 500, 500, hWnd, hInst, *ptr_next_window);
                (*next_window).set_window_descriptor(descrp);
                (*next_window).show_windows(SW_MAXIMIZE, (*next_window).get_window_despriptor());
                (*ptr_window)->show_windows(SW_HIDE, (*ptr_window)->get_window_despriptor());
                break; }
        }    
    }

    void switch_lparam_SuppMenu(Classes::GamePlayWindow** ptr_Field, Classes::GamePlayWindow* Field, Classes::MainWindow** ptr_SuppMenu, 
                                char* ready_universe, LPARAM message, HINSTANCE hInst, HWND hWnd_2){
        switch(message){
            case choose_file: {
                (*Field).window_d = (*Field).create_window(GName, _T("Game"), WS_OVERLAPPEDWINDOW, 0, 0, 500, 500, hWnd_2, hInst, *ptr_Field);
                (*Field).show_windows(SW_MAXIMIZE, (*Field).window_d);
                (*ptr_SuppMenu)->show_windows(SW_HIDE, (*ptr_SuppMenu)->get_window_despriptor());
                break; }
            case choose_random: {
                (*ptr_Field)->file_name = ready_universe;
                (*Field).window_d = (*Field).create_window(GName, _T("Game"), WS_OVERLAPPEDWINDOW, 0, 0, 500, 500, hWnd_2, hInst, *ptr_Field);
                (*Field).show_windows(SW_MAXIMIZE, (*Field).window_d);
                (*ptr_SuppMenu)->show_windows(SW_HIDE, (*ptr_SuppMenu)->get_window_despriptor());
                break; }
            case choose_offline: {
                if ((*ptr_SuppMenu)->get_cmd_input_file().length() == 0){
                        MessageBox((*ptr_Field)->window_d, _T("NO INPUT FILE!"), _T("ERROR"), MB_OK);
                }
                else{
                    (*Field).cmd_input_file = (*ptr_SuppMenu)->get_cmd_input_file();
                    (*Field).cmd_output_file = (*ptr_SuppMenu)->get_cmd_output_file();
                    (*Field).cmd_iter_num = (*ptr_SuppMenu)->get_cmd_iter_num();
                    (*Field).window_d = (*Field).create_window(GName, _T("Game"), WS_OVERLAPPEDWINDOW, 0, 0, 500, 500, hWnd_2, hInst, *ptr_Field);
                    (*Field).show_windows(SW_MAXIMIZE, (*Field).window_d);
                    (*ptr_SuppMenu)->show_windows(SW_HIDE, (*ptr_SuppMenu)->get_window_despriptor());
                }
                break; }
            case choose_exit: {
                HWND hc;
                hc = FindWindow(WinName,  _T("Application"));
                ShowWindow(hc, SW_SHOW);
                (*ptr_SuppMenu)->destroy_window((*ptr_SuppMenu)->get_window_despriptor());
                break; }
        }
    }

    void choose_file_to_open(Classes::GamePlayWindow** ptr_Field, char** buff, OPENFILENAME* file, TCHAR* name, Classes::GameField* child, SuppClasses::FileReader* file_reader){
        (*ptr_Field)->game_field = child;
        if ((*ptr_Field)->file_name != nullptr) (*file_reader).set_filename((*ptr_Field)->file_name);
        if ((*ptr_Field)->cmd_input_file != ""){

            (*file_reader).set_filename((*ptr_Field)->cmd_input_file);
        } 
        if ((*file_reader).get_filename() == nullptr){
            GetOpenFileName(file);
            if (name == ""){
                return;
            }
            (*file_reader).set_filename(name);
            (*file_reader).read_buffer((*ptr_Field)->game_field);
            (*ptr_Field)->game_field->birth_needed = file_reader->get_birth();
            (*ptr_Field)->game_field->survival_needed = file_reader->get_survive();
            (*ptr_Field)->game_field->univerce_name = file_reader->get_univerce_name();
        }
        else{
            if ((*file_reader).read_buffer((*ptr_Field)->game_field) == wrong_format){
                MessageBox((*ptr_Field)->window_d, _T("WRONG INPUT FILE NAME!"), _T("ERROR"), MB_OK);
            }
            else{
                (*ptr_Field)->game_field->birth_needed = file_reader->get_birth();
                (*ptr_Field)->game_field->survival_needed = file_reader->get_survive();
                (*ptr_Field)->game_field->univerce_name = file_reader->get_univerce_name();
            }
        }
    }

    void set_file_settings(OPENFILENAME* file, HINSTANCE hInst, TCHAR* name){
        (*file).lStructSize = sizeof(OPENFILENAME);
        (*file).hInstance = hInst;
        (*file).lpstrFilter = _T("Text\0*.txt");
        (*file).lpstrFile = name;
        (*file).nMaxFile = 256;
        (*file).lpstrInitialDir = _T(".\\");
        (*file).lpstrDefExt = _T("txt");
        (*file).Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_READONLY;
    }

    void switch_lparam_Field(LPARAM lParam, Classes::GamePlayWindow** ptr_Field, int& iteration, char** text, int& flag, 
                            HWND* DumpButton, HWND* TickButton, HWND* ReturnButton,HWND* HelpButton, HWND* ExistButton, 
                            HWND* NewButton, HWND* Return_To_Game_Button, OPENFILENAME* file, TCHAR* name, SuppClasses::FileReader* file_reader){
        HWND hc;
        switch(lParam){
            case choose__exit: {
                hc = FindWindow(PName,  _T("PLAY"));
                ShowWindow(hc, SW_SHOW);
                (*ptr_Field)->game_field->survival_needed.clear();
                (*ptr_Field)->game_field->birth_needed.clear();
                (*ptr_Field)->game_field->univerce_name.clear();
                iteration = 0;
                (*ptr_Field)->game_field->destroy_window((*ptr_Field)->game_field->get_window_despriptor());
                (*ptr_Field)->destroy_window((*ptr_Field)->window_d);
                break; }
            case choose_tick: {
                iteration++;
                SendMessage((*ptr_Field)->game_field->get_window_despriptor(), change_matrix, (WPARAM) (*ptr_Field)->game_field, NULL);
                InvalidateRect((*ptr_Field)->window_d, NULL, TRUE);
                break; }
            case choose_dump: {
                (*ptr_Field)->show_windows(SW_HIDE, *DumpButton, *TickButton, *ReturnButton, *HelpButton,  (*ptr_Field)->game_field->get_window_despriptor());
                (*ptr_Field)->show_windows(SW_SHOW, *ExistButton, *NewButton);
                break; }
            case choose_help: {
                if (IsWindowVisible((*ptr_Field)->game_field->get_window_despriptor())){
                    (*ptr_Field)->show_windows(SW_HIDE, *DumpButton, *TickButton, *ReturnButton, *HelpButton, (*ptr_Field)->game_field->get_window_despriptor());
                    (*ptr_Field)->show_windows(SW_SHOW, *Return_To_Game_Button);
                    (*ptr_Field)->redraw_window((*ptr_Field)->window_d, TRUE);
                }
                break; }
            case return_to_game: {
                (*ptr_Field)->show_windows(SW_SHOW, *DumpButton, *TickButton, *ReturnButton, *HelpButton, (*ptr_Field)->game_field->get_window_despriptor());
                (*ptr_Field)->show_windows(SW_HIDE, *Return_To_Game_Button);
                (*ptr_Field)->redraw_window((*ptr_Field)->window_d, TRUE);
                break; }
            case exist_file: {
                GetOpenFileName(file);
                std::ofstream out;
                out.open(name);
                dump_file(out, (*ptr_Field));
                out.close();
                (*ptr_Field)->show_windows(SW_SHOW, *DumpButton, *TickButton, *ReturnButton, *HelpButton, (*ptr_Field)->game_field->get_window_despriptor());
                (*ptr_Field)->show_windows(SW_HIDE, *ExistButton, *NewButton);
                break; }
            case new_file: {
                (*ptr_Field)->show_windows(SW_HIDE, *ExistButton, *NewButton);
                *text = new char[100];
                for (int i = 0; i < 100; i++) (*text)[i] = 0;
                flag = 1;
                SendMessage((*ptr_Field)->window_d, WM_CHAR, VK_BACK, 0);
                break; }
        }
    }

    void display_file_name(int& flag, int& size_out, char** text, Classes::GamePlayWindow** ptr_Field, WPARAM wParam, HWND* DumpButton, 
                            HWND* TickButton, HWND* ReturnButton,HWND* HelpButton){
        if (flag == 1) add_new_symbol(size_out, wParam, *text, *ptr_Field);
        if ((TCHAR) wParam == VK_RETURN && flag == 1){ 
            flag = 0;                
            (*text)[size_out] = '\0';
            std::ofstream out;
            out.open(*text);
            dump_file(out, *ptr_Field);
            out.close();
            (*ptr_Field)->show_windows(SW_SHOW, *DumpButton, *TickButton, *ReturnButton, *HelpButton, (*ptr_Field)->game_field->get_window_despriptor());
            size_out = 0;
            delete [] (*text);
        }
    }

    void check_cmd_input(Classes::GamePlayWindow** ptr_Field, SuppClasses::FileReader* file_reader){
        if ((*ptr_Field)->cmd_iter_num != "" && file_reader->get_buff_size() != -1){
            int iter = std::stoi((*ptr_Field)->cmd_iter_num);
            if (iter >= 0) SendMessage((*ptr_Field)->window_d, WM_COMMAND, offline_mode, iter);
            else  MessageBox((*ptr_Field)->window_d, _T("INCORRECT NUMBER OF ITERATIONS!"), _T("ERROR"), MB_OK);
        }
    }

    void print_lattice(HDC* hdc, PAINTSTRUCT* ps){
        int nCanvasWidth = (*ps).rcPaint.right - (*ps).rcPaint.left;
        int nCanvasHeight = (*ps).rcPaint.bottom - (*ps).rcPaint.top;

        HDC hMemDC = CreateCompatibleDC(*hdc);
        HBITMAP hBitmap = CreateCompatibleBitmap(*hdc, nCanvasWidth, nCanvasHeight);
        SelectObject(hMemDC, hBitmap);

        HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
        FillRect(hMemDC, &(*ps).rcPaint, hBrush);
        DeleteObject(hBrush);

        int nXCount = nCanvasWidth / 10;
        int nYCount = nCanvasHeight / 10;
        for (int i = 1; i <= nYCount; i++){
            MoveToEx(hMemDC, 0, i * 10, NULL);
            LineTo(hMemDC, nCanvasWidth, i * 10);
        }
        for (int i = 1; i <= nXCount; i++){
            MoveToEx(hMemDC, i * 10, 0, NULL);
            LineTo(hMemDC, i * 10, nCanvasHeight);
        }
        BitBlt(*hdc, 0, 0, nCanvasWidth, nCanvasHeight, hMemDC, 0, 0, SRCCOPY);
        DeleteObject(hBitmap);
        DeleteDC(hMemDC);
    }

    void print_matrix(Classes::GameField** ptr_child, HDC* hdc){
        for (int i = 0; i < (*ptr_child)->size_x; i++){
            for (int j = 0; j < (*ptr_child)->size_y; j++){
                if ((*ptr_child)->matrix[i][j] == alive){
                    for (int k = i * 10; k < i * 10 + 10; k++){
                        for (int s = j * 10; s < j * 10 + 10; s++) SetPixel(*hdc, k, s, BLACK_BRUSH);
                    }
                }
            }
        }
    }

    void create_alive_unit(Classes::GameField** ptr_child, LPARAM lParam){
        int l = LOWORD(lParam);
        int h = HIWORD(lParam);
        if (abs(l/10) < (*ptr_child)->size_x && abs(h/10) < (*ptr_child)->size_y && l != 0 && h != 0){
            if ((*ptr_child)->matrix[(l/10)][(h/10)] == dead) {
                (*ptr_child)->matrix[(l/10)][(h/10)] = alive;
                (*ptr_child)->redraw_window((*ptr_child)->get_window_despriptor(), TRUE);
            }
        }
    }

}