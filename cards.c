#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

/* handy typedefs */
typedef unsigned char card;
typedef unsigned char pairs;



/* arrays for the names of things */
static char *suits[] = {"Hearts","Diamonds","Clubs","Spades"};
static char *values[]= {"Ace","Two","Three","Four","Five","Six",\
	"Seven","Eight","Nine","Ten","Jack",\
	"Queen","King"};
static char *colours[]= {"Black","Red"};

/* function prototypes */
void printcard(card c); /* Displays the value of a card*/

void printdeck(card deck[52]); /* prints an entire deck of cards*/

void filldeck(card deck[52]); /* Populates a deck of cards */

void shuffle(card deck[52]); /* Randomizes the order of cards */

int compareface(const void* c1,const void *c2); 


/* compares the face value of 2 cards, suitable to pass to qsort
as the fourth argument */

pairs findpairs(card *hand); /* finds any pairs in a hand */

int testHighest(int pairValue, pairs highest); //find highest pair value

int main()
{
	printf("Rachel's Code \n");
	
	card deck[52],*deckp;
	card hands[5][5];
	pairs numpairs[5],highest;
	int hand,cd,winner,tmp=0;

	srand(time(NULL));       /* seed the random number generator */

	
	/*populate and shuffle the deck */
	filldeck(deck);
	printdeck(deck);
	shuffle(deck);
	printdeck(deck);

	for(cd=0;cd<5;cd++)
	{
		for(hand=0;hand<5;hand++)
		{
			/* deal the hands here */
			
			hands[hand][cd] = deck[tmp];

			tmp++;
			
		}
	}

	for(hand=0;hand<5;hand++)
	{
		/* sort the hands here */
		qsort(hands[hand], 5, sizeof(card), compareface);
		
		
		
		/* print the hands here */
		printf("Hand %i \n",hand+1);
		for(int cardhand=0;cardhand<5;cardhand++){
			printf("Hand list: ");
			printcard(hands[hand][cardhand]);
		}
		/* print the number and value of any pairs here */
		numpairs[hand]=findpairs(hands[hand]);
		printf("Pairs in hand %i: %i. \n",hand+1, numpairs[hand]);
	}

	/* determine the winner and print it */
	printf("Winner is hand %i \n",hand);
	return 0;
}

pairs findpairs(card *hand)
{
	pairs numpairs=0;  
	pairs highest=0;
	

	int pairValue = 0;
	/* find the pairs here */ 
	for(int i=0;i<4;i++){
		/*Debugging code
		printf("Findpairs check: ");
		printcard(hand[i]);*/
		if (compareface(&hand[i],&hand[i+1]) == 0 && (compareface(&hand[i+1],&hand[i+2]) != 0)){
			//increment for each set of pairs found
			numpairs++;
			highest = testHighest((hand[i] >> 2) & 15,highest);
		};
	}
	//printf("how many pairs? %i \n",x);
 
	//arrange using bitwise functions
	numpairs = (numpairs << 0) & 15; //moves ZERO to the left
	
	 //printf("Code is %d%d%d%d. ", (numpairs>>3)&15,(numpairs>>2)&15,(numpairs>>1)&15,numpairs&15);
	 if (numpairs >= 1){
	 printf("Highest value: %s \n", values[highest]);
	 }
	return numpairs; 
}

int testHighest(int faceValue, pairs highest){

if (faceValue > highest){
	highest = faceValue;
}

return highest;

}

card makecard (int suit, int faceValue)
{

	card cardFace = 0;
	cardFace |= (faceValue << 2)  & 60; //moves 2 to the left
	cardFace |= (suit << 0) & 3; //moves ZERO to the left
	cardFace |= ((suit & 2) << 5) ^64; //set colour
	/* arrange everything using bitwise functions */
	
	
	return cardFace;
}

void filldeck(card deck[52])
{
	/* populate the deck here */
	int i=0,suit=0,faceValue=0;
	for(suit=0;suit<4;suit++){  
		//printf("suit %d ",suit);
		for(faceValue=0;faceValue<13;faceValue++){
			deck[i]=makecard(suit, faceValue);
			//printf("value %d ",faceValue);
			i++;
		}
	}
	return;
}

void printdeck(card deck[52])
{
	int i;
	for(i=0;i<52;i++){
		
		printcard(deck[i]);
	}
	return;
}

void printcard(card c)
{
	/* print the value of the card here */
	int value = (c >> 2) & 15;
	int suit = c & 3;
	int colour = c >> 6 & 1;
	printf("This card is the %s of %s. Colour is %s. Code is %d%d%d%d%d%d%d%d. \n",values[value],suits[suit], colours[colour], (c>>7)&1,(c>>6)&1,(c>>5)&1,(c>>4)&1,(c>>3)&1,(c>>2)&1,(c>>1)&1,c&1);
	return;
}

void swap(card *rnd, card *i){
	int temp = *rnd;
	*rnd = *i;
	*i = temp;
	return;
}
void shuffle(card deck[52])
{
	int i,rnd;
	card c;

	for(i=0;i<52;i++)
	{
		/* generate a random number between 0 & 51 */
		rnd=rand() * 52.0 / RAND_MAX; 
		
		/* swap card at random index with next card */
		
		swap(&deck[rnd],&deck[i]);
		/* debugging code to check swapping function 
		printf("swapping %d and %d", rnd, i);*/
	}
	printf("shuffled \n");
	return;
}


int compareface(const void* c1, const void *c2)
{
	/* This function extracts the two cards face values
	and returns 1 if cd1 > cd2, 0 if cd1 == cd2, and
	-1 otherwise. The weird argument types are for
	compatibility with qsort(), the first two lines
	decode the arguments back into "card".
	*/
	card cd1,cd2;
	
	cd1=*((card*) c1);
	cd2=*((card*) c2);
	
	int cdFace1 = (cd1 >> 2) & 15;
	int cdFace2 = (cd2 >> 2) & 15;
	/*/debugging code
	printf("comparing: \n \t");
	
	printcard(cd1);printf("\t");
	printf("%i",cdFace1);
	printf("\n");
	printcard(cd2);
	printf("\t");
	printf("%i",cdFace2);
	*/
	
	if(cdFace1>cdFace2){
		//printf("greater than");
		return 1;};
	if(cdFace1==cdFace2){
		/*store value of pair*/
		pairs pair = (cd1 << 2)  & 60; //moves 2 to the left
		
		return 0;}
	//printf("less than");	
	return -1;
}