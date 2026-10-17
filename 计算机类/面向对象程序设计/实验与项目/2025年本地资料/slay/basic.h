#ifndef CORE_CLASSES_H
#define CORE_CLASSES_H

#include <vector>
#include <string>
#include <memory>
#include <random>
#include <iostream>

class Card;
class Creature;
class Player;
class Monster;
class StatusEffect;

enum class CardRarity { COMMON, UNCOMMON, RARE };
enum class CardType { ATTACK, SKILL, POWER };
enum class StatusType { WEAK, STRENGTH, VULNERABLE, Frail };//虚弱，力量，易伤，脆弱
enum class RoomType { COMBAT, SHOP, REST, TREASURE, EVENT };

// 状态
class StatusEffect {
private:
    StatusType type;//类型
    int intensity; // 效果强度
    int duration;  // 持续回合数
    bool isPermanent; // 是否永久效果

public:
    StatusEffect(StatusType type, int intensity, int duration, bool isPermanent = false)
        : type(type), intensity(intensity), duration(duration), isPermanent(isPermanent) {}

    // 应用
    void apply(Creature* target);
    
    // 更新状态
    void update();
    
    // 获取效果信息
    std::string getInfo() const;
    
    // 获取剩余持续时间
    int getDuration() const { return duration; }
    
    // 增加效果强度
    void increaseIntensity(int amount) { intensity += amount; }
    
    // 检查是否应该被移除
    bool shouldRemove() const { return !isPermanent && duration <= 0; }
};

// 生物基类
class Creature {
protected:
    std::string name;
    int health;
    int maxHealth;//最大生命
    int energy;
    int maxEnergy;//最大能量
    int block; //格挡值
    std::vector<std::unique_ptr<StatusEffect>> statusEffects;//状态
    bool alive;

public:
    Creature(std::string name, int maxHealth, int maxEnergy)
        : name(std::move(name)), maxHealth(maxHealth), health(maxHealth),
          maxEnergy(maxEnergy), energy(maxEnergy), block(0), alive(true) {}

    virtual ~Creature() = default;

    // 基础属性操作
    void takeDamage(int amount);
    void heal(int amount);
    void gainBlock(int amount) { block += amount; }
    void gainEnergy(int amount) { energy = energy + amount; }
    
    // 状态效果管理
    void addStatusEffect(StatusType type, int intensity, int duration, bool isPermanent = false);
    void clearStatusEffects();
    void updateStatusEffects(); // 每回合更新所有状态效果
    
    // 获取状态
    bool isAlive() const { return alive; }
    int getHealth() const { return health; }
    int getMaxHealth() const { return maxHealth; }
    int getEnergy() const { return energy; }
    int getBlock() const { return block; }
    std::string getName() const { return name; }
    
    // 重置每回合状态
    virtual void resetTurn();
    
    // 打印状态信息
    virtual void printStatus() const;
};

// 卡牌基类
class Card {
protected:
    std::string name;
    std::string description;
    int energyCost;
    CardRarity rarity;
    CardType type;
    bool isCurse; // 是否为诅咒牌

public:
    Card(std::string name, std::string description, int energyCost, 
         CardRarity rarity, CardType type, bool isCurse = false)
        : name(std::move(name)), description(std::move(description)), 
          energyCost(energyCost), rarity(rarity), type(type), isCurse(isCurse) {}

    virtual ~Card() = default;

    // 纯虚函数，使用卡牌
    virtual void use(Player* player, Creature* target) = 0;
    
    // 获取卡牌信息
    std::string getInfo() const;
    
    // 获取基础属性
    std::string getName() const { return name; }
    int getEnergyCost() const { return energyCost; }
    CardType getType() const { return type; }
    bool isCurseCard() const { return isCurse; }
};

// 攻击牌
class AttackCard : public Card {
private:
    int baseDamage;

public:
    AttackCard(std::string name, std::string description, int energyCost, 
               CardRarity rarity, int baseDamage)
        : Card(std::move(name), std::move(description), energyCost, rarity, CardType::ATTACK),
          baseDamage(baseDamage) {}

    void use(Player* player, Creature* target) override;
};

// 技能牌
class SkillCard : public Card {
private:
    StatusType effectType;
    int effectValue;
    bool targetsPlayer; // 效果是否作用于玩家自己

public:
    SkillCard(std::string name, std::string description, int energyCost, 
              CardRarity rarity, StatusType effectType, int effectValue, bool targetsPlayer = true)
        : Card(std::move(name), std::move(description), energyCost, rarity, CardType::SKILL),
          effectType(effectType), effectValue(effectValue), targetsPlayer(targetsPlayer) {}

    void use(Player* player, Creature* target) override;
};

// 能力牌
class PowerCard : public Card {
private:
    StatusType powerType;
    int baseIntensity;
    bool isPermanent; // 是否永久生效

public:
    PowerCard(std::string name, std::string description, int energyCost, 
              CardRarity rarity, StatusType powerType, int baseIntensity, bool isPermanent = true)
        : Card(std::move(name), std::move(description), energyCost, rarity, CardType::POWER),
          powerType(powerType), baseIntensity(baseIntensity), isPermanent(isPermanent) {}

    void use(Player* player, Creature* target) override;
};

// 牌组管理相关类
class Deck {
private:
    std::vector<std::unique_ptr<Card>> cards;

public:
    Deck() = default;
    
    // 添加卡牌
    void addCard(std::unique_ptr<Card> card);
    
    // 移除卡牌（返回是否成功）
    bool removeCard(const std::string& cardName);
    
    // 洗牌
    void shuffle();
    
    // 获取卡牌数量
    int getSize() const { return cards.size(); }
    
    // 抽取顶部卡牌
    //std::unique_ptr<Card> drawCard();
    
    // 查看所有卡牌
    void viewAllCards() const;
};

//抽牌堆
class DrawPile {
private:
    std::vector<std::unique_ptr<Card>> cards;

public:
    DrawPile() = default;
    
    // 添加卡牌到抽牌堆
    void addCard(std::unique_ptr<Card> card);
    
    // 从弃牌堆重置抽牌堆
    void resetFromDiscard(std::vector<std::unique_ptr<Card>>& discardPile);
    
    // 抽取顶部卡牌
    std::unique_ptr<Card> drawCard();
    
    // 获取剩余卡牌数量
    int getRemaining() const { return cards.size(); }
};

//弃牌堆
class DiscardPile {
private:
    std::vector<std::unique_ptr<Card>> discardedCards;

public:

    std::vector<std::unique_ptr<Card>> getCards() const { 
        return discardedCards; 
    }

    DiscardPile() = default;
    
    // 添加弃牌
    void addDiscarded(std::unique_ptr<Card> card);
    
    // 清空弃牌堆（返回所有卡牌）
    std::vector<std::unique_ptr<Card>> clear();
    
    // 获取弃牌数量
    int getSize() const { return discardedCards.size(); }
};

//手牌
class Hand {
private:
    std::vector<std::unique_ptr<Card>> currentCards;
    int maxSize;

public:
    Hand(int maxSize = 5) : maxSize(maxSize) {}
    
    // 从抽牌堆抽牌
    bool drawFromDrawPile(DrawPile& drawPile, DiscardPile& discardPile);
    
    // 打出卡牌
    bool playCard(int index, Player* player, Creature* target, DiscardPile& discardPile);
    
    // 丢弃所有手牌到弃牌堆
    void discardAll(DiscardPile& discardPile);
    
    // 显示当前手牌
    void showHand() const;
    
    // 获取手牌数量
    int getSize() const { return currentCards.size(); }
};

// 玩家类
class Player : public Creature {
private:
    Deck deck;
    DrawPile drawPile;
    DiscardPile discardPile;
    Hand hand;
    int gold;
    std::vector<std::string> relics; // 遗物列表
public:
    // 返回引用而非副本
    DiscardPile& getDiscardPile() { 
        return discardPile; 
    }

    Player(std::string name = "Player", int maxHealth = 100, int maxEnergy = 3)
        : Creature(std::move(name), maxHealth, maxEnergy), gold(0) {
        initializeStartingDeck();
    }
    
    // 初始化初始牌组
    void initializeStartingDeck();
    
    // 开始回合
    void startTurn();
    
    // 结束回合
    void endTurn();
    
    // 牌组操作
    void addCardToDeck(std::unique_ptr<Card> card);
    void viewDeck() const { deck.viewAllCards(); }
    
    // 遗物操作
    void addRelic(const std::string& relicName);
    void viewRelics() const;
    
    // 金币操作
    void gainGold(int amount) { gold += amount; }
    bool spendGold(int amount);
    
    // 获取手牌
    Hand& getHand() { return hand; }
    
    // 重写打印状态
    void printStatus() const override;

    //获取金币
    int getGold(){return gold;}
};

// 怪物类
class Monster : public Creature {
private:
    std::vector<int> attackPattern; // 攻击模式，记录每回合攻击强度
    int currentPatternIndex;
    int rewardGold;
    std::vector<std::unique_ptr<Card>> rewardCards;

public:
    Monster(std::string name, int maxHealth, int maxEnergy, 
            std::vector<int> attackPattern, int rewardGold)
        : Creature(std::move(name), maxHealth, maxEnergy), 
          attackPattern(std::move(attackPattern)), currentPatternIndex(0), rewardGold(rewardGold) {}
    
    // 怪物回合行动
    void takeTurn(Player* player);
    
    // 掉落奖励
    void dropLoot(Player* player);
    
    // 添加奖励卡牌
    void addRewardCard(std::unique_ptr<Card> card);
    
    // 重置战斗状态
    void resetCombat();
};

// 房间基类
class Room {
protected:
    RoomType type;
    std::string name;
    bool isExplored;

public:
    Room(RoomType type, std::string name)
        : type(type), name(std::move(name)), isExplored(false) {}

    virtual ~Room() = default;
    
    // 进入房间
    virtual void enter(Player* player) = 0;
    
    // 获取房间类型
    RoomType getType() const { return type; }
    
    // 获取房间名称
    std::string getName() const { return name; }
    
    // 检查是否已探索
    bool isRoomExplored() const { return isExplored; }
};

// 战斗房间
class CombatRoom : public Room {
private:
    std::vector<std::unique_ptr<Monster>> monsters;

public:
    CombatRoom(std::string name) : Room(RoomType::COMBAT, std::move(name)) {}
    
    // 添加怪物
    void addMonster(std::unique_ptr<Monster> monster);
    
    // 进入房间（开始战斗）
    void enter(Player* player) override;
};

// 商店房间
/*
class ShopRoom : public Room {
private:
    std::vector<std::unique_ptr<Card>> cardsForSale;
    std::vector<std::pair<std::string, int>> relicsForSale; // 遗物名称和价格
    int potionHealAmount;
    int healCost;

public:
    ShopRoom(std::string name) : Room(RoomType::SHOP, std::move(name)), 
                                 potionHealAmount(30), healCost(50) {}
    
    // 添加可购买卡牌
    void addCardForSale(std::unique_ptr<Card> card);
    
    // 添加可购买遗物
    void addRelicForSale(const std::string& relicName, int price);
    
    // 进入房间（显示商店界面）
    void enter(Player* player) override;
};
*/

// 楼层类
class Floor {
private:
    int floorNumber;
    std::vector<std::unique_ptr<Room>> rooms;
    int currentRoomIndex;

public:
    Floor(int floorNumber) : floorNumber(floorNumber), currentRoomIndex(0) {}
    
    // 添加房间
    void addRoom(std::unique_ptr<Room> room);
    
    // 进入下一个房间
    bool nextRoom(Player* player);
    
    // 获取当前楼层号
    int getFloorNumber() const { return floorNumber; }
    
    // 检查是否完成当前楼层
    bool isFloorCompleted() const;
};

// 游戏主类
class Game {
private:
    std::unique_ptr<Player> player;
    std::vector<std::unique_ptr<Floor>> floors;
    int currentFloorIndex;
    bool isRunning;

public:
    Game() : currentFloorIndex(0), isRunning(true) {
        player = std::make_unique<Player>();
    }
    
    // 初始化游戏
    void initialize(int numFloors = 3);
    
    // 运行游戏主循环
    void run();
    
    // 生成楼层
    void generateFloor(int floorNumber);
    
    // 游戏结束
    void gameOver(bool victory);
};

#endif // CORE_CLASSES_H
