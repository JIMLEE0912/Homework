
# 李柏均 41141123 

作業一  Problem 1    

## 解題說明

本題要求實作一個遞迴函式 — Ackermann 函數，計算𝐴(𝑚,𝑛)的值。

## 解題策略
**遞迴版本**
1. 根據 Ackermann 函數的數學定義實作三種遞迴情況：  

   $$
   A(m,n) = \begin{cases}
   n + 1 & \text{，if } m = 0 \\
   A(m-1, 1) & \text{，if } n = 0 \\
   A(m-1, A(m, n-1)) & \text{，otherwise}
   \end{cases}
   $$

2. 將三種情況分別實作為：

    終止條件：if (m == 0) return n + 1;

    子遞迴一層：if (n == 0) return akm(m - 1, 1);

    子遞迴兩層：return akm(m - 1, akm(m, n - 1));
3. 主程式中要求使用者輸入 m 和 n，並呼叫遞迴函式輸出結果。

**非遞迴版本**
1. 使用 stack 模擬函數呼叫堆疊。
2. 將 m 推入堆疊。
3. 迴圈中依據 Ackermann 函數定義進行堆疊操作：

   若 m == 0，n = n + 1；

   若 n == 0，推入 (m - 1) 並設 n = 1；

   m、n 都不等於 0，先推入 (m - 1) 與 m，並將 n = n - 1，模擬雙層遞迴。
4. 重複堆疊處理直到堆疊清空，最後回傳 n 為結果。   
5. 主程式中要求使用者輸入 m 和 n，並呼叫非遞迴函式輸出結果。

## 程式實作

以下為主要程式碼：

**遞迴版本：**
```cpp
#include <iostream>        
#include <string>          
using namespace std;     

int akm(int m, int n)
{
    if (m == 0)            
    {
        return n + 1;       
    }
    else if (n == 0)       
    {
        return akm(m - 1, 1); 
    }
    else                 
    {
        return akm(m - 1, akm(m, n - 1));
    }
}

int main() {                             
    unsigned int m, n;                   
    cout << "Enter m and n: ";          
    cin >> m >> n;                       
    cout << "Ackermann(" << m << ", " << n << ") = " << akm(m, n) << endl;
    return 0;                           
}
```
**非遞迴版本：**
```cpp
#include <iostream>
#include <stack>
using namespace std;

unsigned int akm(unsigned int m, unsigned int n) {
    stack<unsigned int> stk;
    stk.push(m);

    while (!stk.empty()) {
        m = stk.top();
        stk.pop();

        if (m == 0) {
            n = n + 1;
        }
        else if (n == 0) {
            n = 1;
            stk.push(m - 1);
        }
        else {
            stk.push(m - 1);
            stk.push(m);
            n = n - 1;
        }
    }
    return n;
}

int main() {
    unsigned int m, n;
    cout << "Enter m and n: ";
    cin >> m >> n;
    cout << "Ackermann(" << m << ", " << n << ") = " << akm(m, n) << endl;
    return 0;
}
```

## 效能分析

1. **時間複雜度**：

    遞迴版本的時間複雜度為 O(A(m,n))，根據參數呈指數成長。


    非遞迴版本遞迴版本的時間複雜度為 O(遞迴深度)=O(A(m,n))。


2. **空間複雜度**：
    
    遞迴版本的空間複雜度為 O(A(m,n))，與遞迴相同，根據參數呈指數成長。

    非遞迴版本的空間複雜度為 O(堆疊最大深度)=O(A(m,n))。

## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數 (m,n) | 預期輸出 | 實際輸出 |
|----------|----------------|----------|----------|
| 測試一   | (0, 0)         | 1        | 1        |
| 測試二   | (1, 0)         | 2        | 2        |
| 測試三   | (1, 2)         | 4        | 4        |
| 測試四   | (2, 2)         | 7        | 7        |
| 測試五   | (3, 3)         | 61       | 61       |

### 編譯與執行指令

```bash
$ g++ -std=c++17 -o ackermann ackermann.cpp
$ ./ackermann
Enter m and n: 2 2
Ackermann(2, 2) = 7
```

## 結論

1. 本程式能正確實作 Ackermann 函數，能依輸入 m 與 n 計算𝐴(𝑚,𝑛)的值。
2. 測試的案例覆蓋常見範圍，並結果正確。
3. 要注意輸入數值過大（如 m=4）可能造成堆疊溢位。

## 申論與開發報告

### 遞迴寫法

1. **系統呼叫堆疊（Call Stack）**  

   遞迴過程中每次函數呼叫都會壓入系統堆疊，保存變數與返回位址。

   系統自動管理遞迴的狀態與返回順序。

2. **Divide and Conquer（分治法）思想**  

   每一個 akm(m,n) 的呼叫會遞減地處理 m 和 n，直到觸發基本情況（m==0 或 n==0）。

   將原問題分解為更小的子問題，再組合子問題的結果。

   使用遞迴寫法原因：
   因為 Ackermann 函數本身就是依據數學遞迴定義來設計，使用系統遞迴呼叫自然地對應其數學結構，且適合展示極端遞迴深度與程式語言對堆疊的支援極限。

### 非遞迴寫法

1. **自訂堆疊（Stack 資料結構）**  

   使用 stack<pair<int,int>> 來手動模擬遞迴過程中 m 與 n 的狀態。

   每當要遞迴時，將參數推入堆疊，代替系統堆疊。

2. **模擬狀態機（State Machine 模式）**  

   程式需要自行追蹤執行狀態與下一步決策，如：

   m == 0 ➜ n + 1

   n == 0 ➜ akm(m-1, 1)

   否則 ➜ akm(m-1, akm(m, n-1))
   
   使用非遞迴寫法原因：

   非遞迴寫法能避免系統堆疊溢位（stack overflow），特別是在 m 與 n 較大時，對於程式可控性也更高，可進行更細緻的記憶體與效能管理，也更好除錯與追蹤。


# 作業一
Problem 2

## 解題說明

本題要求撰寫一個遞迴程式，列出輸入集合的所有子集合 powerset(S)。

### 解題策略

1. 使用遞迴函式將「產生所有子集合」的問題拆解為兩種子問題：
    
    一、包含當前字元
    
    二、不包含當前字元
    
2. 每個字元都有兩種選擇，故對長度為 $n$ 的集合，會產生 $2^n$ 個子集合。
3. 當遞迴至字串結尾（ input[index] == '\\0'），即為遞迴終止條件，輸出目前累積的子集合內容。

## 程式實作

以下為主要程式碼：

```cpp
#include <cstdio>    
#include <cstring>   
#include <iostream>  

using namespace std; 

const int MAX = 100;    
char input[MAX];         
char subset[MAX];        

void powerSet(int index, int length) {

    if (input[index] == '\0') {
        subset[length] = '\0';      
        printf("(");                
        for (int i = 0; subset[i]; ++i) {
            printf("%c", subset[i]); 
        }
        printf(")\n");            
        return;
    }

    powerSet(index + 1, length);
    subset[length] = input[index];
    powerSet(index + 1, length + 1);
}

int main() {
    cout << "Enter set: ";    
    cin >> input;              
    printf("Power set:\n");   
    powerSet(0, 0);            
    return 0;
}
```

## 效能分析

1. **時間複雜度**：每個元素都有選擇或不選擇兩種情況，共會產生 $2^n$ 個子集，所以時間複雜度為 $O(2^n)$。
2. **空間複雜度**：遞迴深度最深為 n，額外使用 subset 陣列儲存中間結果，所以空間複雜度為 $O(n)$。

## 測試與驗證

### 測試案例

| 測試案例 | 輸入集合 | 預期輸出子集合數 | 實際輸出 |
|----------|----------|------------------|-----------|
| 測試一   | a        | 2                | (), (a)   |
| 測試二   | ab       | 4                | (), (a), (b), (ab) |
| 測試三   | abc      | 8                | 所有組合  |

### 編譯與執行指令

```bash
$ g++ -std=c++17 -o powerset powerset.cpp
$ ./powerset
Enter set: ab
Power set:
()
(b)
(a)
(ab)
```

## 結論

1. 程式成功列出所有輸入集合的子集合，並符合遞迴解題策略。
2. 使用遞迴可以清楚表達每個元素的選擇過程，程式碼結構清楚。
3. 輸入集合長度增加會指數級增長，需要控制輸入長度避免大量輸出。

## 申論與開發報告

1. **使用的資料結構：字元陣列 char [ ]**
 
   為了儲存輸入集合（如 abc）與正在組合的子集合（subset [ ]），使用 char 陣列即可達成。

   不需要使用額外如 vector 或 string，可以直接操作字元陣列來提升效率。

   使用 C-style 字串（以 '\0' 結尾）方便判斷字串結束並輸出。

2. **使用的演算法：遞迴演算法**  
  
   子集產生問題本質上是一個二元選擇的遞迴問題：每個元素「選擇」或「不選擇」。

   遞迴可以很好的表達「選或不選」的決策樹結構，讓程式碼簡潔、邏輯清晰。

   遞迴過程中使用 call stack 隱式記錄狀態，避免手動管理堆疊或回朔陣列。

3. **遞迴結合資料結構的好處：** 

   每次遞迴呼叫只處理一個元素，並透過 subset[] 記錄目前的子集合。

   input [ ] 保持不變，遞迴依序決定是否將其中的每個字元加入 subset [ ] 中。

   終止條件為 input[index] == '\0'，表示走訪完畢，即可輸出子集合。  

透過這次作業讓我更好的了解到遞迴在數學與程式設計的關係，在 Ackermann 函數中即使輸入值非常小但結果仍會快速膨脹，導致計算資源用盡，讓我知道做好記憶體與資源管理也相當重要，以及更清楚在 power set 遞迴的實作時進行決策過程。
