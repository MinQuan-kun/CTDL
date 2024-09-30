#include <iostream>
#include <string>
#include <cctype>
#include <stdexcept>
using namespace std;

template <class DataType>
class Stack;
// Cấu trúc của một nút trong danh sách liên kết đơn
template <class DataType>
struct Node {
    friend class Stack<DataType>; // Cho phép lớp Stack truy cập các thành viên riêng tư của Node

private:
    // Dữ liệu của Node
    DataType _data;
    // Con trỏ đến Node kế tiếp
    Node* _pNext;

public:
    // Constructor khởi tạo Node mới có giá trị là data
    Node(DataType data);
    // Hiển thị dữ liệu của Node
    void display();
};

// Constructor khởi tạo Node mới
template <class DataType>
Node<DataType>::Node(DataType data) : _data(data), _pNext(nullptr) {}

// Hiển thị giá trị của Node
template <class DataType>
void Node<DataType>::display() {
    cout << _data << endl;
}

// Lớp Stack sử dụng danh sách liên kết đơn
template <class DataType>
class Stack {
private:
    // Con trỏ đến phần tử đỉnh của Stack
    Node<DataType>* _pTop;
    // Số phần tử hiện tại của Stack
    int _iSize;

public:
    // Constructor khởi tạo Stack rỗng
    Stack();
    // Destructor hủy bỏ Stack
    ~Stack();

    // Kiểm tra xem Stack có rỗng không
    bool isEmpty() const;
    // Thêm một phần tử vào đỉnh Stack
    void push(DataType data);
    // Xóa và trả về phần tử ở đỉnh Stack
    DataType pop();
    // Xem giá trị của phần tử ở đỉnh Stack
    DataType peek() const;
    // Hiển thị toàn bộ Stack
    void display() const;
    // Xóa toàn bộ Stack
    void clear();
    // Lấy số phần tử hiện tại của Stack
    int getSize() const;
};

// Constructor khởi tạo Stack rỗng
template <class DataType>
Stack<DataType>::Stack() : _pTop(nullptr), _iSize(0) {}

// Destructor hủy bỏ Stack
template <class DataType>
Stack<DataType>::~Stack() {
    clear();
}

// Kiểm tra Stack có rỗng không
template <class DataType>
bool Stack<DataType>::isEmpty() const {
    return _pTop == nullptr;
}

// Thêm một phần tử vào đỉnh Stack
template <class DataType>
void Stack<DataType>::push(DataType data) {
    Node<DataType>* pTemp = new Node<DataType>(data);
    pTemp->_pNext = _pTop;
    _pTop = pTemp;
    _iSize++;
}

// Xóa và trả về phần tử ở đỉnh Stack
template <class DataType>
DataType Stack<DataType>::pop() {
    if (isEmpty()) {
        throw runtime_error("Stack rong!!!");
    }
    Node<DataType>* pTemp = _pTop;
    DataType value = pTemp->_data;
    _pTop = pTemp->_pNext;
    delete pTemp;
    _iSize--;
    return value;
}

// Xem giá trị của phần tử ở đỉnh Stack
template <class DataType>
DataType Stack<DataType>::peek() const {
    if (isEmpty()) {
        throw runtime_error("Stack rong!!!");
    }
    return _pTop->_data;
}

// Hiển thị toàn bộ Stack
template <class DataType>
void Stack<DataType>::display() const {
    if (isEmpty()) {
        cout << "Stack rong!!!" << endl;
    }
    else {
        Node<DataType>* p = _pTop;
        while (p != nullptr) {
            p->display();
            p = p->_pNext;
        }
        cout << "So phan tu cua Stack: " << _iSize << endl;
    }
}

// Xóa toàn bộ Stack
template <class DataType>
void Stack<DataType>::clear() {
    Node<DataType>* pTemp;
    while (_pTop != nullptr) {
        pTemp = _pTop;
        _pTop = pTemp->_pNext;
        delete pTemp;
    }
    _iSize = 0;
}

// Lấy số phần tử hiện tại của Stack
template <class DataType>
int Stack<DataType>::getSize() const {
    return _iSize;
}

// Hàm tính toán giá trị của một phép toán
int evaluate(int left, int right, char op) {
    switch (op) {
    case '+': return left + right;
    case '-': return left - right;
    case '*': return left * right;
    case '/':
        if (right == 0) throw runtime_error("Khong the chia cho 0");
        return left / right;
    default: throw runtime_error("Phep toan sai");
    }
}

// Hàm tính giá trị của biểu thức hậu tố
int calculateValue(const string& postfix) {
    Stack<int> stack;
    string token;

    for (char c : postfix) {
        if (isspace(c)) {
            if (!token.empty()) {
                // Nếu token không rỗng, xử lý token
                stack.push(stoi(token));
                token.clear();
            }
        }
        else if (isdigit(c)) {
            token += c;
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            if (!token.empty()) {
                stack.push(stoi(token));
                token.clear();
            }
            int right = stack.pop();
            int left = stack.pop();
            stack.push(evaluate(left, right, c));
        }
        else {
            throw runtime_error("Sai ky tu");
        }
    }
    // Xử lý token cuối cùng
    if (!token.empty()) {
        stack.push(stoi(token));
    }

    if (stack.isEmpty()) {
        throw runtime_error("Bieu thuc hau to khong hop le");
    }

    return stack.pop();
}

// Hàm chính
int main() {
    string postfix;
    cout << "Nhap bieu thuc hau to: ";
    getline(cin, postfix);

    try {
        int result = calculateValue(postfix);
        cout << "Gia tri cua bieu thuc hau to la: " << result << endl;
    }
    catch (const runtime_error& e) {
        cout << "Loi: " << e.what() << endl;
    }

    return 0;
}
