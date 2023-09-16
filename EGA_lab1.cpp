#include <iostream>
#include <ctime>
#include <bitset>
#include <vector>
#include <math.h>
using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");
    const int L = 15;
    cout << "Пространство поиска сосотит из двоичных кодировок s(i) длинны L=15\n";
    cout << "Выберите каким способом приспособленность будет определяться: \n";
    cout << "1. Случайное задание приспособленностей\n";
    cout << "2. Приспособленность соответствует натуральному значению бинарного кода\n";
    cout << "3. Приспособленность вычисляется как квадратичная функция: u(s(i)) = (x(i) - 2^(L-1))^2\n";
    char mod = ' ';
    vector <int> adap;
    int N = 0;
    cin >> mod;
    switch (mod) {
    case '1':
        srand(time(NULL));
        for (int i = 0; i < 32798; i++) {
            adap.push_back(rand());
        }
        break;
    case '2':
        for (int i = 0; i < 32798; i++) adap.push_back(i);
        break;
    case '3':
        for (int i = 0; i < 32798; i++) adap.push_back(pow(i - pow(2, L - 1), 2));
        break;
    }
    srand(time(NULL));
    cout << "Ландшафт поиска: \n";
    for (int i = 0; i < 32; i++) {
        int cur = rand();
        cout << bitset<L>(cur) << ": " << adap[cur] << "\n";
    }
    cout << "...и т.д.\n";
    cout << "Введите объём выборки N = ";
    cin >> N;
        int i = 0;
        int max = 0;
        bitset<L> maxS;
        srand(time(NULL));
        int cur = 0;
        int curAdap = 0;
        while (i < N) {
            cur = rand();
            curAdap = adap[cur];
            cout << "Шаг " << i << ": " << "max = " << max << "| maxS = " << maxS << "| s(" << i << ") = " << bitset<L>(cur) << "| u(s(" << i << ")) = " << curAdap << "\n";
            if (max < curAdap) {
                max = curAdap;
                maxS = bitset<L>(cur);
                cout << "Смена максимума: " << "max = " << max << "| maxS = " << maxS << "\n";
            }
            i++;
        }
        cout << "Лучший результат: " << "max = " << max << "| maxS = " << maxS << "\n";
}