#include <iostream>
#include <string>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
using namespace std;

class during_university{
public:
    int turn_number; // 回合数
    int choice;
    int groschen;    //钱
    struct player_attribute{
        int satiety_value;//饱腹值
        int mood;//心情
        int health;//健康
        int academic;//学识
        int finance;//财政
        int Military;//军事
    } pla_a;
    struct npc_attribute{
        int Favorability;
    } ;
    // 物品类型枚举
    enum ItemType {
        FOOD,       // 食物（可吃，加饱腹/心情）
        BOOK,       // 书籍（学习用，加属性）
        ATTIRE,    // 装束
        TOOL,       // 工具
        VALUABLE,   // 值钱的东西
        MISC        // 杂物
    };

    // 狼牙项链
    struct wolf_tooth{
        string name;        // 物品名称
        ItemType type;      // 物品类型
        string description; // 描述文字
        int quantity;       // 数量（堆叠用）
        int storage_location;//储存位置,1:行李 2:背包 3:被装备 0：已使用，交出，失去
        int passive_bonus;  // 被动加成，装备后所有检定成功率+10%
    }; wol
    
    struct Item {
        string name;        // 物品名称
        ItemType type;      // 物品类型
        string description; // 描述文字
        int value;          // 效果值（食物的饱腹恢复量 / 书籍的属性加成等）
        int price;          // 卖价（格罗申）
        int quantity;       // 数量（堆叠用）
    };
    Game() {
        turn_number = 1;
        groschen = 100;
        wol.name = "狼牙项链";
        wol.type = VALUABLE;
        wol.description = ""
    }
    // 游戏开场剧情
    void Opening_scene() {
        cout << "1436年秋，波西米亚。" << endl;
    cout << "你十六岁，刚刚踏入布拉格查理大学的艺学院。" << endl;
    cout << "你的名字是Jan z Vlkanova。" << endl;
    system("pause");
    system("cls");

    cout << "十四年前你出生时，胡斯被烧死在康斯坦茨。十四年间，这片土地没有一天不在流血。" << endl;
    cout << "你的父亲——符尔卡诺夫的小领主，带着圣杯派的战旗活过了战争。" << endl;
    cout << "但他向西吉斯蒙德国王交出的那笔赎金，几乎掏空了城堡下的每一个钱袋。" << endl;
    system("pause");
    system("cls");

    cout << "你的母亲来自米兰，一个意大利贵族之女。童年时她带你躲进布拉格，" << endl;
    cout << "用带着托斯卡纳口音的拉丁语教你读书写字。" << endl;
    cout << "三天前她回了符尔卡诺夫城堡，临走时只说了一句：\"别跟酒馆里的粗人学坏。\"" << endl;
    system("pause");
    system("cls");

    cout << "如今，里潘战役的尸骨已经凉了，塔博尔派退守南方，西吉斯蒙德坐在布拉格的王座上。" << endl;
    cout << "《伊格劳协定》让圣杯派暂时赢了，但谁都看得出来——这和平撑不了多久。" << endl;
    cout << "而你，一个穷贵族的儿子，站在这座城市的石厅里，长袍上沾着从乡下带来的尘土。" << endl;
    cout << "你的大学第一天，开始了。" << endl;
    system("pause");
    system("cls");
    cout << "早上8点，提恩教堂的钟声你从宿舍的稻草垫上叫起来，阳光透过窗户照到你的身上，你撑起身，环顾四周：这间屋子不大，石墙潮得发青，角落里还对着你的行李" << endl;
    system("pause");
    system("cls");
    cout << "按1打开行李" << endl;
    if(_getch() == 1)
    }
    void start_day(){
        
    }
};
int main() {
    during_university game1;
    return 0;
}
    
    
