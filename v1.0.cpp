#include <iostream>
#include <string>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class during_university {
public:
    int turn_number;                    //回合数
    int days;                           //天数
    int clock;                          //时间
    int i_input1;
    int i_input2;
    char c_input;
    int groschen;                       //钱

    //玩家属性类型定义
    struct player_attribute {
        int satiety_value;              //饱腹值
        int mood;                       //心情
        int Learning_efficiency;        //学习效率
        int achievement;                //成就
        int health;                     //健康
        int charm;                      //魅力
        int academic;                   //学识
        int logic;                      //逻辑
        int eloquence;                  //口才
        int make_skill;                 //制作技能
    } pla_a;

    struct npc_attribute {
        int Favorability;
    };

    // 物品类型枚举
    enum ItemType {
        FOOD,                            // 食物
        MEDICINE,                        // 药剂
        BOOK,                            // 书籍
        ATTIRE,                          // 装束
        TOOL,                            // 工具
        VALUABLE,                        // 宝物
        MISC,                            // 杂物
        MATERIAL                         // 材料
    };

    // 食物
    struct food_information {
        string name;                    //物品名称
        ItemType type;                  //物品类型
        string description;             //描述文字
        string after_use;               //食用感受
        int satiety_gain;               //饱腹获得
        int mood_gain;                  //心情获得
        int health_gain;                //健康获得
        int warehouse_quantity;		    //仓库数量
        int bag_quantity;               //背包数量
        vector<int> warehouse_shelf_life;//仓库保质期
        vector<int> bag_shelf_life;     //背包保质期
        int shelf_life;                 //总保质期
    };
    //装束
    struct attire_information {
        string name;                    //物品名称
        ItemType type;                  //物品类型
        string description;             //描述文字
        int durability;                 //耐久度
        int Learning_efficiency_gain;   //学习效率加成

    };
    //制作
    struct CraftingRecipe {
        string result_name;             // 做出来的东西叫啥
        vector<string> mat_names;       // 需要哪些材料
        vector<int> mat_counts;         // 每种要几个
        int skill_required;             // 需要的制作技能等级
    };

    vector <food_information> food_storage;//食物储存
    vector <attire_information> attire_storage;//装束储存


    during_university() {

        turn_number = 1;
        days = 1;
        clock = 8;
        groschen = 100;

        food_information black_bread;
        black_bread.name = "黑面包";
        black_bread.type = FOOD;
        black_bread.description = "制作粗糙的面包,口感不佳,能填饱肚子,是布拉格街头上最常见和最廉价的食物之一";
        black_bread.after_use = "你掰下一块，硬得像瓦片。放进嘴里嚼了半天，麦壳的粗粝感刮着舌头，酸涩里带点坚果味";
        black_bread.satiety_gain = 20;
        black_bread.mood_gain = 5;
        black_bread.health_gain = 0;
        black_bread.warehouse_quantity = 2;
        black_bread.bag_quantity = 0;
        black_bread.shelf_life = 100;
        black_bread.warehouse_shelf_life.push_back(100);
        black_bread.warehouse_shelf_life.push_back(100);
        food_storage.push_back(black_bread);
    }
    // 游戏开场剧情
    void Opening_scene() {
        type_text("1436年秋，波西米亚。");
        type_text("你十六岁，即将踏入布拉格查理大学的艺学院。");
        type_text("你的名字是Jan z Vlkanova。");
        wait_key();

        type_text("十四年前你出生时，胡斯被烧死在康斯坦茨。十四年间，这片土地没有一天不在流血。");
        type_text("你的父亲——符尔卡诺夫的小领主，带着圣杯派的战旗活过了战争。");
        type_text("但他向西吉斯蒙德国王交出的那笔赎金，几乎掏空了城堡下的每一个钱袋。");
        wait_key();

        type_text("你的母亲来自米兰，一个意大利贵族之女。用带着托斯卡纳口音的拉丁语教你读书写字。");
        type_text("你长大了，你的母亲送你来到布拉格查理大学读书");
        type_text("昨天前她回了符尔卡诺夫城堡，临走时只说了一句：\"别让你父亲失望\"");
        wait_key();

        type_text("如今，里潘战役的尸骨已经凉了，塔博尔派退守南方，西吉斯蒙德坐在布拉格的王座上。");
        type_text("《伊格劳协定》让圣杯派暂时赢了，但谁都看得出来——这和平撑不了多久。");
        type_text("而你，一个穷贵族的儿子，站在这座城市的石厅里，长袍上沾着从乡下带来的尘土。");
        type_text("你的大学第一天，开始了。");
        wait_key();

        type_text("早上8点，提恩教堂的钟声把你从宿舍的稻草垫上叫起来，阳光透过窗户照到你的身上，你撑起身，环顾四周：这间屋子不大，石墙潮得发青，角落里还堆着你的行李");
        wait_key();

        type_text("按1打开行李,这里就是你的仓库,你可以在这里存放或者拿取东西");
        map <int, int> lookup_f;//查看物品映射
        int a = 1, i = 0;
        system("cls");
        cout << "===============================1.行李===============================" << endl;
        cout << "===============================2.背包===============================" << endl;
        cout << "按1打开仓库菜单，你可以在这里使用，丢弃，物品，或者存入背包" << endl;
        i_input1 = get_input(1, 1);
        if (i_input1 == 1) {
            system("cls");
            cout << "===============================行李===============================" << endl;
            cout << "[1.食物][2.药剂][3.书籍][4.装束][5.工具][6.值钱的东西][7.杂物][8.材料]" << endl;
            cout << "上面是你仓库里的物品种类，你可以按下对应的数字查看物品，现在按1查看食物" << endl;
            i_input1 = get_input(1, 1);
            system("cls");
            //显示物品
            if (i_input1 == 1) {
                cout << "===============================食物===============================" << endl;
                for (i = 0; i < food_storage.size(); i++) {
                    if (food_storage[i].warehouse_quantity != 0) {
                        lookup_f[a] = i;
                        cout << "[" << a << "." << food_storage[i].name << "×" << food_storage[i].warehouse_quantity << "]";
                        a++;
                    }
                }
                cout << "这里显示了你仓库里的食物，你可以按下对应的数字查看物品详情，现在按下1查看面包" << endl;
                i_input1 = get_input(1, a - 1);
                cout << i_input1 << endl;
                //物品详情
                system("cls");
                cout << "==============================================================" << endl;
                cout << "名称:" << food_storage[lookup_f[i_input1]].name << endl;
                cout << "数量:" << food_storage[lookup_f[i_input1]].warehouse_quantity << endl;
                cout << "类型:食物" << endl;
                cout << "饱腹获得:" << food_storage[lookup_f[i_input1]].satiety_gain << endl;
                cout << "心情获得:" << food_storage[lookup_f[i_input1]].mood_gain << endl;
                cout << "健康获得:" << food_storage[lookup_f[i_input1]].health_gain << endl;
                cout << "总新鲜时间:" << food_storage[lookup_f[i_input1]].shelf_life << endl;
                cout << "每个的新鲜时间:" << endl;
                for (int i = 0; i < food_storage[lookup_f[i_input1]].warehouse_shelf_life.size(); i++) {
                    cout << "第" << i + 1 << "个:" << food_storage[lookup_f[i_input1]].warehouse_shelf_life[i] << endl;
                }
                cout << food_storage[lookup_f[i_input1]].description << endl;
                cout << "==============================================================" << endl;
                cout << "这里是你查看的物品详情，你可以选择取到背包，食用，或者丢弃，现在按下2食用" << endl;
                cout << "(1.取到背包) (2.食用 ) (3.丢弃)" << endl;
                i_input2 = get_input(2, 2);
                cout << i_input2 << endl;
                //对物品的操作
                if (food_storage[lookup_f[i_input1]].warehouse_quantity > 0) {
                    switch (i_input2) {
                    case 2:
                        pla_a.satiety_value += food_storage[lookup_f[i_input1]].satiety_gain;
                        pla_a.mood += food_storage[lookup_f[i_input1]].mood_gain;
                        pla_a.health += food_storage[lookup_f[i_input1]].health_gain;
                        food_storage[lookup_f[i_input1]].warehouse_quantity--;
                        wait_key();
                        type_text(food_storage[lookup_f[i_input1]].after_use);
                        cout << "目前总饱腹:" << pla_a.satiety_value << endl;
                        cout << "目前总心情:" << pla_a.mood << endl;
                        cout << "目前总健康:" << pla_a.health << endl;
                        food_storage[lookup_f[i_input1]].warehouse_shelf_life.pop_back();
                        break;
                    }
                }
            }
        }
		cout << "现在按1回到仓库菜单" << endl;
		i_input1 = get_input(1, 1);
        if (i_input1 == 1) {
            warehouse();
		}
    }
    //等待函数
    void wait_key() {
        cout << "\n按任意键继续...";
        cin.ignore();
        cin.get();
        system("cls");
    }

    // 逐字打印文字（带打字机效果）
    void type_text(const string& text, int delay = 10) {
        for (char c : text) {
            cout << c << flush;
            Sleep(delay);
        }
        cout << endl;
    }
    // 输入验证函数
    int get_input(int min, int max) {
        int input;
        while (true) {
            cin >> input;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "输入非法，请输入数字！" << endl;
                continue;
            }
            if (input < min || input > max) {
                cout << "请输入 " << min << "~" << max << " 之间的数字: ";
                continue;
            }
            return input;
        }
    }


    //主界面
    void main_interface() {
        cout << "==================主界面=================" << endl;
        cout << "现在是第" << days << "天" << endl;
        cout << "第" << clock << "小时" << endl;
        cout << ">-(1.查看属性和装备)" << endl;
        cout << ">-(2.打开背包)" << endl;
        cout << ">-(3.打开地图)" << endl;
        cout << ">-(4.查看地点)" << endl;
        cin >> i_input1;
        cout << i_input1 << endl;
        int a = i_input1;
        system("cls");
        switch (i_input1) {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        }
    }
    //22
    //每天第1回合
    void start_day() {

    }

    //仓库函数
    void warehouse() {
        map <int, int> lookup_f;//查看物品映射
        int a = 1, i = 0;
        system("cls");
        cout << "===============================1.行李===============================" << endl;
        cout << "===============================2.背包===============================" << endl;
        cout << "请输入你要打开的：" << endl;
        i_input1 = get_input(1, 2);
        if (i_input1 == 1) {
            system("cls");
            cout << "===============================行李===============================" << endl;
            cout << "[1.食物][2.药剂][3.书籍][4.装束][5.工具][6.值钱的东西][7.杂物][8.材料]" << endl;
            cout << endl << "请按下你要查看的物品序号种类:";
            i_input1 = get_input(1, 8);
            system("cls");
            //显示物品
            if (i_input1 == 1) {
                cout << "===============================食物===============================" << endl;
                for (i = 0; i < food_storage.size(); i++) {
                    if (food_storage[i].warehouse_quantity != 0) {
                        lookup_f[a] = i;
                        cout << "[" << a << "." << food_storage[i].name << "×" << food_storage[i].warehouse_quantity << "]";
                        a++;
                    }
                }
                cout << endl << "请选择你要查看的物品:";
                i_input1 = get_input(1, a - 1);
                cout << i_input1 << endl;
                //物品详情
                system("cls");
                cout << "==============================================================" << endl;
                cout << "名称:" << food_storage[lookup_f[i_input1]].name << endl;
                cout << "数量:" << food_storage[lookup_f[i_input1]].warehouse_quantity << endl;
                cout << "类型:食物" << endl;
                cout << "饱腹获得:" << food_storage[lookup_f[i_input1]].satiety_gain << endl;
                cout << "心情获得:" << food_storage[lookup_f[i_input1]].mood_gain << endl;
                cout << "健康获得:" << food_storage[lookup_f[i_input1]].health_gain << endl;
                cout << "总新鲜时间:" << food_storage[lookup_f[i_input1]].shelf_life << endl;
                cout << "每个的新鲜时间:" << endl;
                for (int i = 0; i < food_storage[lookup_f[i_input1]].warehouse_shelf_life.size(); i++) {
                    cout << "第" << i + 1 << "个:" << food_storage[lookup_f[i_input1]].warehouse_shelf_life[i] << endl;
                }
                cout << food_storage[lookup_f[i_input1]].description << endl;
                cout << "==============================================================" << endl;
                cout << "(1.取到背包) (2.食用 ) (3.丢弃)" << endl;
                cin >> i_input2;
                cout << i_input2 << endl;
                //对物品的操作
                if (food_storage[lookup_f[i_input1]].warehouse_quantity > 0) {
                    switch (i_input2) {
                        //取到背包
                    case 1:
                        food_storage[lookup_f[i_input1]].warehouse_quantity--;
                        food_storage[lookup_f[i_input1]].bag_quantity++;
                        food_storage[lookup_f[i_input1]].bag_shelf_life.push_back(food_storage[lookup_f[i_input1]].warehouse_shelf_life.back());
                        cout << "已取到背包" << endl;
                        break;
                        //食用
                    case 2:
                        pla_a.satiety_value += food_storage[lookup_f[i_input1]].satiety_gain;
                        pla_a.mood += food_storage[lookup_f[i_input1]].mood_gain;
                        pla_a.health += food_storage[lookup_f[i_input1]].health_gain;
                        food_storage[lookup_f[i_input1]].warehouse_quantity--;
                        wait_key();
                        type_text(food_storage[lookup_f[i_input1]].after_use);
                        cout << "目前总饱腹:" << pla_a.satiety_value << endl;
                        cout << "目前总心情:" << pla_a.mood << endl;
                        cout << "目前总健康:" << pla_a.health << endl;
                        food_storage[lookup_f[i_input1]].warehouse_shelf_life.pop_back();
                        break;
                        //丢弃
                    case 3:
                        food_storage[lookup_f[i_input1]].warehouse_quantity--;
                        food_storage[lookup_f[i_input1]].warehouse_shelf_life.pop_back();
                        break;
                        cout << "已丢弃一个" << endl;
                    }
                }
            }
            cout << "1.回到背包菜单" << endl;
            cout << "2.回到主界面" << endl;
            i_input1 = get_input(1, 2);
            if (i_input1 == 1) {
                warehouse();
            }
            else if (i_input1 == 2) {
                main_interface();
			}
        }
        else {
            if (i_input1 == 2) {
                system("cls");
                cout << "===============================背包===============================" << endl;
                cout << "[1.食物][2.药剂][3.书籍][4.装束][5.工具][6.值钱的东西][7.杂物][8.材料]" << endl;
                cout << endl << "请按下你要查看的物品序号种类:";
                i_input1 = get_input(1, 8);
                system("cls");
                //显示物品
                if (i_input1 == 1) {
                    cout << "===============================食物===============================" << endl;
                    for (i = 0; i < food_storage.size(); i++) {
                        if (food_storage[i].bag_quantity != 0) {
                            lookup_f[a] = i;
                            cout << "[" << a << "." << food_storage[i].name << "×" << food_storage[i].bag_quantity << "]";
                            a++;
                        }
                    }
                    cout << endl << "请选择你要查看的物品:";
                    i_input1 = get_input(1, a - 1);
                    cout << i_input1 << endl;
                    //物品详情
                    system("cls");
                    cout << "==============================================================" << endl;
                    cout << "名称:" << food_storage[lookup_f[i_input1]].name << endl;
                    cout << "数量:" << food_storage[lookup_f[i_input1]].bag_quantity << endl;
                    cout << "类型:食物" << endl;
                    cout << "饱腹获得:" << food_storage[lookup_f[i_input1]].satiety_gain << endl;
                    cout << "心情获得:" << food_storage[lookup_f[i_input1]].mood_gain << endl;
                    cout << "健康获得:" << food_storage[lookup_f[i_input1]].health_gain << endl;
                    cout << "总新鲜时间:" << food_storage[lookup_f[i_input1]].shelf_life << endl;
                    cout << "每个的新鲜时间:" << endl;
                    for (int i = 0; i < food_storage[lookup_f[i_input1]].bag_shelf_life.size(); i++) {
                        cout << "第" << i + 1 << "个:" << food_storage[lookup_f[i_input1]].bag_shelf_life[i] << endl;
                    }
                    cout << food_storage[lookup_f[i_input1]].description << endl;
                    cout << "==============================================================" << endl;
                    cout << "(1.取到背包) (2.食用 ) (3.丢弃)" << endl;
                    i_input2 = get_input(1, 3);
                    cout << i_input2 << endl;
                    //对物品的操作
                    if (food_storage[lookup_f[i_input1]].bag_quantity > 0) {
                        switch (i_input2) {
                            //取到行李
                        case 1:
                            food_storage[lookup_f[i_input1]].bag_quantity--;
                            food_storage[lookup_f[i_input1]].warehouse_quantity++;
                            food_storage[lookup_f[i_input1]].warehouse_shelf_life.push_back(food_storage[lookup_f[i_input1]].bag_shelf_life.back());
                            cout << "已取到行李" << endl;
                            break;
                            //食用
                        case 2:
                            pla_a.satiety_value += food_storage[lookup_f[i_input1]].satiety_gain;
                            pla_a.mood += food_storage[lookup_f[i_input1]].mood_gain;
                            pla_a.health += food_storage[lookup_f[i_input1]].health_gain;
                            food_storage[lookup_f[i_input1]].bag_quantity--;
                            wait_key();
                            type_text(food_storage[lookup_f[i_input1]].after_use);
                            cout << "目前总饱腹:" << pla_a.satiety_value << endl;
                            cout << "目前总心情:" << pla_a.mood << endl;
                            cout << "目前总健康:" << pla_a.health << endl;
                            food_storage[lookup_f[i_input1]].bag_shelf_life.pop_back();
                            break;
                            //丢弃
                        case 3:
                            food_storage[lookup_f[i_input1]].bag_quantity--;
                            food_storage[lookup_f[i_input1]].bag_shelf_life.pop_back();
                            break;
                            cout << "已丢弃一个" << endl;
                        }
                    }
                }
            }
        }
    }
};
int main() {
    during_university game1;
    game1.Opening_scene();
    return 0;
}
