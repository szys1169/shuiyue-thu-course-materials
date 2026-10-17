#pragma once
#include <vector>
#include <map>
#include "game.h"

// 角色卡牌图鉴字典
extern std::map<std::string, Card> PlayerCards;
extern std::map<std::string, Card> InitialCards;
extern std::map<std::string, Card> StatusCards;

// 怪物卡牌图鉴字典
extern std::map<std::string, Card> MonsterCards;

// 怪物图鉴字典（存储所有可使用的怪物原型）
extern std::map<std::string, Monster> Monsters;
extern std::map<std::string, Monster> EliteMonsters;
extern std::map<std::string, Monster> BossMonsters;

// 构造字典函数
void dictionary();
