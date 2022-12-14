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

#pragma once

TCHAR ChildClassName[];
TCHAR WinName[];
TCHAR RName[];
TCHAR PName[];
TCHAR BName[];
TCHAR GName[];
TCHAR ChName[];

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc_2(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc_3(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc_ch(HWND, UINT, WPARAM, LPARAM);