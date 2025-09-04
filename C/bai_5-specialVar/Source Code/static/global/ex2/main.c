#include "stdio.h"
#include "calculation.h"
int main(){
    double a,b,c,delta;
    double x1,x2;
    while(1){
        input_coefficients(&a,&b,&c);

        delta = calculate_delta(a,b,c);
        
        Type result = solve(a,b,c,delta,&x1,&x2);

        display_result(a,b,c,delta);
    }
}