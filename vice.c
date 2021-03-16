#include "stdio.h"
#include "defs.h"



int main() {

	AllInit();
	
	int PieceOne = rand();
	int PieceTwo = rand();
	int PieceThree = rand();
	int PieceFour = rand();

	printf("PieceOne:%X\n", PieceOne);
	printf("PieceTwo:%X\n", PieceTwo);
	printf("PieceThree:%X\n", PieceThree);
	printf("PieceFour:%X\n", PieceFour);

	int Key = PieceOne ^ PieceTwo ^ PieceThree ^ PieceFour;
	int Tempkey = PieceOne;
	Tempkey ^= PieceThree;
	Tempkey ^= PieceFour;
	Tempkey ^= PieceTwo;

	printf("Key:%X\n", Key);
	printf("Tempkey:%X\n", Tempkey);

	return 0;
}