#include "game.h"
#include "cards.h"
std::vector<int> generate3RandomNumbers(int num,int min, int max)
{
   // 确保范围有效
   if (min > max) std::swap(min, max);

   // 用当前时间戳作为随机数种子
   unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
   std::mt19937 rng(seed); // 随机数引擎
   std::uniform_int_distribution<int> dist(min, max); // 范围分布

   std::vector<int> result;
   for (int i = 0; i < num; ++i) {
       result.push_back(dist(rng));
   }
   return result;
}

bool StatusEffect::update() {
    if (!isPermanent && duration > 0) {
        duration--;
    }
    if(duration==0)return true;
    return false;
}

std::string StatusEffect::getInfo() const {
    std::stringstream ss;
    switch (type) {
           case StatusType::BLOCK: ss << "Block"; break;
           case StatusType::FRAIL: ss << "Frail"; break;
           case StatusType::WEAK: ss << "Weak"; break;
           case StatusType::STRENGTH: ss << "Strength"; break;
           case StatusType::AGILE: ss << "Agile"; break;
           case StatusType::VULNERABLE: ss << "Vulnerable"; break;
           case StatusType::RITUAL: ss << "Ritual"; break;
           case StatusType::METAL: ss << "Metal"; break;
           case StatusType::MAD: ss << "Mad"; break;
           case StatusType::CURL: ss << "Curl"; break;
           case StatusType::HAUNT: ss << "Haunt"; break;
           case StatusType::ARTIFICIAL: ss << "Artificial"; break;
       }
    ss << " (" << intensity << " points";
    if(!isPermanent){
        ss << ", " << duration << " turns remaining)";
    }
    else{
        ss << ", permanent)";
    }
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


void Creature::printStatus() const {
    std::cout << name << " - Health: " << health << "/" << maxHealth
              << " Block: " << block << std::endl;

    if (!statusEffects.empty()) {
        std::cout << "Status effects: ";
        for (const auto& effect : statusEffects) {
            std::cout << effect.getInfo() << " ";
        }
        std::cout << std::endl;
    }
}

void Creature::addStatusEffect(StatusType type, float intensity, int duration, bool isPermanent, bool isSelf) {
    switch (type) {
        case StatusType::STRENGTH:
            // 处理力量状态(可叠加)
            if (isPermanent) {
                for (auto& effect : statusEffects){
                    if (effect.getType() == StatusType::STRENGTH){
                        if (effect.getIsPermanent()) {
                            effect.increaseIntensity(intensity);
                            return;
                        }
                    }
                }
            }
            statusEffects.push_back(StatusEffect(type, intensity, duration, isPermanent));
            break;
        case StatusType::AGILE:
            // 处理敏捷状态(可叠加)
            if (isPermanent) {
                for (auto& effect : statusEffects){
                    if (effect.getType() == StatusType::AGILE){
                        if (effect.getIsPermanent()) {
                            effect.increaseIntensity(intensity);
                            return;
                        }
                    }
                }
            }
            statusEffects.push_back(StatusEffect(type, intensity, duration, isPermanent));
            break;
        default:
            // 处理其他状态
            for (auto& effect : statusEffects) {
                if (effect.getType() == type) {
                    if (effect.getIsPermanent()) return;
                    if (isPermanent) {
                        effect = StatusEffect(type, intensity, duration, isPermanent);
                        return;
                    }
                    effect.setDuration(std::max(effect.getDuration(), duration));
                    return;
                }
            }
            // 添加新的状态效果
            statusEffects.push_back(StatusEffect(type, intensity, duration, isPermanent));
            break;
    }
}

void Creature::updateStatusEffects() {
    // 移除所有 update() 返回 true 的效果
    statusEffects.erase(
        // 第一步：将需要删除的元素移到容器末尾
        std::remove_if(
            statusEffects.begin(), 
            statusEffects.end(),
            //  lambda 表达式：判断是否需要删除
            [](StatusEffect& effect) {
                // 如果 effect->update() 返回 true，就标记为待删除
                return effect.update();
            }
        ),
        // 第二步：删除从标记位置到末尾的所有元素
        statusEffects.end()
    );
}

// 回合末效果生效
void Creature::applyEndTurnEffects(){
    for (auto& effect : statusEffects) {
        switch (effect.getType()) {
            case StatusType::RITUAL:
                addStatusEffect(StatusType::STRENGTH, effect.getIntensity(), 999, true, true);
                break;
            case StatusType::METAL:
                gainBlock(effect.getIntensity());
                break;
        }
    }

};// 卡牌类实现
std::string Card::getInfo() const {
    std::stringstream ss;
    ss << name << " (" << energyCost << " energy) - " << description << " [";

    switch (rarity) {
        case CardRarity::COMMON: ss << "Common"; break;
        case CardRarity::UNCOMMON: ss << "Uncommon"; break;
        case CardRarity::RARE: ss << "Rare"; break;
        case CardRarity::INITIAL: ss << "Initial"; break;
        case CardRarity::SPECIAL: ss << "Special"; break;
    }

    ss << "]";
    return ss.str();
}

// 获取怪物出招信息
std::string Card::getInfoMonster() const{
    return description;
    /*
    if(description!="") return description;
    else{
        std::stringstream ss;
        for(auto& effect : effects) {
            switch (effect.getType()) {
            case StatusType::ATTACK:
                ss << "deal " << effect.getIntensity() << " damage to ";
                if(effect.getIsSelf()) ss << "itself";
                else ss << "you";
                break;
            default:
                if(effect.getIsSelf()) ss << "gain ";
                else ss << "apply ";
                switch (effect.getType()){
                    case StatusType::BLOCK:
                    case StatusType::AGILE:
                    case StatusType::STRENGTH:
                        ss << effect.getIntensity();
                    case StatusType::WEAK:
                    case StatusType::VULNERABLE:
                    case StatusType::FRAIL:
                    case StatusType::RITUAL:
                        ss << effect.getDuration();
                }
                switch (effect.getType()){
                    case StatusType::BLOCK: ss << " Block";break;
                    case StatusType::AGILE: ss << " Agile";break;
                    case StatusType::STRENGTH: ss << " Strength";break;
                    case StatusType::WEAK: ss << " Weak";break;
                    case StatusType::VULNERABLE: ss << " Vulnerable";break;
                    case StatusType::FRAIL: ss << " Frail";break;
                    case StatusType::RITUAL:ss << " Ritual";break;
                }
                ss << effect.getDuration() << " to ";
                if(effect.getIsSelf()) ss << "itself";
                else ss << "you";
                break;
            }
            ss << ", ";
    }
    std::string result = ss.str();
    result.pop_back();
    result.pop_back();
    return result;
    }
    */
}

// 使用卡牌

// 使用卡牌
void Card::use(Creature* self, Creature* target) {
    if (!self || !target || !target->isAlive()) return;

    for(auto& effect : effects) {
        Creature* affectedTarget = effect.getIsSelf() ? self : target;
        float effectValue = effect.getIntensity();
        float record = 1;
        int Record = 1;
        switch(effect.getType()) {
            // 空白
            case StatusType::ZERO:
                std::cout << "do nothing" << std::endl;
                break;
            // 格挡
            case StatusType::BLOCK:
                for(auto& statusEffect : target->statusEffects) {
                    if(statusEffect.getType()==StatusType::FRAIL)record *= statusEffect.getIntensity();
                    if(statusEffect.getType()==StatusType::AGILE)effectValue += statusEffect.getIntensity();
                }
                effectValue *= record;
                affectedTarget->gainBlock(effectValue);
                std::cout << "apply " << effectValue << " block to " << affectedTarget->getName() << std::endl;
                break;
            // 攻击
            case StatusType::ATTACK:
                Record = effect.getDuration();// 力量效果x倍
                for(auto& statusEffect : self->statusEffects) {
                    if(statusEffect.getType()==StatusType::WEAK)record *= statusEffect.getIntensity();
                    if(statusEffect.getType()==StatusType::STRENGTH){
                        effectValue += statusEffect.getIntensity()*Record;
                    }
                }
                for(auto& statusEffect : target->statusEffects) {
                    if(statusEffect.getType()==StatusType::VULNERABLE){
                        record *= statusEffect.getIntensity();
                    }
                    if(statusEffect.getType()==StatusType::MAD){
                        target->addStatusEffect(StatusType::STRENGTH, statusEffect.getIntensity(),999,true);
                    }
                    if(statusEffect.getType()==StatusType::CURL){
                        if(statusEffect.getIsPermanent()){
                            target->gainBlock(statusEffect.getIntensity());
                            statusEffect.setIsPermanent(false);
                        }
                    }
                }
                effectValue = int(effectValue*record);
                affectedTarget->takeDamage(effectValue);
                std::cout << "deal " << effectValue << " damage to " << target->getName() << std::endl;
                break;
            // 回能
            case StatusType::ENERGY:
                affectedTarget->gainEnergy(effect.getIntensity());
                std::cout << "apply " << effect.getIntensity() << " energy to " << affectedTarget->getName() << std::endl;
                break;
            // 回血
            case StatusType::HEALTH:
                affectedTarget->gainHealth(effect.getIntensity());
                std::cout << "apply " << effect.getIntensity() << " health to " << affectedTarget->getName() << std::endl;
                break;
            // 复制自己到弃牌堆
            case StatusType::SELFDISCARD:
            {
                Player* Self = dynamic_cast<Player*>(self);
                for(int i=0;i<effect.getIntensity();i++){
                    Self->getDiscardPile().addDiscarded(std::make_unique<Card>(*this));
                    std::cout << "give a copy of " << getName() << " to the discard pile" << std::endl;
                }
                break;
            }
            // 放黏液到弃牌堆
            case StatusType::NIANYEDISCARD:
            {
                Player* Target = dynamic_cast<Player*>(affectedTarget);
                for(int i=0;i<effect.getIntensity();i++){
                    Target->getDiscardPile().addDiscarded(std::make_unique<Card>(StatusCards["NianYe"]));
                    std::cout << "give a NianYe to the discard pile" << std::endl;
                }
                break;
            }
            // 放晕眩到弃牌堆
            case StatusType::YUNXUANDISCARD:
            {
                Player* Target = dynamic_cast<Player*>(affectedTarget);
                for(int i=0;i<effect.getIntensity();i++){
                    Target->getDiscardPile().addDiscarded(std::make_unique<Card>(StatusCards["YunXuan"]));
                    std::cout << "give a YunXuan to the discard pile" << std::endl;
                }
                break;
            }
            // 放灼烧到弃牌堆
            case StatusType::ZHUOSHAODISCARD:
            {
                Player* Target = dynamic_cast<Player*>(affectedTarget);
                for(int i=0;i<effect.getIntensity();i++){
                    Target->getDiscardPile().addDiscarded(std::make_unique<Card>(StatusCards["ZhuoShao"]));
                    std::cout << "give a ZhuoShao to the discard pile" << std::endl;
                }
                break;
            }
            // 放伤口到弃牌堆
            case StatusType::SHANGKOUDISCARD:
            {
                Player* Target = dynamic_cast<Player*>(affectedTarget);
                for(int i=0;i<effect.getIntensity();i++){
                    Target->getDiscardPile().addDiscarded(std::make_unique<Card>(StatusCards["ShangKou"]));
                    std::cout << "give a ShangKou to the discard pile" << std::endl;
                }
                break;
            }
            // 弃牌堆到抽牌堆
            case StatusType::DISCARDDRAW:
            {
                Player* Self = dynamic_cast<Player*>(self);
                if(Self->getDiscardPile().getSize()==0){
                    std::cout << Self->getName() << " has no cards in the discard pile to draw" << std::endl;
                }
                else{
                std::mt19937 generator(std::chrono::system_clock::now().time_since_epoch().count());
                std::uniform_int_distribution<int> dist(0, 10000);
                for(int i=0;i<effect.getIntensity();i++){
                    int randomValue = dist(generator) % Self->getDiscardPile().getSize();
                    auto& discardCards = Self->getDiscardPile().getCards();
                    if (randomValue < discardCards.size() && discardCards[randomValue]) {
                        Self->getDrawPile().addCard(std::move(discardCards[randomValue]));
                        discardCards.erase(discardCards.begin() + randomValue);
                    }
                }
                }
                break;
            }
            // 抽牌堆到手牌
            case StatusType::DRAWHAND:
            {
                Player* Self = dynamic_cast<Player*>(self);
                for(int i=0;i<effect.getIntensity();i++){
                    Self->getHand().drawFromDrawPile(Self->getDrawPile(), Self->getDiscardPile());
                }
                break;
            }
            // 状态
            default:
                // 处理人工制品
                for(auto& status : target->statusEffects){
                    if(status.getType()==StatusType::ARTIFICIAL){
                        status.increaseIntensity(-1);
                        if(status.getIntensity()<=0) status.setIsPermanent(false);
                        return;
                    }
                }
                affectedTarget->addStatusEffect(effect.getType(), effectValue, effect.getDuration(), effect.getIsPermanent());
                std::cout << " apply " << StatusEffect(effect.getType(), effectValue, effect.getDuration(), effect.getIsPermanent()).getInfo() << " to " << affectedTarget->getName() << std::endl;
                break;
        }
    }
}

// 牌组类实现
void Deck::addCard(Card card)
{
    std::cout<<card.getName()<<std::endl;
    cards.push_back(card);
}

bool Deck::removeCard(const std::string& cardName) {
    for (auto it = cards.begin(); it != cards.end(); ++it) {
        if ((*it).getName() == cardName) {
            cards.erase(it);
            return true;
        }
    }
    return false;
}


//洗牌，存疑
void Deck::shuffle() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 g(seed);  // 用时间戳初始化随机数引擎
    std::shuffle(cards.begin(), cards.end(), g);
}

void Deck::viewAllCards() const {
    std::cout << "Deck contains " << cards.size() << " cards:" << std::endl;
    for (const auto& card : cards) {
        std::cout << "- " << card.getInfo() << std::endl;
    }
}

void Deck::moveAllCards(DrawPile& target) {
    shuffle();
    for (auto& card : cards) {

            target.addCard(std::make_unique<Card>(card));

    }
    //cards.clear();
}


// 抽牌堆实现
void DrawPile::addCard(std::unique_ptr<Card> card) {
    if (card) {
        cards.push_back(std::move(card));
    }
}

void DrawPile::resetFromDiscard(std::vector<std::unique_ptr<Card>>& discardPile) {
    cards.reserve(cards.size() + discardPile.size());
    for (auto& card : discardPile) {
        if (card) {
            cards.push_back(std::move(card));
        }
    }
    discardPile.clear(); // 清空弃牌堆
    
    // 洗牌
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 g(seed);  // 用时间戳初始化随机数引擎
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



// 消耗牌堆实现
void ConsumePile::addConsumed(std::unique_ptr<Card> card) {
    if (card) {
        consumedCards.push_back(std::move(card));
    }
}

// 手牌实现
bool Hand::drawFromDrawPile(DrawPile& drawPile, DiscardPile& discardPile) {
    if (currentCards.size() >= maxSize) {
        std::cout << "Hand is full, cannot draw more cards." << std::endl;
        return false;
    }
    
    // 尝试从抽牌堆抽牌
    auto card = drawPile.drawCard();
    
    // 如果抽牌堆为空，从弃牌堆重置
    if (!card) {
        drawPile.resetFromDiscard(const_cast<std::vector<std::unique_ptr<Card>>&>(discardPile.getCards()));
        discardPile.clear();
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
    




    // 处理缠身效果
    if(currentCards[index]->getType()==CardType::ATTACK){
        for(auto& effect : player->statusEffects) {
            if(effect.getType()==StatusType::HAUNT){
                std::cout << "you're haunted and cannot attack!" << std::endl;
                return false;
            }
        }
    }
    // 判断是否不可使用
    if(currentCards[index]->isUnplayable()){
        std::cout << currentCards[index]->getName() << " is unplayable!" << std::endl;
        return false;
    }
    else{
        // 消耗能量
        player->spendEnergy(currentCards[index]->getEnergyCost());

        // 使用卡牌
        std::cout << player->getName() << " use " << currentCards[index]->getName() << std::endl;
        currentCards[index]->use(player, target);

        // 使用卡牌
        //currentCards[index]->use(player, target);
        //currentCards[index]->use(player, target);

        // 将卡牌移到弃牌堆或消耗牌堆
        if(currentCards[index]->isConsume()){
            player->getConsumePile().addConsumed(std::move(currentCards[index]));
        }
        else {
            discardPile.addDiscarded(std::move(currentCards[index]));
        }
        currentCards.erase(currentCards.begin() + index);
    }

    QStringList cardPaths;
        for (const auto& card : currentCards) {
            cardPaths << card->address();
        }
        player->getGame()->updateHandCards(cardPaths); // 需要添加getGame方法

    return true;
}

void Hand::discardAll(DiscardPile& discardPile) {
    while (!currentCards.empty()) {
        discardPile.addDiscarded(std::move(currentCards.back()));
        currentCards.pop_back();
    }
}

void Hand::showHand() const {
    std::cout << "Current hand (" << currentCards.size() << "/" << maxSize << "):" << std::endl;
    for (size_t i = 0; i < currentCards.size(); ++i) {
        std::cout << i << ". " << currentCards[i]->getInfo() << std::endl;
    }
}


// 玩家类实现
void Player::initializeStartingDeck() {
    // Add starting cards
    //std::cout<<114514<<std::endl;
    for (int i = 0; i < 5; ++i)
    {
        deck.addCard(InitialCards["DaJi"]);
    }
    for (int i = 0; i < 4; ++i) deck.addCard(InitialCards["FangYu"]);
    deck.addCard(InitialCards["TongJi"]);
    
    // Shuffle and populate draw pile
    deck.shuffle();
}


void Player::resetTurn() {
    energy = maxEnergy;
    block = 0; // 格挡值每回合重置
}


void Player::startTurn() {
    resetTurn();
    std::cout << "\n===== " << getName() << "'s turn =====" << std::endl;
    
    // 抽5张牌
    for (int i = 0; i < 5; ++i) {
        if (!hand.drawFromDrawPile(drawPile, discardPile)) {
            break;
        }
    }
    
    // 更新状态效果
    //updateStatusEffects();
    printStatus();
    hand.showHand();

    QStringList cardPaths;
       for (const auto& card : hand.getHandCards()) { // 需要添加getHandCards方法
           cardPaths.push_back(card->address());

       }
       getGame()->updateHandCards(cardPaths);
}


void Player::endTurn() {
    std::cout << "\n=====  End turn =====" << std::endl;
        // 将手牌移到弃牌堆
        for (int index = 0; index < hand.getCards().size(); index++)
        {
            if(hand.getCards()[index]->isNihility())
            {
                getConsumePile().addConsumed(std::move(hand.getCards()[index]));
                hand.getCards().erase(hand.getCards().begin() + index);
                index--;
            }
            else if(hand.getCards()[index]->getName() == "ZhuoShao")
            {
                takeDamage(2);
                getConsumePile().addConsumed(std::move(hand.getCards()[index]));
                hand.getCards().erase(hand.getCards().begin() + index);
                index--;
            }
        }

        hand.discardAll(discardPile);

        applyEndTurnEffects();
        // 更新状态效果
        updateStatusEffects();

}

void Player::addCardToDeck(Card card) {

        std::cout << "Obtained new card: " << card.getName() << std::endl;
        deck.addCard(card);


}

void Player::printStatus() const{
    std::cout << name << " - Health: " << health << "/" << maxHealth  
              << " Block: " << block << " Energy: " << energy << "/" << maxEnergy << std::endl;

    if (!statusEffects.empty()) {
        std::cout << "Status Effects: ";
        for (const auto& effect : statusEffects) {
            std::cout << effect.getInfo() << " ";
        }
        std::cout << std::endl;
    }
}


// 怪物类实现（需重写，考虑状态）
void Monster::takeTurn(Player* player) {
    if (!player || !player->isAlive()) return;
    
    std::cout << "\n===== " << getName() << "'s turn =====" << std::endl;
    
    // 执行攻击模式中的当前攻击
    if (currentPatternIndex < attackPattern.size()) {
        attackPattern[currentPatternIndex].use(this, player);
        currentPatternIndex = (currentPatternIndex + 1) % attackPattern.size();
    }

    player->printStatus();

    // 更新状态效果
    updateStatusEffects();
}
void Monster::printStatus() const {
    std::cout << name << " - Health: " << health << "/" << maxHealth  
              << " Block: " << block << std::endl;
    
    if (!statusEffects.empty()) {
        std::cout << "Status effects: ";
        for (const auto& effect : statusEffects) {
            std::cout << effect.getInfo() << " ";
        }
        std::cout << std::endl;
    }
}


// CombatRoom implementation
void CombatRoom::addMonster(std::unique_ptr<Monster> monster) {
    if (monster) {
        monsters.push_back(std::move(monster));
    }
}


bool CombatRoom::enter(Player* player) {
    std::cout << "\n===== Entering combat room: " << getName() << " =====" << std::endl;
    std::cout << "Encountered enemies: ";
    for (const auto& monster : monsters) {
        std::cout << monster->getName() << " ";
    }
    std::cout << std::endl;
    
    // Reset monster status
    for (auto& monster : monsters) {
        monster->resetCombat();
    }
    
    player->initializeDrawPile();

    bool result;
    bool combatActive = true;
    game->isEndTurnRequested = false;
    emit game->updateplayer(player->address());
    emit game->energyChanged();
    for (auto& monster : monsters) {
        game->updatemonster(monster->address());
    }
    while (combatActive) {
        // Player's turn
        player->startTurn();
        emit game->energyChanged();
        emit game->playerHealthChanged();  // 触发玩家血量初始显示
        emit game->monsterHealthChanged(); // 触发怪物血量初始显示
        isPlayerturn = true; // 标记为玩家回合
        // Player actions (simplified)
        bool turnActive = true;
        emit game->updateMonsterIntent();
        while (turnActive && player->isAlive()) {
            //是否需要强制退出回合
            if (isEndTurnRequested) {
                    turnActive = false; // 退出玩家行动循环
                    break;
                }
            // Show hand
            Hand& hand = player->getHand();
            hand.showHand();
            std::cout<<"DiscardPile"<<player->getDiscardPile().getSize()<<std::endl;
            std::cout<<"DrawPile"<<player->getDrawPile().getRemaining()<<std::endl;
            // Show player status
            player->printStatus();
            // Show monster status
            for (auto& monster : monsters) {
                monster->printStatus();
            }
            QEventLoop loop;
                connect(game, &Game::actionProcessed, &loop, &QEventLoop::quit);


                // 等待直到收到结束回合请求
                while (!game->isEndTurnRequested) {
                    emit game->energyChanged();
                    emit game->playerHealthChanged();
                    emit game->monsterHealthChanged();
                    loop.processEvents(QEventLoop::WaitForMoreEvents);
                }

                if (isEndTurnRequested) {
                        turnActive = false; // 退出玩家行动循环
                        break;
                    }
                // 处理结束回合
                if (game->isEndTurnRequested) {
                    turnActive = false;
                    game->isEndTurnRequested = false; // 重置标志位
                }

            /*std::cout << "\nPlease choose an action:" << std::endl;
            std::cout << "1. Use card" << std::endl;
            std::cout << "2. End turn" << std::endl;
            
            int choice;
            std::cin >> choice;

            if (choice == 1) {
                std::cout << "Please enter the card index to use: ";
                int cardIndex;
                std::cin >> cardIndex;
                
                // Select target (simplified to first alive monster)
                Creature* target = nullptr;
                for (const auto& monster : monsters) {
                    if (monster->isAlive()) {
                        target = monster.get();
                        break;
                    }
                }
                
                if (target && player->getHand().playCard(cardIndex, player, target, player->getDiscardPile())) {
                    // Check if all monsters are defeated
                    bool allDead = true;
                    for (const auto& monster : monsters) {
                        if (monster->isAlive()) {
                            allDead = false;
                            break;
                        }
                    }
                    
                    if (allDead) {
                        result = true;
                        break; // All monsters dead, end player turn
                    }
                }
            } else if (choice == 2) {
                turnActive = false;
            }*/
        }
        
        isPlayerturn = false;
        player->endTurn();
        
        // Check if player is dead
        if (!player->isAlive()) {
            combatActive = false;
            result = false;
            break;
        }
        
        // Check if all monsters are defeated
        bool allDead = true;
        for (const auto& monster : monsters) {
            if (monster->isAlive()) {
                allDead = false;
                break;
            }
        }
        
        if (allDead) {
            isEndTurnRequested = true; // 触发强制结束回合
            result = true;
            combatActive = false;
            break;
        }
        
        // Monsters' turn
        for (auto& monster : monsters) {
            if (monster->isAlive()) {
                monster->takeTurn(player);
                
                // Check if player is dead
                if (!player->isAlive()) {
                    combatActive = false;
                    result = false;
                    break;
                }
            }
        }
    }
    player->updatadeck();
    isEndTurnRequested = false; // 重置标志
    if (result) {
        std::cout << "Combat victory" << std::endl;
        //后续填充奖励卡牌
        //生成三个卡牌组范围内的随机数，不包括基础攻击和防御
        std::vector<int> RewardCardindex=generate3RandomNumbers(3,0,PlayerCards.size()-1);
        //

        auto i = PlayerCards.begin();
        auto j = PlayerCards.begin();
        auto k = PlayerCards.begin();
        for(int l=0;l<RewardCardindex[0];l++)i++;
        for(int l=0;l<RewardCardindex[1];l++)j++;
        for(int l=0;l<RewardCardindex[2];l++)k++;
        std::vector<Card> RewardCard={i->second,j->second,k->second};
        for (int i = 0; i < 3; ++i) {
               game->currentRewardCards[i] = RewardCard[i];
           }
        for(auto card:RewardCard)
        {
            std::cout<<card.getInfo()<<std::endl;
        }
        QStringList rewardCardPaths;
           for (const auto& card : RewardCard) { // 需要添加getHandCards方法
               rewardCardPaths.push_back(card.address());
           }

        emit game->showRewardCards(rewardCardPaths);
           QEventLoop loop;
              connect(game, &Game::actionProcessed, &loop, &QEventLoop::quit);
              while (!game->isEndTurnRequested) {
                  loop.processEvents(QEventLoop::WaitForMoreEvents);
              }
              isEndTurnRequested = false;


        /*emit game->showNextRoomButton();
        QEventLoop loop2;
        connect(game, &Game::actionProcessed, &loop2, &QEventLoop::quit);
            while (!game->isEndTurnRequested) {
                loop2.processEvents(QEventLoop::WaitForMoreEvents);
            }
            isEndTurnRequested = false;*/
        return true;
    } else {
        std::cout << "Combat defeat" << std::endl;
        return false;
    }
}

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
    std::cout << "===== welcome to the game =====" << std::endl;
    
    // 生成楼层
    for (int i = 0; i < numFloors; ++i) {
        generateFloor(i + 1);
    }
}

//后期需重写
void Game::generateFloor(int floorNumber) {
    auto floor = std::make_unique<Floor>(floorNumber,this);


    std::vector<int> monsterclass1 =generate3RandomNumbers(4,0,Monsters.size()-1);
    std::vector<int> monsterclass2 =generate3RandomNumbers(4,0,Monsters.size()-1);
    std::vector<int> bossclass =generate3RandomNumbers(1,0,1);
    for(int i=0;i<=3;i++)
    {

        auto j = Monsters.begin();

        for(int l=0;l<monsterclass1[i];l++)j++;
        Monster monster(j->second);
        auto combatRoom = std::make_unique<CombatRoom>("Monster Nest",this);
        combatRoom->addMonster(std::make_unique<Monster>(monster));
        floor->addRoom(std::move(combatRoom));
    }
    Monster elitemonster(EliteMonsters["Gremlin Nob"]);
    auto elitecombatRoom = std::make_unique<CombatRoom>("Elite",this);
    elitecombatRoom->addMonster(std::make_unique<Monster>(elitemonster));
    floor->addRoom(std::move(elitecombatRoom));

    for(int i=0;i<=3;i++)
    {
        auto j = Monsters.begin();

        for(int l=0;l<monsterclass1[i];l++)j++;
        Monster monster(j->second);
        auto combatRoom = std::make_unique<CombatRoom>("Dark Corridor",this);
        combatRoom->addMonster(std::make_unique<Monster>(monster));
        floor->addRoom(std::move(combatRoom));
    }
    auto k = BossMonsters.begin();
    for(int l=0;l<bossclass[0];l++)k++;
    Monster bossmonster(k->second);
    auto bosscombatRoom = std::make_unique<CombatRoom>("Boss",this);
    bosscombatRoom->addMonster(std::make_unique<Monster>(bossmonster));
    floor->addRoom(std::move(bosscombatRoom));

    floors.push_back(std::move(floor));
    std::cout<<".........1"<<std::endl;
}

void Game::run() {
    // 游戏开始时发送背景更新信号
       emit updateBackground("C:/123/qt/untitled/image/游戏页面.png");

    while (isRunning && currentFloorIndex < floors.size()) {
        Floor* currentFloor = floors[currentFloorIndex].get();
        std::cout << "\n=====  " << currentFloor->getFloorNumber() << " floor =====" << std::endl;
        
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

void Game::gameOver(bool victory) {
    isRunning = false;
    if (victory)
    {
        std::cout << "\n===== Congratulations! You have successfully cleared all floors! =====" << std::endl;
        emit gameOverBackground(victory);
    }
    else
    {
        std::cout << "\n===== Game over, your adventure has failed. =====" << std::endl;
        emit gameOverBackground(victory);
    }
}

std::vector<std::unique_ptr<Monster>>& Game::getCurrentRoomMonsters() {
    // 静态空列表，用于索引无效或非战斗房间的情况
    static std::vector<std::unique_ptr<Monster>> emptyMonsters;

    // 1. 检查当前楼层索引是否有效
    if (currentFloorIndex < 0 || currentFloorIndex >= floors.size()) {
        return emptyMonsters;
    }

    // 2. 获取当前楼层
    Floor* currentFloor = floors[currentFloorIndex].get();
    if (!currentFloor) {
        return emptyMonsters;
    }

    // 3. 检查当前房间索引是否有效
    int currentRoomIdx = currentFloor->getCurrentRoomIndex();
    auto& rooms = currentFloor->getRooms(); // 获取当前楼层的房间列表
    if (currentRoomIdx < 0 || currentRoomIdx >= rooms.size()) {
        return emptyMonsters;
    }

    // 4. 获取当前房间并判断是否为战斗房间
    Room* currentRoom = rooms[currentRoomIdx].get();
    CombatRoom* combatRoom = dynamic_cast<CombatRoom*>(currentRoom);
    if (!combatRoom) {
        return emptyMonsters; // 非战斗房间返回空列表
    }

    // 5. 返回战斗房间的怪物列表
    return combatRoom->getMonsters();
}

void Game::onReceivePlayerAction(const QString& action) {
    if (action == "end_turn") {
        isEndTurnRequested = true; // 标记需要结束回合
        emit actionProcessed(); // 发射信号，通知事件循环退出等待
    }
    else if (action.startsWith("use_card_")) {
                bool ok;
                int cardIndex = action.split("_").last().toInt(&ok) - 1; // UI索引从1开始，转换为0基索引
                if (ok) {
                    auto* combatRoom = dynamic_cast<CombatRoom*>(getCurrentRoom());
                    if (combatRoom && combatRoom->isPlayerTurn()) { // 确保在玩家回合
                        Player* player = getPlayer();
                        // 获取当前要使用的卡牌
                                const auto& card = player->hand.getHandCards()[cardIndex];
                                // 检查能量是否足够（怪物卡牌无需消耗能量，这里只检查玩家卡牌）
                                if (card->getType() != CardType::MONSTER && player->getEnergy() < card->getEnergyCost()) {
                                    qDebug() << "Not enough energy to use card: " << QString::fromStdString(card->getName());
                                    emit actionProcessed(); // 仍需通知事件循环继续
                                    return;
                                }
                        // 找到第一个存活的怪物作为目标
                        Creature* target = nullptr;
                        for (auto& monster : combatRoom->getMonsters()) {
                            if (monster->isAlive()) {
                                target = monster.get();
                                break;
                            }
                        }
                        // 使用卡牌
                        if (target && player) {
                            player->getHand().playCard(cardIndex, player, target, player->getDiscardPile());
                            // 检查是否所有怪物已被击败
                            bool allDead = true;
                            for (auto& monster : combatRoom->getMonsters()) {
                                if (monster->isAlive()) {
                                    allDead = false;
                                    break;
                                }
                            }
                            if (allDead) {
                                isEndTurnRequested = true; // 怪物全死则结束回合
                            }
                            emit actionProcessed(); // 通知事件循环继续
                        }
                    }
                }
            }
    else if (action == "next_room") { // 新增：处理进入下一个房间
            // 继续游戏主循环（当前楼层的下一个房间）
            /*if (currentFloorIndex < floors.size()) {
                Floor* currentFloor = floors[currentFloorIndex].get();
                if (!currentFloor->isFloorCompleted()) {
                    currentFloor->nextRoom(player.get());
                } else {
                    currentFloorIndex++; // 进入下一层
                    if (currentFloorIndex < floors.size()) {
                        floors[currentFloorIndex]->nextRoom(player.get());
                    }
                }
            }*/
            isEndTurnRequested = true;
            emit actionProcessed(); // 通知事件循环继续
    }
    else if (action.startsWith("select_reward_card_")) {
        std::cout<<1<<std::endl;
        bool ok;
        int cardIndex = action.split("_").last().toInt(&ok);
        if (ok && cardIndex >= 0 && cardIndex < 3) {
            // 将选中的卡牌添加到玩家牌组
            if (player) {
                std::cout<<1<<std::endl;
                // 从当前奖励卡牌中获取选中的卡牌（需确保currentRewardCards已正确初始化）
                player->addCardToDeck(currentRewardCards[cardIndex]);
                std::cout << "玩家选择了奖励卡牌: " << currentRewardCards[cardIndex].getName() << std::endl;
            }
            isEndTurnRequested = true; // 标记回合结束，退出等待
            emit actionProcessed(); // 通知事件循环继续
        }
    }
}
