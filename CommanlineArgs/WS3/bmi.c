#include <stdio.h>
#include <stdlib.h>

//write a program that accepts two numbers at command line and displays the addition
//of these numbers

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("You need to enter 2 numbers-+");
        return 1;
    }

    float num1 = atof(argv[1]);
    float num2 = atof(argv[2]);

    float bmi = num1 / (num2 * num2);
    printf("BMI: %.2f\n", bmi);

    if (bmi > 30)
    {
        /* code */
        printf("Obese\n");
        return 0;
    } else if (bmi > 25){
        printf("Overweight\n");
        return 0;
    } else if (bmi > 18.5f){
        printf("Normal\n");
        return 0;
    } else {
        printf("Underweight\n");
        return 0;
    }
    
}