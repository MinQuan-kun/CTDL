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

    void addHead(DataType data);
    void addTail(DataType data);
    void addAfter(Node<DataType>* node, DataType data);
    Node<DataType>* search(DataType data);

    Node<DataType>* searchPre(Node<DataType>* node);
    void removeHead();
    void removeTail();
    void removeAfter(Node<DataType>* node);
    void remove(DataType data);

    bool Existdata(DataType data);
    void InterchangeSort();
    void selectionSort();
    int GetSize();
    void displayList();
    void clear();
    void displayMenu();
    void menuLoop();
    bool confirmExit();
    string toLowerCase(const string& str);
    bool getValidInput(DataType& input);
    void listPrimeNumbers();
    void calculateAverage();
    void findLastPerfectSquare();
    void findElementAtPosition(int k);
    void removeDuplicates();
    void findMinValue();
    void updatePerfectNumbers();
    void countOccurrences(DataType data);
    bool isPerfectNumber(DataType data);
    void removeAfterNode(DataType data);
    void addInSortedOrder(DataType data);
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
LinkedList<DataType>::~LinkedList() {}
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
* @Description Thêm một phần tử vào đầu LinkedList
* @parameter Giá trị của phần tử cần thêm
***********************************************************/
template <class DataType>
void LinkedList<DataType>::addHead(DataType data) {
    Node<DataType>* pAdd = new Node<DataType>(data);
    if (_pHead == NULL) {
        _pHead = _pTail = pAdd;
    }
    else {
        pAdd->_pNext = _pHead;
        _pHead = pAdd;
    }
    _iSize++;
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
* @Description Thêm một phần tử vào sau phần tử node trong LinkedList
* @parameter Phần tử node và giá trị của phần tử cần thêm
***********************************************************/
template <class DataType>
void LinkedList<DataType>::addAfter(Node<DataType>* node, DataType data) {
    Node<DataType>* pAdd = new Node<DataType>(data);
    if (node != NULL) {
        pAdd->_pNext = node->_pNext;
        node->_pNext = pAdd;
        if (node == _pTail)
            _pTail = pAdd;
    }
    else {
        addHead(data);
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
* @Description Tìm một phần tử đứng trước một phần tử trong LinkedList khi biết khóa
* @parameter Phần tử đứng trước phần tử cần tìm
* @return    Trả về phần tử được tìm thấy,NULL nếu không tìm thấy
***********************************************************/
template <class DataType>
Node<DataType>* LinkedList<DataType>::searchPre(Node<DataType>* node) {
    Node<DataType>* p = _pHead;
    if (p == node)
        return NULL;
    while ((p != NULL) && (p->_pNext != node))
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
* @Description Xóa phần tử ở cuối LinkedList
***********************************************************/
template <class DataType>
void LinkedList<DataType>::removeTail() {
    if (_pHead == NULL)
        return;
    if (_pHead == _pTail) {
        delete _pHead;
        _pHead = _pTail = NULL;
    }
    else {
        Node<DataType>* pTemp = _pTail;
        _pTail = searchPre(_pTail);
        delete pTemp;
        if (_pTail != NULL)
            _pTail->_pNext = NULL;
    }
    _iSize--;
}
/***********************************************************
* @Description Xóa phần tử ở cuối LinkedList
***********************************************************/
template <class DataType>
void LinkedList<DataType>::removeAfter(Node<DataType>* node) {
    Node<DataType>* pTemp;
    if (node != NULL) {
        pTemp = node->_pNext;
        if (pTemp != NULL) {
            if (pTemp == _pTail)
                _pTail = node;
            node->_pNext = pTemp->_pNext;
            delete pTemp;
        }
    }
    else
        removeHead();
    _iSize--;
}
/***********************************************************
* @Description Xóa phần tử sau 1 phần tử 
***********************************************************/
template <class DataType>
void LinkedList<DataType>::removeAfterNode(DataType q) {
    Node<DataType>* pNode = search(q);
    if (pNode == NULL) {
        cout << "Phan tu " << q << " khong ton tai trong danh sach." << endl;
        return;
    }
    removeAfter(pNode);
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
* @Description Sắp xếp danh sách theo thuật toán Interchange Sort
***********************************************************/
template <class DataType>
void LinkedList<DataType>::InterchangeSort() {
    if (_pHead == NULL || _pHead->_pNext == NULL) {
        return;
    }
    Node<DataType>* pSorted = NULL;
    Node<DataType>* pCurrent = _pHead; // Bắt đầu từ đầu danh sách
    while (pCurrent != NULL) {
        Node<DataType>* next = pCurrent->_pNext; // Lưu lại con trỏ tiếp theo
        if (pSorted == NULL || pSorted->_data >= pCurrent->_data) {
            // Chèn vào đầu danh sách đã sắp xếp
            pCurrent->_pNext = pSorted;
            pSorted = pCurrent;
        }
        else {
            // Tìm vị trí chèn vào giữa danh sách đã sắp xếp
            Node<DataType>* pTemp = pSorted;
            while (pTemp->_pNext != NULL && pTemp->_pNext->_data < pCurrent->_data) {
                pTemp = pTemp->_pNext;
            }
            pCurrent->_pNext = pTemp->_pNext;
            pTemp->_pNext = pCurrent;
        }
        pCurrent = next;
    }
    _pHead = pSorted; // Đặt lại đầu danh sách
}
/***********************************************************
* @Description Sắp xếp danh sách theo thuật toán Selection Sort
***********************************************************/
template <class DataType>
void LinkedList<DataType>::selectionSort() {
    Node<DataType>* pMin; //Trỏ đến pt có data min;
    Node<DataType>* p, * q;
    for (p = _pHead; p->_pNext != NULL; p = p->_pNext) {
        pMin = p;
        for (q = p->_pNext; q != NULL; q = q->_pNext)
            if (q->_data < pMin->_data)
                min = q;
        swap(pMin->_data, p->_data);
    }
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
    cout << "1. Tao danh sach moi" << endl;
    cout << "2. xuat danh sach ra man hinh" << endl;
    cout << "3. Liet ke cac so nguyen to co trong danh sach" << endl;
    cout << "4. Tinh trung binh cong cua cac phan tu trong danh sach" << endl;
    cout << "5. Dem so lan xuat hien cua mot so nguyen nhap tu ban phim co trong danh sach" << endl;
    cout << "6. Tim so chinh phuong cuoi cung trong danh sach" << endl;
    cout << "7. Tim va tra ve phan tu thu k trong danh sach tinh tu dau danh sach" << endl;
    cout << "8. Tim phan tu co gia tri nho nhat trong danh sach" << endl;
    cout << "9. Them mot phan tu vao sau phan tu q trong danh sach" << endl;
    cout << "10. Them mot phan tu vao danh sach sao cho phan tu them vao khong trung voi cac phan tu da co trong danh sach" << endl;
    cout << "11. Xoa k phan tu o dau danh sach (k nhap tu ban phim)" << endl;
    cout << "12. Xoa phan tu co gia tri bang x co trong danh sach" << endl;
    cout << "13. Xoa mot phan tu sau phan tu q trong danh sach" << endl;
    cout << "14. Xoa tat ca cac phan tu lap lai trong danh sach (chi giu lai duy nhat 1 phan tu)" << endl;
    cout << "15. Sap xep danh sach theo thu tu tang dan dung Interchange Sort" << endl;
    cout << "16. Them mot phan tu vao danh sach tang dan (Qua trinh them khong lam mat tinh tang dan cua danh sach)" << endl;
    cout << "17. Cap nhat cac so hoan thien trong danh sach" << endl;
    cout << "18. Thoat" << endl;
    cout << "---------------------Bai1---------------------" << endl;
}
/*******************************************************************
 * @Description Xử lý từng chức năng của menu
 *******************************************************************/
template <class DataType>
void LinkedList<DataType>::menuLoop() {
    while (true) {
        displayMenu();
        cout << "Chon chuc nang (1-18): ";
        string choice;
        getline(cin, choice);
        if (choice.empty() || !isdigit(choice[0])) {
            cout << "Lua chon khong hop le. Vui long nhap lai." << endl;
            Sleep(2000);
            continue;
        }
        int choiceNum = stoi(choice);
        if (choiceNum < 1 || choiceNum > 18) {
            cout << "Lua chon khong hop le. Vui long nhap lai." << endl;
            Sleep(2000);
            continue;
        }
        bool validInput = false;
        switch (choiceNum) {
        case 1:
            clear();
            validInput = false;
            while (!validInput) {
                cout << "Hay tao mot danh sach cac so nguyen : ";
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
            Sleep(2000);
            break;
        case 2:
            displayList();
            Sleep(2000);
            break;
        case 3:
            displayList();
            listPrimeNumbers();
            Sleep(2000);
            break;
        case 4:
            displayList();
            calculateAverage();
            Sleep(2000);
            break;
        case 5:
            displayList();
            cout << "Nhap so nguyen can dem so lan xuat hien: ";
            DataType numToCount;
            getValidInput(numToCount);
            countOccurrences(numToCount);
            Sleep(2000);
            break;
        case 6:
            displayList();
            findLastPerfectSquare();
            Sleep(2000);
            break;
        case 7:
            cout << "Nhap vi tri k cua phan tu can tim: ";
            int k;
            getValidInput(k);
            findElementAtPosition(k);
            Sleep(2000);
            break;
        case 8:
            displayList();
            findMinValue();
            Sleep(2000);
            break;
        case 9: {
            displayList();
            cout << "Nhap gia tri phan tu can them: ";
            DataType newData;
            getValidInput(newData);
            cout << "Nhap gia tri phan tu sau phan tu can them vao: ";
            DataType existingData;
            getValidInput(existingData);
            Node<DataType>* existingNode = search(existingData);
            if (existingNode != NULL) {
                addAfter(existingNode, newData);
                cout << "Them phan tu " << newData << " vao sau phan tu " << existingData << " thanh cong." << endl;
            }
            else {
                cout << "Phan tu " << existingData << " khong ton tai trong danh sach." << endl;
            }
            Sleep(2000);
            break;
        }
        case 10:
            displayList();
            cout << "Nhap gia tri phan tu can them: ";
            DataType uniqueData;
            getValidInput(uniqueData);
            if (!Existdata(uniqueData)) {
                addTail(uniqueData);
                cout << "Them phan tu thanh cong." << endl;
            }
            else {
                cout << "Phan tu da ton tai trong danh sach." << endl;
            }
            Sleep(2000);
            break;
        case 11:
            displayList();
            cout << "Nhap so phan tu can xoa: ";
            int kToDelete;
            getValidInput(kToDelete);
            for (int i = 0; i < kToDelete; ++i) {
                removeHead();
            }
            cout << "Xoa " << kToDelete << " phan tu o dau danh sach thanh cong." << endl;
            Sleep(2000);
            break;
        case 12:
            displayList();
            cout << "Nhap gia tri phan tu can xoa: ";
            DataType valueToDelete;
            getValidInput(valueToDelete);
            remove(valueToDelete);
            cout << "Xoa phan tu co gia tri " << valueToDelete << " thanh cong." << endl;
            Sleep(2000);
            break;
         case 13:
            cout << "Nhap gia tri phan tu q: ";
            DataType q;
            getValidInput(q);
            removeAfterNode(q);
            cout << "Xoa phan tu sau phan tu " << q << " thanh cong." << endl;
            Sleep(2000);
            displayList();
            break;
        case 14:
            removeDuplicates();
            cout << "Xoa cac phan tu lap lai thanh cong." << endl;
            displayList();
            Sleep(2000);
            break;
        case 15:
            InterchangeSort();
            cout << "Da sap xep danh sach tang dan." << endl;
            displayList();
            Sleep(2000);
            break;
        case 16:
            displayList();
            cout << "Nhap gia tri phan tu can them: ";
            DataType newData;
            getValidInput(newData);
            addInSortedOrder(newData);
            cout << "Them phan tu " << newData << " vao danh sach thanh cong." << endl;
            displayList();
            Sleep(2000);
            break;
        case 17:
            updatePerfectNumbers();
            cout << "Cap nhat cac so hoan thien thanh cong." << endl;
            displayList();
            Sleep(2000);
            break;
        case 18:
            if (confirmExit()) {
                cout << "Thoat chuong trinh." << endl;
                return;
            }
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
* @Description Liệt kê các số nguyên tố trong danh sách
***********************************************************/
template <class DataType>
void LinkedList<DataType>::listPrimeNumbers() {
    Node<DataType>* pWalker = _pHead;
    cout << "Cac so nguyen to trong danh sach: ";
    while (pWalker != NULL) {
        DataType number = pWalker->_data;
        if (number > 1) {
            bool isPrime = true;
            for (DataType i = 2; i <= sqrt(number); ++i) {
                if (number % i == 0) {
                    isPrime = false;
                    break;
                }
            }
            if (isPrime) {
                cout << number << " ";
            }
        }
        pWalker = pWalker->_pNext;
    }
    cout << endl;
}

/***********************************************************
* @Description Tính trung bình cộng của các phần tử trong danh sách
* @return Trung bình cộng của các phần tử
***********************************************************/
template <class DataType>
void LinkedList<DataType>::calculateAverage() {
    if (_pHead == NULL) {
        cout << "Danh sach rong." << endl;
        return;
    }

    DataType sum = 0;
    Node<DataType>* pWalker = _pHead;
    while (pWalker != NULL) {
        sum += pWalker->_data;
        pWalker = pWalker->_pNext;
    }
    double average = static_cast<double>(sum) / _iSize;
    cout << "Trung binh cong cua cac phan tu trong danh sach: " << average << endl;
}

/***********************************************************
* @Description Tìm số chính phương cuối cùng trong danh sách
* @return Giá trị số chính phương cuối cùng, hoặc thông báo nếu không tìm thấy
***********************************************************/
template <class DataType>
void LinkedList<DataType>::findLastPerfectSquare() {
    Node<DataType>* pWalker = _pHead;
    DataType lastPerfectSquare = -1;

    while (pWalker != NULL) {
        DataType number = pWalker->_data;
        if (number >= 0) {
            DataType root = static_cast<DataType>(sqrt(number));
            if (root * root == number) {
                lastPerfectSquare = number;
            }
        }
        pWalker = pWalker->_pNext;
    }

    if (lastPerfectSquare != -1) {
        cout << "So chinh phuong cuoi cung trong danh sach: " << lastPerfectSquare << endl;
    }
    else {
        cout << "Khong co so chinh phuong trong danh sach." << endl;
    }
}

/***********************************************************
* @Description Tìm và trả về phần tử thứ k trong danh sách tính từ đầu danh sách
* @param k Vị trí của phần tử cần tìm
* @return Giá trị phần tử tại vị trí k, hoặc thông báo nếu k không hợp lệ
***********************************************************/
template <class DataType>
void LinkedList<DataType>::findElementAtPosition(int k) {
    if (k < 1 || k > _iSize) {
        cout << "Vi tri khong hop le." << endl;
        return;
    }

    Node<DataType>* pWalker = _pHead;
    for (int i = 1; i < k; ++i) {
        pWalker = pWalker->_pNext;
    }
    cout << "Phan tu tai vi tri " << k << " la: " << pWalker->_data << endl;
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
* @Description Tìm giá trị nhỏ nhất trong danh sách
* @return Giá trị nhỏ nhất trong danh sách, hoặc thông báo nếu danh sách rỗng
***********************************************************/
template <class DataType>
void LinkedList<DataType>::findMinValue() {
    if (_pHead == NULL) {
        cout << "Danh sach rong." << endl;
        return;
    }
    DataType minValue = _pHead->_data;
    Node<DataType>* pWalker = _pHead->_pNext;

    while (pWalker != NULL) {
        if (pWalker->_data < minValue) {
            minValue = pWalker->_data;
        }
        pWalker = pWalker->_pNext;
    }
    cout << "Gia tri nho nhat trong danh sach: " << minValue << endl;
}
/***********************************************************
* @Description Cập nhật các số hoàn hảo trong danh sách
*              Các số hoàn hảo được tính lại (bạn có thể thay thế số hoàn hảo bằng giá trị khác nếu cần)
***********************************************************/
template <class DataType>
void LinkedList<DataType>::updatePerfectNumbers() {
    if (_pHead == NULL) {
        cout << "Danh sach rong." << endl;
        return;
    }
    Node<DataType>* pWalker = _pHead;
    while (pWalker != NULL) {
        if (isPerfectNumber(pWalker->_data)) {
            cout << "So hoan thien: " << pWalker->_data << endl;
        }
        pWalker = pWalker->_pNext;
    }
}
/***********************************************************
* @Description Kiểm tra số hoàn hảo
* @param number: số cần kiểm tra
* @return true nếu là số hoàn hảo, false nếu không
***********************************************************/
template <class DataType>
bool LinkedList<DataType>::isPerfectNumber(DataType number) {
    if (number <= 1) return false;

    DataType sum = 1; // Bắt đầu với 1 vì 1 luôn là ước số của bất kỳ số nguyên dương nào
    for (DataType i = 2; i <= number / 2; ++i) {
        if (number % i == 0) {
            sum += i;
        }
    }

    return sum == number;
}
/***********************************************************
 * @Description Đếm số lần xuất hiện của một số nguyên trong danh sách
 * @param numToCount Giá trị cần đếm số lần xuất hiện
 ***********************************************************/
template <class DataType>
void LinkedList<DataType>::countOccurrences(DataType numToCount) {
    int count = 0;
    Node<DataType>* pWalker = _pHead;
    while (pWalker != NULL) {
        if (pWalker->_data == numToCount) {
            count++;
        }
        pWalker = pWalker->_pNext;
    }
    cout << "So lan xuat hien cua " << numToCount << " trong danh sach la: " << count << endl;
    Sleep(200);
}/***********************************************************
 * @Description Thêm một phần tử vào danh sách tăng dần
 * @parameter Giá trị của phần tử cần thêm
 ***********************************************************/
template <class DataType>
void LinkedList<DataType>::addInSortedOrder(DataType data) {
    Node<DataType>* newNode = new Node<DataType>(data);
    if (_pHead == NULL) { // Nếu danh sách rỗng
        _pHead = _pTail = newNode;
    }
    else if (data <= _pHead->_data) { // Nếu thêm vào đầu danh sách
        newNode->_pNext = _pHead;
        _pHead = newNode;
    }
    else if (data >= _pTail->_data) { // Nếu thêm vào cuối danh sách
        _pTail->_pNext = newNode;
        _pTail = newNode;
    }
    else { // Nếu thêm vào giữa danh sách
        Node<DataType>* current = _pHead;
        while (current->_pNext != NULL && current->_pNext->_data < data) {
            current = current->_pNext;
        }
        newNode->_pNext = current->_pNext;
        current->_pNext = newNode;
    }
    _iSize++;
}