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
#include <clocale>

#endif

#pragma once

namespace game_of_life_constants{
    
    const TCHAR WinName[] = _T("MainFrame"); 
    const int input_file = 1;
    const int iter_num = 2;
    const int output_file = 3;
    const int no_args = 1;
    const int succes = 1018;
    const char carriage_rollback = '\r';
    const char new_line = '\n';
    const int wrong_format = 2;
    const int redraw = WM_USER + 100;
    const int plus_sign = 1;
    const int minus_sign = -1;
    const int num_is_digit = 1;
    const int num_not_a_digit = 0;
    const char grid = '#';
    const int convert_to_int = 48;
    const char minus = '-';
    const char backslash = '/';
    const char space = ' ';
    const char name_symbol = 'N';
    const char size_symbol = 'S';
    const char rules_symbol = 'R';
    const int wrong_size = 3;
    const int wrong_coordinate = 4;
    const int not_a_digit = 5;
    const int max_whidth = 130;
    const int max_heigh = 73;
    const int empty_buff = -1;
    const int alive = 1;
    const int dead = 0;
    const int max_digit = 9;
    const int small_step = 1;
    const int step = 2;
    const int big_step = 3;
    const int empty_string = 0;
    const TCHAR ChildClassName[] = _T("WinChild");
    const TCHAR RName[] = _T("RulesFrame");
    const TCHAR PName[] = _T("PlayFrame");
    const TCHAR BName[] = _T("button");
    const TCHAR GName[] = _T("GamePlayFrame");
    const TCHAR ChName[] = _T("ChildFrame");
    const int min_allowed_symbol = 34;
    const int max_allowed_symbol = 125;
    const char end_of_string = '\0';
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
    const int choose_start = 2010;
    const int choose_stop = 2011;
    const int exist_file = 1015;
    const int new_file = 1016;
    const int return_to_game = 1020;
    const int offline_mode = 3000;
    const int change_matrix = WM_USER + 101;
    const int base_10 = 10;
    const int dump_text_top = 100;
    const int dump_text_bottom = 150;
    const int tick_text_top = 160;
    const int tick_text_bottom = 210;
    const int flag_activated = 1;
    const int nMaxbuff = 256;
    const int win_x_coordinate = 0;
    const int win_y_coordinate = 0;
    const int win_whidth = 500;
    const int win_height = 500;
    const int text_size = 100;
    const int change_matrix_for_iter = WM_USER + 102;
    const int play_button_heigh = 150;
    const int play_button_whidth = 200;
    const int button_heigh = 30;
    const int button_whidth = 500;
    const int empty_param = 0;
    const int out_file_size = 200;
    const int button_y_space = 220;
    const int indent = 10;
    const int offset_for_download_button = 165;
    const int offset_for_ready_button = 75;
    const int offset_for_offline_button = 35;
    const int offset_for_return_button = 135;
    const int advice_size = 30;
    const int paintstruct_top = 742;
    const int paintstruct_right = 1300;
    const int paintstruct_bottom = 772;
    const int TubPressed = 1004;
    const int offset_for_play_button = 55;
    const int offset_for_exit_button = 25;

}