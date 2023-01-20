#ifndef LIBS
#define LIBS

#include <windows.h>
#include <string>
#include <tchar.h>
#include <iostream>
#include <vector>
#include <commdlg.h>
#include <fstream>
#include <cmath>
#include <shellapi.h>
#include <atlstr.h>

#endif

#include "WinClasses.hpp"
#include "SuppClasses.hpp"
#include "SuppClasses.hpp"

#pragma once

namespace Supportive{

    void add_new_symbol(int& size, char wParam, char* text, Classes::GamePlayWindow* ptr_hWnd_3);

    std::string to_str(int num);

    void print_help_info(RECT st, HDC hdc);

    void add_menu_to_main(Classes::MainWindow& hWnd, MENUITEMINFO& mii_system);

    void get_window_description(Classes::MainWindow** ptr_window, LPARAM info, HINSTANCE hInst, HWND window);

    void get_window_description(Classes::GamePlayWindow** ptr_window, LPARAM info, HINSTANCE hInst, HWND window);

    void choose_file_to_open(Classes::GamePlayWindow** ptr_Field, char** buff, OPENFILENAME* file, TCHAR* name, Classes::GameField* child, SuppClasses::FileReader* file_reader);

    void set_file_settings(OPENFILENAME* file, HINSTANCE hInst, TCHAR* name);

    void display_file_name(int& flag, int& size_out, char** text, Classes::GamePlayWindow** ptr_Field, WPARAM wParam, HWND* DumpButton, 
    HWND* TickButton, HWND* ReturnButton, HWND* HelpButton);

    void check_cmd_input(Classes::GamePlayWindow** ptr_Field, SuppClasses::FileReader* file_reader);

    void print_lattice(HDC* hdc, PAINTSTRUCT* ps);

    void print_matrix(Classes::GameField** ptr_child, HDC* hdc);

    void create_alive_unit(Classes::GameField** ptr_child, LPARAM lParam);

    bool is_exists (char* name);

    bool is_exists (const char* name);


}