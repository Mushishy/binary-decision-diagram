void demoTree(char* expression, char* order, char* vector) {
    TREE* tree = NULL;
    tree = bddCreate(expression, order);

    printf("\n\nDemo Tree Order ~ %s\n", order);
    printTree(tree);
    
    char use = bddUse(tree,vector);
    if (use == check(tree->root->expression,order, vector))
        printf("\nOutput for bddUse(%s)                         %c", vector, use);
    else {
        printf("\nOutput for bddUse(%s)                         -", vector);
    }
    freeTree(&tree);
}

