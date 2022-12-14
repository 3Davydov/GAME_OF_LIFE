#include "WinClasses.hpp"
#include "WinProcesses.hpp"
#include "SupportiveFunctions.hpp"

#ifndef WINCLASSESDEF
#define WINCLASSESDEF
/*   
Class "MainWindow"
*/
void MainWindow::init_window(TCHAR* win_name, WNDPROC win_proc){
        window_name = win_name;
        window_proc = win_proc;
}

void MainWindow::create_win_class(HINSTANCE hInstance, TCHAR Name[], WNDPROC Proc, WNDCLASS& wc){
        wc.hInstance = hInstance;    
        wc.lpszClassName = Name;   // ˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜  
        wc.lpfnWndProc = Proc;    // ˜˜˜˜˜˜˜ ˜˜˜˜  
        wc.style = CS_HREDRAW | CS_VREDRAW;  // ˜˜˜˜˜ ˜˜˜˜  
        wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); // ˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜  
        wc.hCursor = LoadCursor(NULL,IDC_ARROW); // ˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜  
        wc.lpszMenuName = NULL; // ˜˜˜ ˜˜˜˜  
        wc.cbClsExtra = 0;  // ˜˜˜ ˜˜˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜  
        wc.cbWndExtra = 0; 
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
        RegisterClass(&wc);
}

void MainWindow::CreateButton(HINSTANCE hInst, LPARAM lParam, HWND& hBtn, HWND hWnd, TCHAR Name[], TCHAR visible_text[], int button_id){
        hInst = ((LPCREATESTRUCT)lParam)->hInstance;
        hBtn = CreateWindow(Name, visible_text, WS_CHILD | WS_VISIBLE | WS_BORDER, 0, 100, 120, 30, hWnd, (HMENU) button_id, hInst, NULL);
        ShowWindow(hBtn, SW_SHOWNORMAL);
}

void MainWindow::CreateAllButtons(HINSTANCE hInst, LPARAM lParam, HWND* DownloadButton, 
                                    HWND* ReadyButton, HWND* ReturnButton, HWND* OfflineButton){
    this->CreateButton(hInst, lParam, *DownloadButton, this->window_d, BName, _T("DOWNLOAD THE UNIVERSE FROM A FILE"), CHOOSE_FILE);
    this->CreateButton(hInst, lParam, *ReadyButton, this->window_d, BName, _T("CHOOSE A READY-MADE UNIVERSE"), CHOOSE_RANDOM);
    this->CreateButton(hInst, lParam, *ReturnButton, this->window_d, BName, _T("RETURN TO MAIN MENU"), CHOOSE_EXIT);
    this->CreateButton(hInst, lParam, *OfflineButton, this->window_d, BName, _T("OFFLINE MODE"), CHOOSE_OFFLINE);
}

void MainWindow::SetButtonsPosition(HWND* DownloadButton, HWND* ReadyButton, HWND* ReturnButton, HWND* OfflineButton){
    this->move_window(*DownloadButton, (this->size_x/2 - 250), (this->size_y/2 - 35 - 30 - 70 - 30), 500, 30, TRUE);
    this->move_window(*ReadyButton, (this->size_x/2 - 250), (this->size_y/2 - 35 - 30), 500, 30, TRUE);
    this->move_window(*OfflineButton, (this->size_x/2 - 250), (this->size_y/2 + 35), 500, 30, TRUE);
    this->move_window(*ReturnButton, (this->size_x/2 - 250), (this->size_y/2  + 35 + 30 + 70), 500, 30, TRUE);
}

/*
Class "GameField"
*/
GameField::~GameField(){
        for (int i = 0; i < size_x; i++) {
            delete [] matrix[i];
        }
        delete [] matrix;
}

void GameField::create_matrix(){
        matrix = new char* [size_x];
        for (int i = 0; i < size_x; i++) matrix[i] = new char [size_y];
        for (int i = 0; i < size_x; i++){
            for (int j = 0; j < size_y; j++){
                matrix[i][j] = DEAD;
            }
        }
}

char GameField::birth_check(int x, int y, std::vector<char> birth_needed, std::vector<char> survival_needed, char** oldmatrix){
    int alive_nearby = 0;
    int inf_i = 0, inf_j = 0;
    for (int i = x - 1; i <= x + 1; i++){ 
        for (int j = y - 1; j <= y + 1; j++){
            i < 0 ? inf_i = i + size_x : inf_i = i;
            j < 0 ? inf_j = j + size_y : inf_j = j;
            if ((inf_i != x || inf_j != y) && oldmatrix[inf_i % size_x][inf_j % size_y] == ALIVE) alive_nearby++;     
        }
    }
    for (unsigned int i = 0; i < birth_needed.size(); i++){
        if (alive_nearby == ((int)birth_needed[i] - CONVERT_TO_INT)) return ALIVE;
    }
    return DEAD;
}

char GameField::survive_check(int x, int y, std::vector<char> birth_needed, std::vector<char> survival_needed, char** oldmatrix){
    int alive_nearby = 0;
    int inf_i = 0, inf_j = 0;

    for (int i = x - 1; i <= x + 1; i++){ 
        for (int j = y - 1; j <= y + 1; j++){
            i < 0 ? inf_i = i + size_x : inf_i = i;
            j < 0 ? inf_j = j + size_y : inf_j = j;
            if ((inf_i != x || inf_j != y) && oldmatrix[inf_i % size_x][inf_j % size_y] == ALIVE) alive_nearby++;
        }
    }

    for (unsigned int i = 0; i < survival_needed.size(); i++){
        if (alive_nearby == ((int)survival_needed[i] - CONVERT_TO_INT)) return ALIVE;
    }
    return DEAD;
}

void GameField::change_condition(){
    char** oldmatrix = new char* [size_x];
    for (int i = 0; i < size_x; i++) oldmatrix[i] = new char [size_y];
    for (int i = 0; i < size_x; i++){
        for (int j = 0; j < size_y; j++){
            oldmatrix[i][j] = matrix[i][j];
        }
    }

    for (int i = 0; i < size_x; i++){
        for (int j = 0; j < size_y; j++){
            if (oldmatrix[i][j] == DEAD) matrix[i][j] = birth_check(i, j, birth_needed, survival_needed, oldmatrix);
            else matrix[i][j] = survive_check(i, j, birth_needed, survival_needed, oldmatrix);
        }
    }

    for (int i = 0; i < size_x; i++) {
        delete [] oldmatrix[i];
    }
    delete [] oldmatrix;
}

/*
Class "GamePlayWindow"
*/

void GamePlayWindow::init_window(TCHAR* win_name, WNDPROC win_proc){
        window_name = win_name;
        window_proc = win_proc;
}

void GamePlayWindow::create_win_class(HINSTANCE hInstance, TCHAR Name[], WNDPROC Proc, WNDCLASS& wc){
        wc.hInstance = hInstance;    
        wc.lpszClassName = Name;   // ˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜  
        wc.lpfnWndProc = Proc;    // ˜˜˜˜˜˜˜ ˜˜˜˜  
        wc.style = CS_HREDRAW | CS_VREDRAW;  // ˜˜˜˜˜ ˜˜˜˜  
        wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); // ˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜  
        wc.hCursor = LoadCursor(NULL,IDC_ARROW); // ˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜  
        wc.lpszMenuName = NULL; // ˜˜˜ ˜˜˜˜  
        wc.cbClsExtra = 0;  // ˜˜˜ ˜˜˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜  
        wc.cbWndExtra = 0; 
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
        RegisterClass(&wc);
}

void GamePlayWindow::CreateButton(HINSTANCE hInst, LPARAM lParam, HWND& hBtn, HWND hWnd, TCHAR Name[], TCHAR visible_text[], int button_id){
        hInst = ((LPCREATESTRUCT)lParam)->hInstance;
        hBtn = CreateWindow(Name, visible_text, WS_CHILD | WS_VISIBLE | WS_BORDER, 0, 100, 120, 30, hWnd, (HMENU) button_id, hInst, NULL);
        ShowWindow(hBtn, SW_SHOWNORMAL);
}

bool GamePlayWindow::is_digit(char num){
        if ((int) num >= CONVERT_TO_INT && (int) num <= (9 + CONVERT_TO_INT)) return true;
        return false;
}

int GamePlayWindow::read_num(const char* buff, int size, int* index, int& x){
        std::string str_num = "";
        int sign = 1;

        while(buff[*index] != SPACE && buff[*index] != CARRIAGE_ROLLBACK && buff[*index] != NEW_LINE){
            if (buff[*index] != MINUS) str_num += buff[*index];
            if (buff[*index] == MINUS) sign = -1;
            (*index) += 1;
            if (*index == size) break;
        }

        int num = 0;
        if (str_num.length() == 0) return 0;

        try{
            num = std::stoi(str_num);
        }
        catch(std::invalid_argument err) {return 0;}
        catch(std::out_of_range err) {return 0;}
        
        x = num * sign;
        return 1;
}

int GamePlayWindow::read_name_and_size(int& index, const char* buff, int size){
    char current_symb = 0, prev_symb = 0;
    if (buff[index] != GRID || buff[index + 1] != NAME_SYMBOL) return WRONG_FORMAT;
    index += 3;
    while(true){
        if (index >= size) return WRONG_FORMAT;
        current_symb = buff[index];

        if (current_symb != NEW_LINE && current_symb != CARRIAGE_ROLLBACK && current_symb != RULES_SYMBOL && current_symb != GRID 
            && current_symb != SIZE_SYMBOL) univerce_name += current_symb;
    
        if (prev_symb == GRID && current_symb == SIZE_SYMBOL){
            index += 2;
            if (!read_num(buff, size, &index, size_x)) return NOT_A_DIGIT;
            index++;
            if (!read_num(buff, size, &index, size_y)) return NOT_A_DIGIT;
            if (size_x > MAX_WHIDTH || size_y > MAX_HEIGH) return WRONG_SIZE;
        }

        if (prev_symb == GRID && current_symb == RULES_SYMBOL) {index += 3; break;}
        prev_symb = current_symb;
        index++;
    }
    return SUCCES;
}

int GamePlayWindow::read_birth_and_survival(int& index, const char* buff, int size){
     while (buff[index] != BACKSLASH){
            if (index >= size) 
                return WRONG_FORMAT;
            if (!is_digit((char) buff[index])) return NOT_A_DIGIT;
            game_field->birth_needed.push_back((char)buff[index]); 
            birth_needed.push_back((char)buff[index]); 
            index++;
        }

    index += 2; // ˜˜˜˜˜˜˜˜˜˜ S

    while (buff[index] != CARRIAGE_ROLLBACK && buff[index] != NEW_LINE) {
        if (index >= size){
            index++;
            break;
        }
        if (!is_digit((char) buff[index])) return NOT_A_DIGIT;
        game_field->survival_needed.push_back((char)buff[index]); 
        survival_needed.push_back((char)buff[index]); index++;
    }
    return SUCCES;
}

int GamePlayWindow::read_matrix(int& index, const char* buff, int size){
    game_field->size_x = size_x;
    game_field->size_y = size_y;
    game_field->create_matrix();
    int x, y;

    while (index <= size){
        if (!read_num(buff, size, &index, x)) return NOT_A_DIGIT;
        index += 1;
        if (!read_num(buff, size, &index, y)) return NOT_A_DIGIT;
        if ((abs(x) >= size_x / 2 && x > 0) || (abs(y) >= size_y / 2 && y > 0)) return WRONG_CORDINATE;
        if ((abs(x) > size_x / 2 && x < 0) || (abs(y) > size_y / 2 && y < 0)) return WRONG_CORDINATE;
        game_field->matrix[game_field->size_x / 2 + x][game_field->size_y / 2 - y] = ALIVE;
        index += 1;
    }

    return SUCCES;
}

int GamePlayWindow::read_buffer(const char* buff, int size){
        int index = 0;
        int tmp_res = read_name_and_size(index, buff, size);
        if (tmp_res != SUCCES) return tmp_res;

        tmp_res = read_birth_and_survival(index, buff, size);
        if (tmp_res != SUCCES) return tmp_res;

        while (buff[index] == CARRIAGE_ROLLBACK || buff[index] == NEW_LINE){
            if (index >= size) 
                return WRONG_FORMAT;
            index++;
        }

        tmp_res = read_matrix(index, buff, size);
        if (tmp_res != SUCCES) return tmp_res;
        
        SendMessage(game_field->window_d, REDRAW, (WPARAM) game_field, NULL);
        return SUCCES;
    }

void GamePlayWindow::CreateAllButtons(HINSTANCE hInst, LPARAM lParam, HWND* DumpButton, HWND* TickButton, HWND* ReturnButton,
    HWND* HelpButton, HWND* ExistButton, HWND* NewButton, HWND* Return_To_Game_Button){
    this->CreateButton(hInst, lParam, *DumpButton, this->window_d, BName, _T("DUMP"), CHOOSE_DUMP);
    this->CreateButton(hInst, lParam, *TickButton, this->window_d, BName, _T("TICK"), CHOOSE_TICK);
    this->CreateButton(hInst, lParam, *ReturnButton, this->window_d, BName, _T("RETURN TO MENU"), CHOOSE__EXIT);
    this->CreateButton(hInst, lParam, *HelpButton, this->window_d, BName, _T("HELP"), CHOOSE_HELP);
    this->CreateButton(hInst, lParam, *ExistButton, this->window_d, BName, _T("SAVE TO EXIST FILE"), EXIST_FILE);
    this->CreateButton(hInst, lParam, *NewButton, this->window_d, BName, _T("SAVE TO NEW FILE"), NEW_FILE);
    this->CreateButton(hInst, lParam, *Return_To_Game_Button, this->window_d, BName, _T("RETURN TO GAME"), RETURN_TO_GAME);
}

void GamePlayWindow::SetButtonsPosition(HWND* DumpButton, HWND* TickButton, HWND* ReturnButton,
    HWND* HelpButton, HWND* ExistButton, HWND* NewButton, HWND* Return_To_Game_Button){
        this->move_window(*DumpButton, 10, 10, 200, 150, TRUE);
        this->move_window(*TickButton, 10, 150 + 10 + 60, 200, 150, TRUE);
        this->move_window(*HelpButton, 10, 220 + 150 + 60, 200, 150, TRUE);
        this->move_window(*ReturnButton, 10, 430 + 150 + 60, 200, 150, TRUE);
        this->move_window(*ExistButton, (this->size_x/2 - 250), (this->size_y/2 - 15 - 40), 500, 30, TRUE);
        this->move_window(*NewButton, (this->size_x/2 - 250), (this->size_y/2 - 15 + 40), 500, 30, TRUE);
        this->move_window(*Return_To_Game_Button, (this->size_x/2 -250), (this->size_y/2 + 200), 500, 30, TRUE);
        this->show_windows(SW_HIDE, *ExistButton, *NewButton, *Return_To_Game_Button);
    }

void GamePlayWindow::check_buff_reading(int result, GameField* child){
    switch(result){
        case SUCCES:
            {
            this->move_window((*child).window_d, 220, 11, (*child).size_x * 10 + 2, (*child).size_y * 10 + 2, TRUE);
            (*child).show_windows(SW_SHOW, (*child).window_d);
            this->redraw_window(this->window_d, TRUE);
            break;
            }
        case WRONG_CORDINATE:
            {
            MessageBox(this->window_d, _T("WRONG COORDINATE!"), _T("ERROR"), MB_OK);
            break;
            }
        case NOT_A_DIGIT:
            {
            MessageBox(this->window_d, _T("FORBIDDEN SYMBOL INSTEAD OF DIGIT!"), _T("ERROR"), MB_OK);
            break;
            }
        case WRONG_FORMAT:
            {
            MessageBox(this->window_d, _T("WRONG FORMAT!"), _T("ERROR"), MB_OK);
            break;
            }
        case WRONG_SIZE:
            {
            MessageBox(this->window_d, _T("WRONG SIZE!"), _T("ERROR"), MB_OK);
            break;
            }
    }
}

void GamePlayWindow::print_all_info(int flag, HWND* Return_To_Game_Button, WPARAM wParam, RECT* st, 
                                    RECT* st_t, char* text, RECT* st_t1, int size_out, int iteration){
    HDC hdc;
    PAINTSTRUCT ps;
    (*st).left = 220;
    (*st).top = 742;
    (*st).right = 1300;
    (*st).bottom = 772;
    int wP = wParam;
    hdc = BeginPaint(this->window_d, &ps);
    GetClientRect(this->window_d, st_t);
    if (flag == 1){
        char advice[30] = "Enter the full file name here";
        GetClientRect(this->window_d, st);
        (*st_t1).top = 400;
        (*st_t1).bottom = 450;
        DrawText(hdc, advice, 30, st, DT_SINGLELINE | DT_CENTER);
        DrawText(hdc, (LPCSTR) text, size_out, st, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
        return;
    }
    SetTextColor(hdc, BLACK_BRUSH);
    if (IsWindowVisible(*Return_To_Game_Button) == true && IsWindowVisible(this->game_field->window_d) == false){
        print_help_info(*st, hdc);
        return;
    }
    std::string to_window = set_output(this) + to_str(iteration);
    DrawText(hdc, (LPCSTR) to_window.c_str(), to_window.length(), st, DT_SINGLELINE | DT_NOCLIP | DT_CENTER);                
    EndPaint(this->window_d, &ps);
}

void GamePlayWindow::calculate_offline_mode(int& iteration, LPARAM lParam){
    iteration += lParam;
    SendMessage(this->game_field->window_d, CHANGE_MATRIX_FOR_ITER, (WPARAM) this->game_field, lParam);
    InvalidateRect(this->window_d, NULL, TRUE);
    std::ofstream out;
    char out_file[200];
    out_file[this->cmd_output_file.size()] = '\0';
    std::copy(this->cmd_output_file.begin(), this->cmd_output_file.end(), out_file);
    out.open(out_file);
    if (!out.is_open()) MessageBox(this->window_d, _T("WRONG OUTPUT FILE NAME!"), _T("ERROR"), MB_OK);
    else{
        dump_file(out, this);
        out.close();
    }
}

#endif