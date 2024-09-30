#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

template<class DataType>
class LinkedList;

template <class DataType>
class Node {
    friend LinkedList<DataType>;
private:
    DataType _data;
    Node* _pNext;
public:
    Node(DataType data);
    void display();
};

template <class DataType>
class LinkedList {
    Node<DataType>* _pHead;
    Node<DataType>* _pTail;
    int _iSize;
    vector<string> _invalidData; // Mảng lưu trữ các giá trị không hợp lệ
public:
    LinkedList();
    ~LinkedList();

    void addTail(DataType data);
    void displayList();
    Node<DataType>* search(DataType data);
    void removeHead();
    void clear();
    void addValueList();
    vector<DataType> getListAsVector();
    bool isSubsequence(const vector<DataType>& small, const vector<DataType>& big);
    void createL3FromSubarray(LinkedList<DataType>& L1, LinkedList<DataType>& L2);
};

int main() {
    LinkedList<int> L1, L2, L3;

    cout << "Tao danh sach L1:" << endl;
    L1.addValueList();
    cout << "Tao danh sach L2:" << endl;
    L2.addValueList();

    L3.createL3FromSubarray(L1, L2);

    cout << "Danh sach L3:" << endl;
    L3.displayList();

    return 0;
}

/***********************************************************
* @Description Khởi tạo một Node mới có giá trị là data
***********************************************************/
template <class DataType>
Node<DataType>::Node(DataType data) {
    _data = data;
    _pNext = NULL;
}

/***********************************************************
* @Description Hiển thị giá trị của Node
***********************************************************/
template <class DataType>
void Node<DataType>::display() {
    cout << _data << " ";
}

/***********************************************************
* @Description Xóa phần tử ở đầu LinkedList
***********************************************************/
template <class DataType>
void LinkedList<DataType>::removeHead() {
    if (_pHead != NULL) {
        Node<DataType>* pTemp = _pHead;
        _pHead = _pHead->_pNext;
        delete pTemp;
        if (_pHead == NULL)
            _pTail = NULL;
        _iSize--;
    }
}

/***********************************************************
* @Description Khởi tạo LinkedList với các thành viên mặc định
***********************************************************/
template <class DataType>
LinkedList<DataType>::LinkedList() : _pHead(NULL), _pTail(NULL), _iSize(0) {}

/***********************************************************
* @Description Destructor - Xóa tất cả các Node trong LinkedList
***********************************************************/
template <class DataType>
LinkedList<DataType>::~LinkedList() {
    clear();
}

/***********************************************************
* @Description Thêm một phần tử vào cuối LinkedList
* @parameter data: Giá trị của phần tử cần thêm
***********************************************************/
template <class DataType>
void LinkedList<DataType>::addTail(DataType data) {
    Node<DataType>* pAdd = new Node<DataType>(data);
    if (_pHead == NULL) {
        _pHead = _pTail = pAdd;
    }
    else {
        _pTail->_pNext = pAdd;
        _pTail = pAdd;
    }
    _iSize++;
}

/***********************************************************
* @Description Xuất toàn bộ dữ liệu của LinkedList
***********************************************************/
template <class DataType>
void LinkedList<DataType>::displayList() {
    if (_pHead == NULL) {
        cout << "Danh sach rong." << endl;
        return;
    }
    Node<DataType>* pWalker = _pHead;
    cout << "Danh sach hien tai: ";
    while (pWalker != NULL) {
        pWalker->display(); // Gọi hàm display của Node để hiển thị dữ liệu của node
        pWalker = pWalker->_pNext; // Di chuyển đến node tiếp theo
    }
    cout << endl;
}

/***********************************************************
* @Description Xóa toàn bộ các Node trong LinkedList
***********************************************************/
template <class DataType>
void LinkedList<DataType>::clear() {
    while (_pHead != NULL)
        removeHead(); // Xóa từng Node từ đầu danh sách
}

/***********************************************************
* @Description Chuyển đổi LinkedList thành vector
* @return vector chứa các giá trị từ LinkedList
***********************************************************/
template <class DataType>
vector<DataType> LinkedList<DataType>::getListAsVector() {
    vector<DataType> result;
    Node<DataType>* pWalker = _pHead;
    while (pWalker != NULL) {
        result.push_back(pWalker->_data);
        pWalker = pWalker->_pNext;
    }
    return result;
}

/***********************************************************
* @Description Nhập giá trị cho danh sách từ người dùng
***********************************************************/
template <class DataType>
void LinkedList<DataType>::addValueList() {
    _invalidData.clear();

    bool validInput = false;
    while (!validInput) {
        cout << "Hay nhap cac so nguyen cho danh sach: ";
        string input;
        getline(cin, input);
        stringstream inputStream(input);
        DataType value;
        bool hasValidValue = false;
        string token;
        // Phân tích từng giá trị trong chuỗi nhập vào
        while (inputStream >> token) {
            stringstream ss(token);
            if (ss >> value && ss.eof()) {
                addTail(value);
                hasValidValue = true;
            } else {
                _invalidData.push_back(token); // Lưu trữ dữ liệu không hợp lệ
            }
        }
        if (hasValidValue) {
            validInput = true;
        } else {
            cout << "Ban phai nhap it nhat 1 gia tri hop le." << endl;
        }
    }
    cout << "Tao danh sach moi thanh cong." << endl;
    displayList();

    // In ra các dữ liệu không hợp lệ (nếu có)
    if (!_invalidData.empty()) {
        cout << "Du lieu khong hop le: ";
        for (const string& data : _invalidData) {
            cout << data << " ";
        }
        cout << endl;
    }
}

/***********************************************************
* @Description Kiểm tra một danh sách có chứa dãy con của danh sách khác không
* @parameter small: dãy con cần kiểm tra
* @parameter big: danh sách lớn để kiểm tra
* @return true nếu small là dãy con của big, ngược lại false
***********************************************************/
template <class DataType>
bool LinkedList<DataType>::isSubsequence(const vector<DataType>& small, const vector<DataType>& big) {
    if (small.empty()) return true;
    auto it = big.begin();
    for (int num : small) {
        it = find(it, big.end(), num);
        if (it == big.end()) return false;
        ++it;
    }
    return true;
}

/***********************************************************
* @Description Tạo LinkedList L3 từ các subarray chung của L1 và L2
* @parameter L1: LinkedList nguồn đầu tiên
* @parameter L2: LinkedList nguồn thứ hai
***********************************************************/
template <class DataType>
void LinkedList<DataType>::createL3FromSubarray(LinkedList<DataType>& L1, LinkedList<DataType>& L2) {
    vector<DataType> list1 = L1.getListAsVector();
    vector<DataType> list2 = L2.getListAsVector();

    for (size_t len = list1.size(); len > 0; --len) {
        for (size_t start = 0; start + len <= list1.size(); ++start) {
            vector<DataType> subarray(list1.begin() + start, list1.begin() + start + len);
            if (isSubsequence(subarray, list2)) {
                for (const DataType& item : subarray) {
                    addTail(item);
                }
                return;
            }
        }
    }
}
