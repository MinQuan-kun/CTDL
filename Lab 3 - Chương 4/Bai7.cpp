#include <iostream>
#include <sstream>
using namespace std;

template<class DataType>
class Stack {
private:
    DataType* _pData;
    int _iSize;
    int _iCapacity;

    void resize() {
        _iCapacity *= 2;
        DataType* tmp = new DataType[_iCapacity];
        for (int i = 0; i < _iSize; i++) {
            tmp[i] = _pData[i];
        }
        delete[] _pData;
        _pData = tmp;
    }

public:
    Stack() {
        _pData = new DataType[10];
        _iSize = 0;
        _iCapacity = 10;
    }

    ~Stack() {
        delete[] _pData;
    }

    void push(DataType value) {
        if (_iSize == _iCapacity) {
            resize();
        }
        _pData[_iSize++] = value;
    }

    DataType top() const {
        if (_iSize > 0) {
            return _pData[_iSize - 1];
        }
        cout << "Stack rỗng!" << endl;
        return DataType();
    }

    void pop() {
        if (_iSize > 0) {
            _iSize--;
        }
        else {
            cout << "Stack rỗng!" << endl;
        }
    }

    bool empty() const {
        return _iSize == 0;
    }

    int getSize() const {
        return _iSize;
    }
};

template<typename T>
string toString(const T& value) {
    ostringstream oss;
    oss << value;
    return oss.str();
}

int main() {
    Stack<string> stringStack;
    string input;
    string type;

    cout << "Nhap so luong phan tu: ";
    int count;
    cin >> count;
    cin.ignore();  // Đọc ký tự newline còn sót lại

    for (int i = 0; i < count; ++i) {
        cout << "Nhap kieu du lieu (int, double, string): ";
        getline(cin, type);

        cout << "Nhap gia tri: ";
        getline(cin, input);

        if (type == "int") {
            int intValue = stoi(input);
            stringStack.push(toString(intValue));
        }
        else if (type == "double") {
            double doubleValue = stod(input);
            stringStack.push(toString(doubleValue));
        }
        else if (type == "string") {
            stringStack.push(input);
        }
        else {
            cout << "Kieu du lieu khong hop le" << endl;
        }
    }

    cout << "Cac phan tu trong Stack:" << endl;
    while (!stringStack.empty()) {
        cout << "Phan tu tren cung Stack: " << stringStack.top() << endl;
        stringStack.pop();
    }

    return 0;
}
