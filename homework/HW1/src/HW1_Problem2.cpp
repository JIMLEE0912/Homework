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
