#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int wdth;
    int hght;
    int pos;
} board;

void initTopBot(char *bitMap, int *idx, board mainBoard) { 
    int line = (2 * mainBoard.wdth + 2);
    for(int i = 0; i < line; ++i) {
        if(i == line - 1) { 
            bitMap[*idx] = '\n'; 
        }
        else {
            bitMap[*idx] = '-';
        }
        ++(*idx);
    }
}

void initBlank(char *bitMap, int *idx, board mainBoard) { 
    int line = 2 * mainBoard.wdth + 2;
    for(int i = 0; i < line; ++i) {
        if(i == line - 1) { 
            bitMap[*idx] = '\n'; 
        }
        else if(i == 0 || i == line - 2) {
            bitMap[*idx] = '|'; 
        }
        else {
            bitMap[*idx] = ' ';
        }
        ++(*idx);
    }
}

void initLine(char *bitMap, int *idx, board mainBoard) { 
    int line = 2 * mainBoard.wdth + 2;
    for(int i = 0; i < 2 * mainBoard.wdth + 2; ++i) { 
            if (i == 2 * mainBoard.wdth + 1) {
                (bitMap)[*idx] = '\n';
            }
            else if (i == 0 || i == line - 2) {
                (bitMap)[*idx] = '|';
            }
            else if (i % 2 == 0) {
                (bitMap)[*idx] = ' ';
            }
            else {
                (bitMap)[*idx] = '*';
            }
            ++(*idx);
        }
}

void initBitMap (char **bitMapP, board mainBoard) {
    int idx = 0; 
    int bitMapLen = (2 * mainBoard.wdth + 2) * (2 * mainBoard.hght + 1) + 1;
    *bitMapP = (char *)malloc(bitMapLen);
    for(int i = 0; i < (2 * mainBoard.hght + 1); ++i) {
        if(i == 0 || i == 2 * mainBoard.hght) {
            initTopBot(*bitMapP, &idx, mainBoard); 
        }
        else if(i % 2 == 0){
            initBlank(*bitMapP, &idx, mainBoard); 
        }
        else {
            initLine(*bitMapP, &idx, mainBoard); 
        }
    }
    (*bitMapP)[idx] = '\0';
}

bool goRight(board *gapP, int *idx, char *bitMapP, board mainBoard) {
    bool flag = false;
    bool retVal = false; 
    int line = 2 * mainBoard.wdth + 2;
    int bitMapLen = (2 * mainBoard.wdth + 2) * (2 * mainBoard.hght + 1) + 1;
    *idx += 2; 
    gapP->wdth = 0;
    if(*idx + line > bitMapLen) {
        flag = true;
        retVal = true;
        gapP->wdth = mainBoard.wdth;
    }
    while(!flag) { 
        if(bitMapP[*idx] == ' ' ||
            bitMapP[*idx] == '|') {
            if(bitMapP[*idx - line - 2] == '|') {
                flag = true;
                retVal = true;
            }
            else {
                flag = true;
                *idx -= 2;
            }
        } 
        else {
            *idx += 2; 
            ++gapP->wdth;
        } 
    }
    return retVal;
}

void goDown(board *gapP, int *idx, char *bitMapP, board mainBoard) {
    bool flag = false; 
    int line = 2 * mainBoard.wdth + 2;
    *idx += 2 * line; 
    while(!flag) { 
        if(bitMapP[*idx] == '-') {
            gapP->pos = *idx; 
            flag = true;
        }
        else {
            *idx += 2 * line; 
        }
        ++gapP->hght; 
    }
}

void gapFnd(board *gapP, char *bitMap, board mainBoard) {
    bool flag = false;
    int idx = 0;
    gapP->hght = 0;
    while(!flag) { 
        goDown(gapP, &idx, bitMap, mainBoard);
        flag = goRight(gapP, &idx, bitMap, mainBoard); 
    }
}

void cutBitMap(char *bitMap, board cutBoard, board mainBoard) {
    int line = 2 * mainBoard.wdth + 2;
    int idx = cutBoard.pos - 2 * cutBoard.hght * line;
    int tmp = idx;
    while(bitMap[idx] != '-') {
        bitMap[idx] = '|';
        idx += line;
    }
    idx = tmp;
    while(idx < tmp + 2 * cutBoard.wdth + 1) {
        bitMap[idx] = '-';
        ++idx;
    }
    --idx;
    idx += line;
    while(bitMap[idx] != '-') {
        bitMap[idx] = '|';
        idx += line;
    }
}

void shapeCalc(board *cutBoard, int idx, int maxArea, board *gapP) {
    bool runOnce = false; 
    int ratioLimit = sqrt(2 * maxArea);
    int maxWdth = gapP->wdth < ratioLimit ? gapP->wdth : ratioLimit;
    int remainder;
    int height;
    int minRemainder; 
    int i = 0; 
    do {
        height = maxArea / (maxWdth - i);
        height = height > 2 * (maxWdth - i) ? 2 * (maxWdth - i) : height;
        height = height > gapP->hght ? gapP->hght : height;
        remainder = maxArea % ((maxWdth - i) * height);
        if(!runOnce) {
            minRemainder = remainder + 1;
            runOnce = true;
        }
        if(remainder < minRemainder) {
            minRemainder = remainder;
            cutBoard[idx].wdth = maxWdth - i;
            cutBoard[idx].hght = height;
            cutBoard[idx].pos = gapP->pos; 
        }
        ++i;
    } while(height != maxWdth &&
        remainder != 0 &&
        gapP->wdth > ratioLimit);
    gapP->wdth -= cutBoard[idx].wdth;
    gapP->pos +=  2 * cutBoard[idx].wdth; 
}

void cutter(char *bitMap, int maxArea, board *gapP, board mainBoard) {
    int size = 0;
    int idx = 0;
    board *cutBoardP;
    cutBoardP = (board *)malloc(sizeof(board));
    while(gapP->wdth != 0) {
        cutBoardP = (board *)realloc(cutBoardP, size += sizeof(board));
        shapeCalc(cutBoardP, idx, maxArea, gapP);
        cutBitMap(bitMap, cutBoardP[idx], mainBoard);
        ++idx;
    }
    free(cutBoardP);
}

int main() {
    bool skipFirst = false;
    int posBefore;
    int maxArea;
    char *bitMapP;
    board mainBoard;
    board gap;
    scanf("%d%d%d", &mainBoard.wdth, &mainBoard.hght, &maxArea);
    initBitMap(&bitMapP, mainBoard);
    while(true) {
        gapFnd(&gap, bitMapP, mainBoard);
        if(skipFirst) {
            if(posBefore == gap.pos) {
                break;
            }
        }
        skipFirst = true;
        posBefore = gap.pos;
        cutter(bitMapP, maxArea, &gap, mainBoard);
        printf("%s\n", bitMapP);
    }
    free(bitMapP);
    return 0;
}
