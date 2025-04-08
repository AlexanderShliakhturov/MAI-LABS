#include <gtest/gtest.h>
#include <utility>

#include "main_func.h"
#include "functions.h"
#include "DynamicArray.h"
#include "Octal.h"
#include "main_func.h"



TEST(diff_t_s, diff_throw_dights)
{

    std::string first = "7467";
    std::string second = "756";
    char operand = '-';

    Octal result = main_func(first, operand, second);

    ASSERT_TRUE(result.to_string() == Octal("6511").to_string());
}

TEST(diff_t_s, equa_minus_equal)
{
    
    std::string first = "7777";
    std::string second = "7777";
    char operand = '-';
    
    Octal result = main_func(first, operand, second);
   
    ASSERT_TRUE(result.to_string() == Octal("0000").to_string());
}

TEST(diff_t_s, zero_minus_zero)
{
    
    std::string first = "0";
    std::string second = "0";
    char operand = '-';
    
    Octal result = main_func(first, operand, second);
    
    ASSERT_TRUE(result.to_string() == Octal("0").to_string());
}

TEST(plus_t_s, zero_plus_zero)
{
    
    std::string first = "0";
    std::string second = "0";
    char operand = '+';
    
    Octal result = main_func(first, operand, second);
    
    ASSERT_TRUE(result.to_string() == Octal("0").to_string());
}

TEST(plus_t_s, sum_throw_dight)
{
   
    std::string first = "7777";
    std::string second = "77";
    char operand = '+';
   
    Octal result = main_func(first, operand, second);
    
    ASSERT_TRUE(result.to_string() == Octal("10076").to_string());
}

TEST(plus_t_s, easy_sum)
{
    
    std::string first = "123";
    std::string second = "123";
    char operand = '+';
    
    Octal result = main_func(first, operand, second);
    
    ASSERT_TRUE(result.to_string() == Octal("246").to_string());
}

TEST(more_t_s, more_more_than_less)
{
    
    std::string first = "777";
    std::string second = "7";
    char operand = '>';
    
    std::string result = Octal(first).more_than(Octal(second));
    
    ASSERT_TRUE(result == "TRUE");
}

TEST(more_t_s, more_less_than_less)
{
    
    std::string first = "777";
    std::string second = "7";
    char operand = '<';
    
    std::string result = Octal(first).less_than(Octal(second));
   
    ASSERT_TRUE(result == "FALSE");
}

TEST(eq_t_s, zer0_equal_zero)
{
    
    std::string first = "0";
    std::string second = "0";
    char operand = '=';
    
    std::string result = Octal(first).equal(Octal(second));
    
    ASSERT_TRUE(result == "TRUE");
}

TEST(more_t_s, zero_more_than_zero)
{
    
    std::string first = "0";
    std::string second = "0";
    char operand = '>';
    
    std::string result = Octal(first).more_than(Octal(second));
   
    ASSERT_TRUE(result == "FALSE");
}

TEST(less_t_s, zero_less_than_zero)
{
    
    std::string first = "0";
    std::string second = "0";
    char operand = '<';
   
    std::string result = Octal(first).less_than(Octal(second));
  
    ASSERT_TRUE(result == "FALSE");
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}