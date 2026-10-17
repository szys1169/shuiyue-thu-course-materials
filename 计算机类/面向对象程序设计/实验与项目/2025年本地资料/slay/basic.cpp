#include "basic.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <sstream>

// 状态效果类实现
void StatusEffect::apply(Creature* target) 
{
    // 应用效果的具体实现
    // 实际游戏中需要根据状态类型实现不同效果
}

void StatusEffect::update() {
    if (!isPermanent) {
        duration--;
    }
}

std::string StatusEffect::getInfo() const {
    std::stringstream ss;
    switch (type) {
        case StatusType::POISON: ss << "中毒"; break;
        case StatusType::WEAK: ss << "虚弱"; break;
        case StatusType::STRENGTH: ss << "力量"; break;
        case StatusType::VULNERABLE: ss << "易伤"; break;
        case StatusType::BLOCK: ss << "格挡"; break;
    }
    ss << " (" << intensity << "点，剩余" << duration << "回合)";
    return ss.str();
}

// 生物类实现
void Creature::takeDamage(int amount) {
    if (amount <= 0) return;
    
    // 先消耗格挡值
    if (block > 0) {
        int damageTaken = std::max(0, amount - block);
        block = std::max(0, block - amount);
        health -= damageTaken;
    } else {
        health -= amount;
    }
    
    if (health <= 0) {
        health = 0;
        alive = false;
    }
}

void Creature::heal(int amount) {
    if (amount <= 0) return;
    health = std::min(health + amount, maxHealth);
}

void Creature::addStatusEffect(StatusType type, int intensity, int duration, bool isPermanent) {
    // 检查是否已有相同类型的效果，如果有则叠加
    for (const auto& effect : statusEffects) {
        if (effect->getInfo().find(StatusEffect(type, 0, 0).getInfo()) != std::string::npos) {
            // 这里简化处理，实际应该更精确地判断类型
            effect->increaseIntensity(intensity);
            return;
        }
    }
    
    statusEffects.emplace_back(std::make_unique<StatusEffect>(type, intensity, duration, isPermanent));
}

void Creature::clearStatusEffects() {
    statusEffects.clear();
}

void Creature::updateStatusEffects() {
    // 应用所有状态效果
    for (const auto& effect : statusEffects) {
        effect->apply(this);
    }
    
    // 更新效果持续时间并移除已结束的效果
    auto it = statusEffects.begin();
    while (it != statusEffects.end()) {
        (*it)->update();
        if ((*it)->shouldRemove()) {
            it = statusEffects.erase(it);
        } else {
            ++it;
        }
    }
}

void Creature::resetTurn() {
    energy = maxEnergy;
    block = 0; // 格挡值每回合重置
}

void Creature::printStatus() const {
    std::cout << name << " - 生命值: " << health << "/" << maxHealth 
              << " 能量: " << energy << "/" << maxEnergy 
              << " 格挡: " << block << std::endl;
    
    if (!statusEffects.empty()) {
        std::cout << "状态效果: ";
        for (const auto& effect : statusEffects) {
            std::cout << effect->getInfo() << " ";
        }
        std::cout << std::endl;
    }
}

// 卡牌类实现
std::string Card::getInfo() const {
    std::stringstream ss;
    ss << name << " (" << energyCost << "能量) - " << description << " [";
    
    switch (rarity) {
        case CardRarity::COMMON: ss << "普通"; break;
        case CardRarity::UNCOMMON: ss << "稀有"; break;
        case CardRarity::RARE: ss << "史诗"; break;
    }
    
    ss << "]";
    return ss.str();
}

// 攻击牌实现
void AttackCard::use(Player* player, Creature* target) {
    if (!player || !target || !target->isAlive()) return;
    
    // 检查能量是否足够
    if (player->getEnergy() < getEnergyCost()) {
        std::cout << "能量不足，无法使用" << getName() << std::endl;
        return;
    }
    
    // 消耗能量
    // 实际实现中需要有消耗能量的方法
    // player->spendEnergy(getEnergyCost());
    
    // 计算伤害（这里简化处理，实际可能受状态影响）
    int damage = baseDamage;
    
    // 应用伤害
    target->takeDamage(damage);
    std::cout << player->getName() << "使用了" << getName() 
              << "，对" << target->getName() << "造成了" << damage << "点伤害！" << std::endl;
}

// 技能牌实现
void SkillCard::use(Player* player, Creature* target) {
    if (!player) return;
    
    // 检查能量是否足够
    if (player->getEnergy() < getEnergyCost()) {
        std::cout << "能量不足，无法使用" << getName() << std::endl;
        return;
    }
    
    // 消耗能量
    // player->spendEnergy(getEnergyCost());
    
    Creature* affectedTarget = targetsPlayer ? player : target;
    if (!affectedTarget || (!targetsPlayer && !affectedTarget->isAlive())) return;
    
    // 应用技能效果
    affectedTarget->addStatusEffect(effectType, effectValue, 1);
    std::cout << player->getName() << "使用了" << getName() 
              << "，对" << affectedTarget->getName() << "施加了" 
              << StatusEffect(effectType, effectValue, 1).getInfo() << std::endl;
}

// 能力牌实现
void PowerCard::use(Player* player, Creature* target) {
    if (!player) return;
    
    // 检查能量是否足够
    if (player->getEnergy() < getEnergyCost()) {
        std::cout << "能量不足，无法使用" << getName() << std::endl;
        return;
    }
    
    // 消耗能量
    // player->spendEnergy(getEnergyCost());
    
    // 应用能力效果（通常是对玩家自己）
    player->addStatusEffect(powerType, baseIntensity, isPermanent ? 999 : 1, isPermanent);
    std::cout << player->getName() << "使用了" << getName() 
              << "，获得了" << StatusEffect(powerType, baseIntensity, 
              isPermanent ? 999 : 1, isPermanent).getInfo() << std::endl;
}

// 牌组类实现
void Deck::addCard(std::unique_ptr<Card> card) {
    if (card) {
        cards.push_back(std::move(card));
    }
}

bool Deck::removeCard(const std::string& cardName) {
    for (auto it = cards.begin(); it != cards.end(); ++it) {
        if ((*it)->getName() == cardName) {
            cards.erase(it);
            return true;
        }
    }
    return false;
}

void Deck::shuffle() {
    static std::random_device rd;
    static std::mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
}

std::unique_ptr<Card> Deck::drawCard() {
    if (cards.empty()) {
        return nullptr;
    }
    
    auto card = std::move(cards.back());
    cards.pop_back();
    return card;
}

void Deck::viewAllCards() const {
    std::cout << "牌组包含 " << cards.size() << " 张卡牌:" << std::endl;
    for (const auto& card : cards) {
        std::cout << "- " << card->getInfo() << std::endl;
    }
}

// 抽牌堆实现
void DrawPile::addCard(std::unique_ptr<Card> card) {
    if (card) {
        cards.push_back(std::move(card));
    }
}

void DrawPile::resetFromDiscard(std::vector<std::unique_ptr<Card>>& discardPile) {
    // 将弃牌堆的所有卡牌移到抽牌堆
    while (!discardPile.empty()) {
        cards.push_back(std::move(discardPile.back()));
        discardPile.pop_back();
    }
    
    // 洗牌
    static std::random_device rd;
    static std::mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
    
    //std::cout << "抽牌堆已用尽，从弃牌堆重新补充并洗牌。" << std::endl;
}

std::unique_ptr<Card> DrawPile::drawCard() {
    if (cards.empty()) {
        return nullptr;
    }
    
    auto card = std::move(cards.back());
    cards.pop_back();
    return card;
}

// 弃牌堆实现
void DiscardPile::addDiscarded(std::unique_ptr<Card> card) {
    if (card) {
        discardedCards.push_back(std::move(card));
    }
}

std::vector<std::unique_ptr<Card>> DiscardPile::clear() {
    std::vector<std::unique_ptr<Card>> result;
    result.swap(discardedCards);
    return result;
}

// 手牌实现
bool Hand::drawFromDrawPile(DrawPile& drawPile, DiscardPile& discardPile) {
    if (currentCards.size() >= maxSize) {
        std::cout << "手牌已达上限，无法再抽牌。" << std::endl;
        return false;
    }
    
    // 尝试从抽牌堆抽牌
    auto card = drawPile.drawCard();
    
    // 如果抽牌堆为空，从弃牌堆重置
    if (!card) {
        std::vector<std::unique_ptr<Card>> discarded = discardPile.getCards(); // 获取当前弃牌
        discardPile.clear(); // 清空弃牌堆
        drawPile.resetFromDiscard(discarded); // 用弃牌重置抽牌堆
        card = drawPile.drawCard();
    }
    
    if (card) {
        currentCards.push_back(std::move(card));
        return true;
    }
    
    return false;
}

bool Hand::playCard(int index, Player* player, Creature* target, DiscardPile& discardPile) {
    if (index < 0 || index >= currentCards.size()) {
        return false;
    }
    
    // 使用卡牌
    currentCards[index]->use(player, target);
    
    // 将卡牌移到弃牌堆
    discardPile.addDiscarded(std::move(currentCards[index]));
    currentCards.erase(currentCards.begin() + index);
    
    return true;
}

void Hand::discardAll(DiscardPile& discardPile) {
    while (!currentCards.empty()) {
        discardPile.addDiscarded(std::move(currentCards.back()));
        currentCards.pop_back();
    }
}

void Hand::showHand() const {
    std::cout << "当前手牌 (" << currentCards.size() << "/" << maxSize << "):" << std::endl;
    for (size_t i = 0; i < currentCards.size(); ++i) {
        std::cout << i << ". " << currentCards[i]->getInfo() << std::endl;
    }
}

// 玩家类实现
void Player::initializeStartingDeck() {
    // 添加初始卡牌
    for (int i = 0; i < 5; ++i) {
        deck.addCard(std::make_unique<AttackCard>(
            "打击", "造成5点伤害", 1, CardRarity::COMMON, 5
        ));
    }
    
    for (int i = 0; i < 4; ++i) {
        deck.addCard(std::make_unique<SkillCard>(
            "防御", "获得5点格挡", 1, CardRarity::COMMON, 
            StatusType::BLOCK, 5, true
        ));
    }
    
    // 洗牌并填充抽牌堆
    deck.shuffle();
    for (int i = 0; i < deck.getSize(); ++i) {
        if (auto card = deck.drawCard()) {
            drawPile.addCard(std::move(card));
        }
    }
}

void Player::startTurn() {
    resetTurn();
    std::cout << "\n===== " << getName() << "的回合 =====" << std::endl;
    
    // 抽5张牌
    for (int i = 0; i < 5; ++i) {
        if (!hand.drawFromDrawPile(drawPile, discardPile)) {
            break;
        }
    }
    
    // 更新状态效果
    updateStatusEffects();
    printStatus();
    hand.showHand();
}

void Player::endTurn() {
    std::cout << "\n===== 结束回合 =====" << std::endl;
    // 将手牌移到弃牌堆
    hand.discardAll(discardPile);
}

void Player::addCardToDeck(std::unique_ptr<Card> card) {
    if (card) {
        discardPile.addDiscarded(std::move(card));
        std::cout << "获得了新卡牌: " << card->getName() << std::endl;
    }
}

void Player::addRelic(const std::string& relicName) {
    relics.push_back(relicName);
    std::cout << "获得了遗物: " << relicName << std::endl;
}

void Player::viewRelics() const {
    if (relics.empty()) {
        std::cout << "尚未获得任何遗物。" << std::endl;
        return;
    }
    
    std::cout << "拥有的遗物 (" << relics.size() << "):" << std::endl;
    for (const auto& relic : relics) {
        std::cout << "- " << relic << std::endl;
    }
}

bool Player::spendGold(int amount) {
    if (amount <= 0 || gold < amount) {
        return false;
    }
    gold -= amount;
    return true;
}

void Player::printStatus() const {
    Creature::printStatus();
    std::cout << "金币: " << gold << "  抽牌堆剩余: " << drawPile.getRemaining()
              << "  弃牌堆: " << discardPile.getSize() << std::endl;
}

// 怪物类实现
void Monster::takeTurn(Player* player) {
    if (!player || !player->isAlive()) return;
    
    std::cout << "\n===== " << getName() << "的回合 =====" << std::endl;
    
    // 更新状态效果
    updateStatusEffects();
    
    // 执行攻击模式中的当前攻击
    if (currentPatternIndex < attackPattern.size()) {
        int damage = attackPattern[currentPatternIndex];
        player->takeDamage(damage);
        std::cout << getName() << "攻击了" << player->getName() 
                  << "，造成了" << damage << "点伤害！" << std::endl;
        
        currentPatternIndex = (currentPatternIndex + 1) % attackPattern.size();
    }
    
    player->printStatus();
}

void Monster::dropLoot(Player* player) {
    if (!player) return;
    
    std::cout << getName() << "被击败了！获得了 " << rewardGold << " 金币！" << std::endl;
    player->gainGold(rewardGold);
    
    // 掉落奖励卡牌
    for (auto& card : rewardCards) {
        player->addCardToDeck(std::move(card));
    }
    rewardCards.clear();
}

void Monster::addRewardCard(std::unique_ptr<Card> card) {
    if (card) {
        rewardCards.push_back(std::move(card));
    }
}

void Monster::resetCombat() {
    health = maxHealth;
    alive = true;
    currentPatternIndex = 0;
    clearStatusEffects();
}

// 战斗房间实现
void CombatRoom::addMonster(std::unique_ptr<Monster> monster) {
    if (monster) {
        monsters.push_back(std::move(monster));
    }
}

void CombatRoom::enter(Player* player) {
    if (!player || isExplored) return;
    
    std::cout << "\n===== 进入战斗房间: " << getName() << " =====" << std::endl;
    std::cout << "遭遇了敌人: ";
    for (const auto& monster : monsters) {
        std::cout << monster->getName() << " ";
    }
    std::cout << std::endl;
    
    // 重置怪物状态
    for (auto& monster : monsters) {
        monster->resetCombat();
    }
    
    // 战斗主循环
    bool combatActive = true;
    while (combatActive) {
        // 玩家回合
        player->startTurn();
        
        // 玩家行动（简化版）
        bool turnActive = true;
        while (turnActive && player->isAlive()) {
            std::cout << "\n请选择要执行的操作:" << std::endl;
            std::cout << "1. 使用卡牌" << std::endl;
            std::cout << "2. 结束回合" << std::endl;
            
            int choice;
            std::cin >> choice;
            
            if (choice == 1) {
                std::cout << "请输入要使用的卡牌编号: ";
                int cardIndex;
                std::cin >> cardIndex;
                
                // 选择目标（简化为第一个怪物）
                Creature* target = nullptr;
                for (const auto& monster : monsters) {
                    if (monster->isAlive()) {
                        target = monster.get();
                        break;
                    }
                }
                
                if (target && player->getHand().playCard(cardIndex, player, target, player->getDiscardPile())) {
                    // 检查所有怪物是否已被击败
                    bool allDead = true;
                    for (const auto& monster : monsters) {
                        if (monster->isAlive()) {
                            allDead = false;
                            break;
                        }
                    }
                    
                    if (allDead) {
                        break; // 所有怪物都死了，结束玩家回合
                    }
                }
            } else if (choice == 2) {
                turnActive = false;
            }
        }
        
        player->endTurn();
        
        // 检查玩家是否死亡
        if (!player->isAlive()) {
            combatActive = false;
            break;
        }
        
        // 检查所有怪物是否已被击败
        bool allDead = true;
        for (const auto& monster : monsters) {
            if (monster->isAlive()) {
                allDead = false;
                break;
            }
        }
        
        if (allDead) {
            // 所有怪物被击败，发放奖励
            for (auto& monster : monsters) {
                monster->dropLoot(player);
            }
            combatActive = false;
            break;
        }
        
        // 怪物回合
        for (auto& monster : monsters) {
            if (monster->isAlive()) {
                monster->takeTurn(player);
                
                // 检查玩家是否死亡
                if (!player->isAlive()) {
                    combatActive = false;
                    break;
                }
            }
        }
    }
    
    isExplored = true;
}

// 商店房间实现
void ShopRoom::addCardForSale(std::unique_ptr<Card> card) {
    if (card) {
        cardsForSale.push_back(std::move(card));
    }
}

void ShopRoom::addRelicForSale(const std::string& relicName, int price) {
    relicsForSale.emplace_back(relicName, price);
}

/*void ShopRoom::enter(Player* player) {
    if (!player || isExplored) return;
    
    std::cout << "\n===== 进入商店: " << getName() << " =====" << std::endl;
    std::cout << "欢迎光临！您当前有 " << player->getGold() << " 金币。" << std::endl;
    
    bool shopping = true;
    while (shopping) {
        std::cout << "\n商店菜单:" << std::endl;
        std::cout << "1. 购买卡牌" << std::endl;
        std::cout << "2. 购买遗物" << std::endl;
        std::cout << "3. 治疗 (" << healCost << "金币，恢复" << potionHealAmount << "点生命)" << std::endl;
        std::cout << "4. 离开商店" << std::endl;
        std::cout << "请选择: ";
        
        int choice;
        std::cin >> choice;
        
        switch (choice) {
            case 1: {
                if (cardsForSale.empty()) {
                    std::cout << "目前没有可购买的卡牌。" << std::endl;
                    break;
                }
                
                std::cout << "可购买的卡牌:" << std::endl;
                for (size_t i = 0; i < cardsForSale.size(); ++i) {
                    // 卡牌价格简单处理：普通50，稀有75，史诗100
                    int price = 50;
                    // 实际实现中需要根据卡牌稀有度计算价格
                    std::cout << i << ". " << cardsForSale[i]->getInfo() << " - " << price << "金币" << std::endl;
                }
                
                std::cout << "请输入要购买的卡牌编号 (输入-1取消): ";
                int cardIndex;
                std::cin >> cardIndex;
                
                if (cardIndex >= 0 && cardIndex < cardsForSale.size()) {
                    int price = 50; // 简化处理
                    if (player->spendGold(price)) {
                        player->addCardToDeck(std::move(cardsForSale[cardIndex]));
                        cardsForSale.erase(cardsForSale.begin() + cardIndex);
                        std::cout << "购买成功！" << std::endl;
                    } else {
                        std::cout << "金币不足，无法购买。" << std::endl;
                    }
                }
                break;
            }
            case 2: {
                if (relicsForSale.empty()) {
                    std::cout << "目前没有可购买的遗物。" << std::endl;
                    break;
                }
                
                std::cout << "可购买的遗物:" << std::endl;
                for (size_t i = 0; i < relicsForSale.size(); ++i) {
                    std::cout << i << ". " << relicsForSale[i].first 
                              << " - " << relicsForSale[i].second << "金币" << std::endl;
                }
                
                std::cout << "请输入要购买的遗物编号 (输入-1取消): ";
                int relicIndex;
                std::cin >> relicIndex;
                
                if (relicIndex >= 0 && relicIndex < relicsForSale.size()) {
                    auto& [name, price] = relicsForSale[relicIndex];
                    if (player->spendGold(price)) {
                        player->addRelic(name);
                        relicsForSale.erase(relicsForSale.begin() + relicIndex);
                        std::cout << "购买成功！" << std::endl;
                    } else {
                        std::cout << "金币不足，无法购买。" << std::endl;
                    }
                }
                break;
            }
            case 3: {
                if (player->getHealth() >= player->getMaxHealth()) {
                    std::cout << "你的生命值已经是满的了。" << std::endl;
                    break;
                }
                
                if (player->spendGold(healCost)) {
                    player->heal(potionHealAmount);
                    std::cout << "治疗成功！当前生命值: " << player->getHealth() << "/" << player->getMaxHealth() << std::endl;
                } else {
                    std::cout << "金币不足，无法治疗。" << std::endl;
                }
                break;
            }
            case 4:
                shopping = false;
                break;
            default:
                std::cout << "无效的选择，请重试。" << std::endl;
        }
    }
    
    isExplored = true;
    std::cout << "离开商店。" << std::endl;
}
*/
// 楼层类实现
void Floor::addRoom(std::unique_ptr<Room> room) {
    if (room) {
        rooms.push_back(std::move(room));
    }
}

bool Floor::nextRoom(Player* player) {
    if (currentRoomIndex >= rooms.size()) {
        return false;
    }
    
    rooms[currentRoomIndex]->enter(player);
    currentRoomIndex++;
    return true;
}

bool Floor::isFloorCompleted() const {
    return currentRoomIndex >= rooms.size();
}

// 游戏类实现
void Game::initialize(int numFloors) {
    std::cout << "===== 欢迎来到尖塔冒险 =====" << std::endl;
    
    // 生成楼层
    for (int i = 0; i < numFloors; ++i) {
        generateFloor(i + 1);
    }
}

void Game::run() {
    while (isRunning && currentFloorIndex < floors.size()) {
        Floor* currentFloor = floors[currentFloorIndex].get();
        std::cout << "\n===== 第 " << currentFloor->getFloorNumber() << " 层 =====" << std::endl;
        
        // 遍历当前楼层的所有房间
        while (!currentFloor->isFloorCompleted()) {
            if (!currentFloor->nextRoom(player.get())) {
                break;
            }
            
            // 检查玩家是否死亡
            if (!player->isAlive()) {
                gameOver(false);
                return;
            }
        }
        
        currentFloorIndex++;
    }
    
    // 如果所有楼层都完成了，游戏胜利
    if (player->isAlive()) {
        gameOver(true);
    }
}

void Game::generateFloor(int floorNumber) {
    auto floor = std::make_unique<Floor>(floorNumber);
    
    // 为楼层添加房间（简化版）
    // 1. 添加战斗房间
    auto combatRoom = std::make_unique<CombatRoom>("怪物巢穴");
    combatRoom->addMonster(std::make_unique<Monster>(
        "史莱姆", 30 + floorNumber * 5, 1, 
        std::vector<int>{5 + floorNumber * 2}, 15 + floorNumber * 5
    ));
    
    // 给怪物添加奖励卡牌
    if (floorNumber % 2 == 0) {
        combatRoom->addMonster(std::make_unique<Monster>(
            "骷髅战士", 40 + floorNumber * 5, 1, 
            std::vector<int>{7 + floorNumber * 2}, 20 + floorNumber * 5
        ));
    }
    
    floor->addRoom(std::move(combatRoom));
    
    // 2. 每隔一层添加一个商店
    if (floorNumber % 2 == 0) {
        auto shopRoom = std::make_unique<ShopRoom>("旅行者商店");
        shopRoom->addCardForSale(std::make_unique<AttackCard>(
            "重斩", "造成10点伤害", 2, CardRarity::UNCOMMON, 10
        ));
        shopRoom->addCardForSale(std::make_unique<SkillCard>(
            "坚固防御", "获得8点格挡", 2, CardRarity::UNCOMMON, 
            StatusType::BLOCK, 8, true
        ));
        shopRoom->addRelicForSale("铜制护身符", 100);
        floor->addRoom(std::move(shopRoom));
    }
    
    // 3. 再添加一个战斗房间
    auto combatRoom2 = std::make_unique<CombatRoom>("黑暗走廊");
    combatRoom2->addMonster(std::make_unique<Monster>(
        "蝙蝠群", 25 + floorNumber * 4, 1, 
        std::vector<int>{4 + floorNumber * 2, 0}, 10 + floorNumber * 5
    ));
    floor->addRoom(std::move(combatRoom2));
    
    floors.push_back(std::move(floor));
}

void Game::gameOver(bool victory) {
    isRunning = false;
    if (victory) {
        std::cout << "\n===== 恭喜你！成功通关所有楼层！ =====" << std::endl;
    } else {
        std::cout << "\n===== 游戏结束，你的冒险失败了。 =====" << std::endl;
    }
}
