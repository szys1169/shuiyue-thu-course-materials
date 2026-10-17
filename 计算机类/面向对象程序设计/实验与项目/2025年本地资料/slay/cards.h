#pragma once
#include <vector>
#include "new(8).h"

// 角色卡牌图鉴数组
std::vector<Card> playerCards = {
    Card("iron", "gain 5 block, deal 5 damage", 1,
        CardRarity::COMMON, CardType::ATTACK,
        {StatusEffect(StatusType::BLOCK, 5, 1), StatusEffect(StatusType::ATTACK, 5, 1)}
    ),
    Card("raidon", "deal 6 damage, apply 1 vulnerable", 1,
        CardRarity::COMMON, CardType::ATTACK,
        {StatusEffect(StatusType::ATTACK, 6, 1), StatusEffect(StatusType::VULNERABLE, 1, 1)}
    ),
    Card("giveup", "apply -2 strength", 1,
        CardRarity::UNCOMMON, CardType::SKILL,
        {StatusEffect(StatusType::STRENGTH, -2, 999, true)}
    ),
    Card("scare", "apply 2 weak", 0,
        CardRarity::UNCOMMON, CardType::SKILL,
        {StatusEffect(StatusType::WEAK, 2, 999, true)}
    ),
    Card("burn", "gain 2 strength", 1,
        CardRarity::UNCOMMON, CardType::POWER,
        {StatusEffect(StatusType::STRENGTH, 2, 999, true)}
    ),
};

// 怪物卡牌图鉴数组
std::vector<Card> MonsterCards = {
    Card("curse", "gain 3 strength", 0,
        CardRarity::COMMON, CardType::MONSTER,
        {StatusEffect(StatusType::STRENGTH, 3, 999, true)}
    ),
    Card("black strike", "deal 6 damage", 0,
        CardRarity::COMMON, CardType::MONSTER,
        {StatusEffect(StatusType::ATTACK, 6, 1)}
    )
};
// 怪物图鉴数组（存储所有可使用的怪物原型）
std::vector<Monster> monsters = {
    // 普通
    Monster(
        "Cultist", 1, 
        {MonsterCards[0],MonsterCards[1]}
    ),
    Monster(
        "Cultist+", 2, 
        {MonsterCards[0],MonsterCards[1]}
    ),
};

// 卡牌图鉴数组
