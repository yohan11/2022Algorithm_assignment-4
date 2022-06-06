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


struct BTreeNode* splitNode(int pos, struct BTreeNode* node, struct BTreeNode* parent){ 
    int middle_key;
    middle_key = node->cnt_key / 2;
    struct BTreeNode* right_node; 

    right_node = (struct BTreeNode*)malloc(sizeof(struct BTreeNode));
    right_node-> leaf = node->leaf;
    right_node-> cnt_key = 0;
    right_node-> cnt_child = 0;
    
    int num_iter = node->cnt_key;
    for(int i = middle_key+1; i< num_iter; i++){
        right_node->key[i-(middle_key+1)] = node->key[i];
        right_node ->cnt_key++;
        node->cnt_key--;
    }

    if (!node->leaf){ 
        num_iter = node->cnt_child;
        for (int i = middle_key+1; i < num_iter; i++ ) { 
            right_node->child[i-(middle_key+1)] = node ->child[i];
            right_node-> cnt_child++; 
            node->cnt_child--;
        }
    }

    if (node==root) { 
        struct BTreeNode* new_parent_node;
        new_parent_node = createNode(node->key[middle_key]); 
        node->cnt_key--;
        new_parent_node->child[0] = node;
        new_parent_node->child[1] = right_node;

        new_parent_node->cnt_child = 2;
        return new_parent_node; 
    }
    else {
        for (int i= parent->cnt_key; i> pos; i--){ 
            parent->key[i] = parent->key[i-1];
            parent->child[i+1] = parent->child[i];
        }

        parent->key[pos]= node->key[middle_key];
        parent->cnt_key++; 
        node->cnt_key--;
        parent-> child[pos+1] = right_node; 
        parent->cnt_child+=1;
    }
    return node; 
}


struct BTreeNode* insertNode(int parent_pos, int val, struct BTreeNode* node, struct BTreeNode* parent) { // 삽입할 값,  
    int pos; 
    for (pos =0; pos < node->cnt_key; pos++ ) {
        if (val == node -> key[pos]){
            printf("Duplicates are not permitted!\n");
            return node;
        }
        else if (val< node->key[pos]){ 
            break;
        }
    }
    if (!node->leaf) {
        node -> child[pos] = insertNode(pos, val, node->child[pos] ,node); 
        if (node->cnt_key == max_keys +1){ 
            node = splitNode(parent_pos, node,parent); 
        }
    }
    else {
        for (int i = node->cnt_key; i > pos; i--) { 
            node -> key[i] = node->key[i-1];
            node -> child[i+1] = node->child[i]; 
        }

        node -> key[pos] = val;
        node -> cnt_key++;
        if (node-> cnt_key == max_keys+1){ 
            node = splitNode(parent_pos, node,parent);
        }
    }   
    return node;

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