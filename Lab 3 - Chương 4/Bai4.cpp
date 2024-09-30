#include <iostream>
#include <stdexcept>
using namespace std;

template <class DataType>
class Stack;
// Định nghĩa cấu trúc của Node cho danh sách liên kết đơn
template <class DataType>
struct Node {
    friend Stack<DataType>;
private:
    //Dữ liệu của Node
    DataType _data;
    //Con trỏ đến Node Kế tiếp
    Node* _pNext;
public:
    //Khởi tạo Node mới có giá trị là data
    Node(DataType data);
    //Hiện thị dữ liệu của Node
    void display();
};
/********************************************************************
* @Description Khởi tạo một Node mới có giá trị là data
********************************************************************/
template <class DataType>
Node<DataType>::Node(DataType data) {
    _data = data;
    _pNext = NULL;
}
/********************************************************************
* @Description Hiện thị giá trị Node
********************************************************************/
template <class DataType>
void Node<DataType>::display() {
    cout << _data << endl;
}
// Lớp Stack sử dụng danh sách liên kết đơn
template <class DataType>
class Stack {
private:
    //Con trỏ trỏ tới phần tử đỉnh Stack
    Node<DataType>* _pTop;
    //Số phần tử hiện tại của Stack
    int _iSize;
public:
    //Khởi tạo Stack rỗng
    Stack();
    //Hủy bỏ Stack
    ~Stack();

    //Kiểm tra xem Stack có rỗng không
    bool isEmpty();
    //thêm vào Stack phần tử có giá trị data
    void push(DataType data);
    //Xóa và trả về phần tử ở đỉnh Stack
    DataType pop();
    //Xem giá trị phần tử ở đỉnh Stack
    DataType peek();
    //Hiện thị Stack
    void display();
    //Hủy bỏ Stack
    void clear();
    //Lấy số phần tử hiện tại của Stack
    int getSize();
};

/********************************************************************
* @Description Constructor tao Stack rong
********************************************************************/
template <class DataType>
Stack<DataType>::Stack() : _pTop(nullptr), _iSize(0) {}
/********************************************************************
* @Description Destructor huy bo Stack
********************************************************************/
template <class DataType>
Stack<DataType>::~Stack() {
    clear();
}
/********************************************************************
* @Description Kiem tra Stack co rong hay khong
* @return treu neu Stack rong, false neu Stack khac rong
********************************************************************/
template <class DataType>
bool Stack<DataType>::isEmpty() {
    return _pTop == nullptr;
}
/********************************************************************
* @Description Them mot phan tu vao dinh Stack
* @parameter Gia tri cua phan tu can them
********************************************************************/
template <class DataType>
void Stack<DataType>::push(DataType data) {
    Node<DataType>* pTemp = new Node<DataType>(data);
    pTemp->_pNext = _pTop;
    _pTop = pTemp;
    _iSize++;
}
/********************************************************************
* @Description Lay phan tu o dinh STack ra khoi Stack
* @parameter Gia tri cua phan tu o dinh Stack
* @attention Neu Stack rong thi thong bao ngoai le
********************************************************************/
template <class DataType>
DataType Stack<DataType>::pop() {
    if (isEmpty()) {
        cout << "Stack rong !!!" << endl;
        exit;
    }

    Node<DataType>* pTemp = _pTop;
    DataType temp = pTemp->_data;
    _pTop = pTemp->_pNext;
    delete pTemp;
    _iSize--;
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
        cout << "Stack rong !!!" << endl;
        exit;
    }
    return _pTop->_data;
}
/********************************************************************
* @Description Hien thi toan bo Stack
********************************************************************/
template <class DataType>
void Stack<DataType>::display() {
    if (isEmpty())
        cout << "Stack rong !!!" << endl;
    else
    {
        for (Node<DataType>* p = _pTop; p != NULL; p = p->_pNext)
            p->display();
        cout << "So phan tu cua Stack: " << _iSize << endl;
    }
}
/********************************************************************
* @Description Xoa toan bo Stack
********************************************************************/
template <class DataType>
void Stack<DataType>::clear() {
    Node<DataType>* pTemp;
    while (_pTop != NULL) {
        pTemp = _pTop;
        _pTop = pTemp->_pNext;
        delete pTemp;
    }
    _iSize = 0;
}
/********************************************************************
* @Description Tra ve so phan tu hien tai cua Stack
* @return So phan tu hien tai cua Stack
********************************************************************/
template <class DataType>
int Stack<DataType>::getSize() {
    return _iSize;
}
/********************************************************************
* @Description Tra ve so phan tu hien tai cua Stack
* @return So phan tu hien tai cua Stack
********************************************************************/
template <class DataType>
int partition(DataType a[], int low, int high) {
    DataType pivot = a[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (a[j] <= pivot) {
            i++;
            swap(a[i], a[j]);
        }
    }
    swap(a[i + 1], a[high]);
    return (i + 1);
}
/********************************************************************
* @Description Tra ve so phan tu hien tai cua Stack
* @return So phan tu hien tai cua Stack
********************************************************************/
template <class DataType>
void quickSortIterative(DataType a[], int size) {
    Stack<int> stack;

    stack.push(0);
    stack.push(size - 1);

    while (!stack.isEmpty()) {
        int high = stack.pop();
        int low = stack.pop();

        if (low < high) {
            int p = partition(a, low, high);

            // Push right partition
            stack.push(p + 1);
            stack.push(high);

            // Push left partition
            stack.push(low);
            stack.push(p - 1);
        }
    }
}

// Hàm main để kiểm tra thuật toán
int main() {
    int a[] = { 10, 7, 8, 9, 1, 5 };
    int size = sizeof(a) / sizeof(a[0]);

    cout << "Truoc khi sap xep: ";
    for (int i = 0; i < size; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
    quickSortIterative(a, size);

    cout << "Sau khi sap xep: ";
    for (int i = 0; i < size; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    return 0;
}