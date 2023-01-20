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

#include "SupportiveFunctions.hpp"
#include "WinClasses.hpp"
#include "WinProcesses.hpp"
#include <map>
#pragma once

namespace smart_switch{

    /*
    Main Menu Switch
    */

    class SwitchMainMenu{
        public:
            virtual void execute_action(Classes::MainWindow** ptr_window, HWND hWnd, Classes::MainWindow* next_window, Classes::MainWindow** ptr_next_window, HINSTANCE hInst) = 0;
    };

    class MenuToGreen : public SwitchMainMenu{
        public:
            void execute_action(Classes::MainWindow** ptr_window, HWND hWnd, Classes::MainWindow* next_window, Classes::MainWindow** ptr_next_window, HINSTANCE hInst) override;
    };

    class MenuToWhite : public SwitchMainMenu{
        public:
            void execute_action(Classes::MainWindow** ptr_window, HWND hWnd, Classes::MainWindow* next_window, Classes::MainWindow** ptr_next_window, HINSTANCE hInst) override;
    };

    class ExitFromMenu : public SwitchMainMenu{
        public:
            void execute_action(Classes::MainWindow** ptr_window, HWND hWnd, Classes::MainWindow* next_window, Classes::MainWindow** ptr_next_window, HINSTANCE hInst) override;
    };

    class RulesButtonClicked : public SwitchMainMenu{
        public:
            void execute_action(Classes::MainWindow** ptr_window, HWND hWnd, Classes::MainWindow* next_window, Classes::MainWindow** ptr_next_window, HINSTANCE hInst) override;
    };

    class PlayButtonClicked : public SwitchMainMenu{
        public:
           void execute_action(Classes::MainWindow** ptr_window, HWND hWnd, Classes::MainWindow* next_window, Classes::MainWindow** ptr_next_window, HINSTANCE hInst) override;
    };

    /*
    Supportive Menu Switch
    */
    class SwitchSuppMenu{
        public:
            virtual void execute_action(Classes::GamePlayWindow** ptr_Field, Classes::GamePlayWindow* Field, Classes::MainWindow** ptr_SuppMenu, char* ready_universe, LPARAM message, HINSTANCE hInst, HWND hWnd_2) = 0;
    };

    class ChooseFileClicked : public SwitchSuppMenu{
        public:
            virtual void execute_action(Classes::GamePlayWindow** ptr_Field, Classes::GamePlayWindow* Field, Classes::MainWindow** ptr_SuppMenu, char* ready_universe, LPARAM message, HINSTANCE hInst, HWND hWnd_2) override;
    };

    class ChooseRandomClicked : public SwitchSuppMenu{
        public:
            virtual void execute_action(Classes::GamePlayWindow** ptr_Field, Classes::GamePlayWindow* Field, Classes::MainWindow** ptr_SuppMenu, char* ready_universe, LPARAM message, HINSTANCE hInst, HWND hWnd_2) override;
    };

    class ChooseOfflineClicked : public SwitchSuppMenu{
        public:
            virtual void execute_action(Classes::GamePlayWindow** ptr_Field, Classes::GamePlayWindow* Field, Classes::MainWindow** ptr_SuppMenu, char* ready_universe, LPARAM message, HINSTANCE hInst, HWND hWnd_2) override;
    };

    class ChooseExitClicked : public SwitchSuppMenu{
        public:
            virtual void execute_action(Classes::GamePlayWindow** ptr_Field, Classes::GamePlayWindow* Field, Classes::MainWindow** ptr_SuppMenu, char* ready_universe, LPARAM message, HINSTANCE hInst, HWND hWnd_2) override;
    };

    /*
    Field Switch
    */

   class SwitchField{
        public:
            virtual void execute_action(LPARAM lParam, Classes::GamePlayWindow** ptr_Field, int& iteration, char** text, int& flag, 
                            HWND* DumpButton, HWND* TickButton, HWND* ReturnButton,HWND* HelpButton, HWND* ExistButton, 
                            HWND* NewButton, HWND* Return_To_Game_Button, HWND* StartButton, HWND* StopButton, OPENFILENAME* file, TCHAR* name, SuppClasses::FileReader* file_reader) = 0;
    };

    class ChooseExit : public SwitchField{
        public:
            virtual void execute_action(LPARAM lParam, Classes::GamePlayWindow** ptr_Field, int& iteration, char** text, int& flag, 
                            HWND* DumpButton, HWND* TickButton, HWND* ReturnButton,HWND* HelpButton, HWND* ExistButton, 
                            HWND* NewButton, HWND* Return_To_Game_Button, HWND* StartButton, HWND* StopButton, OPENFILENAME* file, TCHAR* name, SuppClasses::FileReader* file_reader) override;
    };

    class ChooseTickClicked : public SwitchField{
        public:
            virtual void execute_action(LPARAM lParam, Classes::GamePlayWindow** ptr_Field, int& iteration, char** text, int& flag, 
                            HWND* DumpButton, HWND* TickButton, HWND* ReturnButton,HWND* HelpButton, HWND* ExistButton, 
                            HWND* NewButton, HWND* Return_To_Game_Button, HWND* StartButton, HWND* StopButton, OPENFILENAME* file, TCHAR* name, SuppClasses::FileReader* file_reader) override;
    };

    class ChooseDumpClicked : public SwitchField{
        public:
            virtual void execute_action(LPARAM lParam, Classes::GamePlayWindow** ptr_Field, int& iteration, char** text, int& flag, 
                            HWND* DumpButton, HWND* TickButton, HWND* ReturnButton,HWND* HelpButton, HWND* ExistButton, 
                            HWND* NewButton, HWND* Return_To_Game_Button, HWND* StartButton, HWND* StopButton, OPENFILENAME* file, TCHAR* name, SuppClasses::FileReader* file_reader) override;
    };

    class ChooseHelpClicked : public SwitchField{
        public:
            virtual void execute_action(LPARAM lParam, Classes::GamePlayWindow** ptr_Field, int& iteration, char** text, int& flag, 
                            HWND* DumpButton, HWND* TickButton, HWND* ReturnButton,HWND* HelpButton, HWND* ExistButton, 
                            HWND* NewButton, HWND* Return_To_Game_Button, HWND* StartButton, HWND* StopButton, OPENFILENAME* file, TCHAR* name, SuppClasses::FileReader* file_reader) override;
    };

    class ChooseReturnToGameClicked : public SwitchField{
        public:
            virtual void execute_action(LPARAM lParam, Classes::GamePlayWindow** ptr_Field, int& iteration, char** text, int& flag, 
                            HWND* DumpButton, HWND* TickButton, HWND* ReturnButton,HWND* HelpButton, HWND* ExistButton, 
                            HWND* NewButton, HWND* Return_To_Game_Button, HWND* StartButton, HWND* StopButton, OPENFILENAME* file, TCHAR* name, SuppClasses::FileReader* file_reader) override;
    };

    class ChooseExistFileClicked : public SwitchField{
        public:
            virtual void execute_action(LPARAM lParam, Classes::GamePlayWindow** ptr_Field, int& iteration, char** text, int& flag, 
                            HWND* DumpButton, HWND* TickButton, HWND* ReturnButton,HWND* HelpButton, HWND* ExistButton, 
                            HWND* NewButton, HWND* Return_To_Game_Button, HWND* StartButton, HWND* StopButton, OPENFILENAME* file, TCHAR* name, SuppClasses::FileReader* file_reader) override;
    };

    class ChooseNewFileClicked : public SwitchField{
        public:
            virtual void execute_action(LPARAM lParam, Classes::GamePlayWindow** ptr_Field, int& iteration, char** text, int& flag, 
                            HWND* DumpButton, HWND* TickButton, HWND* ReturnButton,HWND* HelpButton, HWND* ExistButton, 
                            HWND* NewButton, HWND* Return_To_Game_Button, HWND* StartButton, HWND* StopButton, OPENFILENAME* file, TCHAR* name, SuppClasses::FileReader* file_reader) override;
    };

    class StartClicked : public SwitchField{
        public:
            virtual void execute_action(LPARAM lParam, Classes::GamePlayWindow** ptr_Field, int& iteration, char** text, int& flag, 
                            HWND* DumpButton, HWND* TickButton, HWND* ReturnButton,HWND* HelpButton, HWND* ExistButton, 
                            HWND* NewButton, HWND* Return_To_Game_Button, HWND* StartButton, HWND* StopButton, OPENFILENAME* file, TCHAR* name, SuppClasses::FileReader* file_reader) override;
    };

    class StopClicked : public SwitchField{
        public:
            virtual void execute_action(LPARAM lParam, Classes::GamePlayWindow** ptr_Field, int& iteration, char** text, int& flag, 
                            HWND* DumpButton, HWND* TickButton, HWND* ReturnButton,HWND* HelpButton, HWND* ExistButton, 
                            HWND* NewButton, HWND* Return_To_Game_Button, HWND* StartButton, HWND* StopButton, OPENFILENAME* file, TCHAR* name, SuppClasses::FileReader* file_reader) override;
    };

    /*
    Factory MainMenu
    */

    class AbstractCreator_MainMenu{
        public:
            AbstractCreator_MainMenu(){}
            virtual SwitchMainMenu* create_option() = 0;
    };

    template <class Option>
    class Creator_MainMenu : public AbstractCreator_MainMenu{
        public:
            Creator_MainMenu(){}
            SwitchMainMenu* create_option() override{
                return new Option();
            }
    };

    class Factory_MainMenu{
        private:
            typedef std::map<int, AbstractCreator_MainMenu*> FactoryMap;
            FactoryMap factory;
        public:
            Factory_MainMenu() {}

            template <class Option>
            void add (const int code){
                FactoryMap::iterator it = factory.find(code);
                if (it == factory.end()){
                    factory[code] = new Creator_MainMenu<Option>();
                }
            }

            SwitchMainMenu* create_option(const int code){
                FactoryMap::iterator it = factory.find(code);
                if (it != factory.end()){
                    return it->second->create_option();
                }
                return 0;
            }
    };

    Factory_MainMenu get_possible_options_for_main_menu();

    /*
    Factory SuppMenu
    */

    class AbstractCreator_SuppMenu{
        public:
            AbstractCreator_SuppMenu(){}
            virtual SwitchSuppMenu* create_option() = 0;
    };

    template <class Option>
    class Creator_SuppMenu : public AbstractCreator_SuppMenu{
        public:
            Creator_SuppMenu(){}
            SwitchSuppMenu* create_option() override{
                return new Option();
            }
    };

    class Factory_SuppMenu{
        private:
            typedef std::map<int, AbstractCreator_SuppMenu*> FactoryMap;
            FactoryMap factory;
        public:
            Factory_SuppMenu() {}

            template <class Option>
            void add (const int code){
                FactoryMap::iterator it = factory.find(code);
                if (it == factory.end()){
                    factory[code] = new Creator_SuppMenu<Option>();
                }
            }

            SwitchSuppMenu* create_option(const int code){
                FactoryMap::iterator it = factory.find(code);
                if (it != factory.end()){
                    return it->second->create_option();
                }
                return 0;
            }
    };

    Factory_SuppMenu get_possible_options_for_supp_menu();

    /*
    Factory Field
    */

    class AbstractCreator_Field{
        public:
            AbstractCreator_Field(){}
            virtual SwitchField* create_option() = 0;
    };

    template <class Option>
    class Creator_Field : public AbstractCreator_Field{
        public:
            Creator_Field(){}
            SwitchField* create_option() override{
                return new Option();
            }
    };

    class Factory_Field{
        private:
            typedef std::map<int, AbstractCreator_Field*> FactoryMap;
            FactoryMap factory;
        public:
            Factory_Field() {}

            template <class Option>
            void add (const int code){
                FactoryMap::iterator it = factory.find(code);
                if (it == factory.end()){
                    factory[code] = new Creator_Field<Option>();
                }
            }

            SwitchField* create_option(const int code){
                FactoryMap::iterator it = factory.find(code);
                if (it != factory.end()){
                    return it->second->create_option();
                }
                return 0;
            }
    };

    Factory_Field get_possible_options_for_field();


}