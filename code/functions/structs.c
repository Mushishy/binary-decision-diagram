// Linear Hashtable
typedef struct LinearCell {                 // Cell of Linear Hashtable
    char key[STRING];                       // the key is boolean expression 
    struct BddNode *node;                   // the data is pointer to a tree node
} CELL;

// BDD Tree
typedef struct BddNode {                    // Binary Decision Diagram Tree Node
    char expression[STRING];                // stores boolean expression
    struct BddNode *pointer[2];             // pointer to right node, and left node 
} NODE;

typedef struct BddTrunk {                   // Binary Decision Diagram Tree Trunk
    struct BddNode* root,* zero,* one;      // pointer to root of the tree, zero, and one nodes
    struct LinearCell*** table;             // two-dimensional array of LinearCells table[current_table][current_cell]
    int size, levels, expected_size;        // size of tree, number of levels (boolean expression order_size), expected size of tree without resize
} TREE;