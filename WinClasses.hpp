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

class AbstractWindow{
public:
    HWND window_d;

    TCHAR* window_name;

    WNDCLASS window_class;

    WNDPROC window_proc;

    std::string cmd_input_file;

    std::string cmd_output_file;

    std::string cmd_iter_num;

    int size_x;

    int size_y;

    template <class Head> void show_windows(int command, Head head){
        ShowWindow(head, command);
    }
    template <class Head, class... Args> void show_windows(int command, Head head, Args... args){
        ShowWindow(head, command);
        show_windows(command, args...);
    }
    virtual void init_window(TCHAR* name, WNDPROC win_proc) = 0; // ˜˜˜ ˜˜˜˜  + ˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜
                                                                // ˜˜˜˜˜˜˜˜˜ - ˜˜˜˜ private, ˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜ ˜˜˜ ˜˜˜˜˜˜˜ ˜˜˜˜˜˜
    virtual void create_win_class(HINSTANCE hInstance, TCHAR Name[], WNDPROC Proc, WNDCLASS& wc) = 0;
                                                                    // ˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜, ˜˜˜˜˜˜˜ ˜˜˜˜ ˜˜˜ ˜˜˜˜˜˜˜ ˜˜˜˜˜˜
    virtual  void CreateButton(HINSTANCE hInst, LPARAM lParam, HWND& hBtn, HWND hWnd, TCHAR Name[], TCHAR visible_text[], int button_id) = 0;
    
    virtual HWND create_window(TCHAR* class_name, TCHAR* win_name, DWORD style, int x, int y, int nWidth, int nHeight, 
                                HWND parent, HINSTANCE hInstanse, void* ptr){
        return CreateWindow(class_name, win_name, style, x, y, nWidth, nHeight, parent, NULL, hInstanse, ptr);
    }
    virtual void update_window(HWND win_d){ 
        UpdateWindow(win_d); 
    }
    virtual void move_window(HWND win_d, int x, int y, int nWidth, int nHeight, bool repaint){
        MoveWindow(win_d, x, y, nWidth, nHeight, repaint);
    }
    virtual void redraw_window(HWND win_d, bool erase){ 
        InvalidateRect(win_d, NULL, erase); 
    }
    virtual void destroy_window(HWND win_d){ 
        DestroyWindow(win_d); 
    }
};

class MainWindow : public AbstractWindow{
public:
    MainWindow(){}

    void init_window(TCHAR* win_name, WNDPROC win_proc);

    void create_win_class(HINSTANCE hInstance, TCHAR Name[], WNDPROC Proc, WNDCLASS& wc);

    void CreateButton(HINSTANCE hInst, LPARAM lParam, HWND& hBtn, HWND hWnd, TCHAR Name[], TCHAR visible_text[], int button_id);

    void CreateAllButtons(HINSTANCE hInst, LPARAM lParam, HWND* DownloadButton, 
                                        HWND* ReadyButton, HWND* ReturnButton, HWND* OfflineButton);
    
    void SetButtonsPosition(HWND* DownloadButton, HWND* ReadyButton, HWND* ReturnButton, HWND* OfflineButton);

};

class GameField : public MainWindow{
public:
    char** matrix;
    int size_x;
    int size_y;
    std::vector<char> birth_needed;
    std::vector<char> survival_needed;

    GameField(){}

    ~GameField();

    void create_matrix();

    char birth_check(int x, int y, std::vector<char> birth_needed, std::vector<char> survival_needed, char** oldmatrix);

    char survive_check(int x, int y, std::vector<char> birth_needed, std::vector<char> survival_needed, char** oldmatrix);

    void change_condition();

};

class GamePlayWindow : public AbstractWindow{
public:
    GamePlayWindow(){}

    ~GamePlayWindow(){
        delete [] file_name;
    }
    
    void init_window(TCHAR* win_name, WNDPROC win_proc);

    void create_win_class(HINSTANCE hInstance, TCHAR Name[], WNDPROC Proc, WNDCLASS& wc);

    void CreateButton(HINSTANCE hInst, LPARAM lParam, HWND& hBtn, HWND hWnd, TCHAR Name[], TCHAR visible_text[], int button_id);
    
    bool is_digit(char num);

    int read_num(const char* buff, int size, int* index, int& x);

    int read_buffer(const char* buff, int size);

    int read_name_and_size(int& index, const char* buff, int size);

    int read_birth_and_survival(int& index, const char* buff, int size);

    int read_matrix(int& index, const char* buff, int size);

    void CreateAllButtons(HINSTANCE hInst, LPARAM lParam, HWND* DumpButton, HWND* TickButton, HWND* ReturnButton,
    HWND* HelpButton, HWND* ExistButton, HWND* NewButton, HWND* Return_To_Game_Button);

    void SetButtonsPosition(HWND* DumpButton, HWND* TickButton, HWND* ReturnButton,
    HWND* HelpButton, HWND* ExistButton, HWND* NewButton, HWND* Return_To_Game_Button);

    void check_buff_reading(int result, GameField* child);

    void print_all_info(int flag, HWND* Return_To_Game_Button, WPARAM wParam, RECT* st, 
                        RECT* st_t, char* text, RECT* st_t1, int size_out, int iteration);

    void calculate_offline_mode(int& iteration, LPARAM lParam);

    int size;

    GameField* game_field = nullptr;

    char* file_name = nullptr;

    std::string univerce_name;

    std::vector<char> birth_needed;

    std::vector<char> survival_needed;
};