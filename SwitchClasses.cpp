#include "SupportiveFunctions.hpp"
#include "WinClasses.hpp"
#include "WinProcesses.hpp"
#include "SwitchClasses.hpp"

#pragma once

namespace smart_switch{

    const int menu_white = 1003;
    const int menu_green = 1002;
    const int menu_exit = 1000;
    const int rules_button = 100;
    const int play_button = 101;
    const int choose_random = 1006;
    const int choose_file = 1007;
    const int choose_exit = 1008;
    const int choose_offline = 1009;
    const int change_matrix = WM_USER + 101;
    const int choose_dump = 1010;
    const int choose_tick = 1011;
    const int choose__exit = 1012;
    const int choose_help = 1013;
    const int exist_file = 1015;
    const int new_file = 1016;
    const int return_to_game = 1020;


    const TCHAR PName[] = _T("PlayFrame");
    const TCHAR GName[] = _T("GamePlayFrame");
    const TCHAR WinName[] = _T("MainFrame");

    /*
    Main Menu
    */

    Factory_MainMenu get_possible_options_for_main_menu(){
        Factory_MainMenu factory;
        factory.add <MenuToWhite>(menu_white);
        factory.add <MenuToGreen>(menu_green);
        factory.add <ExitFromMenu>(menu_exit);
        factory.add <RulesButtonClicked>(rules_button);
        factory.add <PlayButtonClicked>(play_button);
        return factory;
    }

    void MenuToGreen::execute_action(Classes::MainWindow** ptr_window, HWND hWnd, Classes::MainWindow* next_window, Classes::MainWindow** ptr_next_window, HINSTANCE hInst){
        HBRUSH greenBrush = CreateSolidBrush(RGB(40,80,0));
        (*ptr_window)->redraw_window((*ptr_window)->get_window_despriptor(), TRUE);
        SetClassLong(hWnd, GCLP_HBRBACKGROUND,(LONG)greenBrush);
    }

    void MenuToWhite::execute_action(Classes::MainWindow** ptr_window, HWND hWnd, Classes::MainWindow* next_window, Classes::MainWindow** ptr_next_window, HINSTANCE hInst){
        HBRUSH whiteBrush = CreateSolidBrush(RGB(255,255,255));
        (*ptr_window)->redraw_window((*ptr_window)->get_window_despriptor(), TRUE);
        SetClassLong(hWnd,GCLP_HBRBACKGROUND,(LONG)whiteBrush);
    }

    void ExitFromMenu::execute_action(Classes::MainWindow** ptr_window, HWND hWnd, Classes::MainWindow* next_window, Classes::MainWindow** ptr_next_window, HINSTANCE hInst){
        if (MessageBox(hWnd, _T("Really exit?"), _T("Think twice"), MB_OKCANCEL) == IDOK){
            (*ptr_window)->destroy_window((*ptr_window)->get_window_despriptor());
        }
    }

    void RulesButtonClicked::execute_action(Classes::MainWindow** ptr_window, HWND hWnd, Classes::MainWindow* next_window, Classes::MainWindow** ptr_next_window, HINSTANCE hInst){
        (*ptr_window)->destroy_window((*ptr_window)->get_window_despriptor());
    }

    void PlayButtonClicked::execute_action(Classes::MainWindow** ptr_window, HWND hWnd, Classes::MainWindow* next_window, Classes::MainWindow** ptr_next_window, HINSTANCE hInst){
        (*next_window).set_cmd_input_file((*ptr_window)->get_cmd_input_file());
        (*next_window).set_cmd_output_file((*ptr_window)->get_cmd_output_file());
        (*next_window).set_cmd_iter_num((*ptr_window)->get_cmd_iter_num());
        HWND descrp = (*next_window).create_window(PName, _T("Play"), WS_OVERLAPPEDWINDOW, 0, 0, 500, 500, hWnd, hInst, *ptr_next_window);
        (*next_window).set_window_descriptor(descrp);
        (*next_window).show_windows(SW_MAXIMIZE, (*next_window).get_window_despriptor());
        (*ptr_window)->show_windows(SW_HIDE, (*ptr_window)->get_window_despriptor());
    } 

    /*
    Supp Menu
    */

    void ChooseFileClicked::execute_action(Classes::GamePlayWindow** ptr_Field, Classes::GamePlayWindow* Field, Classes::MainWindow** ptr_SuppMenu, char* ready_universe, LPARAM message, HINSTANCE hInst, HWND hWnd_2){
        (*Field).set_window_descriptor((*Field).create_window(GName, _T("Game"), WS_OVERLAPPEDWINDOW, 0, 0, 500, 500, hWnd_2, hInst, *ptr_Field));
        (*Field).show_windows(SW_MAXIMIZE, (*Field).get_window_despriptor());
        (*ptr_SuppMenu)->show_windows(SW_HIDE, (*ptr_SuppMenu)->get_window_despriptor());
    }

    void ChooseRandomClicked::execute_action(Classes::GamePlayWindow** ptr_Field, Classes::GamePlayWindow* Field, Classes::MainWindow** ptr_SuppMenu, char* ready_universe, LPARAM message, HINSTANCE hInst, HWND hWnd_2){
        (*ptr_Field)->set_file_name(ready_universe);
        (*Field).set_window_descriptor((*Field).create_window(GName, _T("Game"), WS_OVERLAPPEDWINDOW, 0, 0, 500, 500, hWnd_2, hInst, *ptr_Field));
        (*Field).show_windows(SW_MAXIMIZE, (*Field).get_window_despriptor());
        (*ptr_SuppMenu)->show_windows(SW_HIDE, (*ptr_SuppMenu)->get_window_despriptor());
    }

    void ChooseOfflineClicked::execute_action(Classes::GamePlayWindow** ptr_Field, Classes::GamePlayWindow* Field, Classes::MainWindow** ptr_SuppMenu, char* ready_universe, LPARAM message, HINSTANCE hInst, HWND hWnd_2){
        if ((*ptr_SuppMenu)->get_cmd_input_file().length() == 0){
                MessageBox((*ptr_Field)->get_window_despriptor(), _T("NO INPUT FILE!"), _T("ERROR"), MB_OK);
        }
        else{
            (*Field).set_cmd_input_file((*ptr_SuppMenu)->get_cmd_input_file());
            (*Field).set_cmd_output_file((*ptr_SuppMenu)->get_cmd_output_file());
            (*Field).set_cmd_iter_num((*ptr_SuppMenu)->get_cmd_iter_num());
            (*Field).set_window_descriptor((*Field).create_window(GName, _T("Game"), WS_OVERLAPPEDWINDOW, 0, 0, 500, 500, hWnd_2, hInst, *ptr_Field));
            (*Field).show_windows(SW_MAXIMIZE, (*Field).get_window_despriptor());
            (*ptr_SuppMenu)->show_windows(SW_HIDE, (*ptr_SuppMenu)->get_window_despriptor());
        }
    }

    void ChooseExitClicked::execute_action(Classes::GamePlayWindow** ptr_Field, Classes::GamePlayWindow* Field, Classes::MainWindow** ptr_SuppMenu, char* ready_universe, LPARAM message, HINSTANCE hInst, HWND hWnd_2){
        HWND hc;
        hc = FindWindow(WinName,  _T("Application"));
        ShowWindow(hc, SW_SHOW);
        (*ptr_SuppMenu)->destroy_window((*ptr_SuppMenu)->get_window_despriptor());
    }

    Factory_SuppMenu get_possible_options_for_supp_menu(){
        Factory_SuppMenu factory;
        factory.add <ChooseRandomClicked>(choose_random);
        factory.add <ChooseFileClicked>(choose_file);
        factory.add <ChooseExitClicked>(choose_exit);
        factory.add <ChooseOfflineClicked>(choose_offline);
        return factory;
    }

    /*
    Field
    */
    void ChooseExit::execute_action(LPARAM lParam, Classes::GamePlayWindow** ptr_Field, int& iteration, char** text, int& flag, 
                            HWND* DumpButton, HWND* TickButton, HWND* ReturnButton,HWND* HelpButton, HWND* ExistButton, 
                            HWND* NewButton, HWND* Return_To_Game_Button, OPENFILENAME* file, TCHAR* name, SuppClasses::FileReader* file_reader){
        HWND hc = FindWindow(PName,  _T("PLAY"));
        ShowWindow(hc, SW_SHOW);
        (*ptr_Field)->get_game_field_pointer()->clear();
        iteration = 0;
        (*ptr_Field)->get_game_field_pointer()->destroy_window((*ptr_Field)->get_game_field_pointer()->get_window_despriptor());
        (*ptr_Field)->destroy_window((*ptr_Field)->get_window_despriptor());
    }

    void ChooseTickClicked::execute_action(LPARAM lParam, Classes::GamePlayWindow** ptr_Field, int& iteration, char** text, int& flag, 
                            HWND* DumpButton, HWND* TickButton, HWND* ReturnButton,HWND* HelpButton, HWND* ExistButton, 
                            HWND* NewButton, HWND* Return_To_Game_Button, OPENFILENAME* file, TCHAR* name, SuppClasses::FileReader* file_reader){
        iteration++;
        SendMessage((*ptr_Field)->get_game_field_pointer()->get_window_despriptor(), change_matrix, (WPARAM) (*ptr_Field)->get_game_field_pointer(), NULL);
        InvalidateRect((*ptr_Field)->get_window_despriptor(), NULL, TRUE);
    }

    void ChooseDumpClicked::execute_action(LPARAM lParam, Classes::GamePlayWindow** ptr_Field, int& iteration, char** text, int& flag, 
                            HWND* DumpButton, HWND* TickButton, HWND* ReturnButton,HWND* HelpButton, HWND* ExistButton, 
                            HWND* NewButton, HWND* Return_To_Game_Button, OPENFILENAME* file, TCHAR* name, SuppClasses::FileReader* file_reader){
        (*ptr_Field)->show_windows(SW_HIDE, *DumpButton, *TickButton, *ReturnButton, *HelpButton,  (*ptr_Field)->get_game_field_pointer()->get_window_despriptor());
        (*ptr_Field)->show_windows(SW_SHOW, *ExistButton, *NewButton);
    }

    void ChooseHelpClicked::execute_action(LPARAM lParam, Classes::GamePlayWindow** ptr_Field, int& iteration, char** text, int& flag, 
                            HWND* DumpButton, HWND* TickButton, HWND* ReturnButton,HWND* HelpButton, HWND* ExistButton, 
                            HWND* NewButton, HWND* Return_To_Game_Button, OPENFILENAME* file, TCHAR* name, SuppClasses::FileReader* file_reader){
        if (IsWindowVisible((*ptr_Field)->get_game_field_pointer()->get_window_despriptor())){
            (*ptr_Field)->show_windows(SW_HIDE, *DumpButton, *TickButton, *ReturnButton, *HelpButton, (*ptr_Field)->get_game_field_pointer()->get_window_despriptor());
            (*ptr_Field)->show_windows(SW_SHOW, *Return_To_Game_Button);
            (*ptr_Field)->redraw_window((*ptr_Field)->get_window_despriptor(), TRUE);
        }
    }

    void ChooseReturnToGameClicked::execute_action(LPARAM lParam, Classes::GamePlayWindow** ptr_Field, int& iteration, char** text, int& flag, 
                            HWND* DumpButton, HWND* TickButton, HWND* ReturnButton,HWND* HelpButton, HWND* ExistButton, 
                            HWND* NewButton, HWND* Return_To_Game_Button, OPENFILENAME* file, TCHAR* name, SuppClasses::FileReader* file_reader){
        (*ptr_Field)->show_windows(SW_SHOW, *DumpButton, *TickButton, *ReturnButton, *HelpButton, (*ptr_Field)->get_game_field_pointer()->get_window_despriptor());
        (*ptr_Field)->show_windows(SW_HIDE, *Return_To_Game_Button);
        (*ptr_Field)->redraw_window((*ptr_Field)->get_window_despriptor(), TRUE);
    }

    void ChooseExistFileClicked::execute_action(LPARAM lParam, Classes::GamePlayWindow** ptr_Field, int& iteration, char** text, int& flag, 
                            HWND* DumpButton, HWND* TickButton, HWND* ReturnButton,HWND* HelpButton, HWND* ExistButton, 
                            HWND* NewButton, HWND* Return_To_Game_Button, OPENFILENAME* file, TCHAR* name, SuppClasses::FileReader* file_reader){
        GetOpenFileName(file);
        std::ofstream out;
        out.open(name);
        (*ptr_Field)->get_game_field_pointer()->dump_file(out);
        out.close();
        (*ptr_Field)->show_windows(SW_SHOW, *DumpButton, *TickButton, *ReturnButton, *HelpButton, (*ptr_Field)->get_game_field_pointer()->get_window_despriptor());
        (*ptr_Field)->show_windows(SW_HIDE, *ExistButton, *NewButton);
    }

    void ChooseNewFileClicked::execute_action(LPARAM lParam, Classes::GamePlayWindow** ptr_Field, int& iteration, char** text, int& flag, 
                            HWND* DumpButton, HWND* TickButton, HWND* ReturnButton,HWND* HelpButton, HWND* ExistButton, 
                            HWND* NewButton, HWND* Return_To_Game_Button, OPENFILENAME* file, TCHAR* name, SuppClasses::FileReader* file_reader){
        (*ptr_Field)->show_windows(SW_HIDE, *ExistButton, *NewButton);
        *text = new char[100];
        for (int i = 0; i < 100; i++) (*text)[i] = 0;
        flag = 1;
        SendMessage((*ptr_Field)->get_window_despriptor(), WM_CHAR, VK_BACK, 0);
    }

    Factory_Field get_possible_options_for_field(){
        Factory_Field factory;
        factory.add <ChooseExit>(choose__exit);
        factory.add <ChooseTickClicked>(choose_tick);
        factory.add <ChooseDumpClicked>(choose_dump);
        factory.add <ChooseHelpClicked>(choose_help);
        factory.add <ChooseReturnToGameClicked>(return_to_game);
        factory.add <ChooseExistFileClicked>(exist_file);
        factory.add <ChooseNewFileClicked>(new_file);
        return factory;
    }
    
}