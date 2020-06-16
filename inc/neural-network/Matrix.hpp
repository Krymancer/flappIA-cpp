#pragma once
#include <stdlib.h>

#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>
#include <random>

typedef double (*functioncall)(double args);

using std::tuple;
using std::vector;

class Matrix {
   private:
    unsigned rows;
    unsigned cols;
    vector<vector<double> > data;

   public:
    Matrix(unsigned, unsigned, double);
    Matrix(const char *);
    Matrix(const Matrix &);
    Matrix(vector<double>);
    Matrix();

    // Matrix Operations
    Matrix operator+(Matrix &);
    Matrix operator-(Matrix &);
    Matrix operator*(Matrix &);
    Matrix transpose();

    // Scalar Operations
    Matrix operator+(double);
    Matrix operator-(double);
    Matrix operator*(double);
    Matrix operator/(double);

    // Aesthetic Methods
    double &operator()(const unsigned &, const unsigned &);
    void print() const;
    unsigned getRows() const;
    unsigned getCols() const;
    vector<double> toArray();

    // Power Iteration
    tuple<Matrix, double, int> powerIter(unsigned, double);

    // Deflation
    Matrix deflation(Matrix &, double &);

    //Randomize
    void randomize();

    //Activation Function
    Matrix sigmod();
    Matrix dSigmod();

    // Map
    Matrix map(functioncall);
};