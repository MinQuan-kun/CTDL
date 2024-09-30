#include <bits/stdc++.h>
using namespace std;
int main() {
    stack<char> ds; 
    string str; cin >> str;
    if (str.size() == 0) {
        cout << "yes"; return 0;
    }
    for (auto x : str) {
        if (x == '(' || x == '[' || x == '{')
            ds.push(x);
        else {
            if (!ds.empty()) {
                char ch = ds.top(); ds.pop();
                if ((ch == '(' && x != ')') || (ch == '[' && x != ']') || (ch == '{' && x != '}')) {
                    cout << "no"; return 0;
                }
            } else {
                cout << "no"; return 0;
            }
        }
    }

    (!ds.empty()) ? cout << "no" : cout << "yes";
    return 0;
}
// Code của Ty