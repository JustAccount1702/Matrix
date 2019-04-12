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
TEST_CASE("operator <<", "Matrix_Tests")
{
    Matrix<int> m(2, 2);
    m.fillRandom();
    std::cout << m << std::endl;
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

TEST_CASE("GetMinor", "Matrix_Tests")
{
    Matrix<int> m1(2, 2);
    m1.fillRandom();
    Matrix<int> minor = m1.getMinor(0,0);
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
    Matrix<int> m1(3, 3);
    Matrix<int> m2(3, 4);
    m1.fillRandom();
    m2.fillRandom();

    Matrix<int> m3 = m1.appendRight(m2);

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 7; ++j)
            REQUIRE(m3.getValue(i,j) == ((j < 3)? m1.getValue(i,j) : m2.getValue(i,j - 3)));
}

TEST_CASE("Operator+", "Matrix_Tests")
{
    Matrix<int> m1(2, 2);
    Matrix<int> m2(2, 2);
    m1.fillRandom();
    m2.fillRandom();

    Matrix<int> m3 = m1+m2;

    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            REQUIRE(m3.getValue(i,j) == m1.getValue(i,j) + m2.getValue(i,j));
}

TEST_CASE("Operator*", "Matrix_Tests")
{
    Matrix<int> m1(2, 2);
    Matrix<int> m2(2, 2);
    m1.fillRandom();
    m2.fillRandom();

    Matrix<int> m3 = m1 * m2;

    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            REQUIRE(m3.getValue(i,j) == m1.getValue(i,0)*m2.getValue(0,j) + m1.getValue(i,1)*m2.getValue(1,j));
}

TEST_CASE("Operator^", "Matrix_Tests")
{
    Matrix<int> m1(2, 2);
    m1.fillRandom();

    Matrix<int> m2 = m1^2;
    Matrix<int> m3 = m1^-2;

    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            REQUIRE(m2.getValue(i,j) == (m1*m1).getValue(i,j));

    //for (int i = 0; i < 2; ++i)
       //for (int j = 0; j < 2; ++j)
            //REQUIRE(m3.getValue(i,j) == (m1.inverse()*m1.inverse()).getValue(i,0));

}

TEST_CASE("Operator+=", "Matrix_Tests")
{
    Matrix<int> m1(2, 2);
    Matrix<int> m2(2, 2);
    m1.fillRandom();
    m2.fillRandom();

    Matrix<int> m3 = m1;
    m3 += m2;

    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            REQUIRE(m3.getValue(i,j) == m1.getValue(i,j)+m2.getValue(i,j));
}

TEST_CASE("Operator-=", "Matrix_Tests")
{
    Matrix<int> m1(2, 2);
    Matrix<int> m2(2, 2);
    m1.fillRandom();
    m2.fillRandom();

    Matrix<int> m3 = m1;
    m3 -= m2;

    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            REQUIRE(m3.getValue(i,j) == m1.getValue(i,j)-m2.getValue(i,j));
}
TEST_CASE("Operator*=", "Matrix_Tests")
{
    Matrix<int> m1(2, 2);
    Matrix<int> m2(2, 2);
    m1.fillRandom();
    m2.fillRandom();

    Matrix<int> m3 = m1;
    m3 *= m2;

    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            REQUIRE(m3.getValue(i,j) == m1.getValue(i,0)*m2.getValue(0,j) + m1.getValue(i,1)*m2.getValue(1,j));
}

TEST_CASE("Operator/=", "Matrix_Tests")
{
    Matrix<int> m1(2, 2);
    Matrix<int> m2(2, 2);
    m1.fillRandom();
    m2.fillRandom();

    Matrix<int> m3 = m1;
    m3 /= m2;

    Matrix<int> m4 = m2.inverse();


    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            REQUIRE(m3.getValue(i,j) == m1.getValue(i,0)*m4.getValue(0,j) + m1.getValue(i,1)*m4.getValue(1,j));
}
