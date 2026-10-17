#include "new(8).h"


int main() {
    // 创建游戏实例
    Game game;
    
    // 初始化游戏（设置3层楼）
    game.initialize(3);
    
    Player Warrior;
    
    // 运行游戏主循环
    game.run();

    return 0;
}
