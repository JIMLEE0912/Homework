#include <iostream>
#include <cmath>
using namespace std;

struct PolyNode {
    int coef;       // 係數
    int exp;        // 指數
    PolyNode* link; // 指向下一個節點
};

class Polynomial {
private:
    PolyNode* head; // 表頭節點（循環串列）

    // 建立節點
    PolyNode* NewNode(int c, int e) {
        PolyNode* node = new PolyNode;
        node->coef = c;
        node->exp = e;
        node->link = nullptr;
        return node;
    }

    // 釋放所有節點（用於解構或清空）
    void Clear() {
        PolyNode* cur = head->link;
        while (cur != head) {
            PolyNode* temp = cur;
            cur = cur->link;
            delete temp;
        }
        head->link = head; // 回到空串列狀態
    }

public:
    // 預設建構子
    Polynomial() {
        head = NewNode(0, 0); // 表頭節點
        head->link = head;    // 循環指向自己
    }

    // 複製建構子 (c)
    Polynomial(const Polynomial& a) {
        head = NewNode(0, 0);
        head->link = head;
        PolyNode* cur = a.head->link;
        while (cur != a.head) {
            InsertTerm(cur->coef, cur->exp);
            cur = cur->link;
        }
    }

    // 指派運算子 (d)
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

    // 解構子 (e)
    ~Polynomial() {
        Clear();
        delete head;
    }

    // 插入一項（保持降冪）
    void InsertTerm(int c, int e) {
        if (c == 0) return; // 係數 0 不加入
        PolyNode* prev = head;
        PolyNode* cur = head->link;
        while (cur != head && cur->exp > e) {
            prev = cur;
            cur = cur->link;
        }
        if (cur != head && cur->exp == e) {
            cur->coef += c;
            if (cur->coef == 0) { // 刪除係數為 0 的項
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

    // 加法 (f)
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

    // 減法 (g)
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

    // 乘法 (h)
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

    // 輸入 (a)
    friend istream& operator>>(istream& is, Polynomial& x) {
        int n, c, e;
        is >> n;
        for (int i = 0; i < n; i++) {
            is >> c >> e;
            x.InsertTerm(c, e);
        }
        return is;
    }

    // 輸出 (b)
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
    cout << "輸入多項式 p1 (格式: n c1 e1 c2 e2 ...): ";
    cin >> p1;
    cout << "輸入多項式 p2 (格式: n c1 e1 c2 e2 ...): ";
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
    cout << "輸入 x 值計算 p1(x): ";
    cin >> x;
    cout << "p1(" << x << ") = " << p1.Evaluate(x) << endl;

    return 0;
}
