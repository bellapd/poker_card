# poker_card
# Assignment 1-1

Consider a standard 52-card deck. Each card has a suit of either clubs, diamonds, hearts or spades. Each card also has a value (or face) of either 2 through 10, jack, queen,
king, or ace. A poker hand consists of five cards dealt from the deck. Poker cards are ranked first by their values then by their suits, given that spades > hearts > diamonds > clubs. Poker hands are ranked by their nine patterns as follows (from the largest to the smallest).

1. **Straight Flush** (同花順). Five cards of the same suit with consecutive values. ranked by the highest card in the hand. Note that “10 J Q K A” is considered the largest
straight and “2 3 4 5 6” is considered the smallest. “A 2 3 4 5” is NOT considered a straight.
2. **Four of a Kind** (鐵支). Four cards with the same value. ranked by the value of the four cards.
3. **Full House** (葫蘆). Three cards of the same value, with the remaining two cards forming a pair. Ranked by the value of the three cards.
4. **Flush** (同花). Hand contains five cards of the same suit. Hands which are both flushes are ranked by their largest card.
5. **Straight** (順子). This type of hand contains five cards with consecutive values. Hands which both contain straight are ranked by their highest card.
6. **Three of a Kind** (三條). Three of the cards in the hand have the same value. Hands which both contain three of a kind are ranked by the value of the three cards.
7. **Two Pairs** (兩對). This type of hand contains two different pairs. Hands which both contain two pairs are ranked by the value of their highest pair. Hands with the same highest pair are ranked by the high suits of the highest pairs.
8. **Pair** (對子). Two of the five cards in the hand have the same value. Hands which both contain a pair are ranked by the value of the cards forming the pair. Hands with the same value of pair are ranked by the high suits of the pairs.
9. **High Card** (胡亂). The hand that does not fit in any category is ranked by the value of their
highest card. 



---
## What you need to do ##

First you get the input from the user. In your input, the suits are represented by the characters S, H, D, C (for spade, heart, diamond, and club). The values are represented by 2~9, T (representing 10), J, Q, K, and A. Here is an example of the input. `CT CK CJ CA CQ`.
Your program should determine the highest pattern of a poker hand and output the sorted pattern according to the following rules.

1. For straight flush, flush, straight, and high card, your output should be sorted in **ascending order**. You should also output the highest card. On the previous input your program should output
```js
CA-straight flush
C10 CJ CQ CK CA
```
In this example, CA (the club ace) is the highest card in this straight flush. That's why you should show it. You should also output '10' instead of 'T'.


2. For four of a kind, you should output the single card first, followed by the sorted four of a kind. You should also output the value of the four of a kind. For example, on input `D2 ST S2 H2 C2`, your program should output
```js
2-four of a kind
S10 C2 D2 H2 S2
```


3. For full house, you should first output the sorted pair, followed by the sorted three of a kind. You should also output the value of the three of a kind.
On input `D7 SJ H7 HJ C7`, your program should output
```js
7-full house
HJ SJ C7 D7 H7
```

4. For two pairs, you should first output the single card, followed by the sorted smaller pair and the sorted larger pair. You should also output the highest card of the highest pair. On input `D5 H5 SA HA CQ`, your program should output
```js
SA-two pairs
CQ D5 H5 HA SA
```

5. For three of a kind, you should output the (sorted) two single cards not in the ‘three of a kind’, followed by the sorted three of a kind. You should also output the value of the three of a kind.  On input `D9 SQ H9 H3 C9`, your program should output
```js
9-three of a kind
H3 SQ C9 D9 H9
```

6. For pair, you should output the (sorted) three single cards not in forming the pair, followed by the sorted pair. You should also output the highest card of the pair.
On input `D5 H5 SA HK CQ`, your program should output
```js
H5-pair
CQ HK SA D5 H5
```

7. For high card, you should output the cards in ascending order. You should also output the highest card.
On input `D5 H6 SA HK CQ`, your program should output
```js
SA-high card
D5 H6 CQ HK SA
```

You can always assume the user inputs legitimate data. **No input checking is required**.

---
## Grading Criteria ##
### Correctness 70% + Coding style 30%###
You should follow the [Github coding style] (https://github.com/MaJerle/c-code-style#variables) as this contributes to 30% of your grades. Note that you will ONLY get style points if your program is correct on at least some of our hidden cases. In other words, if your program cannot work, you won't get any style points.



Make sure you pass all test cases before submission. Any submissions after the deadline will **NOT be counted**. 


# Assignment 1-2


---
## What you need to do ##

Continuing from assignment 1-1, we are to compare two hands. First we take input from the user like the following example

```js
CT CK CJ CA CQ
D7 SJ H7 HJ C7
```
Here the user input a CA-straight flush and a 7-full house. Your program should compare them. Since straight flushes are bigger, your program should output
```js
C10 CJ CQ CK CA > HJ SJ C7 D7 H7
```
Note that your program should comply with the output format as in 1-1.

Here is another example. If the user inputs
```js
CT CK CJ CA CQ
C9 CQ CT CK CJ
```
Now, both of them are straight flushes. Your program should compare them according to their highest card and outputs
```js
C10 CJ CQ CK CA > C9 C10 CJ CQ CK
```
In the last example, if the user inputs the same hands as follows.
```js
CT CK CJ CA CQ
CA CK CJ CT CQ
```
Your program should output
```js
C10 CJ CQ CK CA == C10 CJ CQ CK CA
```
Note that your comparison should comply with the rules of ordinary card games. Althought different patterns have different comparison rules, we always compare hands according to their largest element first. If they are equal, we always compare them accoding to their smaller elements in order. For example, for high cards, we compare their largest card first, followed by their second largest and so on so forth. Their should not be any confusion. If you are not familiar with card games, do ask the TAs about them.

You can always assume the user inputs legitimate data. **No input checking is required**.

---
## Grading Criteria ##
### Correctness 70% + Coding style 30%###
You should follow the [Github coding style] (https://github.com/MaJerle/c-code-style#variables) as this contributes to 30% of your grades. Note that you will ONLY get style points if your program is correct on at least some of our hidden cases. In other words, if your program cannot work, you won't get any style points.



Make sure you pass all test cases before submission. Any submissions after the deadline will **NOT be counted**. 


