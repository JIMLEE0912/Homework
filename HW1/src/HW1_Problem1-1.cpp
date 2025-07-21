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

