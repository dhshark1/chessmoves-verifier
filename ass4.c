/**************************
 * Daniel Haber
 * 322230020
 * 01
 * ass04
 **************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "ass4.h"

// defining the structure move
typedef struct {
    char srcPiece, srcRow, srcCol, destPiece, destRow, destCol, promotionPiece;
    int iSrc, jSrc, iDest, jDest;
    int isWhite, isCapture, isPromotion, isCheck, isMate, isLegal;
} Move;

const char FIRST_COL = 'a';

const char EMPTY = ' ';
/****************************************
 * Function Name:printColumns
 * Input: none
 * Output: none
 * Function Operation: this function is responsible for printing all the columns of the board, such as A, B, C, D
 ***************************************/
void printColumns() {
    //printing each letter to indicate columns
    char column = toupper(FIRST_COL);
    // separator for the board
    printf("* |");
    for (int i = 0; i < SIZE; i++) {
        if (i) {
            printf(" ");
        }
        //actual printing of the letter size amount of times
        printf("%c", column);
        column++;
    }
    printf("| *\n");
}

/****************************************
 * Function Name: printSpacers
 * Input: none
 * Output: none
 * Function Operation: this function is responsible for printing the spacers in the board at the top and bottom
 ***************************************/
void printSpacers() {
    //printing the spacers to separate the columns from the board
    printf("* -");
    for (int i = 0; i < SIZE; i++) {
        //printing 2 dashes size amount of times
        printf("--");
    }
    printf(" *\n");
}

/****************************************
 * Function Name: createBoard
 * Input: char board[][SIZE], char fen[]
 * Output: none
 * Function Operation: this function is responsible for creating a 2D array that will represent the board from a fen
 string that provides all the information about the board
 ***************************************/
void createBoard(char board[][SIZE], char fen[]) {
    //initializing variables
    int i = 0, j = 0, k = 0;
    //while loop that iterates as many times as the string of fen
    while (i != strlen(fen)) {
        //if fen[i] is the separator, move to the next dimension in the list
        if (fen[i] == '/') {
            i++;
            //initialize index of the columns
            j = 0;
            k++;
            continue;
        }
        else if (isdigit(fen[i])) {
            //if fen[i] is a digit, the fill the board with digits the amount of times as the digit
            for (int x = 0; x < (fen[i] - '0'); x++) {
                board[k][j] = EMPTY;
                j++;
            }
        }
        else {
            //if board is a letter then put it into [i][j]
            board[k][j] = fen[i];
            j++;
        }
        i++;
    }
}

/****************************************
 * Function Name: printBoard
 * Input: char board[][SIZE]
 * Output: none
 * Function Operation: this function is responsible for printing the 2D array that was created by the function createBoard.
 this is done by specific format with specific columns and spacers.
 ***************************************/
void printBoard(char board[][SIZE]) {
    //calling the functions printColumns and printSpacers for format of board
    printColumns();
    printSpacers();
    for (int i = 0; i < SIZE; i++) {
        //print row numbers before printing each row
        printf("%d ", SIZE - i);
        for (int j = 0; j < SIZE; j++) {
            //print a separator and each element of the board
            printf("|%c", board[i][j]);
        }
        printf("|");
        //print row of numbers after printing each row
        printf(" %d", SIZE - i);
        printf("\n");
    }
    //calling the functions printColumns andprintSpacers for format of board
    printSpacers();
    printColumns();
}

/****************************************
 * Function Name: isPieceAt
 * Input: char board[][SIZE], int fromRow, int fromCol, int toRow, int toCol
 * Output: an integer of 1 or 0
 * Function Operation: this function is responsible for determining whether there is a piece blocking its pathway of movement.
 this is done by checking all 8 possible directions of movement for a piece.
 ***************************************/
int isPieceAt(char board[][SIZE], int fromRow, int fromCol, int toRow, int toCol) {
    int i;
    //checking movement path if piece is going vertical north
    if (fromCol == toCol && fromRow > toRow) {
        for (i = fromRow - 1; i >= toRow +1; i--) {
            //if the board at that specific point is not empty, then piece cannot complete movement
            if (board[i][fromCol] != EMPTY)
                return 0;
        }
    }
    //checking movement path if piece is going horizontal east
    else if (fromCol < toCol && fromRow == toRow) {
        for (i = fromCol + 1; i <= toCol - 1; i++) {
            //if the board at that specific point is not empty, then piece cannot complete movement
            if (board[fromRow][i] != EMPTY)
                return 0;
        }
    }
    //checking movement path if piece is going vertical south
    else if (fromCol == toCol && fromRow < toRow) {
        for (i = fromRow + 1; i <= toRow - 1; i++) {
            //if the board at that specific point is not empty, then piece cannot complete movement
            if (board[i][fromCol] != EMPTY)
                return 0;
        }
    }
    //checking movement path if piece is going horizontal west
    else if (fromCol > toCol&& fromRow == toRow) {
        for (i = fromCol - 1; i >= toCol + 1; i--) {
            //if the board at that specific point is not empty, then piece cannot complete movement
            if (board[fromRow][i] != EMPTY)
                return 0;
        }
    }
    //checking movement path if piece is going north-east
    else if (fromCol < toCol && fromRow > toRow) {
        for (i = 1; i < toCol - fromCol; i++) {
            //if the board at that specific point is not empty, then piece cannot complete movement
            if (board[fromRow - i][fromCol + i] != EMPTY)
                return 0;
        }
    }
    //checking movement path if piece is going south-east
    else if (fromCol < toCol&& fromRow < toRow) {
        for (i = 1; i < toCol - fromCol; i++) {
            //if the board at that specific point is not empty, then piece cannot complete movement
            if (board[fromRow + i][fromCol + i] != EMPTY)
                return 0;
        }
    }
    //checking movement path if piece is going south-west
    else if (fromCol > toCol&& fromRow < toRow) {
        for (i = 1; i < fromCol - toCol;i++) {
            //if the board at that specific point is not empty, then piece cannot complete movement
            if (board[fromRow + i][fromCol - i] != EMPTY)
                return 0;
        }
    }
    //checking movement path if piece is going south-east
    else if (fromCol > toCol&& fromRow > toRow) {
        for (i = 1; i < fromCol - toCol;i++) {
            //if the board at that specific point is not empty, then piece cannot complete movement
            if (board[fromRow - i][fromCol - i] != EMPTY)
                return 0;
        }
    }
    //if none of the movements have indicated of an invalid path, then return 1
    return 1;
}

/****************************************
 * Function Name: validRookMove
 * Input: char board[][SIZE], int fromRow, int fromCol, int toRow, int toCol
 * Output: an integer of 1 or 0
 * Function Operation: this function is responsible for determining if a rook's move is valid using only horizontal or
 vertical movements, like in the rules of chess. if the move is invalid, return 0.
 ***************************************/
int validRookMove(char board[][SIZE], int fromRow, int fromCol, int toRow, int toCol) {
    //if the move is horizontal, check if it is valid
    if (fromRow == toRow) {
        if (!isPieceAt(board, fromRow, fromCol, toRow, toCol)) {
            return 0;
        }
    }
    //if the move is vertical, check if it is valid
    else if (fromCol == toCol) {
        if (!isPieceAt(board, fromRow, fromCol, toRow, toCol)) {
            return 0;
        }
    }
    //if it is not a horizontal or vertical move, return 0
    else {
        return 0;
    }

    return 1;
}

/****************************************
 * Function Name: validBishopMove
 * Input: char board[][SIZE], int fromRow, int fromCol, int toRow, int toCol
 * Output: an integer of 1 or 0
 * Function Operation: this function is responsible for determining if a bishop's move is valid using only diagonal
 movements, like in the rules of chess. if the move is invalid, return 0.
 ***************************************/
int validBishopMove(char board[][SIZE], int fromRow, int fromCol, int toRow, int toCol) {
    //check if the movement is diagonal by checking if the subtraction of row and columns is the same in abs value
    if (abs(fromRow - toRow) == abs(fromCol - toCol)) {
        //check if path is free
        if (isPieceAt(board, fromRow, fromCol, toRow, toCol))
            return 1;
    }
    return 0;
}

/****************************************
 * Function Name: isBlackPiece
 * Input: char board[][SIZE], int toRow, int toCol
 * Output: an integer of 1 or 0
 * Function Operation: this function is responsible for determining if there is a black piece at the destination point
 in the board. if there is, return 1. otherwise, return 0.
 ***************************************/
int isBlackPiece(char board[][SIZE], int toRow, int toCol) {
    //check if there is a black piece at destination point
    if (islower(board[toRow][toCol])) {
        return 1;
    }
    return 0;
}

/****************************************
 * Function Name: isWhitePiece
 * Input: char board[][SIZE], int toRow, int toCol
 * Output: an integer of 1 or 0
 * Function Operation: this function is responsible for determining if there is a white piece at the destination point
 in the board. if there is, return 1. otherwise, return 0.
 ***************************************/
int isWhitePiece(char board[][SIZE], int toRow, int toCol) {
    //check if there is a white piece at destination point
    if (isupper(board[toRow][toCol])) {
        return 1;
    }
    return 0;
}

/****************************************
 * Function Name: validWhitePawn
 * Input: char board[][SIZE], int fromRow, int fromCol, int toRow, int toCol
 * Output: an integer of 1 or 0
 * Function Operation: this function is responsible for determining if a white pawn's move is valid according to the
 rules of chess. if yes return 1, otherwise return 0. this function also checks the valid move of a pawn in the act of capturing.
 ***************************************/
int validWhitePawn(char board[][SIZE], int fromRow, int fromCol, int toRow, int toCol) {
    //check if a movement of squares forward is valid
    if ((board[toRow][toCol] == EMPTY) && (board[toRow + 1][toCol] == EMPTY) && (toCol == fromCol) && (fromRow == SIZE - 2) && ((toRow == fromRow - 2)))
        return 1;
    //check if regular movement of pawn is valid- 1 square forward
    else if ((board[toRow][toCol] == EMPTY) && (toCol == fromCol) && ((toRow == fromRow - 1)))
        return 1;
    //movement of pawn during capture, check if valid
    else if (fromRow - 1 == toRow && (fromCol == toCol - 1 || fromCol == toCol + 1))
        return isBlackPiece(board, toRow, toCol);
    return 0;
}

/****************************************
 * Function Name: validBlackPawn
 * Input: char board[][SIZE], int fromRow, int fromCol, int toRow, int toCol
 * Output: an integer of 1 or 0
 * Function Operation: this function is responsible for determining if a black pawn's move is valid according to the
 rules of chess. if yes return 1, otherwise return 0. this function also checks the valid move of a pawn in the act of capturing.
 ***************************************/
int validBlackPawn(char board[][SIZE], int fromRow, int fromCol, int toRow, int toCol) {
    //check if a movement of squares forward is valid
    if ((board[toRow][toCol] == EMPTY) && (board[toRow - 1][toCol] == EMPTY) && (toCol == fromCol) && (fromRow == 1) && ((toRow == fromRow + 2)))
        return 1;
    //check if regular movement of pawn is valid- 1 square forward
    else if ((board[toRow][toCol] == EMPTY) && (toCol == fromCol) && ((toRow == fromRow + 1)))
        return 1;
    //movement of pawn during capture, check if valid
    else if (fromRow + 1 == toRow && (fromCol == toCol - 1 || fromCol == toCol + 1))
        return isWhitePiece(board, toRow, toCol);
    return 0;
}

/****************************************
 * Function Name: validKnightMove
 * Input: int fromRow, int fromCol, int toRow, int toCol
 * Output: an integer of 1 or 0
 * Function Operation: this function is responsible for determining if a knight's move is valid according to the
 rules of chess. if yes return 1, otherwise return 0.
 ***************************************/
int validKnightMove(int fromRow, int fromCol, int toRow, int toCol) {
    //checking the 8 possible ways a knight can reach its destination on the board
    if ((fromRow + 1 == toRow) && (fromCol + 2 == toCol))
        return 1;
    else if ((fromRow - 1 == toRow) && (fromCol + 2 == toCol))
        return 1;
    else if ((fromRow - 1 == toRow) && (fromCol - 2 == toCol))
        return 1;
    else if ((fromRow + 1 == toRow) && (fromCol - 2 == toCol))
        return 1;
    else if ((fromRow + 2 == toRow) && (fromCol + 1 == toCol))
        return 1;
    else if ((fromRow - 2 == toRow) && (fromCol + 1 == toCol))
        return 1;
    else if ((fromRow - 2 == toRow) && (fromCol - 1 == toCol))
        return 1;
    else if ((fromRow + 2 == toRow) && (fromCol - 1 == toCol))
        return 1;
    //if none of these moves are possible, return 0
    return 0;
}

/****************************************
 * Function Name: validKingMove
 * Input: char board[][SIZE], int fromRow, int fromCol, int toRow, int toCol
 * Output: an integer of 1 or 0
 * Function Operation: this function is responsible for determining if a king's move is valid according to the
 rules of chess. if yes return 1, otherwise return 0.
 ***************************************/
int validKingMove(char board[][SIZE], int fromRow, int fromCol, int toRow, int toCol) {
    //checking the 8 possible destinations of a king on the board
    if ((fromRow == toRow) && (fromCol + 1 == toCol))
        return 1;
    else if ((fromRow == toRow) && (fromCol - 1 == toCol))
        return 1;
    else if ((fromRow - 1 == toRow) && (fromCol == toCol))
        return 1;
    else if ((fromRow + 1 == toRow) && (fromCol == toCol))
        return 1;
    else if ((fromRow + 1 == toRow) && (fromCol + 1 == toCol))
        return 1;
    else if ((fromRow - 1 == toRow) && (fromCol - 1 == toCol))
        return 1;
    else if ((fromRow + 1 == toRow) && (fromCol - 1 == toCol))
        return 1;
    else if ((fromRow - 1 == toRow) && (fromCol + 1 == toCol))
        return 1;
    //if none of these moves happen, return 0
    return 0;
}

/****************************************
 * Function Name: validQueenMove
 * Input: char board[][SIZE], int fromRow, int fromCol, int toRow, int toCol
 * Output: an integer of 1 or 0
 * Function Operation: this function is responsible for determining if a queen's move is valid according to the
 rules of chess. this is done by applying the movement functions of the bishop and rook. if yes return 1, otherwise return 0.
 ***************************************/
int validQueenMove(char board[][SIZE], int fromRow, int fromCol, int toRow, int toCol) {
    //call the functions of bishop and rook because the queen is a combination of those two pieces.
    //if move is valid returns 1
    return (validBishopMove(board, fromRow, fromCol, toRow, toCol) || validRookMove(board, fromRow, fromCol, toRow, toCol));
}

/****************************************
 * Function Name: isValid
 * Input: char board[][SIZE], char piece, int fromRow, int fromCol, int toRow, int toCol
 * Output: an integer of 1 or 0
 * Function Operation: this function checks overall if a move is valid according to the rules of chess. first,
 it checks whether the move is within the boundaries, and the checks if the move is valid according to what piece it
 it is. if valid return 1, otherwise return 0.
 ***************************************/
int isValid(char board[][SIZE], char piece, int fromRow, int fromCol, int toRow, int toCol) {
    //check if moves is within boundaries of board
    if (fromRow < 0 || fromRow >(SIZE - 1) || fromCol < 0 || fromCol >(SIZE - 1) ||
        toRow < 0 || toRow >(SIZE - 1) || toCol < 0 || toCol >(SIZE - 1))
        return 0;
    //check what piece we are dealing with
    //call function to check validity of move of piece
    switch (piece)
    {
        case 'P':
            return (validWhitePawn(board, fromRow, fromCol, toRow, toCol));
        case 'p':
            return (validBlackPawn(board, fromRow, fromCol, toRow, toCol));
        case 'N':
        case 'n':
            return (validKnightMove(fromRow, fromCol, toRow, toCol));
        case 'B':
        case 'b':
            return (validBishopMove(board, fromRow, fromCol, toRow, toCol));
        case 'R':
        case 'r':
            return (validRookMove(board, fromRow, fromCol, toRow, toCol));
        case 'Q':
        case 'q':
            return (validQueenMove(board, fromRow, fromCol, toRow, toCol));
        case 'K':
        case 'k':
            return (validKingMove(board, fromRow, fromCol, toRow, toCol));
        default:
            break;
    }
    //if the letter is none of the above or move is out of boundaries then return 0
    return 0;
}

/****************************************
 * Function Name: validateCapture
 * Input: char board[][SIZE], int toRow, int toCol, Move* m
 * Output: an integer of 1 or 0
 * Function Operation: this function checks whether there actually is a potential capture in the move and validates the
 struct decleration of a capture in the function validateMove.
 ***************************************/
int validateCapture(char board[][SIZE], int toRow, int toCol, Move* m) {
    //if the move is white then check if there is a black piece at the destination
    // otherwise check for white piece at destination
    if (m->isWhite)
        return isBlackPiece(board, toRow, toCol);
    else {
        return isWhitePiece(board, toRow, toCol);
    }
}

/****************************************
 * Function Name: isCheck
 * Input: char board[][SIZE], Move* m
 * Output: an integer of 1 or 0
 * Function Operation: this function checks whether there actually is a potential check against an opponent in the move
 and validates the struct decleration of a check in the function validateMove.
 ***************************************/
int isCheck(char board[][SIZE], Move* m) {
    //initializing variables for the loops
    int i, j, iK, jK;
    int x, y;
    char king_colour = 'K';
    //initializing a duplicate board
    char dummyBoard[SIZE][SIZE];
    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++){
            dummyBoard[i][j] = board[i][j];
        }
    //if a promotion was declared, check for move with promotion piece on duplicate board
    if (m->isPromotion){
        dummyBoard[m->iSrc][m->jSrc] = EMPTY;
        dummyBoard[m->iDest][m->jDest] = m->promotionPiece;
    }
    //if promotion wasn't declared, check for move with original piece on duplicate board
    else{
        if(m->iSrc != -1 && m->jSrc != -1){
            dummyBoard[m->iSrc][m->jSrc] = EMPTY;
            dummyBoard[m->iDest][m->jDest] = m->srcPiece;
        }
        else{
            return 0;
        }
    }
    //if it is a white move now, then check for check on black king
    if (m->isWhite == 1)
        king_colour = 'k';
    //for loops to locate the position of the king we are looking to check for check
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (board[i][j] == king_colour) {
                iK = i;
                jK = j;
                break;
            }
        }
    }
    //scan the duplicate board with the made move to check if there are any pieces of opposite colour threatening the king
    // if so return 1
    for (x = 0; x < SIZE; x++) {
        for (y = 0; y < SIZE; y++) {
            if (king_colour == 'K' && islower(dummyBoard[x][y]) && isValid(dummyBoard, dummyBoard[x][y], x, y, iK, jK) && !m->isWhite)
                return 1;
            else if (king_colour == 'k' && isupper(dummyBoard[x][y]) && isValid(dummyBoard, dummyBoard[x][y], x, y, iK, jK) && m->isWhite)
                return 1;
        }
    }
    return 0;
}

/****************************************
 * Function Name: isCheck
 * Input: char board[][SIZE], Move* m
 * Output: an integer of 1 or 0
 * Function Operation: this function checks whether there actually is a potential check for the self piece as a
 result of making a move. validates the struct decleration of a check in the function validateMove.
 ***************************************/
int isMeCheck(char board[][SIZE], Move* m) {
    //initializing variables for the loops
    int i, j;
    int x, y;
    char king_colour = 'k';
    //initializing a duplicate board
    char dummyBoard[SIZE][SIZE];
    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++)
            dummyBoard[i][j] = board[i][j];
    //if a promotion was declared, check for move with promotion piece on duplicate board
    if (m->isPromotion){
        dummyBoard[m->iSrc][m->jSrc] = EMPTY;
        dummyBoard[m->iDest][m->jDest] = m->promotionPiece;
    }
    //if promotion wasn't declared, check for move with original piece on duplicate board
    else{
        if(m->iSrc != -1 && m->jSrc != -1){
            dummyBoard[m->iSrc][m->jSrc] = EMPTY;
            dummyBoard[m->iDest][m->jDest] = m->srcPiece;
        }
        else{
            return 0;
        }
    }
    //if it is a black move now, then check for check on black king
    if (m->isWhite == 0)
        king_colour = 'k';
    //for loops to locate the position of the king we are looking to check for check
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (board[i][j] == king_colour) {
                break;
            }
        }
    }
    //scan the duplicate board with the made move to check if there are any pieces of opposite colour threatening the king
    // if so return 1
    for (x = 0; x < SIZE; x++) {
        for (y = 0; y < SIZE; y++) {
            if (king_colour == 'K' && islower(dummyBoard[x][y]) && isValid(dummyBoard, dummyBoard[x][y], x, y, i, j) && m->isWhite)
                return 1;
            else if (king_colour == 'k' && isupper(dummyBoard[x][y]) && isValid(dummyBoard, dummyBoard[x][y], x, y, i, j) && !m->isWhite)
                return 1;
        }
    }
    return 0;
}

/****************************************
 * Function Name: isPromotion
 * Input: Move* m, int fromRow,int toRow
 * Output: an integer of 1 or 0
 * Function Operation: this function checks whether there actually is a potential promotion in the move
 and validates the struct decleration of a check in the function validateMove.
 ***************************************/
int isPromotion(Move* m, int fromRow,int toRow) {
    //check valid promotion of white piece
    if (m->isWhite && m->srcPiece == 'P' && fromRow == 1 && toRow == 0)
        return 1;
    //check valid promotion of black piece
    if (!m->isWhite && m->srcPiece == 'p' && fromRow == SIZE - 2 && toRow == SIZE - 1)
        return 1;
    return 0;
}

/****************************************
 * Function Name: pgnAnalysis
 * Input: char pgn[], char board[][SIZE], int isWhiteTurn, Move* m
 * Output: an integer of 1 or 0
 * Function Operation: this function break down the pgn string and stores all of the information provided from it in
 the struct. then, using the struct, we perform the checks whether the move is valid.
 ***************************************/
int pgnAnalysis(char pgn[], char board[][SIZE], int isWhiteTurn, Move* m) {
    int x, y;
    //if it is a white turn, the scan for which piece is being played
    if (isWhiteTurn) {
        switch (pgn[0])
        {
            case 'K':
                m->srcPiece = 'K';
                break;
            case 'N':
                m->srcPiece = 'N';
                break;
            case 'R':
                m->srcPiece = 'R';
                break;
            case 'Q':
                m->srcPiece = 'Q';
                break;
            case 'B':
                m->srcPiece = 'B';
                break;
            default:
                m->srcPiece = 'P';
                break;
        }
    }
    //if it is a black piece then check for which piece is being played
    else {
        switch (pgn[0])
        {
            case 'K':
                m->srcPiece = 'k';
                break;
            case 'N':
                m->srcPiece = 'n';
                break;
            case 'R':
                m->srcPiece = 'r';
                break;
            case 'Q':
                m->srcPiece = 'q';
                break;
            case 'B':
                m->srcPiece = 'b';
                break;
            default:
                m->srcPiece = 'p';
                break;
        }
    }
    //initializing i to the length of pgn minus 1
    int i = strlen(pgn) - 1;
    //while loop that scans information from the pgn from the end
    //do not scan for first character unless it is a pawn
    while (i >= 1 || (m->srcPiece == 'p' && i >= 0) || (m->srcPiece == 'P' && i >= 0)) {
        //if pgn[i] is a digit and destination row is not initialized yet
        if (isdigit((pgn[i])) && m->iDest == -1) {
            m->iDest = -(pgn[i] - '0' - SIZE);
        }
        //if pgn[i] is a digit and destination is initialized, then initialize the source row
        else if (isdigit((pgn[i])) && m->iDest != -1) {
            m->iSrc += 1;
            m->iSrc = pgn[i] - '0';
        }
        //if pgn[i] is a letter, which is not x, and destination column is not initialized yet
        else if (!isdigit((pgn[i])) && m->jDest == -1 && isalpha(pgn[i]) && pgn[i] != 'x' && (islower(pgn[i]))) {
            m->jDest += 1;
            m->jDest = pgn[i] - 'a';
        }
        //if pgn[i] is a letter, which is not x, and destination column is initialized then initialize source column
        else if (!isdigit((pgn[i])) && m->jDest != -1 && isalpha(pgn[i]) && pgn[i] != 'x' && (islower(pgn[i]))) {
            m->jSrc += 1;
            m->jSrc = pgn[i] - 'a';
        }
        //check if check is declared
        if (pgn[i] == '+' || pgn[i] == '#')
            m->isCheck = 1;
        //check if promotion is declared
        if (pgn[i] == '=') {
            m->isPromotion = 1;
            m->promotionPiece = pgn[i+1];
            //if black move then make sure promotion piece is in lower case
            if (m->isWhite == 0)
                m->promotionPiece= tolower(m->promotionPiece);

        }
        //check if capture is declared
        if (pgn[i] == 'x')
            m->isCapture = 1;
        i--;
    }
    //if source row and column have no been declared yet
    if (m->iSrc == -1 && m->jSrc == -1) {
        //scan the whole board for the specific source piece
        //if source piece is found, then check if it can move to destination with valid move
        //if yes, then assign to source row and column
        for (x = 0; x < SIZE; x++) {
            for (y = 0; y < SIZE; y++) {
                if (board[x][y] == m->srcPiece) {
                    if ((isValid(board, m->srcPiece, x, y, m->iDest, m->jDest))) {
                        m->iSrc = x;
                        m->jSrc = y;
                        return 1;
                    }
                }
            }
        }
    }
    //if source column was initialized and source row was not
    else if (m->iSrc == -1 && m->jSrc != -1) {
        //scan the row for potential column where there could be a valid move
        //if there is, assign the row value
        for (x = 0; x < SIZE; x++) {
            if (board[x][m->jSrc] == m->srcPiece) {
                if (isValid(board, m->srcPiece, x, m->jSrc, m->iDest, m->jDest)) {
                    m->iSrc = x;
                    return 1;
                }
            }
        }
    }
    //if source column was not initialized and source row was initialized
    else if (m->iSrc != -1 && m->jSrc == -1) {
        //scan column in the row where there could be a valid move
        //if yes, assign the column value
        for (x = 0; x < SIZE; x++) {
            if (board[m->iSrc][x] == m->srcPiece) {
                if (isValid(board, m->srcPiece, m->iSrc, x, m->iDest, m->jDest)) {
                    m->iSrc = x;
                    return 1;
                }
            }
        }
    }
    return 0;
}

/****************************************
 * Function Name: validateMove
 * Input: Move* m, char board[][SIZE], int fromRow, int fromCol, int toRow, int toCol
 * Output: an integer of 1 or 0
 * Function Operation: this function validates every check with what has been declared by the pgn string and stored in
 the struct. all checks must match each other and not cause an inequality in order for the move to be validated.
 this is the final check before a move is performed. if valid, return 1, otherwise return 0.
 ***************************************/
int validateMove(Move* m, char board[][SIZE], int fromRow, int fromCol, int toRow, int toCol) {
    //if capture was declared but the capture is not valid and vice versa
    if (m->isCapture != validateCapture(board, toRow, toCol, m))
        return 0;
    //if check was declared but check is not valid and vice versa
    if (m->isCheck != isCheck(board, m))
        return 0;
    //check if promotion was declared and is not valid and vice versa
    if (m->isPromotion != isPromotion(m, fromRow, toRow))
        return 0;
    //check if move is not valid according to rules of chess
    if (m->isLegal != isValid(board, m->srcPiece, fromRow, fromCol, toRow, toCol))
        return 0;
    //check if there is a white move and black piece at destination, and capture wasn't declared
    if (isBlackPiece(board, toRow, toCol) && m->isWhite && (m->isCapture == 0))
        return 0;
    //check if there is a black move and white piece at destination and capture wasn't declared
    if (isWhitePiece(board, toRow, toCol) && (!m->isWhite) && (m->isCapture == 0))
        return 0;
    //check if black move and there is a black piece at destination
    if (isBlackPiece(board, toRow, toCol) && (!m->isWhite))
        return 0;
    //check if white move and there is a white piece at destination
    if (isWhitePiece(board, toRow, toCol) && (m->isWhite))
        return 0;
    //check if a move is valid and it causes a check on the player that made the move
    if (isMeCheck(board, m) && isValid(board, m->srcPiece, fromRow, fromCol, toRow, toCol))
        return 0;
    return 1;
}

/****************************************
 * Function Name: initializeStruct
 * Input: Move* m, int isWhiteTurn
 * Output: none
 * Function Operation: this function initializes all the values of the struct to make sure while checking for validation
 the struct will possess values that are true for the specific pgn.
 ***************************************/
void initializeStruct(Move* m, int isWhiteTurn) {
    //initializing all structure values
    m->srcPiece = 'P';
    m->srcRow = 0;
    m->srcCol = 0;
    m->destPiece = 0;
    m->destPiece = 0;
    m->promotionPiece = ' ';
    m->iSrc = -1;
    m->jSrc = -1;
    m->iDest = -1;
    m->jDest = -1;
    m->isWhite = isWhiteTurn;
    m->isCapture = 0;
    m->isPromotion = 0;
    m->isCheck = 0;
    m->isMate = 0;
    m->isLegal = 1;
}

/****************************************
 * Function Name: makeMove
 * Input: char board[][SIZE], char pgn[], int isWhiteTurn
 * Output: an integer of 1 or 0
 * Function Operation: this function performs the move declared by the pgn string if valid. if the move is valid return
 1 and change the board, otherwise return 0.
 ***************************************/
int makeMove(char board[][SIZE], char pgn[], int isWhiteTurn) {
    //initialize struct
    Move m;
    initializeStruct(&m, isWhiteTurn);
    //analyze information from given pgn, and put all values into struct
    pgnAnalysis(pgn, board, isWhiteTurn, &m);
    //if the move is valid, perform it on the board
    //if a promotion was declared then perform the move with promotion piece
    if (validateMove(&m, board, m.iSrc, m.jSrc, m.iDest, m.jDest)) {
        if(m.isPromotion == 1){
            board[m.iSrc][m.jSrc] = EMPTY;
            board[m.iDest][m.jDest] = m.promotionPiece;
        }
        else {
            board[m.iSrc][m.jSrc] = EMPTY;
            board[m.iDest][m.jDest] = m.srcPiece;
        }
        return 1;
    }
    return 0;
}