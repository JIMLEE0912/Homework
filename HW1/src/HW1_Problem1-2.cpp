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
