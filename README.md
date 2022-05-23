<!--
 * @Author: lawrence-cell 850140027@qq.com
 * @Generate Date: Do not edit
 * @LastEditors: lawrence-cell 850140027@qq.com
 * @LastEditTime: 2022-05-22 15:01:40
 * @FilePath: \UNO\README.md
 * @Description: 
 * 
 * Copyright (c) 2022 by lawrence-cell 850140027@qq.com, All Rights Reserved. 
-->
# 比鸡游戏（CHICKRACE）
![](https://img.shields.io/badge/version-v1.0-9cf)

这是基于[Gusabary的github项目](https://github.com/Gusabary/UNO)改编的传统纸牌游戏，**比鸡**！



这是一款在我的老家江浙沪皖一带非常流行的棋牌游戏，游戏在依靠运气的同时也考验我们的取舍和博弈。

## 游戏流程
三位玩家轮流摸牌(当然在本游戏中以系统给玩家发牌的方式实现，虽然可能少了一些乐趣)。每人都有9张，通过配牌，每组三张牌，将9张牌配成3组，三组必须按照大小顺序进行排序(排序准则见后),第一组牌最小，第二组牌次之，第三组牌最大。等到所有人都配好牌后，大家按组进行比较，所有玩家的第一组(也就是最小的一组)进行比较，然后所有玩家的第二组以及第三组进行比较。每组比较最大的玩家为胜者，第二大的须给赢家一定数量的钱，第三大的须给赢家双倍的钱，依次类推。
## 牌库
传统的扑克牌去掉大王和小王。黑桃红桃梅花方块，四种花色各有13张牌分别是：A, 2~10, J, Q, K.

B = 黑桃，R = 红桃, F = 梅花，S = 方块。

在本游戏中以字母加上数字的方式确认每一张牌，第一个字母为花色，第二个数字(或字母)为数字，例如R2代表红桃2，RJ代表红桃J.
## 排序规则
### 组合排序(以下按照组合从大到小排序)
|     名称     |           组合           |        例子         |
| :----------: | :----------------------: | :-----------------: |
| 三个头(豹子) |   三张牌花色且数字一样   | R1 B1 F1 ; BJ FJ SJ |
| 金条(同花顺) | 三张牌花色一样且数字连号 | RA R2 R3 ; RQ RK RA |
| 青子(清一色) |      三张牌花色一样      | RA R7 R3 ; R* R* R* |
| 顺子(拖拉机) |      三张牌数字连号      | RA F2 S3 ; RQ SK BA |
|     对子     |  三张牌中有两张同样数字  | RA R2 F2 ; RQ FQ RA |
### 单牌排序
A>>K>>Q>>J>>10>>9>>...>>2
### 花色排序
B = 黑桃 >> R = 红桃 >> F = 梅花 >> S = 方块
### 其他规则
* 若一组三张牌的组合不满足以上任何一种，则为最小的组合；
* 若两组组合均属于同一类的组合，则比三张牌中最大的那一张牌。例如两个青子组合(RA, R2, R3) 与(FQ, F3, F6)，因为RA与FQ为组合中最大的牌，将他俩相比较，因A > Q所以第一个组合大；
* 若两组组合均属于同一类的组合，且最大牌的数字一样大，则比较第二大的牌，若第二大的牌也一样大，则比较第三大的牌。例如两个青子组合(RA, R2, R3) 与(FA, F3, F6)， 因最大的牌均为A，则比较第二大的牌，F6 > R3， 所以第二个组合大；
* 若两个组合的仅靠数字无法判定大小，需要依赖花色。例如两个青子组合(RA, R2, R3) 与(FA, F2, F3)，由于R > F，所以第一个组合大

## 奖励机制(喜钱机制)（BONUS）
当玩家摸到的牌触发了喜钱机制,则所有玩家需要给该玩家喜钱, 金额数量是单组数量的一半.例如所有玩家的第一组(每个玩家有三组牌,每组3张牌共9张牌)进行比较, 最小的玩家需要给出金额为2A的钱,则喜钱为A, 且所有其他玩家均需给触发喜钱机制的玩家数量为A的钱，且喜钱机制可以叠加。
### 触发条件
* 摸到的9张牌全红或全黑(R(红桃)+ S(方块) = 红， B(黑桃) + F(梅花) = 黑)
* 一个玩家的三组牌每组都是全场最大(俗称通关、三通)
* 摸到同一数字的四种花色，例如 R2,B2,F2,S2(俗称四个头)
* 摸到两个豹子，例如R2,B2,F2;F4,B4,S4.