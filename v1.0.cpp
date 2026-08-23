#include <iostream>
#include <string>
#include <cstdlib>
#include <windows.h>
using namespace std;

class Game {
public:
    int turn; // 回合数

    struct Resources {
        int Groschen;   // 钱
        int population; // 人口
        int food;       // 食物
        int timber;     // 木头
        int iron;       // 铁
        int stone;      // 石头
        int steel;      // 钢
        int silver;     // 银
    } res;//创建对象

    // 构造函数
    Game() {
        turn = 1;
        res.Groschen = 100000;
        res.population = 1000;
        res.food = 1000;
        res.timber = 500;
        res.iron = 200;
        res.stone = 500;
        res.steel = 0;
        res.silver = 0;
    }

    // 回合函数
    void showStatus() {
        system("cls");
        cout << "第 " << turn << " 回合" << endl;
        cout << "钱：" << res.Groschen << endl;
        cout << "人口：" << res.population << endl;
        cout << "食物：" << res.food << endl;
        cout << "木头：" << res.timber << endl;
        cout << "铁：" << res.iron << endl;
        cout << "石头：" << res.stone << endl;
        cout << "钢：" << res.steel << endl;
        cout << "银：" << res.silver << endl;
    }

    // 游戏开场剧情
    void Opening_scene() {
        system("cls");
        cout << "1435年的波西米亚，胡斯战争已经打了十五年。去年，圣杯派的贵族和城市联军在利帕尼战场消灭了激进的塔博尔派主力。战争虽然还没正式结束，但最激烈的流血已经停了。\n";
        system("pause");
        system("cls");

        cout << "现在的波西米亚处于一种微妙的平衡状态。作为妥协，圣杯派信徒获准领受圣杯，但教皇拒绝承认这一协定。西吉斯蒙德虽然是名义上的国王，但他还在和帝国扯皮，并不常驻布拉格。真正的权力掌握在由贵族和城市议员组成的议会手中。\n";
        system("pause");
        system("cls");

        cout << "你今年十五岁，是查理大学文学院的学生。你的父亲是乡下的圣杯派乡绅，靠着在战争中站队正确，保住了那点微薄的领地。小时候为了躲避战火，你被送进布拉格，在那之后就没怎么回过家。\n";
        system("pause");
        system("cls");

        cout << "现在的你，每天穿梭在布拉格的石板路和大学回廊里。身边是还没散尽的硝烟味，以及这座城市在战后试图重建秩序的嘈杂声。你的父亲来信，希望你多学些法律和神学，将来好回去守住家族的根基。但在这座城市里，关于信仰、法律和权力的争论，远比课本上要复杂。\n";
        system("pause");
        system("cls");
    }
};

class character{
    struct player_attribute{
        
    } pla_a;
    struct npc_attribute{
        
    } npc_a;
};
int main() {
    Game game;
    return 0;
}
