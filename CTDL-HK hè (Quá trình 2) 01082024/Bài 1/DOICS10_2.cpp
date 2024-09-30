#include <iostream>
#include <stack>
using namespace std;
// Hàm chuyển đổi từ hệ cơ số 10 sang hệ cơ số 2
void chuyencoso2(int n) {
    stack<int> m;
    // Chuyển đổi
    while (n > 0) {
        int value = n % 2; // Lấy phần dư khi chia cho 2
        m.push(value); // Đẩy phần dư vào ngăn xếp
        n /= 2; // Chia cho 2 để tiếp tục chuyển đổi
    }
    // In kết quả
    while (!m.empty()) {
        cout << m.top(); // Lấy phần tử ở đầu ngăn xếp
        m.pop(); // Xóa phần tử ở đầu ngăn xếp
    }
}
int main() {
    int n;
    cin >> n;
    if (n == 0) {
        cout<<0;
        return 0;
    }
    chuyencoso2(n);
    return 0;
}