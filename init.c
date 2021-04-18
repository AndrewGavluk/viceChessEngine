// init.c

#include "defs.h"
#include "stdlib.h"

#define RAND_64 (	(U64)rand() + \
					(U64)rand() << 15 + \
					(U64)rand() << 30 + \
					(U64)rand() << 45 + \
					((U64)rand() & 0xf) << 60 )


// Array to convert Board120 to Board64
int Sq120ToSq64[BRD_SQ_NUM];
int Sq64ToSq120[64];

// SetMask is an array of masks. 1 in i position of i number in an array
// ClearMask is an array of masks. 0 in i position of i number in an array
U64 SetMask[64];
U64 ClearMask[64];

// PieceKeys is a unique key for each piece (chessman), on each square
//		[13] - is for chessmans: 0 - none, 1 - wP (white pawn), 2 - wB, ... 12 - bK
//		[120] - "extended" chessboard
// SideKey - key for white/black side to move
// Castling - 4 views of castling (wK, wQ, bK, bQ) 2^4 = 16
U64 PieceKeys[13][120];
U64 SideKey;
U64 CastleKeys[16];

void InitHashKeys(){
	int index1 = 0;
	int index2 = 0;
	
	for (; index1 < 13; ++index1)
		for (index2 = 0 ; index2 < 120 ; ++index2)
			PieceKeys[index1][index2] = RAND_64;

	SideKey = RAND_64;
	for (index1 = 0; index1 < 16; ++index1)
		CastleKeys[index1] = RAND_64;
}

void InitBitMasks(){
	u_int8_t i = 0;
	
	for (i = 0; i < 64; ++i){
		SetMask[i]= 0ULL;
		ClearMask[i] = 0ULL;
	} 

	for (i = 0; i < 64; ++i){
		SetMask[i] |= (1ULL << i) ;
		ClearMask[i] = ~SetMask[i];
	} 
}

void InitSq120To64() {

	int index = 0;
	int file = FILE_A;
	int rank = RANK_1;
	int sq = A1;
	int sq64 = 0;
	for(index = 0; index < BRD_SQ_NUM; ++index) {
		Sq120ToSq64[index] = 65;
	}
	
	for(index = 0; index < 64; ++index) {
		Sq64ToSq120[index] = 120;
	}
	
	for(rank = RANK_1; rank <= RANK_8; ++rank) {
		for(file = FILE_A; file <= FILE_H; ++file) {
			sq = FR2SQ(file,rank);
			Sq64ToSq120[sq64] = sq;
			Sq120ToSq64[sq] = sq64;
			sq64++;
		}
	}
}

void AllInit() {
	InitSq120To64();	
	InitBitMasks();
	InitHashKeys();
}
