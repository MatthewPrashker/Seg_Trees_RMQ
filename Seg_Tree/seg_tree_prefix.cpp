#include <iostream>
using namespace std;
typedef long long ll;
const int MAX_ARR_SIZE = 20000;
const int MAX_TREE_SIZE = 4*MAX_ARR_SIZE;

struct node {
    ll sum;
    ll prefix;
    node(ll sum, ll prefix): sum(sum), prefix(prefix) {}
    node(ll x = 0): sum(x), prefix(std::max(0LL, x)) {}

    //merge two nodes
    node operator+(const node& other) {
        return {sum + other.sum, std::max(prefix, sum + other.prefix)};
    }
};

void update(int i, int val, int k, int l, int r, node (&tree)[MAX_TREE_SIZE], int (&arr)[MAX_ARR_SIZE]) {
    if(l == r) {
        tree[k] = node(val);
        arr[i] = val;
        return;
    }
    int m = (l + r)/2;
    if(i <= m) {
        update(i, val, 2*k, l, m, tree, arr);
    } else {
        update(i, val, 2*k + 1, m + 1, r, tree, arr);
    }
    tree[k] = tree[2*k] + tree[2*k + 1]; //merge the two updated nodes
}

node query(int ql, int qr, int k, int l, int r, node (&tree)[MAX_TREE_SIZE], int (&arr)[MAX_ARR_SIZE]) {
    if(ql > r || qr < l) {
        return node(0);
    }
    if(ql <= l && r <= qr) {
        return tree[k];
    }
    int m = (l + r)/2;
    node query_left = query(ql, qr, 2*k, l, m, tree, arr);
    node query_right = query(ql, qr, 2*k + 1, m + 1, r, tree, arr);
    return query_left + query_right;
}

void build(int k, int l, int r, node (&tree)[MAX_TREE_SIZE], int (&arr)[MAX_ARR_SIZE]) {
    
    // if(l > r) {
    //     return;
    // }
    if(l == r) {
        tree[k] = node(arr[l]);
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
    build(1,0, MAX_ARR_SIZE - 1, tree, A);
    std::cout << query(0, 1, 1, 0, MAX_ARR_SIZE - 1, tree, A).prefix << "\n";
    update(1,-10,1,0,MAX_ARR_SIZE - 1, tree, A);
    std::cout << query(0, 1, 1, 0, MAX_ARR_SIZE - 1, tree, A).prefix << "\n";
}

