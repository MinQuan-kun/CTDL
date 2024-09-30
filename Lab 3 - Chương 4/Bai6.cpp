#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <windows.h>

using namespace std;

class HangHoa {
private:
    string maHang;
    string tenHang;
    int soLuong;
    int donGia;
public:
    HangHoa* next;

    HangHoa() : maHang(""), tenHang(""), soLuong(0), donGia(0), next(NULL) {}

    HangHoa(string id, string name, int amount, int price)
        : maHang(id), tenHang(name), soLuong(amount), donGia(price), next(NULL) {}

    void print() const {
        cout << maHang << " " << tenHang << " " << soLuong << " " << donGia << endl;
    }

    string getMaHang() const {
        return maHang;
    }
};

class Queue {
private:
    HangHoa* head;
    HangHoa* tail;
public:
    Queue() : head(NULL), tail(NULL) {}

    void enqueue(HangHoa* sample) {
        if (tail == NULL) {
            head = tail = sample;
        }
        else {
            tail->next = sample;
            tail = sample;
        }
    }

    HangHoa* dequeue() {
        if (isEmpty()) {
            cout << "Queue rong" << endl;
            return NULL;
        }
        HangHoa* temp = head;
        head = head->next;
        if (head == NULL) {
            tail = NULL;
        }
        delete temp;
        return head;
    }

    HangHoa* front() const {
        return head;
    }

    bool isEmpty() const {
        return head == NULL;
    }

    void printQueue() const {
        if (isEmpty()) {
            cout << "Queue rong" << endl;
        }
        else {
            for (HangHoa* temp = head; temp != NULL; temp = temp->next) {
                temp->print();
            }
        }
    }

    bool removeItemById(const string& id) {
        HangHoa* current = head;
        HangHoa* previous = NULL;

        while (current != NULL) {
            if (current->getMaHang() == id) {
                if (previous == NULL) { // item to be removed is head
                    head = current->next;
                    if (head == NULL) {
                        tail = NULL;
                    }
                }
                else {
                    previous->next = current->next;
                    if (previous->next == NULL) {
                        tail = previous;
                    }
                }
                delete current;
                return true;
            }
            previous = current;
            current = current->next;
        }
        return false;
    }
};

void menuDisplay() {
    system("cls");
    cout << "1 Xem tat ca cac hang hoa trong kho" << endl;
    cout << "2 Xem mat hang sap xuat kho" << endl;
    cout << "3 Them mot mat hang vao kho" << endl;
    cout << "4 Xuat mot mat hang ra khoi kho" << endl;
    cout << "5 Thoat" << endl;
}

void menuLoop(Queue& store) {
    int choice;
    string id, name;
    int amount, price;

    while (true) {
        menuDisplay();
        cout << "Chon chuc nang: ";
        string choiceStr;
        getline(cin, choiceStr);

        if (choiceStr.empty() || !isdigit(choiceStr[0])) {
            cout << "Lua chon khong hop le Vui long nhap lai" << endl;
            Sleep(2000);
            continue;
        }

        choice = stoi(choiceStr);
        if (choice < 1 || choice > 5) {
            cout << "Lua chon khong hop le Vui long nhap lai" << endl;
            Sleep(2000);
            continue;
        }

        switch (choice) {
        case 1:
            cout << "Danh sach hang hoa trong kho" << endl;
            store.printQueue();
            Sleep(2000);
            break;

        case 2:
            if (!store.isEmpty()) {
                cout << "Mat hang sap duoc xuat kho" << endl;
                store.front()->print();
            }
            else {
                cout << "Kho khong co hang hoa" << endl;
            }
            Sleep(2000);
            break;

        case 3:
            cout << "Nhap ma hang hoa: ";
            getline(cin, id);
            cout << "Nhap ten hang hoa: ";
            getline(cin, name);
            cout << "Nhap so luong: ";
            cin >> amount;
            cout << "Nhap don gia: ";
            cin >> price;
            cin.ignore();

            {
                HangHoa* newItem = new HangHoa(id, name, amount, price);
                store.enqueue(newItem);
            }
            Sleep(2000);
            break;

        case 4:
            cout << "Nhap ma hang hoa can xuat kho: ";
            getline(cin, id);
            if (store.removeItemById(id)) {
                cout << "Mat hang da xuat kho" << endl;
            }
            else {
                cout << "Mat hang khong tim thay" << endl;
            }
            Sleep(2000);
            break;

        case 5:
            Sleep(2000);
            return;

        default:
            cout << "Lua chon khong hop le Vui long chon lai" << endl;
        }
    }
}

int main() {
    Queue store;
    menuLoop(store);
    return 0;
}
