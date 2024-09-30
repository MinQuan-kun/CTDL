#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long
#define inp freopen("file.inp", "r", stdin)
#define out freopen("file.out", "w", stdout)
#define TIME 1.0*clock()/CLOCKS_PER_SEC
#define fastIO ios_base::sync_with_stdio(0); cin.tie(0)

const int MAXN = 1e6 + 5;
const int MOD = 1e9 + 7;

struct Node {
    int data;
    Node *pNext;
    Node(int value): data(value), pNext(nullptr) {}
};

void push_back(Node *&pHead, int value); 
void processLists(Node *list, Node *numbers); 
void clear(Node *&pHead); 

signed main() {
    fastIO;
    int n; 
    Node *list = nullptr;
    Node *numbers = nullptr;

    while (cin >> n) 
        push_back(numbers, n);
    
    for (int i = 0; i <= 9; i++) 
        push_back(list, i);

    processLists(list, numbers);
    clear(list);
    clear(numbers);
    
    return 0;
} 

void push_back(Node *&pHead, int value) {
    Node *node = new Node(value); 

    if (pHead == nullptr) {
        pHead = node;
        return;
    }

    Node *tmp = pHead;
    while (tmp->pNext != nullptr) 
        tmp = tmp->pNext; 
    tmp->pNext = node;
}

void processLists(Node *list, Node *numbers) {
    int k = 0;
    Node *current = list;
    Node *numberNode = numbers;
    
    while (numberNode != nullptr) {
        if (numberNode->data < 0) 
            k = (k + 10 + numberNode->data) % 10;
        else 
            k = (k + numberNode->data) % 10;

        for (int i = 0; i < k; i++)
            current = current->pNext; 
            
        cout << current->data << " ";
        current = list; 
        numberNode = numberNode->pNext;
    }
} 

void clear(Node *&pHead) {
    while (pHead != nullptr) {
        Node *tmp = pHead;
        pHead = pHead->pNext; 
        delete tmp;
    }
}
