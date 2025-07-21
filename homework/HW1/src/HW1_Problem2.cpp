#include <cstdio>    // �ޤJ C �зǿ�X�J�禡�A�Ҧp printf
#include <cstring>   // �ޤJ C �r��B�z�禡�A�Ҧp strcpy, strlen ��
#include <iostream>  // �ޤJ C++ ��J��X�禡�A�Ҧp cin�Bcout

using namespace std; // �ϥ� std �R�W�Ŷ��A�ٲ��g std:: �e��

const int MAX = 100;      // �w�q�̤j�r�����סA�����J���X�j�p
char input[MAX];          // �x�s�ϥΪ̿�J����l���X�]�Ҧp "abc"�^
char subset[MAX];         // �ΨӼȦs�ثe���l���X���e�]�ΨӲզX�^

// ���j���;����X power set
// index�G�ثe�B�z input ���ĴX�Ӧr��
// length�G�ثe�l���X subset ������
void powerSet(int index, int length) {
    // ���j�פ����G���� input �������]null terminator '\0'�^
    if (input[index] == '\0') {
        subset[length] = '\0';      // �� subset �[�W�r�굲���Ÿ�
        printf("(");                // ��X�l���X�}�Y���A��
        for (int i = 0; subset[i]; ++i) { // �L�X�l���X���C�Ӧr��
            printf("%c", subset[i]);
        }
        printf(")\n");              // ��X�l���X�������A���P����
        return;                     // �^��W�@�h���j
    }

    // ���p 1�G���]�t input[index]�A�������L���r��
    powerSet(index + 1, length);

    // ���p 2�G�]�t input[index]�A�[�J subset �A���j
    subset[length] = input[index];           // ���e�r���[�� subset ��
    powerSet(index + 1, length + 1);         // ���j�U�@�Ӧr���A�ç�s subset ����
}

int main() {
    cout << "Enter set: "; // ���ܨϥΪ̿�J���X
    cin >> input;                      // Ū����J�r��� input �}�C

    printf("Power set:\n");           // ��X���D��r
    powerSet(0, 0);                   // �q index=0�Blength=0 �}�l���j���� power set

    return 0;                         // �{������
}
