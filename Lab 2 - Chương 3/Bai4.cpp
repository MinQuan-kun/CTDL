#include <iostream>
#include <windows.h>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
using namespace std;

template<class DataType>
class LinkedList;
template <class DataType>
class Node {
    // khai báo lớp bạn với lớp linkedlist
    friend LinkedList<DataType>;
private:
    //Thành phần dữ liệu của Node
    DataType _data;
    //Con trỏ trỏ đến Node kế tiếp
    Node* _pNext;
public:
    // khởi tạo node mới có dữ liệu là data
    Node(DataType data);
    //Hiển thị dữ liệu của node
    void display();
};
template <class DataType>
class LinkedList {
    Node<DataType>* _pHead;
    Node<DataType>* _pTail;
    int _iSize;
    vector<string> _invalidData; //Mảng lưu trữ các giá trị không hợp lệ
public:
    LinkedList();
    ~LinkedList();

    void addValueList();
    void addTail(DataType data);
    Node<DataType>* search(DataType data);
    void removeHead();
    void remove(DataType data);

    bool Existdata(DataType data);
    int GetSize();
    void displayList();
    void clear();
    void displayMenu();
    void menuLoop();
    bool confirmExit();
    string toLowerCase(const string& str);
    bool getValidInput(DataType& input);
};

int main() {
    LinkedList<int> list;
    list.menuLoop();
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
* @Description Hiện thị giá trị Node
***********************************************************/
template <class DataType>
void Node<DataType>::display() {
    cout << _data << " ";
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
    bool validInput = false;
    validInput = false;
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
            }
            else {
                _invalidData.push_back(token);
            }
        }
        if (hasValidValue) {
            validInput = true;
        }
        else {
            cout << "Ban phai nhap it nhat 1 gia tri hop le." << endl;
        }
    }
    cout << "Tao danh sach moi thanh cong." << endl;
    displayList();
    // In ra các dữ liệu không hợp lệ (nếu có)
    if (!_invalidData.empty())
        cout << "Du lieu khong hop le: ";
    for (const string& data : _invalidData)
        cout << data << " ";
    cout << endl;
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
        pWalker->display(); // Gọi hàm display của Node để hiển thị dữ liệu của node
        pWalker = pWalker->_pNext; // Di chuyển đến node tiếp theo
    }
    cout << endl;
}
/***********************************************************
* @Description Kiểm tra có phần tử data trong danh sách không
* @return true nếu tìm ra, ngược lại false;
***********************************************************/
template <class DataType>
bool LinkedList<DataType>::Existdata(DataType data) {
    if (search(data) != NULL)
        return true;
    return false;
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
    }
    else {
        _pTail->_pNext = pAdd;
        _pTail = pAdd;
    }
    _iSize++;
}
/***********************************************************
* @Description Tìm một phần tử trong LinkedList khi biết khóa
* @parameter Giá tri khóa của phần tử cần tìm
* @return    Trả về phần tử được tìm thấy,NULL nếu không tìm thấy
***********************************************************/
template <class DataType>
Node<DataType>* LinkedList<DataType>::search(DataType data) {
    Node<DataType>* p = _pHead;
    while ((p != NULL) && (p->_data != data))
        p = p->_pNext;
    return p;
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
* @Description Xóa phần tử có khóa là data trong LinkedList
***********************************************************/
template <class DataType>
void LinkedList<DataType>::remove(DataType data) {
    Node<DataType>* pWalker = _pHead, * pTemp = NULL;
    while ((pWalker != NULL) && (pWalker->_data != data)) {
        pTemp = pWalker;
        pWalker = pWalker->_pNext;
    }
    if (pWalker == NULL)
        return;
    if (pTemp != NULL) {
        if (pWalker == _pTail) {
            _pTail = pTemp;
            _pTail->_pNext = NULL;
        }
        pTemp->_pNext = pWalker->_pNext;
        delete pWalker;
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
* @return      Trả về số phần tử có trong LinkedList
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
    DataType value;
    while (true) {
        displayMenu();
        string choice;
        getline(cin, choice);
        if (choice.empty() || !isdigit(choice[0])) {
            cout << "Lua chon khong hop le. Vui long nhap lai." << endl;
            Sleep(2000);
            continue;
        }
        int choiceNum = stoi(choice);
        if (choiceNum < 1 || choiceNum > 7) {
            cout << "Lua chon khong hop le. Vui long nhap lai." << endl;
            Sleep(2000);
            continue;
        }
        switch (choiceNum) {
            case 1: {
                string type;
                cout << "Hay chon kieu du lieu cho gia tri ban muon nhap (int/char/double/string): ";
                cin >> type;
                cin.ignore();
                if (type == "int") {
                    LinkedList<int> intList;
                    intList.addValueList();
                } 
                else if (type == "char") {
                    LinkedList<char> charList;
                    charList.addValueList();
                }   
                else if (type == "double") {
                    LinkedList<double> doubleList;
                    doubleList.addValueList();
                }   
                else if (type == "string") {
                    LinkedList<string> stringList;
                    stringList.addValueList();
                } 
                else {
                cout << "Kieu du lieu khong hop le!" << endl;
                }
                Sleep(3000);
                break;
            }
            case 2: {
                string type;
                cout << "Hay chon kieu du lieu cho gia tri ban muon xoa (int/char/double/string): ";
                cin >> type;
                cin.ignore(); // Đọc ký tự newline còn lại sau cin
                if (type == "int") {
                    LinkedList<int> intList;
                    cout << "Nhap gia tri can xoa: ";
                    int value;
                    cin >> value;
                    cin.ignore(); // Đọc ký tự newline còn lại sau cin
                    intList.remove(value);
                    intList.displayList();
                } 
                else if (type == "char") {
                    LinkedList<char> charList;
                    cout << "Nhap gia tri can xoa: ";
                    char value;
                    cin >> value;
                    cin.ignore(); // Đọc ký tự newline còn lại sau cin
                    charList.remove(value);
                    charList.displayList();
                } 
                else if (type == "double") {
                    LinkedList<double> doubleList;
                    cout << "Nhap gia tri can xoa: ";
                    double value;
                    cin >> value;
                    cin.ignore(); // Đọc ký tự newline còn lại sau cin
                    doubleList.remove(value);
                    doubleList.displayList();
                } 
                else if (type == "string") {
                    LinkedList<string> stringList;
                    cout << "Nhap gia tri can xoa: ";
                    string value;
                    getline(cin, value);
                    stringList.remove(value);
                    stringList.displayList();
                } 
                else {
                    cout << "Kieu du lieu khong hop le!" << endl;
                }   
                Sleep(3000);
                break;
            }
            case 3: {
                string type;
                cout << "Hay chon kieu du lieu cho gia tri ban muon tim (int/char/double/string): ";
                cin >> type;
                cin.ignore(); // Đọc ký tự newline còn lại sau cin
            
                if (type == "int") {
                    LinkedList<int> intList;
                    cout << "Nhap gia tri can tim: ";
                    int value;
                    cin >> value;
                    cin.ignore(); // Đọc ký tự newline còn lại sau cin
                    Node<int>* result = intList.search(value);
                    if (result) {
                        cout << "Gia tri " << value << " da duoc tim thay trong danh sach." << endl;
                    } 
                    else {
                        cout << "Gia tri " << value << " khong ton tai trong danh sach." << endl;
                    }
                }  
                else if (type == "char") {
                    LinkedList<char> charList;
                    cout << "Nhap gia tri can tim: ";
                    char value;
                    cin >> value;
                    cin.ignore(); // Đọc ký tự newline còn lại sau cin
                    Node<char>* result = charList.search(value);
                    if (result) {
                        cout << "Gia tri '" << value << "' da duoc tim thay trong danh sach." << endl;
                    } 
                    else {
                        cout << "Gia tri '" << value << "' khong ton tai trong danh sach." << endl;
                    }
                }   
                else if (type == "double") {
                    LinkedList<double> doubleList;
                    cout << "Nhap gia tri can tim: ";
                    double value;
                    cin >> value;
                    cin.ignore(); // Đọc ký tự newline còn lại sau cin
                    Node<double>* result = doubleList.search(value);
                    if (result) {
                        cout << "Gia tri " << value << " da duoc tim thay trong danh sach." << endl;
                    }
                    else {
                        cout << "Gia tri " << value << " khong ton tai trong danh sach." << endl;
                    }
                } 
                else if (type == "string") {
                    LinkedList<string> stringList;
                    cout << "Nhap gia tri can tim: ";
                    string value;
                    getline(cin, value);
                    Node<string>* result = stringList.search(value);
                    if (result) {
                        cout << "Gia tri \"" << value << "\" da duoc tim thay trong danh sach." << endl;
                    }   
                    else {
                        cout << "Gia tri \"" << value << "\" khong ton tai trong danh sach." << endl;
                    }
                } 
                else {
                    cout << "Kieu du lieu khong hop le!" << endl;
                }
                Sleep(3000);
                break;
            }
        case 4:
            string type;
            cout << "Hay chon kieu du lieu cho danh sach ban muon hien thi (int/char/double/string): ";
            cin >> type;
            cin.ignore(); // Đọc ký tự newline còn lại sau cin
            
            if (type == "int") {
                LinkedList<int> intList;
                intList.displayList();
            } else if (type == "char") {
                LinkedList<char> charList;
                charList.displayList();
            } else if (type == "double") {
                LinkedList<double> doubleList;
                doubleList.displayList();
            } else if (type == "string") {
                LinkedList<string> stringList;
                stringList.displayList();
            } else {
                cout << "Kieu du lieu khong hop le!" << endl;
            }
            Sleep(3000);
            break;
        }
        case 5: {
            string type;
            cout << "Hay chon kieu du lieu cho danh sach ban muon xoa toan bo (int/char/double/string): ";
            cin >> type;
            cin.ignore(); // Đọc ký tự newline còn lại sau cin
            
            if (type == "int") {
                LinkedList<int> intList;
                intList.clear();
                cout << "Danh sach int da duoc xoa toan bo." << endl;
            } else if (type == "char") {
                LinkedList<char> charList;
                charList.clear();
                cout << "Danh sach char da duoc xoa toan bo." << endl;
            } else if (type == "double") {
                LinkedList<double> doubleList;
                doubleList.clear();
                cout << "Danh sach double da duoc xoa toan bo." << endl;
            } else if (type == "string") {
                LinkedList<string> stringList;
                stringList.clear();
                cout << "Danh sach string da duoc xoa toan bo." << endl;
            } else {
                cout << "Kieu du lieu khong hop le!" << endl;
            }
            Sleep(3000);
            break;
        }
        case 6:
            if (confirmExit()) {
                cout << "Thoat chuong trinh." << endl;
                return;
            }
            break;
        default:
            cout << "Lua chon khong hop le. Vui long nhap lai." << endl;
            Sleep(3000);
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
/*******************************************************************
 * @Description Hàm hỗ trợ lấy đầu vào hợp lệ cho kiểu dữ liệu DataType
 * @parament input biến để lưu đầu vào hợp lệ
 * @return true nếu đầu vào hợp lệ, false nếu không
 *******************************************************************/
template <class DataType>
bool LinkedList<DataType>::getValidInput(DataType& input) {
    string line;
    while (getline(cin, line)) {
        stringstream ss(line);
        if (ss >> input) {
            return true;
        }
        else {
            cout << "Gia tri khong hop le. Vui long nhap lai: ";
        }
    }
    return false;
}