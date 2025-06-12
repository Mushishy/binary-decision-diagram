int hashFunction(char* key, int table_size)  {
    // this function takes key string, and converts its characters to numbers one by one
    // to prevent collision of the same strings, but with different positions the number is multiplied by (index+1) 
    // sum % table_size is the wanted cell position 
    int hash = 0;
    
    int i = 0;
    while(key[i] != '\0') {
        hash += (int)key[i] * (i+1);
        i++;
    }
    return (hash % table_size);
}
CELL* newcellLinear(char* new_key, NODE* new_node) {
    //return pointer to new cell initialised to a given key, and data
    CELL* new_cell = NULL;
    new_cell = calloc(SINGLE, sizeof(CELL));
    if (new_cell != NULL) {
        strcpy(new_cell->key, new_key);
        new_cell->node = new_node;
        return new_cell;
    }
    else
        // if calloc was not successfull exit
        exit(-1);
}
CELL** initLinear(int table_size) {
    // return pointer to new table with array of cells initialised inside of it
    CELL** table = NULL;
        
    table =  calloc(table_size, sizeof(CELL*));
    if (table != NULL) {
        for(int i = 0; i < table_size; i++) {
            (table)[i] = NULL;
        }
    }
    else
        // if calloc was not successfull exit
        exit(-1);

    return table;
}
void freeLinear(CELL** table, int table_size) {
    // free the whole table, and nodes inside of it
    if(table == NULL)
        return;
    
    for(int i = 0; i < table_size; i++) {
        if (table[i] != NULL) { 
            if ((table)[i]->node != NULL && strcmp((table)[i]->node->expression, "1") != 0 && strcmp((table)[i]->node->expression, "0") != 0 ){
                free((table)[i]->node);
            }
            free(table[i]);
        }
    }
    free(table);
}
void printLinear(CELL** table, int table_size) { 
    // print the table
    if(table == NULL)
        return;

    for(int i = 0; i < table_size; i++) {
        if (table[i] == NULL)
            printf("%d | NULL\n", i);
        else
            printf("%d | contains = %s\n", i, table[i]->key);
    }
}
void insertLinear(CELL** table, char* key, NODE* node, int table_size) {
    // create new cell, and go over the table to find an empty place in the table
    // starting with an index given by hashfunction
    // tree size is incremented
    if(table == NULL)
        return;

    CELL* new_cell = newcellLinear(key, node);
    int hash = hashFunction(key, table_size);
    
    for (int j = hash; j < table_size; j++) {
        if (table[j] == NULL) {
            table[j] = new_cell;
            return;
        }
        else if (strcmp(table[j]->key, key) == 0){
            printf("Node with [%s] key is already present\n", key);
            free(new_cell);
            free(node);
            return;
        }
    }   
    for (int i = 0; i < hash; i++) {
        if (table[i] == NULL) {
            table[i] = new_cell;
            return;
        }
        else if (strcmp(table[i]->key, key) == 0){
            printf("Node with [%s] key is already present\n", key);
            free(new_cell);
            free(node);
            return;
        }
    }
}
CELL* searchLinear(CELL** table, char* key, int table_size) {
    // search the table, if the cell is not located, where the hashfunction supposes it should be,
    // search the rest of the table until the cell is found or NULL is encountered, return either pointer to cell or null
    if (table == NULL) 
        return NULL;
    
    int hash = hashFunction(key, table_size);
    for (int j = hash; j < table_size; j++) {
        if (table[j] != NULL) {
            if (strcmp(table[j]->key, key) == 0)
                return table[j];
        }
        else
            return NULL;
    }   
    for (int i = 0; i < hash; i++) {
         if (table[i] != NULL) {
            if (strcmp(table[i]->key, key) == 0)
                return table[i];
        }
        else
            return NULL;
    }
        
    return NULL;
}
