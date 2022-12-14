#include "SupportiveFunctions.hpp"
#include "WinClasses.hpp"
#include "WinProcesses.hpp"

#ifndef SUPPORTIVE
#define SUPPORTIVE

void add_new_symbol(int& size, char wParam, char* text, GamePlayWindow* ptr_hWnd_3){
    switch ((TCHAR)wParam){
        case VK_BACK:
            if (size > 0) size--;
            break;
        default:
            if ((int) wParam >= MIN_ALLOWED_SYMBOL && (int) wParam <= MAX_ALLOWED_SYMBOL && (TCHAR) wParam != VK_RETURN){
                text[size] = (char) wParam;
                size++;
            }
            break;
    }
    ptr_hWnd_3->redraw_window(ptr_hWnd_3->window_d, TRUE);
}

std::string to_str(int num){
    std::string str_num = "";
    while (num > 0){
        str_num += (char)(num % 10) + CONVERT_TO_INT;
        num /= 10;
    }
    std::reverse(str_num.begin(), str_num.end());
    if (str_num.size() == 0) str_num += "0";
    return str_num;
}

void fill_buffer(GamePlayWindow* ptr_hWnd_3, int size, char* buff){
    HFILE FileHandle;
    for (int i = 0; i < size; i++) buff[i] = 0; 
    FileHandle= _lopen(ptr_hWnd_3->file_name, OF_READ);
    if (FileHandle == HFILE_ERROR) ptr_hWnd_3->destroy_window(ptr_hWnd_3->window_d);
    _lread(FileHandle, buff, size);
    _lclose(FileHandle);
}

int get_buffer_size(char* name){
    FILE* f;
    if (fopen_s(&f, name, "r")) return -1;
    fseek(f, 0, SEEK_END);
    int size = ftell(f);
    fclose(f);
    return size;
}

std::string set_output(GamePlayWindow* ptr_hWnd_3){
    std::string output = "Univerce name: " + ptr_hWnd_3->univerce_name;
    output += "    Rules:  B";
    for (unsigned int i = 0; i < ptr_hWnd_3->birth_needed.size(); i++) output += (char) ptr_hWnd_3->birth_needed[i];
    output += "/S";
    for (unsigned int i = 0; i < ptr_hWnd_3->survival_needed.size(); i++) output += (char) ptr_hWnd_3->survival_needed[i];
    output += "    Current iteration: ";
    return output;
}

void dump_file(std::ofstream& out, GamePlayWindow* ptr_hWnd_3){
    out << "#N " << ptr_hWnd_3->univerce_name << CARRIAGE_ROLLBACK << "#S " << ptr_hWnd_3->size_x << " " << ptr_hWnd_3->size_y << CARRIAGE_ROLLBACK << "#R B";

    for (unsigned int i = 0; i < ptr_hWnd_3->birth_needed.size(); i++) out << ptr_hWnd_3->birth_needed[i];

    out << "/S";

    for (unsigned int i = 0; i < ptr_hWnd_3->survival_needed.size(); i++) out << ptr_hWnd_3->survival_needed[i];

    for (int i = 0; i < ptr_hWnd_3->size_x; i++){
        for (int j = 0; j < ptr_hWnd_3->size_y; j++){
            if (ptr_hWnd_3->game_field->matrix[i][j] == ALIVE) 
                    out << CARRIAGE_ROLLBACK << -ptr_hWnd_3->size_x/2 + i <<  " " << ptr_hWnd_3->size_y/2 - j;
        }
    }
}

void print_help_info(RECT st, HDC hdc){
    std::string to_window = "DUMP - save the universe to a file. You can select an existing file, or create a new one";
    st.top = 100;
    st.bottom = 150;
    DrawText(hdc, (LPCSTR) to_window.c_str(), to_window.length(), &st, DT_NOCLIP | DT_CENTER);
    st.top = 160;
    st.bottom = 210;
    to_window = "TICK - calculate the state of the field in one iteration";
    DrawText(hdc, (LPCSTR) to_window.c_str(), to_window.length(), &st, DT_NOCLIP | DT_CENTER);
}

void add_menu_to_main(MainWindow& hWnd, MENUITEMINFO& mii_system){
    mii_system.cbSize = sizeof(MENUITEMINFO);
    mii_system.fMask = MIIM_STRING | MIIM_ID;
    mii_system.wID = MENU_WHITE;
    mii_system.dwTypeData = "White";

    HMENU hMainMenu = CreateMenu();
    HMENU hPopMenuFile = CreatePopupMenu();
    HMENU hPopMenuFile1 = CreatePopupMenu();
    HMENU hPopMenuFile2 = CreatePopupMenu();
    AppendMenu(hMainMenu, MF_STRING, MENU_EXIT, _T("Exit"));
    AppendMenu(hMainMenu, MF_STRING | MF_POPUP, (UINT)hPopMenuFile, _T("Settings"));
    AppendMenu(hPopMenuFile, MF_STRING | MF_POPUP, (UINT)hPopMenuFile1, _T("Background style"));
    AppendMenu(hPopMenuFile1, MF_STRING, MENU_GREEN, _T("Green"));
    InsertMenuItem(hPopMenuFile1, (UINT)hPopMenuFile2, FALSE, &mii_system);
    SetMenu(hWnd.window_d, hMainMenu);
    SetMenu(hWnd.window_d, hPopMenuFile);
}

void get_window_description(MainWindow** ptr_window, LPARAM info, HINSTANCE hInst, HWND window){
    hInst = ((LPCREATESTRUCT)info)->hInstance;
    SetWindowLongPtr(window, GWLP_USERDATA, (LONG)((LPCREATESTRUCT)info)->lpCreateParams);
    *ptr_window = (MainWindow*)GetWindowLongPtr(window, GWLP_USERDATA);
    (*ptr_window)->window_d = window;
}

void get_window_description(GamePlayWindow** ptr_window, LPARAM info, HINSTANCE hInst, HWND window){
    hInst = ((LPCREATESTRUCT)info)->hInstance;
    SetWindowLongPtr(window, GWLP_USERDATA, (LONG)((LPCREATESTRUCT)info)->lpCreateParams);
    *ptr_window = (GamePlayWindow*)GetWindowLongPtr(window, GWLP_USERDATA);
    (*ptr_window)->window_d = window;
}

void switch_lparam_MainMenu(LPARAM message, MainWindow** ptr_window, HWND hWnd, MainWindow* next_window, MainWindow** ptr_next_window, HINSTANCE hInst){
    switch(message){
        case MENU_GREEN: {
            HBRUSH greenBrush = CreateSolidBrush(RGB(40,80,0));
            (*ptr_window)->redraw_window((*ptr_window)->window_d, TRUE);
            SetClassLong(hWnd,GCLP_HBRBACKGROUND,(LONG)greenBrush);
            break; }
        case MENU_WHITE: {
            HBRUSH whiteBrush = CreateSolidBrush(RGB(255,255,255));
            (*ptr_window)->redraw_window((*ptr_window)->window_d, TRUE);
            SetClassLong(hWnd,GCLP_HBRBACKGROUND,(LONG)whiteBrush);
            break; }
        case MENU_EXIT: {
            if (MessageBox(hWnd, _T("Really exit?"), _T("Think twice"), MB_OKCANCEL) == IDOK){
                (*ptr_window)->destroy_window((*ptr_window)->window_d);
            }
            break; }
        case RULES_BUTTON: {
            (*ptr_window)->destroy_window((*ptr_window)->window_d);
            break; }
        case PLAY_BUTTON: {
            (*next_window).cmd_input_file = (*ptr_window)->cmd_input_file;
            (*next_window).cmd_output_file = (*ptr_window)->cmd_output_file;
            (*next_window).cmd_iter_num = (*ptr_window)->cmd_iter_num;
            (*next_window).window_d = (*next_window).create_window(PName, _T("Play"), WS_OVERLAPPEDWINDOW, 0, 0, 500, 500, hWnd, hInst, *ptr_next_window);
            (*next_window).show_windows(SW_MAXIMIZE, (*next_window).window_d);
            (*ptr_window)->show_windows(SW_HIDE, (*ptr_window)->window_d);
            break; }
    }    
}

void switch_lparam_SuppMenu(GamePlayWindow** ptr_Field, GamePlayWindow* Field, MainWindow** ptr_SuppMenu, 
                            char* ready_universe, LPARAM message, HINSTANCE hInst, HWND hWnd_2){
    switch(message){
        case CHOOSE_FILE: {
            (*Field).window_d = (*Field).create_window(GName, _T("Game"), WS_OVERLAPPEDWINDOW, 0, 0, 500, 500, hWnd_2, hInst, *ptr_Field);
            (*Field).show_windows(SW_MAXIMIZE, (*Field).window_d);
            (*ptr_SuppMenu)->show_windows(SW_HIDE, (*ptr_SuppMenu)->window_d);
            break; }
        case CHOOSE_RANDOM: {
            (*ptr_Field)->file_name = ready_universe;
            (*Field).window_d = (*Field).create_window(GName, _T("Game"), WS_OVERLAPPEDWINDOW, 0, 0, 500, 500, hWnd_2, hInst, *ptr_Field);
            (*Field).show_windows(SW_MAXIMIZE, (*Field).window_d);
            (*ptr_SuppMenu)->show_windows(SW_HIDE, (*ptr_SuppMenu)->window_d);
            break; }
        case CHOOSE_OFFLINE: {
            if ((*ptr_SuppMenu)->cmd_input_file.length() == 0){
                    MessageBox((*ptr_Field)->window_d, _T("NO INPUT FILE!"), _T("ERROR"), MB_OK);
            }
            else{
                (*Field).cmd_input_file = (*ptr_SuppMenu)->cmd_input_file;
                (*Field).cmd_output_file = (*ptr_SuppMenu)->cmd_output_file;
                (*Field).cmd_iter_num = (*ptr_SuppMenu)->cmd_iter_num;
                (*Field).window_d = (*Field).create_window(GName, _T("Game"), WS_OVERLAPPEDWINDOW, 0, 0, 500, 500, hWnd_2, hInst, *ptr_Field);
                (*Field).show_windows(SW_MAXIMIZE, (*Field).window_d);
                (*ptr_SuppMenu)->show_windows(SW_HIDE, (*ptr_SuppMenu)->window_d);
            }
            break; }
        case CHOOSE_EXIT: {
            HWND hc;
            hc = FindWindow(WinName,  _T("Application"));
            ShowWindow(hc, SW_SHOW);
            (*ptr_SuppMenu)->destroy_window((*ptr_SuppMenu)->window_d);
            break; }
    }
}

void choose_file_to_open(GamePlayWindow** ptr_Field, char** buff, OPENFILENAME* file, TCHAR* name, GameField* child){
    (*ptr_Field)->game_field = child;
    if ((*ptr_Field)->cmd_input_file != ""){
        (*ptr_Field)->file_name = new char [(*ptr_Field)->cmd_input_file.size() + 1];
        (*ptr_Field)->file_name[(*ptr_Field)->cmd_input_file.size()] = '\0';
        std::copy((*ptr_Field)->cmd_input_file.begin(), (*ptr_Field)->cmd_input_file.end(), (*ptr_Field)->file_name);
    } 
    if ((*ptr_Field)->file_name == nullptr){
        GetOpenFileName(file);
        (*ptr_Field)->file_name = name;
        (*ptr_Field)->size = get_buffer_size((*ptr_Field)->file_name);
        *buff = new char [(*ptr_Field)->size];
        for (int i = 0; i < (*ptr_Field)->size; i++) (*buff)[i] = 0; 
        fill_buffer((*ptr_Field), (*ptr_Field)->size, *buff);
    }
    else{
        (*ptr_Field)->size = get_buffer_size((*ptr_Field)->file_name);
        if ((*ptr_Field)->size == -1) {
            MessageBox((*ptr_Field)->window_d, _T("WRONG INPUT FILE NAME!"), _T("ERROR"), MB_OK);
        }
        else{
            *buff = new char [(*ptr_Field)->size]; 
            for (int i = 0; i < (*ptr_Field)->size; i++) (*buff)[i] = 0;
            fill_buffer((*ptr_Field), (*ptr_Field)->size, *buff);
        }
    }
}

void set_file_settings(OPENFILENAME* file, HINSTANCE hInst, TCHAR* name){
    (*file).lStructSize = sizeof(OPENFILENAME);
    (*file).hInstance = hInst;
    (*file).lpstrFilter = _T("Text\0*.txt");
    (*file).lpstrFile = name;
    (*file).nMaxFile = 256;
    (*file).lpstrInitialDir = _T(".\\");
    (*file).lpstrDefExt = _T("txt");
    (*file).Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_READONLY;
}

void switch_lparam_Field(LPARAM lParam, GamePlayWindow** ptr_Field, int& iteration, char** text, int& flag, 
                        HWND* DumpButton, HWND* TickButton, HWND* ReturnButton,HWND* HelpButton, HWND* ExistButton, 
                        HWND* NewButton, HWND* Return_To_Game_Button, OPENFILENAME* file, TCHAR* name){
    HWND hc;
    switch(lParam){
        case CHOOSE__EXIT: {
            hc = FindWindow(PName,  _T("PLAY"));
            ShowWindow(hc, SW_SHOW);
            (*ptr_Field)->survival_needed.clear();
            (*ptr_Field)->birth_needed.clear();
            (*ptr_Field)->univerce_name.clear();
            iteration = 0;
            (*ptr_Field)->game_field->destroy_window((*ptr_Field)->game_field->window_d);
            (*ptr_Field)->destroy_window((*ptr_Field)->window_d);
            break; }
        case CHOOSE_TICK: {
            iteration++;
            SendMessage((*ptr_Field)->game_field->window_d, CHANGE_MATRIX, (WPARAM) (*ptr_Field)->game_field, NULL);
            InvalidateRect((*ptr_Field)->window_d, NULL, TRUE);
            break; }
        case CHOOSE_DUMP: {
            (*ptr_Field)->show_windows(SW_HIDE, *DumpButton, *TickButton, *ReturnButton, *HelpButton,  (*ptr_Field)->game_field->window_d);
            (*ptr_Field)->show_windows(SW_SHOW, *ExistButton, *NewButton);
            break; }
        case CHOOSE_HELP: {
            if (IsWindowVisible((*ptr_Field)->game_field->window_d)){
                (*ptr_Field)->show_windows(SW_HIDE, *DumpButton, *TickButton, *ReturnButton, *HelpButton, (*ptr_Field)->game_field->window_d);
                (*ptr_Field)->show_windows(SW_SHOW, *Return_To_Game_Button);
                (*ptr_Field)->redraw_window((*ptr_Field)->window_d, TRUE);
            }
            break; }
        case RETURN_TO_GAME: {
            (*ptr_Field)->show_windows(SW_SHOW, *DumpButton, *TickButton, *ReturnButton, *HelpButton, (*ptr_Field)->game_field->window_d);
            (*ptr_Field)->show_windows(SW_HIDE, *Return_To_Game_Button);
            (*ptr_Field)->redraw_window((*ptr_Field)->window_d, TRUE);
            break; }
        case EXIST_FILE: {
            GetOpenFileName(file);
            std::ofstream out;
            out.open(name);
            dump_file(out, (*ptr_Field));
            out.close();
            (*ptr_Field)->show_windows(SW_SHOW, *DumpButton, *TickButton, *ReturnButton, *HelpButton, (*ptr_Field)->game_field->window_d);
            (*ptr_Field)->show_windows(SW_HIDE, *ExistButton, *NewButton);
            break; }
        case NEW_FILE: {
            (*ptr_Field)->show_windows(SW_HIDE, *ExistButton, *NewButton);
            *text = new char[100];
            for (int i = 0; i < 100; i++) (*text)[i] = 0;
            flag = 1;
            SendMessage((*ptr_Field)->window_d, WM_CHAR, VK_BACK, 0);
            break; }
    }
}

void display_file_name(int& flag, int& size_out, char** text, GamePlayWindow** ptr_Field, WPARAM wParam, HWND* DumpButton, 
                        HWND* TickButton, HWND* ReturnButton,HWND* HelpButton){
    if (flag == 1) add_new_symbol(size_out, wParam, *text, *ptr_Field);
    if ((TCHAR) wParam == VK_RETURN && flag == 1){ 
        flag = 0;                
        (*text)[size_out] = '\0';
        std::ofstream out;
        out.open(*text);
        dump_file(out, *ptr_Field);
        out.close();
        (*ptr_Field)->show_windows(SW_SHOW, *DumpButton, *TickButton, *ReturnButton, *HelpButton, (*ptr_Field)->game_field->window_d);
        size_out = 0;
        delete [] (*text);
    }
}

void check_cmd_input(GamePlayWindow** ptr_Field){
    if ((*ptr_Field)->cmd_iter_num != "" && (*ptr_Field)->size != -1){
        int iter = std::stoi((*ptr_Field)->cmd_iter_num);
        if (iter >= 0) SendMessage((*ptr_Field)->window_d, WM_COMMAND, OFFLINE_MODE, iter);
        else  MessageBox((*ptr_Field)->window_d, _T("INCORRECT NUMBER OF ITERATIONS!"), _T("ERROR"), MB_OK);
    }
}

void print_lattice(HDC* hdc, PAINTSTRUCT* ps){
    int nCanvasWidth = (*ps).rcPaint.right - (*ps).rcPaint.left;
    int nCanvasHeight = (*ps).rcPaint.bottom - (*ps).rcPaint.top;

    HDC hMemDC = CreateCompatibleDC(*hdc);
    HBITMAP hBitmap = CreateCompatibleBitmap(*hdc, nCanvasWidth, nCanvasHeight);
    SelectObject(hMemDC, hBitmap);

    HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
    FillRect(hMemDC, &(*ps).rcPaint, hBrush);
    DeleteObject(hBrush);

    int nXCount = nCanvasWidth / 10;
    int nYCount = nCanvasHeight / 10;
    for (int i = 1; i <= nYCount; i++){
        MoveToEx(hMemDC, 0, i * 10, NULL);
        LineTo(hMemDC, nCanvasWidth, i * 10);
    }
    for (int i = 1; i <= nXCount; i++){
        MoveToEx(hMemDC, i * 10, 0, NULL);
        LineTo(hMemDC, i * 10, nCanvasHeight);
    }
    BitBlt(*hdc, 0, 0, nCanvasWidth, nCanvasHeight, hMemDC, 0, 0, SRCCOPY);
    DeleteObject(hBitmap);
    DeleteDC(hMemDC);
}

void print_matrix(GameField** ptr_child, HDC* hdc){
    for (int i = 0; i < (*ptr_child)->size_x; i++){
        for (int j = 0; j < (*ptr_child)->size_y; j++){
            if ((*ptr_child)->matrix[i][j] == ALIVE){
                for (int k = i * 10; k < i * 10 + 10; k++){
                    for (int s = j * 10; s < j * 10 + 10; s++) SetPixel(*hdc, k, s, BLACK_BRUSH);
                }
            }
        }
    }
}

void create_alive_unit(GameField** ptr_child, LPARAM lParam){
    int l = LOWORD(lParam);
    int h = HIWORD(lParam);
    if (abs(l/10) < (*ptr_child)->size_x && abs(h/10) < (*ptr_child)->size_y && l != 0 && h != 0){
        if ((*ptr_child)->matrix[(l/10)][(h/10)] == DEAD) {
            (*ptr_child)->matrix[(l/10)][(h/10)] = ALIVE;
            (*ptr_child)->redraw_window((*ptr_child)->window_d, TRUE);
        }
    }
}

#endif