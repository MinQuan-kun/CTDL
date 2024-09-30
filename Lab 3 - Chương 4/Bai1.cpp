#include<iostream>
#define MAX_SIZE 10;


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

    void decimalToBinary(int n);
};

int main() {
    int n;
    bool validInput = false;
    while (!validInput) {
        cout << "Nhap so nguyen N: ";
        try {
            cin >> n;
            if (cin.fail()) {
                cout << "Khong phai so nguyen. Vui long nhap lai!";
            }
            validInput = true;
        }
        catch (runtime_error& e) {
            cout << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    Stack<int> stack;
    stack.decimalToBinary(n);
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
    if (isEmpty)
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
/********************************************************************
* @Description Ham doi co song 10 sang 2
* @return Co so 2
********************************************************************/
template <class DataType>
void Stack<DataType>::decimalToBinary(int n) {
    Stack<int> binaryStack;
    while (n > 0) {
        int remainder = n % 2;
        binaryStack.push(remainder);
        n /= 2;
    }
    cout << "So nhi phan la: ";
    while (!binaryStack.isEmpty()) {
        cout << binaryStack.pop();
    }
    cout << endl;
}
