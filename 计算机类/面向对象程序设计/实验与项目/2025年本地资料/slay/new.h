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
class DrawPile;

enum class CardRarity { COMMON, UNCOMMON, RARE };
enum class CardType { ATTACK, SKILL, POWER };
enum class StatusType { WEAK, STRENGTH, VULNERABLE, Frail,BLOCK,ZERO};//虚弱，力量，易伤，脆弱，空
enum class RoomType { COMBAT, SHOP, REST, TREASURE, EVENT };//目前只有COMBAT

// 效果
class StatusEffect {
private:
    StatusType type;//类型
    float intensity; // 效果强度
    int duration;  // 持续回合数
    bool isPermanent; // 是否永久效果

public:
    StatusEffect(StatusType type, float intensity, int duration, bool isPermanent = false)
        : type(type), intensity(intensity), duration(duration), isPermanent(isPermanent) {}

    // 应用
    // void apply(Creature* target);
    
    // 更新状态
    bool update();
    
    // 获取效果信息
    std::string getInfo() const;

    // 获取类型
    StatusType getType() const { return type; }

    // 获取剩余持续时间
    int getDuration() const { return duration; }

    // 获取是否永久
    bool getIsPermanent() const { return isPermanent; }

    // 获取效果强度
    int getIntensity() const { return intensity; }

    // 设置持续回合数
    void setDuration(int newDuration) { duration = newDuration; }

    // 增加效果强度
    //void increaseIntensity(int amount) { intensity += amount; }
    
    // 检查是否应该被移除
    //bool shouldRemove() const { return !isPermanent && duration <= 0; }
};


// 生物基类
class Creature {
protected:
    std::string name;
    int health;
    int maxHealth;//最大生命
    int block; //格挡值
    bool alive;

public:
    std::vector<std::unique_ptr<StatusEffect>> statusEffects;//状态
    Creature(std::string name, int maxHealth)
        : name(std::move(name)), maxHealth(maxHealth), health(maxHealth),
           block(0), alive(true) {}

    virtual ~Creature() = default;

    // 基础属性操作
    void takeDamage(int amount);
    void heal(int amount);
    void gainBlock(int amount) { block += amount; }
    
    
    // 状态效果管理
    void addStatusEffect(StatusType type, int intensity, int duration, bool isPermanent = false);
    void clearStatusEffects(){statusEffects.clear();};
    void updateStatusEffects(); // 每回合更新所有状态效果
    
    // 获取状态
    bool isAlive() const { return alive; }
    int getHealth() const { return health; }
    int getMaxHealth() const { return maxHealth; }
    
    int getBlock() const { return block; }
    std::string getName() const { return name; }
    
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

    // 拷贝构造函数
    Card(const Card& other)
        : name(other.name), description(other.description),
          energyCost(other.energyCost), rarity(other.rarity),
          type(other.type), isCurse(other.isCurse) {}

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
    StatusType effectType;
    int effectValue;
    int baseDamage;

public:
    AttackCard(std::string name, std::string description, int energyCost, 
               CardRarity rarity, int baseDamage,StatusType effectType, int effectValue)
        : Card(std::move(name), std::move(description), energyCost, rarity, CardType::ATTACK),
          baseDamage(baseDamage),effectType(effectType), effectValue(effectValue) {}

    // 拷贝构造函数：先拷贝基类部分，再拷贝派生类成员
    AttackCard(const AttackCard& other)
        : Card(other),
        effectType(other.effectType), effectValue(other.effectValue), baseDamage(other.baseDamage) {}

    void use(Player* player, Creature* target) override;
};


// 技能牌
class SkillCard : public Card {
private:
    StatusType effectType;
    int effectValue;
    int duration;
    bool targetsPlayer; // 效果是否作用于玩家自己

public:
    SkillCard(std::string name, std::string description, int energyCost, 
              CardRarity rarity, StatusType effectType, int effectValue, bool targetsPlayer = true)
        : Card(std::move(name), std::move(description), energyCost, rarity, CardType::SKILL),
          effectType(effectType), effectValue(effectValue), targetsPlayer(targetsPlayer) {}
    
    // 拷贝构造函数
    SkillCard(const SkillCard& other)
        : Card(other),  // 拷贝基类成员
          effectType(other.effectType), effectValue(other.effectValue), targetsPlayer(other.targetsPlayer) {}
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

    // 拷贝构造函数
    PowerCard(const PowerCard& other)
        : Card(other),  // 拷贝基类成员
          powerType(other.powerType), baseIntensity(other.baseIntensity), isPermanent(other.isPermanent) {}
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

    //移动卡牌到抽牌堆
    void moveAllCards(DrawPile& target);
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

    //移动卡牌到牌堆
    void moveAllCards(Deck& target);
};


//弃牌堆
class DiscardPile {
private:
    std::vector<std::unique_ptr<Card>> discardedCards;

public:

    const std::vector<std::unique_ptr<Card>>& getCards() const { 
        return discardedCards; 
    }

    DiscardPile() = default;
    
    // 添加弃牌
    void addDiscarded(std::unique_ptr<Card> card);
    
    // 清空弃牌堆（返回所有卡牌）
    std::vector<std::unique_ptr<Card>> clear();
    
    // 获取弃牌数量
    int getSize() const { return discardedCards.size(); }

    //移动卡牌到牌堆
    void moveAllCards(Deck& target);
};


//手牌
class Hand {
private:
    std::vector<std::unique_ptr<Card>> currentCards;
    int maxSize;

public:
    Hand(int maxSize = 10) : maxSize(maxSize) {}
    
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

    //移动卡牌到牌堆
    void moveAllCards(Deck& target);
};


// 玩家类
class Player : public Creature {
private:
    Deck deck;
    DrawPile drawPile;
    DiscardPile discardPile;
    Hand hand;
    int energy;
    int maxEnergy;
    //int gold;
    //std::vector<std::string> relics; // 遗物列表
public:
    // 重置每回合状态
    virtual void resetTurn();
    
    //消耗能量
    void spendEnergy(int EnergyCost){energy=energy-EnergyCost;}

    // 返回引用而非副本
    DiscardPile& getDiscardPile() { 
        return discardPile; 
    }

    void gainEnergy(int amount) { energy = energy + amount; }

    int getEnergy() const { return energy; }

    Player(std::string name = "Player", int maxHealth = 100, int maxenergy = 3)
        : Creature(std::move(name), maxHealth),energy(maxenergy),maxEnergy(maxenergy) {
        initializeStartingDeck();
    }
    
    // 初始化初始牌组
    void initializeStartingDeck();
    
    //初始抽牌堆
    void initializeDrawPile()
    {
        deck.moveAllCards(drawPile);
    }

    //战斗房间结束刷新牌堆
    void updatadeck()
    {
        drawPile.moveAllCards(deck);
        discardPile.moveAllCards(deck);
        hand.moveAllCards(deck);
    }

    // 开始回合
    void startTurn();
    
    // 结束回合
    void endTurn();
    
    // 牌组操作
    void addCardToDeck(std::unique_ptr<Card> card);
    void viewDeck() const { deck.viewAllCards(); }
    
    // 遗物操作
    //void addRelic(const std::string& relicName);
    //void viewRelics() const;
    
    // 金币操作
    //void gainGold(int amount) { gold += amount; }
    // spendGold(int amount);
    
    // 获取手牌
    Hand& getHand() { return hand; }
    
    // 重写打印状态
    void printStatus() const override;

    //获取金币
    //int getGold(){return gold;}
};


// 怪物类
class Monster : public Creature {
private:
    std::vector<int> attackPattern; // 攻击模式，记录每回合攻击强度
    std::vector<StatusEffect> toself; //-1则对自身
    std::vector<StatusEffect> toplayer;//-2则对玩家
    int currentPatternIndex;//行动序列
    int rewardGold;
    //std::vector<std::unique_ptr<Card>> rewardCards;

public:
    Monster(std::string name, int maxHealth, 
            std::vector<int> attackPattern, int rewardGold,
            std::vector<StatusEffect> Toself,std::vector<StatusEffect> Toplayer)
        : Creature(std::move(name), maxHealth), 
          attackPattern(std::move(attackPattern)), currentPatternIndex(0), rewardGold(rewardGold), 
          toself(Toself),toplayer(Toplayer){}
    
    //怪物实现拷贝复制
    Monster(const Monster& other)
        : Creature(other.name, other.maxHealth), // 拷贝基类成员
        attackPattern(other.attackPattern),  currentPatternIndex(other.currentPatternIndex),
        rewardGold(other.rewardGold), toself(other.toself),toplayer(other.toplayer) {
            for (const auto& effect : other.statusEffects) {
                statusEffects.push_back(std::make_unique<StatusEffect>(*effect));
            }
        }
          // 怪物回合行动
    void takeTurn(Player* player);
    
    // 掉落奖励
    //void dropLoot(Player* player);
    
    // 添加奖励卡牌
    //void addRewardCard(std::unique_ptr<Card> card);
    
    // 重置战斗状态
    void resetCombat(){currentPatternIndex=0;health=maxHealth;};

    //怪物打印状态
    void printStatus() const override;
};

// 房间基类
class Room {
protected:
    RoomType type;
    std::string name;
    //bool isExplored;

public:
    Room(RoomType type, std::string name)
        : type(type), name(std::move(name)) {}

    virtual ~Room() = default;
    
    // 进入房间
    virtual bool enter(Player* player) = 0;
    
    // 获取房间类型
    RoomType getType() const { return type; }
    
    // 获取房间名称
    std::string getName() const { return name; }
    
    // 检查是否已探索
    //bool isRoomExplored() const { return isExplored; }
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
    bool enter(Player* player) override;
};


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
    
    // 判断是否进入下一个房间
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
