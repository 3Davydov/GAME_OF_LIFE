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

#include "WinClasses.hpp"
#pragma once

namespace SuppClasses{
    class FileReader{
    private:
        int buff_size;
        char* file_name = nullptr;
        std::string univerce_name;
        std::vector<char> birth_needed;
        std::vector<char> survival_needed;
        char* buff = nullptr;
        int size_x;
        int size_y;
        int current_index;

        void fill_buffer();
        int read_name_and_size(int& index);
        int read_birth_and_survival(int& index);
        void check_buff_reading(int result, Classes::GameField* child);
        bool is_digit(char num);
        int read_num(int* index, int& x);
        int get_buffer_size();

    public:
        ~FileReader(){
            delete [] buff;
        }
        void delete_data(std::string cmd_file){
            univerce_name.clear();
            birth_needed.clear();
            survival_needed.clear();
            if (cmd_file.size() == 0) file_name = nullptr;
            else delete [] file_name;
        }
        
        int read_buffer(Classes::GameField* game_field);
        int get_size();
        void set_filename(char* new_filename);
        void set_filename(std::string new_filename);
        const char* get_buffer();
        const int get_buff_size();
        const int get_current_index();
        const int get_size_x();
        const int get_size_y();
        std::vector<char> get_birth();
        std::vector<char> get_survive();
        std::string get_univerce_name();
        const char* get_filename();
    };
}