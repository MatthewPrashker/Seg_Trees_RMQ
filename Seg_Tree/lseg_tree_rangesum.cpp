//lazy seg tree which supports range updates and range sum

#include <iostream>
using namespace std;
typedef long long ll;
const int MAX_ARR_SIZE = 200005;
const int MAX_TREE_SIZE = 4*MAX_ARR_SIZE;


struct node {
    int32_t sum;
    int lazy;
    
    node(): sum(0), lazy(0)  {}
    node(int sum, int lazy_val): sum(sum), lazy(lazy_val) {}

    //merge two nodes
    node operator+(const node& other) {
        return node(sum + other.sum, 0); //we only ever merge nodes if they have no lazy value
    }
};

void push(int k, int l, int r, node(&tree)[MAX_TREE_SIZE], int (&arr)[MAX_ARR_SIZE]) {
    tree[k].sum += tree[k].lazy*(r- l + 1);
    tree[2*k].lazy += tree[k].lazy;
    tree[2*k + 1].lazy += tree[k].lazy;
    tree[k].lazy = 0; 
}
//update the node in the tree at position k and distribute the nodes to the left and the right children
void update(int ul, int ur, int val, int k, int l, int r, node (&tree)[MAX_TREE_SIZE], int (&arr)[MAX_ARR_SIZE]) {
    
    push(k, l, r, tree, arr);

    if(ur < l || r < ul) {return;}

    if(ul <= l && r <= ur) {
        tree[k].lazy += val;
        return;
    }

    //compute the overlap and update the sum
    tree[k].sum += val*(min(ur, r) - max(ul, l) + 1);
    int mid = (l + r)/2;
    update(ul, ur, val, 2*k, l, mid,  tree, arr);
    update(ul, ur, val, 2*k + 1, mid + 1, r, tree, arr);
}

node query(int ql, int qr, int k, int l, int r, node (&tree)[MAX_TREE_SIZE], int (&arr)[MAX_ARR_SIZE]) {
    
    push(k, l, r, tree, arr);

    if(ql > r|| qr < l) {
        return node(); //dummy node
    }
    if(ql <= l && r <= qr) {
        return tree[k];
    }
    int mid = (l + r)/2;
    node query_left = query(ql, qr, 2*k, l, mid, tree, arr);
    node query_right = query(ql, qr, 2*k + 1, mid + 1, r, tree, arr);
    return query_left + query_right;
}

void build(int k, int l, int r, node (&tree)[MAX_TREE_SIZE], int (&arr)[MAX_ARR_SIZE]) {
    
    if(l == r) {
        tree[k] = node(arr[l], 0); //all nodes originally have zero lazy values
        return;
    }
    int m = (l + r)/2;

    //recursively build the trees and merge the children nodes
    build(2*k, l, m, tree, arr);
    build(2*k + 1, m + 1, r, tree, arr);
    tree[k] = tree[2*k] + tree[2*k + 1]; 
}


int main() {
    node tree[MAX_TREE_SIZE];
    int A[MAX_ARR_SIZE];
    for(int i = 0; i < MAX_ARR_SIZE; i++) {
        A[i] = 2;
    }

    //The first three parameters in query and update are what matter
    //First three parameters of query are (query-left, query-right) - get the sum in this range
    //First three parameters of update are (update-left, update-right, val) - adds val to ever node in this change.
    //Here all of the Arrays are 0 indexed. 

    build(1,0, MAX_ARR_SIZE - 1, tree, A);
    std::cout << query(0, 0, 1,0, MAX_ARR_SIZE - 1, tree, A).sum << "\n";
    update(0,0,5,1,0,MAX_ARR_SIZE - 1,tree, A);
    std::cout << query(0, 0, 1, 0, MAX_ARR_SIZE - 1, tree, A).sum << "\n";
}

