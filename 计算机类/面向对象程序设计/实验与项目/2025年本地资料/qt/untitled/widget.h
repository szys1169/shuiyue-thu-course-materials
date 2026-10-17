#ifndef WIDGET_H
#define WIDGET_H

#include "game.h"
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QThread>
#include<QMap>
#include"cards.h"
// 移除不必要的Ui命名空间（如果不使用.ui文件）
class GamestartWindow : public QWidget
{
    Q_OBJECT

public:
    Game game;
    GamestartWindow(QWidget *parent = nullptr);
    ~GamestartWindow();

    // 初始化场景
    void initScene();

signals:
    // 新增：向逻辑线程发送字符串的信号
    void sendPlayerAction(const QString& action);
private slots:
    void onStartGameClicked();  // 开始游戏按钮点击事件
    void onExitGameClicked();   // 结束游戏按钮点击事件
    void onPlayerButtonClicked();
    void onMonsterButtonClicked();

private:
    // 移除Ui::Widget指针（如果不使用.ui文件）
    //Ui::Widget *ui;
    QLabel* playerInfoLabel; // 玩家信息标签
    QLabel* monsterInfoLabel; // 怪物信息标签
    void setupMainPage();       // 设置主页面
    void setupGamePage();       // 设置游戏页面（声明需要实现）

    QLabel *backgroundLabel;    // 背景图片标签
    QPushButton *startButton;   // 开始游戏按钮（需初始化）
    QPushButton *exitButton;    // 结束游戏按钮（需初始化）
    QPushButton *playerButton;  // 人物按钮
    QPushButton *monsterButton; // 怪物按钮
    QWidget* handCardContainer;  // 手牌容器
    QHBoxLayout* handCardLayout; // 手牌布局
    QMap<int, QPushButton*> cardButtons; // 卡牌按钮映射（索引->按钮）
    QPushButton* endTurnButton; // 新增：结束回合按钮
    QPushButton* nextRoomButton; // 新增：下一关按钮
    QLabel* energyLabel;;    // 能量标签
    QLabel* playerHealthLabel;  // 玩家血量标签
    QLabel* monsterHealthLabel; // 怪物血量标签
    QLabel* monsterIntentLabel;//怪物意图标签

    // 奖励卡牌相关组件
        QLabel* rewardLabel;          // 奖励提示标签
        QWidget* rewardCardContainer; // 奖励卡牌容器
        QHBoxLayout* rewardCardLayout;// 奖励卡牌布局
        QMap<int, QPushButton*> rewardCardButtons; // 奖励卡牌按钮映射
private slots:
    // 处理背景更新的槽函数
    void onUpdateBackground(const QString& imagePath);
    // 处理人物的槽函数
    void onUpdateplayer(const QString& imagePath);
    // 处理怪物的槽函数
    void onUpdatemonster(const QString& imagePath);
    void onUpdateHandCards(const QStringList& cardImagePaths);
    void onEndTurnClicked(); // 新增：结束回合按钮点击事件
    void onNextRoomClicked();//下一关按钮
    void updateEnergyLabel(Player* player);//更新能量
    void updatePlayerHealthLabel(Player* player);//更新人物血量
    void updateMonsterHealthLabel();//更新怪物血量
    // 处理奖励卡牌更新
    void onShowRewardCards(const QStringList& rewardCardPaths);
    // 处理奖励卡牌选择
    void onRewardCardSelected(int index);
    //更新怪物意图标签
    void updateMonsterIntentLabel();
    // 处理游戏结束时的背景更新
    void onGameOverBackground(bool victory);
};
/*
class GameThread : public QThread {
    Q_OBJECT
public:
    void run() override {
        Game game;
        game.initialize(3);
        game.run(); // 游戏循环在子线程中执行
    }
};
*/
#endif // WIDGET_H
