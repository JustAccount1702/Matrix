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
TEST_CASE("Fill random", "Matrix_Tests")
{
    Matrix<int> m(2, 2);
    m.fillRandom();
    m.getValue(0,0);
}
TEST_CASE("Clear", "Matrix_Tests")
{
    Matrix<int> m(2, 2);
    m.clear();
    for (int i = 0; i < 4; ++i )
        REQUIRE(m.getValue(i/2,i%2) == 0);
    m.clear(true);
     for (int i = 0; i < 4; ++i )
        REQUIRE(m.getValue(i/2,i%2) == ((i == 0 || i == 3)?1:0));

}

TEST_CASE("Transpose", "Matrix_Tests")
{
    Matrix<int> m1(2, 2);
    m1.fillRandom();
    Matrix<int> m2 = m1.transpose();
    for (int i = 0; i < 4; ++i )
        REQUIRE(m1.getValue(i/2,i%2) == m2.getValue(i%2, i/2));
}

TEST_CASE("Minor", "Matrix_Tests")
{
    Matrix<int> m1(2, 2);
    m1.fillRandom();
    Matrix<int> minor = m1.minor(0,0);
    REQUIRE(minor.getValue(0,0) == m1.getValue(1,1));
}

TEST_CASE("Determinat", "Matrix_Tests")
{
    Matrix<int> m1(2, 2);
    m1.fillRandom();
    int det = m1.getValue(0,0)*m1.getValue(1,1)-m1.getValue(0,1)*m1.getValue(1,0);
    REQUIRE(m1.determinat() == det);
}

TEST_CASE("AppendRight", "Matrix_Tests")
{
    Matrix<int> m1(2, 2);
    Matrix<int> m2(2, 2);
    m1.fillRandom();
    m2.fillRandom();

    Matrix<int> m3 = m1.appendRight(m2);

    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 4; ++j)
            REQUIRE(m3.getValue(i,j) == ((j < 2)? m1.getValue(i,j) : m2.getValue(i,j - 2)));
}