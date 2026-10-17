#include "new.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <sstream>

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
        case StatusType::Frail: ss << "Frail"; break;
        case StatusType::WEAK: ss << "Weak"; break;
        case StatusType::STRENGTH: ss << "Strength"; break;
        case StatusType::VULNERABLE: ss << "Vulnerable"; break;
        case StatusType::BLOCK: ss << "Block"; break;
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


// Creature class implementation
void Creature::takeDamage(int amount) {
    if (amount <= 0) return;
    
    // Consume block first
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
            std::cout << effect->getInfo() << " ";
        }
        std::cout << std::endl;
    }
}

void Creature::addStatusEffect(StatusType type, int intensity, int duration, bool isPermanent) {
    for (auto& effect : statusEffects) {
        if (effect->getType() == type) {
            if (effect->getIsPermanent()) return;
            if (isPermanent) {
                effect = std::make_unique<StatusEffect>(type, intensity, duration, isPermanent);
                return;
            }
            effect->setDuration(std::max(effect->getDuration(), duration));
            return;
        }
    }
    // Add new status effect
    statusEffects.push_back(std::make_unique<StatusEffect>(type, intensity, duration, isPermanent));
}

void Creature::updateStatusEffects() {
    // Remove all effects where update() returns true
    statusEffects.erase(
        std::remove_if(
            statusEffects.begin(), 
            statusEffects.end(),
            [](const std::unique_ptr<StatusEffect>& effect) {
                return effect->update();
            }
        ),
        statusEffects.end()
    );
}


// Card class implementation
std::string Card::getInfo() const {
    std::stringstream ss;
    ss << name << " (" << energyCost << " energy) - " << description << " [";
    
    switch (rarity) {
        case CardRarity::COMMON: ss << "Common"; break;
        case CardRarity::UNCOMMON: ss << "Uncommon"; break;
        case CardRarity::RARE: ss << "Rare"; break;
    }
    
    ss << "]";
    return ss.str();
}


// AttackCard implementation
void AttackCard::use(Player* player, Creature* target) {
    if (!player || !target || !target->isAlive()) return;
    
    // Check if enough energy
    if (player->getEnergy() < getEnergyCost()) {
        std::cout << "Not enough energy to use " << getName() << std::endl;
        return;
    }
    
    // Consume energy
    player->spendEnergy(getEnergyCost());
    
    // Calculate damage
    int damage = baseDamage;
    for(auto& effect : player->statusEffects) {
        switch (effect->getType()) {
            case StatusType::WEAK:
                damage *= effect->getIntensity();
                break;
            case StatusType::STRENGTH:
                damage += effect->getIntensity();
                break;
        }
    }
    for(auto& effect : target->statusEffects) {
        switch (effect->getType()) {
            case StatusType::VULNERABLE:
                damage *= effect->getIntensity();
                break;
        }
    }

    // Apply damage
    target->takeDamage(damage);
    std::cout << player->getName() << " used " << getName() 
              << ", dealing " << damage << " damage to " << target->getName() << "!" << std::endl;
}

// SkillCard implementation
void SkillCard::use(Player* player, Creature* target) {
    if (!player) return;
    
    // Check if enough energy
    if (player->getEnergy() < getEnergyCost()) {
        std::cout << "Not enough energy to use " << getName() << std::endl;
        return;
    }
    
    // Consume energy
    player->spendEnergy(getEnergyCost());
    
    Creature* affectedTarget = targetsPlayer ? player : target;
    if (!affectedTarget || (!targetsPlayer && !affectedTarget->isAlive())) return;
    
    // Apply skill effect
    if(effectType==StatusType::BLOCK) {
        for(auto& effect : target->statusEffects){
            if(effect->getType()==StatusType::Frail) {
                effectValue = int(2.0/3.0 * effectValue);
                break;
            }
        }
        affectedTarget->gainBlock(effectValue);
    }
    else affectedTarget->addStatusEffect(effectType, effectValue, duration);
    std::cout << player->getName() << " used " << getName() 
              << ", applying " 
              << StatusEffect(effectType, effectValue, duration).getInfo() << " to " << affectedTarget->getName() << std::endl;
}

// PowerCard implementation
void PowerCard::use(Player* player, Creature* target) {
    if (!player) return;
    
    // Check if enough energy
    if (player->getEnergy() < getEnergyCost()) {
        std::cout << "Not enough energy to use " << getName() << std::endl;
        return;
    }
    
    // Consume energy
    player->spendEnergy(getEnergyCost());
    
    // Apply power effect (usually to self)
    player->addStatusEffect(powerType, baseIntensity, isPermanent ? 999 : 1, isPermanent);
    std::cout << player->getName() << " used " << getName() 
              << ", gaining " << StatusEffect(powerType, baseIntensity, 
              isPermanent ? 999 : 1, isPermanent).getInfo() << std::endl;
}


// Deck class implementation
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

void Deck::viewAllCards() const {
    std::cout << "Deck contains " << cards.size() << " cards:" << std::endl;
    for (const auto& card : cards) {
        std::cout << "- " << card->getInfo() << std::endl;
    }
}

void Deck::moveAllCards(DrawPile& target) {
        for (auto& card : cards) {
            if (card) {
                target.addCard(std::move(card));
            }
        }
        cards.clear();
    }

// DrawPile implementation
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
    discardPile.clear();
    
    // Shuffle
    static std::random_device rd;
    static std::mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
}

std::unique_ptr<Card> DrawPile::drawCard() {
    if (cards.empty()) {
        return nullptr;
    }
    
    auto card = std::move(cards.back());
    cards.pop_back();
    return card;
}

void DrawPile::moveAllCards(Deck& target) {
        for (auto& card : cards) {
            if (card) {
                target.addCard(std::move(card));
            }
        }
        cards.clear();
    }

// DiscardPile implementation
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

void DiscardPile::moveAllCards(Deck& target) {
        for (auto& card : discardedCards) {
            if (card) {
                target.addCard(std::move(card));
            }
        }
        discardedCards.clear();
    }

// Hand implementation
bool Hand::drawFromDrawPile(DrawPile& drawPile, DiscardPile& discardPile) {
    if (currentCards.size() >= maxSize) {
        std::cout << "Hand is full, cannot draw more cards." << std::endl;
        return false;
    }
    
    // Try to draw from draw pile
    auto card = drawPile.drawCard();
    
    // If draw pile is empty, reset from discard pile
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
    
    // Use the card
    currentCards[index]->use(player, target);
    
    // Move card to discard pile
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
    std::cout << "Current hand (" << currentCards.size() << "/" << maxSize << "):" << std::endl;
    for (size_t i = 0; i < currentCards.size(); ++i) {
        std::cout << i << ". " << currentCards[i]->getInfo() << std::endl;
    }
}

void Hand::moveAllCards(Deck& target) {
        for (auto& card : currentCards) {
            if (card) {
                target.addCard(std::move(card));
            }
        }
        currentCards.clear();
    }

// Player class implementation
void Player::initializeStartingDeck() {
    // Add starting cards
    for (int i = 0; i < 1; ++i) {
        deck.addCard(std::make_unique<AttackCard>(
            "Strike", "Deals 5 damage", 1, CardRarity::COMMON, 5, StatusType::ZERO, 0
        ));
    }

    for (int i = 0; i < 1; ++i) {
        deck.addCard(std::make_unique<AttackCard>(
            "oooo", "Deals 5 damage", 1, CardRarity::COMMON, 5, StatusType::ZERO, 0
        ));
    }

    for (int i = 0; i < 1; ++i) {
        deck.addCard(std::make_unique<AttackCard>(
            "hhhh", "Deals 5 damage", 1, CardRarity::COMMON, 5, StatusType::ZERO, 0
        ));
    }

    for (int i = 0; i < 1; ++i) {
        deck.addCard(std::make_unique<AttackCard>(
            "6666", "Deals 5 damage", 1, CardRarity::COMMON, 5, StatusType::ZERO, 0
        ));
    }
    
    for (int i = 0; i < 1; ++i) {
        deck.addCard(std::make_unique<SkillCard>(
            "Defend", "Gains 5 block", 1, CardRarity::COMMON, 
            StatusType::BLOCK, 5, true
        ));
    }

    for (int i = 0; i < 1; ++i) {
        deck.addCard(std::make_unique<AttackCard>(
            "Strike1", "Deals 5 damage", 1, CardRarity::COMMON, 5, StatusType::ZERO, 0
        ));
    }

    for (int i = 0; i < 1; ++i) {
        deck.addCard(std::make_unique<AttackCard>(
            "oooo1", "Deals 5 damage", 1, CardRarity::COMMON, 5, StatusType::ZERO, 0
        ));
    }

    for (int i = 0; i < 1; ++i) {
        deck.addCard(std::make_unique<AttackCard>(
            "hhhh1", "Deals 5 damage", 1, CardRarity::COMMON, 5, StatusType::ZERO, 0
        ));
    }

    for (int i = 0; i < 1; ++i) {
        deck.addCard(std::make_unique<AttackCard>(
            "66661", "Deals 5 damage", 1, CardRarity::COMMON, 5, StatusType::ZERO, 0
        ));
    }
    
    for (int i = 0; i < 1; ++i) {
        deck.addCard(std::make_unique<SkillCard>(
            "Defend1", "Gains 5 block", 1, CardRarity::COMMON, 
            StatusType::BLOCK, 5, true
        ));
    }
    
    // Shuffle and populate draw pile
    deck.shuffle();
}


void Player::resetTurn() {
    energy = maxEnergy;
    block = 0; // Block resets each turn
}


void Player::startTurn() {
    resetTurn();
    std::cout << "\n===== " << getName() << "'s turn =====" << std::endl;
    
    // Draw 5 cards
    for (int i = 0; i < 5; ++i) {
        if (!hand.drawFromDrawPile(drawPile, discardPile)) {
            break;
        }
    }
    
    // Update status effects
    updateStatusEffects();
    //printStatus();
    //hand.showHand();
}


void Player::endTurn() {
    std::cout << "\n===== End turn =====" << std::endl;
    // Move all hand cards to discard pile
    hand.discardAll(discardPile);
}

void Player::addCardToDeck(std::unique_ptr<Card> card) {
    if (card) {
        discardPile.addDiscarded(std::move(card));
        std::cout << "Obtained new card: " << card->getName() << std::endl;
    }
}

void Player::printStatus() const{
    std::cout << name << " - Health: " << health << "/" << maxHealth  
              << " Block: " << block << " Energy: " << energy << "/" << maxEnergy << std::endl;
    
    if (!statusEffects.empty()) {
        std::cout << "Status effects: ";
        for (const auto& effect : statusEffects) {
            std::cout << effect->getInfo() << " ";
        }
        std::cout << std::endl;
    }
}


// Monster class implementation
void Monster::takeTurn(Player* player) {
    if (!player || !player->isAlive()) return;
    
    std::cout << "\n===== " << getName() << "'s turn =====" << std::endl;
    
    // Execute current attack in pattern
    if (currentPatternIndex < attackPattern.size()) {
        int damage = attackPattern[currentPatternIndex];
        if(damage >= 0) {
            for(auto& effect : statusEffects) {
                switch (effect->getType()) {
                    case StatusType::WEAK:
                        damage *= effect->getIntensity();
                        break;
                    case StatusType::STRENGTH:
                        damage += effect->getIntensity();
                        break;
                }
            }
            for(auto& effect : player->statusEffects) {
                switch (effect->getType()) {
                    case StatusType::VULNERABLE:
                        damage *= effect->getIntensity();
                        break;
                }
            }
            player->takeDamage(damage);
            std::cout << getName() << " attacked " << player->getName() 
                << ", dealing " << damage << " damage!" << std::endl;
        }

        else if(damage == -1) {
            StatusEffect effect = toself[currentPatternIndex];
            int effectValue = effect.getIntensity();
            if(effect.getType() == StatusType::BLOCK) {
                for(auto& effect : statusEffects) {
                    if(effect->getType() == StatusType::Frail) {
                        effectValue = int(2.0/3.0 * effectValue);
                        break;
                    }
                }
            }
            gainBlock(effectValue);
        }
        else {
            StatusEffect effect = toself[currentPatternIndex];
            if(effect.getType() == StatusType::BLOCK) 
                player->gainBlock(effect.getIntensity());
            else 
                player->addStatusEffect(effect.getType(), effect.getIntensity(), effect.getDuration(), effect.getIsPermanent());
            std::cout << getName() << " applied " 
                      << effect.getInfo() << " to " << player->getName() << std::endl;
        }
        
        currentPatternIndex = (currentPatternIndex + 1) % attackPattern.size();
    }
    
    player->printStatus();

    // Update status effects
    updateStatusEffects();
}

void Monster::printStatus() const {
    std::cout << name << " - Health: " << health << "/" << maxHealth  
              << " Block: " << block << std::endl;
    
    if (!statusEffects.empty()) {
        std::cout << "Status effects: ";
        for (const auto& effect : statusEffects) {
            std::cout << effect->getInfo() << " ";
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
    while (combatActive) {
        // Player's turn
        player->startTurn();
        
        // Player actions (simplified)
        bool turnActive = true;
        while (turnActive && player->isAlive()) {
            // Show hand
            Hand& hand = player->getHand();
            hand.showHand();
            // Show player status
            player->printStatus();
            // Show monster status
            for (auto& monster : monsters) {
                monster->printStatus();
            }
            std::cout << "\nPlease choose an action:" << std::endl;
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
            }
        }
        
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

    if (result) {
        std::cout << "Combat victory" << std::endl;
        //后续填充奖励卡牌
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
    auto floor = std::make_unique<Floor>(floorNumber);

    // Add rooms to the floor (simplified version)
    // 1. Add combat room
    std::string aa="Slime"; 
    Monster monster(std::move(aa),1, {20}, 20,{},{});

    auto combatRoom = std::make_unique<CombatRoom>("Monster Nest");
    combatRoom->addMonster(std::make_unique<Monster>(monster));


    floor->addRoom(std::move(combatRoom));

    // 2. Add another combat room
    std::string aa1="Bat Swarm"; 
    Monster monster2(std::move(aa1),1,std::vector<int>{4 + floorNumber * 2, 0},20,{},{});

    auto combatRoom2 = std::make_unique<CombatRoom>("Dark Corridor");
    combatRoom2->addMonster(std::make_unique<Monster>(monster2));
    floor->addRoom(std::move(combatRoom2));

    floors.push_back(std::move(floor));
}

void Game::run() {
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
    if (victory) {
        std::cout << "\n===== Congratulations! You have successfully cleared all floors! =====" << std::endl;
    } else {
    std::cout << "\n===== Game over, your adventure has failed. =====" << std::endl;
    }
}