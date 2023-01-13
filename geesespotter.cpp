#include "geesespotter_lib.h"
#include <iostream>

char *createBoard(std::size_t xdim, std::size_t ydim);
void hideBoard(char *board, std::size_t xdim, std::size_t ydim);
void cleanBoard(char *board);
void printBoard(char *board, std::size_t xdim, std::size_t ydim);
int mark(char *board, std::size_t xdim, std::size_t ydim, std::size_t x_loc, std::size_t y_loc);

bool isGameWon(char *board, std::size_t xdim, std::size_t ydim);
void computeNeighbors(char *board, std::size_t xdim, std::size_t ydim);
int reveal(char *board, std::size_t xdim, std::size_t ydim, std::size_t x_loc, std::size_t y_loc);

char *createBoard(std::size_t xdim, std::size_t ydim){
    //dynamically allocated memory for the board
    char *board{new char[xdim*ydim]{0}};
    return board;
}

void hideBoard(char *board, std::size_t xdim, std::size_t ydim){
    //set up the hidden bit
    int mask{hiddenBit()};
    for(int i{0}; i < (xdim*ydim); ++i){
        board[i] = (board[i] | mask);
    }
}

void cleanBoard(char *board){
    delete[] board;
    board = nullptr;
}

void printBoard(char *board, std::size_t xdim, std::size_t ydim){
    for(int i{0}; i < (xdim*ydim); ++i){
        //check if marked
        if((board[i] & markedBit()) == markedBit()){
            std::cout << "M";
        }
        //check if hidden or contains a certain int
        else{
            if ((board[i] & hiddenBit()) == hiddenBit()){
                std::cout << "*";
            }
            else{
                int temp = (board[i] & valueMask());
                std::cout << temp << ""; 
            }
        }
        if((i+1) % xdim == 0){
            std::cout << std::endl;
        }
    }
}

int mark(char *board, std::size_t xdim, std::size_t ydim, std::size_t x_loc, std::size_t y_loc){
    //1 column early, 1 row early
    int board_ind = y_loc*xdim + x_loc;
    //check if hidden, if not
    if ((board[board_ind] & hiddenBit()) == 0){
        return 2;
    }
    //else toggle the mark bit
    else{
        board[board_ind] = (board[board_ind] ^ markedBit());
        return 0;
    }
}

bool isGameWon(char *board, std::size_t xdim, std::size_t ydim){
    //sometimes it works, sometimes not, not sure where the problems is.
    int temp{0};
    int goose_count{0};
    int reveal_count{0};
    for(int i{0}; i < (xdim*ydim); ++i){
        temp = (board[i] & valueMask());
        if(temp == 9){
            ++goose_count;
        }
        else if((board[i] & hiddenBit()) == 0){
            ++reveal_count;
        }
    }
    if((xdim*ydim - goose_count) == reveal_count){
        return true;
    } 
    else{
        return false;
    }
}

void computeNeighbors(char *board, std::size_t xdim, std::size_t ydim){
    for(int i{0}; i < (xdim*ydim); ++i){
        int ind{0};
        int count{0};
        int x_loc = i % xdim;
        int y_loc = i / xdim;
        int temp{0};
        temp = (board[i] & valueMask());

        if(temp != 9){
            for(int k{-1}; k < 2; ++k){
                for(int j{-1}; j < 2; ++j){
                    if(((y_loc + k) >= 0) && ((y_loc + k) < ydim) && ((x_loc + j) >= 0) && ((x_loc + j) < xdim)){
                        ind = (y_loc + k)*xdim + (x_loc + j);
                        //store the value stored at a field
                        int around = (board[ind] & valueMask());
                        if(around == 9){
                            ++count;
                        }
                    }
                }
            }
            //clean value part
            board[i] = (board[i] & (~valueMask()));
            //assign count to board
            board[i] = (board[i] | count);
            count = 0;
        }
    }
    return;
}

int reveal(char *board, std::size_t xdim, std::size_t ydim, std::size_t x_loc, std::size_t y_loc){
    int board_ind = y_loc*xdim + x_loc;
    //check if marked
    if((board[board_ind] & markedBit()) == markedBit()){
        return 1;
    }
    //check if revealed
    else if((board[board_ind] & hiddenBit()) == 0){
        return 2;
    }
    else{
        //isolate the value stored at that loc
        int temp = board[board_ind];
        temp &= valueMask();
        //check if the value is 9
        if(temp == 9){
            board[board_ind] = (board[board_ind] & (~hiddenBit()));
            return 9;
        }
        else{
            //needs to reveal the surrounding fields if the value stored is 0
            if(temp == 0){
                for(int i{-1}; i < 2; ++i){
                    for(int k{-1}; k < 2; ++k){
                        if(((y_loc + i) >= 0) && ((y_loc + i) < ydim) && ((x_loc + k) >= 0) && ((x_loc + k) < xdim)){
                            int ind = (y_loc + i)*xdim + (x_loc + k);
                            board[ind] = (board[ind] & (~hiddenBit()));
                        }
                    }
                }
            }
            //if not, just reveal the field
            else{
                board[board_ind] = (board[board_ind] & (~hiddenBit()));
            }
            return 0;
        }
    }
}