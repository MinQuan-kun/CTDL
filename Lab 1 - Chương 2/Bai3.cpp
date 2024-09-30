#include <iostream>
#include <windows.h>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#define MAX_SIZE 100 // Kích thước tối đa của mảng
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
    void getItems();
    bool isEmpty();
    bool isFull();
    bool contains(DataType data);
    void selectionSort();
    void add(DataType data);
    vector<int> binary_search(DataType data); // Tìm kiếm nhị phân
    void display();
    void clear();
    int getSize();
    bool getValidInput(DataType& input);
    bool isSorted(); // Kiểm tra xem mảng có được sắp xếp hay không
    bool compareArrays(DataType* arr1, DataType* arr2, int size); // So sánh hai mảng
};

// Hàm main
int main() {
    ArrayList<int> array;
    array.getItems();

    if (!array.isSorted()) {
        char choice;
        cout << "Mang nay chua sap xep, ban co muon sap xep khong? (y/n): ";
        cin >> choice;

        if (choice == 'n' || choice == 'N') {
            cout << "Hay nhap mot list da sap xep khac." << endl;
            return 0;
        }
        else if (choice == 'y' || choice == 'Y') {
            array.selectionSort();
        }
        else {
            cout << "Lua chon khong hop le. Ket thuc chuong trinh." << endl;
            return 0;
        }
    }

    array.display();

    int x;
    cout << "Nhap gia tri can tim: ";
    cin >> x;

    vector<int> result = array.binary_search(x);

    if (!result.empty()) {
        cout << "Gia tri x = " << x << " duoc tim thay tai vi tri " << result[0] << " trong mang." << endl;
        cout << "So lan chia doi mang la: " << result[1] - 1 << endl;
    }
    else {
        cout << "Khong tim thay gia tri x = " << x << " trong mang." << endl;
    }

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
 * @param Số phần tử tối đa của List
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
 * @return true nếu List rỗng, false nếu List khác rỗng
 *******************************************************************/
template <class DataType>
bool ArrayList<DataType>::isEmpty() {
    return _iSize == 0;
}

/*******************************************************************
 * @Description Kiểm tra List có đầy hay không
 * @return true nếu List đầy, false nếu List khác đầy
 *******************************************************************/
template <class DataType>
bool ArrayList<DataType>::isFull() {
    return _iSize == _iCapacity;
}

/*******************************************************************
 * @Description Thêm phần tử vào List
 * @param data Giá trị phần tử cần thêm
 *******************************************************************/
template <class DataType>
void ArrayList<DataType>::add(DataType data) {
    if (!isFull()) {
        _items[_iSize++] = data;
    }
}

/*******************************************************************
 * @Description Nhập các phần tử cho List
 *******************************************************************/
template <class DataType>
void ArrayList<DataType>::getItems() {
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
}

/*******************************************************************
 * @Description Kiểm tra List có chứa phần tử có giá trị data không
 * @param data Giá trị phần tử cần kiểm tra
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
 * @Description Sắp xếp List bằng thuật toán chọn
 *******************************************************************/
template <class DataType>
void ArrayList<DataType>::selectionSort() {
    for (int i = 0; i < _iSize - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < _iSize; ++j) {
            if (_items[j] < _items[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(_items[i], _items[minIndex]);
        }
    }
}

/*******************************************************************
 * @Description Tìm kiếm nhị phân các vị trí có giá trị data trong List
 * @param data Giá trị phần tử cần tìm
 * @return các vị trí có data và số lần chia đôi mảng
 *******************************************************************/
template <class DataType>
vector<int> ArrayList<DataType>::binary_search(DataType data) {
    int left = 0, right = _iSize - 1;
    int count = 0;
    vector<int> result;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        count++;



        if (_items[mid] == data) {
            result.push_back(mid);
            result.push_back(count);
            return result;
        }

        if (_items[mid] < data) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
        cout << "Lan " << count << ": x = " << data << " nam trong doan [" << left << ".." << right << "] // mid = " << mid << endl;
    }

    return result; // Không tìm thấy
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
 * @Description Trả về số phần tử hiện tại của List
 * @return Số phần tử hiện tại của List
 *******************************************************************/
template <class DataType>
int ArrayList<DataType>::getSize() {
    return _iSize;
}

/*******************************************************************
 * @Description Hàm hỗ trợ lấy đầu vào hợp lệ cho kiểu dữ liệu DataType
 * @param input Biến để lưu đầu vào hợp lệ
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

/*******************************************************************
 * @Description Kiểm tra xem mảng có được sắp xếp hay chưa
 * @return true nếu mảng đã được sắp xếp, false nếu chưa
 *******************************************************************/
template <class DataType>
bool ArrayList<DataType>::isSorted() {
    for (int i = 0; i < _iSize - 1; ++i) {
        if (_items[i] > _items[i + 1]) {
            return false;
        }
    }
    return true;
}

/*******************************************************************
 * @Description So sánh hai mảng
 * @param arr1 Mảng thứ nhất
 * @param arr2 Mảng thứ hai
 * @param size Kích thước của hai mảng
 * @return true nếu hai mảng giống nhau, false nếu khác nhau
 *******************************************************************/
template <class DataType>
bool ArrayList<DataType>::compareArrays(DataType* arr1, DataType* arr2, int size) {
    for (int i = 0; i < size; ++i) {
        if (arr1[i] != arr2[i]) {
            return false;
        }
    }
    return true;
}