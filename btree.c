#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define T 5
#define max_children T
#define max_keys max_children-1
#define min_keys (int)(ceil(T/2.0))-1

struct BTreeNode{
    bool leaf; 
    int key[max_keys+1]; 
    int cnt_key; 
    struct BTreeNode* child[max_children+1]; 
    int cnt_child; 
};

int deleteValFromNode(int val, struct BTreeNode* node);

struct BTreeNode* root;

struct BTreeNode* createNode(int val){ 
    struct BTreeNode* newNode;
    newNode = (struct BTreeNode*)malloc(sizeof(struct BTreeNode)); 
    newNode -> leaf = false; 
    newNode -> key[0] = val; 
    newNode -> cnt_key = 1;
    newNode -> cnt_child = 0;
    return newNode;
}

void insert(int val){
    if (!root){ 
        root = createNode(val);
        root -> leaf = true ;
        return;
    }
    else{ 
        root = insertNode(0,val,root,root); 
    }
}
