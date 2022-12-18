#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include "../SupportiveFunctions.hpp"
#include "../WinClasses.hpp"
/*
class TestInput : public ::testing::TestWithParam<std::tuple<std::string, std::string>> {};
class TestOutput_1 : public ::testing::TestWithParam<std::string> {};
class TestInput_2 : public ::testing::TestWithParam<std::string> {};

using namespace Classes;
using namespace Supportive;
TEST_P(TestInput, testing_correct_input){
    const int alive = 1;
    GamePlayWindow wnd;
    GameField* child = new GameField;
    wnd.game_field = child;
    std::string input = std::get<0>(GetParam());
    std::string output = std::get<1>(GetParam());
    wnd.file_name = new char [input.length() + 1];
    unsigned int len = input.length();
    for (unsigned int i = 0; i < len; i++) wnd.file_name[i] = input[i];
    wnd.file_name[input.length()] = '\0';
    wnd.size = get_buffer_size(wnd.file_name);

    EXPECT_TRUE(wnd.size == 52);

    char* buffer = new char [wnd.size];
    fill_buffer(&wnd, wnd.size, buffer);
    int res = wnd.read_buffer(buffer, wnd.size);

    EXPECT_TRUE(wnd.univerce_name == "My univerce");
    EXPECT_TRUE(wnd.birth_needed.size() == 1);
    EXPECT_TRUE(wnd.survival_needed.size() == 2);
    EXPECT_TRUE(wnd.birth_needed[0] == '3');
    EXPECT_TRUE(wnd.survival_needed[0] == '2' && wnd.survival_needed[1] == '3');
    EXPECT_TRUE(wnd.size_x == 130 && wnd.size_y == 72);
    for (int i = 10; i < 13; i++){
        EXPECT_TRUE(child->matrix[child->size_x / 2 + 10][child->size_y / 2 - 10] == alive);
    }
    child->change_condition();
    for (int i = 9; i < 12; i++){
        EXPECT_TRUE(child->matrix[child->size_x / 2 + 11][child->size_y / 2 - i] == alive);
    }
    std::ofstream out;
    out.open(output);
    dump_file(out, &wnd);


    delete [] buffer;
    delete child;
}

INSTANTIATE_TEST_CASE_P(testing_constructors, TestInput, ::testing::Values (
                                                                            std::make_tuple("C:\\Users\\davyd\\Desktop\\InputForTestGame\\CorrectInput_1.txt",
                                                                                            "C:\\Users\\davyd\\Desktop\\InputForTestGame\\ExpectingOutput.txt")
                                                                            ));

TEST_P(TestOutput_1, testing_output){
    const int alive = 1;
    GamePlayWindow wnd;
    GameField* child = new GameField;
    wnd.game_field = child;
    std::string input = GetParam();
    wnd.file_name = new char [input.length() + 1];
    unsigned int len = input.length();
    for (unsigned int i = 0; i < len; i++) wnd.file_name[i] = input[i];
    wnd.file_name[input.length()] = '\0';
    wnd.size = get_buffer_size(wnd.file_name);

    EXPECT_TRUE(wnd.size == 51);

    char* buffer = new char [wnd.size];
    fill_buffer(&wnd, wnd.size, buffer);
    int res = wnd.read_buffer(buffer, wnd.size);

    EXPECT_TRUE(wnd.univerce_name == "My univerce");
    EXPECT_TRUE(wnd.birth_needed.size() == 1);
    EXPECT_TRUE(wnd.survival_needed.size() == 2);
    EXPECT_TRUE(wnd.birth_needed[0] == '3');
    EXPECT_TRUE(wnd.survival_needed[0] == '2' && wnd.survival_needed[1] == '3');
    EXPECT_TRUE(wnd.size_x == 130 && wnd.size_y == 72);
    for (int i = 9; i < 12; i++){
        EXPECT_TRUE(child->matrix[child->size_x / 2 + 11][child->size_y / 2 - i] == alive);
    }
    child->change_condition();
    for (int i = 10; i < 13; i++){
        EXPECT_TRUE(child->matrix[child->size_x / 2 + 10][child->size_y / 2 - 10] == alive);
    }
    delete [] buffer;
    delete child;
}

INSTANTIATE_TEST_CASE_P(testing_constructors, TestOutput_1, ::testing::Values ("C:\\Users\\davyd\\Desktop\\InputForTestGame\\ExpectingOutput.txt"));

TEST_P(TestInput_2, testing_output){
    const int wrong_format = 2;
    const int wrong_size = 3;
    const int wrong_coordinate = 4;
    const int not_a_digit = 5;
    GamePlayWindow wnd;
    GameField* child = new GameField;
    wnd.game_field = child;
    std::string input = GetParam();
    wnd.file_name = new char [input.length() + 1];
    unsigned int len = input.length();
    for (unsigned int i = 0; i < len; i++) wnd.file_name[i] = input[i];
    wnd.file_name[input.length()] = '\0';
    wnd.size = get_buffer_size(wnd.file_name);

    char* buffer = new char [wnd.size];
    fill_buffer(&wnd, wnd.size, buffer);
    int res = wnd.read_buffer(buffer, wnd.size);
    if (input == "C:\\Users\\davyd\\Desktop\\InputForTestGame\\IncorrectInput_1.txt") EXPECT_TRUE(res == wrong_format);
    if (input == "C:\\Users\\davyd\\Desktop\\InputForTestGame\\IncorrectInput_2.txt") EXPECT_TRUE(res == wrong_size);
    if (input == "C:\\Users\\davyd\\Desktop\\InputForTestGame\\IncorrectInput_3.txt") EXPECT_TRUE(res == not_a_digit);
    if (input == "C:\\Users\\davyd\\Desktop\\InputForTestGame\\IncorrectInput_4.txt") EXPECT_TRUE(res == wrong_coordinate);    
    delete [] buffer;
}

INSTANTIATE_TEST_CASE_P(testing_constructors, TestInput_2, ::testing::Values ("C:\\Users\\davyd\\Desktop\\InputForTestGame\\IncorrectInput_1.txt", 
                                                                              "C:\\Users\\davyd\\Desktop\\InputForTestGame\\IncorrectInput_2.txt",
                                                                              "C:\\Users\\davyd\\Desktop\\InputForTestGame\\IncorrectInput_3.txt",
                                                                              "C:\\Users\\davyd\\Desktop\\InputForTestGame\\IncorrectInput_4.txt"
                                                                               ));
*/