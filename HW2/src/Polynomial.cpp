#include <iostream>
#include <algorithm>
#include <cmath>

struct Term {
    float coef;
    int exp;
};

class Polynomial {
private:
    Term* termArray;
    int capacity;
    int terms;

    void expand() {
        capacity *= 2;
        Term* temp = new Term[capacity];
        for (int i = 0; i < terms; ++i)
            temp[i] = termArray[i];
        delete[] termArray;
        termArray = temp;
    }

public:
    Polynomial() : capacity(10), terms(0) {
        termArray = new Term[capacity];
    }

    ~Polynomial() {
        delete[] termArray;
    }

    Polynomial(const Polynomial& other) : capacity(other.capacity), terms(other.terms) {
        termArray = new Term[capacity];
        for (int i = 0; i < terms; ++i)
            termArray[i] = other.termArray[i];
    }

    Polynomial& operator=(const Polynomial& other) {
        if (this != &other) {
            delete[] termArray;
            capacity = other.capacity;
            terms = other.terms;
            termArray = new Term[capacity];
            for (int i = 0; i < terms; ++i)
                termArray[i] = other.termArray[i];
        }
        return *this;
    }

    void addTerm(float coef, int exp) {
        if (coef == 0) return;

        for (int i = 0; i < terms; ++i) {
            if (termArray[i].exp == exp) {
                termArray[i].coef += coef;
                if (termArray[i].coef == 0) {
                    for (int j = i; j < terms - 1; ++j)
                        termArray[j] = termArray[j + 1];
                    --terms;
                }
                return;
            }
        }

        if (terms == capacity) expand();
        termArray[terms++] = { coef, exp };
        std::sort(termArray, termArray + terms, [](auto a, auto b) {
            return a.exp > b.exp;
            });
    }

    Polynomial Add(Polynomial poly) {
        Polynomial result = *this;
        for (int i = 0; i < poly.terms; ++i)
            result.addTerm(poly.termArray[i].coef, poly.termArray[i].exp);
        return result;
    }

    Polynomial Mult(Polynomial poly) {
        Polynomial result;
        for (int i = 0; i < terms; ++i)
            for (int j = 0; j < poly.terms; ++j)
                result.addTerm(termArray[i].coef * poly.termArray[j].coef,
                    termArray[i].exp + poly.termArray[j].exp);
        return result;
    }

    float Eval(float f) {
        float result = 0.0;
        for (int i = 0; i < terms; ++i)
            result += termArray[i].coef * pow(f, termArray[i].exp);
        return result;
    }

    friend std::istream& operator>>(std::istream& is, Polynomial& poly);
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& poly);
};

std::istream& operator>>(std::istream& is, Polynomial& poly) {
    int numTerms;
    is >> numTerms;

    poly.terms = 0;
    for (int i = 0; i < numTerms; ++i) {
        float coef;
        int exp;
        is >> coef >> exp;
        poly.addTerm(coef, exp);
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const Polynomial& poly) {
    if (poly.terms == 0) return os << "0";

    for (int i = 0; i < poly.terms; ++i) {
        float coef = poly.termArray[i].coef;
        int exp = poly.termArray[i].exp;

        if (i > 0)
            os << (coef > 0 ? " + " : " - ");
        else if (coef < 0)
            os << "-";

        float absCoef = abs(coef);
        if (absCoef != 1 || exp == 0)
            os << ((i == 0 || coef < 0) ? absCoef : coef);

        if (exp > 0) {
            os << "x";
            if (exp > 1) os << "^" << exp;
        }
    }
    return os;
}

int main() {
    Polynomial p1, p2;

    std::cout << "�п�J�Ĥ@�Ӧh�����G\n";
    std::cout << "���ơG";
    std::cin >> p1;

    std::cout << "�п�J�ĤG�Ӧh�����G\n";
    std::cout << "���ơG";
    std::cin >> p2;

    Polynomial sum = p1.Add(p2);
    Polynomial product = p1.Mult(p2);

    std::cout << "\n�h����1: " << p1 << std::endl;
    std::cout << "�h����2: " << p2 << std::endl;
    std::cout << "�[�`���G: " << sum << std::endl;
    std::cout << "���n���G: " << product << std::endl;

    float x;
    std::cout << "\n�п�J�ܼ�x����(�Ω�p��h����1): ";
    std::cin >> x;
    std::cout << "p1(" << x << ") = " << p1.Eval(x) << std::endl;

    return 0;
}