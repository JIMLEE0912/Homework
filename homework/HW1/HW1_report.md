
# 李柏均 41141123 

作業一  Problem 1    

## 解題說明

本題要求實作一個遞迴函式 — Ackermann 函數，計算𝐴(𝑚,𝑛)的值。

## 解題策略
**遞迴版本**
1. 根據 Ackermann 函數的數學定義實作三種遞迴情況：  
 $$
A(m,n) = \begin{cases}
n + 1 & \text{if } m = 0 \\
A(m-1, 1) & \text{if } n = 0 \\
A(m-1, A(m, n-1)) & \text{otherwise}
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

### 選擇遞迴的原因

Ackermann 函數的定義本身就是一種遞迴結構，因此以遞迴實作最為自然，原因如下：

1. **符合數學遞迴定義**  
   Ackermann 函數使用三層條件來表示不同情況的遞迴關係，遞迴寫法能直接對應公式。

2. **遞迴語意清晰**  
   每一次遞迴呼叫都是子問題的處理，最終組合成整體解答。

3. **適合展示遞迴的威力與風險**  
   此函數是少數無法用一般迴圈取代的遞迴函數之一，很適合展示深層遞迴與堆疊限制。




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

### 遞迴設計優點

1. 每次遞迴只處理一個字元，並分支為「選或不選」，自然對應到二元決策樹。
2. 程式具備高度可讀性與可維護性，邏輯清晰簡單。
3. 可以輕鬆地列出所有可能組合，不用手動管理迴圈或狀態。
