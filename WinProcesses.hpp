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

#endif

#pragma once

namespace Processes{

    LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
    LRESULT CALLBACK WndProc_2(HWND, UINT, WPARAM, LPARAM);
    LRESULT CALLBACK WndProc_3(HWND, UINT, WPARAM, LPARAM);
    LRESULT CALLBACK WndProc_ch(HWND, UINT, WPARAM, LPARAM);
}