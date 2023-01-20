#include "SupportiveFunctions.hpp"
#include "WinClasses.hpp"
#include "WinProcesses.hpp"
#include "SwitchClasses.hpp"
#include "MyConstants.hpp"

#pragma once

using namespace game_of_life_constants;
namespace Supportive{

    void add_new_symbol(int& size, char wParam, char* text, Classes::GamePlayWindow* ptr_hWnd_3){
        switch ((TCHAR)wParam){
            case VK_BACK:
                if (size > NULL) size--;
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
        while (num > NULL){
            str_num += (char)(num % base_10) + convert_to_int;
            num /= base_10;
        }
        std::reverse(str_num.begin(), str_num.end());
        if (str_num.size() == NULL) str_num += "0";
        return str_num;
    }

    void print_help_info(RECT st, HDC hdc){
        std::string to_window = "DUMP - save the universe to a file. You can select an existing file, or create a new one";
        st.top = dump_text_top;
        st.bottom = dump_text_bottom;
        DrawText(hdc, (LPCSTR) to_window.c_str(), to_window.length(), &st, DT_NOCLIP | DT_CENTER);
        st.top = tick_text_top;
        st.bottom = tick_text_bottom;
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

    bool is_exists (const char* name) {
        if (FILE *file = fopen(name, "r")) {
            fclose(file);
            return true;
        } else {
            return false;
        }
    }

    void choose_file_to_open(Classes::GamePlayWindow** ptr_Field, char** buff, OPENFILENAME* file, TCHAR* name, Classes::GameField* child, SuppClasses::FileReader* file_reader){
        (*ptr_Field)->set_game_field_pointer(child);
        if ((*ptr_Field)->get_filename() != nullptr) (*file_reader).set_filename((*ptr_Field)->get_filename());
        if ((*ptr_Field)->get_cmd_input_file() != ""){
            if (!is_exists((*ptr_Field)->get_cmd_input_file().c_str())){
                MessageBox((*ptr_Field)->get_window_despriptor(), _T("WRONG INPUT FILE NAME!"), _T("ERROR"), MB_OK);
                return;
            }
            if (!is_exists((*ptr_Field)->get_cmd_output_file().c_str())){
                MessageBox((*ptr_Field)->get_window_despriptor(), _T("WRONG OUTPUT FILE NAME!"), _T("ERROR"), MB_OK);
                return;
            }
            int num = std::stoi((*ptr_Field)->get_cmd_iter_num());
            if (num < 0){
                MessageBox((*ptr_Field)->get_window_despriptor(), _T("WRONG ITERATIONS COUNT!"), _T("ERROR"), MB_OK);
                return;
            }
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
        (*file).nMaxFile = nMaxbuff;
        (*file).lpstrInitialDir = _T(".\\");
        (*file).lpstrDefExt = _T("txt");
        (*file).Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_READONLY;
    }

    bool is_exists (char* name) {
        if (FILE *file = fopen(name, "r")) {
            fclose(file);
            return true;
        } else {
            return false;
        }
    }

    void display_file_name(int& flag, int& size_out, char** text, Classes::GamePlayWindow** ptr_Field, WPARAM wParam, HWND* DumpButton, 
                            HWND* TickButton, HWND* ReturnButton,HWND* HelpButton){
        if (flag == flag_activated) add_new_symbol(size_out, wParam, *text, *ptr_Field);
        if ((TCHAR) wParam == VK_RETURN && flag == flag_activated){ 
            flag = NULL;                
            (*text)[size_out] = end_of_string;
            std::ofstream out;
            if (!is_exists(*text)){
                MessageBox((*ptr_Field)->get_window_despriptor(), _T("WRONG FILE NAME!"), _T("ERROR"), MB_OK);
                (*ptr_Field)->show_windows(SW_SHOW, *DumpButton, *TickButton, *ReturnButton, *HelpButton, (*ptr_Field)->get_game_field_pointer()->get_window_despriptor());
                size_out = NULL;
                delete [] (*text);
                return;
            }
            else { 
                out.open(*text);
                (*ptr_Field)->get_game_field_pointer()->dump_file(out);
                out.close();
                (*ptr_Field)->show_windows(SW_SHOW, *DumpButton, *TickButton, *ReturnButton, *HelpButton, (*ptr_Field)->get_game_field_pointer()->get_window_despriptor());
                size_out = NULL;
                delete [] (*text);
            }
        }
    }

    void check_cmd_input(Classes::GamePlayWindow** ptr_Field, SuppClasses::FileReader* file_reader){
        if ((*ptr_Field)->get_cmd_iter_num() != "" && file_reader->get_buff_size() != empty_buff){
            int iter = std::stoi((*ptr_Field)->get_cmd_iter_num());
            if (iter >= NULL) SendMessage((*ptr_Field)->get_window_despriptor(), WM_COMMAND, offline_mode, iter);
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

        int nXCount = nCanvasWidth / base_10;
        int nYCount = nCanvasHeight / base_10;
        for (int i = 1; i <= nYCount; i++){
            MoveToEx(hMemDC, NULL, i * base_10, NULL);
            LineTo(hMemDC, nCanvasWidth, i * base_10);
        }
        for (int i = 1; i <= nXCount; i++){
            MoveToEx(hMemDC, i * base_10, NULL, NULL);
            LineTo(hMemDC, i * base_10, nCanvasHeight);
        }
        BitBlt(*hdc, NULL, NULL, nCanvasWidth, nCanvasHeight, hMemDC, NULL, NULL, SRCCOPY);
        DeleteObject(hBitmap);
        DeleteDC(hMemDC);
    }

    void print_matrix(Classes::GameField** ptr_child, HDC* hdc){
        for (int i = 0; i < (*ptr_child)->get_size_x(); i++){
            for (int j = 0; j < (*ptr_child)->get_size_y(); j++){
                if ((*ptr_child)->get_matrix_elem(i, j) == alive){
                    for (int k = i * base_10; k < i * base_10 + base_10; k++){
                        for (int s = j * base_10; s < j * base_10 + base_10; s++) SetPixel(*hdc, k, s, BLACK_BRUSH);
                    }
                }
            }
        }
    }

    void create_alive_unit(Classes::GameField** ptr_child, LPARAM lParam){
        int l = LOWORD(lParam);
        int h = HIWORD(lParam);
        if (abs(l/base_10) < (*ptr_child)->get_size_x() && abs(h/base_10) < (*ptr_child)->get_size_y() && l != NULL && h != NULL){
            if ((*ptr_child)->get_matrix_elem(l/base_10, h/base_10) == dead) {
                (*ptr_child)->set_matrix_elem(l/base_10, h/base_10, alive);
                (*ptr_child)->redraw_window((*ptr_child)->get_window_despriptor(), TRUE);
            }
        }
    }

}