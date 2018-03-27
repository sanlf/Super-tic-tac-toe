
void play()
{
    if(currboard == nullptr){
        //choice board as a human or as ia
        currboard = chosenboard;
    {

    //chooses and puts a piece in a cell
    putPiece(turn.piece, currboard, position);
    updateWinner();
    
    //update winner
    if(winner != NONE){
        endgame();
    }else{
        if(bboard[position].winner == NONE)
            currboard = bboard[position];
        else
            currboard = nullptr;

        //puts last play in stack
        plays.push(turn.piece, currboard, position);

        //change turn
        turn = turn == p1? p2 : p1;
    }
}

