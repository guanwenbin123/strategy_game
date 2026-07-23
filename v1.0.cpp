#include <iostream>
#include <string>
using namespace std;
class aa {
public:
    int a;
    string b;
    struct bb {
        int bb_M;
        int bb_F;
        int bb_W;
        int bb_I;
        int bb_S;
        int bb_G;
    };
    aa() {
        bb dd;
        dd.bb_M = 500;//钱
        dd.bb_F = 1000;//食物
        dd.bb_W = 500;//木头
        dd.bb_I = 200;//铁
        dd.bb_Stone = 500;//石头
		dd.bb_Steel = 0;//钢
		dd.bb_silver = 0;//银

    }
    void cc() {
        cout << " " << ;
    }
}
int main() {
    aa GAME;
    GAME.cc();
}
