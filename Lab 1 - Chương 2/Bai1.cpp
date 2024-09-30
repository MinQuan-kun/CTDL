#include <iostream>
#include <windows.h>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#define MAX_SIZE 100; // Kích thức tối đa của mảng
using namespace std;

// Khai báo lớp
template <class DataType>
class ArrayList {
private:
    DataType* _items;
    int _iSize;
    int _iCapacity;
    vector<string> _invalidItems; // Mảng lưu trữ các giá trị không hợp lệ
    
public:
    ArrayList();                    // Khởi tạo mặc định
    ArrayList(int maxSize);         // Khởi tạo list với giá trị maxsize
    ~ArrayList();                   // Hủy cấp phát bộ nhớ

    bool isEmpty();
    bool isFull();
    void add(DataType data);
    void insert(int index, DataType data);
    void removeAt(int index);
    void remove(DataType data);
    void removeAll(DataType data);  //chức năng xóa tất cả các phần tử có giá trị data
    bool contains(DataType data);
    int indexOf(DataType data);
    int lastIndexOf(DataType data);
    vector<int> sequential_search(DataType data); //tìm kiếm tuần tự
    void display();
    void clear();
    int getSize();
    void displayMenu();
    void menuLoop();
    bool confirmExit();
    string toLowerCase(const string& str);
    bool getValidInput(DataType& input);
};

int main() {
    ArrayList<int> array;
    array.menuLoop();
    return 0;
}
/******************************************************************* 
* @Description Hàm khởi tạo List rỗng có số phần tử tối đa là MAX_SIZE 
*******************************************************************/
template <class DataType>
ArrayList<DataType>::ArrayList() {
    _iCapacity = MAX_SIZE;
    _items = new DataType[_iCapacity];
    _iSize = 0;
}
/******************************************************************* 
 * @Description Constructor tạo List rỗng có số phần tử tối đa là maxSize
 * @parameter Số phần tử tối đa của List
 * @ Nếu maxSize <= 0 thì lấy giá trị mặc định là MAX_SIZE
 *******************************************************************/
template <class DataType>
ArrayList<DataType>::ArrayList(int maxSize) {
    _iCapacity = maxSize > 0 ? maxSize : MAX_SIZE;
    _items = new DataType[_iCapacity];
    _iSize = 0;
}
/******************************************************************* 
 * @Description Destructor hủy cấp phát bộ nhớ cho items
 *******************************************************************/
template <class DataType>
ArrayList<DataType>::~ArrayList() {
    delete[] _items;
}
/******************************************************************* 
 * @Description Kiểm tra List có rỗng hay không 
 * @return  true nếu List rỗng, false nếu List khác rỗng
 *******************************************************************/
template <class DataType>
bool ArrayList<DataType>::isEmpty() {
    if(_iSize == 0)
        return true;
    return false;
}
/******************************************************************* 
 * @Description Kiểm tra List có đầy hay không 
 * @return true nếu List rỗng, false nếu List khác rỗng
 *******************************************************************/
template <class DataType>
bool ArrayList<DataType>::isFull() {
    if(_iSize == _iCapacity)
        return true;
    return false;
}
/******************************************************************* 
 * @Description Thêm một phần tử vào cuối List 
 * @parament Giá trị của phần tử cần thêm
 * @attention Nếu List đầy thì thông báo ngoại lệ
 *******************************************************************/
template <class DataType>
void ArrayList<DataType>::add(DataType data) {
    if (!isFull()) {
        _items[_iSize] = data;
        _iSize++;
    }
    else {
        cout << "List day! Khong the them phan tu moi!" << endl;
    }
}
/******************************************************************* 
 * @Description Thêm một phần tử vào vị trí index trong List 
 * @parament index là vị trí cần chèn, data là giá trị cần thêm
 * @attention Nếu List đầy thì thông báo ngoại lệ
 *******************************************************************/
template <class DataType>
void ArrayList<DataType>::insert(int index, DataType data) {
    if (index >= 0 && index <= _iSize && !isFull()) {
        for (int i = _iSize; i > index; --i) {
            _items[i] = _items[i - 1];
        }
        _items[index] = data;
        _iSize++;
    }
    else {
        cout << "List day! Khong the them phan tu moi!" << endl;
    }
}
/******************************************************************* 
 * @Description Xóa một phần tử ở vị trí index trong list
 * @parament Vị trí cần xóa
 * @attention Nếu index >=size hoặc index < 0 thì thông báo ngoại lệ
 *******************************************************************/
template <class DataType>
void ArrayList<DataType>::removeAt(int index) {
    if (index >= 0 && index < _iSize && !isEmpty()) {
        for (int i = index + 1; i < _iSize; ++i) {
            _items[i - 1] = _items[i];
        }
        _iSize--;
    }
    else {
        cout << "Vi tri khong hop le" << endl;
    }
}
/******************************************************************* 
 * @Description Xóa một phần tử có giá trị data trong list
 * @parament Giá trị phần tử cần xóa
 *******************************************************************/
template <class DataType>
void ArrayList<DataType>::remove(DataType data) {
    int iIndex = indexOf(data);
    if (iIndex >= 0) {
        removeAt(iIndex);
    }
}
/******************************************************************* 
 * @Description Kiểm tra List có chứa phần tử có giá trị data không
 * @parament Giá trị phần tử cần xóa
 * @return true nếu có, false nếu không có
 *******************************************************************/
template <class DataType>
bool ArrayList<DataType>::contains(DataType data) {
    for (int i = 0; i < _iSize; ++i) {
        if (_items[i] == data) {
            return true;
        }
    }
    return false;
}
/******************************************************************* 
 * @Description Tìm vị trí đầu tiên có giá trị data trong List
 * @parament Giá trị phần tử cần tìm
 * @return Vị trí đầu tiên có giá trị data, -1 nếu không tìm thấy
 *******************************************************************/
template <class DataType>
int ArrayList<DataType>::indexOf(DataType data) {
    for (int i = 0; i < _iSize; ++i) {
        if (_items[i] == data) {
            return i;
        }
    }
    return -1;
}
/******************************************************************* 
 * @Description Tìm vị trí cuối cùng có giá trị data trong List
 * @parament Giá trị phần tử cần tìm
 * @return Vị trí cuối cùng có giá trị data, -1 nếu không tìm thấy
 *******************************************************************/
template <class DataType>
int ArrayList<DataType>::lastIndexOf(DataType data) {
    for (int i = _iSize - 1; i >= 0; --i) {
        if (_items[i] == data) {
            return i;
        }
    }
    return -1;
}
/******************************************************************* 
 * @Description Tìm tất cả vị trí có giá trị data trong List bằng phương pháp tuần tự
 * @parament Giá trị phần tử cần tìm
 * @return các vị trí có data
 *******************************************************************/
template <class DataType>
vector<int> ArrayList<DataType>::sequential_search(DataType data) {
    vector<int> indices;
    for (int i = 0; i < _iSize; ++i) {
        if (_items[i] == data) {
            indices.push_back(i);
        }
    }
    return indices;
}
/******************************************************************* 
 * @Description In danh sách
 *******************************************************************/
template <class DataType>
void ArrayList<DataType>::display() {
    for (int i = 0; i < _iSize; ++i) {
        cout << _items[i] << " ";
    }
    cout << endl;
}
/******************************************************************* 
 * @Description Hủy bỏ danh sách, các phần tử có giá trị mặc định là 0
 *******************************************************************/
template <class DataType>
void ArrayList<DataType>::clear() {
    _iSize = 0;
}
/******************************************************************* 
 * @Description Trả về số phần tử hiện tại của Stack
 * @return Số phần tử hiện tại của Stack
 *******************************************************************/
template <class DataType>
int ArrayList<DataType>::getSize() {
    return _iSize;
}
/******************************************************************* 
 * @Description Xóa hết tất cả phần tử có giá trị data
 *******************************************************************/
template <class DataType>
void ArrayList<DataType>::removeAll(DataType data) {
    while (contains(data)) {
        remove(data);
    }
}
/*******************************************************************
 * @Description Hiển thị menu
 *******************************************************************/
template <class DataType>
void ArrayList<DataType>::displayMenu() {
    system("cls"); // Xóa màn hình;
    cout << "---------------------MENU---------------------" << endl;
    cout << "1. Tao mang moi" << endl;
    cout << "2. Kiem tra list rong" << endl;
    cout << "3. Kiem tra list day" << endl;
    cout << "4. Them phan tu vao list" << endl;
    cout << "5. Them phan tu vao vi tri index" << endl;
    cout << "6. Xoa phan tu tai vi tri index" << endl;
    cout << "7. Xoa phan tu co gia tri x" << endl;
    cout << "8. Xoa tat ca cac phan tu co gia tri x" << endl;
    cout << "9. Tim vi tri dau tien co gia tri x" << endl;
    cout << "10. Tim vi tri cuoi cung co gia tri x" << endl;
    cout << "11. Tim tat ca vi tri co gia tri x" << endl;
    cout << "12. In danh sach" << endl;
    cout << "13. Xoa list" << endl;
    cout << "14. Kiem tra danh sach co chua phan tu x" << endl;
    cout << "15. Thoat" << endl;
    cout << "---------------------Bai1---------------------" << endl;
}
/******************************************************************* 
 * @Description Xử lý từng chức năng của menu
 *******************************************************************/
template <class DataType>
void ArrayList<DataType>::menuLoop() {
    int index;
    DataType data;
    while (true) {
        displayMenu();
        cout << "Chon chuc nang (1-15): ";
        string choice;
        getline(cin, choice);
        if (choice.empty() || !isdigit(choice[0])) {
            cout << "Lua chon khong hop le. Vui long nhap lai." << endl;
            Sleep(2000);
            continue;
        }
        int choiceNum = stoi(choice);
        if (choiceNum < 0 || choiceNum > 16) {
            cout << "Lua chon khong hop le. Vui long nhap lai." << endl;
            Sleep(2000);
            continue;
        }
        switch (choiceNum) {
            case 1: {
                int size;
                while (true) {
                    cout << "Nhap so luong phan tu: ";
                    string inputSize;
                    getline(cin, inputSize);
                    stringstream sizeStream(inputSize);
                    if (sizeStream >> size && sizeStream.eof() && size > 0) {
                        break;
                    }
                    cout << "So luong phan tu khong hop le. Vui long nhap lai." << endl;
                }
                delete[] _items;
                _items = new DataType[size];
                _iCapacity = size;
                _iSize = 0;
                _invalidItems.clear(); // Xóa các giá trị không hợp lệ trước khi nhập dữ liệu mới
                // Nhập giá trị cho mảng
                bool validInput = false;
                while (!validInput) {
                    cout << "Nhap cac phan tu cua mang (toi da " << size << " phan tu): ";
                    string input;
                    getline(cin, input);
                    stringstream inputStream(input);
                    DataType value;
                    // Phân tích từng giá trị trong chuỗi nhập vào
                    while (inputStream >> value) {
                        if (!isFull() && _iSize < size) {
                            add(value);
                            validInput = true; // Đảm bảo ít nhất một giá trị hợp lệ được nhập vào
                        }
                        else {
                            _invalidItems.push_back(to_string(value)); // Lưu giá trị không hợp lệ
                        }
                    }
                    if (!validInput) {
                        cout << "Ban phai nhap it nhat mot gia tri hop le." << endl;
                    }
                }
                // Hiển thị kết quả
                cout << "Mang da duoc tao: ";
                display();
                if (!_invalidItems.empty()) {
                    cout << "Cac gia tri khong hop le: ";
                    for (const auto& item : _invalidItems) {
                        cout << item << " ";
                    }
                    cout << endl;
                }
                Sleep(4000);
                break;
            }
            case 2:
                cout << (isEmpty() ? "List rong." : "List khong rong.") << endl;
                Sleep(3000);
                break;
            case 3:
                if (isEmpty()) {
                    cout << "Mang trong" << endl;
                    Sleep(2000);
                    break;
                }
                else {
                    cout << (isFull() ? "List day." : "List chua day.") << endl;
                    Sleep(3000);
                    break;
                }
            case 4:
                if (isEmpty()) {
                    cout << "Mang trong" << endl;
                    Sleep(2000);
                    break;
                }
                else {
                    cout << "Nhap gia tri phan tu can them: ";
                    if (getValidInput(data)) {
                        add(data);
                    }
                    cout << "Mang hien tai: ";
                    display();
                    Sleep(3000);
                    break;
                }
            case 5:
                if (isEmpty()) {
                    cout << "Mang trong" << endl;
                    Sleep(2000);
                    break;
                }
                else {
                    cout << "Nhap vi tri can chen: ";
                    if (getValidInput(index)) {
                        cout << "Nhap gia tri phan tu can chen: ";
                        if (getValidInput(data)) {
                            insert(index, data);
                        }
                    }
                    cout << "Mang hien tai: ";
                    display();
                    Sleep(3000);
                    break;
                }
            case 6:
                if (isEmpty()) {
                    cout << "Mang trong" << endl;
                    Sleep(2000);
                    break;
                }
                else {
                    cout << "Nhap vi tri phan tu can xoa: ";
                    if (getValidInput(index)) {
                        removeAt(index);
                    }
                    cout << "Mang hien tai: ";
                    display();
                    Sleep(3000);
                    break;
                }
            case 7:
                if (isEmpty()) {
                    cout << "Mang trong" << endl;
                    Sleep(2000);
                    break;
                }
                else {
                    while (true) {
                        cout << "Nhap gia tri phan tu can xoa: ";
                        DataType value;
                        cin >> value;
                        cin.ignore();
                        if (contains(value)) {
                            removeAll(value);
                            cout << "Tat ca phan tu co gia tri " << value << " da duoc xoa." << endl;
                            break;
                        }
                        else {
                            cout << "Khong tim thay gia tri " << value << " trong mang. Vui long nhap lai." << endl;
                        }
                    }
                cout << "Mang hien tai: ";
                display();
                Sleep(3000);
                break;
                }
            case 8:
                if (isEmpty()) {
                    cout << "Mang trong" << endl;
                    Sleep(2000);
                    break;
                }
                else {
                    cout << "Nhap gia tri phan tu can xoa tat ca: ";
                    if (getValidInput(data)) {
                        removeAll(data);
                    }
                    cout << "Mang hien tai: ";
                    display();
                    Sleep(3000);
                    break;
                }
            case 9:
                if (isEmpty()) {
                    cout << "Mang trong" << endl;
                    Sleep(2000);
                    break;
                }
                else {
                    cout << "Nhap gia tri phan tu can tim: ";
                    if (getValidInput(data)) {
                        index = indexOf(data);
                        if (index != -1) {
                            cout << "Vi tri dau tien co gia tri " << data << " la: " << index << endl;
                        }
                        else {
                            cout << "Khong tim thay phan tu co gia tri " << data << " trong list." << endl;
                        }
                    }              
                    cout << "Mang hien tai: ";
                    display();
                    Sleep(3000);
                    break;
                }   
            case 10:
                if (isEmpty()) {
                    cout << "Mang trong" << endl;
                    Sleep(2000);
                    break;
                }
                else {
                    cout << "Nhap gia tri phan tu can tim: ";
                    if (getValidInput(data)) {
                        index = lastIndexOf(data);
                        if (index != -1) {
                            cout << "Vi tri cuoi cung co gia tri " << data << " la: " << index << endl;
                        }
                        else {
                            cout << "Khong tim thay phan tu co gia tri " << data << " trong list." << endl;
                        }
                    }
                    Sleep(3000);
                    break;
                }
            case 11:
                if (isEmpty()) {
                    cout << "Mang trong" << endl;
                    Sleep(2000);
                    break;
                }   
                else {
                    DataType data;
                    cout << "Nhap gia tri can tim: ";
                    cin >> data;
                    cin.ignore();
                    vector<int> temp = sequential_search(data);
                    if (!temp.empty()) {
                        cout << "Cac vi tri tim thay: ";
                        for (int index : temp) {
                            cout << index << " ";
                        }
                        cout << endl;
                    } 
                    else {
                        cout << "Khong tim thay gia tri " << data << " trong mang" << endl;
                    }
                    cout << "Mang hien tai: ";
                    display();
                    Sleep(5000);
                    break;
                }
            case 12:
                if (isEmpty()) {
                    cout << "Mang trong" << endl;
                    Sleep(2000);
                    break;
                }
                else {
                    cout << "Danh sach cac phan tu trong list: ";
                    display();
                    Sleep(3000);
                    break;
                }
            case 13:
                if (isEmpty()) {
                    cout << "Mang trong" << endl;
                    Sleep(2000);
                    break;
                }
                else {
                    clear();
                    cout << "List da duoc xoa." << endl;
                    Sleep(3000);
                    break;
                }
            case 14:
                if (isEmpty()) {
                    cout << "Mang trong" << endl;
                    Sleep(2000);
                    break;
                }
                else {
                    cout << "Nhap gia tri phan tu can kiem tra: ";
                    if
                        (getValidInput(data)) {
                        if (contains(data)) {
                            cout << "Danh sach co chua phan tu co gia tri " << data << "." << endl;
                        }
                        else {
                            cout << "Danh sach khong chua phan tu co gia tri " << data << "." << endl;
                        }
                    }
                    Sleep(3000);
                    break;
                }
            case 15: {
                if (confirmExit()) {
                    return;
                }
                break;
            }

            default: {
                cout << "Lua chon khong hop le.Vui long chon lai.";
                Sleep(2000);
                break;
            }
        }   
    }
}
/******************************************************************* 
 * @Description Xác nhận thoát chương trình
 * @return true nếu chọn yes, false nếu chọn no
 *******************************************************************/
template <class DataType>
bool ArrayList<DataType>::confirmExit() {
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
string ArrayList<DataType>::toLowerCase(const string& str) {
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
bool ArrayList<DataType>::getValidInput(DataType& input) {
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