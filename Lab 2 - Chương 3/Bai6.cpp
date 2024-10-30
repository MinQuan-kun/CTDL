
#include <iostream>
#include <windows.h>
#include <string>
#include <sstream>
#include <algorithm>
#include <variant>
#include <vector>

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

using DataType = std::variant<int, double, string, char>;

template <class DataType>
class LinkedList {
    Node<DataType>* _pHead;
    Node<DataType>* _pTail;
    int _iSize;
    vector<string> _invalidData;
public:
    LinkedList();
    ~LinkedList();
    
    void addValueList();
    void addTail(DataType data);
    void removeHead();
    bool remove(DataType data);
    void removeValue();
    void searchValue();
    bool search(DataType data);
    bool Existdata(DataType data);
    int GetSize();
    void displayList();
    void clear();
    void displayMenu();
    void menuLoop();
    bool isEmpty();
    bool confirmExit();
    string toLowerCase(const string& str);
    bool getValidInput(DataType& input);
};

int main() {
    LinkedList<DataType> myList;
    myList.menuLoop();
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
* @Description Hiện thị giá trị Node
***********************************************************/
template <class DataType>
void Node<DataType>::display() {
    std::visit([](auto&& arg) { std::cout << arg << " "; }, _data);
}

/***********************************************************
* @Description Khởi tạo mặc định
***********************************************************/
template <class DataType>
LinkedList<DataType>::LinkedList() : _pHead(NULL), _pTail(NULL), _iSize(0) {}

/***********************************************************
* @Description Destructor
***********************************************************/
template <class DataType>
LinkedList<DataType>::~LinkedList() {
    clear();
}

/**********************************************************
 * @Description Nhập giá trị cho danh sách
 *********************************************************/
template <class DataType>
void LinkedList<DataType>::addValueList() {
    string input;
    bool hasValidInput = false;
    do {
        cout << "Hay nhap cho danh sach: ";
        getline(cin, input);
        stringstream inputStream(input);
        DataType value;
        hasValidInput = false;
        while (inputStream >> input) {
            if (getValidInput(value)) {
                addTail(value);
                hasValidInput = true;
            } else {
                _invalidData.push_back(input); // Lưu trữ dữ liệu không hợp lệ
            }
        }
        if (!hasValidInput) {
            cout << "Ban phai nhap it nhat 1 gia tri hop le." << endl;
        } else {
            cout << "Them gia tri thanh cong." << endl;
        }
    } while (!hasValidInput);

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
    Sleep(2000);
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
    cout << "Danh sach hien tai ";
    while (pWalker != NULL) {
        pWalker->display();
        pWalker = pWalker->_pNext;
    }
    cout << endl;
}

/***********************************************************
* @Description Kiểm tra có phần tử data trong danh sách không
* @return true nếu tìm ra, ngược lại false;
***********************************************************/
template <class DataType>
bool LinkedList<DataType>::Existdata(DataType data) {
    return search(data);
}

/***********************************************************
* @Description Thêm một phần tử vào cuối LinkedList
* @parameter Giá trị của phần tử cần thêm
***********************************************************/
template <class DataType>
void LinkedList<DataType>::addTail(DataType data) {
    Node<DataType>* pAdd = new Node<DataType>(data);
    if (_pHead == NULL) {
        _pHead = _pTail = pAdd;
    } else {
        _pTail->_pNext = pAdd;
        _pTail = pAdd;
    }
    _iSize++;
}

/***********************************************************
* @Description Xóa phần tử ở đầu LinkedList
***********************************************************/
template <class DataType>
void LinkedList<DataType>::removeHead() {
    if (_pHead != NULL) {
        Node<DataType>* pTeamp = _pHead;
        _pHead = _pHead->_pNext;
        delete pTeamp;
        if (_pHead == NULL)
            _pTail = NULL;
        _iSize--;
    }
}

/***********************************************************
* @Description Xóa toàn bộ LinkedList
***********************************************************/
template <class DataType>
void LinkedList<DataType>::clear() {
    while (_pHead != NULL)
        removeHead();
}

/***********************************************************
* @Description Lấy số lượng phần tử có trong LinkedList
* @return Trả về số phần tử có trong LinkedList
***********************************************************/
template <class DataType>
int LinkedList<DataType>::GetSize() {
    return _iSize;
}

/***********************************************************
* @Description Hiện thị menu lựa chọn chức năng
***********************************************************/
template <class DataType>
void LinkedList<DataType>::displayMenu() {
    system("cls"); // Xóa màn hình;
    cout << "---------------------MENU---------------------" << endl;
    cout << "1. Them gia tri vao danh sach" << endl;
    cout << "2. Xoa gia tri khoi danh sach" << endl;
    cout << "3. Tim gia tri trong danh sach" << endl;
    cout << "4. Hien thi danh sach" << endl;
    cout << "5. Xoa toan bo danh sach" << endl;
    cout << "6. Thoat" << endl;
    cout << "---------------------Bai6---------------------" << endl;
}

/*******************************************************************
 * @Description Xử lý từng chức năng của menu
 *******************************************************************/
template <class DataType>
void LinkedList<DataType>::menuLoop() {
    while (true) {
        displayMenu();
        string choice;
        cout << "Chon chuc nang (1-6): ";
        getline(cin, choice);
        if (choice.empty() || !isdigit(choice[0])) {
            cout << "Lua chon khong hop le. Vui long nhap lai." << endl;
            Sleep(2000);
            continue;
        }
        int choiceNum = stoi(choice);
        if (choiceNum < 1 || choiceNum > 6) {
            cout << "Lua chon khong hop le. Vui long nhap lai." << endl;
            Sleep(2000);
            continue;
        }
        
        switch (choiceNum) {
            case 1: 
                addValueList();
                break;
            case 2: 
                removeValue();
                break;
            case 3: 
                searchValue();
                break;
            case 4: 
                displayList();
                break;
            case 5: 
                clear();
                cout << "Danh sach da duoc xoa." << endl;
                break;
            case 6: 
                if (confirmExit()) 
                    return;
                break;
            default: 
                cout << "Lua chon khong hop le. Vui long nhap lai." << endl;
                Sleep(2000);
                break;
        }
    }
}

/*******************************************************************
 * @Description Xác nhận thoát chương trình
 * @return true nếu chọn yes, false nếu chọn no
 *******************************************************************/
template <class DataType>
bool LinkedList<DataType>::confirmExit() {
    string confirm;
    while (true) {
        cout << "Chac chan? (yes/no): ";
        cin >> confirm;
        confirm = toLowerCase(confirm); // Chuyển đổi thành chữ thường
        if (confirm == "yes") {
            return true; // Xác nhận thoát
        }
        else if (confirm == "no") {
            return false; // Không thoát, quay lại menu
        }
        else {
            cout << "Chon 'yes' hoac 'no' thoi. " << endl;
        }
    }
}

/*******************************************************************
 * @Description Chuyển các chữ in hoa về thành chữ thường
 *******************************************************************/
template <class DataType>
string LinkedList<DataType>::toLowerCase(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

template <class DataType>
bool LinkedList<DataType>::isEmpty() {
    return _pHead == nullptr;
}

// Hàm xóa một giá trị bất kỳ trong danh sách
template <class DataType>
void LinkedList<DataType>::removeValue() {
    DataType value;
    cout << "Nhap gia tri can xoa: ";
    if (getValidInput(value)) {
        if (remove(value)) {
            cout << "Da xoa gia tri khoi danh sach." << endl;
        } else {
            cout << "Gia tri khong ton tai trong danh sach." << endl;
        }
    }
    Sleep(2000);
}

/***********************************************************
* @Description Tìm một phần tử trong LinkedList khi biết khóa
* @parameter Giá tri khóa của phần tử cần tìm
* @return    Trả về phần tử được tìm thấy, NULL nếu không tìm thấy
***********************************************************/
template <class DataType>
bool LinkedList<DataType>::search(DataType data) {
    Node<DataType>* current = _pHead;
    while (current != nullptr) {
        if (current->_data == data) {
            return true;
        }
        current = current->_pNext;
    }
    return false;
}

/***********************************************************
* @Description Xóa phần tử có khóa là data trong LinkedList
***********************************************************/
template <class DataType>
bool LinkedList<DataType>::remove(DataType data) {
    Node<DataType>* current = _pHead;
    Node<DataType>* prev = nullptr;
    while (current != nullptr && current->_data != data) {
        prev = current;
        current = current->_pNext;
    }
    if (current == nullptr) {
        return false; // Không tìm thấy
    }
    if (prev == nullptr) {
        _pHead = current->_pNext;
    } else {
        prev->_pNext = current->_pNext;
    }
    delete current;
    _iSize--;
    return true;
}

// Hàm tìm kiếm một giá trị trong danh sách
template <class DataType>
void LinkedList<DataType>::searchValue() {
    DataType value;
    cout << "Nhap gia tri can tim: ";
    if (getValidInput(value)) {
        if (search(value)) {
            std::visit([](auto&& arg) { std::cout << "Gia tri " << arg << " ton tai trong danh sach." << endl; }, value);
        } else {
            std::visit([](auto&& arg) { std::cout << "Gia tri " << arg << " khong ton tai trong danh sach." << endl; }, value);
        }
    }
    Sleep(2000);
}

/*******************************************************************
 * @Description Hàm hỗ trợ lấy đầu vào hợp lệ cho kiểu dữ liệu DataType
 * @parament input biến để lưu đầu vào hợp lệ
 * @return true nếu đầu vào hợp lệ, false nếu không
 *******************************************************************/
template <class DataType>
bool LinkedList<DataType>::getValidInput(DataType& input) {
    if (std::holds_alternative<int>(input)) {
        int value;
        cin >> value;
        if (!cin.fail()) {
            input = value;
            return true;
        }
    } else if (std::holds_alternative<double>(input)) {
        double value;
        cin >> value;
        if (!cin.fail()) {
            input = value;
            return true;
        }
    } else if (std::holds_alternative<string>(input)) {
        string value;
        cin.ignore();
        getline(cin, value);
        if (!value.empty()) {
            input = value;
            return true;
        }
    } else if (std::holds_alternative<char>(input)) {
        char value;
        cin >> value;
        if (!cin.fail() && cin.get() == '\n') {
            input = value;
            return true;
        }
    }
    return false;
}

// Bài này e làm đại :<