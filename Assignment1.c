#include<string.h>
#include<stdio.h>
#include<stdlib.h>

typedef struct {
  char suit;
  char face;
  int suit_rank;
  int face_rank;
  int idx;
} game_cards;

const char face_rank_asc[]={'2','3','4','5','6','7','8','9','T','J','Q','K','A'};
const char suit_rank_asc[]={'C','D','H','S'};

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

int card2idx(char suit, char face) {
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
  if (card[1].suit == card[2].suit && 
      card[1].suit == card[3].suit && 
      card[1].suit == card[4].suit) {
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

int isThreeKind(game_cards card[]) {
  game_cards tmp[5];
  selectionSort(&*card, 5);
  if (card[0].face == card[1].face && card[1].face == card[2].face) {
    if(card[3].face==card[4].face) {
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
  }
  if(card[1].face == card[2].face && card[2].face == card[3].face) {
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
  }
  if(card[2].face == card[3].face && card[3].face == card[4].face) {
    if(card[0].face==card[1].face ){
      return 2;
    } else {
      return 1;
    }
  }
  return 0;
}

int isTwoPair(game_cards *sorted_card) {
  int pairCount;
  pairCount = 0;
  int i;

  for (i = 0; i < 5; i++) {
    if (sorted_card[i].face == sorted_card[i+1].face) {
        pairCount++;
        i=i+1;
    }
  }
  if (pairCount == 2) {
    return 1;
  } else {
    return 0;
  }
}

int isPair(game_cards *sorted_card) {
  int pairCount;
  pairCount=0;
  int i;

  for (i = 0; i < 5; i++) {
    if (sorted_card[i].face == sorted_card[i+1].face) {
      pairCount++;
      i = i + 1;
    }
  }
  if (pairCount == 1) {
    return 1;
  } else {
    return 0;
  }
}

int isHighCard(game_cards *card) {
  selectionSort(&*card, 5);
  return 1;
}

int main() {
game_cards card[5];
game_cards sorted_card[5];
char *idx2cardtemp;
int i,j,k;

  /*input*/
  for(i = 0; i < 5; i++){
    if (i == 4) {
      scanf("%c%c",&card[i].suit,&card[i].face);
    } else {
      scanf("%c%c ",&card[i].suit,&card[i].face);
    }
    card[i].face_rank=get_rank(face_rank_asc,card[i].face);
    card[i].suit_rank=get_rank(suit_rank_asc,card[i].suit);
    card[i].idx=card2idx(card[i].suit,card[i].face);
  }

  /*STRAIGHT FLUSH*/
  if (isStraightF(&*card)) { 
    selectionSort(&*card, 5);
    printf("%c%c-straight flush\n", card[4].suit, card[4].face);
    
    for(i = 0;  i < 5; i++){
      if(card[i].face == 'T'){
        if(i == 4) {
          printf("%c10",card[i].suit);
        } else {
          printf("%c10 ",card[i].suit);
        }
      } else {
        if(i == 4) {
          printf("%c%c",card[i].suit,card[i].face);
        } else {
          printf("%c%c ",card[i].suit,card[i].face);
        }
      }
    } 
    return 0;
  }
  
  /*FOUR OF A KIND*/
  if (isFourkind(&*card)) { 
    printf("%c-four of a kind\n",card[2].face);

    int temp,temp1;
    temp = card[4].suit;
    temp1 = card[4].face;

    for(i = 4; i > 0; i--) {
      card[i].suit = card[i-1].suit;
      card[i].face = card[i-1].face;
    }
    card[0].suit = temp;
    card[0].face = temp1;
    for(i = 0; i < 5; i++) {
      if(card[i].face == 'T') {
        if(i == 4) {
          printf("%c10",card[i].suit);
        } else {
          printf("%c10 ",card[i].suit);
        }
      } else {
        if(i == 4){
          printf("%c%c",card[i].suit,card[i].face);
        } else {
          printf("%c%c ",card[i].suit,card[i].face);
        }
      }
    } 
    return 0;
  }

  /*FULL HOUSE*/
  if (isThreeKind(&*card) == 2) { 
    printf("%c-full house\n",card[4].face);
    for(i = 0; i < 5; i++){
      if (card[i].face == 'T') {
        if (i == 4) {
          printf("%c10",card[i].suit);
        } else {
          printf("%c10 ",card[i].suit);
        }
      } else {
        if(i == 4) {
          printf("%c%c",card[i].suit,card[i].face);
        } else {
          printf("%c%c ",card[i].suit,card[i].face);
        }
      }
    } 
    return 0;
  }

  /*FLUSH*/
  if (isFlush(&*card) && !isStraight(&*card)) { 
    selectionSort(&*card, 5);
    printf("%c%c-flush\n",card[4].suit, card[4].face);
    for (i = 0; i < 5; i++) {
      if (card[i].face == 'T') {
        if (i == 4) {
          printf("%c10",card[i].suit);
        } else {
          printf("%c10 ",card[i].suit);
        }
      } else {
        if(i == 4) {
          printf("%c%c",card[i].suit,card[i].face);
        } else {
          printf("%c%c ",card[i].suit,card[i].face);
        }
      }
    } 
    return 0;
  }

  /*STRAIGHT*/
  if (isStraight(&*card) && !isFlush(&*card)) { 
    selectionSort(&*card, 5);
    printf("%c%c-straight\n",card[4].suit, card[4].face);
    for (i = 0; i < 5; i++) {
      if (card[i].face == 'T') {
        if (i == 4) {
          printf("%c10",card[i].suit);
        } else {
          printf("%c10 ",card[i].suit);
        }
      } else {
        if(i == 4) {
          printf("%c%c",card[i].suit,card[i].face);
        } else {
          printf("%c%c ",card[i].suit,card[i].face);
        }
      }
    } 
    return 0;
  }
  
  /*THREE OF A KIND*/
  if (isThreeKind(&*card) == 1) { 
    printf("%c-three of a kind\n",card[4].face);
    for(i = 0; i < 5; i++){
      if (card[i].face == 'T') {
        if (i == 4) {
          printf("%c10",card[i].suit);
        } else {
          printf("%c10 ",card[i].suit);
        }
      } else {
        if(i == 4) {
          printf("%c%c",card[i].suit,card[i].face);
        } else {
          printf("%c%c ",card[i].suit,card[i].face);
        }
      }
    } 
    return 0;
  }

  /*TWO PAIR*/
  memcpy(sorted_card, card, sizeof(card));
  selectionSort(sorted_card,5);
  if (isTwoPair(sorted_card)) {
    game_cards TwoPairCard[4];
    int idx_single_card;
    idx_single_card = -1;

    /*find the single card index*/
    for(i = 0; i < 5; i++) {
      for(j = 0; j < 5; j++) {
        if (card[i].face == card[j].face && i!=j) {
          break;
        } else if (j == 4) {
            idx_single_card=i;
            break;
        }
      }
      if (idx_single_card != -1) {
        break;
      }
    }

    /*fill array with 2 pair card*/
    for(i = 0; i < 5; i++) {
      if (i != idx_single_card) {
        if (i > idx_single_card) {
          TwoPairCard[i-1]=card[i];
        } else {
          TwoPairCard[i]=card[i];
        }
      }
    }
    /*order 2 pair card*/
    selectionSort(TwoPairCard,4);
    printf("%c%c-two pairs\n%c%c ",TwoPairCard[3].suit,TwoPairCard[3].face,card[idx_single_card].suit,card[idx_single_card].face);
    for (k = 0; k < 5; k++) {
      if (card[k].face == 'T') {
        for (i = 0; i < 4; i++) {
          if (i == 3) {
            printf("%c10\n",TwoPairCard[i].suit);
          } else {
            printf("%c10 ",TwoPairCard[i].suit);
          }
        }
      } else {
        for (i = 0; i < 4; i++) {
          if (i == 3) {
            printf("%c%c\n",TwoPairCard[i].suit,TwoPairCard[i].face);
          } else {
            printf("%c%c ",TwoPairCard[i].suit,TwoPairCard[i].face);
          }
        }
      }
      break;
    } 
    return 0;
  }

  /*PAIR*/
  memcpy(sorted_card, card, sizeof(card));
  selectionSort(sorted_card,5);
  if (isPair(sorted_card)) {
      game_cards PairCard[2];
      int idx_single_card;
      idx_single_card=-1;
      /*find the single card index*/
      for (i = 0; i < 5; i++) {
        for(j = 0; j < 5; j++) {
          if (card[i].face == card[j].face && i!=j) {
            break;
          } else if (j == 4) {
            idx_single_card=i;
            break;
          }
        }
        if (idx_single_card != -1) {
          break;
        }
      }
      /*fill array with a pair card*/
      for(i = 0; i < 5; i++){
        if (i != idx_single_card) {
          if (i > idx_single_card) {
            PairCard[i-1]=card[i];
          } else {
            PairCard[i]=card[i];
          }
        }
      }
      /*order a pair card*/
      selectionSort(PairCard,3);
      printf("%c%c-pair\n%c%c ",PairCard[1].suit,PairCard[1].face,card[idx_single_card].suit,card[idx_single_card].face);
      for (k = 0; k < 5; k++) {
        if (card[k].face == 'T') {
          for(i = 0; i < 5; i++) { 
            if (i == 3 || i == 4) {
              printf("%c10 ",card[i].suit);
            }
          } 
          printf("%c10 %c10\n",PairCard[0].suit,PairCard[1].suit);
        } else {
          for(i = 0; i < 5; i++) { 
            if (i == 3 || i == 4) {
              printf("%c%c ",card[i].suit,card[i].face);
            }
          } 
          printf("%c%c %c%c\n",PairCard[0].suit,PairCard[0].face,PairCard[1].suit,PairCard[1].face);
        }
      break;
    } 
    return 0;
  }

  /*HIGH CARD*/
  else {
    selectionSort(&*card, 5);
    printf("%c%c-high card\n",card[4].suit,card[4].face);
    for(i = 0; i < 5; i++){
      if(card[i].face == 'T'){
        if(i == 4){
          printf("%c10",card[i].suit);
        } else {
          printf("%c10 ",card[i].suit);
        }
      } else {
        if(i == 4) {
          printf("%c%c",card[i].suit,card[i].face);
        } else {
          printf("%c%c ",card[i].suit,card[i].face);
        }
      }
    } 
    return 0;
  }
}