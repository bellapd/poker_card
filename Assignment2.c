#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char suit;
  char face;
  int suit_rank;
  int face_rank;
  int idx;
} game_cards;

const char face_rank_asc[]={'2','3','4','5','6','7','8','9','T','J','Q','K','A'};
const char suit_rank_asc[]={'C','D','H','S'};
const char *rankStrings[]={"High Card","Single Pair","Two Pair","Three of a Kind","Straight","Flush","Full House","Four of a Kind","Straight Flush"};


int get_rank(const char* string, char c) {
  char* e = strchr(string, c);
  if (e == NULL) {
    return -1;
  }
  return (int)(e - string);
}

void swap(game_cards *xp, game_cards *yp) {
  game_cards temp = *xp;
  *xp = *yp;
  *yp = temp;
}

void selectionSort(game_cards arr[], int n) {
  int i, j, min_idx;
  /*One by one move boundary of unsorted subarray*/
  for (i = 0; i < n-1; i++) {
    /* Find the minimum element in unsorted array*/
    min_idx = i;
    for (j = i+1; j < n; j++) {
      if (arr[j].idx < arr[min_idx].idx) {
        min_idx = j;
      }
    }
    /*Swap the found minimum element with the first element*/
    swap(&arr[min_idx], &arr[i]);
  }
}

int card_idx(char suit, char face) {
  int suit_rank, face_rank;
  face_rank=get_rank(face_rank_asc,face);
  suit_rank=get_rank(suit_rank_asc,suit);
  return (int)((face_rank*4)+suit_rank);
}

char* idx2card(int idx) {
  int suit_rank, face_rank;
  static char card[2];

  face_rank=(int) idx/4;
  suit_rank=(int) idx%4;

  card[0]=suit_rank_asc[suit_rank];
  card[1]=face_rank_asc[face_rank];

  return card;
}


int isFlush(game_cards *card) {
  if (card[1].suit==card[2].suit && card[1].suit==card[3].suit && card[1].suit==card[4].suit) {
    return 1;  
  } else {
    return 0;
  }
}

int isStraight(game_cards *card) {
  selectionSort(&*card, 5);
  if (card[4].face == 'A') {
    if(card[3].face  == 'K' && card[2].face  == 'Q' &&
     card[1].face  == 'J' && card[0].face == 'T') {
      return 1;
    }
  }
  if (card[4].face == 'K') {
    if(card[3].face == 'Q' && card[2].face == 'J' && 
    card[1].face == 'T' && card[0].face == '9') {
      return 1;
    }
  }
  if (card[4].face == 'Q') {
    if(card[3].face == 'J' && card[2].face == 'T' && 
    card[1].face == '9' && card[0].face == '8') {
      return 1;
    }
  }
  if (card[4].face == 'J') {
    if(card[3].face == 'T' && card[2].face == '9' && 
    card[1].face == '8' && card[0].face == '7') {
      return 1;
    }
  }
  if (card[4].face == 'T') {
    if(card[3].face == '9' && card[2].face == '8' && 
    card[1].face == '7' && card[0].face == '6') {
      return 1;
    }
  } else {
      int j = 3, flag = 1, k = 1;

      while (j>=0 && flag == 1) {
        if ((int)card[4].face - 48 == (int)card[j].face - 48 + k) {
          j--;
          k++;
        } else {
          return 0;
        }
      }
  } 
  return 1;
}

int isThreeKind(game_cards card[]) {
  game_cards tmp[5];
  selectionSort(&*card, 5); 
  if (card[0].face == card[1].face && card[1].face == card[2].face) {
    if(card[3].face == card[4].face) {
      tmp[0] = card[3];
      tmp[1] = card[4];
      tmp[2] = card[0];
      tmp[3] = card[1];
      tmp[4] = card[2];
      card[0] = tmp[0];
      card[1] = tmp[1];
      card[2] = tmp[2];
      card[3] = tmp[3];
      card[4] = tmp[4];
      return 2;
    } else {
      tmp[0] = card[3];
      tmp[1] = card[4];
      tmp[2] = card[0];
      tmp[3] = card[1];
      tmp[4] = card[2];
      card[0] = tmp[0];
      card[1] = tmp[1];
      card[2] = tmp[2];
      card[3] = tmp[3];
      card[4] = tmp[4];
      return 1;
    }
  } if(card[1].face == card[2].face && card[2].face == card[3].face) {
    tmp[0] = card[0];
    tmp[1] = card[4];
    tmp[2] = card[1];
    tmp[3] = card[2];
    tmp[4] = card[3];
    card[0] = tmp[0];
    card[1] = tmp[1];
    card[2] = tmp[2];
    card[3] = tmp[3];
    card[4] = tmp[4];
  return 1;
  } if(card[2].face == card[3].face && card[3].face == card[4].face) {
      if(card[0].face == card[1].face){
        return 2;
      } else {
        return 1;
      }
  } 
  return 0;
}

int isTwoPair(game_cards *card) {
  game_cards tmp[5];
  selectionSort(&*card, 5);
  if(card[0].face == card[1].face && card[2].face == card[3].face) {
    tmp[0] = card[4];
    tmp[1] = card[0];
    tmp[2] = card[1];
    tmp[3] = card[2];
    tmp[4] = card[3];
    card[0] = tmp[0];
    card[1] = tmp[1];
    card[2] = tmp[2];
    card[3] = tmp[3];
    card[4] = tmp[4];
    return 1;
  } else if (card[0].face == card[1].face && card[4].face == card[3].face) {
    tmp[0] = card[2];
    tmp[1] = card[0];
    tmp[2] = card[1];
    tmp[3] = card[3];
    tmp[4] = card[4];
    card[0] = tmp[0];
    card[1] = tmp[1];
    card[2] = tmp[2];
    card[3] = tmp[3];
    card[4] = tmp[4];
    return 1;
  }
  return 0;
}

int isPair(game_cards *card) {
  selectionSort(&*card, 5);
  game_cards tmp[5];
  if(card[0].face == card[1].face) {
    tmp[0] = card[2];
    tmp[1] = card[3];
    tmp[2] = card[4];
    tmp[3] = card[0];
    tmp[4] = card[1];
    card[0] = tmp[0];
    card[1] = tmp[1];
    card[2] = tmp[2];
    card[3] = tmp[3];
    card[4] = tmp[4];
    return 1;
  } else if (card[1].face == card[2].face) {
    tmp[0] = card[0];
    tmp[1] = card[3];
    tmp[2] = card[4];
    tmp[3] = card[1];
    tmp[4] = card[2];
    card[0] = tmp[0];
    card[1] = tmp[1];
    card[2] = tmp[2];
    card[3] = tmp[3];
    card[4] = tmp[4];
    return 1;
  } else if (card[2].face == card[3].face) {
    tmp[0] = card[0];
    tmp[1] = card[1];
    tmp[2] = card[4];
    tmp[3] = card[2];
    tmp[4] = card[3];
    card[0] = tmp[0];
    card[1] = tmp[1];
    card[2] = tmp[2];
    card[3] = tmp[3];
    card[4] = tmp[4];
    return 1;
  } else if (card[3].face == card[4].face) {
    tmp[0] = card[0];
    tmp[1] = card[1];
    tmp[2] = card[2];
    tmp[3] = card[3];
    tmp[4] = card[4];
    card[0] = tmp[0];
    card[1] = tmp[1];
    card[2] = tmp[2];
    card[3] = tmp[3];
    card[4] = tmp[4];
    return 1;
  }
  return 0;
}

int isFourkind(game_cards *card) {
  selectionSort(&*card, 5);
  if (card[0].face == card[1].face &&
      card[1].face == card[2].face &&
      card[2].face == card[3].face) {
    return 1;
  }
  if (card[1].face == card[2].face && 
      card[2].face == card[3].face && 
      card[3].face == card[4].face) {
    return 1;
  } 
  return 0;
}

int isStraightF(game_cards *card) {
  if(isStraight(&*card) && isFlush(&*card)) {
    return 1;
  } else {
    return 0;
  } 
}

int isHighCard(game_cards *card) {
  selectionSort(&*card, 5);
  return 1;
}

int getScore(game_cards *card)
{
  if (isStraightF(&*card)) {
      return 9;
  } else if (isFourkind(&*card)) {
      return 8;
  } else if (isThreeKind(&*card) == 2) {
      return 7;
  } else if (isFlush(&*card)) {
      selectionSort(&*card, 5);
      return 6;
  } else if (isStraight(&*card)) {
      selectionSort(&*card, 5);
      return 5;
  } else if (isThreeKind(&*card) == 1) {
      return 4;
  } else if (isTwoPair(&*card)) {
      return 3;
  } else if (isPair(&*card)) {
      return 2;
  } else if (isHighCard(&*card)) {
      return 1;
  }
  return 0;
}

int main() {
  game_cards card1[5];
  game_cards card2[5];
  game_cards sorted_card[5];
  char *idx2cardtemp;
  int i,j,k;

  /*input hand 1*/
  for(i = 0; i < 5; i++) {
      if (i == 4) {
      scanf("%c%c\n\r",&card1[i].suit,&card1[i].face);
      } else {
      scanf("%c%c ",&card1[i].suit,&card1[i].face);
      }
      card1[i].face_rank=get_rank(face_rank_asc,card1[i].face);
      card1[i].suit_rank=get_rank(suit_rank_asc,card1[i].suit);
      card1[i].idx=card_idx(card1[i].suit,card1[i].face);
  }
  int card1_score = getScore(card1);

  /*input hand 2*/
  for(i = 0; i < 5; i++) {
      if (i == 4) {
      scanf("%c%c",&card2[i].suit,&card2[i].face);
      } else {
      scanf("%c%c ",&card2[i].suit,&card2[i].face);
      }
      card2[i].face_rank=get_rank(face_rank_asc,card2[i].face);
      card2[i].suit_rank=get_rank(suit_rank_asc,card2[i].suit);
      card2[i].idx=card_idx(card2[i].suit,card2[i].face);
  }
  int card2_score = getScore(card2);

  /*output*/
  for (i = 0; i < 5; i++){
    if (card1[i].face == 'T') {
      if (i == 4) {
        printf("%c10",card1[i].suit);
      } else {
        printf("%c10 ",card1[i].suit);
      }
    } else {
      if(i == 4) {
        printf("%c%c",card1[i].suit,card1[i].face);
      } else {
        printf("%c%c ",card1[i].suit,card1[i].face);
      }
    }
  }

  /*compare for same*/
  if (card1_score == card2_score) {
    if (card1[4].idx > card2[4].idx) {
      printf(" > ");
    } else if (card1[4].idx < card2[4].idx) {
      printf(" < ");
    } else {
      printf(" == ");
    }
  } else if (card1_score > card2_score) {
      printf(" > ");
  } else if (card1_score < card2_score) {
      printf(" < ");
  }
  
  for (int i = 0; i < 5; i++) {
    if (card2[i].face == 'T') {
      if (i == 4) {
        printf("%c10",card2[i].suit);
      } else {
        printf("%c10 ",card2[i].suit);
      }
    } else {
      if(i == 4) {
        printf("%c%c",card2[i].suit,card2[i].face);
      } else {
        printf("%c%c ",card2[i].suit,card2[i].face);
      }
    }
  }
}