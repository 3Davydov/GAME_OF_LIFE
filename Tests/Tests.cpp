#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include "../SupportiveFunctions.hpp"
#include "../WinClasses.hpp"
#include "../SuppClasses.hpp"

class TestInput : public ::testing::TestWithParam<std::tuple<std::string, std::string>> {};
class TestOutput_1 : public ::testing::TestWithParam<std::string> {};
class TestInput_2 : public ::testing::TestWithParam<std::string> {};

using namespace Classes;
using namespace Supportive;
using namespace SuppClasses;


TEST_P(TestInput, testing_correct_input){
    const int alive = 1;
    GamePlayWindow wnd;
    GameField* child = new GameField;
    FileReader* file_reader = new FileReader;
    wnd.set_game_field_pointer(child);
    std::string input = std::get<0>(GetParam());
    std::string output = std::get<1>(GetParam());
    char* filename = new char [input.length() + 1];
    unsigned int len = input.length();
    for (unsigned int i = 0; i < len; i++) filename[i] = input[i];
    filename[input.length()] = '\0';

    wnd.set_file_name(filename);
    file_reader->set_filename(filename);
    file_reader->read_buffer(wnd.get_game_field_pointer());

    EXPECT_TRUE(file_reader->get_buff_size() == 52);

    EXPECT_TRUE(file_reader->get_univerce_name() == "My univerce");
    EXPECT_TRUE(file_reader->get_birth().size() == 1);
    EXPECT_TRUE(file_reader->get_survive().size() == 2);
    EXPECT_TRUE(file_reader->get_birth()[0] == '3');
    EXPECT_TRUE(file_reader->get_survive()[0] == '2' && file_reader->get_survive()[1] == '3');
    EXPECT_TRUE(file_reader->get_size_x() == 130 && file_reader->get_size_y() == 72);
    int res = child->read_matrix(file_reader->get_current_index(), file_reader->get_buffer(), file_reader->get_buff_size(), file_reader->get_size_x(), 
                                 file_reader->get_size_y(), file_reader->get_birth(), file_reader->get_survive());
    child->get_univerce_name(file_reader->get_univerce_name());
    for (int i = 10; i < 13; i++){
        EXPECT_TRUE(child->get_matrix_elem(child->get_size_x() / 2 + 10, child->get_size_y() / 2 - 10) == alive);
    }
    
    child->change_condition();
    for (int i = 9; i < 12; i++){
        EXPECT_TRUE(child->get_matrix_elem(child->get_size_x() / 2 + 11, child->get_size_y() / 2 - i) == alive);
    }
    std::ofstream out;
    out.open(output);
    child->dump_file(out);

    delete child;
}

INSTANTIATE_TEST_CASE_P(testing_constructors, TestInput, ::testing::Values (
                                                                            std::make_tuple("..\\..\\..\\Tests\\InputForTestGame\\CorrectInput_1.txt",
                                                                                            "..\\..\\..\\Tests\\InputForTestGame\\ExpectingOutput.txt")
                                                                            ));

TEST_P(TestOutput_1, testing_output){
    const int alive = 1;
    FileReader* file_reader = new FileReader;
    GamePlayWindow wnd;
    GameField* child = new GameField;
    wnd.set_game_field_pointer(child);
    std::string input = GetParam();
   char* filename = new char [input.length() + 1];
    unsigned int len = input.length();
    for (unsigned int i = 0; i < len; i++) filename[i] = input[i];
    filename[input.length()] = '\0';
    wnd.set_file_name(filename);
    file_reader->set_filename(filename);
    file_reader->read_buffer(wnd.get_game_field_pointer());

    EXPECT_TRUE(file_reader->get_buff_size() == 51);

    EXPECT_TRUE(file_reader->get_univerce_name() == "My univerce");
    EXPECT_TRUE(file_reader->get_birth().size() == 1);
    EXPECT_TRUE(file_reader->get_survive().size() == 2);
    EXPECT_TRUE(file_reader->get_birth()[0] == '3');
    EXPECT_TRUE(file_reader->get_survive()[0] == '2' && file_reader->get_survive()[1] == '3');
    EXPECT_TRUE(file_reader->get_size_x() == 130 && file_reader->get_size_y() == 72);

    int res = child->read_matrix(file_reader->get_current_index(), file_reader->get_buffer(), file_reader->get_buff_size(), file_reader->get_size_x(), 
                                 file_reader->get_size_y(), file_reader->get_birth(), file_reader->get_survive());
    child->get_univerce_name(file_reader->get_univerce_name());

    for (int i = 9; i < 12; i++){
        EXPECT_TRUE(child->get_matrix_elem(child->get_size_x() / 2 + 11, child->get_size_y() / 2 - i) == alive);
    }
    child->change_condition();
    for (int i = 10; i < 13; i++){
        EXPECT_TRUE(child->get_matrix_elem(child->get_size_x() / 2 + 10, child->get_size_y() / 2 - 10) == alive);
    }

    delete child;
}

INSTANTIATE_TEST_CASE_P(testing_constructors, TestOutput_1, ::testing::Values ("..\\..\\..\\Tests\\InputForTestGame\\ExpectingOutput.txt"));

TEST_P(TestInput_2, testing_output){
    const int wrong_format = 2;
    const int wrong_size = 3;
    const int wrong_coordinate = 4;
    const int not_a_digit = 5;
    FileReader* file_reader = new FileReader;
    GamePlayWindow wnd;
    GameField* child = new GameField;
    wnd.set_game_field_pointer(child);
    std::string input = GetParam();
   char* filename = new char [input.length() + 1];
    unsigned int len = input.length();
    for (unsigned int i = 0; i < len; i++) filename[i] = input[i];
    filename[input.length()] = '\0';
    wnd.set_file_name(filename);
    file_reader->set_filename(filename);
    int res = file_reader->read_buffer(wnd.get_game_field_pointer());

    int res_1 = child->read_matrix(file_reader->get_current_index(), file_reader->get_buffer(), file_reader->get_buff_size(), file_reader->get_size_x(), 
                                 file_reader->get_size_y(), file_reader->get_birth(), file_reader->get_survive());
    child->get_univerce_name(file_reader->get_univerce_name());

    if (input == "..\\..\\..\\Tests\\InputForTestGame\\IncorrectInput_1.txt") EXPECT_TRUE(res == wrong_format);
    if (input == "..\\..\\..\\Tests\\InputForTestGame\\IncorrectInput_2.txt") EXPECT_TRUE(res == wrong_size);
    if (input == "..\\..\\..\\Tests\\InputForTestGame\\IncorrectInput_3.txt") EXPECT_TRUE(res_1 == not_a_digit);
    if (input == "..\\..\\..\\Tests\\InputForTestGame\\IncorrectInput_4.txt") EXPECT_TRUE(res_1 == wrong_coordinate);    
}

INSTANTIATE_TEST_CASE_P(testing_constructors, TestInput_2, ::testing::Values ("..\\..\\..\\Tests\\InputForTestGame\\IncorrectInput_1.txt", 
                                                                              "..\\..\\..\\Tests\\InputForTestGame\\IncorrectInput_2.txt",
                                                                              "..\\..\\..\\Tests\\InputForTestGame\\IncorrectInput_3.txt",
                                                                              "..\\..\\..\\Tests\\InputForTestGame\\IncorrectInput_4.txt"
                                                                               ));
