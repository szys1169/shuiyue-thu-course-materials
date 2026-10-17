#include "widget.h"
#include "config.h"
#include "gamethread.h"
#include <QGridLayout>  // 改用网格布局
#include <QPixmap>
#include <QStyleOption>
#include <QPainter>
#include<iostream>
#include<QDebug>

GamestartWindow::GamestartWindow(QWidget *parent) : QWidget(parent)
{

    initScene();

    // 1. 初始化背景标签（底层，铺满整个窗口）
    backgroundLabel = new QLabel(this);
    backgroundLabel->setScaledContents(true);  // 图片自适应窗口
    backgroundLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // 2. 初始化按钮（上层，父部件是主窗口，确保能覆盖背景）
    startButton = new QPushButton("开始游戏", this);
    exitButton = new QPushButton("结束游戏", this);
    startButton->setFixedSize(120, 40);
    exitButton->setFixedSize(120, 40);
    // 按钮样式（可选，增强视觉）
    startButton->setStyleSheet(R"(
        QPushButton { background-color: #2E8B57; color: white; border: none; border-radius: 4px; }
        QPushButton:hover { background-color: #3eaa6d; }
    )");
    exitButton->setStyleSheet(R"(
        QPushButton { background-color: #DC143C; color: white; border: none; border-radius: 4px; }
        QPushButton:hover { background-color: #e63946; }
    )");

    // 3. 按钮子布局（垂直排列两个按钮）
    QVBoxLayout *btnVLayout = new QVBoxLayout();
    btnVLayout->setSpacing(15);  // 按钮之间的间距
    btnVLayout->addWidget(startButton);
    btnVLayout->addWidget(exitButton);
    btnVLayout->setContentsMargins(0, 0, 0, 0);  // 清除子布局边距

    // 4. 关键：用网格布局实现“背景+按钮”叠加
    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->setContentsMargins(20, 20, 20, 20);  // 窗口整体边距（避免内容贴边）
    mainLayout->setSpacing(0);

    // 把背景标签放在网格的 (0,0) 单元格（占满整个单元格）
    mainLayout->addWidget(backgroundLabel, 0, 0, 1, 1);
    // 把按钮布局也放在 (0,0) 单元格（与背景同一位置），并对齐到左下角
    mainLayout->addLayout(btnVLayout, 0, 0, 1, 1, Qt::AlignBottom | Qt::AlignLeft);

    // 5. 信号槽连接
    connect(startButton, &QPushButton::clicked, this, &GamestartWindow::onStartGameClicked);
    connect(exitButton, &QPushButton::clicked, this, &GamestartWindow::onExitGameClicked);

    // 初始化主页面
    setupMainPage();
}

GamestartWindow::~GamestartWindow()
{
    // Qt 对象树会自动释放子部件，无需手动 delete（除非手动脱离对象树）
}

// 初始化场景（窗口大小、标题）
void GamestartWindow::initScene()
{
    setFixedSize(GAME_WIDTH, GAME_HEIGHT);
    setWindowTitle(GAME_TITLE);
}

// 设置主页面（初始背景+显示按钮）
void GamestartWindow::setupMainPage()
{
    // 加载背景图片（替换为你的实际路径，建议用相对路径，如 "./image/背景.png"）
    QPixmap pixmap("C:/123/qt/untitled/image/background.png");
    if (pixmap.isNull()) {
        backgroundLabel->setText("❌ 背景图片加载失败");
        backgroundLabel->setStyleSheet("color: red; font-size: 24px;");
        backgroundLabel->setAlignment(Qt::AlignCenter);  // 错误提示居中
    } else {
        backgroundLabel->setPixmap(pixmap);
        backgroundLabel->setAlignment(Qt::AlignCenter);  // 图片居中（避免拉伸变形）
    }
    // 显示按钮
    startButton->show();
    exitButton->show();
}
// 开始游戏按钮点击事件
void GamestartWindow::onStartGameClicked()
{
    setupGamePage();  // 切换到游戏页面
}

// 结束游戏按钮点击事件
void GamestartWindow::onExitGameClicked()
{
    close();  // 关闭整个窗口
}
void GamestartWindow::onUpdateBackground(const QString& imagePath) {
    QPixmap pixmap(imagePath);
    if (pixmap.isNull()) {
        backgroundLabel->setText("❌ 游戏背景加载失败");
        backgroundLabel->setStyleSheet("color: red; font-size: 24px;");
    } else {
        backgroundLabel->setPixmap(pixmap.scaled(
            backgroundLabel->size(),
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
        ));
    }
}

// 设置游戏页面（切换背景）
void GamestartWindow::setupGamePage()
{


    GameThread* gameThread = new GameThread(&game, this);  // 传递Game*参数


    // 隐藏按钮（进入游戏后按钮消失）
    startButton->hide();
    exitButton->hide();

    // 新增：初始化结束回合按钮
        endTurnButton = new QPushButton("结束回合", this);
        endTurnButton->setFixedSize(120, 40);
        endTurnButton->setStyleSheet(R"(
            QPushButton { background-color: #4682B4; color: white; border: none; border-radius: 4px; }
            QPushButton:hover { background-color: #5a9bd5; }
        )");
        // 设置位置（例如：右上角）
        endTurnButton->setGeometry(GAME_WIDTH - 140, 20, 120, 40);
        endTurnButton->show();
        // 关联点击事件
        connect(endTurnButton, &QPushButton::clicked, this, &GamestartWindow::onEndTurnClicked);
    //人物信息标签初始化
    playerInfoLabel = new QLabel(this);
        playerInfoLabel->setStyleSheet(R"(
            background-color: rgba(0, 0, 0, 0.7);
            color: white;
            padding: 8px;
            border-radius: 4px;
            font-size: 14px;
        )");
        playerInfoLabel->hide(); // 初始隐藏
        // 初始化怪物信息标签
           monsterInfoLabel = new QLabel(this);
           monsterInfoLabel->setStyleSheet(playerInfoLabel->styleSheet()); // 复用样式
           monsterInfoLabel->setFixedSize(200, 100); // 固定尺寸，与人物信息面板一致
           monsterInfoLabel->hide(); // 初始隐藏

           // 初始化手牌容器
               handCardContainer = new QWidget(this);
               handCardContainer->setStyleSheet("background-color: rgba(0, 0, 0, 0.3); border-radius: 8px;");
               handCardContainer->setFixedHeight(150); // 固定高度

               // 初始化水平布局（居中排列卡牌）
               handCardLayout = new QHBoxLayout(handCardContainer);
               handCardLayout->setSpacing(10); // 卡牌间距
               handCardLayout->setAlignment(Qt::AlignCenter); // 居中对齐
               handCardLayout->setContentsMargins(20, 10, 20, 10); // 容器内边距

               // 设置手牌容器位置（底部居中）
               handCardContainer->setGeometry(0, GAME_HEIGHT - 170, GAME_WIDTH, 150);
               handCardContainer->show();

               // 连接手牌更新信号
               connect(gameThread->getGame(), &Game::updateHandCards,
                       this, &GamestartWindow::onUpdateHandCards,
                       Qt::QueuedConnection);


    connect(gameThread->getGame(), &Game::updateBackground,
                this, &GamestartWindow::onUpdateBackground,
                Qt::QueuedConnection);

    connect(gameThread->getGame(), &Game::updateplayer,
                this, &GamestartWindow::onUpdateplayer,
                Qt::QueuedConnection);

    connect(gameThread->getGame(), &Game::updatemonster,
                this, &GamestartWindow::onUpdatemonster,
                Qt::QueuedConnection);
    //connect(this, &GamestartWindow::sendPlayerAction,gameThread->getGame(), &Game::onReceivePlayerAction,Qt::QueuedConnection);
    //连接结束回合按钮
    connect(this, &GamestartWindow::sendPlayerAction,
            gameThread->getGame(), &Game::onReceivePlayerAction,
            Qt::QueuedConnection);

    playerButton = new QPushButton(this);
    monsterButton = new QPushButton(this);
        // 设置按钮样式（无边框、透明背景，仅显示图片）
    playerButton->setStyleSheet("border: none; background: transparent;");
    monsterButton->setStyleSheet("border: none; background: transparent;");
        // 初始隐藏（进入游戏后再显示）
    playerButton->hide();
    monsterButton->hide();
        // 关联按钮点击事件（可选）
    connect(playerButton, &QPushButton::clicked, this, &GamestartWindow::onPlayerButtonClicked);
    connect(monsterButton, &QPushButton::clicked, this, &GamestartWindow::onMonsterButtonClicked);

    // 初始化奖励提示标签
    rewardLabel = new QLabel("选择一张卡牌作为奖励", this);
    rewardLabel->setStyleSheet(R"(
        color: white;
        font-size: 20px;
        font-weight: bold;
        background-color: rgba(0, 0, 0, 0.5);
        padding: 8px;
        border-radius: 4px;
    )");
    rewardLabel->setAlignment(Qt::AlignCenter);
    rewardLabel->hide(); // 初始隐藏

    // 初始化奖励卡牌容器
    rewardCardContainer = new QWidget(this);
    rewardCardContainer->setStyleSheet("background-color: rgba(0, 0, 0, 0.3); border-radius: 8px;");
    rewardCardContainer->setFixedHeight(200);

    // 初始化水平布局
    rewardCardLayout = new QHBoxLayout(rewardCardContainer);
    rewardCardLayout->setSpacing(30);
    rewardCardLayout->setAlignment(Qt::AlignCenter);
    rewardCardLayout->setContentsMargins(20, 10, 20, 10);

    // 设置位置（屏幕中间）
    rewardCardContainer->setGeometry(0, (GAME_HEIGHT - 200) / 2, GAME_WIDTH, 200);
    rewardCardContainer->hide();

    // 连接奖励卡牌信号
    connect(gameThread->getGame(), &Game::showRewardCards,
            this, &GamestartWindow::onShowRewardCards,
            Qt::QueuedConnection);
    //能量标签
    energyLabel = new QLabel(this);
    energyLabel->setVisible(false); // 初始隐藏
    energyLabel->setStyleSheet("background-color: rgba(0,0,0,0.7); color: white; padding: 5px; border-radius: 3px;");
    connect(gameThread->getGame(), &Game::energyChanged, this, [this]() {
        updateEnergyLabel(game.getPlayer());
    });
    // 初始化玩家血量标签
        playerHealthLabel = new QLabel(this);
        playerHealthLabel->setStyleSheet("color: green; font-size: 16px; font-weight: bold;");
        playerHealthLabel->hide(); // 初始隐藏

        // 初始化怪物血量标签
        monsterHealthLabel = new QLabel(this);
        monsterHealthLabel->setStyleSheet("color: red; font-size: 16px; font-weight: bold;");
        monsterHealthLabel->hide(); // 初始隐藏

        // 新增玩家血量标签连接
        connect(gameThread->getGame(), &Game::playerHealthChanged, this, [this]() {
            updatePlayerHealthLabel(game.getPlayer());
        });

        // 新增怪物血量标签连接
        connect(gameThread->getGame(), &Game::monsterHealthChanged, this, [this]() {
            updateMonsterHealthLabel();
        });
        //怪物意图标签
        monsterIntentLabel = new QLabel(this);
        monsterIntentLabel->setStyleSheet("color: yellow; font-size: 14px; background-color: rgba(0,0,0,0.7); padding: 5px;");
        monsterIntentLabel->setVisible(false);

        connect(gameThread->getGame(), &Game::updateMonsterIntent, this, &GamestartWindow::updateMonsterIntentLabel);
    //下一关按钮初始化
    nextRoomButton = new QPushButton("下一关", this);
       nextRoomButton->setFixedSize(120, 40);
       nextRoomButton->setStyleSheet(R"(
           QPushButton { background-color: #FFA500; color: white; border: none; border-radius: 4px; }
           QPushButton:hover { background-color: #ffb733; }
       )");
       // 设置位置（例如：屏幕底部中央）
       nextRoomButton->setGeometry((GAME_WIDTH - 120) / 2, GAME_HEIGHT - 80, 120, 40);
       nextRoomButton->hide(); // 默认隐藏，战斗胜利后显示
       // 关联点击事件
       connect(nextRoomButton, &QPushButton::clicked, this, &GamestartWindow::onNextRoomClicked);
       connect(gameThread->getGame(), &Game::showNextRoomButton,
                   this, [this]() {
           // 1. 隐藏结束回合按钮
                          //endTurnButton->hide();

                          // 2. 隐藏玩家和怪物按钮
                          playerButton->hide();
                          monsterButton->hide();

                          // 3. 隐藏玩家/怪物信息标签（如果显示）
                          //playerInfoLabel->hide();
                          //monsterInfoLabel->hide();

                          // 4. 清除并隐藏所有卡牌按钮
                          //qDeleteAll(cardButtons.values());
                          //cardButtons.clear();
                          //handCardContainer->hide(); // 隐藏手牌容器

                          // 5. 最后显示下一关按钮
                       //endTurnButton->hide();
                       // 显示下一关按钮
                       nextRoomButton->show();
                   }, Qt::QueuedConnection);
       //结束更新游戏界面
       connect(gameThread->getGame(), &Game::gameOverBackground,
               this, &GamestartWindow::onGameOverBackground,
               Qt::QueuedConnection);
   // 启动游戏线程
    gameThread->start();
    //Game game;

    // 初始化游戏（设置3层楼）
    //game.initialize(3);

    //Player Warrior;

    // 运行游戏主循环
    //game.run();
}

// 处理人物的槽函数
void GamestartWindow::onUpdateplayer(const QString& imagePath)
{

    QPixmap pixmap(imagePath);
    if (pixmap.isNull()) {
        // 图片加载失败时显示文本
        playerButton->setText("❌ 玩家图片加载失败");
        playerButton->setStyleSheet("color: red; font-size: 16px; border: none;");
    } else {
        // 图片加载成功时设置为按钮图标
        QIcon icon(pixmap.scaled(
            600, 400,
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
        ));
        playerButton->setIcon(icon);
        // 设置图标大小（与按钮大小一致）
        playerButton->setIconSize(QSize(600, 400));
        // 重置样式（避免残留文本样式）
        playerButton->setStyleSheet("border: none; background: transparent;");
    }
        // 计算中间左侧位置（基于1920x1080窗口）
        int playerX = (GAME_WIDTH / 2-700) ;  // 中间偏左300像素
        int playerY = (GAME_HEIGHT / 2-200) ;  // 垂直居中（减去图片高度的一半）

        // 设置玩家位置
        playerButton->setGeometry(playerX, playerY, 600, 400);
        playerButton->raise();
        playerButton->show();
}

// 处理怪物的槽函数

void GamestartWindow::onUpdatemonster(const QString& imagePath)
{
    QPixmap pixmap(imagePath);
        if (pixmap.isNull()) {
            // 图片加载失败时显示文本
            monsterButton->setText("❌ 怪物图片加载失败");
            monsterButton->setStyleSheet("color: red; font-size: 16px; border: none;");
        } else {
            // 图片加载成功时设置为按钮图标
            QIcon icon(pixmap.scaled(
                400, 600,
                Qt::KeepAspectRatio,
                Qt::SmoothTransformation
            ));
            monsterButton->setIcon(icon);
            // 设置图标大小（与按钮大小一致）
            monsterButton->setIconSize(QSize(400, 600));
            // 重置样式
            monsterButton->setStyleSheet("border: none; background: transparent;");
        }

        // 计算中间右侧位置（基于1920x1080窗口）
        int monsterX = (GAME_WIDTH / 2) + 400;  // 中间偏右180像素
        int monsterY = (GAME_HEIGHT / 2)-300;  // 垂直居中（减去图片高度的一半）

        // 设置怪物位置
        monsterButton->setGeometry(monsterX, monsterY, 400, 600);
        monsterButton->show();
}

void GamestartWindow::onPlayerButtonClicked()
{
    if (playerInfoLabel->isVisible()) {
          playerInfoLabel->hide();
          return;
      }
    // 示例：弹出人物信息
    // QMessageBox::information(this, "玩家信息", "当前玩家生命值：xxx");
    //emit sendPlayerAction("player_clicked");
       Player* player = game.getPlayer(); // 假设Game类添加getPlayer()方法返回Player*
       if (!player) return;

       // 1. 拼接信息字符串
       QString info;
       // 血量：当前/最大
       info += QString("血量: %1/%2\n").arg(player->getHealth()).arg(player->getMaxHealth());
       // 护盾
       info += QString("护盾: %1\n").arg(player->getBlock());
       // 状态效果
       info += "状态: ";
       bool hasStatus = false;
       for (const auto& effect : player->statusEffects) {
           hasStatus = true;
           info += QString::fromStdString(effect.getInfo()) + " ";
       }
       if (!hasStatus) info += "无";

       // 2. 设置信息到标签
       playerInfoLabel->setText(info);

       // 3. 计算标签位置（人物按钮右侧10像素，对齐顶部）
       QRect playerRect = playerButton->geometry();
       int x = playerRect.right() + 10;
       int y = playerRect.top();
       playerInfoLabel->setGeometry(x, y, 200, 100); // 宽度200，高度100

       // 4. 显示标签
       playerInfoLabel->show();
}

// 怪物按钮点击事件
void GamestartWindow::onMonsterButtonClicked()
{
    // 示例：弹出怪物信息
    // QMessageBox::information(this, "怪物信息", "当前怪物生命值：xxx");
    // 1. 如果已显示则隐藏
        if (monsterInfoLabel->isVisible()) {
            monsterInfoLabel->hide();
            return;
        }

        // 2. 未显示则加载怪物信息
        // 获取当前战斗房间的第一个存活怪物
        Monster* monster = nullptr;
        auto& monsters = game.getCurrentRoomMonsters(); // 从Game类获取当前房间怪物
        for (auto& m : monsters) {
            if (m->isAlive()) {
                monster = m.get();
                break;
            }
        }
        if (!monster) {
            monsterInfoLabel->setText("无存活怪物");
            monsterInfoLabel->show();
            return;
        }

        // 3. 拼接怪物信息字符串
        QString info;
        info += QString("名称: %1\n").arg(QString::fromStdString(monster->getName()));
        info += QString("血量: %1/%2\n").arg(monster->getHealth()).arg(monster->getMaxHealth());
        info += QString("护盾: %1\n").arg(monster->getBlock());
        info += "状态: ";
        bool hasStatus = false;
        for (const auto& effect : monster->statusEffects) {
            hasStatus = true;
            info += QString::fromStdString(effect.getInfo()) + " ";
        }
        if (!hasStatus) info += "无";

        // 4. 设置标签位置（怪物按钮左侧10像素，对齐顶部）
        QRect monsterRect = monsterButton->geometry();
        int x = monsterRect.left() - monsterInfoLabel->width() - 10; // 左侧间距10px
        int y = monsterRect.top();
        monsterInfoLabel->setGeometry(x, y, monsterInfoLabel->width(), monsterInfoLabel->height());
        monsterInfoLabel->setText(info);

        // 5. 显示标签
        monsterInfoLabel->show();
}

void GamestartWindow::onUpdateHandCards(const QStringList& cardImagePaths) {
    // 清除现有卡牌按钮
    qDeleteAll(cardButtons.values());
    cardButtons.clear();

    // 限制最大显示数量（10张）
    int displayCount = qMin(cardImagePaths.size(), 10);

    // 创建新的卡牌按钮
    for (int i = 0; i < displayCount; ++i) {
        QPushButton* cardBtn = new QPushButton(handCardContainer);
        cardBtn->setFixedSize(100, 140); // 卡牌尺寸
        cardBtn->setStyleSheet("border: 2px solid #555; border-radius: 4px;");

        // 设置卡牌图片
        //qDebug() << "Card image path:" << cardImagePaths[i];
        QPixmap pixmap(cardImagePaths[i]);

        if (!pixmap.isNull()) {
            cardBtn->setIcon(QIcon(pixmap.scaled(
                96, 136,
                Qt::KeepAspectRatio,
                Qt::SmoothTransformation
            )));
            cardBtn->setIconSize(QSize(96, 136));
        } else {
            cardBtn->setText(QString("卡牌 %1").arg(i+1));
            cardBtn->setStyleSheet("background-color: #888; color: white; border: 2px solid #555; border-radius: 4px;");
        }

        // 存储按钮索引并连接点击事件
        cardButtons[i] = cardBtn;
        connect(cardBtn, &QPushButton::clicked, [this, i]() {
            // 发送使用卡牌的动作（索引+1因为用户习惯从1开始）
            emit sendPlayerAction(QString("use_card_%1").arg(i+1));
        });

        handCardLayout->addWidget(cardBtn);
    }
}

// 结束回合按钮点击事件
void GamestartWindow::onEndTurnClicked() {
    emit sendPlayerAction("end_turn"); // 发送“结束回合”信号给逻辑层
}

// 新增：下一关按钮点击事件
void GamestartWindow::onNextRoomClicked() {
    // 清除现有奖励卡牌按钮
    qDeleteAll(rewardCardButtons.values());
    rewardCardButtons.clear();

    // 隐藏下一关按钮
    nextRoomButton->hide();
    // 2. 重置手牌容器并显示（为新房间手牌做准备）
        handCardContainer->show();
        qDeleteAll(cardButtons.values());  // 强制清除残留卡牌按钮
        cardButtons.clear();


        // 3. 显示结束回合按钮（新回合需要）
        endTurnButton->show();

        // 4. 发送进入下一关信号
        emit sendPlayerAction("next_room");
}
//展示奖励卡牌
void GamestartWindow::onShowRewardCards(const QStringList& rewardCardPaths) {
    // 清除现有奖励卡牌按钮
    qDeleteAll(rewardCardButtons.values());
    rewardCardButtons.clear();

    // 隐藏其他UI元素
    endTurnButton->hide();
    playerButton->hide();
    monsterButton->hide();
    playerInfoLabel->hide();
    monsterInfoLabel->hide();
    handCardContainer->hide();
    nextRoomButton->hide();
    energyLabel->hide();
    monsterIntentLabel->hide();
    playerHealthLabel->hide();
    monsterHealthLabel->hide();

    // 显示奖励相关UI
    rewardLabel->setGeometry((GAME_WIDTH - 300) / 2, (GAME_HEIGHT - 300) / 2 - 50, 300, 40);
    rewardLabel->show();
    rewardCardContainer->show();

    // 创建奖励卡牌按钮
    for (int i = 0; i < rewardCardPaths.size() && i < 3; ++i) {
        QPushButton* cardBtn = new QPushButton(rewardCardContainer);
        cardBtn->setFixedSize(150, 180);
        cardBtn->setStyleSheet("border: 2px solid #555; border-radius: 4px;");

        // 设置卡牌图片
        QPixmap pixmap(rewardCardPaths[i]);
        if (!pixmap.isNull()) {
            cardBtn->setIcon(QIcon(pixmap.scaled(
                146, 176,
                Qt::KeepAspectRatio,
                Qt::SmoothTransformation
            )));
            cardBtn->setIconSize(QSize(146, 176));
        } else {
            cardBtn->setText(QString("奖励卡牌 %1").arg(i+1));
            cardBtn->setStyleSheet("background-color: #888; color: white; border: 2px solid #555; border-radius: 4px;");
        }

        // 连接点击事件
        rewardCardButtons[i] = cardBtn;
        connect(cardBtn, &QPushButton::clicked, [this, i]() {
            onRewardCardSelected(i);
        });

        rewardCardLayout->addWidget(cardBtn);
    }
}
//奖励卡牌选择后
void GamestartWindow::onRewardCardSelected(int index) {
    // 隐藏奖励相关UI（现有代码）
    rewardLabel->hide();
    rewardCardContainer->hide();
    qDeleteAll(rewardCardButtons.values());
    rewardCardButtons.clear();

    // 发送选择结果给逻辑层（确保格式正确）
    emit sendPlayerAction(QString("select_reward_card_%1").arg(index));
    handCardContainer->show();
    qDeleteAll(cardButtons.values());  // 强制清除残留卡牌按钮
    cardButtons.clear();


    // 3. 显示结束回合按钮（新回合需要）
    endTurnButton->show();

    // 4. 发送进入下一关信号
    emit sendPlayerAction("next_room");
}
//更新标签
void GamestartWindow::updateEnergyLabel(Player* player) {
    if (!player) return;

    // 设置能量文本
    QString energyText = QString("能量: %1/%2").arg(player->getEnergy()).arg(3);
    energyLabel->setText(energyText);

    // 设置位置（示例：玩家按钮下方）
    QRect playerRect = playerButton->geometry();
    int x = playerRect.left();
    int y = playerRect.bottom() + 10;
    energyLabel->setGeometry(x, y, 100, 30);

    energyLabel->show();
}
// 更新玩家血量标签
void GamestartWindow::updatePlayerHealthLabel(Player* player) {
    if (!player) return;

    // 设置血量文本（当前血量/最大血量）
    QString healthText = QString("血量: %1/%2")
        .arg(player->getHealth())
        .arg(player->getMaxHealth());
    playerHealthLabel->setText(healthText);

    // 定位在玩家按钮上方（示例位置，可调整）
    QRect playerRect = playerButton->geometry();
    int x = playerRect.left();
    int y = playerRect.top() - 30; // 按钮上方30像素
    playerHealthLabel->setGeometry(x, y, 120, 30);

    playerHealthLabel->show();
}

// 更新怪物血量标签
void GamestartWindow::updateMonsterHealthLabel() {
    // 获取当前存活的第一个怪物
    Monster* monster = nullptr;
    auto& monsters = game.getCurrentRoomMonsters();
    for (auto& m : monsters) {
        if (m->isAlive()) {
            monster = m.get();
            break;
        }
    }
    if (!monster) {
        monsterHealthLabel->hide();
        return;
    }

    // 设置血量文本（当前血量/最大血量）
    QString healthText = QString("血量: %1/%2")
        .arg(monster->getHealth())
        .arg(monster->getMaxHealth());
    monsterHealthLabel->setText(healthText);

    // 定位在怪物按钮上方（示例位置，可调整）
    QRect monsterRect = monsterButton->geometry();
    int x = monsterRect.left();
    int y = monsterRect.top() - 30; // 按钮上方30像素
    monsterHealthLabel->setGeometry(x, y, 120, 30);

    monsterHealthLabel->show();
}

//更新怪物意图标签
void GamestartWindow::updateMonsterIntentLabel() {
    // 获取当前存活的第一个怪物
    Monster* monster = nullptr;
    auto& monsters = game.getCurrentRoomMonsters();
    for (auto& m : monsters) {
        if (m->isAlive()) {
            monster = m.get();
            break;
        }
    }
    if (!monster) {
        monsterIntentLabel->hide();
        return;
    }

    // 获取怪物下一回合的行动
    std::string intent;
    const auto& attackPattern = monster->getAttackPattern(); // 需要在Monster类中添加getter方法
    int nextIndex = monster->getCurrentPatternIndex(); // 需要在Monster类中添加getter方法

    if (!attackPattern.empty()) {
        // 获取下一个要执行的攻击卡片
        const Card& nextAction = attackPattern[nextIndex];
        intent = "意图: " + nextAction.getInfoMonster();
    } else {
        intent = "意图: 无";
    }

    // 设置意图文本
    monsterIntentLabel->setText(QString::fromStdString(intent));

    // 定位在怪物血量标签上方
    QRect monsterRect = monsterButton->geometry();
    int x = monsterRect.left();
    int y = monsterRect.top() - 60; // 血量标签上方30像素
    monsterIntentLabel->setGeometry(x, y, 200, 30);

    monsterIntentLabel->show();
}

// 添加在widget.cpp中
void GamestartWindow::onGameOverBackground(bool victory) {
    // 成功背景
    if(victory)onUpdateBackground("C:/123/qt/untitled/image/background.png");
    //失败背景
    else onUpdateBackground("C:/123/qt/untitled/image/background.png");

    // 可选：隐藏游戏中的UI元素（如按钮、卡牌容器等），只显示结束背景
    endTurnButton->hide();
    playerButton->hide();
    monsterButton->hide();
    playerInfoLabel->hide();
    monsterInfoLabel->hide();
    handCardContainer->hide();
    nextRoomButton->hide();
    energyLabel->hide();
    monsterIntentLabel->hide();
    playerHealthLabel->hide();
    monsterHealthLabel->hide();
}
