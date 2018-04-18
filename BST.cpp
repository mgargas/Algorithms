#include <iostream>

using namespace std;

struct BSTnode{
    int v;
    BSTnode* left;
    BSTnode* right;
};


BSTnode* make_node(int v){
    BSTnode* node = new BSTnode;
    node->v = v;
    node->right = NULL;
    node->left = NULL;
    return node;
}

void insert(BSTnode* &root, BSTnode* node){
    if(root == NULL) root = node;
    else if(node->v <= root->v) insert(root->left, node);
    else insert(root->right, node);
}


BSTnode* find(BSTnode* root, int key){
    if(root == NULL) return NULL;
    if(key < root -> v) return find(root -> left, key);
    else if(key > root -> v) return find(root -> right, key);
    return root;
}


void in_order(BSTnode* root){
    if(root != NULL){
        in_order(root->left);
        cout<<root->v<<" ";
        in_order(root->right);
    }
}


BSTnode* get_min(BSTnode* root){
    while(root->left != NULL) {
        //printf("%d", root->v);
        root = root -> left;
    }
    return root;
}


BSTnode* get_max(BSTnode* root){
    while(root -> right != NULL){
        root = root -> right;
    }
    return root;
}


BSTnode* successor(BSTnode* root, BSTnode* node){
    if(node -> right != NULL) return get_min(node -> right);
    BSTnode* succ = root;
    while(root){
        if(node -> v < root -> v){
            succ = root;
            root = root -> left;
        } else if(node -> v > root -> v){
            root = root -> right;
        } else break;
    }
    return succ;
}

BSTnode* predecessor(BSTnode* root, BSTnode* node){
    if(node -> left != NULL) return get_max(node -> left);
    BSTnode* pred = root;
    while(root){
        if(node -> v > root -> v){
            pred = root;
            root = root -> right;
        } else if(node -> v < root -> v){
            root = root -> left;
        } else break;
    }
    return pred;
}

bool is_BST(BSTnode* root) {
    if (root == NULL) return false;
    if (root->left != NULL) {
        if (root->left->v > root->v) return false;
        bool left = is_BST(root->left);
    }
    if (root->right != NULL) {
        if (root->right->v <= root->v) return false;
        bool right = is_BST(root->right);
    }
    return left && right;
}


int count_nodes(BSTnode* root){
    if(root == 0) return 0;
    return 1 + count_nodes(root -> left) + count_nodes(root -> right);
}


int get_mean_value(BSTnode* root){
    int count = count_nodes(root);
    BSTnode* middle = get_min(root);
    for(int i=0; i<count/2; i++) middle = successor(root, middle);
    if(count % 2 != 0) return middle -> v;
    return (middle -> v + successor(root, middle) -> v) / 2;
}


int get_height(BSTnode* root){
    if(root == NULL) return -1;
    return 1 + max(get_height(root->left), get_height(root->right));
}


bool is_AVL(BSTnode* root){
    int n = count_nodes(root);
    BSTnode* current = get_min(root);
    for(int i=0; i<n; i++){
        if(abs(get_height(current -> left) - get_height(current -> right)) > 1) return false;
        current = successor(root, current);
    }
    return true;
}

int main() {
    BSTnode* root = NULL;
    insert(root, make_node(19));
    insert(root, make_node(9));
    insert(root, make_node(25));
    insert(root, make_node(14));
    insert(root, make_node(2));
    insert(root, make_node(5));
    insert(root, make_node(39));
    insert(root, make_node(7));
    insert(root, make_node(100));
    insert(root, make_node(102));
    in_order(root);
    printf("\n");
    printf("%d\n", get_min(root) -> v);
    printf("%d\n", get_max(root) ->  v);
    printf("%d\n", find(root, 39) ->  v);
    printf("%d\n", successor(root, find(root, 14)) -> v);
    printf("%d\n", predecessor(root, find(root, 7)) -> v);
    if(is_BST(root)) printf("It is indeed a BST Tree my friend\n");
    if(is_AVL(root)) printf("It is indeed an AVL Tree my friend\n");
    else printf("Sorry, you have to make it balanced\n");
    printf("%d\n", count_nodes(root));
    printf("%d\n", get_mean_value(root));

    BSTnode* AVL_root = NULL;
    insert(AVL_root, make_node(50));
    insert(AVL_root, make_node(17));
    insert(AVL_root, make_node(12));
    insert(AVL_root, make_node(9));
    insert(AVL_root, make_node(14));
    insert(AVL_root, make_node(23));
    insert(AVL_root, make_node(19));
    insert(AVL_root, make_node(72));
    insert(AVL_root, make_node(54));
    insert(AVL_root, make_node(76));
    insert(AVL_root, make_node(67));
    if(is_AVL(AVL_root)) printf("Finally, you made a nice AVL Tree\n");
    return 0;
}