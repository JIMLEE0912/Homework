#include <iostream>        // 引入標準輸入輸出函式庫，用來使用 cin 和 cout
#include <string>          // 雖然本程式沒用到 string，可以移除；但不影響執行
using namespace std;       // 使用 std 命名空間，這樣就不用每次寫 std::cout 之類的

int akm(int m, int n)       // 宣告 Ackermann 函數，接收兩個整數 m 與 n
{
    if (m == 0)             // 根據 Ackermann 函數定義：如果 m 是 0
    {
        return n + 1;       // 就回傳 n+1
    }
    else if (n == 0)        // 否則如果 n 是 0
    {
        return akm(m - 1, 1); // 根據遞迴定義：呼叫 akm(m-1, 1)
    }
    else                    // 如果 m ≠ 0 且 n ≠ 0 的情況
    {
        // 遞迴呼叫：先算 akm(m, n-1)，再將結果當作第二參數遞迴呼叫 akm(m-1, 結果)
        return akm(m - 1, akm(m, n - 1));
    }
}


int main() {                             // 主程式進入點
    unsigned int m, n;                   // 宣告兩個無號整數 m 和 n
    cout << "Enter m and n: ";           // 提示使用者輸入 m 和 n
    cin >> m >> n;                       // 從鍵盤讀入 m 和 n 的值
    // 輸出結果：顯示使用者輸入的 m 和 n 對應的 Ackermann 值
    cout << "Ackermann(" << m << ", " << n << ") = " << akm(m, n) << endl;
    return 0;                            // 結束程式，回傳 0 給作業系統
}

