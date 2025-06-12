void bddTest(int test) {
    CLOCK;
    double createTime = 0, useTime = 0, actual_size = 0, expected_size = 0, sum = 0, vectors = 0;
    
    TREE* tree = NULL;
    
    int variables = 0, size = 5000;
    FILE* f_expression = NULL;
    FILE* f_vector = NULL;
    char order[STRING];
    char use = 'x';
    char* buffer = NULL;
    
    switch(test) {
        case 1:
            f_expression = fopen(TEST_A, "r");
            f_vector = fopen(VECTOR_A, "r");
            vectors = 8192;
            variables = 13;
            break;
        case 2:
            f_expression = fopen(TEST_B, "r");
            f_vector = fopen(VECTOR_B, "r");
            vectors = 32768;
            variables = 15;
            break;
        case 3:
            f_expression = fopen(TEST_C, "r");
            f_vector = fopen(VECTOR_C, "r");
            vectors = 1048576;
            variables = 20;
            break;
        default:
            return;
    }
    printf("\n\n%d Variables Test on %d random boolean expressions\n\n", variables, size);
    buffer = (char*)calloc(STRING, sizeof(char));
    
    int iter = 0;
    for (iter = 0; iter < (variables+1); iter++) {
        order[iter] = 'A' + iter;
    }
    order[variables+1] = '\0';
    
    for (int i = 0; i < size; i++) {
        fgets(buffer, STRING, f_expression);
        buffer = replaceChar(buffer, '\n', '\0');
        
        BEG;
        tree = bddCreate(buffer, order);
        END;
        createTime += (double)(-start_t + end_t)/ CLOCKS_PER_SEC;
        expected_size += tree->expected_size;
        actual_size += tree->size;

        BEG;
        while (fgets(buffer, STRING, f_vector)) {
            use = bddUse(tree, buffer);
            if (use != check(tree->root->expression, order, buffer))
                printf("%s %s", tree->root->expression, buffer);
        }
        END;

        useTime += (double)(-start_t + end_t)/ CLOCKS_PER_SEC;
        rewind(f_vector);

        freeTree(&tree);
    }
    
    for (int i = 0; i <= variables; i++) {
        sum += (double)pow(2,i);
    }

    printf("\tActual Number of Nodes                       %g\n\tNumber of Nodes without Hashtable Reduction  %g\n\tNumber of Nodes without Reduction            %g\n\tReduction Rate                               %g%%\n\tTotal bddCreate Time                         %g\n\tTotal bddUse Time                            %g", actual_size, expected_size, sum*vectors*(double)size, 100 - (actual_size / expected_size) * 100, createTime, useTime);
    fclose(f_expression);
    fclose(f_vector);
    free(buffer);
}