#include "geesespotter_lib.h"

//Return pointer
char * createBoard(std::size_t xdim, std::size_t ydim) { 
    
    char *createBoard = new char[xdim*ydim];

    for (int i = 0; i < xdim*ydim; i++) {

        createBoard[i] = 0x00;
        //std::cout << createBoard[i];
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
        
        //(board[i]^0x20 < 0x10) && (board[i]^0x20 >= 0x00)

            // if (board[i + k + counter] >= 0x10) {
                
            
            if ((board[i] & 0x10) == 0x10) {

                    // if (isM == 0) {
                        std::cout << "M";
                        //numState = false;isM++;
                //     }
                // isM = 0;
            }

            else if ((board[i] & 0x20) == 0x20) {

                std::cout << "*";
                
            }      

            else {

                // int num = 0;

                // //if (isM = 0) {
                    
                //     for (int j = 0; j < board[i + k + counter]; j++) {

                //         num++;   
                //     }std::cout << num;
                // //}
                int integer = board[i] & valueMask();
                std::cout << integer;
            }
            
            rowCount++;

            if (rowCount == xdim) {
                
                std::cout << std::endl;
                rowCount = 0;
            }

            // numState = true;
        }

        
        counter = counter + ydim; //counter + 2 works?

}
int reveal(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc) {
    
    // int counter = 0;
    // int zeroCount = 1;

    // // if (ydim != 0) { //Determines the postion of coord in the 1D Array
    // //     for (int yPt = 0; yPt < yloc; yPt++) {

    // //         counter = ydim + counter;
    // //     }    

    // //     //std::cout << board[xloc + yloc + counter] << std::endl;
    // // }

    // //Do 0x20 before 0x10

    // for (int i = 1; i <= ydim; i++) { 

    ////////////////////////////////////////////

    ///////////////////////////////////////////
    
    if ((board[xdim*yloc + xloc] & 0x10) > 0) {
        
        // std::cout << "Test5";
        return 1;
    }

    else if ((board[xdim*yloc + xloc] & 0x20) == 0) { //Is revealed when its a number value from 1 to 9

        //std::cout << "This actually works" << std::endl;
        // std::cout << "Test4.2";
        return 2;
    }

    else if ((board[xdim*yloc + xloc] ^ 0x20) == 0x09) { //??
        
        board[xdim*yloc + xloc] = (board[xdim*yloc + xloc] & valueMask());
        // std::cout << "Test3";
        return 9;
    }

    else {

        board[xdim*yloc + xloc] = board[xdim*yloc + xloc] & valueMask();

        if ((board[xdim*yloc + xloc] & valueMask()) == 0)
        {

            // for(int j = -1; j <= 1; ++j)
            // {
            //     for(int i = -1; i <= 1; ++i)
            //     {
            //         if ((xloc + i >= 0x00) && (xloc + i < xdim) && (yloc + j >= 0x00) && (yloc + j < ydim))
            //         {
            //             if ((board[xdim*j + i + xdim*yloc + xloc] ^ 0x20) != 0x09 && (board[xdim*j + i + xdim*yloc + xloc] & markedBit()) == 0)
            //             {
            //                 board[xdim*j + i + xdim*yloc + xloc] = board[xdim*j + i + xdim*yloc + xloc] ^ 0x20;
            //             }
            //         }
                            
            //     }
            // }

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
    // }
    // else if ((board[xdim*yloc + xloc] ^ 0x20) >= 0 && (board[xdim*yloc + xloc] ^ 0x20) < 0x09) {
        
    //     std::cout << "here" << std::endl;

    //             board[xdim*yloc + xloc] = board[xdim*yloc + xloc] ^ 0x20;

    //             // zeroCount = 0;

    //             int colCount = 0;

    //             for (int i = 0; i < yloc; i++) {

    //                 colCount++;
    //             }

    //             if (board[xdim*yloc + xloc] == 0x00) {

    //             if ((xdim*yloc + xloc - 1) >= 0 && (board[xdim*yloc + xloc - 1] & 0x20) > 0 && (xdim*yloc + xloc - 1) <= (xdim*(i-1))) {//&&(counter + i + k - 1) > xdim*i

    //                 board[xdim*yloc + xloc - 1] = board[xdim*yloc + xloc - 1] ^ 0x20;
    //             }
    // //             // std::cout << "Test2" << std::endl;
    //             if ((xdim*yloc + xloc + 1) >= 0 && (board[xdim*yloc + xloc + 1] & 0x20) > 0 && (xdim*yloc + xloc + 1) <= ((xdim*(i)) - 1)) {//&& (counter + i + k + 1) > xdim*i

    //                 board[xdim*yloc + xloc + 1] = board[xdim*yloc + xloc + 1] ^ 0x20;
    //             }

    //             // if ((xdim*yloc + xloc - ydim) >= 0 && (board[xdim*yloc + xloc - ydim] & 0x20) > 0 && (xdim*yloc + xloc - ydim) > (colCount)) { //&& (counter + i + k - 1 - xdim) > xdim*i//Row above

    //             //     board[xdim*yloc + xloc - ydim] = board[xdim*yloc + xloc - ydim] ^ 0x20;
    //             // }

    //             // if ((xdim*yloc + xloc - ydim + 1) >= 0 && (board[xdim*yloc + xloc - ydim + 1] & 0x20) > 0) { //&& (counter + i + k + 1 - xdim) > xdim*i//Row above

    //             //     board[xdim*yloc + xloc - ydim + 1] = board[xdim*yloc + xloc - ydim + 1] ^ 0x20;

    //             //     //std::cout << counter << std::endl;
    //             // }

    //             // if ((xdim*yloc + xloc - ydim + 2) >= 0 && (board[xdim*yloc + xloc - ydim + 2] & 0x20) > 0 && (xdim*yloc + xloc - ydim + 2) <= ((xdim*i) - 1)) { //&& (counter + i + k + 1 - xdim) > xdim*i//Row above

    //             //     board[xdim*yloc + xloc - ydim + 2] = board[xdim*yloc + xloc - ydim + 2] ^ 0x20;

    //             //     //std::cout << counter << std::endl;
    //             // }

    //             // if ((xdim*yloc + xloc  + ydim) >= 0 && (board[xdim*yloc + xloc  + ydim] & 0x20) > 0 && (xdim*yloc + xloc + ydim) <= ((xdim*i) - 1)) { //&& (counter + i + k - 1 + xdim) > xdim*i//Row below

    //             //     board[xdim*yloc + xloc  + ydim] = board[xdim*yloc + xloc  + ydim] ^ 0x20;
    //             // }

    //             // if (((xdim*yloc + xloc - 1 + ydim) >= 0) && (board[xdim*yloc + xloc - 1 + ydim] & 0x20) > 0 && (xdim*yloc + xloc - 1 + ydim) <= (xdim*(i-1))) { //&& (counter + i + k + 1 + xdim) > xdim*i//Row below

    //             //     board[xdim*yloc + xloc - 1 + ydim] = board[xdim*yloc + xloc - 1 + ydim] ^ 0x20;
    //             // }
                
    //             // if ((xdim*yloc + xloc - 2 + ydim) >= 0 && (board[xdim*yloc + xloc - 2 + ydim] & 0x20) > 0 ) { //&& (counter + i + k - xdim) > xdim*i//Center above

    //             //     board[xdim*yloc + xloc - 2 + ydim] = board[xdim*yloc + xloc - 2 + ydim] ^ 0x20;
    //             // }

    //             }
    //         }
    
    // // else if ((board[xloc + yloc + counter] & 0x20) > 0) { //Is outputting 1 zero
        
        
    // //     std::cout << "Test1";
    }    

    return 0;

}
int mark(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc) {
    
    //Maybe if hexa is greater than 20 subtract that first then 10. keep subtracting 20 until less than 20  

    int counter = 0;

    if (ydim != 0) { //Determines the postion of coord in the 1D Array
        for (int yPt = 0; yPt < yloc; yPt++) {

            counter = ydim + counter;
        }    

        //std::cout << "Mark " << counter + xloc + yloc << std::endl;
    }

    

    // else if ((board[xdim*yloc + xloc] & 0x20) > 0 && (board[xdim*yloc + xloc] >= 0x10)) { //if binary number has same number of digits as 0x10 then it will alaways be greater than zero

    //     board[xdim*yloc + xloc] = board[xdim*yloc + xloc] ^ 0x10;
    //     return 0;
    //         //std::cout << "IF3 " << board[xloc + yloc + counter] << "--" << "0x13" << std::endl;
    // }
        
        //((board[xdim + ydim + counter] | 0x10) >= 0x10) && ((board[xdim + ydim + counter] | 0x10) < 0x20)
    if (board[xdim*yloc + xloc] < 0x9) { //Is revealed when its a number value from 1 to 9

        //std::cout << "IF1 : " << board[xloc + yloc + counter] << "--" << "0x12" << std::endl;
        return 2;
    }
    
    else if ((board[xdim*yloc + xloc] & 0x20) > 0 && (board[xdim*yloc + xloc] >= 0x20) && (board[xloc + yloc + counter] < 0x30)) { //if binary number has same number of digits as 0x10 then it will alaways be greater than zero

        board[xdim*yloc + xloc] = board[xdim*yloc + xloc] ^ 0x10; //Makes it hidden and marked?
        // std::cout << "IF2 " << board[xloc + yloc + counter] << "--" << "0x14" << std::endl;
        // std::cout << counter + xloc + yloc << std::endl;
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
    // for (int i = 0; i < (ydim); i++) {

    //     for (int k = 0; k < xdim; k++) {

            
            // if (board[xloc + yloc + counter] == 0x00) {

            //     if ((counter + xloc + yloc - 1) >= 0 && (board[counter + xloc + yloc - 1] & 0x20) > 0) {//&&(counter + i + k - 1) > xdim*i

            //         board[counter + xloc + yloc - 1] = board[counter + xloc + yloc - 1] ^ 0x20;
            //     }
            //     // std::cout << "Test2" << std::endl;
            //     if ((counter + xloc + yloc + 1) >= 0 && (board[counter + xloc + yloc + 1] & 0x20) > 0 ) {//&& (counter + i + k + 1) > xdim*i

            //         board[counter + xloc + yloc + 1] = board[counter + xloc + yloc + 1] ^ 0x20;
            //     }

            //     if ((counter + xloc + yloc - ydim) >= 0 && (board[counter + xloc + yloc - ydim] & 0x20) > 0 ) { //&& (counter + i + k - 1 - xdim) > xdim*i//Row above

            //         board[counter + xloc + yloc - ydim] = board[counter + xloc + yloc - ydim] ^ 0x20;
            //     }

            //     if ((counter + xloc + yloc - ydim - 1) >= 0 && (board[counter + xloc + yloc - ydim - 1] & 0x20) > 0 ) { //&& (counter + i + k + 1 - xdim) > xdim*i//Row above

            //         board[counter + xloc + yloc - ydim - 1] = board[counter + xloc + yloc - ydim - 1] ^ 0x20;

            //         //std::cout << counter << std::endl;
            //     }

            //     if ((counter + xloc + yloc - ydim - 2) >= 0 && (board[counter + xloc + yloc - ydim - 2] & 0x20) > 0 ) { //&& (counter + i + k + 1 - xdim) > xdim*i//Row above

            //         board[counter + xloc + yloc - ydim - 2] = board[counter + xloc + yloc - ydim - 2] ^ 0x20;

            //         //std::cout << counter << std::endl;
            //     }

            //     if ((counter + xloc + yloc + ydim) >= 0 && (board[counter + xloc + yloc + ydim] & 0x20) > 0 ) { //&& (counter + i + k - 1 + xdim) > xdim*i//Row below

            //         board[counter + xloc + yloc + ydim] = board[counter + xloc + yloc + ydim] ^ 0x20;
            //     }

            //     if (((counter + xloc + yloc + 1 + ydim) >= 0) && (board[counter + xloc + yloc + 1 + ydim] & 0x20) > 0 ) { //&& (counter + i + k + 1 + xdim) > xdim*i//Row below

            //         board[counter + xloc + yloc + 1 + ydim] = board[counter + xloc + yloc + 1 + ydim] ^ 0x20;
            //     }
                
            //     if ((counter + xloc + yloc + 2 + ydim) >= 0 && (board[counter + xloc + yloc + 2 + ydim] & 0x20) > 0 ) { //&& (counter + i + k - xdim) > xdim*i//Center above

            //         board[counter + xloc + yloc + 2 + ydim] = board[counter + xloc + yloc + 2 + ydim] ^ 0x20;
            //     }

            //     }
    
    //         if (board[i + k + counter] == 0x09) {

    //             geeseCount++;
    //         }

    //         else {
    //             return false;
    //         }
    //     }
        
    //     counter = ydim + counter;
    // }

    // if ((revCount + geeseCount) == (xdim*ydim)) {

    //     return true;
    // }
    
    return false;
}

