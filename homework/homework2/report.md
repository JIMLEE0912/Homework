
# 李柏均 41141123 

作業二

## 解題說明

本題要求實作一個表示多項式的類別 `Polynomial`，並支援以下操作：

- 多項式的加法與乘法。

- 以某個變數值代入計算。

- 多項式的輸入與輸出操作，並透過運算子多載 `<<` 與 `>>` 實現。

### 解題策略

1. 使用結構 `Term` 表示多項式的單項式，包含係數 `coef` 與次方數 `exp`。
2. 使用動態陣列 `termArray` 儲存所有非零項，並隨著項數自動擴充。
3. 利用排序與合併同次項的策略簡化輸入與加法處理。
4. 實作加法與乘法函式分別處理兩個多項式的合併與展開。
5. 用迴圈方式計算某變數值代入的多項式值。

## 程式實作

以下為主要程式碼：

```cpp
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
        termArray[terms++] = {coef, exp};
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
    
    std::cout << "請輸入第一個多項式：\n";
    std::cout << "項數：";
    std::cin >> p1;
    
    std::cout << "請輸入第二個多項式：\n";
    std::cout << "項數：";
    std::cin >> p2;
    
    Polynomial sum = p1.Add(p2);
    Polynomial product = p1.Mult(p2);
    
    std::cout << "\n多項式1: " << p1 << std::endl;
    std::cout << "多項式2: " << p2 << std::endl;
    std::cout << "加總結果: " << sum << std::endl;
    std::cout << "乘積結果: " << product << std::endl;
    
    float x;
    std::cout << "\n請輸入變數x的值(用於計算多項式1): ";
    std::cin >> x;
    std::cout << "p1(" << x << ") = " << p1.Eval(x) << std::endl;
    
    return 0;
}
```

## 效能分析

1. **時間複雜度**：

    加法的時間複雜度是 $O((m + n) \log (m + n))$，因為合併項目後還要重新排序次方數。


    乘法的時間複雜度是 $O(m \cdot n)$，每一項都要跟另一個多項式的所有項目相乘一次。


2. **空間複雜度**：
    
    加法的空間複雜度是 $O(m + n)$，最多需要儲存的所有項目。

    乘法的空間複雜度是 $O(m \cdot n)$，相乘後可能會產生很多不同次方的新項目。

## 測試與驗證

### 測試案例

| 測試案例 | 多項式1      | 多項式2      | 預期加總結果 | 預期乘積結果 |
|----------|--------------|--------------|---------------|----------------|
| 測試一   | 2x^2 + 3x + 1| x^2 + 1       | 3x^2 + 3x + 2 | 2x^4 + 3x^3 + 3x^2 + 3x + 1 |
| 測試二   | x^2 + 0x + 1 | -x^2 + 3x     | 3x + 1        | -x^4 + 3x^3 - x^2 + 3x |
| 測試三   | 0            | 0            | 0             | 0              |


### 編譯與執行指令
```bash
g++ -std=c++17 -o poly Polynomial.cpp
./poly
```
## 結論

- 正確實作多項式運算與輸入輸出。
- 操作直觀簡潔易懂，格式清楚。
- 程式具有良好的結構與彈性，易於擴充與維護。

## 申論與開發報告

### 程式的優點有：

1. **結構簡潔明確**
 
   使用 `Term` 結構搭配動態陣列 `termArray` 管理每一項非零多項式項，讓資料儲存及操作維持簡單有效率。

2. **運算功能完整**  
  
   程式實作了多項式的加法 `Add` 、乘法 `Mult`，以及變數代入的數值運算 `Eval`。

### 可改進之處：

1. **效能最佳化**
 
   每次新增項目都使用 `std::sort` 排序，雖可保證次方數由大到小排列，但若改用插入排序或在適當位置插入可減少排序成本。

2. **使用 STL 容器可提升安全性與效率**  
  
   若使用 `std::vector<Term>` 來存放項目，就可以取代手動管理陣列和自己寫 `expand()` 函式的做法。