#pragma once
#include <QObject>
#include <vector>
#include <string>
#include <memory>
#include <iomanip>
#include <algorithm>
#include <random>
#include <iostream>
#include <sstream>
#include <QString>
#include <QStringList>
#include<QDebug>
#include<QEventLoop>
#include <random>
#include <chrono>

class Card;
class Creature;
class Player;
class Monster;
class StatusEffect;
class DrawPile;
class Game;

enum class CardRarity { INITIAL, COMMON, UNCOMMON, RARE, SPECIAL };
enum class CardType { ATTACK, SKILL, POWER, STATUS, CURSE, MONSTER};
enum class RoomType { COMBAT, SHOP, REST, TREASURE, EVENT };//目前只有COMBAT
enum class StatusType { BLOCK, ATTACK, ZERO, ENERGY, HEALTH,//格挡，攻击，空白，回能，回血（基本）
                        WEAK, VULNERABLE, FRAIL,//虚弱，易伤，脆弱(不可叠加)
                        STRENGTH, AGILE,//力量，敏捷（可叠加）
                        MAD, CURL,//生气，蜷缩（攻击结算）
                        ARTIFICIAL,//人工制品（特殊效果结算）
                        HAUNT,//缠身（影响出牌）
                        RITUAL, METAL, REMAINBLOCK,//仪式，金属化（回合初/末结算）
                        //（放牌）
                        SELFDISCARD,//复制自己到弃牌堆
                        NIANYEDISCARD,// 放黏液到弃牌堆
                        YUNXUANDISCARD,// 放晕眩到弃牌堆
                        ZHUOSHAODISCARD,// 放灼烧到弃牌堆
                        SHANGKOUDISCARD,// 放伤口到弃牌堆
                        DISCARDDRAW,//弃牌堆到抽牌堆
                        DRAWHAND//抽牌堆到手牌
                        };
//随机数生成函数

std::vector<int> generate3RandomNumbers(int num,int min, int max);

// 状态
class StatusEffect {
private:
    StatusType type;//类型
    float intensity; // 效果强度
    int duration;  // 持续回合数
    bool isPermanent; // 是否永久效果
    bool isSelf; // 是否为只对自身

public:
    StatusEffect(StatusType type, float intensity, int duration = 1, bool isPermanent = false, bool isSelf = false)
        : type(type), intensity(intensity), duration(duration), isPermanent(isPermanent), isSelf(isSelf) {}

    // 应用
    // void apply(Creature* target);

    // 更新状态
    bool update();

    // 获取效果信息
    std::string getInfo() const;

    // 获取类型
    StatusType getType() const { return type; }

    // 获取详细信息
    std::string getDetail() const;

    // 获取剩余持续时间
    int getDuration() const { return duration; }

    // 获取是否永久
    bool getIsPermanent() const { return isPermanent; }

    // 获取效果强度
    float getIntensity() const { return intensity; }

    // 获取是否为自身效果
    bool getIsSelf() const { return isSelf; }

    // 设置持续回合数
    void setDuration(int newDuration) { duration = newDuration; }

    // 设置是否永久
    void setIsPermanent(bool newIsPermanent) { isPermanent = newIsPermanent; }

    // 增加效果强度
    void increaseIntensity(int amount) { intensity += amount; }

    // 检查是否应该被移除
    //bool shouldRemove() const { return !isPermanent && duration <= 0; }
};


// 生物基类
class Creature {
protected:
    std::string name;
    int health;
    int maxHealth;//最大生命
    int energy;
    int maxEnergy;
    int block; //格挡值
    bool alive;
    QString Picture;
    Game* game;

public:
    std::vector<StatusEffect> statusEffects;//状态
    Creature(std::string name, int maxHealth,QString piCture, Game* gAme,
             std::vector<StatusEffect> statusEffects = {}, int energy = 3, int maxEnergy = 3)
        : name(std::move(name)),  health(maxHealth),maxHealth(maxHealth),
          energy(energy), maxEnergy(maxEnergy), block(0), alive(true),Picture(piCture),
          game(gAme),statusEffects(statusEffects) {}

    virtual ~Creature() = default;

    // 基础属性操作
    void takeDamage(int amount);
    void heal(int amount);
    void gainBlock(int amount) { block += amount; }
    int getEnergy() const { return energy; }

    void gainEnergy(int amount) { energy += amount; }
    void gainHealth(int amount) { health += amount; }
    //消耗能量
    void spendEnergy(int EnergyCost){energy=energy-EnergyCost;}

    // 状态效果管理
    void addStatusEffect(StatusType type, float intensity, int duration, bool isPermanent = false, bool isSelf = false);
        //void addStatusEffect(StatusEffect other);
    void clearStatusEffects(){statusEffects.clear();};
    void updateStatusEffects(); // 每回合更新所有状态效果

    // 获取状态
    bool isAlive() const { return alive; }
    int getHealth() const { return health; }
    int getMaxHealth() const { return maxHealth; }

    int getBlock() const { return block; }
    std::string getName() const { return name; }

    //获取图片地址
    QString address(){return Picture;}
    // 打印状态信息
    virtual void printStatus() const;
    //返回所属游戏
    Game* getGame(){return game;}

    // 退出游戏
    void setAlive(bool alive) { this->alive = alive; }

    // 回合末效果
        void applyEndTurnEffects();

};


// 卡牌基类
class Card {
protected:
    std::string name;
    std::string description;
    int energyCost;
    CardRarity rarity;
    CardType type;
    std::vector<StatusEffect> effects;
    QString cardPicture;
    bool Unplayable = false;
        bool Consume = false;
        bool Nihility = false;
        bool Instinct = false;
public:
    Card(std::string name = "weidingyi", std::string description = "", int energyCost = 0,
         CardRarity rarity = CardRarity::COMMON, CardType type = CardType::MONSTER,
         std::vector<StatusEffect> effects = {},
         QString cardpicture="C:/123/qt/untitled/image/ATTACK.png")
        : name(std::move(name)), description(std::move(description)),
          energyCost(energyCost), rarity(rarity), type(type), effects(std::move(effects)),cardPicture(cardpicture){}

    // 拷贝构造函数
    Card(const Card& other)
        : name(other.name), description(other.description),
          energyCost(other.energyCost), rarity(other.rarity),
          type(other.type), effects(other.effects), cardPicture(other.cardPicture)
        , Unplayable(other.Unplayable),
                  Consume(other.Consume), Nihility(other.Nihility), Instinct(other.Instinct){}

    ~Card() = default;

    // 使用卡牌
    void use(Creature* self, Creature* target);

    // 获取卡牌信息
    std::string getInfo() const;

    // 获取怪物出招信息(待完成)
    std::string getInfoMonster() const;

    // 获取基础属性
    std::string getName() const { return name; }
    int getEnergyCost() const { return energyCost; }
    CardType getType() const { return type; }
    //获取图片地址
    QString address()const{return cardPicture;}


    // 获取是否不可打出
    bool isUnplayable() const { return Unplayable; }
    // 设置是否不可打出
    void setUnplayable(bool value) { Unplayable = value; }

    // 获取是否消耗
    bool isConsume() const { return Consume; }
    // 设置是否消耗
    void setConsume(bool value) { Consume = value; }

    // 获取是否虚无
    bool isNihility() const { return Nihility; }
    // 设置是否虚无
    void setNihility(bool value) { Nihility = value; }

    // 获取是否固有
    bool isInstinct() const { return Instinct; }
    // 设置是否固有
    void setInstinct(bool value) { Instinct = value; }
};

class DrawPile;

// 牌组管理相关类
class Deck {
private:
    std::vector<Card> cards;

public:
    Deck() = default;

    // 添加卡牌
    void addCard(Card card);

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

    // 移动所有卡牌到目标抽牌堆
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
        void moveAllCards(){ cards.clear(); };
};


//弃牌堆
class DiscardPile {
private:
    std::vector<std::unique_ptr<Card>> discardedCards;

public:

     std::vector<std::unique_ptr<Card>>& getCards()  {
        return discardedCards;
    }

    DiscardPile() = default;

    // 添加弃牌
    void addDiscarded(std::unique_ptr<Card> card);

    // 清空弃牌堆（返回所有卡牌）
    std::vector<std::unique_ptr<Card>> clear();

    // 获取弃牌数量
    int getSize() const { return discardedCards.size(); }

    void moveAllCards(){
            discardedCards.clear();
        };
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

    // 获取当前手牌
        std::vector<std::unique_ptr<Card>>& getCards() { return currentCards; }

        void moveAllCards(){
                currentCards.clear();
            };

    const std::vector<std::unique_ptr<Card>>& getHandCards() const {
            return currentCards;
        }
};

//消耗牌堆
class ConsumePile {
private:
    std::vector<std::unique_ptr<Card>> consumedCards;

public:

    std::vector<std::unique_ptr<Card>>& getCards() { return consumedCards; }

    ConsumePile() = default;

    // 添加消耗牌
    void addConsumed(std::unique_ptr<Card> card);

    // 清空消耗牌堆（返回所有卡牌）
    // std::vector<std::unique_ptr<Card>> clear();

    // 获取消耗牌数量
    int getSize() const { return consumedCards.size(); }

    //移动卡牌到牌堆
    void moveAllCards(){
        consumedCards.clear();
    };
};



// 玩家类
class Player : public Creature {
private:
    Deck deck;
    DrawPile drawPile;
    DiscardPile discardPile;

     ConsumePile consumePile;
    //int gold;
    //std::vector<std::string> relics; // 遗物列表
public:
    Hand hand;
    // 重置每回合状态
    virtual void resetTurn();


    // 获取手牌
       Hand& getHand() { return hand; }

       // 获取抽牌堆
       DrawPile& getDrawPile() { return drawPile; }

       // 返回引用而非副本
       DiscardPile& getDiscardPile() { return discardPile; }

       // 返回引用而非副本
       ConsumePile& getConsumePile() { return consumePile; }

    void gainEnergy(int amount) { energy = energy + amount; }

    Player(Game* game,QString piCture="C:/123/qt/untitled/image/player.png",
           std::string name = "Player", int maxHealth = 100, int maxenergy = 3)
        : Creature(std::move(name), maxHealth,piCture,game,{},maxenergy, maxenergy) {
        initializeStartingDeck();
    }

    // 初始化初始牌组
    void initializeStartingDeck();

    //初始抽牌堆
    void initializeDrawPile()
    {
        deck.moveAllCards(drawPile);
    }

    //战斗房间结束刷新抽牌堆
    void updatadeck()
    {
        drawPile.moveAllCards();
               discardPile.moveAllCards();
               hand.moveAllCards();
               consumePile.moveAllCards();
    }

    // 开始回合
    void startTurn();

    // 结束回合
    void endTurn();

    // 牌组操作
    void addCardToDeck(Card card);
    void viewDeck() const { deck.viewAllCards(); }

    // 遗物操作
    //void addRelic(const std::string& relicName);
    //void viewRelics() const;

    // 金币操作
    //void gainGold(int amount) { gold += amount; }
    // spendGold(int amount);


    // 重写打印状态
    void printStatus() const override;

    //获取金币
    //int getGold(){return gold;}
};


// 怪物类
class Monster : public Creature {
private:
    std::vector<Card> attackPattern; // 攻击模式，记录每回合攻击强度
    int currentPatternIndex;//行动序列
    //std::vector<std::unique_ptr<Card>> rewardCards;

public:
    Monster(std::string name = "Monster", int maxHealth = 100,
            std::vector<Card> attackPattern = {}, std::vector<StatusEffect> statusEffects = {},
            Game* game=nullptr,QString piCture="C:/123/qt/untitled/image/Monster1.png")
        : Creature(std::move(name), maxHealth,piCture,game,statusEffects),
          attackPattern(std::move(attackPattern)), currentPatternIndex(0) {}

    //怪物实现拷贝复制
    Monster(const Monster& other)
        : Creature(other.name, other.maxHealth,other.Picture,other.game), // 拷贝基类成员
        attackPattern(other.attackPattern),  currentPatternIndex(other.currentPatternIndex){
            for (const auto& effect : other.statusEffects) {
                statusEffects.push_back(effect);
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

    const std::vector<Card>& getAttackPattern() const { return attackPattern; }
    int getCurrentPatternIndex() const { return currentPatternIndex; }
};

// 房间基类
class Room :public QObject {
    Q_OBJECT
protected:
    RoomType type;
    std::string name;
    Game* game;
    //bool isExplored;

public:
    Room(RoomType type, std::string name,Game* GAme)
        : type(type), name(std::move(name)),game(GAme) {}

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
        Q_OBJECT
private:
    std::vector<std::unique_ptr<Monster>> monsters;
    bool isPlayerturn = false; // 新增：标记是否为玩家回合

public:
    bool isEndTurnRequested;
    CombatRoom(std::string name,Game* GAme) : Room(RoomType::COMBAT, std::move(name),GAme), isEndTurnRequested(false)  {}

    // 添加怪物
    void addMonster(std::unique_ptr<Monster> monster);

    // 进入房间（开始战斗）
    bool enter(Player* player) override;
    //获取当前怪物
    std::vector<std::unique_ptr<Monster>>& getMonsters() { return monsters; }
    bool isPlayerTurn() const { return isPlayerturn; }
};


// 楼层类
class Floor {
private:
    int floorNumber;
    std::vector<std::unique_ptr<Room>> rooms;
    int currentRoomIndex;
    Game* game;
public:
    Floor(int floorNumber,Game* gAme) : floorNumber(floorNumber), currentRoomIndex(0),game(gAme) {}

    // 添加房间
    void addRoom(std::unique_ptr<Room> room);

    // 判断是否进入下一个房间
    bool nextRoom(Player* player);

    // 获取当前楼层号
    int getFloorNumber() const { return floorNumber; }

    // 检查是否完成当前楼层
    bool isFloorCompleted() const;

    int getCurrentRoomIndex() const { return currentRoomIndex; }

    // 新增：获取房间列表（返回非const引用，允许修改）
    std::vector<std::unique_ptr<Room>>& getRooms() { return rooms; }
};

// 游戏主类
class Game : public QObject {
    Q_OBJECT
private:

    std::vector<std::unique_ptr<Floor>> floors;
    int currentFloorIndex;
    bool isRunning;
public:
    std::unique_ptr<Player> player;
    Card currentRewardCards[3]={Card("ATTACK", "deal 5 damage", 1,
                                CardRarity::COMMON, CardType::ATTACK,
                                { StatusEffect(StatusType::ATTACK, 5, 1)},"C:/123/qt/untitled/image/ATTACK.png"
                            ),
                            Card("DEFINE", "gain 5 block", 1,
                                CardRarity::COMMON, CardType::ATTACK,
                                { StatusEffect(StatusType::BLOCK, 5, 1)},"C:/123/qt/untitled/image/DEFINE.png"
                            ),
                            Card("iron", "gain 5 block, deal 5 damage", 1,
                                CardRarity::COMMON, CardType::SKILL,
                                {StatusEffect(StatusType::BLOCK, 5, 1), StatusEffect(StatusType::ATTACK, 5, 1)}
                            )}; // 存储当前奖励卡牌
    bool isEndTurnRequested = false;
    Game() : currentFloorIndex(0), isRunning(true) {
        player = std::make_unique<Player>(this);
    }

    // 初始化游戏
    void initialize(int numFloors = 1);

    // 运行游戏主循环
    void run();

    // 生成楼层
    void generateFloor(int floorNumber);

    // 游戏结束
    void gameOver(bool victory);

    //获取玩家信息
    Player* getPlayer(){return player.get();}

    //获取当前房间怪物
    std::vector<std::unique_ptr<Monster>>& getCurrentRoomMonsters();

    Room* getCurrentRoom() {
            if (currentFloorIndex < floors.size()) {
                Floor* currentFloor = floors[currentFloorIndex].get();
                return currentFloor->getRooms()[currentFloor->getCurrentRoomIndex()].get();
            }
            return nullptr;
        }
signals:
    // 新增：通知UI更新背景图片
    void updateBackground(const QString& imagePath);
    // 新增：通知UI更新人物信息
    void updateplayer(const QString& imagePath);
    // 新增：通知UI更新怪物信息
    void updatemonster(const QString& imagePath);
    // 场景更新信号
    void updateScene(const QString& sceneName);

    // 房间信息信号
    void updateRoomInfo(const QString& roomName, const QString& roomType);

    // 玩家状态信号
    void updatePlayerStatus(const QString& status);

    // 手牌更新信号
    void updateHandCards(const QStringList& cardImagePaths);

    // 怪物状态信号
    void updateMonsterStatus(const QString& status);

    // 战斗日志信号
    //void updateCombatLog(const QString& log);

    // 游戏结束信号
    void gameFinished(bool victory);
    // 新增：动作处理完成信号，用于通知事件循环继续
    void actionProcessed();
    void showNextRoomButton(); // 新增：战斗胜利后显示下一关按钮
    void showRewardCards(const QStringList& rewardCardPaths);
    //能量更新信号
    void energyChanged();
    // 新增玩家血量变化信号
        void playerHealthChanged();
        // 新增怪物血量变化信号
        void monsterHealthChanged();
        //怪物意图变化
        void updateMonsterIntent();
        void gameOverBackground(bool victory); // 游戏结束时的背景更新信号
public slots:
    void onReceivePlayerAction(const QString& action); // 处理UI传来的动作

};
