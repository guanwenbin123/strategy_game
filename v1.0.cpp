#include <iostream>
#include <string>
using namespace std;
class aa {
public:
    int a;//回合
    string b;
    struct bb {
        int bb_M;
        int bb_P;
        int bb_F;
        int bb_W;
        int bb_I;
        int bb_S;
        int bb_G;
    };
    aa() {
        b = "";
        bb dd;
        dd.bb_M = 500;//钱
		dd.bb_P = 1000;//人口
        dd.bb_F = 1000;//食物
        dd.bb_W = 500;//木头
        dd.bb_I = 200;//铁
        dd.bb_Stone = 500;//石头
		dd.bb_Steel = 0;//钢
		dd.bb_silver = 0;//银
    }
    void cc() {
        cout << "现在是" << a << "回合" << endl;
        cout << "钱：" << dd.bb_M;
        cout << "人口：" << dd.bb_P;
        cout << "食物：" << dd.bb_F;
        cout << "木头：" << dd.bb_W;
        cout << "铁：" << dd.bb_I;
        cout << "石头：" << dd.bb_Stone;
        cout << "钢：" << dd.bb_Steel;
        cout << "银：" << dd.bb_silver；
    }
    void dd() {
        cout << "" << ;

    }
}
int main() {
    aa GAME;
    GAME.cc();
}
