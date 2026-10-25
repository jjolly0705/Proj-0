// UMBC - CMSC 341 - Fall 2026 - Proj0
#include "bingo.h"
Bingo::Bingo(){
    m_trackCols = nullptr;
    m_trackRows = nullptr;
    m_helper = nullptr;
    m_helperSize = 0;
    m_card = nullptr;
    m_numRows = 0;
    m_numCols = 0;
    m_minBallVal = 0;
    m_maxBallVal = 0;
}

Bingo::Bingo(int rows, int columns, int min, int max){
    m_trackCols = nullptr;
    m_trackRows = nullptr;
    m_helper = nullptr;
    m_helperSize = 0;
    m_card = nullptr;
    m_numRows = 0;
    m_numCols = 0;
    m_minBallVal = 0;
    m_maxBallVal = 0;

    reCreateCard(rows, columns, min, max); //better than copying and then breaking it again
}

bool Bingo::reCreateCard(int rows, int columns, int min, int max){
    if (rows < 2 || rows > 15 || columns != CARDCOLS) {
        return false;
    }
    if (min < MINVAL || max > MAXVAL || min > max){
        return false;
    }
    if ((max- min + 1) % CARDCOLS != 0) {
        return false;
    }
    if (m_card != nullptr || m_helper != nullptr || m_trackRows != nullptr || m_trackCols != nullptr) {
        return false;
    }

    m_numRows = rows;
    m_numCols = columns;
    m_minBallVal = min;
    m_maxBallVal = max;

    m_trackRows = new int[m_numRows]();
    m_trackCols = new int[m_numCols]();
    m_helperSize = (max - min) + 1;
    m_helper = new Cell[m_helperSize]();

    m_card = new Cell* [m_numRows];
    for (int i = 0; i < m_numRows; i++) {
        m_card[i] = new Cell[m_numCols];
    }

    if(!initCard()) {
        clear();
        return false;
    }

    return true;
}

Bingo::~Bingo(){
    clear();
}

void Bingo::clear(){
    if (m_card != nullptr) {
        for (int i = 0; i < m_numRows; ++i) {
            delete[] m_card[i];
        }
        delete[] m_card;
        m_card = nullptr;
    }

    delete[] m_trackCols;
    m_trackCols = nullptr;
    delete[] m_trackRows;
    m_trackRows = nullptr;
    delete[] m_helper;
    m_helper = nullptr;  
    
    m_helperSize = 0;
    m_numRows = 0;
    m_numCols = 0;
    m_minBallVal = 0;
    m_maxBallVal = 0;
}

bool Bingo::initCard(){
    if (m_card == nullptr || m_trackRows == nullptr || m_trackCols == nullptr) {
        return false;
    }
    for (int i = 0; i < m_numRows; ++i) {
        if (m_card[i] == nullptr) {
            return false;
        }
    }
    if (m_numRows <= 0 || m_numCols <= 0 || m_helperSize <= 0) {
        return false;
    }
    for (int i = 0; i < m_numRows; i++) {
        m_trackRows[i] = 0;
    }
    for (int i = 0; i < m_numCols; i++) {
        m_trackCols[i] = 0;
    }
    if (m_helper != nullptr) {
        for (int i = 0; i < m_helperSize; i++) {
            m_helper[i] = 0;
        }
    }

    int valueInEachCol = m_helperSize / m_numCols;
    for (int columnVals = 0; columnVals < m_numCols; columnVals++) {
        int columnMin = m_minBallVal + (columnVals * valueInEachCol);
        int columnMax = (columnMin + valueInEachCol) - 1;

        Random num(columnMin, columnMax, SHUFFLE);
        vector<int> randomColNums;
        num.getShuffle(randomColNums);

        for (int rowVals = 0; rowVals < m_numRows; rowVals++) {
            int value = randomColNums[rowVals];

            m_card[rowVals][columnVals].setRow(rowVals);
            m_card[rowVals][columnVals].setCol(columnVals);
            m_card[rowVals][columnVals].setVal(value);

            int helperVal = value - m_minBallVal;
            m_helper[helperVal].setRow(rowVals);
            m_helper[helperVal].setCol(columnVals);
            m_helper[helperVal].setVal(value);
        }
    }
    return true;
}

vector<int> Bingo::drawBalls(){
    vector<int> ballsDrawn;

    if (m_minBallVal >= m_maxBallVal || m_minBallVal <= 0) {
        return ballsDrawn;
    }

    Random num(m_minBallVal, m_maxBallVal, SHUFFLE);
    num.getShuffle(ballsDrawn);

    return ballsDrawn;
}

int Bingo::play(int numDraws, vector<int> rndBalls){
    int allTheBalls = (m_maxBallVal - m_minBallVal) + 1;

    if (numDraws > allTheBalls || (int)rndBalls.size() > allTheBalls) {
        return 0;
    }
    if (m_trackRows == nullptr || m_trackCols == nullptr || m_numRows <= 0 || m_numCols <= 0) {
        return 0;
    }

    int count = 0;
    int ballsProcessed = numDraws;
    if ((int)rndBalls.size() < ballsProcessed) {
        ballsProcessed = (int)rndBalls.size();
    }

    for (int i = 0; i < ballsProcessed; i++) {
        int drawnBall = rndBalls[i];
        if(drawnBall < m_minBallVal || drawnBall > m_maxBallVal) {
            continue;
        }
        int helperIndex = drawnBall - m_minBallVal;

        if(!m_helper[helperIndex].isEmpty()) {
            int row = m_helper[helperIndex].getRow();
            int column = m_helper[helperIndex].getCol();
            m_card[row][column].setVal(EMPTYCELL);
            m_helper[helperIndex].setVal(EMPTYCELL);

            count++;

            m_trackRows[row]++;
            m_trackCols[column]++;

            if(numDraws == allTheBalls) {
                bool ifRowWins = (m_trackRows[row] == m_numCols);
                bool ifColWins = (m_trackCols[column] == m_numRows);

                if(ifRowWins || ifColWins) {
                    return count;
                }
            }
        }
    } 
    return count;
}

const Bingo & Bingo::operator=(const Bingo & rhs){
    if (this == &rhs) {
        return *this;
    }

    if (m_card != nullptr) {
        for (int i = 0; i < m_numRows; i++) {
            delete[] m_card[i];
        }
        delete[] m_card;
        m_card = nullptr;
    }
    delete[] m_trackCols;
    m_trackCols = nullptr;

    delete[] m_trackRows;
    m_trackRows = nullptr;

    delete[] m_helper;
    m_helper = nullptr;

    m_numRows = rhs.m_numRows;
    m_numCols = rhs.m_numCols;
    m_minBallVal = rhs.m_minBallVal;
    m_maxBallVal = rhs.m_maxBallVal;
    m_helperSize = rhs.m_helperSize;

    if (rhs.m_trackRows != nullptr && m_numRows > 0) {
        m_trackRows = new int[m_numRows];
        for (int i = 0; i < m_numRows; i++) {
            m_trackRows[i] = rhs.m_trackRows[i];
        }
    }
    if (rhs.m_trackCols != nullptr && m_numCols > 0) {
        m_trackCols = new int[m_numCols];
        for (int i = 0; i < m_numCols; i++) {
            m_trackCols[i] = rhs.m_trackCols[i];
        }
    }
    if (rhs.m_helper != nullptr && m_helperSize > 0) {
        m_helper = new Cell[m_helperSize];
        for (int i = 0; i < m_helperSize; i++) {
            m_helper[i] = rhs.m_helper[i];
        }
    }
    if (rhs.m_card != nullptr && m_numRows > 0 && m_numCols > 0) {
        m_card = new Cell*[m_numRows];
        for (int i = 0; i < m_numRows; i++) {
            m_card[i] = new Cell[m_numCols];
            for (int j = 0; j < m_numCols; j++) {
                m_card[i][j] = rhs.m_card[i][j];
            }
        }
    }

    return *this;
}

// The dump function renders the card in the terminal
// This function is provided to facilitate debugging
// Using this function as a test case will not be accepted
void Bingo::dumpCard(){
    cout << "  ";
    cout << "\033[1;35m B   I   N   G   O\033[0m";    
    cout << endl;
    for (int i=1;i <= m_numRows;i++){
        if ((i < 10))
            cout << "\033[1;35m" << "0" << i << " \033[0m";
        else
            cout << "\033[1;35m" << i << " \033[0m";
        for (int j=1;j<=m_numCols;j++){
            if (m_card[i-1][j-1].getVal() == EMPTYCELL)
                cout << "\033[1;31m" << m_card[i-1][j-1].getVal() << "\033[0m" << "  ";
            else
                cout << m_card[i-1][j-1].getVal() << "  ";
        }
        cout << endl;
    }
    cout << endl;
}

// the overloaded equality operator for the Cell object
bool operator==(const Cell & lhs, const Cell & rhs){
    return ((lhs.m_col == rhs.m_col) &&
            (lhs.m_row == rhs.m_row) &&
            (lhs.m_value == rhs.m_value));
}