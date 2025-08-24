#ifndef CALCULATION_H
#define CALCULATION_H

#include <stdio.h>
#include <math.h>
#include <stdbool.h>

typedef struct
{
    double a,b,c;
    double x1;
    double x2;
    bool has_result;    // 1: có nghiệm, 0: vô nghiệm
} Equation;

// Nhập hệ số
void input_coefficients(Equation *eq);

// Tính delta
static double calculate_delta(double a, double b, double c);

// Giải phương trình
static void solve(Equation *eq);

// Hiển thị kết quả
void display_result(Equation eq);

#endif

