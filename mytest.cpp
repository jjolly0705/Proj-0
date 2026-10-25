// UMBC - CMSC 341 - Fall 2026 - Proj0
#include "bingo.h"
#include <iostream>

const char *FAIL_STATEMENT = "*****TEST FAILED: ";
const char *PASS_STATEMENT = "    TEST PASSED: ";

class Tester {
    public: 
    bool testDefaultConstructorNormal();

    bool testConstructorNormal();
    bool testConstructorNotSquare();
    bool testConstructorMinRowsEdge();
    bool testConstructorMaxRowsEdge();
    bool testConstructorRowsError();
    bool testConstructorColError();
    bool testConstructorRange();
    bool testConstructorMinMax();

    bool testRecreateNormal();
    bool testRecreateWOClear(); 
    bool testRecreatePopulated();

    bool testInitCardRange();
    bool testInitCardNotSquare();
    bool testInitCardPosition();
    bool testInitCardHelper();
    bool testInitCardNoDoubleInColumn();
    bool testInitCardNoDoubleOnCard();
    bool testInitCardEmptyError();

    bool testPlayWinNormal();
    bool testPlayColumnWin();
    bool testPlayLessThanRange();
    bool testPlayNumDrawsError();
    bool testPlayBallVectorError();

    bool testDrawBallsNormal();
    bool testDrawBallsNoDouble();
    bool testDrawBallsError();

    bool testAssignNormal();
    bool testAssignSelfAssign();
    bool testAssignChainedAssigned();
    bool testAssignEmptyToNormal();
    bool testAssignNormalToEmpty();

    bool testClearNormal();
    bool testClearEmpty();
    bool testClearReuse();

    // These tests are to see if my code encoutered some bugs that I had at first while I was trying 
    // to write bingo.cpp
    bool testInitCardMinRowsEdge();
    bool testInitCardNotSquareFull();
    bool testPlayEmptyCellCount();
    bool testPlayOnlyOneLine();
    bool testPlayBallVectorNoChange();
};

//testDefaultConstructorNormal
//Case: creates a Bingo object with the default constructor
//Expected: every member variable is initialized which means all pointers are null and the ints are 0
bool Tester::testDefaultConstructorNormal(){
    Bingo card;
 
    bool result = (card.m_card == nullptr) && (card.m_helper == nullptr) && (card.m_trackRows == nullptr) && (card.m_trackCols == nullptr) && (card.m_numRows == 0) && (card.m_numCols == 0) && (card.m_helperSize == 0) && (card.m_minBallVal == 0) && (card.m_maxBallVal == 0);
 
    if (!result){
        cout << FAIL_STATEMENT << "testDefaultConstructorNormal" << endl;
        return false;
    }
    cout << PASS_STATEMENT << "testDefaultConstructorNormal" << endl;
    return true;
}
 
//testConstructorNormal
//Case: creates valid 5x5 card using MINVAL and MAXVAL
//Expected: memory is allocated and all the members set correctly
bool Tester::testConstructorNormal(){
    Bingo card(CARDROWS, CARDCOLS, MINVAL, MAXVAL);
 
    bool result = (card.m_numRows == CARDROWS) && (card.m_numCols == CARDCOLS) && (card.m_minBallVal == MINVAL) && (card.m_maxBallVal == MAXVAL) && (card.m_helperSize == (MAXVAL - MINVAL + 1)) && (card.m_card != nullptr) && (card.m_helper != nullptr) && (card.m_trackRows != nullptr) && (card.m_trackCols != nullptr);
 
    if (!result){
        cout << FAIL_STATEMENT << "testConstructorNormal" << endl;
        return false;
    }
    cout << PASS_STATEMENT << "testConstructorNormal" << endl;
    return true;
}
 
//testConstructorNonSquare
//Case: creates valid non-square card which is 10 rows by 5 columns
//Expected: memory is allocated and dimensions match the rows that were asked for
bool Tester::testConstructorNotSquare(){
    Bingo card(2 * CARDROWS, CARDCOLS, MINVAL, MAXVAL);
 
    if (card.m_numRows != 2 * CARDROWS || card.m_numCols != CARDCOLS || card.m_card == nullptr){
        cout << FAIL_STATEMENT << "testConstructorNotSquare" << endl;
        return false;
    }
    cout << PASS_STATEMENT << "testConstructorNotSquare" << endl;
    return true;
}

//testConstructorMinRowsEdge
//Case: creates smallest valid number of rows which is 2
//Expected: object is created without issues
bool Tester::testConstructorMinRowsEdge(){
    Bingo card(2, CARDCOLS, MINVAL, MAXVAL);
 
    if (card.m_card == nullptr || card.m_numRows != 2){
        cout << FAIL_STATEMENT << "testConstructorMinRowsEdge" << endl;
        return false;
    }
    cout << PASS_STATEMENT << "testConstructorMinRowsEdge" << endl;
    return true;
}
 
//testConstructorMaxRowsEdge
//Case: creates largest valid number of rows which is 15
//Expected: object is created without issues
bool Tester::testConstructorMaxRowsEdge(){
    Bingo card(15, CARDCOLS, MINVAL, MAXVAL);
 
    if (card.m_card == nullptr || card.m_numRows != 15){
        cout << FAIL_STATEMENT << "testConstructorMaxRowsEdge" << endl;
        return false;
    }
    cout << PASS_STATEMENT << "testConstructorMaxRowsEdge" << endl;
    return true;
}
 
//testConstructorRowsErrod
//Case: rows below the valid minimum, which is 1, and above the valid maximum, which is 16
//Expected: both create empty objects
bool Tester::testConstructorRowsError(){
    Bingo tooFew(1, CARDCOLS, MINVAL, MAXVAL);
    Bingo tooMany(16, CARDCOLS, MINVAL, MAXVAL);
 
    if (tooFew.m_card != nullptr || tooFew.m_numRows != 0){
        cout << FAIL_STATEMENT << "testConstructorRowsError" << endl;
        return false;
    }
    if (tooMany.m_card != nullptr || tooMany.m_numRows != 0){
        cout << FAIL_STATEMENT << "testConstructorRowsError" << endl;
        return false;
    }
    cout << PASS_STATEMENT << "testConstructorRowsError" << endl;
    return true;
}
 
//testConstructorColError
//Case: columns are not equal to CARDCOLS
//Expected: an empty object is created
bool Tester::testConstructorColError(){
    Bingo card(CARDROWS, CARDCOLS + 1, MINVAL, MAXVAL);
 
    if (card.m_card != nullptr || card.m_numCols != 0){
        cout << FAIL_STATEMENT << "testConstructorColError" << endl;
        return false;
    }
    cout << PASS_STATEMENT << "testConstructorColError" << endl;
    return true;
}
 
//testConstructorRange
//Case: creates a value range that is not divisible by CARDCOLS
//Expected: an empty object is created
bool Tester::testConstructorRange(){
    Bingo card(CARDROWS, CARDCOLS, MINVAL, MAXVAL - 1);
 
    if (card.m_card != nullptr || card.m_numRows != 0){
        cout << FAIL_STATEMENT << "testConstructorRange" << endl;
        return false;
    }
    cout << PASS_STATEMENT << "testConstructorRange" << endl;
    return true;
}
 
//testConstructorMinMax
//Case: creates range of min greater than max
//Expected: an empty object is created
bool Tester::testConstructorMinMax(){
    Bingo card(CARDROWS, CARDCOLS, MAXVAL, MINVAL);
 
    if (card.m_card != nullptr || card.m_numRows != 0){
        cout << FAIL_STATEMENT << "testConstructorMinMax" << endl;
        return false;
    }
    cout << PASS_STATEMENT << "testConstructorMinMax" << endl;
    return true;
}
 
//testRecreateNormal
//Case: reCreateCard on a default or empty object
//Expected: succeeds and matches the dimensions asked for
bool Tester::testRecreateNormal(){
    Bingo card;
 
    bool created = card.reCreateCard(2 * CARDROWS, CARDCOLS, MINVAL, MAXVAL);
 
    if (!created || card.m_numRows != 2 * CARDROWS || card.m_numCols != CARDCOLS || card.m_card == nullptr){
        cout << FAIL_STATEMENT << "testRecreateNormal" << endl;
        return false;
    }
    cout << PASS_STATEMENT << "testRecreateNormal" << endl;
    return true;
}
 
//testRecreateWOClear *WO means without*
//Case: reCreateCard is called on a not empty object without calling clear() first
//Expected: returns false and leaves the existing object without change
bool Tester::testRecreateWOClear(){
    Bingo card(CARDROWS, CARDCOLS, MINVAL, MAXVAL);
 
    Cell** oldCard = card.m_card;
    int oldRows = card.m_numRows;
 
    bool created = card.reCreateCard(2 * CARDROWS, CARDCOLS, MINVAL, MAXVAL);
 
    if (created || card.m_card != oldCard || card.m_numRows != oldRows){
        cout << FAIL_STATEMENT << "testRecreateWOClear" << endl;
        return false;
    }
    cout << PASS_STATEMENT << "testRecreateWOClear" << endl;
    return true;
}
 
//testRecreatePopulated
//Case: checks the card immediately after a successful reCreateCard, before any separate initCard() call
//Expected: cells already hold valid random values within the range
bool Tester::testRecreatePopulated(){
    Bingo card;
    card.reCreateCard(CARDROWS, CARDCOLS, MINVAL, MAXVAL);
 
    int value = card.m_card[0][0].getVal();
 
    if (value < MINVAL || value > MINVAL + 14){
        cout << FAIL_STATEMENT << "testRecreatePopulated" << endl;
        return false;
    }
    cout << PASS_STATEMENT << "testRecreatePopulated" << endl;
    return true;
}
 
//testInitCardRange
//Case: creates a 5x5 card, verifies every cell's value falls within its column's range
//Expected: all values are within [columnMin, columnMax]
bool Tester::testInitCardRange(){
    Bingo card(CARDROWS, CARDCOLS, MINVAL, MAXVAL);
    int width = (MAXVAL - MINVAL + 1) / CARDCOLS;
 
    for (int j = 0; j < CARDCOLS; j++){
        int colMin = MINVAL + (j * width);
        int colMax = colMin + width - 1;
        for (int i = 0; i < CARDROWS; i++){
            int value = card.m_card[i][j].getVal();
            if (value < colMin || value > colMax){
                cout << FAIL_STATEMENT << "testInitCardRange" << endl;
                return false;
            }
        }
    }
    cout << PASS_STATEMENT << "testInitCardRange" << endl;
    return true;
}
 
//testInitCardNotSquare
//Case: creates a 10x5 card, verifies column ranges still hold for a non-square card
//Expected: all values are within [columnMin, columnMax]
bool Tester::testInitCardNotSquare(){
    Bingo card(2 * CARDROWS, CARDCOLS, MINVAL, MAXVAL);
    int width = (MAXVAL - MINVAL + 1) / CARDCOLS;
 
    for (int j = 0; j < CARDCOLS; j++){
        int colMin = MINVAL + (j * width);
        int colMax = colMin + width - 1;
        for (int i = 0; i < 2 * CARDROWS; i++){
            int value = card.m_card[i][j].getVal();
            if (value < colMin || value > colMax){
                cout << FAIL_STATEMENT << "testInitCardNotSquare" << endl;
                return false;
            }
        }
    }
    cout << PASS_STATEMENT << "testInitCardNotSquare" << endl;
    return true;
}
 
//testInitCardPosition
//Case: verifies if each cell's stored row/col match it's actual position in m_card
//Expected: getRow() == i and getCol() == j for every cell
bool Tester::testInitCardPosition(){
    Bingo card(CARDROWS, CARDCOLS, MINVAL, MAXVAL);
 
    for (int i = 0; i < CARDROWS; i++){
        for (int j = 0; j < CARDCOLS; j++){
            if (card.m_card[i][j].getRow() != i || card.m_card[i][j].getCol() != j){
                cout << FAIL_STATEMENT << "testInitCardPosition" << endl;
                return false;
            }
        }
    }
    cout << PASS_STATEMENT << "testInitCardPosition" << endl;
    return true;
}
 
//testInitCardHelper
//Case: verifies if m_helper maps every card value back to its correct cell
//Expected: m_helper[val - minBallVal] holds the same row/col/value as the card cell
bool Tester::testInitCardHelper(){
    Bingo card(CARDROWS, CARDCOLS, MINVAL, MAXVAL);
 
    for (int i = 0; i < CARDROWS; i++){
        for (int j = 0; j < CARDCOLS; j++){
            int value = card.m_card[i][j].getVal();
            int index = value - card.m_minBallVal;
            if (card.m_helper[index].getRow() != i || card.m_helper[index].getCol() != j ||
                card.m_helper[index].getVal() != value){
                cout << FAIL_STATEMENT << "testInitCardHelper" << endl;
                return false;
            }
        }
    }
    cout << PASS_STATEMENT << "testInitCardHelper" << endl;
    return true;
}
 
//testInitCardNoDoubleInColumn
//Case: verifies that there are no double values within any column
//Expected: all values within a column are different
bool Tester::testInitCardNoDoubleInColumn(){
    Bingo card(CARDROWS, CARDCOLS, MINVAL, MAXVAL);
 
    for (int j = 0; j < CARDCOLS; j++){
        for (int row1 = 0; row1 < CARDROWS; row1++){
            for (int row2 = row1 + 1; row2 < CARDROWS; row2++){
                if (card.m_card[row1][j].getVal() == card.m_card[row2][j].getVal()){
                    cout << FAIL_STATEMENT << "testInitCardNoDoubleInColumn" << endl;
                    return false;
                }
            }
        }
    }
    cout << PASS_STATEMENT << "testInitCardNoDoubleInColumn" << endl;
    return true;
}
 
//testInitCardNoDoubleOnCard
//Case: verifies that there are no double values anywhere on the whole card
//Expected: all card values are different
bool Tester::testInitCardNoDoubleOnCard(){
    Bingo card(CARDROWS, CARDCOLS, MINVAL, MAXVAL);
 
    vector<int> values;
    for (int i = 0; i < CARDROWS; i++){
        for (int j = 0; j < CARDCOLS; j++){
            values.push_back(card.m_card[i][j].getVal());
        }
    }
 
    for (int i = 0; i < (int)values.size(); i++){
        for (int j = i + 1; j < (int)values.size(); j++){
            if (values[i] == values[j]){
                cout << FAIL_STATEMENT << "testInitCardNoDoubleOnCard" << endl;
                return false;
            }
        }
    }
    cout << PASS_STATEMENT << "testInitCardNoDoubleOnCard" << endl;
    return true;
}
 
//testInitCardEmptyError
//Case: calls initCard() on a default or empty object
//Expected: returns false and the object stays empty
bool Tester::testInitCardEmptyError(){
    Bingo card;
 
    bool result = card.initCard();
 
    if (result || card.m_card != nullptr){
        cout << FAIL_STATEMENT << "testInitCardEmptyError" << endl;
        return false;
    }
    cout << PASS_STATEMENT << "testInitCardEmptyError" << endl;
    return true;
}

//testPlayWinNormal
//Case: row wins, a 2x5 card, rndBalls has all 5 row 0 values and then 2 row 1 values, with numDraws equal to the full ball range
//Expected: play returns 5, only 5 cells are EMPTYCELL, row 0 is empty, and row 1 doesn't change 
bool Tester::testPlayWinNormal(){
    Bingo card(2, 5, 11, 20);
    int totalBalls = 10;
 
    vector<int> rndBalls;
    for (int j = 0; j < 5; j++){
        rndBalls.push_back(card.m_card[0][j].getVal());
    }
    rndBalls.push_back(card.m_card[1][0].getVal());
    rndBalls.push_back(card.m_card[1][1].getVal());
 
    int result = card.play(totalBalls, rndBalls);
 
    if (result != 5){
        cout << FAIL_STATEMENT << "testPlayWinNormal" << endl;
        return false;
    }
 
    int emptyCount = 0;
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 5; j++){
            if (card.m_card[i][j].getVal() == EMPTYCELL) emptyCount++;
        }
    }
    if (emptyCount != 5){
        cout << FAIL_STATEMENT << "testPlayWinNormal" << endl;
        return false;
    }
 
    bool row0Empty = true;
    for (int j = 0; j < 5; j++){
        if (card.m_card[0][j].getVal() != EMPTYCELL) row0Empty = false;
    }
    bool row1Changed = false;
    for (int j = 0; j < 5; j++){
        if (card.m_card[1][j].getVal() == EMPTYCELL) row1Changed = true;
    }
    if (!row0Empty || row1Changed){
        cout << FAIL_STATEMENT << "testPlayWinNormal" << endl;
        return false;
    }
 
    cout << PASS_STATEMENT << "testPlayWinNormal" << endl;
    return true;
}
 
//testPlayColumnWin
//Case: column wins, a 2x5 card, rndBalls has both values of column 0 first, then 2 more values from other columns
//Expected: play returns only 2 and stops before getting to the extra balls
bool Tester::testPlayColumnWin(){
    Bingo card(2, 5, 11, 20);
    int totalBalls = 10;
 
    vector<int> rndBalls;
    rndBalls.push_back(card.m_card[0][0].getVal());
    rndBalls.push_back(card.m_card[1][0].getVal());
    rndBalls.push_back(card.m_card[0][1].getVal());
    rndBalls.push_back(card.m_card[0][2].getVal());
 
    int result = card.play(totalBalls, rndBalls);
 
    if (result != 2){
        cout << FAIL_STATEMENT << "testPlayColumnWin" << endl;
        return false;
    }
 
    if (card.m_card[0][0].getVal() != EMPTYCELL || card.m_card[1][0].getVal() != EMPTYCELL){
        cout << FAIL_STATEMENT << "testPlayColumnWin" << endl;
        return false;
    }
    if (card.m_card[0][1].getVal() == EMPTYCELL || card.m_card[0][2].getVal() == EMPTYCELL){
        cout << FAIL_STATEMENT << "testPlayColumnWin" << endl;
        return false;
    }
 
    cout << PASS_STATEMENT << "testPlayColumnWin" << endl;
    return true;
}
 
//testPlayLessThanRange
//Case: numDraws is less than the full ball range, even though the balls passed in would complete a row if all were processed
//Expected: doesn't stop early and only the balls actually processed count, returns only 3 marks and cells
bool Tester::testPlayLessThanRange(){
    Bingo card(2, 5, 11, 20);
 
    vector<int> rndBalls;
    for (int j = 0; j < 5; j++){
        rndBalls.push_back(card.m_card[0][j].getVal());
    }
 
    int result = card.play(3, rndBalls);
 
    if (result != 3){
        cout << FAIL_STATEMENT << "testPlayLessThanRange" << endl;
        return false;
    }
 
    int emptyCount = 0;
    for (int j = 0; j < 5; j++){
        if (card.m_card[0][j].getVal() == EMPTYCELL) emptyCount++;
    }
    if (emptyCount != 3){
        cout << FAIL_STATEMENT << "testPlayLessThanRange" << endl;
        return false;
    }
 
    cout << PASS_STATEMENT << "testPlayLessThanRange" << endl;
    return true;
}
 
//testPlayNumDrawsError
//Case: numDraws is greater than the actual ball range
//Expected: no draws happen, returns 0, card and trackers don't change
bool Tester::testPlayNumDrawsError(){
    Bingo card(2, 5, 11, 20);
    int totalBalls = 10;
 
    vector<int> rndBalls;
    for (int i = 11; i <= 20; i++){
        rndBalls.push_back(i);
    }
 
    int result = card.play(totalBalls + 1, rndBalls);
 
    if (result != 0){
        cout << FAIL_STATEMENT << "testPlayNumDrawsError" << endl;
        return false;
    }
 
    bool untouched = true;
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 5; j++){
            if (card.m_card[i][j].getVal() == EMPTYCELL) untouched = false;
        }
    }
    for (int i = 0; i < 2; i++){
        if (card.m_trackRows[i] != 0) untouched = false;
    }
    for (int i = 0; i < 5; i++){
        if (card.m_trackCols[i] != 0) untouched = false;
    }
    if (!untouched){
        cout << FAIL_STATEMENT << "testPlayNumDrawsError" << endl;
        return false;
    }
 
    cout << PASS_STATEMENT << "testPlayNumDrawsError" << endl;
    return true;
}
 
//testPlayBallVectorError
//Case: creates rndBalls vector that's bigger than the actual ball range
//Expected: no draws happen, returns 0
bool Tester::testPlayBallVectorError(){
    Bingo card(2, 5, 11, 20);
 
    vector<int> rndBalls;
    for (int i = 11; i <= 20; i++){
        rndBalls.push_back(i);
    }
    rndBalls.push_back(11);
 
    int result = card.play(5, rndBalls);
 
    if (result != 0){
        cout << FAIL_STATEMENT << "testPlayBallVectorError" << endl;
        return false;
    }
 
    cout << PASS_STATEMENT << "testPlayBallVectorError" << endl;
    return true;
}

//testDrawBallsNormal
//Case: draws balls on a valid populated object
//Expected: correct count and every value is within [minBallVal, maxBallVal]
bool Tester::testDrawBallsNormal(){
    Bingo card(CARDROWS, CARDCOLS, MINVAL, MAXVAL);
 
    vector<int> balls = card.drawBalls();
 
    if ((int)balls.size() != (MAXVAL - MINVAL + 1)){
        cout << FAIL_STATEMENT << "testDrawBallsNormal" << endl;
        return false;
    }
    for (int i = 0; i < (int)balls.size(); i++){
        if (balls[i] < MINVAL || balls[i] > MAXVAL){
            cout << FAIL_STATEMENT << "testDrawBallsNormal" << endl;
            return false;
        }
    }
    cout << PASS_STATEMENT << "testDrawBallsNormal" << endl;
    return true;
}
 
//testDrawBallsNoDouble
//Case: verifies that the balls drawn have no double values
//Expected: every ball number appear only once
bool Tester::testDrawBallsNoDouble(){
    Bingo card(CARDROWS, CARDCOLS, MINVAL, MAXVAL);
 
    vector<int> balls = card.drawBalls();
 
    for (int i = 0; i < (int)balls.size(); i++){
        for (int j = i + 1; j < (int)balls.size(); j++){
            if (balls[i] == balls[j]){
                cout << FAIL_STATEMENT << "testDrawBallsNoDouble" << endl;
                return false;
            }
        }
    }
    cout << PASS_STATEMENT << "testDrawBallsNoDouble" << endl;
    return true;
}
 
//testDrawBallsError
//Case: calls drawBalls() on a default or empty object
//Expected: returns an empty vector
bool Tester::testDrawBallsError(){
    Bingo card;
 
    vector<int> balls = card.drawBalls();
 
    if (balls.size() != 0){
        cout << FAIL_STATEMENT << "testDrawBallsError" << endl;
        return false;
    }
    cout << PASS_STATEMENT << "testDrawBallsError" << endl;
    return true;
}

//testAssignNormal
//Case: assigns a populated object to a default or empty object
//Expected: creates deep copy with matching values but with separate memory addresses
bool Tester::testAssignNormal(){
    Bingo card1(10, 5, MINVAL, MAXVAL);
    Bingo card2;
 
    card2 = card1;
 
    if (card2.m_numRows != card1.m_numRows || card2.m_numCols != card1.m_numCols || card2.m_minBallVal != card1.m_minBallVal || card2.m_maxBallVal != card1.m_maxBallVal || card2.m_helperSize != card1.m_helperSize){
        cout << FAIL_STATEMENT << "testAssignNormal" << endl;
        return false;
    }
 
    if (card2.m_card == card1.m_card || card2.m_helper == card1.m_helper || card2.m_trackRows == card1.m_trackRows || card2.m_trackCols == card1.m_trackCols){
        cout << FAIL_STATEMENT << "testAssignNormal" << endl;
        return false;
    }
 
    for (int i = 0; i < card1.m_numRows; i++){
        for (int j = 0; j < card1.m_numCols; j++){
            if (!(card1.m_card[i][j] == card2.m_card[i][j])){
                cout << FAIL_STATEMENT << "testAssignNormal" << endl;
                return false;
            }
        }
    }
    for (int i = 0; i < card1.m_helperSize; i++){
        if (!(card1.m_helper[i] == card2.m_helper[i])){
            cout << FAIL_STATEMENT << "testAssignNormal" << endl;
            return false;
        }
    }
    for (int i = 0; i < card1.m_numRows; i++){
        if (card1.m_trackRows[i] != card2.m_trackRows[i]){
            cout << FAIL_STATEMENT << "testAssignNormal" << endl;
            return false;
        }
    }
    for (int i = 0; i < card1.m_numCols; i++){
        if (card1.m_trackCols[i] != card2.m_trackCols[i]){
            cout << FAIL_STATEMENT << "testAssignNormal" << endl;
            return false;
        }
    }
 
    cout << PASS_STATEMENT << "testAssignNormal" << endl;
    return true;
}
 
//testAssignSelfAssign
//Case: tests for self-assignment, card = card
//Expected: object is not changed and memory addresses are the same
bool Tester::testAssignSelfAssign(){
    Bingo card(10, 5, MINVAL, MAXVAL);
 
    Cell** oldCard = card.m_card;
    Cell* oldHelper = card.m_helper;
    int* oldTrackRows = card.m_trackRows;
    int* oldTrackCols = card.m_trackCols;
    int oldRows = card.m_numRows;
    int oldCols = card.m_numCols;
 
    card = card;
 
    if (card.m_card != oldCard || card.m_helper != oldHelper || card.m_trackRows != oldTrackRows || card.m_trackCols != oldTrackCols){
        cout << FAIL_STATEMENT << "testAssignSelfAssign" << endl;
        return false;
    }
    if (card.m_numRows != oldRows || card.m_numCols != oldCols){
        cout << FAIL_STATEMENT << "testAssignSelfAssign" << endl;
        return false;
    }
 
    cout << PASS_STATEMENT << "testAssignSelfAssign" << endl;
    return true;
}
 
//testAssignChainedAssigned
//Case: tests for chained assignment, card3 = card2 = card1
//Expected: all three have equal values but have different memory
bool Tester::testAssignChainedAssigned(){
    Bingo card1(5, 5, MINVAL, MAXVAL);
    Bingo card2, card3;
 
    card3 = card2 = card1;
 
    if (card2.m_numRows != card1.m_numRows || card3.m_numRows != card1.m_numRows){
        cout << FAIL_STATEMENT << "testAssignChainedAssigned" << endl;
        return false;
    }
 
    if (card2.m_card == card1.m_card || card3.m_card == card1.m_card || card3.m_card == card2.m_card){
        cout << FAIL_STATEMENT << "testAssignChainedAssigned" << endl;
        return false;
    }
 
    for (int i = 0; i < card1.m_numRows; i++){
        for (int j = 0; j < card1.m_numCols; j++){
            if (!(card1.m_card[i][j] == card2.m_card[i][j]) || !(card1.m_card[i][j] == card3.m_card[i][j])){
                cout << FAIL_STATEMENT << "testAssignChainedAssigned" << endl;
                return false;
            }
        }
    }
 
    cout << PASS_STATEMENT << "testAssignChainedAssigned" << endl;
    return true;
}
 
//testAssignEmptyToNormal
//Case: assigns an a default or empty object to a populated object
//Expected: the populated object is empty, matching the rhs
bool Tester::testAssignEmptyToNormal(){
    Bingo card1(5, 5, MINVAL, MAXVAL);
    Bingo card2;
 
    card1 = card2;
 
    if (card1.m_card != nullptr || card1.m_helper != nullptr || card1.m_trackRows != nullptr || card1.m_trackCols != nullptr){
        cout << FAIL_STATEMENT << "testAssignEmptyToNormal" << endl;
        return false;
    }
    if (card1.m_numRows != 0 || card1.m_numCols != 0 || card1.m_helperSize != 0 || card1.m_minBallVal != 0 || card1.m_maxBallVal != 0){
        cout << FAIL_STATEMENT << "testAssignEmptyToNormal" << endl;
        return false;
    }
 
    cout << PASS_STATEMENT << "testAssignEmptyToNormal" << endl;
    return true;
}
 
//testAssignNormalToEmpty
//Case: assigns a populated object into a default or empty object
//Expected: the empty object becomes a deep copy of the populated one
bool Tester::testAssignNormalToEmpty(){
    Bingo card1;
    Bingo card2(5, 5, MINVAL, MAXVAL);
 
    card1 = card2;
 
    if (card1.m_card == nullptr || card1.m_numRows != card2.m_numRows || card1.m_numCols != card2.m_numCols){
        cout << FAIL_STATEMENT << "testAssignNormalToEmpty" << endl;
        return false;
    }
    if (card1.m_card == card2.m_card){
        cout << FAIL_STATEMENT << "testAssignNormalToEmpty" << endl;
        return false;
    }
 
    for (int i = 0; i < card2.m_numRows; i++){
        for (int j = 0; j < card2.m_numCols; j++){
            if (!(card1.m_card[i][j] == card2.m_card[i][j])){
                cout << FAIL_STATEMENT << "testAssignNormalToEmpty" << endl;
                return false;
            }
        }
    }
 
    cout << PASS_STATEMENT << "testAssignNormalToEmpty" << endl;
    return true;
}

//testClearNormal
//Case: clears a populated object
//Expected: object matches a new default or empty object
bool Tester::testClearNormal(){
    Bingo card(5, 5, MINVAL, MAXVAL);
 
    card.clear();
 
    bool result = (card.m_card == nullptr) && (card.m_helper == nullptr) && (card.m_trackRows == nullptr) && (card.m_trackCols == nullptr) && (card.m_numRows == 0) && (card.m_numCols == 0) && (card.m_helperSize == 0) && (card.m_minBallVal == 0) && (card.m_maxBallVal == 0);
 
    if (!result){
        cout << FAIL_STATEMENT << "testClearNormal" << endl;
        return false;
    }
    cout << PASS_STATEMENT << "testClearNormal" << endl;
    return true;
}
 
//testClearEmpty
//Case: clears an already default or empty object
//Expected: object stays empty and there is no crash
bool Tester::testClearEmpty(){
    Bingo card;
 
    card.clear();
 
    if (card.m_card != nullptr || card.m_numRows != 0 || card.m_numCols != 0){
        cout << FAIL_STATEMENT << "testClearEmpty" << endl;
        return false;
    }
    cout << PASS_STATEMENT << "testClearEmpty" << endl;
    return true;
}
 
//testClearReuse
//Case: clears then reCreateCard which confirms the object can be reused after
//Expected: reCreateCard works and makes a new, valid, populated card
bool Tester::testClearReuse(){
    Bingo card(5, 5, MINVAL, MAXVAL);
 
    card.clear();
    bool created = card.reCreateCard(10, 5, MINVAL, MAXVAL);
 
    if (!created || card.m_numRows != 10 || card.m_numCols != 5){
        cout << FAIL_STATEMENT << "testClearReuse" << endl;
        return false;
    }
 
    int value = card.m_card[0][0].getVal();
    if (value < MINVAL || value > MINVAL + 14){
        cout << FAIL_STATEMENT << "testClearReuse" << endl;
        return false;
    }
 
    cout << PASS_STATEMENT << "testClearReuse" << endl;
    return true;
}

//testInitCardMinRowsEdge
//Case: creates minimum valid row count, the smallest non-square shape which can expose a numRows/numCols loop bound bug
//Expected: every cell's value falls in the column range, matches the row/col position, maps back correctly, and has no doubles in a column or the card
bool Tester::testInitCardMinRowsEdge(){
    Bingo card(2, CARDCOLS, MINVAL, MAXVAL);
    int width = (MAXVAL - MINVAL + 1) / CARDCOLS;
 
    for (int j = 0; j < CARDCOLS; j++){
        int colMin = MINVAL + (j * width);
        int colMax = colMin + width - 1;
        for (int i = 0; i < 2; i++){
            int value = card.m_card[i][j].getVal();
            if (value < colMin || value > colMax){
                cout << FAIL_STATEMENT << "testInitCardMinRowsEdge" << endl;
                return false;
            }
            if (card.m_card[i][j].getRow() != i || card.m_card[i][j].getCol() != j){
                cout << FAIL_STATEMENT << "testInitCardMinRowsEdge" << endl;
                return false;
            }
            int index = value - card.m_minBallVal;
            if (card.m_helper[index].getRow() != i || card.m_helper[index].getCol() != j || card.m_helper[index].getVal() != value){
                cout << FAIL_STATEMENT << "testInitCardMinRowsEdge" << endl;
                return false;
            }
        }
        if (card.m_card[0][j].getVal() == card.m_card[1][j].getVal()){
            cout << FAIL_STATEMENT << "testInitCardMinRowsEdge" << endl;
            return false;
        }
    }
 
    vector<int> values;
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < CARDCOLS; j++){
            values.push_back(card.m_card[i][j].getVal());
        }
    }
    for (int i = 0; i < (int)values.size(); i++){
        for (int j = i + 1; j < (int)values.size(); j++){
            if (values[i] == values[j]){
                cout << FAIL_STATEMENT << "testInitCardMinRowsEdge" << endl;
                return false;
            }
        }
    }
 
    cout << PASS_STATEMENT << "testInitCardMinRowsEdge" << endl;
    return true;
}
 
//testInitCardNotSquareFull
//Case: creates 10 rows x 5 cols card and checks everything including the range, position, helper mapping, and doubles, on a card other than the 5x5 card
//Expected: every cell passes all the checks
bool Tester::testInitCardNotSquareFull(){
    Bingo card(2 * CARDROWS, CARDCOLS, MINVAL, MAXVAL);
    int width = (MAXVAL - MINVAL + 1) / CARDCOLS;
    int rows = 2 * CARDROWS;
 
    for (int j = 0; j < CARDCOLS; j++){
        int colMin = MINVAL + (j * width);
        int colMax = colMin + width - 1;
        for (int i = 0; i < rows; i++){
            int value = card.m_card[i][j].getVal();
            if (value < colMin || value > colMax){
                cout << FAIL_STATEMENT << "testInitCardNotSquareFull" << endl;
                return false;
            }
            if (card.m_card[i][j].getRow() != i || card.m_card[i][j].getCol() != j){
                cout << FAIL_STATEMENT << "testInitCardNotSquareFull" << endl;
                return false;
            }
            int index = value - card.m_minBallVal;
            if (card.m_helper[index].getRow() != i || card.m_helper[index].getCol() != j || card.m_helper[index].getVal() != value){
                cout << FAIL_STATEMENT << "testInitCardNotSquareFull" << endl;
                return false;
            }
        }
        for (int row1 = 0; row1 < rows; row1++){
            for (int row2 = row1 + 1; row2 < rows; row2++){
                if (card.m_card[row1][j].getVal() == card.m_card[row2][j].getVal()){
                    cout << FAIL_STATEMENT << "testInitCardNotSquareFull" << endl;
                    return false;
                }
            }
        }
    }
 
    vector<int> values;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < CARDCOLS; j++){
            values.push_back(card.m_card[i][j].getVal());
        }
    }
    for (int i = 0; i < (int)values.size(); i++){
        for (int j = i + 1; j < (int)values.size(); j++){
            if (values[i] == values[j]){
                cout << FAIL_STATEMENT << "testInitCardNotSquareFull" << endl;
                return false;
            }
        }
    }
 
    cout << PASS_STATEMENT << "testInitCardNotSquareFull" << endl;
    return true;
}
 
//testPlayEmptyCellCount
//Case: after a winning play() call, counts every EMPTYCELL on the card
//Expected: total EMPTYCELL cells on the card equals the value that play() returned
bool Tester::testPlayEmptyCellCount(){
    Bingo card(2, 5, 11, 20);
 
    vector<int> rndBalls;
    rndBalls.push_back(card.m_card[0][0].getVal());
    rndBalls.push_back(card.m_card[1][0].getVal());
 
    int result = card.play(10, rndBalls);
 
    int emptyCount = 0;
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 5; j++){
            if (card.m_card[i][j].getVal() == EMPTYCELL) emptyCount++;
        }
    }
 
    if (emptyCount != result){
        cout << FAIL_STATEMENT << "testPlayEmptyCellCount" << endl;
        return false;
    }
 
    cout << PASS_STATEMENT << "testPlayEmptyCellCount" << endl;
    return true;
}
 
//testPlayOnlyOneLine
//Case: after a row-win play() call, checks that only one row is fully EMPTYCELL and makes sure no column is also fully EMPTYCELL
//Expected: only the winning row is complete, not zero, not more than one, and no column completes at the same time
bool Tester::testPlayOnlyOneLine(){
    Bingo card(2, 5, 11, 20);
 
    vector<int> rndBalls;
    for (int j = 0; j < 5; j++){
        rndBalls.push_back(card.m_card[0][j].getVal());
    }
 
    card.play(10, rndBalls);
 
    int fullRows = 0;
    for (int i = 0; i < 2; i++){
        bool rowFull = true;
        for (int j = 0; j < 5; j++){
            if (card.m_card[i][j].getVal() != EMPTYCELL) rowFull = false;
        }
        if (rowFull) fullRows++;
    }
 
    int fullCols = 0;
    for (int j = 0; j < 5; j++){
        bool colFull = true;
        for (int i = 0; i < 2; i++){
            if (card.m_card[i][j].getVal() != EMPTYCELL) colFull = false;
        }
        if (colFull) fullCols++;
    }
 
    if (fullRows != 1 || fullCols != 0){
        cout << FAIL_STATEMENT << "testPlayOnlyOneLine" << endl;
        return false;
    }
 
    cout << PASS_STATEMENT << "testPlayOnlyOneLine" << endl;
    return true;
}
 
//testPlayBallVectorNoChange
//Case: rndBalls vector is larger than the actual ball range which is different from the numDraws too big check
//Expected: card and trackers are are not changed after the rejected call
bool Tester::testPlayBallVectorNoChange(){
    Bingo card(2, 5, 11, 20);
 
    vector<int> rndBalls;
    for (int i = 11; i <= 20; i++){
        rndBalls.push_back(i);
    }
    rndBalls.push_back(11);
 
    card.play(5, rndBalls);
 
    bool notChanged = true;
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 5; j++){
            if (card.m_card[i][j].getVal() == EMPTYCELL) notChanged = false;
        }
    }
    for (int i = 0; i < 2; i++){
        if (card.m_trackRows[i] != 0) notChanged = false;
    }
    for (int i = 0; i < 5; i++){
        if (card.m_trackCols[i] != 0) notChanged = false;
    }
 
    if (!notChanged){
        cout << FAIL_STATEMENT << "testPlayBallVectorNoChange" << endl;
        return false;
    }
 
    cout << PASS_STATEMENT << "testPlayBallVectorNoChange" << endl;
    return true;
}

int main() {
    Tester test; 

    test.testDefaultConstructorNormal();

    test.testConstructorNormal();
    test.testConstructorNotSquare();
    test.testConstructorMinRowsEdge();
    test.testConstructorMaxRowsEdge();
    test.testConstructorRowsError();
    test.testConstructorColError();
    test.testConstructorRange();
    test.testConstructorMinMax();

    test.testRecreateNormal();
    test.testRecreateWOClear(); 
    test.testRecreatePopulated();

    test.testInitCardRange();
    test.testInitCardNotSquare();
    test.testInitCardPosition();
    test.testInitCardHelper();
    test.testInitCardNoDoubleInColumn();
    test.testInitCardNoDoubleOnCard();
    test.testInitCardEmptyError();

    test.testPlayWinNormal();
    test.testPlayColumnWin();
    test.testPlayLessThanRange();
    test.testPlayNumDrawsError();
    test.testPlayBallVectorError();

    test.testDrawBallsNormal();
    test.testDrawBallsNoDouble();
    test.testDrawBallsError();

    test.testAssignNormal();
    test.testAssignSelfAssign();
    test.testAssignChainedAssigned();
    test.testAssignEmptyToNormal();
    test.testAssignNormalToEmpty();

    test.testClearNormal();
    test.testClearEmpty();
    test.testClearReuse();

    test.testInitCardMinRowsEdge();
    test.testInitCardNotSquareFull();
    test.testPlayEmptyCellCount();
    test.testPlayOnlyOneLine();
    test.testPlayBallVectorNoChange();

    return 0;
}