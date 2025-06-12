void removeChar(char * str, char charToRemmove){
    // remove all instances of a given char
    // this function is used to remove all '!'
    int i, j;
    int len = strlen(str);
    for(i=0; i<len; i++) {
        if(str[i] == charToRemmove) {
            for(j=i; j<len; j++) {
                str[j] = str[j+1];
            }
            len--;
            i--;
        }
    }
}
char check(char*expression, char*order, char*vector) {
    int i = 0, curOrderIndex = 0, flag = 1;
    char ex[STRING];
    char* token;
    strcpy(ex, expression);

    // search the expression for order[i] 
    // eg. if order[i] == A
    // replace it with its current value based on vector 
    // if !A is present replace 'A' with the negation of vector    
    while(order[i] != '\0') {
        int j = 0;
        while(ex[j] != '\0') {
            if (ex[j] == '!' && ex[j+1] == order[i]) {
                if (vector[curOrderIndex] == '0') {
                    ex[j+1] = '1';
                }
                else { 
                    ex[j+1] = '0';
                }
                j++;
            }
            if (ex[j] == order[i]) {
                ex[j] = vector[curOrderIndex];
            }
            j++;
        } 
        i++;
        curOrderIndex++;
    }

    // remove all instances of '!'
    removeChar(ex, '!');
    
    // cut the expression into pieaces until '+' or '\0'
    token = strtok(ex, DELIM);

    // go over current word, and if it contains '0' go over next word
    // if there are no '0' return '1' else '0' is returned
    while(token != NULL) {
        i = 0;
        flag = 1;
        while (token[i] != '\0') {
            if (token[i] == '0')
                flag = 0;
                break;
        }
        if (flag)
            return '1';
        token = strtok(NULL, DELIM);
    }

    return '0';
}