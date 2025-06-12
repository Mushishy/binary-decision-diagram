// BDD Create
char* replaceChar(char* input, char find, char replace){
    // helper function used to replace '\n' at the end of string read from file
    char *current_pos = strchr(input, find);
    while (current_pos) {
        *current_pos = replace; 
        current_pos = strchr(current_pos, find);
    }
    return input;
}
void analyseWord(char* token, char searched, int* positive, int *negative, int *single) {
    // determine if token part of a boolean expression, contains positive, and/or negative form of searched alphabet
    // and find out if it is single eg. "A", "!A" 
    int i = 0;
    while(token[i] != '\0') {
        if(token[i] == searched)
            *positive = 1;
        if (token[i] == '!') {
            i++;
            if(token[i] == searched)
                *negative = 1;
        }
        i++;
    }

    if ((i == 2) && (*negative == 1)) {
        *single = 1;
        return;
    }
    if(i == 1) 
        *single = 1;
    else
        *single = 0;
}
void analyseSentence(char* input, int* contradiction_possibility, int* negation_possibility, int* numOfPlus) {
    // fast untility function to find out the length of a given string, and number of '+'
    // if length is 3 there is a chance for contradiction "!AA"
    // if length is 2 there is a chance for negation !A
    int i = 0;
    while(input[i] != '\0') {
        if (input[i] == '+')
            *numOfPlus += 1;
        if (i == 3)
            *negation_possibility = 0;
        if (i == 4)
            *contradiction_possibility = 0;
        i++;
    }
}
void create(TREE* tree, NODE* current_node, char* input, char* searching, int index) {
    // recursive used to create the tree, it ends if the cur_node->expression is 1 or 0
    if((strcmp(input,"1") == 0) || (strcmp(input,"0") == 0))
        return;

    // helper print for the current level of recursion 
    //printf("\nINPUT %s\nSEARCHING %c", input, searching[index]);
    
    int con = 1, neg = 1, numOfPlus = 0;                    
    analyseSentence(input, &con, &neg, &numOfPlus);         // before string is tokenized the sentence has to be analysed

    char searched = searching[index];                       // searched char is based on the level of depth of recursion 
    int positive = 0, negative = 0, single = 0;
    int was_neg = 0, was_con = 0;

    char left[STRING] = "\0";
    int l_cursor = 0;                               
    char right[STRING] = "\0";
    int r_cursor = 0;
    
    char *token = strtok(input, DELIM);                     // token represents current word

    while(token != NULL) {
        positive = negative = single = 0;
        
        analyseWord(token, searched, &positive, &negative, &single);

        //// helper print, if we want to see how the current word was analysed
        //puts(token);                    //
        //printf("    s %d\n", single);   //
        //printf("    p %d\n", positive); //
        //printf("    n %d\n", negative); //
        ////
        
        if (positive && negative) {
            // if the word contains both positive and negative char, than 1*0 = 0
            // the word is skipped unless the initiall sentence had size of 3
            // then both sides of node are 0
            if (con) {
                strcpy(right, "0");
                strcpy(left, "0");
                break;
            }
            was_con = 1;
        }
        else if (positive) {
            if(single) {
                // once right is 1 it has to remain unchanged
                strcpy(right, "1");
            }
            else {
                // copy all except for searched
                if (strcmp (right, "1") != 0) {
                    int i = 0;
                    while(token[i] != '\0') {
                        if (token[i] != searched) {
                            right[r_cursor] = token[i];
                            r_cursor++;
                        }
                        i++;
                    }
                    // and append '+'
                    right[r_cursor] = '+';
                    r_cursor++;
                }
                //
            }
        }
        else if (negative) {
            was_neg = 1;
            if (neg) {
                // if the sentence is only !searched
                strcpy(right, "0");
                strcpy(left, "1");
                break;
            }
            else if(single) {
                // once left is 1 it has to remain unchanged
                strcpy(left, "1");
            }
            else {
                // copy all except for !searched
                if (strcmp (left, "1") != 0) {
                    int i = 0;
                    while(token[i] != '\0') {
                        if ((token[i] == '!') && (token[i+1] == searched)) {
                            i++;
                            i++;    
                        }
                        else {
                            left[l_cursor] = token[i];
                            l_cursor++;
                            i++;
                        }
                    }
                    // and append '+'
                    left[l_cursor] = '+';
                    l_cursor++;
                    //
                    if (numOfPlus == 0) {
                        strcpy(right, "0");
                    }
                }
            }
        }
        else {
            // if the word does not contain searched or !searched nor their combination, copy it to both
            int i = 0;
            while(token[i] != '\0') {
                if (strcmp (left, "1") != 0) {
                    left[l_cursor] = token[i];
                    l_cursor++;
                }
                if (strcmp (right, "1") != 0) {
                    right[r_cursor] = token[i];
                    r_cursor++;
                }
                i++;
            }
            // and append '+'
            if (strcmp (left, "1") != 0) {
                left[l_cursor] = '+';
                l_cursor++;
            }
            if (strcmp (right, "1") != 0) {
                right[r_cursor] = '+';
                r_cursor++;
            }
            //
        }
        // move to another token
        token = strtok(NULL, DELIM);
    }
    
    // remove last '+'
    if (r_cursor != 0) {
        if (right[r_cursor-1] == '+') {
            right[r_cursor-1] = '\0';
        }
    }
    if (l_cursor != 0) {
        if (left[l_cursor-1] == '+') { 
            left[l_cursor-1] = '\0';
        }
    }
    //
    if(was_neg && strcmp(left, "0") == 0) {
        strcpy(left, "1");
    }
    if (was_neg && (strcmp(right, "\0") == 0)) {    
        // checker for multiple negations !A+!A+!A..
        strcpy(right, "0");
    }
    if (was_con &&(strcmp(right, "\0") == 0) && (strcmp(left, "\0") == 0)) {
        // additional checker for contradiction
        strcpy(right, "0");
        strcpy(left, "0");
    }
    if(strcmp(left, "\0") == 0) {
        // checker if the sentence contained only words with positive A
        strcpy(left, "0");
    }
    
    // OUTPUT
    //printf("\n\n    %d left: %s", index, left);
    //printf("\n\n    %d right: %s", index, right);
    
    
    // before the word is inserted to the right or left
    // the expression is searched in current index of the hashtable based on the depth of recursion
    // if the expression is not present, new node is inserted to the hashtable 
    // expression serves as key, and data is new node, so that it can be easily searched
    // pointers inside current node are set to point to nodes in the hashtable
    
    // RIGHT
    CELL* searchedR = NULL;
    searchedR = searchLinear(tree->table[index+1], right, (int)pow(2, index+1));
    if (searchedR == NULL) {
        // tree size is incremented only if we are inserting into the hashtable
        // if "1" or "0" do no exist yet they are created, and size is incremented
        if (strcmp(right, "0") == 0) {
            if (tree->zero == NULL) {
                tree->zero = createNode("0");
                tree->size++;
            }

            insert(current_node, tree->zero, RIGHT);
            insertLinear(tree->table[index+1], right, tree->zero, (int)pow(2, index+1));
        }
        else if (strcmp(right, "1") == 0) {
            if (tree->one == NULL) {
                tree->one = createNode("1");
                tree->size++;
            }

            insert(current_node, tree->one, RIGHT);
            insertLinear(tree->table[index+1], right, tree->one, (int)pow(2, index+1));
        }
        else {
            NODE* new_nodeR = NULL;
            new_nodeR = createNode(right);
            insertLinear(tree->table[index+1], right, new_nodeR, (int)pow(2, index+1));
            insert(current_node, new_nodeR, RIGHT);
            tree->size++;
        }
        tree->expected_size++;
    }   
    else {
        insert(current_node, (NODE*)searchedR->node, RIGHT);
        tree->expected_size++;
    }
    ///

    // LEFT
    CELL* searchedL = NULL;
    searchedL = searchLinear(tree->table[index+1], left, (int)pow(2, index+1));
    if (searchedL == NULL) {
        // tree size is incremented only if we are inserting into the hashtable
        // if "1" or "0" do no exist yet they are created, and size is incremented
        if (strcmp(left, "0") == 0) {
            if (tree->zero == NULL) {
                tree->zero = createNode("0");
                tree->size++;
            }

            insert(current_node, tree->zero, LEFT);
            insertLinear(tree->table[index+1], left, tree->zero, (int)pow(2, index+1));
        }
        else if (strcmp(left, "1") == 0) {
            if (tree->one == NULL) {
                tree->one = createNode("1");
                tree->size++;
            }

            insert(current_node, tree->one, LEFT);
            insertLinear(tree->table[index+1], left, tree->one, (int)pow(2, index+1));
        }
        else {
            NODE* new_nodeL = NULL;
            new_nodeL = createNode(left);
            insertLinear(tree->table[index+1], left, new_nodeL, (int)pow(2, index+1));
            insert(current_node, new_nodeL, LEFT);
            tree->size++;
        }
        tree->expected_size++;
    }   
    else {
        insert(current_node,(NODE*) searchedL->node, LEFT);
        tree->expected_size++;
    }
    ///


    //printf("\ntable %d\n", (int)pow(2,index+1));
    //printLinear(tree->table[index+1], (int)pow(2,index+1));
    
    // the recusion index is incremented
    index++;
    if(searching[index] == '\0') 
        // until the end of order string
        return;
    else {
        create(tree, current_node->pointer[RIGHT], right, searching, index);
        create(tree, current_node->pointer[LEFT], left, searching, index);
    }
}

// Main BDD
char bddUse(TREE* tree, char* order) {
    // if there exist only ones or zeroes, return going through the tree is not needed
    // else go through the tree based on order until 1 or 0 is encountered 
    // 1 represents to the right
    // 0 represents to the left
    if (tree->one != NULL && tree->zero != NULL) {
        int i = 0;
        NODE* cur_node = tree->root;
        char directions[STRING] = "\0";
        strcpy(directions, order);

        while(directions[i] != '\0') {
            //printf("%d %s --- o %c\n", i, cur_node->expression, directions[i]);
            if(directions[i] == '1')
                cur_node = cur_node->pointer[RIGHT];
            else if (directions[i] == '0')
                cur_node = cur_node->pointer[LEFT];
            
            if (strcmp(cur_node->expression, "1") == 0)
                    return '1';
            if (strcmp(cur_node->expression, "0") == 0)
                    return '0';
            i++;
        }
    
        return '-';
    }
    else if (tree->one != NULL && tree->zero == NULL) {
        return '1';
    }
    else if (tree->one == NULL && tree->zero != NULL) {
        return '0';
    }
}
TREE* bddCreate(char* input, char *searching) {
    // function returns pointer to newTree based on expression string
    char tokenize[STRING];
    strcpy(tokenize, input);

    TREE* tree = NULL;
    int order_size = (int)strlen(searching);
    tree = createTree(input, order_size);
    create(tree, tree->root, tokenize, searching, 0);
    return tree;
}