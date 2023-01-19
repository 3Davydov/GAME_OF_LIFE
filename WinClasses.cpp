#include "WinClasses.hpp"
#include "WinProcesses.hpp"
#include "SupportiveFunctions.hpp"
#include "MyConstants.hpp"

#pragma once

using namespace game_of_life_constants;
namespace Classes{

    /*
    Class "AbstractWindow"
    */

    void AbstractWindow::set_window_descriptor(HWND new_descriptor){
        if (new_descriptor != NULL) this->window_d = new_descriptor;
    }
    void AbstractWindow::set_window_name(TCHAR* new_name){
        if (new_name != NULL && this->window_name == nullptr) 
            this->window_name = new_name;
    }
    void AbstractWindow::set_window_class(WNDCLASS new_class){
        this->window_class = new_class;
    }
    void AbstractWindow::set_window_proc(WNDPROC new_proc){
        this->window_proc = new_proc;
    }

    const HWND AbstractWindow::get_window_despriptor(){
        return this->window_d;
    }

    void AbstractWindow::create_win_class(HINSTANCE hInstance){
            this->window_class.hInstance = hInstance;    
            this->window_class.lpszClassName = this->window_name;   
            this->window_class.lpfnWndProc = this->window_proc;  
            this->window_class.style = CS_HREDRAW | CS_VREDRAW;  
            this->window_class.hIcon = LoadIcon(NULL, IDI_APPLICATION); 
            this->window_class.hCursor = LoadCursor(NULL,IDC_ARROW); 
            this->window_class.lpszMenuName = NULL; 
            this->window_class.cbClsExtra = NULL; 
            this->window_class.cbWndExtra = NULL; 
            this->window_class.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
            RegisterClass(&(this->window_class));
    }

    void AbstractWindow::set_cmd_input_file(std::string cmd_input_file){
        if (cmd_input_file.size() != empty_param) this->cmd_input_file = cmd_input_file;
    }
    void AbstractWindow::set_cmd_output_file(std::string cmd_output_file){
        if (cmd_output_file.size() != empty_param) this->cmd_output_file = cmd_output_file;
    }    
    void AbstractWindow::set_cmd_iter_num(std::string cmd_iter_num){
        if (cmd_iter_num.size() != empty_param) this->cmd_iter_num = cmd_iter_num;
    }
    void AbstractWindow::set_size_x(int new_size){
        if (new_size > empty_param) this->size_x = new_size;
    }
    void AbstractWindow::set_size_y(int new_size){
        if (new_size > empty_param) this->size_y = new_size;
    }
 
    const std::string AbstractWindow::get_cmd_input_file(){
        return this->cmd_input_file;
    }
    const std::string AbstractWindow::get_cmd_output_file(){
        return this->cmd_output_file;
    }
    const std::string AbstractWindow::get_cmd_iter_num(){
        return this->cmd_iter_num;
    }
    const int AbstractWindow::get_size_x(){
        return this->size_x;
    }
    const int AbstractWindow::get_size_y(){
        return this->size_y;
    }

    void AbstractWindow::CreateButton(HINSTANCE hInst, LPARAM lParam, HWND& hBtn, HWND hWnd, const TCHAR Name[], TCHAR visible_text[], int button_id){
        hInst = ((LPCREATESTRUCT)lParam)->hInstance;
        hBtn = CreateWindow(Name, visible_text, WS_CHILD | WS_VISIBLE | WS_BORDER, NULL, NULL, NULL, NULL, hWnd, (HMENU) button_id, hInst, NULL);
        ShowWindow(hBtn, SW_SHOWNORMAL);
    }

    HWND AbstractWindow::create_window(const TCHAR* class_name, const TCHAR* win_name, DWORD style, int x, int y, int nWidth, int nHeight, HWND parent, HINSTANCE hInstanse, void* ptr){
        return CreateWindow(class_name, win_name, style, x, y, nWidth, nHeight, parent, NULL, hInstanse, ptr);
    }

    /*   
    Class "MainWindow"
    */
    void MainWindow::init_window(TCHAR* win_name, WNDPROC win_proc){
        this->set_window_name(win_name);
        this->set_window_proc(win_proc);
    }

    void MainWindow::CreateAllButtons(HINSTANCE hInst, LPARAM lParam, HWND* DownloadButton, 
                                        HWND* ReadyButton, HWND* ReturnButton, HWND* OfflineButton){
        this->CreateButton(hInst, lParam, *DownloadButton, this->get_window_despriptor(), BName, _T("DOWNLOAD THE UNIVERSE FROM A FILE"), choose_file);
        this->CreateButton(hInst, lParam, *ReadyButton, this->get_window_despriptor(), BName, _T("CHOOSE A READY-MADE UNIVERSE"), choose_random);
        this->CreateButton(hInst, lParam, *ReturnButton, this->get_window_despriptor(), BName, _T("RETURN TO MAIN MENU"), choose_exit);
        this->CreateButton(hInst, lParam, *OfflineButton, this->get_window_despriptor(), BName, _T("OFFLINE MODE"), choose_offline);
    }

    void MainWindow::SetButtonsPosition(HWND* DownloadButton, HWND* ReadyButton, HWND* ReturnButton, HWND* OfflineButton){
        this->move_window(*DownloadButton, this->get_size_x()/2 - button_whidth/2, this->get_size_y()/2 - offset_for_download_button, button_whidth, button_heigh, TRUE);
        this->move_window(*ReadyButton, (this->get_size_x()/2 - button_whidth/2), (this->get_size_y()/2 - offset_for_ready_button), button_whidth, button_heigh, TRUE);
        this->move_window(*OfflineButton, (this->get_size_x()/2 - button_whidth/2), (this->get_size_y()/2 + offset_for_offline_button), button_whidth, button_heigh, TRUE);
        this->move_window(*ReturnButton, (this->get_size_x()/2 - button_whidth/2), (this->get_size_y()/2  + offset_for_return_button), button_whidth, button_heigh, TRUE);
    }

    /*
    Class "GameField"
    */
    GameField::~GameField(){
            for (int i = 0; i < get_size_x(); i++) {
                delete [] matrix[i];
            }
            delete [] matrix;
    }

    void GameField::create_matrix(){
            matrix = new char* [get_size_x()];
            for (int i = 0; i < get_size_x(); i++) matrix[i] = new char [get_size_y()];
            for (int i = 0; i < get_size_x(); i++){
                for (int j = 0; j < get_size_y(); j++){
                    matrix[i][j] = dead;
                }
            }
    }

    char GameField::birth_check(int x, int y, std::vector<char> birth_needed, std::vector<char> survival_needed, char** oldmatrix){
        int alive_nearby = 0;
        int inf_i = 0, inf_j = 0;
        for (int i = x - 1; i <= x + 1; i++){ 
            for (int j = y - 1; j <= y + 1; j++){
                i < 0 ? inf_i = i + get_size_x() : inf_i = i;
                j < 0 ? inf_j = j + get_size_y() : inf_j = j;
                if ((inf_i != x || inf_j != y) && oldmatrix[inf_i % get_size_x()][inf_j % get_size_y()] == alive) alive_nearby++;     
            }
        }
        for (unsigned int i = 0; i < birth_needed.size(); i++){
            if (alive_nearby == ((int)birth_needed[i] - convert_to_int)) return alive;
        }
        return dead;
    }

    char GameField::survive_check(int x, int y, std::vector<char> birth_needed, std::vector<char> survival_needed, char** oldmatrix){
        int alive_nearby = 0;
        int inf_i = 0, inf_j = 0;

        for (int i = x - 1; i <= x + 1; i++){ 
            for (int j = y - 1; j <= y + 1; j++){
                i < 0 ? inf_i = i + get_size_x() : inf_i = i;
                j < 0 ? inf_j = j + get_size_y() : inf_j = j;
                if ((inf_i != x || inf_j != y) && oldmatrix[inf_i % get_size_x()][inf_j % get_size_y()] == alive) alive_nearby++;
            }
        }

        for (unsigned int i = 0; i < survival_needed.size(); i++){
            if (alive_nearby == ((int)survival_needed[i] - convert_to_int)) return alive;
        }
        return dead;
    }

    void GameField::change_condition(){
        char** oldmatrix = new char* [this->get_size_x()];
        for (int i = 0; i < get_size_x(); i++) oldmatrix[i] = new char [this->get_size_y()];
        for (int i = 0; i < get_size_x(); i++){
            for (int j = 0; j < get_size_y(); j++){
                oldmatrix[i][j] = matrix[i][j];
            }
        }

        for (int i = 0; i < get_size_x(); i++){
            for (int j = 0; j < get_size_y(); j++){
                if (oldmatrix[i][j] == dead) matrix[i][j] = birth_check(i, j, birth_needed, survival_needed, oldmatrix);
                else matrix[i][j] = survive_check(i, j, birth_needed, survival_needed, oldmatrix);
            }
        }

        for (int i = 0; i < get_size_x(); i++) {
            delete [] oldmatrix[i];
        }
        delete [] oldmatrix;
    }

    int GameField::read_num(int* index, int& x, const char* buff, const int buff_size){
        std::string str_num = "";
        int sign = plus_sign;

        while(buff[*index] != space && buff[*index] != carriage_rollback && buff[*index] != new_line){
            if (buff[*index] != minus) str_num += buff[*index];
            if (buff[*index] == minus) sign = minus_sign;
            (*index) += small_step;
            if (*index == buff_size) break;
        }

        int num = NULL;
        if (str_num.length() == empty_param) return num_not_a_digit;

        try{
            num = std::stoi(str_num);
        }
        catch(std::invalid_argument err) {return num_not_a_digit;}
        catch(std::out_of_range err) {return num_not_a_digit;}
        
        x = num * sign;
        return num_is_digit;
    }

    int GameField::read_matrix(int index, const char* buff, const int buff_size, const int size_x, const int size_y, std::vector<char> birth_needed, std::vector<char> survival_needed){
        this->birth_needed = birth_needed;
        this->survival_needed = survival_needed;
        set_size_x(size_x);
        set_size_y(size_y);
        this->create_matrix();
        int x, y;

        while (index <= buff_size && (buff_size != 0)){
            if (!read_num(&index, x, buff, buff_size)) return not_a_digit;
            index += small_step;
            if (!read_num(&index, y, buff, buff_size)) return not_a_digit;
            if ((abs(x) > get_size_x() / 2 && x > 0) || (abs(y) > get_size_y() / 2 && y > 0)) 
                return wrong_coordinate;
            if ((abs(x) > size_x / 2 && x < 0) || (abs(y) > get_size_y() / 2 && y < 0)) 
                return wrong_coordinate;
            this->matrix[get_size_x() / 2 + x][this->get_size_y() / 2 - y] = alive;
            index += small_step;
        }
        HWND desc = NULL;
        desc = this->get_window_despriptor();
        SendMessage(this->get_window_despriptor(), redraw, (WPARAM) this, NULL);

        return succes;
    }

    std::string GameField::set_output(){
        std::string output = "Univerce name: " + this->univerce_name;
        output += "    Rules:  B";
        for (unsigned int i = 0; i < this->birth_needed.size(); i++) output += (char) this->birth_needed[i];
        output += "/S";
        for (unsigned int i = 0; i < this->survival_needed.size(); i++) output += (char) this->survival_needed[i];
        output += "    Current iteration: ";
        return output;
    }

    void GameField::dump_file(std::ofstream& out){
         out << "#N " << this->univerce_name << carriage_rollback << "#S " << this->get_size_x() << " " << this->get_size_y() << carriage_rollback << "#R B";
        for (unsigned int i = 0; i < this->birth_needed.size(); i++) out << this->birth_needed[i];
        out << "/S";
        for (unsigned int i = 0; i < this->survival_needed.size(); i++) out << this->survival_needed[i];

        for (int i = 0; i < this->get_size_x(); i++){
            for (int j = 0; j <this->get_size_y(); j++){
                if (this->matrix[i][j] == alive) 
                        out << carriage_rollback << -this->get_size_x()/2 + i <<  " " << this->get_size_y()/2 - j;
            }
        }
    }

    void GameField::get_birth_needed(std::vector<char> new_vec){
        for (unsigned int i = 0; i < new_vec.size(); i++) if (new_vec[i] <= 0) return;
        this->birth_needed = new_vec;
    }
    void GameField::get_survive_needed(std::vector<char> new_vec){
        for (unsigned int i = 0; i < new_vec.size(); i++) if (new_vec[i] <= 0) return;
        this->survival_needed = new_vec;
    }
    void GameField::get_univerce_name(std::string new_name){
        if (new_name != "") this->univerce_name = new_name;
    }

    void GameField::clear(){
        this->birth_needed.clear();
        this->survival_needed.clear();
        this->univerce_name.clear();
    }

    const char GameField::get_matrix_elem(int row, int col){
        return this->matrix[row][col];
    }

    void GameField::set_matrix_elem(int row, int col, int elem){
        if (elem == dead || elem == alive) this->matrix[row][col] = elem;
    }

    /*
    Class "GamePlayWindow"
    */

    void GamePlayWindow::init_window(TCHAR* win_name, WNDPROC win_proc){
            this->set_window_name(win_name);
            this->set_window_proc(win_proc);
            
    }

    void GamePlayWindow::CreateAllButtons(HINSTANCE hInst, LPARAM lParam, HWND* DumpButton, HWND* TickButton, HWND* ReturnButton,
        HWND* HelpButton, HWND* ExistButton, HWND* NewButton, HWND* Return_To_Game_Button){
        this->CreateButton(hInst, lParam, *DumpButton, this->get_window_despriptor(), BName, _T("DUMP"), choose_dump);
        this->CreateButton(hInst, lParam, *TickButton, this->get_window_despriptor(), BName, _T("TICK"), choose_tick);
        this->CreateButton(hInst, lParam, *ReturnButton, this->get_window_despriptor(), BName, _T("RETURN TO MENU"), choose__exit);
        this->CreateButton(hInst, lParam, *HelpButton, this->get_window_despriptor(), BName, _T("HELP"), choose_help);
        this->CreateButton(hInst, lParam, *ExistButton, this->get_window_despriptor(), BName, _T("SAVE TO EXIST FILE"), exist_file);
        this->CreateButton(hInst, lParam, *NewButton, this->get_window_despriptor(), BName, _T("SAVE TO NEW FILE"), new_file);
        this->CreateButton(hInst, lParam, *Return_To_Game_Button, this->get_window_despriptor(), BName, _T("RETURN TO GAME"), return_to_game);
    }

    void GamePlayWindow::SetButtonsPosition(HWND* DumpButton, HWND* TickButton, HWND* ReturnButton,
        HWND* HelpButton, HWND* ExistButton, HWND* NewButton, HWND* Return_To_Game_Button){
            this->move_window(*DumpButton, indent, indent, play_button_whidth, play_button_heigh, TRUE);
            this->move_window(*TickButton, indent, button_y_space, play_button_whidth, play_button_heigh, TRUE);
            this->move_window(*HelpButton, indent, button_y_space * 2 - indent, play_button_whidth, play_button_heigh, TRUE);
            this->move_window(*ReturnButton, indent, button_y_space * 3 - indent * 2, play_button_whidth, play_button_heigh, TRUE);
            this->move_window(*ExistButton, (this->get_size_x()/2 - button_whidth/2), (this->get_size_y()/2 - offset_for_offline_button - indent*2), button_whidth, button_heigh, TRUE);
            this->move_window(*NewButton, (this->get_size_x()/2 - button_whidth/2), (this->get_size_y()/2 + offset_for_offline_button - indent), button_whidth, button_heigh, TRUE);
            this->move_window(*Return_To_Game_Button, (this->get_size_x()/2 - button_whidth/2), (this->get_size_y()/2 + button_y_space - indent*2), button_whidth, button_heigh, TRUE);
            this->show_windows(SW_HIDE, *ExistButton, *NewButton, *Return_To_Game_Button);
        }

    void GamePlayWindow::check_buff_reading(int result, GameField* child){
        switch(result){
            case succes:
                {
                this->move_window((*child).get_window_despriptor(), button_y_space, indent + 1, (*child).get_size_x() * indent + 2, (*child).get_size_y() * indent + 2, TRUE);
                (*child).show_windows(SW_SHOW, (*child).get_window_despriptor());
                this->redraw_window(this->get_window_despriptor(), TRUE);
                break;
                }
            case wrong_coordinate:
                {
                MessageBox(this->get_window_despriptor(), _T("WRONG COORDINATE!"), _T("ERROR"), MB_OK);
                break;
                }
            case not_a_digit:
                {
                MessageBox(this->get_window_despriptor(), _T("FORBIDDEN SYMBOL INSTEAD OF DIGIT!"), _T("ERROR"), MB_OK);
                break;
                }
            case wrong_format:
                {
                MessageBox(this->get_window_despriptor(), _T("WRONG FORMAT!"), _T("ERROR"), MB_OK);
                break;
                }
            case wrong_size:
                {
                MessageBox(this->get_window_despriptor(), _T("WRONG SIZE!"), _T("ERROR"), MB_OK);
                break;
                }
        }
    }

    void GamePlayWindow::print_all_info(int flag, HWND* Return_To_Game_Button, WPARAM wParam, RECT* st, 
                                        RECT* st_t, char* text, RECT* st_t1, int size_out, int iteration){
        HDC hdc;
        PAINTSTRUCT ps;
        (*st).left = button_y_space;
        (*st).top = paintstruct_top;
        (*st).right = paintstruct_right;
        (*st).bottom = paintstruct_bottom;
        int wP = wParam;
        hdc = BeginPaint(this->get_window_despriptor(), &ps);
        GetClientRect(this->get_window_despriptor(), st_t);
        if (flag == flag_activated){
            char advice[advice_size] = "Enter the full file name here";
            GetClientRect(this->get_window_despriptor(), st);
            (*st_t1).top = button_y_space - indent*2;
            (*st_t1).bottom = button_y_space * 2 + indent;
            DrawText(hdc, advice, indent * 3, st, DT_SINGLELINE | DT_CENTER);
            DrawText(hdc, (LPCSTR) text, size_out, st, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
            return;
        }
        SetTextColor(hdc, BLACK_BRUSH);
        if (IsWindowVisible(*Return_To_Game_Button) == true && IsWindowVisible(this->game_field->get_window_despriptor()) == false){
            Supportive::print_help_info(*st, hdc);
            return;
        }
        std::string to_window = this->game_field->set_output() + Supportive::to_str(iteration);
        DrawText(hdc, (LPCSTR) to_window.c_str(), to_window.length(), st, DT_SINGLELINE | DT_NOCLIP | DT_CENTER);                
        EndPaint(this->get_window_despriptor(), &ps);
    }

    void GamePlayWindow::calculate_offline_mode(int& iteration, LPARAM lParam){
        iteration += lParam;
        SendMessage(this->game_field->get_window_despriptor(), change_matrix_for_iter, (WPARAM) this->game_field, lParam);
        InvalidateRect(this->get_window_despriptor(), NULL, TRUE);
        std::ofstream out;
        char out_file[out_file_size];
        out_file[this->get_cmd_output_file().size()] = end_of_string;
        std::copy(this->get_cmd_output_file().begin(), this->get_cmd_output_file().end(), out_file);
        out.open(out_file);
        if (!out.is_open()) MessageBox(this->get_window_despriptor(), _T("WRONG OUTPUT FILE NAME!"), _T("ERROR"), MB_OK);
        else{
            this->game_field->dump_file(out);
            out.close();
        }
    }

    GameField* GamePlayWindow::get_game_field_pointer(){
        return this->game_field;
    }
    void GamePlayWindow::set_file_name(char* new_name){
        this->file_name = new_name;
    }
    void GamePlayWindow::set_game_field_pointer(GameField* new_pointer){
        this->game_field = new_pointer;
    }
    const char* GamePlayWindow::get_filename(){
        return this->file_name;
    }

}