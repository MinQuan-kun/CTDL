#include<iostream>
#include<string>
#define MAX_SIZE 10
using namespace std;

template <class DataType>
class Stack
{
private:
    //Mang cac phan tu cua Stack
    DataType* _array;
    //Chi so cua phan tu o dinh Stack
    int _iTop;
    //So phan tu toi da cua Stack
    int _iCapacity;
public:
    //Khoi tao Stack rong voi gia tri mac dinh
    Stack();
    //Khoi tao Stack rong voi gia tri maxSize
    Stack(int maxSize);
    //Huy bo Stack
    ~Stack();
    //Kiem tra xem Stack co rong khong
    bool isEmpty();
    //Kiem tra xem Stack co day khong
    bool isFull();
    //Them vao Stack phan tu co gia tri data
    void push(DataType data);
    //Xoa tra ve phan tu tren dinh Stack
    DataType pop();
    //Xem gia tri phan tu o dinh Stack
    DataType peek();
    //Hien thi Stack
    void display();
    //Huy bo Stack
    void clear();
    //Lay so phan tu hien tai cua Stack
    int getSize();
};
class InfixToPostfixConverter {
private:
    Stack<char> operators;
    bool isOperator(char c) const {
        return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
    }
    int precedence(char op) const {
        switch (op) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        case '^': return 3;
        default: return 0;
        }
    }
public:
    string infixToPostfix(const string& infix) {
        string postfix;
        for (char c : infix) {
            if (isspace(c)) {
                continue;
            }
            if (isdigit(c) || isalpha(c)) {
                postfix += c;
            }
            else if (c == '(') {
                operators.push(c);
            }
            else if (c == ')') {
                while (!operators.isEmpty() && operators.peek() != '(') {
                    postfix += operators.pop();
                }
                if (!operators.isEmpty()) {
                    operators.pop();
                }
            }
            else if (isOperator(c)) {
                while (!operators.isEmpty() && precedence(operators.peek()) >= precedence(c)) {
                    postfix += operators.pop();
                }
                operators.push(c);
            }
        }
        while (!operators.isEmpty()) {
            postfix += operators.pop();
        }
        return postfix;
    }
};
int main() {
    string infix;
    cout << "Nhap bieu thuc trung to: ";
    getline(cin, infix);
    try {
        InfixToPostfixConverter converter;
        string postfix = converter.infixToPostfix(infix);
        cout << "Bieu thuc hau to: " << postfix << endl;
    }
    catch (const runtime_error& e) {
        cout << "Loi: " << e.what() << endl;
    }
    return 0;
}
/********************************************************************
* @Description Constructor tao Stack rong co so phan tu toi da la MAX_SIZE
********************************************************************/
template <class DataType>
Stack<DataType>::Stack() {
    _iCapacity = MAX_SIZE;
    _array = new DataType[_iCapacity];
    _iTop = -1;
}
/********************************************************************
* @Description Constructor tao Stack rong co so phan tu toi da la maxSize
* @parameter So phan tu toi da cua Stack
* @attention Neu maxSize <=0 thi lay gia tri mac dinh la MAX_SIZE
********************************************************************/
template <class DataType>
Stack<DataType>::Stack(int maxSize) {
    _iCapacity = maxSize > 0 ? maxSize : MAX_SIZE;
    _array = new DataType[_iCapacity];
    _iTop = -1;
}
/********************************************************************
* @Description Destructor huy bo Stack
********************************************************************/
template <class DataType>
Stack<DataType>::~Stack() {
    delete[] _array;
    _iTop = -1;
}
/********************************************************************
* @Description Kiem tra Stack co rong hay khong
* @return treu neu Stack rong, false neu Stack khac rong
********************************************************************/
template <class DataType>
bool Stack<DataType>::isEmpty() {
    return (_iTop == -1);
}
/********************************************************************
* @Description Kiem tra Stack co day hay khong
* @return treu neu Stack day, false neu Stack chua day
********************************************************************/
template <class DataType>
bool Stack<DataType>::isFull() {
    return (_iTop == _iCapacity - 1);
}
/********************************************************************
* @Description Them mot phan tu vao dinh Stack
* @parameter Gia tri cua phan tu can them
* @attention Neu Stack day thi thong bao ngoai le
********************************************************************/
template <class DataType>
void Stack<DataType>::push(DataType data) {
    if (isFull())
        cout << "Stack day! Khong the them phan tu moi !" << endl;
    else
        _array[++_iTop] = data;
}
/********************************************************************
* @Description Lay phan tu o dinh STack ra khoi Stack
* @parameter Gia tri cua phan tu o dinh Stack
* @attention Neu Stack rong thi thong bao ngoai le
********************************************************************/
template <class DataType>
DataType Stack<DataType>::pop() {
    if (isEmpty()) {
        cout << "Stack rong!!!" << endl;
        exit;
    }
    DataType temp = _array[_iTop];
    _iTop--;
    return temp;
}
/********************************************************************
* @Description xem gia tri phan tu o dinh Stack
* @parameter Gia tri cua phan tu o dinh Stack
* @attention Neu Stack rong thi thong bao ngoai le
********************************************************************/
template <class DataType>
DataType Stack<DataType>::peek() {
    if (isEmpty()) {
        cout << "Stack rong!!!" << endl;
        exit;
    }
    return _array[_iTop];
}
/********************************************************************
* @Description Hien thi toan bo Stack
********************************************************************/
template <class DataType>
void Stack<DataType>::display() {
    if (isEmpty())
        cout << "Stack rong!!!" << endl;
    else
        for (int i = _iTop; i >= 0; i--)
            cout << _array[i] << endl;
}
/********************************************************************
* @Description Xoa toan bo Stack
********************************************************************/
template <class DataType>
void Stack<DataType>::clear() {
    _iTop = -1;
}
/********************************************************************
* @Description Tra ve so phan tu hien tai cua Stack
* @return So phan tu hien tai cua Stack
********************************************************************/
template <class DataType>
int Stack<DataType>::getSize() {
    return (_iTop + 1);
}