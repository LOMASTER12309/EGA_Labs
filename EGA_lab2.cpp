#include <iostream>
#include <ctime>
#include <bitset>
#include <vector>
#include <math.h>
#define L 5
using namespace std;

vector <bitset<L>> neighborhood(int num);

int main()
{
    setlocale(LC_ALL, "rus");
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
        for (int i = 0; i < pow(2,L); i++) {
            adap.push_back(rand());
        }
        break;
    case '2':
        for (int i = 0; i < pow(2,L); i++) adap.push_back(i);
        break;
    case '3':
        for (int i = 0; i < pow(2,L); i++) adap.push_back(pow(i - pow(2, L - 1), 2));
        break;
    }
    srand(time(NULL));
    cout << "Ландшафт поиска: \n";
    for (int i = 0; i < 32; i++) {
        int cur = rand() % (int)pow(2,L);
        cout << bitset<L>(cur) << ": " << adap[cur] << "\n";
    }
    cout << "...и т.д.\n";
    cout << "Введите объём выборки N = ";
    cin >> N;
    int i = 0;
    int cur = rand() % (int)pow(2, L);
    bitset<L> curCode = bitset<L>(cur);
    int curAdap = adap[cur];
    int max = curAdap;
    bitset<L> maxS = bitset<L>(cur);
    vector<bitset<L>> okr = neighborhood(cur);
    while (i < N) {
        if (okr.size() > 0) {
            i++;
            cout << "Шаг " << i << ": " << "max = " << max << "| maxS = " << maxS << "| s(" << i << ") = " << bitset<L>(cur) << "| u(s(" << i << ")) = " << curAdap << "\n";
            int rand_cand = rand() % okr.size();
            curCode = okr[rand_cand];
            cout << "Текущая окрестность:\n";
            for (int j = 0; j < okr.size(); j++) {
                cout << okr[j] << ": " << adap[okr[j].to_ulong()];
                if (okr[j] == curCode) cout << " <--";
                cout << "\n";
            }
            okr.erase(okr.begin() + rand_cand);
            cur = curCode.to_ulong();
            curAdap = adap[cur];
            if (max < adap[cur]) {
                maxS = curCode;
                max = adap[cur];
                okr = neighborhood(cur);
                cout << "Смена максимума: " << "max = " << max << "| maxS = " << maxS << "\n";
            }
        }
        else break;
    }
    cout << "Лучший результат: " << "max = " << max << "| maxS = " << maxS << "\n";
}

vector <bitset<L>> neighborhood(int num) {
    vector<bitset<L>> mas;
    for (int i = 0; i < L; i++)
        mas.push_back(bitset<L>(num).flip(i));
    return mas;
}