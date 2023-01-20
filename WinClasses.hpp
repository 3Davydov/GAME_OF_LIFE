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

#pragma once

namespace Classes{
    class AbstractWindow{
    private:
        HWND window_d;
        TCHAR* window_name = nullptr;
        WNDCLASS window_class;
        WNDPROC window_proc;
        std::string cmd_input_file;
        std::string cmd_output_file;
        std::string cmd_iter_num;
        int size_x = 0;
        int size_y = 0;
    public:
        void set_window_descriptor(HWND new_descriptor);
        void set_window_name(TCHAR* new_name);
        void set_window_class(WNDCLASS new_class);
        void set_window_proc(WNDPROC new_proc);
        void set_cmd_input_file(std::string cmd_input_file);
        void set_cmd_output_file(std::string cmd_output_file);
        void set_cmd_iter_num(std::string cmd_iter_num);
        void set_size_x(int new_size);
        void set_size_y(int new_size);

        const HWND get_window_despriptor();
        const std::string get_cmd_input_file();
        const std::string get_cmd_output_file();
        const std::string get_cmd_iter_num();
        const int get_size_x();
        const int get_size_y();

        void create_win_class(HINSTANCE hInstance);

        template <class Head> void show_windows(int command, Head head){
            ShowWindow(head, command);
        }
        template <class Head, class... Args> void show_windows(int command, Head head, Args... args){
            ShowWindow(head, command);
            show_windows(command, args...);
        }
        void init_window(TCHAR* name, WNDPROC win_proc); 
                                                                
        void create_win_class(HINSTANCE hInstance, const TCHAR Name[], WNDPROC Proc, WNDCLASS& wc);

        void CreateButton(HINSTANCE hInst, LPARAM lParam, HWND& hBtn, HWND hWnd, const TCHAR Name[], TCHAR visible_text[], int button_id);
        
        HWND create_window(const TCHAR* class_name, const TCHAR* win_name, DWORD style, int x, int y, int nWidth, int nHeight, HWND parent, HINSTANCE hInstanse, void* ptr);

        void update_window(HWND win_d){ 
            UpdateWindow(win_d); 
        }

        void move_window(HWND win_d, int x, int y, int nWidth, int nHeight, bool repaint){
            MoveWindow(win_d, x, y, nWidth, nHeight, repaint);
        }

        void redraw_window(HWND win_d, bool erase){ 
            InvalidateRect(win_d, NULL, erase); 
        }

        void destroy_window(HWND win_d){ 
            DestroyWindow(win_d); 
        }
    };

    class MainWindow : public AbstractWindow{
    public:
        MainWindow(){}
        void CreateAllButtons(HINSTANCE hInst, LPARAM lParam, HWND* DownloadButton,  HWND* ReadyButton, HWND* ReturnButton, HWND* OfflineButton);
        
        void SetButtonsPosition(HWND* DownloadButton, HWND* ReadyButton, HWND* ReturnButton, HWND* OfflineButton);

        void init_window(TCHAR* win_name, WNDPROC win_proc);

    };

    class GameField : public AbstractWindow{
    private:
        char** matrix;
        std::vector<char> birth_needed;
        std::vector<char> survival_needed;
        std::string univerce_name;

    public:
        GameField(){}

        ~GameField();

        void create_matrix();

        char birth_check(int x, int y, std::vector<char> birth_needed, std::vector<char> survival_needed, char** oldmatrix);

        char survive_check(int x, int y, std::vector<char> birth_needed, std::vector<char> survival_needed, char** oldmatrix);

        void change_condition();

        int read_matrix(int index, const char* buff, const int buff_size, const int size_x, const int size_y, std::vector<char> birth_needed, std::vector<char> survival_needed);

        int read_num(int* index, int& x, const char* buff, const int buff_size);

        void get_birth_needed(std::vector<char> new_vec); 
        void get_survive_needed(std::vector<char> new_vec);
        void get_univerce_name(std::string new_name);
        const char get_matrix_elem(int row, int col);
        void set_matrix_elem(int row, int col, int elem);

        std::string set_output();
        void clear();
        void dump_file(std::ofstream& out);


    };

    class GamePlayWindow : public AbstractWindow{
    private:
        int play_mode_activated = 0;
        GameField* game_field = nullptr;
        char* file_name = nullptr;
    public:
        GamePlayWindow(){}

        ~GamePlayWindow(){
            delete [] file_name;
        }
        
        void set_play_mode_status(int new_status){
            this->play_mode_activated = new_status;
        }

        const int get_play_mode_status(){
            return this->play_mode_activated;
        }

        void init_window(TCHAR* win_name, WNDPROC win_proc);
        
        void CreateAllButtons(HINSTANCE hInst, LPARAM lParam, HWND* DumpButton, HWND* TickButton, HWND* ReturnButton, HWND* HelpButton, HWND* ExistButton, HWND* NewButton, HWND* Return_To_Game_Button, HWND* StartButton, HWND* StopButton);

        void SetButtonsPosition(HWND* DumpButton, HWND* TickButton, HWND* ReturnButton, HWND* HelpButton, HWND* ExistButton, HWND* NewButton, HWND* Return_To_Game_Button, HWND* StartButton, HWND* StopButton);

        void check_buff_reading(int result, GameField* child);

        void print_all_info(int flag, HWND* Return_To_Game_Button, WPARAM wParam, RECT* st, RECT* st_t, char* text, RECT* st_t1, int size_out, int iteration);

        void calculate_offline_mode(int& iteration, LPARAM lParam);
        GameField* get_game_field_pointer();
        void set_game_field_pointer(GameField* new_pointer);
        void set_file_name(char* new_name);
        const char* get_filename();

    };
}