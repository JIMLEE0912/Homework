#include <cstdio>    // 引入 C 標準輸出入函式，例如 printf
#include <cstring>   // 引入 C 字串處理函式，例如 strcpy, strlen 等
#include <iostream>  // 引入 C++ 輸入輸出函式，例如 cin、cout

using namespace std; // 使用 std 命名空間，省略寫 std:: 前綴

const int MAX = 100;      // 定義最大字元長度，限制輸入集合大小
char input[MAX];          // 儲存使用者輸入的原始集合（例如 "abc"）
char subset[MAX];         // 用來暫存目前的子集合內容（用來組合）

// 遞迴產生冪集合 power set
// index：目前處理 input 的第幾個字元
// length：目前子集合 subset 的長度
void powerSet(int index, int length) {
    // 遞迴終止條件：當走到 input 的結尾（null terminator '\0'）
    if (input[index] == '\0') {
        subset[length] = '\0';      // 為 subset 加上字串結尾符號
        printf("(");                // 輸出子集合開頭的括號
        for (int i = 0; subset[i]; ++i) { // 印出子集合中每個字元
            printf("%c", subset[i]);
        }
        printf(")\n");              // 輸出子集合結尾的括號與換行
        return;                     // 回到上一層遞迴
    }

    // 情況 1：不包含 input[index]，直接跳過此字元
    powerSet(index + 1, length);

    // 情況 2：包含 input[index]，加入 subset 再遞迴
    subset[length] = input[index];           // 把當前字元加到 subset 中
    powerSet(index + 1, length + 1);         // 遞迴下一個字元，並更新 subset 長度
}

int main() {
    cout << "Enter set: "; // 提示使用者輸入集合
    cin >> input;                      // 讀取輸入字串到 input 陣列

    printf("Power set:\n");           // 輸出標題文字
    powerSet(0, 0);                   // 從 index=0、length=0 開始遞迴產生 power set

    return 0;                         // 程式結束
}
