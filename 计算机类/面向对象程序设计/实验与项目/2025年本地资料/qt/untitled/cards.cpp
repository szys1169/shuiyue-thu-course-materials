#include "cards.h"

// 角色卡牌图鉴字典
std::map<std::string, Card> PlayerCards;
std::map<std::string, Card> InitialCards;
std::map<std::string, Card> StatusCards;

// 怪物卡牌图鉴字典
std::map<std::string, Card> MonsterCards;

// 怪物图鉴字典（存储所有可使用的怪物原型）
std::map<std::string, Monster> Monsters;
std::map<std::string, Monster> EliteMonsters;
std::map<std::string, Monster> BossMonsters;

// 构造字典函数
void dictionary(){
    // 红色卡牌字典
    // 初始
    InitialCards.insert({"DaJi", Card("DaJi", "deal 9 damage", 1,
    CardRarity::INITIAL, CardType::ATTACK,
    {StatusEffect(StatusType::ATTACK, 9)}
    )});
    InitialCards.insert({"FangYu", Card("FangYu", "gain 8 block", 1,
    CardRarity::INITIAL, CardType::SKILL,
    {StatusEffect(StatusType::BLOCK, 8, 1, false, true)}
    )});
    InitialCards.insert({"TongJi", Card("TongJi", "deal 8 damage, apply 3 vulnerable", 2,
    CardRarity::INITIAL, CardType::ATTACK,
    {StatusEffect(StatusType::ATTACK, 8), StatusEffect(StatusType::VULNERABLE, 1.5, 3)}
    )});

    // 攻击普通
    PlayerCards.insert({"FenNu", Card("FenNu", "deal 6 damage, discarding a copy to discard pile", 0,
    CardRarity::COMMON, CardType::ATTACK,
    {StatusEffect(StatusType::ATTACK, 6), StatusEffect(StatusType::SELFDISCARD, 1)}
    )});
    PlayerCards.insert({"TouChui", Card("TouChui", "deal 12 damage, move 1 card from discard pile to draw pile", 1,
    CardRarity::COMMON, CardType::ATTACK,
    {StatusEffect(StatusType::ATTACK, 12), StatusEffect(StatusType::DISCARDDRAW, 1)}
    )});
    PlayerCards.insert({"ZhongRen", Card("ZhongRen", "deal 14 damage, 5 times effected by strength", 2,
    CardRarity::COMMON, CardType::ATTACK,
    {StatusEffect(StatusType::ATTACK, 14, 5)}
    )});
    PlayerCards.insert({"TieZhanBo", Card("TieZhanBo", "gain 7 block, deal 7 damage", 1,
    CardRarity::COMMON, CardType::ATTACK,
    {StatusEffect(StatusType::BLOCK, 7, 1, false, true), StatusEffect(StatusType::ATTACK, 7)}
    )});
    PlayerCards.insert({"JianBingDaJi", Card("JianBingDaJi", "deal 10 damage, draw 1 card", 1,
    CardRarity::COMMON, CardType::ATTACK,
    {StatusEffect(StatusType::ATTACK, 10), StatusEffect(StatusType::DRAWHAND, 1)}
    )});
    PlayerCards.insert({"FeiJianHuiXuanBiao", Card("FeiJianHuiXuanBiao", "deal 3 damage for 4 times", 1,
    CardRarity::COMMON, CardType::ATTACK,
    {StatusEffect(StatusType::ATTACK, 3), StatusEffect(StatusType::ATTACK, 3), StatusEffect(StatusType::ATTACK, 3), StatusEffect(StatusType::ATTACK, 3)}
    )});
    PlayerCards.insert({"ShuangChongDaJi", Card("ShuangChongDaJi", "deal 7 damage for 2 times", 1,
    CardRarity::COMMON, CardType::ATTACK,
    {StatusEffect(StatusType::ATTACK, 7), StatusEffect(StatusType::ATTACK, 7)}
    )});
    PlayerCards.insert({"KuangYeDaJi", Card("KuangYeDaJi", "deal 17 damage, give 1 ShangKou to the discard pile", 1,
    CardRarity::COMMON, CardType::ATTACK,
    {StatusEffect(StatusType::ATTACK, 17), StatusEffect(StatusType::SHANGKOUDISCARD, 1, 1, false, true)}
    )});
    PlayerCards.insert({"JinGangBi", Card("JinGangBi", "deal 14 damage, apply 3 weak", 2,
    CardRarity::COMMON, CardType::ATTACK,
    {StatusEffect(StatusType::ATTACK, 14), StatusEffect(StatusType::WEAK, 0.75, 3)}
    )});
    // 攻击罕见
    PlayerCards.insert({"YuXueShu", Card("YuXueShu", "lose 2 health, deal 20", 1,
    CardRarity::UNCOMMON, CardType::ATTACK,
    {StatusEffect(StatusType::HEALTH, -2, 0, false, true), StatusEffect(StatusType::ATTACK, 20)}
    )});
    PlayerCards.insert({"LianXuQuan", Card("LianXuQuan", "deal 2 damage for 5 times", 1,
    CardRarity::UNCOMMON, CardType::ATTACK,
    {StatusEffect(StatusType::ATTACK, 2), StatusEffect(StatusType::ATTACK, 2), StatusEffect(StatusType::ATTACK, 2), StatusEffect(StatusType::ATTACK, 2), StatusEffect(StatusType::ATTACK, 2)}
    )});
        PlayerCards["LianXuQuan"].setConsume(true);
    PlayerCards.insert({"WuMouChongFeng", Card("WuMouChongFeng", "deal 10 damage, give 1 ShangKou to the discard pile", 0,
    CardRarity::UNCOMMON, CardType::ATTACK,
    {StatusEffect(StatusType::ATTACK, 10), StatusEffect(StatusType::SHANGKOUDISCARD, 1, 1, false, true)}
    )});
    PlayerCards.insert({"ZhuoReGongJi", Card("ZhuoReGongJi", "deal 16 damage", 2,
    CardRarity::UNCOMMON, CardType::ATTACK,
    {StatusEffect(StatusType::ATTACK, 16)}
    )});
    PlayerCards.insert({"ShangGouQuan", Card("ShangGouQuan", "deal 13 damage, apply 2 weak, apply 2 vulnerable", 2,
    CardRarity::UNCOMMON, CardType::ATTACK,
    {StatusEffect(StatusType::ATTACK, 13), StatusEffect(StatusType::WEAK, 0.75, 2), StatusEffect(StatusType::VULNERABLE, 1.5, 2)}
    )});
    PlayerCards.insert({"CanSha", Card("CanSha", "deal 28 damage, nihility", 2,
    CardRarity::UNCOMMON, CardType::ATTACK,
    {StatusEffect(StatusType::ATTACK, 28)}
    )});
        PlayerCards["CanSha"].setNihility(true);

    // 攻击稀有
    PlayerCards.insert({"ZhongChui", Card("ZhongChui", "deal 42 damage", 3,
    CardRarity::RARE, CardType::ATTACK,
    {StatusEffect(StatusType::ATTACK, 42)}
    )});

    // 技能普通
    PlayerCards.insert({"HuoDongJiRou", Card("HuoDongJiRou", "gain 4 strength for 1 turn", 0,
    CardRarity::COMMON, CardType::SKILL,
    {StatusEffect(StatusType::STRENGTH, 4, 1, false, true)}
    )});
    PlayerCards.insert({"SongJianWuShi", Card("SongJianWuShi", "gain 11 block, draw 1 card", 1,
    CardRarity::COMMON, CardType::SKILL,
    {StatusEffect(StatusType::BLOCK, 11, 1, false, true), StatusEffect(StatusType::DRAWHAND, 1, false, true)}
    )});
    // 技能罕见
    PlayerCards.insert({"JiaoXie", Card("JiaoXie", "apply -3 strength, consume", 1,
    CardRarity::UNCOMMON, CardType::SKILL,
    {StatusEffect(StatusType::STRENGTH, -3, 999, true, false)}
    )});
        PlayerCards["JiaoXie"].setConsume(true);
    PlayerCards.insert({"YouLingKaiJia", Card("YouLingKaiJia", "gain 13 block, consume", 1,
    CardRarity::UNCOMMON, CardType::SKILL,
    {StatusEffect(StatusType::BLOCK, 13, 1, false, true)}
    )});
        PlayerCards["YouLingKaiJia"].setNihility(true);
        /*
    PlayerCards.insert({"YingCheng", Card("YingCheng", "gain 20 block, give 2 ShangKou to the discard pile", 1,
    CardRarity::UNCOMMON, CardType::SKILL,
    {StatusEffect(StatusType::BLOCK, 20, 1, false, true), StatusEffect(StatusType::SHANGKOUDISCARD, 2, 1, false, true)}
    )});*/
    PlayerCards.insert({"ShengNu", Card("ShengNu", "gain 2 energy, consume", 0,
    CardRarity::UNCOMMON, CardType::SKILL,
    {StatusEffect(StatusType::ENERGY, 2, 1, false, true)}
    )});
        PlayerCards["ShengNu"].setConsume(true);
    PlayerCards.insert({"FangXue", Card("FangXue", "gain 3 energy, lose 3 health", 0,
    CardRarity::UNCOMMON, CardType::SKILL,
    {StatusEffect(StatusType::ENERGY, 3, 1, false, true), StatusEffect(StatusType::HEALTH, -3, 1, false, true)}
    )});
    // 技能稀有
    PlayerCards.insert({"KuiRanBuDong", Card("KuiRanBuDong", "gain 40 block, consume", 2,
    CardRarity::UNCOMMON, CardType::SKILL,
    {StatusEffect(StatusType::BLOCK, 40, 1, false, true)}
    )});
        PlayerCards["KuiRanBuDong"].setConsume(true);

    // 能力罕见
    PlayerCards.insert({"RanShao", Card("RanShao", "gain 3 strength", 1,
    CardRarity::UNCOMMON, CardType::POWER,
    {StatusEffect(StatusType::STRENGTH, 3, 999, true, true)}
    )});
    PlayerCards.insert({"JinShuHua", Card("JinShuHua", "gain 4 block when turn ends", 1,
    CardRarity::UNCOMMON, CardType::POWER,
    {StatusEffect(StatusType::METAL, 4, 999, true, true)}
    )});
    // 能力稀有
    PlayerCards.insert({"EMoXingTai", Card("EMoXingTai", "gain 3 strength when turn ends", 1,
    CardRarity::RARE, CardType::POWER,
    {StatusEffect(StatusType::RITUAL, 3, 999, true, true)}
    )});
    PlayerCards.insert({"BILEI", Card("BILEI", "block remain when turn starts", 1,
    CardRarity::RARE, CardType::POWER,
    {StatusEffect(StatusType::REMAINBLOCK, 3, 999, true, true)}
    )});

    // 无色卡牌字典
    StatusCards.insert({"NianYe", Card("NianYe", "consume", 1,
    CardRarity::SPECIAL, CardType::STATUS,
    {StatusEffect(StatusType::ZERO, 5)}
    )});
        StatusCards["NianYe"].setConsume(true);
    StatusCards.insert({"ZhuoShao", Card("ZhuoShao", "unplayable, gain 2 damage when turn ends", 0,
    CardRarity::SPECIAL, CardType::STATUS,
    {StatusEffect(StatusType::ZERO, 2)}
    )});
        StatusCards["ZhuoShao"].setUnplayable(true);
    StatusCards.insert({"YunXuan", Card("YunXuan", "unplayable, nihility", 0,
    CardRarity::SPECIAL, CardType::STATUS,
    {StatusEffect(StatusType::ZERO, 5)}
    )});
        StatusCards["YunXuan"].setUnplayable(true);
        StatusCards["YunXuan"].setNihility(true);
    StatusCards.insert({"ShangKou", Card("ShangKou", "unplayable", 0,
    CardRarity::SPECIAL, CardType::STATUS,
    {StatusEffect(StatusType::ZERO, 2)}
    )});
        StatusCards["ShangKou"].setUnplayable(true);

    // 怪物卡牌图鉴字典
    // 特殊效果
    MonsterCards.insert({"YiShi3", Card("YiShi3", "gain 3 YiShi", 0,
        CardRarity::COMMON, CardType::MONSTER,
        {StatusEffect(StatusType::RITUAL, 3, 999, true, true)}
    )});
    MonsterCards.insert({"LiLiang3", Card("LiLiang3", "gain 3 LiLiang", 0,
        CardRarity::COMMON, CardType::MONSTER,
        {StatusEffect(StatusType::STRENGTH, 3, 999, true, true)}
    )});
    MonsterCards.insert({"XuRuo1", Card("XuRuo1", "gain 1 weak", 0,
        CardRarity::COMMON, CardType::MONSTER,
        {StatusEffect(StatusType::WEAK, 0.75, 1)}
    )});
    MonsterCards.insert({"XuRuo2", Card("XuRuo2", "gain 2 weak", 0,
        CardRarity::COMMON, CardType::MONSTER,
        {StatusEffect(StatusType::WEAK, 0.75, 2)}
    )});
    MonsterCards.insert({"CuiRuo2", Card("CuiRuo2", "apply 2 Frail", 0,
        CardRarity::COMMON, CardType::MONSTER,
        {StatusEffect(StatusType::FRAIL, 0.75, 2)}
    )});
    MonsterCards.insert({"GeDang7", Card("GeDang7", "gain 7 block", 0,
        CardRarity::COMMON, CardType::MONSTER,
        {StatusEffect(StatusType::BLOCK, 7, 1, false, true)}
    )});
    MonsterCards.insert({"XuLi", Card("XuLi", "do nothing", 0,
        CardRarity::COMMON, CardType::MONSTER,
        {StatusEffect(StatusType::ZERO, 0)}
    )});
    MonsterCards.insert({"ChanShen1", Card("ChanShen1", "ban attack cards", 0,
        CardRarity::COMMON, CardType::MONSTER,
        {StatusEffect(StatusType::HAUNT, 0, 1)}
    )});
    MonsterCards.insert({"NianYe3", Card("NianYe3", "give 3 NianYe", 0,
        CardRarity::COMMON, CardType::MONSTER,
        {StatusEffect(StatusType::NIANYEDISCARD, 3, 1)}
    )});
    MonsterCards.insert({"YunXuan2", Card("YunXuan2", "give 2 YunXuan", 0,
        CardRarity::COMMON, CardType::MONSTER,
        {StatusEffect(StatusType::YUNXUANDISCARD, 2, 1)}
    )});
    // 攻击
    MonsterCards.insert({"GongJi4", Card("GongJi4", "deal 4 damage", 0,
        CardRarity::COMMON, CardType::MONSTER,
        {StatusEffect(StatusType::ATTACK, 4)}
    )});
    MonsterCards.insert({"GongJi6", Card("GongJi6", "deal 6 damage", 0,
        CardRarity::COMMON, CardType::MONSTER,
        {StatusEffect(StatusType::ATTACK, 6)}
    )});
    MonsterCards.insert({"GongJi9", Card("GongJi9", "deal 9 damage", 0,
        CardRarity::COMMON, CardType::MONSTER,
        {StatusEffect(StatusType::ATTACK, 9)}
    )});
    MonsterCards.insert({"GongJi12", Card("GongJi12", "deal 12 damage", 0,
        CardRarity::COMMON, CardType::MONSTER,
        {StatusEffect(StatusType::ATTACK, 12)}
    )});
    MonsterCards.insert({"GongJi16", Card("GongJi16", "deal 16 damage", 0,
        CardRarity::COMMON, CardType::MONSTER,
        {StatusEffect(StatusType::ATTACK, 16)}
    )});
    MonsterCards.insert({"GongJi25", Card("GongJi25", "deal 25 damage", 0,
        CardRarity::COMMON, CardType::MONSTER,
        {StatusEffect(StatusType::ATTACK, 25)}
    )});
    MonsterCards.insert({"GongJi35", Card("GongJi35", "deal 35 damage", 0,
        CardRarity::COMMON, CardType::MONSTER,
        {StatusEffect(StatusType::ATTACK, 35)}
    )});
    MonsterCards.insert({"GongJi5*2", Card("GongJi5*2", "deal 5 damage for 2 times", 0,
        CardRarity::COMMON, CardType::MONSTER,
        {StatusEffect(StatusType::ATTACK, 5), StatusEffect(StatusType::ATTACK, 5)}
    )});
    // 攻击+xx
    MonsterCards.insert({"GongJi4+Xuruo1", Card("GongJi4+Xuruo1", "deal 4 damage, apply 1 weak", 0,
        CardRarity::COMMON, CardType::MONSTER,
        {StatusEffect(StatusType::ATTACK, 4, 1), StatusEffect(StatusType::WEAK, 0.75, 1)}
    )});
    MonsterCards.insert({"GongJi8+Xuruo1", Card("GongJi8+Xuruo1", "deal 8 damage, apply 1 weak", 0,
        CardRarity::COMMON, CardType::MONSTER,
        {StatusEffect(StatusType::ATTACK, 8, 1), StatusEffect(StatusType::WEAK, 0.75, 1)}
    )});
    MonsterCards.insert({"GongJi6+ZhuoShao1", Card("GongJi6+ZhuoShao1", "deal 6 damage, give 1 ZhuoShao", 0,
        CardRarity::COMMON, CardType::MONSTER,
        {StatusEffect(StatusType::ATTACK, 6, 1), StatusEffect(StatusType::ZHUOSHAODISCARD, 1)}
    )});
    MonsterCards.insert({"GongJi8+YiShang1", Card("GongJi8+YiShang1", "deal 8 damage, apply 1 weak", 0,
        CardRarity::COMMON, CardType::MONSTER,
        {StatusEffect(StatusType::ATTACK, 8, 1), StatusEffect(StatusType::VULNERABLE, 1.5, 1)}
    )});
    MonsterCards.insert({"GongJi8+YiShang2", Card("GongJi8+YiShang2", "deal 8 damage, apply 2 weak", 0,
        CardRarity::COMMON, CardType::MONSTER,
        {StatusEffect(StatusType::ATTACK, 8, 1), StatusEffect(StatusType::VULNERABLE, 1.5, 2)}
    )});
    MonsterCards.insert({"GongJi8+GeDang5", Card("GongJi8+GeDang5", "deal 8 damage, gain 5 block", 0,
        CardRarity::COMMON, CardType::MONSTER,
        {StatusEffect(StatusType::BLOCK, 5, 1, true, true), StatusEffect(StatusType::ATTACK, 8, 1)}
    )});
    MonsterCards.insert({"GongJi11+NianYe2", Card("GongJi11+NianYe2", "deal 16 damage, give 2 NianYe", 0,
        CardRarity::COMMON, CardType::MONSTER,
        {StatusEffect(StatusType::ATTACK, 11, 1), StatusEffect(StatusType::NIANYEDISCARD, 2)}
    )});
    MonsterCards.insert({"GongJi16+NianYe2", Card("GongJi16+NianYe2", "deal 16 damage, give 2 NianYe", 0,
        CardRarity::COMMON, CardType::MONSTER,
        {StatusEffect(StatusType::ATTACK, 16, 1), StatusEffect(StatusType::NIANYEDISCARD, 2)}
    )});
    MonsterCards.insert({"GongJi6*2+ZhuoShao3", Card("GongJi6*2+ZhuoShao3", "deal 6 damage for 2 times, give 3 ZhuoShao", 0,
        CardRarity::COMMON, CardType::MONSTER,
        {StatusEffect(StatusType::ATTACK, 6, 1), StatusEffect(StatusType::ATTACK, 6, 1), StatusEffect(StatusType::ZHUOSHAODISCARD, 3)}
    )});
    // XX+XX
    MonsterCards.insert({"LiLiang3+GeDang6", Card("LiLiang3+GeDang6", "gain 3 strength, gain 6 block", 0,
        CardRarity::COMMON, CardType::MONSTER,
        {StatusEffect(StatusType::STRENGTH, 3, 1, true, true), StatusEffect(StatusType::BLOCK, 6, 1, true, true)}
    )});
    MonsterCards.insert({"LiLiang2+GeDang12", Card("LiLiang2+GeDang12", "gain 2 strength, gain 12 block", 0,
        CardRarity::COMMON, CardType::MONSTER,
        {StatusEffect(StatusType::STRENGTH, 2, 1, true, true), StatusEffect(StatusType::BLOCK, 12, 1, true, true)}
    )});



    // 怪物图鉴字典（存储所有可使用的怪物原型）
    // 测试
    /*
    Monsters.insert({"Test",
        Monster("Test", 1,
        {MonsterCards["YiShi3"] ,MonsterCards["GongJi6"],MonsterCards["GongJi6"],MonsterCards["GongJi6"],
         MonsterCards["GongJi6"],MonsterCards["GongJi6"],MonsterCards["GongJi6"],MonsterCards["GongJi6"]}
    )});*/
    // 邪教徒
    Monsters.insert({"Cultist",
        Monster("Cultist", 48,
        {MonsterCards["YiShi3"] ,MonsterCards["GongJi6"],MonsterCards["GongJi6"],MonsterCards["GongJi6"],
         MonsterCards["GongJi6"],MonsterCards["GongJi6"],MonsterCards["GongJi6"],MonsterCards["GongJi6"]}
    )});
    // 史莱姆
    Monsters.insert({"Spike Slime",
        Monster("Spike Slime", 64,
        {MonsterCards["GongJi16+NianYe2"], MonsterCards["CuiRuo2"]}
    )});
    Monsters.insert({"AcidSlime",
        Monster("AcidSlime", 65,
        {MonsterCards["GongJi11+NianYe2"], MonsterCards["GongJi16"], MonsterCards["XuRuo2"]}
    )});
    // 小地精
    Monsters.insert({"Fat Gremlin",
        Monster("Fat Gremlin", 13,
        {MonsterCards["GongJi4+Xuruo1"]}
    )});
    Monsters.insert({"Mad Gremlin",
        Monster("Mad Gremlin", 20,
        {MonsterCards["GongJi4"]},
        {StatusEffect(StatusType::MAD, 1, 999, true, true)}
    )});
    Monsters.insert({"Shield Gremlin",
        Monster("Shield Gremlin", 12,
        {MonsterCards["GeDang7"], MonsterCards["GongJi6"]}
    )});
    Monsters.insert({"Sneaky Gremlin",
        Monster("Sneaky Gremlin",  10,
        {MonsterCards["GongJi9"]}
    )});
    Monsters.insert({"Gremlin Wizard",
        Monster("Gremlin Wizard", 21,
        {MonsterCards["XuLi"], MonsterCards["GongJi25"]}
    )});
    // 虱虫
    Monsters.insert({"Red Louse",
        Monster("Red Louse", 10,
        {MonsterCards["LiLiang3"], MonsterCards["GongJi6"]},
        {StatusEffect(StatusType::CURL, 5, 0, true, true)}
    )});
    Monsters.insert({"Green Louse",
        Monster("Green Louse", 11,
        {MonsterCards["XuRuo2"], MonsterCards["GongJi6"]},
        {StatusEffect(StatusType::CURL, 5, 0, true, true)}
    )});
    // 奴隶主
    Monsters.insert({"Red Slaver",
        Monster("Red Slaver", 46,
        {MonsterCards["GongJi12"], MonsterCards["GongJi8+YiShang1"], MonsterCards["ChanShen1"]}
    )});
    Monsters.insert({"Blue Slaver",
        Monster("Blue Slaver", 46,
        {MonsterCards["GongJi12"], MonsterCards["GongJi8+XuRuo1"]}
    )});
    // 大颚虫
    Monsters.insert({"Jaw Worm",
        Monster("Jaw Worm", 40,
        {MonsterCards["GongJi12"], MonsterCards["LiLiang3+GeDang6"], MonsterCards["GongJi8+GeDang5"]}
    )});
    // 真菌兽
    Monsters.insert({"Fungi Beast",
        Monster("Fungi Beast", 45,
        {MonsterCards["GongJi6"], MonsterCards["LiLiang3"]}
    )});
        // 哨卫
    Monsters.insert({"Sentry",
        Monster("Sentry", 38,
        {MonsterCards["GongJi9"], MonsterCards["YunXuan2"]},
        {StatusEffect(StatusType::ARTIFICIAL, 1, 0, true, true)}
    )});

    // 地精大块头
    EliteMonsters.insert({"Gremlin Nob",
        Monster("Gremlin Nob", 82,
        {MonsterCards["YiShi3"], MonsterCards["GongJi8+YiShang2"], MonsterCards["GongJi12"],
         MonsterCards["GongJi8+YiShang2"], MonsterCards["GongJi12"], MonsterCards["GongJi8+YiShang2"], MonsterCards["GongJi12"],
         MonsterCards["GongJi8+YiShang2"], MonsterCards["GongJi12"], MonsterCards["GongJi8+YiShang2"], MonsterCards["GongJi12"],
         MonsterCards["GongJi8+YiShang2"], MonsterCards["GongJi12"], MonsterCards["GongJi8+YiShang2"], MonsterCards["GongJi12"] }
    )});
    // 史莱姆老大
    BossMonsters.insert({"Slime Boss",
        Monster("Slime Boss", 140,
        {MonsterCards["NianYe3"], MonsterCards["GongJi35"], MonsterCards["XuLi"]}
    )});
    // 六火亡魂
    BossMonsters.insert({"Hexaghost",
        Monster("Hexaghost", 250,
        {MonsterCards["XuLi"], MonsterCards["GongJi6+ZhuoShao1"], MonsterCards["GongJi5*2"], MonsterCards["GongJi6+ZhuoShao1"],
         MonsterCards["LiLiang2+GeDang12"], MonsterCards["GongJi5*2"], MonsterCards["GongJi6+ZhuoShao1"], MonsterCards["GongJi6*2+ZhuoShao3"]}
    )});
}


