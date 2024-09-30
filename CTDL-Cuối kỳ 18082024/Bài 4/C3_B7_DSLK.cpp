// Code này đc 3/4
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
class Monomial {
protected:
    int coefficient;
    int exponent;
public:
    Monomial(){} 
    Monomial(int, int);
    int getCoefficient(); 
    int getExponent();
    friend ostream& operator << (ostream&, Monomial);
    friend Monomial operator + (Monomial, Monomial);
    static Monomial derivative(Monomial);
};

class ListNode {
private:
    Monomial monomial;
    ListNode* next;
public:
    static void printPolynomial(ListNode*);
    static void addMonomial(ListNode*&, Monomial);
    static void inputPolynomial(ListNode*&, ListNode*&, vector<double>);
    static ListNode* derivativePolynomial(ListNode*);
    static ListNode* sumPolynomials(ListNode*, ListNode*);
    static double evaluatePolynomial(ListNode*, double x);
};

int main() {
    ListNode *poly1 = NULL, *poly2 = NULL;
    double n; 
    vector<double> coeffExpPairs;

    while (cin >> n) coeffExpPairs.push_back(n);
    double x = coeffExpPairs.back(); 

    ListNode::inputPolynomial(poly1, poly2, coeffExpPairs);
    ListNode::printPolynomial(poly1); cout << " ";
    ListNode::printPolynomial(poly2); cout << endl;
    ListNode* poly3 = ListNode::sumPolynomials(poly1, poly2);
    ListNode* poly4 = ListNode::derivativePolynomial(poly3);
    ListNode::printPolynomial(poly4); cout << endl;
    cout << ListNode::evaluatePolynomial(poly3, x); cout << endl;
    ListNode::printPolynomial(poly3);
    return 0;
}

Monomial::Monomial(int coefficient, int exponent) {
    this->coefficient = coefficient;
    this->exponent = exponent;
}

int Monomial::getCoefficient() {
    return coefficient;
}

int Monomial::getExponent() {
    return exponent;
}

ostream& operator << (ostream& out, Monomial m) {
    if (m.coefficient == 0) return out;
    else if (m.coefficient == 1) {
        if (m.exponent == 0) cout << 1;
        else if (m.exponent == 1) cout << "x";
        else cout << "x^" << m.exponent;
    } else {
        if (m.coefficient == -1) { cout << "-"; }
        if (m.exponent == 0) cout << abs(m.coefficient);
        else if (m.exponent == 1) cout << abs(m.coefficient) << "x";
        else cout << abs(m.coefficient) << "x^" << m.exponent;
    }
    return out;
}

Monomial operator + (Monomial a, Monomial b) {
    Monomial c;
    c.exponent = a.getExponent();
    c.coefficient = a.getCoefficient() + b.getCoefficient();
    return c;
}

Monomial Monomial::derivative(Monomial m) {
    Monomial res;
    if (m.exponent == 0 || m.coefficient == 0) {
        res.exponent = 0; 
        res.coefficient = 0;
    }
    else if (m.exponent == 1) {
        res.exponent = 0; 
        res.coefficient = m.coefficient;
    }
    else {
        res.coefficient = m.coefficient * m.exponent; 
        res.exponent = m.exponent - 1;
    }
    return res;
}

void ListNode::addMonomial(ListNode*& head, Monomial m) {
    ListNode* newNode = new ListNode;
    newNode->monomial = m;
    newNode->next = NULL;
    if (head == NULL) {
        head = newNode;
    } else {
        ListNode* last = head;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = newNode;
    }
}

void ListNode::printPolynomial(ListNode* head) {
    bool isFirstMonomial = true;
    while (head != NULL) {
        if (!isFirstMonomial && head->monomial.getCoefficient() > 0)
            cout << "+" << head->monomial;
        else if (!isFirstMonomial && head->monomial.getCoefficient() < 0)
            cout << "-" << head->monomial;
        else {
            isFirstMonomial = false;
            cout << head->monomial;
        }
        head = head->next;
    }
}
double ListNode::evaluatePolynomial(ListNode* head, double x) {
    double result = 0;
    while (head != NULL) {
        result += head->monomial.getCoefficient() * pow(x, head->monomial.getExponent());
        head = head->next;
    }
    return result;
}
void ListNode::inputPolynomial(ListNode*& poly1, ListNode*& poly2, vector<double> coeffExpPairs) {
    vector<double>::iterator it;
    it = coeffExpPairs.end() - 1; 
    coeffExpPairs.erase(it);

    for (int i = 0; i < coeffExpPairs.size() / 2; i += 2) {
        Monomial m(coeffExpPairs[i], coeffExpPairs[i + 1]);
        addMonomial(poly1, m);
    }

    for (int i = coeffExpPairs.size() / 2; i < coeffExpPairs.size(); i += 2) {
        Monomial m(coeffExpPairs[i], coeffExpPairs[i + 1]);
        addMonomial(poly2, m);
    }
}
ListNode* ListNode::sumPolynomials(ListNode* poly1, ListNode* poly2) {
    int maxExponent = 0;
    ListNode *a = poly1, *b = poly2;
    while (a != NULL) {
        if (maxExponent < a->monomial.getExponent())
            maxExponent = a->monomial.getExponent();
        a = a->next;
    }
    while (b != NULL) {
        if (maxExponent < b->monomial.getExponent())
            maxExponent = b->monomial.getExponent();
        b = b->next;
    }
    ListNode* polySum = NULL;
    while (maxExponent > -1) {
        ListNode* x = poly1, *y = poly2;
        while (x != NULL && x->monomial.getExponent() != maxExponent)
            x = x->next;
        while (y != NULL && y->monomial.getExponent() != maxExponent)
            y = y->next;

        if (x != NULL && y != NULL) {
            Monomial z = x->monomial + y->monomial;
            addMonomial(polySum, z);
        } else if (x != NULL) {
            addMonomial(polySum, x->monomial);
        }
        else if (y != NULL) {
            addMonomial(polySum, y->monomial);
        }
        maxExponent--;
    }
    return polySum;
}
ListNode* ListNode::derivativePolynomial(ListNode* head) {
    ListNode* res = NULL;
    while (head != NULL) {
        addMonomial(res, Monomial::derivative(head->monomial));
        head = head->next;
    } 
    return res;
}