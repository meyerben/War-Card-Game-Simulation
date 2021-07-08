#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// get the size of an array
#define NELEMS(x)  (sizeof(x) / sizeof(x[0]))
#define DECKSIZE 52

//neatly print out an array of things
#define print_type(count, stmt) \
	    do { \
		        printf("["); \
		        for (size_t i = 0; i < (count); ++i) { \
				        stmt; \
				    } \
		        printf("]\n"); \
		        } while (0)

/*
Values can be 1-13
1=Aces
2-10 = 2-10
11 = Jacks
12 = Queens
13 = Kings
Suits can be c,d,h,or s
c = clubs
d = diamonds
h = hearts
s = spades
*/
struct Card {
	int value;
	char suit;
	struct Card* next;
};

//function definitions
static void populate_deck(struct Card* my_deck);
static void shuffle(void *array, size_t n, size_t size);
//these represent the 4 possible suits
char* suits = "cdhs";


// ======================================================


// 					MAIN

					
// ======================================================
int main(){
	//create a deck of cards
	struct Card deck[DECKSIZE];
	populate_deck(deck);
	
	//print_type(NELEMS(deck), printf("{%d %c},", deck[i].value, deck[i].suit));
	shuffle(deck,NELEMS(deck),sizeof(deck[0]));
	printf("Shuffled Deck:\n");
	print_type(NELEMS(deck), printf("{%d %c},", deck[i].value, deck[i].suit));

	//create 2 hands for 2 players
	struct Card alice_hand[DECKSIZE];
	struct Card bob_hand[DECKSIZE];
	
	//deal deck into 2 hands
	int i,a,b;
	a = 0;
	b = 0;
	for(i=0;i<DECKSIZE;i++){
		if(i%2 == 0){ //deal odd cards to alice
			alice_hand[a] = deck[i];
			a++;
		}
		else{ //deal even cards to bob
			bob_hand[b] = deck[i];
			b++;
		}
	}

	printf("Alice:\n");
	print_type(NELEMS(alice_hand)/2, printf("{%d %c},", alice_hand[i].value, alice_hand[i].suit));
	printf("Bob:\n");
	print_type(NELEMS(bob_hand)/2, printf("{%d %c},", bob_hand[i].value, bob_hand[i].suit));
	return(0);
}

/*
simply creates a deck of cards. I was too lazy to create an array of cards by hand
*/
static void populate_deck(struct Card* my_deck){
	char curr_suit;
	int i,j, total;
	for(i = 0;i < strlen(suits);i++){ //for each of the 4 suits
		curr_suit = suits[i]; //set the current suit
		for(j = 0;j<13;j++){ //for each of the 13 possible values
			total++;
			struct Card card; //create a new card
			card.value = j+1; //give it a value
			card.suit = curr_suit; //give it a suit
			my_deck[j + (13*i)] = card; //add it to the deck
			// printf("%d\n",my_deck[j + (13*i)].value); *DEBUG LINE*
		}
	}
	
}

/*
take an array 
count of the array (n)
and size of each item in array
*/
static void shuffle(void *array, size_t n, size_t size) {
	char tmp[size]; //create temporary array of same size
	char *arr = array; 
	size_t stride = size * sizeof(char);
        if (n > 1) {
		size_t i;
		for (i = 0; i < n - 1; ++i) {
			size_t rnd = (size_t) rand();
			size_t j = i + rnd / (RAND_MAX / (n - i) + 1);
			memcpy(tmp, arr + j * stride, size);
			memcpy(arr + j * stride, arr + i * stride, size);
			memcpy(arr + i * stride, tmp, size);
		}
	}
}