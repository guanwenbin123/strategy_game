#include <iostream>
#include <string>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <map>
using namespace std;

class during_university{
public:
    int turn_number;                    // 回合数
    int i_input1;
    int i_input2;
    char c_input;
    int groschen;                       //钱
    
    //玩家属性类型定义
    struct player_attribute{
        int satiety_value;              //饱腹值
        int mood;                       //心情
        int health;                     //健康
        int academic;                   //学识.
        int finance;                    //财政
        int Military;                   //军事
    } pla_a;
    
    struct npc_attribute{
        int Favorability;
    };
    
    // 物品类型枚举
    enum ItemType {
        FOOD,                            // 食物
        MEDICINE,                        // 药水
        BOOK,                            // 书籍
        ATTIRE,                          // 装束
        TOOL,                            // 工具
        VALUABLE,                        // 值钱的东西
        MISC,                            // 杂物
        MATERIAL                         // 材料
    };
    
    // 物品
    struct food_data{
        string name;                    //物品名称
        ItemType type;                  //物品类型
        string description;             //描述文字
        string after_use;               //食用感受
        int bag_quantity ;              //背包数量
        int warehouse_quantity;         //行李箱数量
        int satiety_gain;               //饱腹获得
        int mood_gain;                  //心情获得
        int health_gain;                //健康获得
        int shelf_life;                 //剩余保质期
    };
    
    struct CraftingRecipe {
        string result_name;             // 做出来的东西叫啥
        vector<string> mat_names;       // 需要哪些材料
        vector<int> mat_counts;         // 每种要几个
        int required_skill;             // 需要什么技能等级（比如街头智慧 ≥ 5）
        string skill_type;              // "streetwise" 或 "logic" 等
    };
    
    vector <food_data> food_storage;//食物
    
    
    during_university() {
        turn_number = 1;
        groschen = 100;
        food_storage.push_back({
            "黑面包",
            FOOD,
            "制作粗糙的面包,口感不佳,勉强能填饱肚子,是布拉格街头上最常见和最廉价的食物之一",
            "你掰下一块，硬得像瓦片。放进嘴里嚼了半天，麦壳的粗粝感刮着舌头，酸涩里带点坚果味",
            0,2,
            20,5,0,100
        });
        food_storage.push_back({
            "咸猪肉",
            FOOD,
            "腌制,风干过的猪肉条，表面发黄，饿的时候看起来真的很诱人，嗯而且便于储存"
            "嗯你咬下一口，又咸又腻，但是能给你一种属于穷人的满足感"
            0,2,
            15,20,10,80
        })
    }
    
    // 游戏开场剧情
    void Opening_scene() {
        cout << "1436年秋，波西米亚。" << endl;
        cout << "你十六岁，即将踏入布拉格查理大学的艺学院。" << endl;
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
        cout << "按1打开行李,这里就是你的仓库,你可以在这里存放或者拿取东西" << endl;
        while(1){
            if(_getch() == '1')break;
        }
    }
    
    //主界面
    void main_interface(){
        
    }
    //每天第1回合
    void start_day(){
        
    }
    
    //仓库函数
    void warehouse(){
        map <int,int> lookup_f;//查看物品映射
        int a = 1,i = 0;
        system("cls");
        cout << "====================行李==================" << endl;
        cout << "-------------------A.食物---------------------" << endl;
        //显示物品
        for(i = 0;i < food_storage.size();i++){
            if(food_storage[i].warehouse_quantity != 0){
                lookup_f[a] = i;
                cout << "["<< a <<"."<< food_storage[i].name << "×" << food_storage[i].warehouse_quantity <<"]";
                a++;
            }
        }
        cout << endl << "请按下你要查看的物品序号种类:";
        cin >> c_input;
        if (c_input == 'A' || c_input == 'a'){
            cout << "请选择你要查看的物品:";
            cin >> i_input1;
            if (lookup_f.count(i_input1) == 0) return;//检查输入
            system("cls");
            cout << "=========================================" << endl;
            cout << "名称:" << food_storage[lookup_f[i_input1]].name <<  endl;
            cout << "数量:" << food_storage[lookup_f[i_input1]].warehouse_quantity << endl;
            cout << food_storage[lookup_f[i_input1]].shelf_life << "回合后腐坏" << endl;
            cout << food_storage[lookup_f[i_input1]].description << endl;
            cout << "1.取到背包 2.食用 3.丢弃" << endl;
            int a;
            cin >> a;
            if (food_storage[lookup_f[i_input1]].warehouse_quantity > 0){
                switch(a){
                    //取到背包
                    case 1:food_storage[lookup_f[i_input1]].warehouse_quantity--;
                           food_storage[lookup_f[i_input1]].bag_quantity++;break;
                    //食用       
                    case 2:pla_a.satiety_value += food_storage[lookup_f[i_input1]].satiety_gain;
                           pla_a.mood_value += food_storage[lookup_f[i_input1]].mood_gain;
                           food_storage[lookup_f[i_input1]].warehouse_quantity--;break;
                           cout << food_storage[lookup_f[i_input1]].after_use << endl;
                    //丢弃       
                    case 3:food_storage[lookup_f[i_input1]].warehouse_quantity--;break;
                }
            }
        }
    }    
};
int main() {
    during_university game1;
    return 0;
}
