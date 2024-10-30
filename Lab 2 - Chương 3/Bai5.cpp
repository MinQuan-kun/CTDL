#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <regex>

using namespace std;

// Cấu trúc để lưu trữ thông tin ngày tháng năm sinh
struct DateTime {
    int day, month, year;
};

// Lớp đại diện cho một sinh viên
class Student {
public:
    string id;          // Mã sinh viên
    string name;        // Tên sinh viên
    string className;   // Tên lớp học
    DateTime birthDate; // Ngày sinh
    float gpa;          // GPA

    // Constructor khởi tạo sinh viên với tất cả các thuộc tính
    Student(string id, string name, string className, DateTime birthDate, float gpa)
        : id(id), name(name), className(className), birthDate(birthDate), gpa(gpa) {}
};

// Lớp đại diện cho một nút trong danh sách liên kết
class Node {
public:
    Student data;  // Dữ liệu sinh viên
    Node* next;    // Con trỏ đến nút tiếp theo

    // Constructor khởi tạo nút với dữ liệu sinh viên
    Node(Student data) : data(data), next(nullptr) {}
};

// Lớp quản lý danh sách sinh viên
class StudentList {
private:
    Node* head;     // Con trỏ đến nút đầu tiên của danh sách
    Node* tail;     // Con trỏ đến nút cuối cùng của danh sách
    int size;       // Số lượng sinh viên trong danh sách

    // Hoán đổi dữ liệu của hai nút
    void swap(Node* a, Node* b) {
        Student temp = a->data;
        a->data = b->data;
        b->data = temp;
    }

    // Lấy nút tại chỉ số cụ thể
    Node* getNodeAt(int index) {
        Node* current = head;
        for (int i = 0; i < index && current != nullptr; ++i) {
            current = current->next;
        }
        return current;
    }

public:
    StudentList() : head(nullptr), tail(nullptr), size(0) {} // Constructor khởi tạo danh sách trống
    ~StudentList() { clear(); } // Destructor để xóa danh sách khi không sử dụng

    // Các phương thức của lớp
    void addStudent();
    void displayStudents();
    void displayHighGpaStudents();
    Node* searchStudentSequential(const string& id);
    void sortStudentsById();
    Node* searchStudentBinary(const string& id);
    void removeStudent(const string& id);
    void updateStudentGpa(const string& id);
    void clear();
    void displayMenu();
    void menuLoop();
    bool confirmExit();
    
    bool isValidId(const string& id);            // Kiểm tra mã sinh viên hợp lệ
    bool isValidDate(const string& dateStr, DateTime& date); // Kiểm tra ngày sinh hợp lệ
    bool isValidGpa(float gpa);                   // Kiểm tra GPA hợp lệ
    void inputStudent(Student& student);          // Nhập thông tin sinh viên
    void displayStudent(const Student& student);  // Hiển thị thông tin sinh viên
};

// Kiểm tra mã sinh viên hợp lệ
bool StudentList::isValidId(const string& id) {
    return regex_match(id, regex("^[0-9]{5}[A-Z]{2}[0-9]{4}$"));
}

// Kiểm tra ngày sinh hợp lệ
bool StudentList::isValidDate(const string& dateStr, DateTime& date) {
    stringstream ss(dateStr);
    string token;
    vector<int> dateParts;

    while (getline(ss, token, '/')) {
        dateParts.push_back(stoi(token));
    }

    if (dateParts.size() == 3) {
        date.day = dateParts[0];
        date.month = dateParts[1];
        date.year = dateParts[2];
        return true;
    }

    return false;
}

// Kiểm tra GPA hợp lệ
bool StudentList::isValidGpa(float gpa) {
    return gpa >= 0.0f && gpa <= 10.0f;
}

// Nhập thông tin sinh viên
void StudentList::inputStudent(Student& student) {
    string id, name, className, dateStr;
    DateTime birthDate;
    float gpa;

    // Nhập mã sinh viên và kiểm tra tính hợp lệ
    do {
        cout << "Nhập mã sinh viên (11 ký tự, định dạng 19211TT1234): ";
        getline(cin, id);
    } while (!isValidId(id));
    student.id = id;

    // Nhập tên sinh viên
    cout << "Nhập tên sinh viên: ";
    getline(cin, name);
    student.name = name;

    // Nhập lớp học
    cout << "Nhập lớp học: ";
    getline(cin, className);
    student.className = className;

    // Nhập ngày sinh và kiểm tra tính hợp lệ
    do {
        cout << "Nhập ngày sinh (DD/MM/YYYY): ";
        getline(cin, dateStr);
    } while (!isValidDate(dateStr, birthDate));
    student.birthDate = birthDate;

    // Nhập GPA và kiểm tra tính hợp lệ
    do {
        cout << "Nhập GPA (0-10): ";
        cin >> gpa;
        cin.ignore();
    } while (!isValidGpa(gpa));
    student.gpa = gpa;
}

// Hiển thị thông tin sinh viên
void StudentList::displayStudent(const Student& student) {
    cout << "Mã SV: " << student.id << ", Tên: " << student.name
        << ", Lớp: " << student.className << ", Ngày sinh: "
        << setw(2) << setfill('0') << student.birthDate.day << "/"
        << setw(2) << setfill('0') << student.birthDate.month << "/"
        << student.birthDate.year << ", GPA: " << student.gpa << endl;
}

// Thêm sinh viên vào danh sách
void StudentList::addStudent() {
    Student student("", "", "", { 0, 0, 0 }, 0.0f);
    inputStudent(student);

    Node* newNode = new Node(student);
    if (!head) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }
    size++;

    cout << "Đã thêm sinh viên thành công." << endl;
}

// Hiển thị tất cả sinh viên
void StudentList::displayStudents() {
    if (!head) {
        cout << "Danh sách sinh viên trống." << endl;
        return;
    }

    Node* current = head;
    while (current) {
        displayStudent(current->data);
        current = current->next;
    }
}

// Hiển thị sinh viên có GPA >= 5
void StudentList::displayHighGpaStudents() {
    if (!head) {
        cout << "Danh sách sinh viên trống." << endl;
        return;
    }

    Node* current = head;
    bool found = false;
    while (current) {
        if (current->data.gpa >= 5.0f) {
            displayStudent(current->data);
            found = true;
        }
        current = current->next;
    }

    if (!found) {
        cout << "Không có sinh viên nào có GPA >= 5." << endl;
    }
}

// Tìm sinh viên theo mã sử dụng tìm kiếm tuần tự
Node* StudentList::searchStudentSequential(const string& id) {
    Node* current = head;
    while (current) {
        if (current->data.id == id) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

// Sắp xếp sinh viên theo mã sử dụng thuật toán sắp xếp chọn
void StudentList::sortStudentsById() {
    if (!head) return;

    for (int i = 0; i < size - 1; ++i) {
        Node* minNode = getNodeAt(i);
        for (int j = i + 1; j < size; ++j) {
            Node* current = getNodeAt(j);
            if (current->data.id < minNode->data.id) {
                minNode = current;
            }
        }
        swap(getNodeAt(i), minNode);
    }
}

// Tìm sinh viên theo mã sử dụng tìm kiếm nhị phân
Node* StudentList::searchStudentBinary(const string& id) {
    sortStudentsById(); // Sắp xếp danh sách trước khi tìm kiếm nhị phân

    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        Node* midNode = getNodeAt(mid);
        if (midNode->data.id == id) {
            return midNode;
        }
        else if (midNode->data.id < id) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return nullptr;
}

// Xóa sinh viên khỏi danh sách
void StudentList::removeStudent(const string& id) {
    Node* current = head;
    Node* previous = nullptr;

    while (current && current->data.id != id) {
        previous = current;
        current = current->next;
    }

    if (!current) {
        cout << "Sinh viên với mã " << id << " không tồn tại." << endl;
        return;
    }

    if (!previous) {
        head = head->next;
        if (!head) {
            tail = nullptr;
        }
    }
    else {
        previous->next = current->next;
        if (!current->next) {
            tail = previous;
        }
    }

    delete current;
    size--;

    cout << "Đã xóa sinh viên thành công." << endl;
}

// Cập nhật GPA của sinh viên
void StudentList::updateStudentGpa(const string& id) {
    Node* studentNode = searchStudentSequential(id);
    if (!studentNode) {
        cout << "Sinh viên với mã " << id << " không tồn tại." << endl;
        return;
    }

    float newGpa;
    do {
        cout << "Nhập GPA mới (0-10): ";
        cin >> newGpa;
        cin.ignore();
    } while (!isValidGpa(newGpa));

    studentNode->data.gpa = newGpa;
    cout << "GPA của sinh viên đã được cập nhật thành công." << endl;
}

// Xóa tất cả sinh viên trong danh sách
void StudentList::clear() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    size = 0;
}

// Hiển thị menu lựa chọn
void StudentList::displayMenu() {
    system("cls"); // Xóa màn hình
    cout << "---------------------MENU---------------------" << endl;
    cout << "1. Thêm sinh viên" << endl;
    cout << "2. Hiển thị tất cả sinh viên" << endl;
    cout << "3. Hiển thị sinh viên có GPA >= 5" << endl;
    cout << "4. Tìm sinh viên (Tuần tự)" << endl;
    cout << "5. Sắp xếp sinh viên theo mã" << endl;
    cout << "6. Tìm sinh viên (Nhị phân)" << endl;
    cout << "7. Xóa sinh viên" << endl;
    cout << "8. Cập nhật GPA sinh viên" << endl;
    cout << "9. Xóa danh sách sinh viên" << endl;
    cout << "10. Thoát" << endl;
    cout << "----------------------------------------------" << endl;
}

// Vòng lặp menu để người dùng lựa chọn các chức năng
void StudentList::menuLoop() {
    while (true) {
        displayMenu();
        string choice;
        getline(cin, choice);

        switch (stoi(choice)) {
        case 1:
            addStudent();
            break;
        case 2:
            displayStudents();
            break;
        case 3:
            displayHighGpaStudents();
            break;
        case 4: {
            string id;
            cout << "Nhập mã sinh viên cần tìm: ";
            getline(cin, id);
            Node* student = searchStudentSequential(id);
            if (student) {
                displayStudent(student->data);
            }
            else {
                cout << "Sinh viên không tìm thấy." << endl;
            }
            break;
        }
        case 5:
            sortStudentsById();
            cout << "Đã sắp xếp sinh viên theo mã." << endl;
            break;
        case 6: {
            string id;
            cout << "Nhập mã sinh viên cần tìm: ";
            getline(cin, id);
            Node* student = searchStudentBinary(id);
            if (student) {
                displayStudent(student->data);
            }
            else {
                cout << "Sinh viên không tìm thấy." << endl;
            }
            break;
        }
        case 7: {
            string id;
            cout << "Nhập mã sinh viên cần xóa: ";
            getline(cin, id);
            removeStudent(id);
            break;
        }
        case 8: {
            string id;
            cout << "Nhập mã sinh viên để cập nhật GPA: ";
            getline(cin, id);
            updateStudentGpa(id);
            break;
        }
        case 9:
            clear();
            cout << "Đã xóa tất cả sinh viên." << endl;
            break;
        case 10:
            if (confirmExit()) {
                return;
            }
            break;
        default:
            cout << "Lựa chọn không hợp lệ. Vui lòng thử lại." << endl;
        }
    }
}

// Xác nhận việc thoát chương trình
bool StudentList::confirmExit() {
    string confirm;
    cout << "Bạn có chắc chắn muốn thoát? (có/không): ";
    getline(cin, confirm);
    return confirm == "có" || confirm == "y";
}

// Hàm chính của chương trình
int main() {
    StudentList studentList;
    studentList.menuLoop(); // Bắt đầu vòng lặp menu
    return 0;
}
