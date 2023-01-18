#include "SupportiveFunctions.hpp"
#include "WinClasses.hpp"
#include "WinProcesses.hpp"
#include "SwitchClasses.hpp"

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
        ptr_hWnd_3->redraw_window(ptr_hWnd_3->get_window_despriptor(), TRUE);
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
        (*ptr_window)->set_window_descriptor(window);
    }

    void choose_file_to_open(Classes::GamePlayWindow** ptr_Field, char** buff, OPENFILENAME* file, TCHAR* name, Classes::GameField* child, SuppClasses::FileReader* file_reader){
        (*ptr_Field)->set_game_field_pointer(child);
        if ((*ptr_Field)->get_filename() != nullptr) (*file_reader).set_filename((*ptr_Field)->get_filename());
        if ((*ptr_Field)->get_cmd_input_file() != ""){

            (*file_reader).set_filename((*ptr_Field)->get_cmd_input_file());
        } 
        if ((*file_reader).get_filename() == nullptr){
            GetOpenFileName(file);
            if (name == ""){
                return;
            }
            (*file_reader).set_filename(name);
            (*file_reader).read_buffer((*ptr_Field)->get_game_field_pointer());
            (*ptr_Field)->get_game_field_pointer()->get_birth_needed(file_reader->get_birth());
            (*ptr_Field)->get_game_field_pointer()->get_survive_needed(file_reader->get_survive());
            (*ptr_Field)->get_game_field_pointer()->get_univerce_name(file_reader->get_univerce_name());
        }
        else{
            if ((*file_reader).read_buffer((*ptr_Field)->get_game_field_pointer()) == wrong_format){
                MessageBox((*ptr_Field)->get_window_despriptor(), _T("WRONG INPUT FILE NAME!"), _T("ERROR"), MB_OK); //////////////////
            }
            else{
                (*ptr_Field)->get_game_field_pointer()->get_birth_needed(file_reader->get_birth());
                (*ptr_Field)->get_game_field_pointer()->get_survive_needed(file_reader->get_survive());
                (*ptr_Field)->get_game_field_pointer()->get_univerce_name(file_reader->get_univerce_name());
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

    void display_file_name(int& flag, int& size_out, char** text, Classes::GamePlayWindow** ptr_Field, WPARAM wParam, HWND* DumpButton, 
                            HWND* TickButton, HWND* ReturnButton,HWND* HelpButton){
        if (flag == 1) add_new_symbol(size_out, wParam, *text, *ptr_Field);
        if ((TCHAR) wParam == VK_RETURN && flag == 1){ 
            flag = 0;                
            (*text)[size_out] = '\0';
            std::ofstream out;
            out.open(*text);
            (*ptr_Field)->get_game_field_pointer()->dump_file(out);
            out.close();
            (*ptr_Field)->show_windows(SW_SHOW, *DumpButton, *TickButton, *ReturnButton, *HelpButton, (*ptr_Field)->get_game_field_pointer()->get_window_despriptor());
            size_out = 0;
            delete [] (*text);
        }
    }

    void check_cmd_input(Classes::GamePlayWindow** ptr_Field, SuppClasses::FileReader* file_reader){
        if ((*ptr_Field)->get_cmd_iter_num() != "" && file_reader->get_buff_size() != -1){
            int iter = std::stoi((*ptr_Field)->get_cmd_iter_num());
            if (iter >= 0) SendMessage((*ptr_Field)->get_window_despriptor(), WM_COMMAND, offline_mode, iter);
            else  MessageBox((*ptr_Field)->get_window_despriptor(), _T("INCORRECT NUMBER OF ITERATIONS!"), _T("ERROR"), MB_OK);
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
        for (int i = 0; i < (*ptr_child)->get_size_x(); i++){
            for (int j = 0; j < (*ptr_child)->get_size_y(); j++){
                if ((*ptr_child)->get_matrix_elem(i, j) == alive){
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
        if (abs(l/10) < (*ptr_child)->get_size_x() && abs(h/10) < (*ptr_child)->get_size_y() && l != 0 && h != 0){
            if ((*ptr_child)->get_matrix_elem(l/10, h/10) == dead) {
                (*ptr_child)->set_matrix_elem(l/10, h/10, alive);
                (*ptr_child)->redraw_window((*ptr_child)->get_window_despriptor(), TRUE);
            }
        }
    }

}