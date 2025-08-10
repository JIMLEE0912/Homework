#include <iostream>
#include <cmath>
using namespace std;

struct PolyNode {
    int coef;       // �Y��
    int exp;        // ����
    PolyNode* link; // ���V�U�@�Ӹ`�I
};

class Polynomial {
private:
    PolyNode* head; // ���Y�`�I�]�`����C�^

    // �إ߸`�I
    PolyNode* NewNode(int c, int e) {
        PolyNode* node = new PolyNode;
        node->coef = c;
        node->exp = e;
        node->link = nullptr;
        return node;
    }

    // ����Ҧ��`�I�]�Ω�Ѻc�βM�š^
    void Clear() {
        PolyNode* cur = head->link;
        while (cur != head) {
            PolyNode* temp = cur;
            cur = cur->link;
            delete temp;
        }
        head->link = head; // �^��Ŧ�C���A
    }

public:
    // �w�]�غc�l
    Polynomial() {
        head = NewNode(0, 0); // ���Y�`�I
        head->link = head;    // �`�����V�ۤv
    }

    // �ƻs�غc�l (c)
    Polynomial(const Polynomial& a) {
        head = NewNode(0, 0);
        head->link = head;
        PolyNode* cur = a.head->link;
        while (cur != a.head) {
            InsertTerm(cur->coef, cur->exp);
            cur = cur->link;
        }
    }

    // �����B��l (d)
    const Polynomial& operator=(const Polynomial& a) {
        if (this != &a) {
            Clear();
            PolyNode* cur = a.head->link;
            while (cur != a.head) {
                InsertTerm(cur->coef, cur->exp);
                cur = cur->link;
            }
        }
        return *this;
    }

    // �Ѻc�l (e)
    ~Polynomial() {
        Clear();
        delete head;
    }

    // ���J�@���]�O�������^
    void InsertTerm(int c, int e) {
        if (c == 0) return; // �Y�� 0 ���[�J
        PolyNode* prev = head;
        PolyNode* cur = head->link;
        while (cur != head && cur->exp > e) {
            prev = cur;
            cur = cur->link;
        }
        if (cur != head && cur->exp == e) {
            cur->coef += c;
            if (cur->coef == 0) { // �R���Y�Ƭ� 0 ����
                prev->link = cur->link;
                delete cur;
            }
        }
        else {
            PolyNode* node = NewNode(c, e);
            node->link = cur;
            prev->link = node;
        }
    }

    // �[�k (f)
    Polynomial operator+(const Polynomial& b) const {
        Polynomial result;
        PolyNode* p = head->link;
        PolyNode* q = b.head->link;
        while (p != head && q != b.head) {
            if (p->exp > q->exp) {
                result.InsertTerm(p->coef, p->exp);
                p = p->link;
            }
            else if (p->exp < q->exp) {
                result.InsertTerm(q->coef, q->exp);
                q = q->link;
            }
            else {
                result.InsertTerm(p->coef + q->coef, p->exp);
                p = p->link;
                q = q->link;
            }
        }
        while (p != head) {
            result.InsertTerm(p->coef, p->exp);
            p = p->link;
        }
        while (q != b.head) {
            result.InsertTerm(q->coef, q->exp);
            q = q->link;
        }
        return result;
    }

    // ��k (g)
    Polynomial operator-(const Polynomial& b) const {
        Polynomial result;
        PolyNode* p = head->link;
        PolyNode* q = b.head->link;
        while (p != head && q != b.head) {
            if (p->exp > q->exp) {
                result.InsertTerm(p->coef, p->exp);
                p = p->link;
            }
            else if (p->exp < q->exp) {
                result.InsertTerm(-q->coef, q->exp);
                q = q->link;
            }
            else {
                result.InsertTerm(p->coef - q->coef, p->exp);
                p = p->link;
                q = q->link;
            }
        }
        while (p != head) {
            result.InsertTerm(p->coef, p->exp);
            p = p->link;
        }
        while (q != b.head) {
            result.InsertTerm(-q->coef, q->exp);
            q = q->link;
        }
        return result;
    }

    // ���k (h)
    Polynomial operator*(const Polynomial& b) const {
        Polynomial result;
        for (PolyNode* p = head->link; p != head; p = p->link) {
            for (PolyNode* q = b.head->link; q != b.head; q = q->link) {
                result.InsertTerm(p->coef * q->coef, p->exp + q->exp);
            }
        }
        return result;
    }

    // Evaluate (i)
    float Evaluate(float x) const {
        float sum = 0;
        for (PolyNode* p = head->link; p != head; p = p->link) {
            sum += p->coef * pow(x, p->exp);
        }
        return sum;
    }

    // ��J (a)
    friend istream& operator>>(istream& is, Polynomial& x) {
        int n, c, e;
        is >> n;
        for (int i = 0; i < n; i++) {
            is >> c >> e;
            x.InsertTerm(c, e);
        }
        return is;
    }

    // ��X (b)
    friend ostream& operator<<(ostream& os, const Polynomial& x) {
        PolyNode* p = x.head->link;
        bool first = true;
        while (p != x.head) {
            if (!first && p->coef > 0) os << "+";
            os << p->coef;
            if (p->exp != 0) os << "x^" << p->exp;
            p = p->link;
            first = false;
        }
        if (first) os << "0";
        return os;
    }
};

int main() {
    Polynomial p1, p2;
    cout << "��J�h���� p1 (�榡: n c1 e1 c2 e2 ...): ";
    cin >> p1;
    cout << "��J�h���� p2 (�榡: n c1 e1 c2 e2 ...): ";
    cin >> p2;

    cout << "p1 = " << p1 << endl;
    cout << "p2 = " << p2 << endl;

    Polynomial sum = p1 + p2;
    Polynomial diff = p1 - p2;
    Polynomial prod = p1 * p2;

    cout << "p1 + p2 = " << sum << endl;
    cout << "p1 - p2 = " << diff << endl;
    cout << "p1 * p2 = " << prod << endl;

    float x;
    cout << "��J x �ȭp�� p1(x): ";
    cin >> x;
    cout << "p1(" << x << ") = " << p1.Evaluate(x) << endl;

    return 0;
}
