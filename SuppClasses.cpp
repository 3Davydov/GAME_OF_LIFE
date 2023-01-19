#include "SuppClasses.hpp"
#include "WinClasses.hpp"

#pragma once

namespace SuppClasses{

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

    void FileReader::fill_buffer(){
        HFILE FileHandle;
        for (int i = 0; i < this->buff_size; i++) buff[i] = 0; 
        FileHandle= _lopen(this->file_name, OF_READ);
        //if (FileHandle == HFILE_ERROR) ptr_hWnd_3->destroy_window(ptr_hWnd_3->window_d);
        _lread(FileHandle, this->buff, this->buff_size);
        _lclose(FileHandle);
    }

    bool FileReader::is_digit(char num){
        if ((int) num >= convert_to_int && (int) num <= (9 + convert_to_int)) return true;
        return false;
    }

    int FileReader::get_buffer_size(){
        FILE* f;
        if (fopen_s(&f, this->file_name, "r")) 
            return -1;
        fseek(f, 0, SEEK_END);
        int size = ftell(f);
        fclose(f);
        return size;
    }

    int FileReader::read_num(int* index, int& x){
        std::string str_num = "";
        int sign = plus_sign;

        while(this->buff[*index] != space && this->buff[*index] != carriage_rollback && this->buff[*index] != new_line){
            if (this->buff[*index] != minus) str_num += this->buff[*index];
            if (this->buff[*index] == minus) sign = minus_sign;
            (*index) += 1;
            if (*index == this->buff_size) break;
        }

        int num = 0;
        if (str_num.length() == 0) return num_not_a_digit;

        try{
            num = std::stoi(str_num);
        }
        catch(std::invalid_argument err) {return num_not_a_digit;}
        catch(std::out_of_range err) {return num_not_a_digit;}
        
        x = num * sign;
        return num_is_digit;
    }

    int FileReader::read_name_and_size(int& index){
        char current_symb = 0, prev_symb = 0;
        if (this->buff[index] != grid || this->buff[index + 1] != name_symbol) return wrong_format;
        index += 3;
        while(true){
            if (index >= this->buff_size) return wrong_format;
            current_symb = this->buff[index];

            if (current_symb != new_line && current_symb != carriage_rollback && current_symb != rules_symbol && current_symb != grid 
                && current_symb != size_symbol) this->univerce_name += current_symb;
        
            if (prev_symb == grid && current_symb == size_symbol){
                index += 2;
                if (!read_num(&index, size_x)) return not_a_digit;
                index++;
                if (!read_num(&index, size_y)) return not_a_digit;
                if (this->size_x > max_whidth || this->size_y > max_heigh) return wrong_size;
            }

            if (prev_symb == grid && current_symb == rules_symbol) {index += 3; break;}
            prev_symb = current_symb;
            index++;
        }
        return succes;
    }

    int FileReader::read_birth_and_survival(int& index){
        while (this->buff[index] != backslash){
            if (index >= this->buff_size) 
                return wrong_format;
            if (!is_digit((char) this->buff[index])) return not_a_digit;
            //game_field->birth_needed.push_back((char)buff[index]); после всего заполнить поля gamefield и game play
            this->birth_needed.push_back((char) this->buff[index]); 
            index++;
        }

        index += 2;

        while (this->buff[index] != carriage_rollback && this->buff[index] != new_line) {
            if (index >= this->buff_size){
                index++;
                break;
            }
            if (!is_digit((char) this->buff[index])) return not_a_digit;
            //game_field->survival_needed.push_back((char)buff[index]); !!!! то же самое
            this->survival_needed.push_back((char) this->buff[index]); index++;
        }
        return succes;
    }

    int FileReader::read_buffer(Classes::GameField* game_field){
        int index = 0;
        this->buff_size = empty_buff;
        this->buff_size = this->get_buffer_size();
        if (this->buff_size == empty_buff) return wrong_format;
        this->buff = new char [this->buff_size];
        this->fill_buffer();
        int tmp_res = read_name_and_size(index);
        if (tmp_res != succes) return tmp_res;

        tmp_res = read_birth_and_survival(index);
        if (tmp_res != succes) return tmp_res;

        while (this->buff[index] == carriage_rollback || this->buff[index] == new_line){
            if (index >= this->buff_size) 
                return wrong_format;
            index++;
        }
        this->current_index = index;
        return succes;
    }

    void FileReader::set_filename(char* new_filename){
        if (new_filename != nullptr && this->file_name == nullptr) this->file_name = new_filename;
    }

    void FileReader::set_filename(std::string new_filename){
        if (this->file_name == nullptr){
            this->file_name = new char [new_filename.size() + 1];
            this->file_name[new_filename.size()] = '\0';
            std::copy(new_filename.begin(), new_filename.end(), this->file_name);
        }
    }

    const char* FileReader::get_buffer(){
        return this->buff;
    }
    const int FileReader::get_buff_size(){
        return this->buff_size;
    }
    const int FileReader::get_current_index(){
        return this->current_index;
    }
    const int FileReader::get_size_x(){
        return this->size_x;
    }
    const int FileReader::get_size_y(){
        return this->size_y;
    }
    std::vector<char> FileReader::get_birth(){
        return this->birth_needed;
    }
    std::vector<char> FileReader::get_survive(){
        return this->survival_needed;
    }
    std::string FileReader::get_univerce_name(){
        return this->univerce_name;
    }
    const char* FileReader::get_filename(){
        return this->file_name;
    }

}