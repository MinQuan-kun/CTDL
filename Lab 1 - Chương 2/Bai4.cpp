#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // for sort and transform
#include <iomanip>   // for setw
using namespace std;

const int STU_ID_LEN = 11;
const int MAX_COURSE_CREDITS = 5;
const int MAX_COURSE_SCORE = 10;

class Course {
public:
    string courseCode;
    string courseName;
    int credits;
    float score;

    Course() : credits(0), score(0.0f) {}
};

class Student {
public:
    string studentID;
    string fullName;
    string birthDate; // format: dd/mm/yyyy
    vector<Course> courses;

    float getAverageScore() const;
    bool isEligibleForScholarship() const;
    void input();
    void display() const;
};

class StudentManagement {
private:
    vector<Student> students;

public:
    void addStudents();
    void searchAndEditStudent();
    void insertionSortByName();
    void binarySearchAndDelete();
    void selectionSortByAvgScore();
    void displayScholarshipStudents();
    void quickSortByBirthDate();
    void displayStudents();
};

float Student::getAverageScore() const {
    float totalScore = 0;
    int totalCredits = 0;
    for (const auto& course : courses) {
        totalScore += course.score * course.credits;
        totalCredits += course.credits;
    }
    return totalCredits ? totalScore / totalCredits : 0;
}

bool Student::isEligibleForScholarship() const {
    if (getAverageScore() < 7.0) return false;
    for (const auto& course : courses) {
        if (course.score < 5) return false;
    }
    return true;
}

void Student::input() {
    cout << "Nhập mã sinh viên (11 ký tự): ";
    cin >> studentID;
    cin.ignore();

    while (studentID.length() != STU_ID_LEN) {
        cout << "Mã sinh viên phải đúng 11 ký tự. Nhập lại: ";
        getline(cin, studentID);
    }

    cout << "Nhập họ tên: ";
    getline(cin, fullName);

    cout << "Nhập ngày sinh (dd/mm/yyyy): ";
    getline(cin, birthDate);

    int numCourses;
    cout << "Nhập số lượng môn học: ";
    cin >> numCourses;
cin.ignore(); // Ignore newline left in the buffer

    for (int j = 0; j < numCourses; ++j) {
        Course course;
        cout << "Nhập mã môn học: ";
        getline(cin, course.courseCode);
        cout << "Nhập tên môn học: ";
        getline(cin, course.courseName);
        cout << "Nhập số tín chỉ (<= 5): ";
        cin >> course.credits;
        while (course.credits <= 0 || course.credits > MAX_COURSE_CREDITS) {
            cout << "Số tín chỉ không hợp lệ, phải <= 5. Nhập lại: ";
            cin >> course.credits;
        }
        cout << "Nhập điểm môn học (0-10): ";
        cin >> course.score;
        while (course.score < 0 || course.score > MAX_COURSE_SCORE) {
            cout << "Điểm không hợp lệ (0-10). Nhập lại: ";
            cin >> course.score;
        }
        cin.ignore();

        courses.push_back(course);
    }
}

void Student::display() const {
    cout << "Mã sinh viên: " << studentID << endl;
    cout << "Họ tên: " << fullName << endl;
    cout << "Ngày sinh: " << birthDate << endl;
    cout << "Điểm trung bình: " << fixed << setprecision(2) << getAverageScore() << endl;
    cout << "Danh sách môn học:" << endl;
    for (const auto& course : courses) {
        cout << "  Mã môn: " << course.courseCode << ", Tên môn: " << course.courseName
             << ", Số tín chỉ: " << course.credits << ", Điểm: " << course.score << endl;
    }
    cout << endl;
}

void StudentManagement::addStudents() {
    int n;
    cout << "Nhập số lượng sinh viên: ";
    cin >> n;
    cin.ignore(); // Ignore newline left in the buffer

    for (int i = 0; i < n; ++i) {
        Student student;
        student.input();
        students.push_back(student);
    }
}

void StudentManagement::searchAndEditStudent() {
    string studentID, newFullName;
    cout << "Nhập mã sinh viên cần tìm: ";
    getline(cin, studentID);
    cout << "Nhập họ tên mới: ";
    getline(cin, newFullName);

    for (auto& student : students) {
if (student.studentID == studentID) {
            student.fullName = newFullName;
            cout << "Đã cập nhật họ tên sinh viên." << endl;
            return;
        }
    }
    cout << "Không tìm thấy sinh viên có mã " << studentID << "." << endl;
}

void StudentManagement::insertionSortByName() {
    for (size_t i = 1; i < students.size(); ++i) {
        Student key = students[i];
        int j = i - 1;
        while (j >= 0 && students[j].fullName < key.fullName) {
            students[j + 1] = students[j];
            --j;
        }
        students[j + 1] = key;
    }
    cout << "Đã sắp xếp danh sách sinh viên theo họ tên giảm dần." << endl;
}

void StudentManagement::binarySearchAndDelete() {
    string fullName;
    cout << "Nhập họ tên sinh viên cần xóa: ";
    getline(cin, fullName);

    insertionSortByName(); // Sắp xếp danh sách trước khi tìm kiếm nhị phân

    int low = 0, high = students.size() - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (students[mid].fullName == fullName) {
            students.erase(students.begin() + mid);
            cout << "Đã xóa sinh viên " << fullName << "." << endl;
            return;
        } else if (students[mid].fullName < fullName) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    cout << "Không tìm thấy sinh viên có họ tên " << fullName << "." << endl;
}

void StudentManagement::selectionSortByAvgScore() {
    for (size_t i = 0; i < students.size() - 1; ++i) {
        size_t minIndex = i;
        for (size_t j = i + 1; j < students.size(); ++j) {
            if (students[j].getAverageScore() < students[minIndex].getAverageScore()) {
                minIndex = j;
            }
        }
        swap(students[i], students[minIndex]);
    }
    cout << "Đã sắp xếp danh sách sinh viên theo điểm trung bình tăng dần." << endl;
}

void StudentManagement::displayScholarshipStudents() {
cout << "Danh sách sinh viên được học bổng:" << endl;
    for (const auto& student : students) {
        if (student.isEligibleForScholarship()) {
            cout << student.fullName << endl;
        }
    }
}

int partition(vector<Student>& students, int low, int high) {
    string pivot = students[high].birthDate; // Chọn ngày sinh cuối làm pivot
    int i = low - 1;
    for (int j = low; j <= high - 1; ++j) {
        if (students[j].birthDate < pivot) {
            ++i;
            swap(students[i], students[j]);
        }
    }
    swap(students[i + 1], students[high]);
    return i + 1;
}

void quickSort(vector<Student>& students, int low, int high) {
    if (low < high) {
        int pi = partition(students, low, high);
        quickSort(students, low, pi - 1);
        quickSort(students, pi + 1, high);
    }
}

void StudentManagement::quickSortByBirthDate() {
    quickSort(students, 0, students.size() - 1);
    cout << "Đã sắp xếp danh sách sinh viên theo năm sinh tăng dần." << endl;
}

void StudentManagement::displayStudents() {
    for (const auto& student : students) {
        student.display();
    }
}

void printMenu() {
    cout << "--- MENU ---" << endl;
    cout << "1. Nhập danh sách sinh viên" << endl;
    cout << "2. Tìm và sửa họ tên sinh viên theo mã" << endl;
    cout << "3. Sắp xếp sinh viên theo họ tên giảm dần" << endl;
    cout << "4. Tìm và xóa sinh viên theo họ tên" << endl;
    cout << "5. Sắp xếp sinh viên theo điểm trung bình tăng dần" << endl;
    cout << "6. Hiển thị danh sách sinh viên được học bổng" << endl;
    cout << "7. Sắp xếp sinh viên theo năm sinh tăng dần" << endl;
    cout << "8. Hiển thị danh sách sinh viên" << endl;
    cout << "9. Thoát" << endl;
}

void executeChoice(StudentManagement& sm) {
    int choice;
    cout << "Nhập lựa chọn: ";
    cin >> choice;
    cin.ignore(); // Ignore newline left in the buffer

    switch (choice) {
    case 1:
        sm.addStudents();
        break;
    case 2:
        sm.searchAndEditStudent();
        break;
    case 3:
        sm.insertionSortByName();
        sm.displayStudents();
        break;
    case 4:
        sm.binarySearchAndDelete();
        sm.displayStudents();
        break;
    case 5:
        sm.selectionSortByAvgScore();
        sm.displayStudents();
        break;
    case 6:
        sm.displayScholarshipStudents();
        break;
    case 7:
        sm.quickSortByBirthDate();
        sm.displayStudents();
        break;
    case 8:
        sm.displayStudents();
        break;
    case 9:
        cout << "Thoát chương trình." << endl;
        exit(0);
    default:
        cout << "Lựa chọn không hợp lệ!" << endl;
        break;
    }
}

int main() {
    StudentManagement sm;
    while (true) {
        printMenu();
        executeChoice(sm);
    }
    return 0;
}
