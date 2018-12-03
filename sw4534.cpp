#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;

#define MOD 1000000007
long long cache[100000][2];
bool visited[100000] = {false, };

class Node {
public:
    int val;
    int root;
    vector<Node*> children;

    Node(int v) {
        val = v;
        root = 1;
    }
};

// white 0 black 1
long long totalCaseNum(Node* node, int color) { 
    visited[node->val] = true;
    if (cache[node->val][color] > 0)
        return cache[node->val][color];
    
    else {
        vector<Node*>::iterator child_it;
        long long ret = 1;
        if (color == 0) {         
            long long val = 1;
            for (child_it = node->children.begin(); child_it != node->children.end(); ++child_it) { 
                if (visited[(*child_it)->val]) {
                    continue;
                }
                val = (val * ((totalCaseNum(*child_it, 0) + totalCaseNum(*child_it, 1)) % MOD)) % MOD;                  
            }            
            cache[node->val][color] = val;
            
        }
        else if (color == 1) {  
            long long val = 1;
            for (child_it = node->children.begin(); child_it != node->children.end(); ++child_it) {
                if (visited[(*child_it)->val]) {
                    continue;
                }
                val = (val * (totalCaseNum(*child_it, 0) % MOD)) % MOD;                  
            }
            cache[node->val][color] = val;
            
        }
        visited[node->val] = false;
        return cache[node->val][color];
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int test_case = 1; test_case <= T; test_case++) {
        Node* node_list[100000];
        int N;
        cin >> N;
        
        for (int i = 0; i < N; i++) {
            node_list[i] = new Node(i);
        }
        for (int i = 0; i < N - 1; i++) {
            int first, second;
            cin >> first >> second;

            Node* parent;
            Node* child;
            parent = node_list[first- 1];
            child = node_list[second - 1];
            parent->children.push_back(child);
            child->children.push_back(parent);
        }
       
        Node* root = node_list[0];
        long long result = (totalCaseNum(root, 0) % MOD + totalCaseNum(root, 1) % MOD) %MOD;
        cout << "#" << test_case << " " << result << endl;

        for (int i = 0; i < N; i++) {            
            free(node_list[i]);
            cache[i][0] = 0;
            cache[i][1] = 0;
            visited[i] = false;
        }        
    }
    
    return 0;
}