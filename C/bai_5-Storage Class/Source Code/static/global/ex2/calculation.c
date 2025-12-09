#include "calculation.h"
// Nhập hệ số
void input_coefficients(double* a,double* b,double* c){
    printf("nhập các hệ số a ,b , c: ");
    scanf("%lf %lf %lf",a,b,c);
}

// Tính delta
double calculate_delta(double a, double b, double c){
    return pow(b,2) - 4*a*c;
}

// Giải phương trình
Type solve(double a,double b,double c,double delta,double* x1,double* x2){
    if(delta > 0){
        *x1 = (-b + sqrt(delta)) / (2 * a);
        *x2 = (-b - sqrt(delta)) / (2 * a);
        return HAI_NGHIEM;
    }
    else if(delta == 0){
        *x1 = *x2 = (double)(-b) / (2 * a);
        return NGHIEM_KEP;
    }
    else {
        *x1 = *x2 = NAN;
    }
}

// Hiển thị kết quả
void display_result(double a,double b,double c,double delta){
    double x1 = 0 , x2 = 0;
    Type type = solve(a,b,c,delta,&x1,&x2);
    switch (type)
    {
    case VO_NGHIEM:
        printf("phương trình vô nghiệm\n");
        break;
    case HAI_NGHIEM:
        PRINTF("Phương trình có 2 nghiệm phân biẹt\n");
        printf("x1 = %f\nx2 = %f\n",x1,x2);
    case NGHIEM_KEP:
        printf("Phương trình có nghiệm kép\n");
        printf("x1 = x2 = %f",x1);
    default:
        break;
    }
}