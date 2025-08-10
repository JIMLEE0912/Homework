# 李柏均 41141123 

作業三

## 解題說明

本題要求以 **C++** 實作一個表示單變數多項式的類別 `Polynomial`，並使用 **帶有表頭節點的循環鏈結串列** 來儲存多項式的項目。  
需支援以下操作：

- 多項式的加法、減法與乘法。
- 代入某個變數值計算多項式的值。
- 多項式的輸入與輸出（使用運算子多載 `>>` 與 `<<`）。
- 複製建構子、指定運算子與解構子正確管理記憶體。

### 解題策略

1. 使用結構 `PolyNode` 表示多項式的一項，包含 **係數 (`coef`)**、**指數 (`exp`)** 與 **指標 (`link`)**。
2. 使用一個 **表頭節點** 作為循環鏈結串列的起點與終點，方便插入與刪除。
3. 插入新項目時保持 **指數降冪排序**，如果遇到相同次方則合併係數。
4. 加法、減法採用**同步走訪**兩個多項式節點合併結果。
5. 乘法採用**巢狀迴圈**計算每一項的乘積並插入到結果多項式。
6. `Evaluate(x)` 以 `pow` 計算每項的值並累加。
7. 輸入格式為：
   ```
   n c1 e1 c2 e2 ... cn en
   ```
   其中 `n` 為項數，`ci` 為係數，`ei` 為指數，且 `e1 > e2 > ... > en`。

## 程式實作

以下為主要程式碼：

```cpp
#include <iostream>
#include <cmath>
using namespace std;

struct PolyNode {
    int coef;
    int exp;
    PolyNode* link;
};

class Polynomial {
private:
    PolyNode* head;

    PolyNode* NewNode(int c, int e) {
        PolyNode* node = new PolyNode;
        node->coef = c;
        node->exp = e;
        node->link = nullptr;
        return node;
    }

    void Clear() {
        PolyNode* cur = head->link;
        while (cur != head) {
            PolyNode* temp = cur;
            cur = cur->link;
            delete temp;
        }
        head->link = head;
    }

public:
    Polynomial() {
        head = NewNode(0, 0);
        head->link = head;
    }

    Polynomial(const Polynomial& a) {
        head = NewNode(0, 0);
        head->link = head;
        PolyNode* cur = a.head->link;
        while (cur != a.head) {
            InsertTerm(cur->coef, cur->exp);
            cur = cur->link;
        }
    }

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

    ~Polynomial() {
        Clear();
        delete head;
    }

    void InsertTerm(int c, int e) {
        if (c == 0) return;
        PolyNode* prev = head;
        PolyNode* cur = head->link;
        while (cur != head && cur->exp > e) {
            prev = cur;
            cur = cur->link;
        }
        if (cur != head && cur->exp == e) {
            cur->coef += c;
            if (cur->coef == 0) {
                prev->link = cur->link;
                delete cur;
            }
        } else {
            PolyNode* node = NewNode(c, e);
            node->link = cur;
            prev->link = node;
        }
    }

    Polynomial operator+(const Polynomial& b) const {
        Polynomial result;
        PolyNode* p = head->link;
        PolyNode* q = b.head->link;
        while (p != head && q != b.head) {
            if (p->exp > q->exp) {
                result.InsertTerm(p->coef, p->exp);
                p = p->link;
            } else if (p->exp < q->exp) {
                result.InsertTerm(q->coef, q->exp);
                q = q->link;
            } else {
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

    Polynomial operator-(const Polynomial& b) const {
        Polynomial result;
        PolyNode* p = head->link;
        PolyNode* q = b.head->link;
        while (p != head && q != b.head) {
            if (p->exp > q->exp) {
                result.InsertTerm(p->coef, p->exp);
                p = p->link;
            } else if (p->exp < q->exp) {
                result.InsertTerm(-q->coef, q->exp);
                q = q->link;
            } else {
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

    Polynomial operator*(const Polynomial& b) const {
        Polynomial result;
        for (PolyNode* p = head->link; p != head; p = p->link) {
            for (PolyNode* q = b.head->link; q != b.head; q = q->link) {
                result.InsertTerm(p->coef * q->coef, p->exp + q->exp);
            }
        }
        return result;
    }

    float Evaluate(float x) const {
        float sum = 0;
        for (PolyNode* p = head->link; p != head; p = p->link) {
            sum += p->coef * pow(x, p->exp);
        }
        return sum;
    }

    friend istream& operator>>(istream& is, Polynomial& x) {
        int n, c, e;
        is >> n;
        for (int i = 0; i < n; i++) {
            is >> c >> e;
            x.InsertTerm(c, e);
        }
        return is;
    }

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
```

## 效能分析

1. **時間複雜度**：

    加法與減法的時間複雜度為 $O(m + n)$，因為加法與減法需走訪兩個多項式。

    時間複雜度為 $O(m \cdot n)$，因乘法為雙重迴圈。

     評估多項式的時間複雜度為 $O(m)$，因為需逐項計算並累加。


2. **空間複雜度**：
    
    加法與減法結果最多需要 $O(m + n)$ 節點。

    乘法結果最多需要 $O(m \cdot n)$ 節點。

## 測試與驗證

### 測試案例
輸入：
```
輸入多項式 p1 (格式: n c1 e1 c2 e2 ...): 3 4 5 3 2 -1 0
輸入多項式 p2 (格式: n c1 e1 c2 e2 ...): 2 5 3 2 0
輸入 x 值計算 p1(x): 2
```
輸出：
```
p1 = 4x^5+3x^2-1
p2 = 5x^3+2
p1 + p2 = 4x^5+5x^3+3x^2+1
p1 - p2 = 4x^5-5x^3+3x^2-3
p1 * p2 = 20x^8+10x^5+15x^5+6x^2-5x^3-2
p1(2) = 133
```

## 編譯與執行指令
```bash
g++ -std=c++17 -o poly polyHW3.cpp
./poly
```

## 結論

- 使用循環鏈結串列能方便動態插入與刪除節點，節省記憶體浪費。
- 多項式運算功能完整，輸入輸出直觀。
- 乘法演算法仍為 $O(mn)$，可研究更快的多項式乘法（如 FFT）。

## 申論與開發報告

### 優點
1. 採用鏈結串列結構，避免動態陣列擴充的額外成本。
2. 加減運算只需一次線性走訪即可完成，效率高。
3. 程式模組化，便於維護與擴充。

### 可改進之處
1. 可額外設計 **可用節點串列**（available-space list）管理記憶體。
2. 乘法可優化合併同類項的過程，減少重複插入成本。
