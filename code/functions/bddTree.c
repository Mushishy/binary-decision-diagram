NODE* createNode(char* new_expression) {
    // return pointer to a new node initialised to a given value
    NODE* new_node = NULL;
    new_node = (NODE*)calloc(SINGLE, sizeof(NODE));
    
    if(new_node != NULL) {
        new_node->pointer[LEFT] = new_node->pointer[RIGHT] = NULL;
        strcpy(new_node->expression, new_expression);
    }
    // if calloc was not successfull exit
    else 
        exit(-1);

    return new_node;
}
TREE* createTree(char* input, int order_size) {
    // return pointer to tree initialised with root set to the input expression, size 1, and start two-dimensional array of cells
    // hashtable is always set to size 2^1 for each level of tree
    
    TREE* new_tree = NULL;
    new_tree = (TREE*)calloc(SINGLE, sizeof(TREE));
    if (new_tree != NULL) {
        new_tree->root = createNode(input);
        
        new_tree->zero = NULL;
        new_tree->one = NULL;
        
        new_tree->size = 1;
        new_tree->expected_size = 1;

        new_tree->levels = order_size;
        
        /// 
        new_tree->table = NULL;
        new_tree->table =  calloc(order_size+1, sizeof(CELL**));
        if (new_tree->table != NULL) {
            for(int i = 0; i <= order_size; i++) {
                (new_tree->table)[i] = initLinear((int)pow(2,i));
            }
        }
        else
            exit(-1);
        ///

    }
    else 
        exit(-1);

    return new_tree;
}
void insert(NODE* node, NODE* new_node, int right) {
    // new_node is inserted to node either right or left
    if (right)
        node->pointer[RIGHT] = new_node;
    else
        node->pointer[LEFT] = new_node;
}
void output(NODE* current_node, int depth) {
    // recursive function for printing the tree into console
    PRINT_COLUMN(0, depth);
    printf("%s\n", current_node->expression);

    if(current_node->pointer[LEFT] != NULL) {
        PRINT_COLUMN(0, depth);
        puts("left");
        output((NODE* ) current_node->pointer[LEFT], depth + 1);
    }

    if(current_node->pointer[RIGHT] != NULL) {
        PRINT_COLUMN(0, depth)
        puts("right");
        output((NODE* ) current_node->pointer[RIGHT], depth + 1);
    }

    PRINT_COLUMN(0, depth)
    puts("end");
}
void printTree(TREE* tree) {
    // call output, and print size of tree, as well as expected size of tree
    if(tree != NULL) {
        output(tree->root, 0);
        int sum = 1;
        for (int i = 1; i <= tree->levels; i++) {
            printf("\n table[%d]\n", i);
            printLinear(tree->table[i], pow(2,i));
            sum += pow(2,i);
        }
              
        printf("\nActual Number of Nodes                         %d\nNumber of Nodes without Hashtable Reduction    %d\nNumber of Nodes without Reduction              %d\n", tree->size, tree->expected_size, sum);
    }
    else 
        puts("Tree does not exist.");
}
void freeTree(TREE** tree) {
    // free tree, tables, and nodes
    // nodes are freed inside of tables
    for(int i = 0; i <= (*tree)->levels; i++) {
        if ((*tree)->table[i] != NULL) {
            freeLinear((*tree)->table[i], (int)pow(2,i));
        }
    }
    if ((*tree)->table != NULL) {
        free((*tree)->table);
    }
    if ((*tree)->root != NULL) {
        free((*tree)->root);
    }
    if ((*tree)->zero != NULL) {
        free((*tree)->zero);
    }
    if ((*tree)->one != NULL) {
        free((*tree)->one);
    }
    free(*tree);
    *tree = NULL;
}