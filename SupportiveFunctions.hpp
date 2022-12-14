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

#ifndef DEFINES
#define DEFINES

#define ID_FILE_OPEN 40002
#define RULES_BUTTON 100
#define PLAY_BUTTON 101
#define MENU_EXIT 1000
#define MENU_SETTINGS 1005
#define MENU_GREEN 1002
#define MENU_WHITE 1003
#define RULES_WINDOW 103
#define TUB_PRESSED 1004
#define CHOOSE_RANDOM 1006
#define CHOOSE_FILE 1007
#define CHOOSE_EXIT 1008
#define CHOOSE_OFFLINE 1009
#define CHOOSE_DUMP 1010
#define CHOOSE_TICK 1011
#define CHOOSE__EXIT 1012
#define CHOOSE_HELP 1013
#define ALIVE 1
#define DEAD 0
#define WRONG_SIZE 1014
#define WRONG_CORDINATE 1017
#define SUCCES 1018
#define EXIST_FILE 1015
#define NEW_FILE 1016
#define RETURN_TO_GAME 1020
#define WRONG_FORMAT 1021
#define NOT_A_DIGIT 1022
#define CONVERT_TO_INT 48
#define MINUS '-'
#define BACKSLASH '/'
#define SPACE ' '
#define NAME_SYMBOL 'N'
#define SIZE_SYMBOL 'S'
#define RULES_SYMBOL 'R'
#define CARRIAGE_ROLLBACK '\r'
#define NEW_LINE '\n'
#define GRID '#'
#define REDRAW WM_USER + 100
#define CHANGE_MATRIX_FOR_ITER WM_USER + 102
#define CHANGE_MATRIX WM_USER + 101
#define MAX_WHIDTH 130
#define MAX_HEIGH 73
#define MIN_ALLOWED_SYMBOL 34
#define MAX_ALLOWED_SYMBOL 125
#define OFFLINE_MODE 3000

#endif

#include "WinClasses.hpp"
#pragma once

void add_new_symbol(int& size, char wParam, char* text, GamePlayWindow* ptr_hWnd_3);

std::string to_str(int num);

void fill_buffer(GamePlayWindow* ptr_hWnd_3, int size, char* buff);

int get_buffer_size(char* name);

std::string set_output(GamePlayWindow* ptr_hWnd_3);

void dump_file(std::ofstream& out, GamePlayWindow* ptr_hWnd_3);

void print_help_info(RECT st, HDC hdc);

void add_menu_to_main(MainWindow& hWnd, MENUITEMINFO& mii_system);

void get_window_description(MainWindow** ptr_window, LPARAM info, HINSTANCE hInst, HWND window);

void get_window_description(GamePlayWindow** ptr_window, LPARAM info, HINSTANCE hInst, HWND window);

void switch_lparam_MainMenu(LPARAM message, MainWindow** ptr_window, HWND hWnd, MainWindow* next_window, MainWindow** ptr_next_window, HINSTANCE hInst);

void switch_lparam_SuppMenu(GamePlayWindow** ptr_Field, GamePlayWindow* Field, MainWindow** ptr_SuppMenu, 
                            char* ready_univerce, LPARAM message, HINSTANCE hInst, HWND hWnd_2);

void choose_file_to_open(GamePlayWindow** ptr_Field, char** buff, OPENFILENAME* file, TCHAR* name, GameField* child);

void set_file_settings(OPENFILENAME* file, HINSTANCE hInst, TCHAR* name);

void switch_lparam_Field(LPARAM lParam, GamePlayWindow** ptr_Field, int& iteration, char** text, int& flag, 
                        HWND* DumpButton, HWND* TickButton, HWND* ReturnButton,HWND* HelpButton, HWND* ExistButton, 
                        HWND* NewButton, HWND* Return_To_Game_Button, OPENFILENAME* file, TCHAR* name);

void display_file_name(int& flag, int& size_out, char** text, GamePlayWindow** ptr_Field, WPARAM wParam, HWND* DumpButton, 
HWND* TickButton, HWND* ReturnButton, HWND* HelpButton);

void check_cmd_input(GamePlayWindow** ptr_Field);

void print_lattice(HDC* hdc, PAINTSTRUCT* ps);

void print_matrix(GameField** ptr_child, HDC* hdc);

void create_alive_unit(GameField** ptr_child, LPARAM lParam);