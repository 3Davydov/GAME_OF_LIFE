
#include "WinProcesses.hpp"
#include "WinClasses.hpp"
#include "SupportiveFunctions.hpp"
#include "SuppClasses.hpp"

using namespace Classes;

#pragma once

namespace Processes{

    const TCHAR ChildClassName[] = _T("WinChild");
    const TCHAR WinName[] = _T("MainFrame");
    const TCHAR RName[] = _T("RulesFrame");
    const TCHAR PName[] = _T("PlayFrame");
    const TCHAR BName[] = _T("button");
    const TCHAR GName[] = _T("GamePlayFrame");
    const TCHAR ChName[] = _T("ChildFrame");
    const int play_button = 101;
    const int rules_button = 100;
    const int TubPressed = 1004;
    const int menu_exit = 1000;
    const int change_matrix = WM_USER + 101;
    const int change_matrix_for_iter = WM_USER + 102;
    const int redraw = WM_USER + 100;
    const int offline_mode = 3000;
    const int play_button_heigh = 150;
    const int play_button_whidth = 200;
    const int button_heigh = 30;
    const int button_whidth = 500;
    const int succes = 1018;
    const int empty_buff = -1;
    


    LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
    
    static HWND PlayButton, ExitButton;
    static HINSTANCE hInst;
    static MainWindow SuppMenu;
    static MainWindow* ptr_MainMenu;

        switch (message) { 
            case WM_CREATE: {
                SuppMenu.set_window_name(_T("PlayFrame"));
                SuppMenu.set_window_proc(Processes::WndProc_2);
                SuppMenu.create_win_class(hInst);
                
                Supportive::get_window_description(&ptr_MainMenu, lParam, hInst, hWnd);
                
                ptr_MainMenu->CreateButton(hInst, lParam, PlayButton, hWnd, BName, _T("PLAY"), play_button);
                ptr_MainMenu->CreateButton(hInst, lParam, ExitButton, hWnd, BName, _T("EXIT"), rules_button);
                break; }
            case WM_DESTROY: {
                PostQuitMessage(0); 
                break; }
            case WM_SIZE: {
                ptr_MainMenu->set_size_x(LOWORD(lParam));
                ptr_MainMenu->set_size_y(HIWORD(lParam));
                ptr_MainMenu->move_window(PlayButton, (ptr_MainMenu->get_size_x()/2 - button_whidth/2), (ptr_MainMenu->get_size_y()/2 - 55), button_whidth, button_heigh, TRUE);
                ptr_MainMenu->move_window(ExitButton, (ptr_MainMenu->get_size_x()/2 - button_whidth/2), (ptr_MainMenu->get_size_y()/2 + 25), button_whidth, button_heigh, TRUE);
                break; }
            case WM_COMMAND: {
                MainWindow* ptr_SuppMenu = &SuppMenu;
                int l = LOWORD(wParam);
                int h = HIWORD(wParam);
                int tub_pressed = wParam;
                if (tub_pressed == TubPressed) l = menu_exit;
                Supportive::switch_lparam_MainMenu(l, &ptr_MainMenu, hWnd, &SuppMenu, &ptr_SuppMenu, hInst);
                break; }
            case WM_CHAR: if ((TCHAR) wParam == VK_ESCAPE) SendMessage(hWnd, WM_COMMAND, TubPressed, NULL);
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
                Field.init_window(_T("GamePlayFrame"), WndProc_3);
                Field.create_win_class(hInst, Field.window_name, Field.window_proc, Field.window_class);
                Supportive::get_window_description(&ptr_SuppMenu, lParam, hInst, hWnd_2);
                
                ptr_SuppMenu->CreateAllButtons(hInst, lParam, &DownloadButton, &ReadyButton, &ReturnButton, &OfflineButton);
                break;
                }
            case WM_SIZE:
                {
                ptr_SuppMenu->set_size_x(LOWORD(lParam));
                ptr_SuppMenu->set_size_y(HIWORD(lParam));
                ptr_SuppMenu->SetButtonsPosition(&DownloadButton, &ReadyButton, &ReturnButton, &OfflineButton);
                break;
                }
            case WM_COMMAND:
                {
                GamePlayWindow* ptr_Field = &Field;
                char ready_universe[] = "C:\\Users\\davyd\\Desktop\\forAPI.txt";
                int l = LOWORD(wParam);
                int h = HIWORD(wParam);
                Supportive::switch_lparam_SuppMenu(&ptr_Field, &Field, &ptr_SuppMenu, ready_universe, l, hInst, hWnd_2);
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
        Supportive::set_file_settings(&file, hInst, name);
        static char* text;
        static int flag = 0, size_out;
        static SuppClasses::FileReader* file_reader = new SuppClasses::FileReader;

        switch(message){
            case WM_CREATE:
                {
                child.set_window_name(_T("ChildFrame"));
                child.set_window_proc(Processes::WndProc_ch);
                child.create_win_class(hInst);
                Supportive::get_window_description(&ptr_Field, lParam, hInst, hWnd_3);
                Supportive::choose_file_to_open(&ptr_Field, &buff, &file, name, &child, file_reader);

                GameField* ptr_child = &child;
                ptr_Field->CreateAllButtons(hInst, lParam, &DumpButton, &TickButton, &ReturnButton, &HelpButton, &ExistButton, &NewButton, &Return_To_Game_Button);
                HWND descr;
                if (file_reader->get_buff_size() != empty_buff){
                    descr = child.create_window(_T("ChildFrame"), _T("Child"), WS_CHILD | WS_BORDER, NULL, NULL, 1300, 720, hWnd_3, hInst, ptr_child);
                    child.set_window_descriptor(descr);
                }
                else{
                    HWND hc;
                    hc = FindWindow(PName,  _T("PLAY"));
                    ShowWindow(hc, SW_SHOW);
                    (ptr_Field)->destroy_window((ptr_Field)->window_d);
                }
                break;
                }
            case WM_SIZE:
                {
                ptr_Field->size_x = LOWORD(lParam); 
                ptr_Field->size_y = HIWORD(lParam); 
                ptr_Field->SetButtonsPosition(&DumpButton, &TickButton, &ReturnButton, &HelpButton, &ExistButton, &NewButton, &Return_To_Game_Button);
                ptr_Field->game_field = &child;

                int res = 0;
                res = child.read_matrix(file_reader->get_current_index(), file_reader->get_buffer(), file_reader->get_buff_size(), file_reader->get_size_x(), file_reader->get_size_y(), file_reader->get_birth(), file_reader->get_survive());
                ptr_Field->check_buff_reading(res, &child);
                Supportive::check_cmd_input(&ptr_Field, file_reader);
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
                if (offline == offline_mode){
                    ptr_Field->calculate_offline_mode(iteration, lParam);
                    break;
                }
                Supportive::switch_lparam_Field(l, &ptr_Field, iteration, &text, flag, &DumpButton, &TickButton, &ReturnButton, 
                                    &HelpButton, &ExistButton, &NewButton, &Return_To_Game_Button, &file, name, file_reader);
                break;
                }
            case WM_CHAR:
                {
                Supportive::display_file_name(flag, size_out, &text, &ptr_Field, wParam, &DumpButton, &TickButton, &ReturnButton, &HelpButton);
                break;
                }
            case WM_DESTROY:
                {
                
                file_reader->delete_data(ptr_Field->cmd_input_file);
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

        switch(message){
            case WM_DESTROY:
                break;
            case WM_SIZE:
                left = LOWORD(lParam); 
                top = HIWORD(lParam);
                break;
            case change_matrix_for_iter: {
                ptr_child = (GameField*) wParam;
                for (int i = 0; i < lParam; i++) ptr_child->change_condition();
                break; }
            case redraw:
                size = lParam;
                ptr_child = (GameField*) wParam;
                InvalidateRect(hWnd, NULL, TRUE);
                break;
            case change_matrix:
                ptr_child = (GameField*) wParam;
                ptr_child->change_condition();
                break;
            case WM_PAINT: {
                hdc = BeginPaint(hWnd, &ps);
                Supportive::print_lattice(&hdc, &ps);
                Supportive::print_matrix(&ptr_child, &hdc);
                EndPaint(hWnd, &ps); break;}
            case WM_LBUTTONDOWN: Supportive::create_alive_unit(&ptr_child, lParam);
            default:
                return DefWindowProc(hWnd, message, wParam, lParam); break;
        }
        return 0;
    }

}
