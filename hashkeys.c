#include "defs.h"

U64 generatePositionKey(const S_BOARD *pos){
    
    // cicle param initialization
    int sq =0;
    int piece = EMPTY;

    // result initialization
    U64 finalKeay = 0;

    // summ of each chessman position hash as final hash
    for (sq = 0; sq < BRD_SQ_NUM; ++sq){
        piece = pos->pieces[sq];
        if (piece != NO_SQ && piece!=EMPTY){
            ASSERT( piece>=wP && piece<=bK );
            finalKeay ^= PieceKeys[piece][sq];
        }
    }

    // summ the side
    if (pos->side == WHITE)
        finalKeay ^= SideKey;

    // summ the enPas
    if (pos->enPas != NO_SQ){
        ASSERT(pos->enPas>=0 && pos->enPas<BRD_SQ_NUM);
        finalKeay ^= PieceKeys[EMPTY][pos->enPas];
    }

    ASSERT(pos->castlePerm>=0 && pos->castlePerm<=15);
    finalKeay ^= CastleKeys[pos->castlePerm];

    return finalKeay;
    
} 