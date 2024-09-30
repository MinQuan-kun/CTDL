#include <iostream>
#include <string>
using namespace std;

struct Guest {
    string _strName;
    int _iSeat;

    Guest() : _strName(""), _iSeat(0) {}

    Guest(string strName, int iSeat) : _strName(strName), _iSeat(iSeat) {}

    void Set(string strName, int iSeat) {
        _strName = strName;
        _iSeat = iSeat;
    }

    friend ostream& operator<<(ostream& os, const Guest& obj) {
        os << obj._strName << " " << obj._iSeat;
        return os;
    }
};

template <class DataType> 
class Node {
public:
    DataType _data;
    Node<DataType>* _pNext;

    Node() : _pNext(nullptr) {}
    Node(DataType data) : _data(data), _pNext(nullptr) {}
};

template <class DataType>
class List {
private:
    Node<DataType>* _pHead; 
public:
    List() : _pHead(nullptr) {}

    ~List() {
        while (!_IsEmpty()) {
            _Dequeue();
        }
    }

    void _Push(DataType value) {
        Node<DataType>* pNewNode = new Node<DataType>(value);
        if (_pHead == nullptr) {
            _pHead = pNewNode;
        } else {
            Node<DataType>* pTmp = _pHead;
            while (pTmp->_pNext != nullptr) {
                pTmp = pTmp->_pNext;
            }
            pTmp->_pNext = pNewNode;
        }
    }

    void _Dequeue() {
        if (_pHead == nullptr) return;
        Node<DataType>* pTmp = _pHead;
        _pHead = _pHead->_pNext;
        delete pTmp;
    }

    DataType& _Front() {
        return _pHead->_data;
    }

    bool _IsEmpty() const {
        return _pHead == nullptr;
    }

    DataType& _Back() {
        Node<DataType>* pTmp = _pHead;
        while (pTmp->_pNext != nullptr) {
            pTmp = pTmp->_pNext;
        }
        return pTmp->_data;
    }

    void _Print() const {
        Node<DataType>* pTmp = _pHead;
        while (pTmp != nullptr) {
            cout << pTmp->_data << endl;
            pTmp = pTmp->_pNext;
        }
    }
};

void _GetNums(List<int>& list) {
    if (list._IsEmpty()) {
        list._Push(1);
    } else {
        int iNums = list._Back() + 1;
        list._Push(iNums);
    }
}

void _AddGuest(List<int>& seats, List<int>& queue, List<Guest>& soldTickets) {
    string strGuestName;
    cout << "Nhap ten khach: ";
    cin >> strGuestName;

    if (!seats._IsEmpty()) {
        Guest guest(strGuestName, seats._Front());
        soldTickets._Push(guest);
        seats._Dequeue();
        queue._Dequeue();
        cout << "Da them khach vao danh sach ve da ban." << endl;
    } else {
        cout << "Khong con ghe trong." << endl;
    }
}

void _CancelTicket(List<int>& seats, List<Guest>& soldTickets) {
    if (!soldTickets._IsEmpty()) {
        Guest cancelledGuest = soldTickets._Front();
        soldTickets._Dequeue();
        seats._Push(cancelledGuest._iSeat);
        cout << "Da huy ve cho khach " << cancelledGuest._strName << " va ghe " << cancelledGuest._iSeat << " da duoc tra lai." << endl;
    } else {
        cout << "Danh sach ve da ban rong." << endl;
    }
}

void _DisplaySoldTickets(const List<Guest>& soldTickets) {
    cout << "Danh sach ve da ban:" << endl;
    soldTickets._Print();
}

int _GetValidInteger() {
    int value;
    while (true) {
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Gia tri nhap vao khong hop le. Vui long nhap lai: ";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

void _Solution(int iNumSeats, int iNumGuests) {
    List<int> seats;
    List<int> queue;
    List<Guest> soldTickets;

    for (int i = 0; i < iNumSeats; ++i) {
        _GetNums(seats);
    }

    for (int i = 0; i < iNumGuests; ++i) {
        _GetNums(queue);
    }

    int choice;
    do {
        cout << "\nMenu:" << endl;
        cout << "1. Them khach vao danh sach ve da ban" << endl;
        cout << "2. Huy ve" << endl;
        cout << "3. Hien thi danh sach ve da ban" << endl;
        cout << "4. Thoat" << endl;
        cout << "Chon chuc nang (1-4): ";
        choice = _GetValidInteger();

        switch (choice) {
            case 1:
                _AddGuest(seats, queue, soldTickets);
                break;
            case 2:
                _CancelTicket(seats, soldTickets);
                break;
            case 3:
                _DisplaySoldTickets(soldTickets);
                break;
            case 4:
                cout << "Thoat chuong trinh." << endl;
                break;
            default:
                cout << "Lua chon khong hop le. Vui long chon lai." << endl;
        }
    } while (choice != 4);
}

int main() {
    int iNumSeats, iNumGuests;
    cout << "Nhap so luong ghe va so luong khach: ";
    iNumSeats = _GetValidInteger();
    iNumGuests = _GetValidInteger();
    _Solution(iNumSeats, iNumGuests);
    return 0;
}