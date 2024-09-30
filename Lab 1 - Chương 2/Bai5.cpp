#include <iostream>
#include <windows.h>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#define MAX_SIZE 10 // Kích thước tối đa của bộ sưu tập sách

using namespace std;

// Lớp mẫu để đại diện cho một cuốn sách
template <class DataType>
class Book {
private:
    string _iCode;   // Mã sách
    string _iTitle;  // Tiêu đề sách
    int _iYear;      // Năm xuất bản
    int _iPrice;     // Giá sách

public:
    Book();                                                   // Khởi tạo mặc định
    Book(string code, string title, int year, int price);     // Khởi tạo với giá trị
    ~Book();                                                  // Hủy cấp phát bộ nhớ

    void input();              // Nhập thông tin sách
    void display() const;     // Hiển thị thông tin sách
    string getCode() const;   // Lấy mã sách
    string getTitle() const;  // Lấy tiêu đề sách
    int getYear() const;      // Lấy năm xuất bản
    int getPrice() const;     // Lấy giá sách
    void updatePrice(int newPrice); // Cập nhật giá sách
};

// Lớp mẫu để đại diện cho một thư viện
template <class DataType>
class Library {
private:
    int _capacity;           // Dung lượng thư viện
    vector<Book<DataType>> books; // Bộ sưu tập sách trong thư viện

public:
    Library() : _capacity(MAX_SIZE) {} // Khởi tạo thư viện với dung lượng tối đa
    void createNewLibrary(); // Tạo một thư viện mới với dung lượng mới
    bool isEmpty();  // Kiểm tra xem thư viện có rỗng không
    bool isFull();   // Kiểm tra xem thư viện có đầy không
    void addBook(const Book<DataType>& book); // Thêm một cuốn sách mới vào thư viện
    void removeBook(int index);  // Xóa một cuốn sách khỏi thư viện theo chỉ số
    typename vector<Book<DataType>>::iterator sequential_search(const string& data); // Tìm kiếm tuần tự theo tiêu đề
    int binary_search(const string& code); // Tìm kiếm nhị phân theo mã sách
    void SelectionSortByCode();  // Sắp xếp sách theo mã bằng cách sử dụng sắp xếp chọn
    void InsertionSortByYear();  // Sắp xếp sách theo năm xuất bản bằng cách sử dụng sắp xếp chèn
    void BubbleSortByTitle();    // Sắp xếp sách theo tiêu đề bằng cách sử dụng sắp xếp bong bóng
    void QuickSortByPrice(int left, int right); // Sắp xếp sách theo giá bằng cách sử dụng sắp xếp nhanh
    void displayMenu();  // Hiển thị các tùy chọn menu
    void libraryDisplay(); // Hiển thị tất cả sách trong thư viện
    void menuLoop();    // Xử lý các hoạt động của menu trong vòng lặp
    bool confirmExit(); // Xác nhận nếu người dùng muốn thoát chương trình
    void updateBookPrice(const string& title); // Cập nhật giá sách theo tiêu đề
    string toLowerCase(const string& str); // Chuyển chuỗi thành chữ thường
    int getSize();
};

// Main function
int main() {
    Library<int> lib;
    lib.menuLoop();
    return 0;
}

// Khởi tạo mặc định cho lớp Book
template <class DataType>
Book<DataType>::Book() {}

// Khởi tạo với giá trị cho lớp Book
template <class DataType>
Book<DataType>::Book(string code, string title, int year, int price)
    : _iCode(code), _iTitle(title), _iYear(year), _iPrice(price) {}

// Hủy cấp phát bộ nhớ cho lớp Book
template <class DataType>
Book<DataType>::~Book() {}

/*******************************************************************
 * @Description Nhập thông tin sách
 *******************************************************************/
template <class DataType>
void Book<DataType>::input() {
    while (true) {
        cout << "Nhap ma sach (toan bo 6 ki tu, bat dau bang 'LIB' va theo sau 3 so): ";
        getline(cin, _iCode);
        // Kiểm tra độ dài của mã sách
        if (_iCode.length() != 6) {
            cout << "Ma sach phai co 6 ki tu. Vui long nhap lai." << endl;
            continue;
        }
        // Kiểm tra phần đầu của mã sách
        if (_iCode.substr(0, 3) != "LIB") {
            cout << "Ma sach phai bat dau bang 'LIB'. Vui long nhap lai." << endl;
            continue;
        }
        // Kiểm tra các ký tự còn lại có phải là số không
        string numericPart = _iCode.substr(3, 3);
        if (!all_of(numericPart.begin(), numericPart.end(), ::isdigit)) {
            cout << "3 ki tu sau 'LIB' phai la so. Vui long nhap lai." << endl;
            continue;
        }
        // Nếu mã sách hợp lệ, thoát khỏi vòng lặp
        break;
    }
    // Nhập và kiểm tra tiêu đề sách
    while (true) {
        cout << "Nhap tieu de sach (toi da 30 ki tu): ";
        getline(cin, _iTitle);
        if (_iTitle.length() > 30) {
            cout << "Tieu de sach khong duoc vuot qua 30 ki tu. Vui long nhap lai." << endl;
        }
        else {
            break;
        }
    }
    // Nhập và kiểm tra năm xuất bản
    while (true) {
        cout << "Nhap nam xuat ban (lon hon 1900): ";
        cin >> _iYear;
        if (_iYear <= 1900) {
            cout << "Nam xuat ban phai lon hon 1900. Vui long nhap lai." << endl;
        }
        else {
            break;
        }
    }
    // Nhập và kiểm tra giá sách
    while (true) {
        cout << "Nhap gia sach (toi da 6 chu so): ";
        cin >> _iPrice;
        if (_iPrice < 0 || _iPrice > 999999) {
            cout << "Gia sach phai trong khoang 0 den 999999. Vui long nhap lai." << endl;
        }
        else {
            break;
        }
    }
    cin.ignore();
}

/*******************************************************************
 * @Description Hiển thị thông tin sách
 *******************************************************************/
template <class DataType>
void Book<DataType>::display() const {
    cout << "Ma sach: " << _iCode << endl;
    cout << "Tieu de: " << _iTitle << endl;
    cout << "Nam xuat ban: " << _iYear << endl;
    cout << "Gia: " << _iPrice << endl;
}

/*******************************************************************
 * @Description Lấy mã sách
 * @return Mã sách
 *******************************************************************/
template <class DataType>
string Book<DataType>::getCode() const {
    return _iCode;
}

/*******************************************************************
 * @Description Lấy tiêu đề sách
 * @return Tiêu đề sách
 *******************************************************************/
template <class DataType>
string Book<DataType>::getTitle() const {
    return _iTitle;
}

/*******************************************************************
 * @Description Lấy năm xuất bản
 * @return Năm xuất bản
 *******************************************************************/
template <class DataType>
int Book<DataType>::getYear() const {
    return _iYear;
}

/*******************************************************************
 * @Description Lấy giá sách
 * @return Giá sách
 *******************************************************************/
template <class DataType>
int Book<DataType>::getPrice() const {
    return _iPrice;
}

/*******************************************************************
 * @Description Cập nhật giá sách
 * @param newPrice Giá mới cho sách
 *******************************************************************/
template <class DataType>
void Book<DataType>::updatePrice(int newPrice) {
    _iPrice = newPrice;
}

/*******************************************************************
 * @Description Kiểm tra xem thư viện có rỗng không
 * @return true nếu thư viện rỗng, false nếu không
 *******************************************************************/
template <class DataType>
bool Library<DataType>::isEmpty() {
    return books.empty();
}

/*******************************************************************
 * @Description Kiểm tra xem thư viện có đầy không
 * @return true nếu thư viện đầy, false nếu không
 *******************************************************************/
template <class DataType>
bool Library<DataType>::isFull() {
    return books.size() >= _capacity;
}

/*******************************************************************
 * @Description Thêm một cuốn sách mới vào thư viện
 * @param book Cuốn sách mới để thêm vào thư viện
 *******************************************************************/
template <class DataType>
void Library<DataType>::addBook(const Book<DataType>& book) {
    if (isFull()) {
        cout << "Thu vien da day. Khong the them sach moi." << endl;
        return;
    }
    books.push_back(book);
}

/*******************************************************************
 * @Description Xóa một cuốn sách khỏi thư viện theo chỉ số
 * @param index Chỉ số của cuốn sách cần xóa
 *******************************************************************/
template <class DataType>
void Library<DataType>::removeBook(int index) {
    if (index >= 0 && index < books.size()) {
        books.erase(books.begin() + index);
        cout << "Sach da duoc xoa." << endl;
    }
    else {
        cout << "Chi so sach khong hop le." << endl;
    }
}

/*******************************************************************
 * @Description Tìm kiếm tuần tự theo tiêu đề
 * @param data Tiêu đề sách để tìm kiếm
 * @return Iterator trỏ đến cuốn sách nếu tìm thấy, nếu không thì trỏ đến end của vector
 *******************************************************************/
template <class DataType>
typename vector<Book<DataType>>::iterator Library<DataType>::sequential_search(const string& data) {
    for (auto it = books.begin(); it != books.end(); ++it) {
        if (toLowerCase(it->getTitle()) == toLowerCase(data)) {
            return it;
        }
    }
    return books.end();
}

/*******************************************************************
 * @Description Tìm kiếm nhị phân theo mã sách
 * @param code Mã sách để tìm kiếm
 * @return Chỉ số của cuốn sách nếu tìm thấy, nếu không thì -1
 *******************************************************************/
template <class DataType>
int Library<DataType>::binary_search(const string& code) {
    int left = 0;
    int right = books.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (books[mid].getCode() == code) {
            return mid;
        }
        else if (books[mid].getCode() < code) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1;
}

/*******************************************************************
 * @Description Sắp xếp sách theo mã bằng cách sử dụng sắp xếp chọn
 *******************************************************************/
template <class DataType>
void Library<DataType>::SelectionSortByCode() {
    int n = books.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (books[j].getCode() < books[minIndex].getCode()) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(books[i], books[minIndex]);
        }
    }
}

/*******************************************************************
 * @Description Sắp xếp sách theo năm xuất bản bằng cách sử dụng sắp xếp chèn
 *******************************************************************/
template <class DataType>
void Library<DataType>::InsertionSortByYear() {
    int n = books.size();
    for (int i = 1; i < n; ++i) {
        Book<DataType> key = books[i];
        int j = i - 1;
        while (j >= 0 && books[j].getYear() > key.getYear()) {
            books[j + 1] = books[j];
            --j;
        }
        books[j + 1] = key;
    }
}

/*******************************************************************
 * @Description Sắp xếp sách theo tiêu đề bằng cách sử dụng sắp xếp bong bóng
 *******************************************************************/
template <class DataType>
void Library<DataType>::BubbleSortByTitle() {
    int n = books.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (books[j].getTitle() > books[j + 1].getTitle()) {
                swap(books[j], books[j + 1]);
            }
        }
    }
}

/*******************************************************************
 * @Description Sắp xếp sách theo giá bằng cách sử dụng sắp xếp nhanh
 * @param left Vị trí trái của dãy cần sắp xếp
 * @param right Vị trí phải của dãy cần sắp xếp
 *******************************************************************/
template <class DataType>
void Library<DataType>::QuickSortByPrice(int left, int right) {
    if (left < right) {
        int pivot = books[right].getPrice();
        int i = left - 1;
        for (int j = left; j < right; ++j) {
            if (books[j].getPrice() <= pivot) {
                ++i;
                swap(books[i], books[j]);
            }
        }
        swap(books[i + 1], books[right]);
        int pi = i + 1;

        QuickSortByPrice(left, pi - 1);
        QuickSortByPrice(pi + 1, right);
    }
}

/*******************************************************************
 * @Description Tạo một thư viện mới với dung lượng mới
 *******************************************************************/
template <class DataType>
void Library<DataType>::createNewLibrary() {
    int newCapacity;
    cout << "Nhap dung luong moi cho thu vien: ";
    cin >> newCapacity;
    cin.ignore();
    if (newCapacity < 1) {
        cout << "Dung luong phai lon hon 0. Dung luong se duoc dat la 1." << endl;
        newCapacity = 1;
    }
    _capacity = newCapacity;
    books.clear();
    cout << "Thu vien da duoc tao moi voi dung luong " << _capacity << "." << endl;
}

/*******************************************************************
 * @Description Hiển thị tất cả sách trong thư viện
 *******************************************************************/
template <class DataType>
void Library<DataType>::libraryDisplay() {
    if (isEmpty()) {
        cout << "Thu vien hien tai trong." << endl;
        return;
    }
    for (size_t i = 0; i < books.size(); ++i) {
        cout << "Sach thu " << i + 1 << ":" << endl;
        books[i].display();
        cout << "-----------------" << endl;
    }
}

/*******************************************************************
 * @Description Cập nhật giá sách theo tiêu đề
 * @param title Tiêu đề sách để cập nhật giá
 *******************************************************************/
template <class DataType>
void Library<DataType>::updateBookPrice(const string& title) {
    auto it = sequential_search(title);
    if (it != books.end()) {
        int newPrice;
        cout << "Nhap gia moi cho sach '" << title << "': ";
        cin >> newPrice;
        it->updatePrice(newPrice);
        cout << "Gia sach da duoc cap nhat." << endl;
    }
    else {
        cout << "Sach co tieu de '" << title << "' khong ton tai trong thu vien." << endl;
    }
}

/*******************************************************************
 * @Description Chuyển chuỗi thành chữ thường
 * @param str Chuỗi đầu vào
 * @return Chuỗi đã chuyển thành chữ thường
 *******************************************************************/
template <class DataType>
string Library<DataType>::toLowerCase(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}
/*******************************************************************
 * @Description Hiển thị các tùy chọn menu
 *******************************************************************/
template <class DataType>
void Library<DataType>::displayMenu() {
    system("cls");
    cout << "---------------------MENU---------------------" << endl;
    cout << "1. Tao thu vien moi" << endl;
    cout << "2. Kiem tra thu vien co rong khong" << endl;
    cout << "3. Kiem tra thu vien co day khong" << endl;
    cout << "4. Them sach vao thu vien" << endl;
    cout << "5. Tim va xoa sach khoi thu vien" << endl;
    cout << "6. Tim va chinh sua gia cua sach" << endl;
    cout << "7. Sap xep danh sach theo ma sach" << endl;
    cout << "8. Sap xep danh sach theo nam xuat ban" << endl;
    cout << "9. Sap xep danh sach theo tua sach" << endl;
    cout << "10. Sap xep danh sach theo gia" << endl;
    cout << "11. Thoat" << endl;
    cout << "---------------------Bai5---------------------" << endl;
}
/*******************************************************************
 * @Description Xử lý các hoạt động của menu trong vòng lặp
 *******************************************************************/
template <class DataType>
void Library<DataType>::menuLoop() {
    while (true) {
        displayMenu();
        cout << "Chon chuc nang (1-11): ";
        string choice;
        getline(cin, choice);
        if (choice.empty() || !isdigit(choice[0])) {
            cout << "Lua chon khong hop le. Vui long nhap lai." << endl;
            Sleep(2000);
            continue;
        }
        int choiceNum = stoi(choice);
        if (choiceNum < 1 || choiceNum > 11) {
            cout << "Lua chon khong hop le. Vui long nhap lai." << endl;
            Sleep(2000);
            continue;
        }
        switch (choiceNum) {
        case 1: {
            createNewLibrary();
            Sleep(3000); 
            break;
        }
        case 2:
            cout << (isEmpty() ? "Thu vien rong" : "Thu vien khong rong") << endl;
            Sleep(3000);
            break;
        case 3:
            cout << (isFull() ? "Thu vien day" : "Thu vien chua day") << endl;
            Sleep(3000);
            break;
        case 4: {
            Book<DataType> newBook;
            newBook.input();
            addBook(newBook);
            Sleep(3000);
            break;
        }
        case 5: {
            cout << "Nhap ma sach de xoa: ";
            string code;
            getline(cin, code);
            int index = binary_search(code);
            if (index != -1) {
                removeBook(index);
            }
            else {
                cout << "Khong tim thay sach." << endl;
            }
            Sleep(3000);
            break;
        }
        case 6: {
            cout << "Nhap tua de sach de tim va sua gia: ";
            string title;
            getline(cin, title);
            updateBookPrice(title);
            Sleep(3000);
            break;
        }
        case 7:
            SelectionSortByCode();
            for (const auto& book : books) {
                book.display();
            }
            Sleep(3000);
            break;
        case 8:
            InsertionSortByYear();
            for (const auto& book : books) {
                book.display();
            }
            Sleep(3000);
            break;
        case 9: {
            BubbleSortByTitle();
            for (const auto& book : books) {
                book.display();
            }
            Sleep(3000);
            break;
        }
        case 10: {
            QuickSortByPrice(0, books.size() - 1);
            for (const auto& book : books) {
                book.display();
            }
            Sleep(3000);
            break;
        }
        case 11:
            if (confirmExit()) {
                return;
            }
            break;
        default: {
            cout << "Lua chon khong hop le. Vui long chon lai." << endl;
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
bool Library<DataType>::confirmExit() {
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