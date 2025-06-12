#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#define SINGLE 1
#define LEFT 0
#define RIGHT 1
#define STRING 100
#define DELIM "+"

#define CLOCK  clock_t start_t, end_t
#define BEG start_t = clock()
#define END   end_t = clock()

#define PRINT_COLUMN(x,y) for(int i = 0; i < depth; i++) {printf("      ");}

#define EXPRESSION "expressions.txt"
#define VECTOR "vector.txt"

#define TEST_A "./tests/input/13_expression.txt"
#define TEST_B "./tests/input/15_expression.txt"
#define TEST_C "./tests/input/20_expression.txt"

#define VECTOR_A "./tests/input/13_vector.txt.txt"
#define VECTOR_B "./tests/input/15_vector.txt.txt"
#define VECTOR_C "./tests/input/20_vector.txt.txt"

#include "./functions/structs.c"
#include "./functions/linear.c"
#include "./functions/bddTree.c"
#include "./functions/bddFunctions.c"

#include "./tests/check.c"
#include "./tests/test.c"
#include "./tests/demo.c"

int main() {
    // there is no expression correctness checker
    // so expression has to contain all variables mentioned in order
    // and the individual parts divided by + have to be in alphabetical order
    // !, + cannot be placed at the end, and + cannot be at the start
    // for the algorithm to function properly

    printf("\n\tInitialising demos>>");
    demoTree("A!C+ABC+!AB+!BC", "ABC", "100");
    demoTree("AC+AB!B", "CAB", "101");
   
    printf("\n\n\tInitialising tests>>");
    bddTest(1); // 13, 5000
    bddTest(2); // 15, 5000
    bddTest(3); // 20, 5000
    
    puts("\n\nPress <ANY KEY> to exit");
    getchar();

    return 0;
}