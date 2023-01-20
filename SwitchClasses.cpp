#include "SupportiveFunctions.hpp"
#include "WinClasses.hpp"
#include "WinProcesses.hpp"
#include "SwitchClasses.hpp"
#include "MyConstants.hpp"

#pragma once

using namespace game_of_life_constants;
namespace smart_switch{

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
        HWND descrp = (*next_window).create_window(PName, _T("Play"), WS_OVERLAPPEDWINDOW, win_x_coordinate, win_y_coordinate, win_whidth, win_height, hWnd, hInst, *ptr_next_window);
        (*next_window).set_window_descriptor(descrp);
        (*next_window).show_windows(SW_MAXIMIZE, (*next_window).get_window_despriptor());
        (*ptr_window)->show_windows(SW_HIDE, (*ptr_window)->get_window_despriptor());
    } 

    /*
    Supp Menu
    */

    void ChooseFileClicked::execute_action(Classes::GamePlayWindow** ptr_Field, Classes::GamePlayWindow* Field, Classes::MainWindow** ptr_SuppMenu, char* ready_universe, LPARAM message, HINSTANCE hInst, HWND hWnd_2){
        (*Field).set_window_descriptor((*Field).create_window(GName, _T("Game"), WS_OVERLAPPEDWINDOW, win_x_coordinate, win_y_coordinate, win_whidth, win_height, hWnd_2, hInst, *ptr_Field));
        (*Field).show_windows(SW_MAXIMIZE, (*Field).get_window_despriptor());
        (*ptr_SuppMenu)->show_windows(SW_HIDE, (*ptr_SuppMenu)->get_window_despriptor());
    }

    void ChooseRandomClicked::execute_action(Classes::GamePlayWindow** ptr_Field, Classes::GamePlayWindow* Field, Classes::MainWindow** ptr_SuppMenu, char* ready_universe, LPARAM message, HINSTANCE hInst, HWND hWnd_2){
        (*ptr_Field)->set_file_name(ready_universe);
        (*Field).set_window_descriptor((*Field).create_window(GName, _T("Game"), WS_OVERLAPPEDWINDOW, win_x_coordinate, win_y_coordinate, win_whidth, win_height, hWnd_2, hInst, *ptr_Field));
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
            (*Field).set_window_descriptor((*Field).create_window(GName, _T("Game"), WS_OVERLAPPEDWINDOW, win_x_coordinate, win_y_coordinate, win_whidth, win_height, hWnd_2, hInst, *ptr_Field));
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
                            HWND* NewButton, HWND* Return_To_Game_Button, HWND* StartButton, HWND* StopButton, OPENFILENAME* file, TCHAR* name, SuppClasses::FileReader* file_reader){
        HWND hc = FindWindow(PName,  _T("PLAY"));
        ShowWindow(hc, SW_SHOW);
        (*ptr_Field)->get_game_field_pointer()->clear();
        iteration = NULL;
        (*ptr_Field)->get_game_field_pointer()->destroy_window((*ptr_Field)->get_game_field_pointer()->get_window_despriptor());
        (*ptr_Field)->destroy_window((*ptr_Field)->get_window_despriptor());
    }


    DWORD __stdcall thread_start(LPVOID params)
        {
        Classes::GamePlayWindow** ptr_Field = (Classes::GamePlayWindow**) params;
        while ((*ptr_Field)->get_play_mode_status() == 1){
        Sleep(250);
        SendMessage((*ptr_Field)->get_game_field_pointer()->get_window_despriptor(), change_matrix, (WPARAM) (*ptr_Field)->get_game_field_pointer(), NULL);
        InvalidateRect((*ptr_Field)->get_window_despriptor(), NULL, TRUE);}
        return 0;
        };

    void ChooseTickClicked::execute_action(LPARAM lParam, Classes::GamePlayWindow** ptr_Field, int& iteration, char** text, int& flag, 
                            HWND* DumpButton, HWND* TickButton, HWND* ReturnButton,HWND* HelpButton, HWND* ExistButton, 
                            HWND* NewButton, HWND* Return_To_Game_Button, HWND* StartButton, HWND* StopButton, OPENFILENAME* file, TCHAR* name, SuppClasses::FileReader* file_reader){
        iteration++;
        SendMessage((*ptr_Field)->get_game_field_pointer()->get_window_despriptor(), change_matrix, (WPARAM) (*ptr_Field)->get_game_field_pointer(), NULL);
        InvalidateRect((*ptr_Field)->get_window_despriptor(), NULL, TRUE);
    }

    void ChooseDumpClicked::execute_action(LPARAM lParam, Classes::GamePlayWindow** ptr_Field, int& iteration, char** text, int& flag, 
                            HWND* DumpButton, HWND* TickButton, HWND* ReturnButton,HWND* HelpButton, HWND* ExistButton, 
                            HWND* NewButton, HWND* Return_To_Game_Button, HWND* StartButton, HWND* StopButton, OPENFILENAME* file, TCHAR* name, SuppClasses::FileReader* file_reader){
        (*ptr_Field)->show_windows(SW_HIDE, *DumpButton, *TickButton, *ReturnButton, *HelpButton,  (*ptr_Field)->get_game_field_pointer()->get_window_despriptor());
        (*ptr_Field)->show_windows(SW_SHOW, *ExistButton, *NewButton);
    }

    void ChooseHelpClicked::execute_action(LPARAM lParam, Classes::GamePlayWindow** ptr_Field, int& iteration, char** text, int& flag, 
                            HWND* DumpButton, HWND* TickButton, HWND* ReturnButton,HWND* HelpButton, HWND* ExistButton, 
                            HWND* NewButton, HWND* Return_To_Game_Button, HWND* StartButton, HWND* StopButton, OPENFILENAME* file, TCHAR* name, SuppClasses::FileReader* file_reader){
        if (IsWindowVisible((*ptr_Field)->get_game_field_pointer()->get_window_despriptor())){
            (*ptr_Field)->show_windows(SW_HIDE, *DumpButton, *TickButton, *ReturnButton, *HelpButton, (*ptr_Field)->get_game_field_pointer()->get_window_despriptor());
            (*ptr_Field)->show_windows(SW_SHOW, *Return_To_Game_Button);
            (*ptr_Field)->redraw_window((*ptr_Field)->get_window_despriptor(), TRUE);
        }
    }

    void ChooseReturnToGameClicked::execute_action(LPARAM lParam, Classes::GamePlayWindow** ptr_Field, int& iteration, char** text, int& flag, 
                            HWND* DumpButton, HWND* TickButton, HWND* ReturnButton,HWND* HelpButton, HWND* ExistButton, 
                            HWND* NewButton, HWND* Return_To_Game_Button, HWND* StartButton, HWND* StopButton, OPENFILENAME* file, TCHAR* name, SuppClasses::FileReader* file_reader){
        (*ptr_Field)->show_windows(SW_SHOW, *DumpButton, *TickButton, *ReturnButton, *HelpButton, (*ptr_Field)->get_game_field_pointer()->get_window_despriptor());
        (*ptr_Field)->show_windows(SW_HIDE, *Return_To_Game_Button);
        (*ptr_Field)->redraw_window((*ptr_Field)->get_window_despriptor(), TRUE);
    }

    void ChooseExistFileClicked::execute_action(LPARAM lParam, Classes::GamePlayWindow** ptr_Field, int& iteration, char** text, int& flag, 
                            HWND* DumpButton, HWND* TickButton, HWND* ReturnButton,HWND* HelpButton, HWND* ExistButton, 
                            HWND* NewButton, HWND* Return_To_Game_Button, HWND* StartButton, HWND* StopButton, OPENFILENAME* file, TCHAR* name, SuppClasses::FileReader* file_reader){
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
                            HWND* NewButton, HWND* Return_To_Game_Button, HWND* StartButton, HWND* StopButton, OPENFILENAME* file, TCHAR* name, SuppClasses::FileReader* file_reader){
        (*ptr_Field)->show_windows(SW_HIDE, *ExistButton, *NewButton);
        *text = new char[text_size];
        for (int i = 0; i < text_size; i++) (*text)[i] = NULL;
        flag = flag_activated;
        SendMessage((*ptr_Field)->get_window_despriptor(), WM_CHAR, VK_BACK, NULL);
    }

    void StartClicked::execute_action(LPARAM lParam, Classes::GamePlayWindow** ptr_Field, int& iteration, char** text, int& flag, 
                            HWND* DumpButton, HWND* TickButton, HWND* ReturnButton,HWND* HelpButton, HWND* ExistButton, 
                            HWND* NewButton, HWND* Return_To_Game_Button, HWND* StartButton, HWND* StopButton, OPENFILENAME* file, TCHAR* name, SuppClasses::FileReader* file_reader){
        DWORD         dwThreadId;
        (*ptr_Field)->set_play_mode_status(1);
        (*ptr_Field)->show_windows(SW_HIDE, *StartButton);
        (*ptr_Field)->show_windows(SW_SHOW, *StopButton);
        HANDLE hr = CreateThread(NULL,0,thread_start,ptr_Field,0,&dwThreadId);
    }

    void StopClicked::execute_action(LPARAM lParam, Classes::GamePlayWindow** ptr_Field, int& iteration, char** text, int& flag, 
                            HWND* DumpButton, HWND* TickButton, HWND* ReturnButton,HWND* HelpButton, HWND* ExistButton, 
                            HWND* NewButton, HWND* Return_To_Game_Button, HWND* StartButton, HWND* StopButton, OPENFILENAME* file, TCHAR* name, SuppClasses::FileReader* file_reader){
        (*ptr_Field)->set_play_mode_status(0);
        (*ptr_Field)->show_windows(SW_SHOW, *StartButton);
        (*ptr_Field)->show_windows(SW_HIDE, *StopButton);
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
        factory.add <StartClicked>(choose_start);
        factory.add <StopClicked>(choose_stop);
        return factory;
    }
    
}