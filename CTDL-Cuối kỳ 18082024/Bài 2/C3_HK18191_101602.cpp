#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e6 + 5;
const int MOD = 1e9 + 7;
struct Node {
    int data;
    Node *next;
    Node(int value) : data(value), next(nullptr) {}
};
bool isEmpty(Node *head);
int getFront(Node *head);
void clearList(Node *&head);
void addBack(Node *&head, int value);
void addFront(Node *&head, int value);
void removeFront(Node *&head);
signed main() {
    int n, k;
    Node *head = nullptr;
    cin >> n >> k;

    if (k > 0) {
        for (int i = 0; i < n; i++) {
            addBack(head, i);
        }
    } else {
        for (int i = 1; i < n; i++) {
            addFront(head, i);
        }
        addFront(head, 0);
    }

    k = abs(k);
    while (!isEmpty(head)) {
        for (int i = 1; i < k; i++) {
            addBack(head, getFront(head));
            removeFront(head);
        }
        cout << getFront(head) << " ";
        removeFront(head);
    }

    clearList(head);
    return 0;
}
bool isEmpty(Node *head) {
    return head == nullptr;
}
int getFront(Node *head) {
    return head->data;
}
void clearList(Node *&head) {
    while (head != nullptr) {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
}
void addBack(Node *&head, int value) {
    Node *newNode = new Node(value);
    if (head == nullptr) {
        head = newNode;
        return;
    }

    Node *current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    current->next = newNode;
}
void addFront(Node *&head, int value) {
    Node *newNode = new Node(value);
    newNode->next = head;
    head = newNode;
}
void removeFront(Node *&head) {
    if (head != nullptr) {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
}
