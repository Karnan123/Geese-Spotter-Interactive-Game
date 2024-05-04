#include "geesespotter_lib.h"

char * createBoard(std::size_t xdim, std::size_t ydim) { 
    
    char *createBoard = new char[xdim*ydim];

    for (int i = 0; i < xdim*ydim; i++) {

        createBoard[i] = 0x00;
    }

    return createBoard;
}

void computeNeighbors(char * board, std::size_t xdim, std::size_t ydim) {

    int numGeese = 0;
    int xPt = 0;
    int yPt = 0;

    for(int k = 0; k < xdim*ydim; k++)
    {
        if ((board[k] & valueMask()) == 0x09)
        {
            for(int yRange = -1; yRange <= 1; yRange++)
            {
                for(int xRange = -1; xRange  <= 1; xRange++)
                {
                    xPt = k % xdim;

                    yPt = k / xdim;

                    if ((xPt + xRange  > -1) && (xPt + xRange  < xdim) && (yPt + yRange  > -1) && (yPt + yRange  < ydim))
                    {
                        if ((board[k + xdim*yRange  + xRange] & valueMask()) != 0x09)
                        {
                            numGeese = numGeese + 1;
                            board[k + xdim*yRange + xRange] = numGeese + board[k + xdim*yRange + xRange];
                            numGeese = 0;
                        }
                    }
                    
                }
            }
        }
    }
}
void hideBoard(char * board, std::size_t xdim, std::size_t ydim) {
    
    for (int i = 0; i < (xdim*ydim); i++) {

        board[i] = (board[i] | 0x20);
    }
}

void cleanBoard(char * board) {

    delete[] board;
    board = nullptr;
}
void printBoard(char * board, std::size_t xdim, std::size_t ydim) {

    int counter = 0;
    int isM = 0;
    bool numState = true;
    int rowCount = 0;

    for (int i = 0; i < ydim*xdim; i++) {

        int k = 0;
        
            // if (board[i + k + counter] >= 0x10) {
                
            
            if ((board[i] & 0x10) == 0x10) {

                  
                std::cout << "M";
            }

            else if ((board[i] & 0x20) == 0x20) {

                std::cout << "*";
            }      

            else {

                int integer = board[i] & valueMask();
                std::cout << integer;
            }
            
            rowCount++;

            if (rowCount == xdim) {
                
                std::cout << std::endl;
                rowCount = 0;
            }
        }

        
        counter = counter + ydim; //counter + 2 works?

}
int reveal(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc) {
    
    if ((board[xdim*yloc + xloc] & 0x10) > 0) {
        
        return 1;
    }

    else if ((board[xdim*yloc + xloc] & 0x20) == 0) { //Is revealed when its a number value from 1 to 9

        return 2;
    }

    else if ((board[xdim*yloc + xloc] ^ 0x20) == 0x09) { //??
        
        board[xdim*yloc + xloc] = (board[xdim*yloc + xloc] & valueMask());
        return 9;
    }

    else {

        board[xdim*yloc + xloc] = board[xdim*yloc + xloc] & valueMask();

        if ((board[xdim*yloc + xloc] & valueMask()) == 0)
        {
            for(int j = -1; j <= 1; ++j)
            {
                for(int i = -1; i <=1; ++i)
                {
                if ((xloc + i >= 0) && (xloc + i < xdim) && (yloc + j >= 0) && (yloc + j < ydim))
                {
                    if ((board[xdim*j + i + xdim*yloc + xloc] & valueMask()) != 9 && (board[xdim*j + i +xdim*yloc + xloc] & 0x10) == 0)
                    {
                        board[xdim*j + i + xdim*yloc + xloc] = (board[xdim*j + i + xdim*yloc + xloc] & valueMask());
                    }
                }
                            
                }
            }
        }
    }    

    return 0;

}
int mark(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc) {
    
    int counter = 0;

    if (ydim != 0) { //Determines the postion of coord in the 1D Array
        for (int yPt = 0; yPt < yloc; yPt++) {

            counter = ydim + counter;
        }    
    }

    if (board[xdim*yloc + xloc] < 0x9) { //Is revealed when its a number value from 1 to 9

        return 2;
    }
    
    else if ((board[xdim*yloc + xloc] & 0x20) > 0 && (board[xdim*yloc + xloc] >= 0x20) && (board[xloc + yloc + counter] < 0x30)) { //if binary number has same number of digits as 0x10 then it will alaways be greater than zero

        board[xdim*yloc + xloc] = board[xdim*yloc + xloc] ^ 0x10; 
        return 0;
    }
    
    return 0;
}
bool isGameWon(char * board, std::size_t xdim, std::size_t ydim) {
    
    int counter = 0;
    int geeseCount = 0;
    int revCount = 0;
    bool result = false;

    for (int i = 0; i < xdim*ydim; i++) {

        if ((board[i] & 0x20) != 0x20) {

            counter++;
        }

        if ((board[i] & valueMask()) == 0x09) {

            geeseCount++;
        }
    }

    if (xdim*ydim == (counter + geeseCount)) {

        return true;
    }

    return false; 
    
    return false;
}

