#include <iostream>
#include <cmath>

using namespace std;

// Lớp đại diện cho một hạng tử trong đa thức
class PolynomialTerm {
public:
    int coefficient;   // Hệ số của hạng tử
    int exponent;      // Mũ của hạng tử
    PolynomialTerm* next; // Con trỏ đến hạng tử tiếp theo

    // Constructor khởi tạo hạng tử với hệ số và mũ
    PolynomialTerm(int c, int e) : coefficient(c), exponent(e), next(nullptr) {}
};

// Lớp đại diện cho một đa thức
class Polynomial {
private:
    PolynomialTerm* head; // Con trỏ đến hạng tử đầu tiên của đa thức

public:
    Polynomial() : head(nullptr) {} // Constructor khởi tạo đa thức rỗng

    // Thêm một hạng tử vào đa thức
    void addTerm(int coefficient, int exponent) {
        PolynomialTerm* newTerm = new PolynomialTerm(coefficient, exponent);
        if (!head || head->exponent < exponent) {
            newTerm->next = head;
            head = newTerm;
        }
        else {
            PolynomialTerm* current = head;
            while (current->next && current->next->exponent > exponent) {
                current = current->next;
            }
            if (current->exponent == exponent) {
                current->coefficient += coefficient;
                delete newTerm;
            }
            else {
                newTerm->next = current->next;
                current->next = newTerm;
            }
        }
    }

    // In đa thức ra màn hình
    void print() const {
        PolynomialTerm* current = head;
        while (current) {
            cout << current->coefficient << "x^" << current->exponent;
            current = current->next;
            if (current) cout << " + ";
        }
        cout << endl;
    }

    // Tính đạo hàm của đa thức
    Polynomial derivative() const {
        Polynomial result;
        PolynomialTerm* current = head;
        while (current) {
            if (current->exponent != 0) {
                result.addTerm(current->coefficient * current->exponent, current->exponent - 1);
            }
            current = current->next;
        }
        return result;
    }

    // Đánh giá đa thức tại giá trị x
    double evaluate(double x) const {
        double result = 0.0;
        PolynomialTerm* current = head;
        while (current) {
            result += current->coefficient * pow(x, current->exponent);
            current = current->next;
        }
        return result;
    }

    // Cộng hai đa thức
    static Polynomial add(const Polynomial& p1, const Polynomial& p2) {
        Polynomial result;
        PolynomialTerm* current1 = p1.head;
        PolynomialTerm* current2 = p2.head;

        while (current1 && current2) {
            if (current1->exponent == current2->exponent) {
                result.addTerm(current1->coefficient + current2->coefficient, current1->exponent);
                current1 = current1->next;
                current2 = current2->next;
            }
            else if (current1->exponent > current2->exponent) {
                result.addTerm(current1->coefficient, current1->exponent);
                current1 = current1->next;
            }
            else {
                result.addTerm(current2->coefficient, current2->exponent);
                current2 = current2->next;
            }
        }

        while (current1) {
            result.addTerm(current1->coefficient, current1->exponent);
            current1 = current1->next;
        }

        while (current2) {
            result.addTerm(current2->coefficient, current2->exponent);
            current2 = current2->next;
        }

        return result;
    }

    // Nhân hai đa thức
    static Polynomial multiply(const Polynomial& p1, const Polynomial& p2) {
        Polynomial result;
        PolynomialTerm* current1 = p1.head;

        while (current1) {
            PolynomialTerm* current2 = p2.head;
            while (current2) {
                result.addTerm(current1->coefficient * current2->coefficient, current1->exponent + current2->exponent);
                current2 = current2->next;
            }
            current1 = current1->next;
        }

        return result;
    }
};

// Hiển thị menu lựa chọn
void displayMenu() {
    cout << "---------------------MENU---------------------" << endl;
    cout << "1. Tạo đa thức F1" << endl;
    cout << "2. Tạo đa thức F2" << endl;
    cout << "3. Hiển thị đa thức F1 và F2" << endl;
    cout << "4. Tính đạo hàm của đa thức F1" << endl;
    cout << "5. Tính đạo hàm của đa thức F2" << endl;
    cout << "6. Đánh giá đa thức F1 tại x" << endl;
    cout << "7. Đánh giá đa thức F2 tại x" << endl;
    cout << "8. Tính đa thức F3 là F1 + F2" << endl;
    cout << "9. Tính đa thức F3 là F1 * F2" << endl;
    cout << "10. Thoát" << endl;
    cout << "----------------------------------------------" << endl;
}

int main() {
    Polynomial F1, F2, F3;
    int choice;

    while (true) {
        displayMenu();
        cout << "Nhập lựa chọn của bạn: ";
        cin >> choice;

        switch (choice) {
        case 1:
        {
            int coef, exp;
            cout << "Nhập hệ số và mũ (nhập -1 -1 để dừng): " << endl;
            while (true) {
                cin >> coef >> exp;
                if (coef == -1 && exp == -1) break;
                F1.addTerm(coef, exp);
            }
            break;
        }
        case 2:
        {
            int coef, exp;
            cout << "Nhập hệ số và mũ (nhập -1 -1 để dừng): " << endl;
            while (true) {
                cin >> coef >> exp;
                if (coef == -1 && exp == -1) break;
                F2.addTerm(coef, exp);
            }
            break;
        }
        case 3:
            cout << "F1: ";
            F1.print();
            cout << "F2: ";
            F2.print();
            break;
        case 4:
        {
            Polynomial derivativeF1 = F1.derivative();
            cout << "Đạo hàm của F1: ";
            derivativeF1.print();
            break;
        }
        case 5:
        {
            Polynomial derivativeF2 = F2.derivative();
            cout << "Đạo hàm của F2: ";
            derivativeF2.print();
            break;
        }
        case 6:
        {
            double x;
            cout << "Nhập giá trị x: ";
            cin >> x;
            cout << "F1(" << x << ") = " << F1.evaluate(x) << endl;
            break;
        }
        case 7:
        {
            double x;
            cout << "Nhập giá trị x: ";
            cin >> x;
            cout << "F2(" << x << ") = " << F2.evaluate(x) << endl;
            break;
        }
        case 8:
            F3 = Polynomial::add(F1, F2);
            cout << "F3 (F1 + F2): ";
            F3.print();
            break;
        case 9:
            F3 = Polynomial::multiply(F1, F2);
            cout << "F3 (F1 * F2): ";
            F3.print();
            break;
        case 10:
            cout << "Đang thoát chương trình." << endl;
            return 0;
        default:
            cout << "Lựa chọn không hợp lệ. Vui lòng thử lại." << endl;
        }
    }

    return 0;
}
