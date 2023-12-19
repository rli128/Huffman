#include "HCTree.hpp"
#include <queue>
#include <stack>
using namespace std;

//Recursive clearing function I implemented in PA2
void deleteRecursive(HCNode* newNode) {
    //check if nullptr
    if (newNode != nullptr) {
        if (newNode->c0 != nullptr) {
            deleteRecursive(newNode->c0);
        }

        if (newNode->c1 != nullptr) {
            deleteRecursive(newNode->c1);
        }
        delete newNode;
    }
}


HCTree::~HCTree() {
    deleteRecursive(root);
}

void print(vector<HCNode*> leaves) {
    for (HCNode* nodes: leaves) {
        if (nodes != nullptr) {
            HCNode* curr = nodes;
            stack<int> binary;
            while(curr->p != nullptr) {
                HCNode* prev = curr;
                curr = curr->p;
                if (curr->c0 == prev) {
                    binary.push(0);
                }

                else {
                    binary.push(1);
                }
            }
            cout << nodes->symbol << endl;
            while (!binary.empty()) {
            cout << (binary.top()) << endl;
                binary.pop();
            }
        }
    }

}

void HCTree::build(const vector<int>& freqs) {
    int count = 0;
    for (int i: freqs) {
        if (i > 0) {
            leaves[count] = new HCNode(i, (char) count);
        }
        count++;
    }

    priority_queue<HCNode*, vector<HCNode*>, greater<HCNode*>> pq;
    for (HCNode* nodes: leaves) {
        if (nodes != nullptr) {
            pq.push(nodes);
        }
    }

    if (pq.size() > 2) {
        while (pq.size() > 1) {
            HCNode* zero = pq.top();
            pq.pop();
            HCNode* one = pq.top(); 
            pq.pop();

            HCNode* combo = new HCNode(one->count + zero->count, zero->symbol);
            combo->c0 = zero;
            combo->c1 = one;
            zero->p = combo;
            one->p = combo;
            pq.push(combo);
        }
    root = pq.top();
    //print(leaves);
    }


}



void HCTree::encode(unsigned char symbol, FancyOutputStream & out) const{
    HCNode* curr = leaves[symbol];
    stack<int> binary;
    while(curr->p != nullptr) {
        HCNode* prev = curr;
        curr = curr->p;
        if (curr->c0 == prev) {
            binary.push(0);
        }

        else {
            binary.push(1);
        }
    }

    while (!binary.empty()) {
        out.write_bit(binary.top());
        binary.pop();
    }


}


unsigned char HCTree::decode(FancyInputStream & in) const{
    HCNode* curr = root;
    int binary;
    while (curr->c0 != nullptr) {
        binary = in.read_bit();
        if (binary == 0) {
            if (curr->c0 != nullptr) {
                curr = curr->c0;
            }
            else return curr->symbol;
        }

        if (binary == 1) {
            if (curr->c1 != nullptr) {
                curr = curr->c1;
            }
            else return curr->symbol;
        }
        if (binary == -1) {
            return -1;
        }

    }
    return curr->symbol;
}
