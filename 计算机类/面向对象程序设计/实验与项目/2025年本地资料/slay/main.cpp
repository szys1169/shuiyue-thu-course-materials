#include "new.h"

int main() {
    // 创建游戏实例
    Game game;
    
    // 初始化游戏（设置3层楼）
    //game.initialize(3);
    
    //房间1
    std::string aa="feiyue"; 
    Monster monster(std::move(aa),14, {20}, 20,{},{});

    CombatRoom lile("lile");
    lile.addMonster(std::make_unique<Monster>(monster));

    //房间2
    std::string aa2="feiyue2"; 
    Monster monster2(std::move(aa2),14, {20}, 20,{},{});

    CombatRoom lile2("lile2");
    lile2.addMonster(std::make_unique<Monster>(monster2));

    Player Warrior;
    // 运行游戏主循环
    //game.run();
    
    bool result=lile.enter(&Warrior);
    if(result)
    {
        result=lile2.enter(&Warrior);
    }
    
    return 0;
}
