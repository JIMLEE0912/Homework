#include <iostream>        // �ޤJ�зǿ�J��X�禡�w�A�ΨӨϥ� cin �M cout
#include <string>          // ���M���{���S�Ψ� string�A�i�H�����F�����v�T����
using namespace std;       // �ϥ� std �R�W�Ŷ��A�o�˴N���ΨC���g std::cout ������

int akm(int m, int n)       // �ŧi Ackermann ��ơA������Ӿ�� m �P n
{
    if (m == 0)             // �ھ� Ackermann ��Ʃw�q�G�p�G m �O 0
    {
        return n + 1;       // �N�^�� n+1
    }
    else if (n == 0)        // �_�h�p�G n �O 0
    {
        return akm(m - 1, 1); // �ھڻ��j�w�q�G�I�s akm(m-1, 1)
    }
    else                    // �p�G m �� 0 �B n �� 0 �����p
    {
        // ���j�I�s�G���� akm(m, n-1)�A�A�N���G��@�ĤG�Ѽƻ��j�I�s akm(m-1, ���G)
        return akm(m - 1, akm(m, n - 1));
    }
}


int main() {                             // �D�{���i�J�I
    unsigned int m, n;                   // �ŧi��ӵL����� m �M n
    cout << "Enter m and n: ";           // ���ܨϥΪ̿�J m �M n
    cin >> m >> n;                       // �q��LŪ�J m �M n ����
    // ��X���G�G��ܨϥΪ̿�J�� m �M n ������ Ackermann ��
    cout << "Ackermann(" << m << ", " << n << ") = " << akm(m, n) << endl;
    return 0;                            // �����{���A�^�� 0 ���@�~�t��
}

