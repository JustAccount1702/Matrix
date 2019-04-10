//
// Created by maxk on 07.04.19.
//
#include "iostream"
#include "matrix.hpp"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Get/Set Value", "Matrix_Tests")
{
    Matrix<int> m(2, 2);
    m.setValue(0,0,1);
    m.setValue(0,1,2);
    m.setValue(1,0,3);
    m.setValue(1,1,4);
    REQUIRE(m.getValue(0,0) == 1);
    REQUIRE(m.getValue(0,1) == 2);
    REQUIRE(m.getValue(1,0) == 3);
    REQUIRE(m.getValue(1,1) == 4);
}
TEST_CASE("Get/Set Value", "Matrix_Tests")
{
    Matrix<int> m(2, 2);
    m.setValue(0,0,1);
    m.setValue(0,1,2);
    m.setValue(1,0,3);
    m.setValue(1,1,4);
    REQUIRE(m.getValue(0,0) == 1);
    REQUIRE(m.getValue(0,1) == 2);
    REQUIRE(m.getValue(1,0) == 3);
    REQUIRE(m.getValue(1,1) == 4);
}
