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
    void removeDuplicates();
    void createL3Union(LinkedList<DataType>& L1, LinkedList<DataType>& L2);
    void createL3Difference(LinkedList<DataType>& L1, LinkedList<DataType>& L2);
    void createL3Intersection(LinkedList<DataType>& L1, LinkedList<DataType>& L2);
    bool checkForDuplicates(LinkedList<DataType>& L1, LinkedList<DataType>& L2);
    void removeFirstGreaterThanSum(LinkedList<DataType>& L2);
    void createL3sum(LinkedList<DataType>& L1, LinkedList<DataType>& L2);
    DataType findMaxInList();
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
    cout << "1. Tao danh sach L3 moi (L2 noi sau L1)" << endl;
    cout << "2. Tao danh sach L3 (L3 la hieu cua L1 và L2)" << endl;
    cout << "3. Tao danh sach L3 (L3 la giao cua L1 và L2)" << endl;
    cout << "4. Tao danh sach L3 (L3 la hop  cua L1 và L2) loai bo cac phan tu trung lap" << endl;
    cout << "5. Tao danh sach L3 la tong cua L1 va L2" << endl;
    cout << "6. Kiem tra danh sach L1, L2 co gia tri trung hay khong" << endl;
    cout << "7. Xoa phan tu dau tien duoc tim thay trong L1 (gia tri cua no lon hon tong gia tri phan tu trong L2)" << endl;
    cout << "8. Xoa tat ca cac phan tu trong L1 co gia tri bang gia tri lon nhat trong L2" << endl;
    cout << "9. In danh sach L3" << endl;
    cout << "10. Thoat" << endl;
    cout << "---------------------Bai2---------------------" << endl;
}
/*******************************************************************
 * @Description Xử lý từng chức năng của menu
 *******************************************************************/
template <class DataType>
void LinkedList<DataType>::menuLoop() {
    LinkedList<int> L1, L2, L3;
    L1.clear();
    L2.clear();
    cout << "Tao danh sach L1" << endl;
    L1.addValueList();
    cout << "Tao danh sach L2" << endl;
    L2.addValueList();
    Sleep(2000);
    DataType value;
    while (true) {
        displayMenu();
        L1.displayList();
        cout << "L1: " << endl;
        L2.displayList();
        cout << "L2: " << endl;
        cout << "Chon chuc nang (1-10): ";
        string choice;
        getline(cin, choice);
        if (choice.empty() || !isdigit(choice[0])) {
            cout << "Lua chon khong hop le. Vui long nhap lai." << endl;
            Sleep(2000);
            continue;
        }
        int choiceNum = stoi(choice);
        if (choiceNum < 1 || choiceNum > 10) {
            cout << "Lua chon khong hop le. Vui long nhap lai." << endl;
            Sleep(2000);
            continue;
        }
        switch (choiceNum) {
        case 1:
            L1.clear();
            L2.clear();
            cout << "Tao danh sach L1:" << endl;
            L1.addValueList();
            cout << "Tao danh sach L2:" << endl;
            L2.addValueList();
            L3.clear();
            L3.createL3Union(L2, L1);
            cout << "Danh sach L3: " << endl;
            L3.displayList();
            cout << "Tao danh sach moi thanh cong." << endl;
            Sleep(3000);
            break;
        case 2:
            L3.clear();
            L3.createL3Difference(L1, L2);
            cout << "Danh sach L3 (cac phan tu chi xuat hien trong L1):" << endl;
            L3.displayList();
            cout << "Tao danh sach moi thanh cong." << endl;
            Sleep(3000);
            break;
        case 3:
            L3.clear();
            L3.createL3Intersection(L1, L2);
            cout << "Danh sach L3 (cac phan tu xuat hien trong ca L1 va L2):" << endl;
            L3.displayList();
            cout << "Tao danh sach moi thanh cong." << endl;
            Sleep(3000);
            break;
        case 4:
            L3.clear();
            L3.createL3Union(L1, L2);
            L3.removeDuplicates();
            cout << "Danh sach L3: " << endl;
            L3.displayList();
            cout << "Tao danh sach moi thanh cong." << endl;
            Sleep(3000);
            break;
        case 5:
            L3.clear();
            L3.createL3sum(L1, L2);
            cout << "Danh sach L3 (tong cua L1 va L2):" << endl;
            L3.displayList();
            cout << "Tao danh sach moi thanh cong." << endl;
            Sleep(3000);
            break;
        case 6:
            if (checkForDuplicates(L1, L2)) {
                cout << "Danh sach L1 va L2 co gia tri trung nhau." << endl;
            }
            else {
                cout << "Danh sach L1 va L2 khong co gia tri trung nhau." << endl;
            }
            Sleep(3000);
            break;
        case 7:
            L1.removeFirstGreaterThanSum(L2);
            cout << "Da xoa phan tu thoa man dieu kien trong L1." << endl;
            L1.displayList();
            Sleep(3000);
            break;
        case 8:
            try {
                // Tìm giá trị lớn nhất trong L2
                DataType maxInL2 = L2.findMaxInList();
                // Xóa tất cả các phần tử trong L1 có giá trị bằng giá trị lớn nhất trong L2
                Node<DataType>* pWalker = L1._pHead;
                while (pWalker != NULL) {
                    Node<DataType>* pNext = pWalker->_pNext;
                    if (pWalker->_data == maxInL2) {
                        L1.remove(pWalker->_data);
                    }
                    pWalker = pNext;
                }
                cout << "Da xoa tat ca cac phan tu co gia tri bang " << maxInL2 << " trong L1." << endl;
                L1.displayList();
            }
            catch (const runtime_error& e) {
                cout << e.what() << endl;
            }
            Sleep(3000);
            break;
        case 9:
            L3.displayList();
            Sleep(3000);
            break;
        case 10:
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
/***********************************************************
* @Description Xóa tất cả các phần tử trùng lặp trong danh sách
***********************************************************/
template <class DataType>
void LinkedList<DataType>::removeDuplicates() {
    if (_pHead == NULL) {
        return;
    }
    Node<DataType>* pCurrent = _pHead;
    while (pCurrent != NULL) {
        Node<DataType>* pRunner = pCurrent;
        while (pRunner->_pNext != NULL) {
            if (pRunner->_pNext->_data == pCurrent->_data) {
                Node<DataType>* pTemp = pRunner->_pNext;
                pRunner->_pNext = pRunner->_pNext->_pNext;
                if (pTemp == _pTail) {
                    _pTail = pRunner;
                }
                delete pTemp;
                _iSize--;
            }
            else {
                pRunner = pRunner->_pNext;
            }
        }
        pCurrent = pCurrent->_pNext;
    }
    cout << "Da xoa tat ca cac phan tu lap lai trong danh sach." << endl;
}
/***********************************************************
 * @Description Tạo danh sách L3  (L2 nối L1)
 ***********************************************************/
template <class DataType>
void LinkedList<DataType>::createL3Union(LinkedList<DataType>& L1, LinkedList<DataType>& L2) {
    Node<DataType>* pWalker = L1._pHead;
    while (pWalker != NULL) {
        addTail(pWalker->_data);
        pWalker = pWalker->_pNext;
    }
    pWalker = L2._pHead;
    while (pWalker != NULL) {
        addTail(pWalker->_data);
        pWalker = pWalker->_pNext;
    }
}
/***********************************************************
 * @Description Tạo danh sách L3 là hiệu của L1 và L2
 ***********************************************************/
template <class DataType>
void LinkedList<DataType>::createL3Difference(LinkedList<DataType>& L1, LinkedList<DataType>& L2) {
    Node<DataType>* pWalker = L1._pHead;
    while (pWalker != NULL) {
        if (!L2.Existdata(pWalker->_data)) {
            addTail(pWalker->_data);
        }
        pWalker = pWalker->_pNext;
    }
}
/***********************************************************
 * @Description Tạo danh sách L3 là giao của L1 và L2
 ***********************************************************/
template <class DataType>
void LinkedList<DataType>::createL3Intersection(LinkedList<DataType>& L1, LinkedList<DataType>& L2) {
    Node<DataType>* pWalker = L1._pHead;
    while (pWalker != NULL) {
        if (L2.Existdata(pWalker->_data)) {
            addTail(pWalker->_data);
        }
        pWalker = pWalker->_pNext;
    }
}
/***********************************************************
 * @Description Tạo danh sách L3 là tổng của L1 và L2
 ***********************************************************/
template <class DataType>
void LinkedList<DataType>::createL3sum(LinkedList<DataType>& L1, LinkedList<DataType>& L2) {
    // Tìm độ dài lớn nhất giữa L1 và L2
    int maxLength = max(L1.GetSize(), L2.GetSize());
    // Con trỏ đến các nút đầu của L1 và L2
    Node<DataType>* pNodeL1 = L1._pHead;
    Node<DataType>* pNodeL2 = L2._pHead;
    // Duyệt qua các chỉ số từ 0 đến maxLength - 1
    for (int i = 0; i < maxLength; ++i) {
        // Lấy giá trị của phần tử tại chỉ số i của L1 và L2
        DataType valueL1 = (pNodeL1 != NULL) ? pNodeL1->_data : 0;
        DataType valueL2 = (pNodeL2 != NULL) ? pNodeL2->_data : 0;

        // Thêm tổng của các giá trị vào danh sách L3
        addTail(valueL1 + valueL2);

        // Di chuyển đến nút tiếp theo trong L1 và L2 nếu có
        if (pNodeL1 != NULL) pNodeL1 = pNodeL1->_pNext;
        if (pNodeL2 != NULL) pNodeL2 = pNodeL2->_pNext;
    }
}
/***********************************************************
*@Description Kiểm tra 2 danh sách có giá trị trùng hay không
* @return true nếu có giá trị trùng, ngược lại false
***********************************************************/
template <class DataType>
bool LinkedList<DataType>::checkForDuplicates(LinkedList<DataType>& L1, LinkedList<DataType>& L2) {
    Node<DataType>* pNodeL1 = L1._pHead;
    while (pNodeL1 != NULL) {
        if (L2.Existdata(pNodeL1->_data)) {
            return true; // Tìm thấy giá trị trùng
        }
        pNodeL1 = pNodeL1->_pNext;
    }
    return false; // Không tìm thấy giá trị trùng
}
/***********************************************************
 * @Description Xóa phần tử đầu tiên trong L1 lớn hơn tổng giá trị trong L2
 ***********************************************************/
template <class DataType>
void LinkedList<DataType>::removeFirstGreaterThanSum(LinkedList<DataType>& L2) {
    if (L2._pHead == NULL) {
        throw runtime_error("Danh sach L2 rong. Khong the tinh tong.");
    }
    // Tính tổng giá trị các phần tử trong danh sách L2
    DataType sum = 0;
    Node<DataType>* pNodeL2 = L2._pHead;
    while (pNodeL2 != NULL) {
        sum += pNodeL2->_data;
        pNodeL2 = pNodeL2->_pNext;
    }
    // Tìm và xóa phần tử đầu tiên trong L1 thỏa mãn điều kiện
    Node<DataType>* pNodeL1 = _pHead;
    while (pNodeL1 != NULL) {
        if (pNodeL1->_data > sum) {
            remove(pNodeL1->_data);
            cout << "Da xoa phan tu " << pNodeL1->_data << " trong L1." << endl;
            return; // Xóa phần tử đầu tiên thỏa mãn điều kiện
        }
        pNodeL1 = pNodeL1->_pNext;
    }
    cout << "Khong tim thay phan tu nao trong L1 thoa man dieu kien." << endl;
}
/************************************************************
* @Description Tìm phần tử lớn nhất trong List
* @return trả về phần tử lớn nhất
************************************************************/
template <class DataType>
DataType LinkedList<DataType>::findMaxInList() {
    if (_pHead == NULL) {
        throw runtime_error("Danh sach rong. Khong the tim gia tri lon nhat.");
    }
    DataType maxVal = _pHead->_data;
    Node<DataType>* pWalker = _pHead->_pNext;
    while (pWalker != NULL) {
        if (pWalker->_data > maxVal) {
            maxVal = pWalker->_data;
        }
        pWalker = pWalker->_pNext;
    }
    return maxVal;
}