//
// Created by Sebastian Mygind on 15-10-2023.
// This Program was built to fix the RUN_CALCULATOR function of the previous iteration
// The function RUN_CALCULATOR must return the accumulated value (ACCUMULATOR)
#include <stdio.h>
#include <math.h>

void IS_VALID_AND_UNARY(char OPERATOR, int *VALID, int *UNARY);
int SCAN_DATA(char *OPERATOR, double *INPUT, int *IS_VALID, int *IS_UNARY);
double DO_NEXT_OP (char OPERATOR, double ACCUMULATOR, double INPUT, int UNARY);
double RUN_CALCULATOR(char OPERATOR, double ACCUMULATOR, double INPUT, int IS_VALID, int IS_UNARY, int QUIT);


int main(void){
    double ACCUMULATOR = 0.0, INPUT;
    char OPERATOR = '0';
    int QUIT = 0;

    char *pOPERATOR = &OPERATOR;
    double *pINPUT = &INPUT;

    while (QUIT == 0) {
        int IS_VALID = 0;
        int IS_UNARY = 0;

        QUIT = SCAN_DATA(pOPERATOR, pINPUT, &IS_VALID, &IS_UNARY);

        ACCUMULATOR = RUN_CALCULATOR(OPERATOR, ACCUMULATOR, INPUT, IS_VALID, IS_UNARY, QUIT);

    }
    return 0;
}


void IS_VALID_AND_UNARY(char OPERATOR, int *VALID, int *UNARY) {

    if (OPERATOR == '#' || OPERATOR == '%' || OPERATOR == '!') {
        *VALID = 1;
        *UNARY = 1;
    }
    else if (OPERATOR == '+' || OPERATOR == '-' || OPERATOR == '*' || OPERATOR == '/' || OPERATOR == '^') {
        *VALID = 1;
        *UNARY = 0;
    }
}

int SCAN_DATA(char *OPERATOR, double *INPUT, int *IS_VALID, int *IS_UNARY) {

    printf("Hvilken Operator vil du bruge? \n");
    scanf("%s", OPERATOR);
    if (*OPERATOR == 'q') {
        *IS_VALID = 1;
        printf("Programmet lukker!\n");
        return 1;
    }
    else
        IS_VALID_AND_UNARY(*OPERATOR, IS_VALID, IS_UNARY);
    if (*IS_VALID && !(*IS_UNARY)) {
        printf("Indtast input!\n");
        scanf("%lf", INPUT);
    }
    return 0;
}

double DO_NEXT_OP (char OPERATOR, double ACCUMULATOR, double INPUT, int UNARY) {
    if (UNARY) {
        switch (OPERATOR) {
            case '#':
                if (ACCUMULATOR < 0) {
                    printf("Kan ikke tage kvadratroden af et negativt tal!\n");
                    return 0;
                }
                else
                    return sqrt(ACCUMULATOR);
            case '%':
                return (-1 * ACCUMULATOR);
            case '!':
                if (ACCUMULATOR == 0.0) {
                    printf("FEJL: nul division!\n");
                    return ACCUMULATOR;
                }
                else
                    return (1/ACCUMULATOR);
            default:
                printf("Fejl i DO_NEXT!\n");
                return 0;
        }
    }
    else {
        switch (OPERATOR) {
            case '+':
                return (ACCUMULATOR + INPUT);
            case '-':
                return (ACCUMULATOR - INPUT);
            case '*':
                return (ACCUMULATOR * INPUT);
            case '/':
                if (INPUT == 0.0){
                    printf("Fejl: nul division!\n");
                    return ACCUMULATOR;
                }
                else
                    return (ACCUMULATOR / INPUT);
            case '^':
                return (pow(ACCUMULATOR, INPUT));
            default:
                printf("Fejl i DO_NEXT!\n");
                return 0;
        }
    }
}

double RUN_CALCULATOR(char OPERATOR, double ACCUMULATOR, double INPUT, int IS_VALID, int IS_UNARY, int QUIT) {
    double RESULT = 0.0;

    if (QUIT == 0 && IS_VALID) {
        RESULT = DO_NEXT_OP(OPERATOR, ACCUMULATOR, INPUT, IS_UNARY);
        printf("resultatet er: %lf\n", RESULT);
    }
    else if (IS_VALID == 0)
        printf("Ugyldigt input!\n");
    return RESULT;
}