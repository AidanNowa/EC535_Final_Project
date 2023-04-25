#include <QtWidgets>

#include "mybutton.h"

#define maxSide  25
#define maxMines 99
int sideSize = 10;
int totalMines = 10;

//track which mouse button is clicked
bool rightClick, leftClick;
//used to store tile click values
int click[2];

class Minesweeper : public QWidget {

public:
    Minesweeper(QWidget *parent = nullptr) : QWidget(parent) {
            this -> setWindowTitle("Minesweeper");
            this->setFixedSize(300, 350);
            QVBoxLayout * mainlayout = new QVBoxLayout(this);
            QHBoxLayout * lcdlayout= new QHBoxLayout();

            lcdTimer = new QLCDNumber(this); //timer will increase until 999
            QTimer *timer = new QTimer(this);
            lcdTimer->setDigitCount(3);
            timer->setInterval(1000);
            lcdTimer->display(0);
            connect(timer, &QTimer::timeout, this, &Minesweeper::updateTimerDisplay);
            timer->start();
            lcdlayout->addWidget(lcdTimer);

            mineCounter = new QLCDNumber(this);  //counter start form 10 and change as play flag
            mineCounter->setDigitCount(3);
            lcdlayout->addWidget(mineCounter);
            mineCounter->display(numMines);

            for(int i = 0; i < 10; i++){
                for(int j = 0; j < 10; j++){
                    hiddenBoard[i][j] = new MyButton(this, false, false, false);
                }
            }
            //generate mine grid
            setMines(mines, hiddenBoard);

            gridlayout = new QGridLayout(); //initualize minefield
            gridlayout -> setSpacing(0);
            gridlayout -> setContentsMargins(0,0,0,0);
            for (int row = 0; row < numRows; ++row) {
                for (int col = 0; col < numCols; ++col) {
                    //check if matches grind


                    hiddenBoard[row][col]->setFixedSize(28,30);
                    hiddenBoard[row][col]->setProperty("row", row);
                    hiddenBoard[row][col]->setProperty("col", col);
                    connect( hiddenBoard[row][col], &MyButton::leftClicked, this, &Minesweeper::onButtonLeftClicked); //if leftclicked
                    connect( hiddenBoard[row][col], &MyButton::rightClicked, this, &Minesweeper::onButtonRightClicked); //if rightclicked

                    gridlayout->addWidget( hiddenBoard[row][col], row, col);
                }
            }
            mainlayout->addLayout(lcdlayout);
            mainlayout->addLayout(gridlayout);
            setLayout(mainlayout); //put lcd and grid together

        }

    //check if selected tile is a valid tile
    bool isValid(int row, int col){
        //return true if row and col are within range of 0-10
        return (row >= 0) && (row < sideSize) && (col >= 0) && (col < sideSize);
    }

    int countAdjMines(int row, int col){
        int count = 0;

        // For naming positions we use the classic number pad configuration
        // i.e. the clicked tile is "5"
        // before each mine check, check that adjacent tile is a valid tile
        // top left = positon 7
        if(isValid (row-1, col-1) == true){
            if(hiddenBoard[row-1][col-1]->getminestatus() == true){
                count++;
            }
        }
        // position 8
        if(isValid (row-1, col) == true){
            if(hiddenBoard[row-1][col]->getminestatus() == true){
                count++;
            }
        }
        // position 9
        if(isValid (row-1, col+1) == true){

            if(hiddenBoard[row-1][col+1]->getminestatus() == true){
                count++;
            }
        }
        // position 4
        if(isValid (row, col-1) == true){

            if(hiddenBoard[row][col-1]->getminestatus() == true){
                count++;
            }
        }
        // position 6
        if(isValid (row, col+1) == true){

            if(hiddenBoard[row][col+1]->getminestatus() == true){
                count++;
            }
        }
        // position 1
        if(isValid (row+1, col-1) == true){

            if(hiddenBoard[row+1][col-1]->getminestatus() == true){
                count++;
            }
        }
        // position 2
        if(isValid (row+1, col) == true){

            if(hiddenBoard[row+1][col]->getminestatus() == true){
                count++;
            }
        }
        // position 3
        if(isValid (row+1, col+1) == true){

            if(hiddenBoard[row+1][col+1]->getminestatus() == true){
                count++;
            }
        }

        return count;
    }

    bool playGame(int row, int col){
        qDebug() << "entered playGame" << row << " " << col;
        //base case for recusion
        if(hiddenBoard[row][col]->getflipstatus() == true){

            return false;
        }
        hiddenBoard[row][col]->setfliptrue();
        moveCount++;
        qDebug() << "past base case";

            // Did not click mine
            // calc number of adjacent mines and place on board
            int count = countAdjMines(row, col);
            qDebug() << "count " << count;
            if(count == 0){
                hiddenBoard[row][col]->setStyleSheet("background-color: black");
            }
            else if(count == 1){
                QPixmap pixmap("/home/aidannow/EC535/lab5/Working_Minesweeper/images/1.png");
                QIcon ButtonIcon(pixmap);
                hiddenBoard[row][col]->setIcon(ButtonIcon);
            }
            else if(count == 2){
                QPixmap pixmap("/home/aidannow/EC535/lab5/Working_Minesweeper/images/2.png");
                QIcon ButtonIcon(pixmap);
                hiddenBoard[row][col]->setIcon(ButtonIcon);
            }
            else if(count == 3){
                QPixmap pixmap("/home/aidannow/EC535/lab5/Working_Minesweeper/images/3.png");
                QIcon ButtonIcon(pixmap);
                hiddenBoard[row][col]->setIcon(ButtonIcon);
            }
            else if(count == 4){
                QPixmap pixmap("/home/aidannow/EC535/lab5/Working_Minesweeper/images/4.png");
                QIcon ButtonIcon(pixmap);
                hiddenBoard[row][col]->setIcon(ButtonIcon);
            }
            else if(count == 5){
                QPixmap pixmap("/home/aidannow/EC535/lab5/Working_Minesweeper/images/5.png");
                QIcon ButtonIcon(pixmap);
                hiddenBoard[row][col]->setIcon(ButtonIcon);
            }
            else if(count == 6){
                QPixmap pixmap("/home/aidannow/EC535/lab5/Working_Minesweeper/images/6.png");
                QIcon ButtonIcon(pixmap);
                hiddenBoard[row][col]->setIcon(ButtonIcon);
            }
            else if(count == 7){
                QPixmap pixmap("/home/aidannow/EC535/lab5/Working_Minesweeper/images/7.png");
                QIcon ButtonIcon(pixmap);
                hiddenBoard[row][col]->setIcon(ButtonIcon);
            }
            else if(count == 8){
                QPixmap pixmap("/home/aidannow/EC535/lab5/Working_Minesweeper/images/8.png");
                QIcon ButtonIcon(pixmap);
                hiddenBoard[row][col]->setIcon(ButtonIcon);
            }


            if(count == 0){
                // position 7
                if(isValid (row-1, col-1) == true){
                    // adjacent tile isnt mine, so click on it
                       playGame(row-1, col-1);
                }
                // position 8
                if(isValid (row-1, col) == true){
                        playGame(row-1, col);
                }
                // position 9
                if(isValid (row-1, col+1) == true){
                        playGame(row-1, col+1);
                }
                // position 4
                if(isValid (row, col-1) == true){

                        playGame(row, col-1);
                }
                // position 6
                if(isValid (row, col+1) == true){

                        playGame(row, col+1);

                }
                // position 1
                if(isValid (row+1, col-1) == true){

                        playGame(row+1, col-1);

                }
                // position 2
                if(isValid (row+1, col) == true){

                        playGame(row+1, col);

                }
                // position 3
                if(isValid (row+1, col+1) == true){
                        playGame(row+1, col+1);
                }
            }
            // no mine so game is not over
            return false;

    }

    void setMines(int mines[][2], MyButton * realBoard[][10]){
        bool mark[100];

        memset(mark, false, sizeof(mark));
        srand(time(nullptr));
        for(int i = 0; i < totalMines; ){
            int x = rand() % (10);
            int y = rand() % (10);


            //place mine if no mine has already been placed on this tile
            if(mark[x * 10 + y] == false){
                //row and column index
                mines[i][0] = x;
                mines[i][1] = y;

                //place mine
                realBoard[mines[i][0]][mines[i][1]]->changeminestatus();
                qDebug() << "mine at (" << mines[i][0] << ", " << mines[i][1] << ")";
                mark[x * 10 + y] = true;
                i++; //increment only after a mine has been successfully placed
            }
        }
        return;
    }


    //called when user left-clicks on a tile. reveals square and adjcaent ones without a mine
    void sweep(int i, int j) {
        qDebug() << "move count" << moveCount;

        qDebug() << "Sweep at (" << i << ", " << j << ")";

        //qDebug() << clickedButton->property("row").toInt() << " " << clickedButton->property("col").toInt();

        if(moveCount == 0){
            TARGET: if(hiddenBoard[i][j]->getminestatus() == true){
                qDebug() << "triggered";
                //if first move was mine, remove it and move it to next avaliable location
                for(int x = 0; x<10; x++){
                    for(int y = 0; y < 10; y++){
                        if(hiddenBoard[x][y]->getminestatus() == false){
                            hiddenBoard[x][y]->changeminestatus();
                            hiddenBoard[i][j]->changeminestatus();
                            goto TARGET;
                        }
                    }
                }
            }
        }
        //check if move was valid, if so increment as successful move
        if(isValid(i, j) && hiddenBoard[i][j]->getflipstatus() == false){
            if(hiddenBoard[i][j]->getminestatus() == true){
                reveal();
                return;
            }
            qDebug() << "Playing the Game!";
            playGame(i, j);


            //get if tile/surroundings are mine
        }
        //Game is won -- display victory
        if(moveCount == maxMoves){
            //victory display
            victory();
        }

    }
    //called when user right-clicks? on a tile. place flag on tile
    void mine(int i, int j) {
        qDebug() << "Mine at (" << i << ", " << j << ")";
        click[0] = i;
        click[1] = j;
    }
    void reveal(){
        qDebug() << "Game Over";
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 10; j++){
                if(hiddenBoard[i][j]->getminestatus() == true){
                     QPixmap pixmap("/home/aidannow/EC535/lab5/Working_Minesweeper/images/mine.png");
                     QIcon ButtonIcon(pixmap);
                     hiddenBoard[i][j]->setIcon(ButtonIcon);
                }
            }
        }
    }
    void victory(){
        qDebug() << "Victory";
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 10; j++){
                if(hiddenBoard[i][j]->getminestatus() == true){
                     QPixmap pixmap("/home/aidannow/EC535/lab5/Working_Minesweeper/images/checkmark.png");
                     QIcon ButtonIcon(pixmap);
                     hiddenBoard[i][j]->setIcon(ButtonIcon);
                }
            }
        }
    }

private slots:
    void updateTimerDisplay()
        {
            if(lcdTimer->intValue() < 999){
                int currentTime = lcdTimer->intValue() + 1;
                lcdTimer->display(currentTime);
            }
        }

    void onButtonLeftClicked() {
            MyButton *button = qobject_cast<MyButton *>(sender());
            int i = button->property("row").toInt();
            int j = button->property("col").toInt();
            //QPixmap pixmap("C:/Users/aidan/OneDrive/Documents/BU_Classes/2023_Spring/Embedded Systems/Lab5/images/1.png");
            //QIcon ButtonIcon(pixmap);
            //button->setIcon(ButtonIcon);
            if (QGuiApplication::keyboardModifiers() == Qt::NoModifier) {
                sweep(i, j);
            }
        }

    void onButtonRightClicked() {
        MyButton *button = qobject_cast<MyButton *>(sender());
                int i = button->property("row").toInt();
                int j = button->property("col").toInt();

                int minesLeft = mineCounter->intValue();
                if(minesLeft > 0 && !button->getflagstatus() && !button->getflipstatus()){ //if it is not fliped or flagged
                    button->changeflagstatus();
                    minesLeft--;
                    mineCounter->display(minesLeft);
                    QPixmap pixmap("C:/Users/aidan/OneDrive/Documents/BU_Classes/2023_Spring/Embedded Systems/Lab5/images/flag.png"); //set flag
                    QIcon ButtonIcon(pixmap);
                    button->setIcon(ButtonIcon);
                    if (QGuiApplication::keyboardModifiers() == Qt::NoModifier) {
                        mine(i, j);
                    }
                }else if(minesLeft < 10 && button->getflagstatus()){ //if it is flaged
                    button->changeflagstatus();
                    minesLeft++;
                    mineCounter->display(minesLeft);
                    button->setIcon(QIcon()); //reset
                }
    }


private:
    const int numRows = 10;
    const int numCols = 10;
    const int numMines = 10;
    int moveCount = 0;
    bool gameOver = false;
    int maxMoves = numRows * numCols - numMines;
    MyButton *hiddenBoard[10][10];
    int mines[10][2]; //stores (x,y) coordinates of all mines

    QGridLayout *gridlayout;
    QElapsedTimer timer;
    QLCDNumber *mineCounter;
    QLCDNumber *lcdTimer;
};

class MinesweeperStartingPage : public QWidget
{
public:
    MinesweeperStartingPage(QWidget *parent = nullptr) : QWidget(parent)
    {
        // Create the layout for the starting page
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->setAlignment(Qt::AlignCenter);
        layout->setContentsMargins(50, 50, 50, 50);

        // Create the title label
        QLabel *title = new QLabel(tr("Minesweeper"));
        QFont titleFont = title->font();
        titleFont.setPointSize(32);
        title->setFont(titleFont);
        layout->addWidget(title, 0, Qt::AlignCenter);

        // Create the subtitle label
        QLabel *subtitle = new QLabel(tr("Select a difficulty level:"));
        QFont subtitleFont = subtitle->font();
        subtitleFont.setPointSize(16);
        subtitle->setFont(subtitleFont);
        layout->addWidget(subtitle, 0, Qt::AlignCenter);

        // Create the difficulty buttons
        QHBoxLayout *buttonLayout = new QHBoxLayout;
        buttonLayout->setSpacing(50);
        buttonLayout->setContentsMargins(0, 30, 0, 0);

        QPushButton *beginnerButton = new QPushButton(tr("Beginner"));
        beginnerButton->setStyleSheet("background-color: green; color: black;");
        connect(beginnerButton, &QPushButton::clicked, this, &MinesweeperStartingPage::beginnerClicked);
        beginnerButton->setFixedWidth(100);
        buttonLayout->addWidget(beginnerButton, 0, Qt::AlignCenter);

        QPushButton *intermediateButton = new QPushButton(tr("Intermediate"));
        intermediateButton->setStyleSheet("background-color: yellow; color: black;");
        connect(intermediateButton, &QPushButton::clicked, this, &MinesweeperStartingPage::intermediateClicked);
        intermediateButton->setFixedWidth(100);
        buttonLayout->addWidget(intermediateButton, 0, Qt::AlignCenter);

        QPushButton *expertButton = new QPushButton(tr("Expert"));
        expertButton->setStyleSheet("background-color: red; color: black;");
        connect(expertButton, &QPushButton::clicked, this, &MinesweeperStartingPage::expertClicked);
        expertButton->setFixedWidth(100);
        buttonLayout->addWidget(expertButton, 0, Qt::AlignCenter);

        layout->addLayout(buttonLayout);
    }

signals:
    void beginnerClicked(){
        Minesweeper *minesweeper = new Minesweeper;
        minesweeper->show();
        close();
    }
    void intermediateClicked(){
        Minesweeper *minesweeper = new Minesweeper;
        minesweeper->show();
        close();
    }
    void expertClicked(){
        Minesweeper *minesweeper = new Minesweeper;
        minesweeper->show();
        close();
    }
};

/*
//update current board
void updateBoard(char myBoard[][10]){
    int i, j;

    for(i = 0; i < 10; i++){
        for(j = 0; j < 10; j++){

        }
    }
}

//check if selected tile is a valid tile
bool isValid(int row, int col){
    //return true if row and col are within range of 0-10
    return (row >= 0) && (row < sideSize) && (col >= 0) && (col < sideSize);
}

//check if selected tile is a mine
bool isMine(int row, int col, char board[][10]){
    if(board[row][col] == '*')
        return true;
    else
        return false;
}

int countAdjMines(int row, int col, int mines[][2], char realBoard[][10]){
    int count = 0;

    // For naming positions we use the classic number pad configuration
    // i.e. the clicked tile is "5"
    // before each mine check, check that adjacent tile is a valid tile
    // top left = positon 7
    if(isValid (row-1, col-1) == true){
        if(isMine(row-1, col-1, realBoard) == true){
            count++;
        }
    }
    // position 8
    if(isValid (row-1, col) == true){
        if(isMine(row-1, col, realBoard) == true){
            count++;
        }
    }
    // position 9
    if(isValid (row-1, col+1) == true){
        if(isMine(row-1, col+1, realBoard) == true){
            count++;
        }
    }
    // position 4
    if(isValid (row, col-1) == true){
        if(isMine(row, col-1, realBoard) == true){
            count++;
        }
    }
    // position 6
    if(isValid (row, col+1) == true){
        if(isMine(row, col+1, realBoard) == true){
            count++;
        }
    }
    // position 1
    if(isValid (row+1, col-1) == true){
        if(isMine(row+1, col-1, realBoard) == true){
            count++;
        }
    }
    // position 2
    if(isValid (row+1, col) == true){
        if(isMine(row+1, col, realBoard) == true){
            count++;
        }
    }
    // position 3
    if(isValid (row+1, col+1) == true){
        if(isMine(row+1, col+1, realBoard) == true){
            count++;
        }
    }

    return count;
}

//Recursive funtion used to play the game
bool playGame(char myBoard[][10], char realBoard[][10], int mines [][2],int row, int col){
    //base case for recusion
    if(myBoard[row][col] != '-'){
        return false;
    }

    int i;

    //if a mine was clicked, game over
    if(realBoard[row][col] == '*'){
        myBoard[row][col] = '*';
        qDebug() << "Mine found";

        for (i = 0; i < totalMines; i++){
            myBoard[mines[i][0]][mines[i][1]] = '*';
        }

        // add function to print over board
        //updateBoard(myBoard);
        return true;
    }
    else{
        // Did not click mine
        // calc number of adjacent mines and place on board
        int count = countAdjMines(row, col, mines, realBoard);

        myBoard[row][col] = count + '0';
        qDebug() << "Safe!";

        if(!count){

            if(isValid (row-1, col-1) == true){
                // adjacent tile isnt mine, so click on it
                if(isMine(row-1, col-1, realBoard) == false){
                    playGame(myBoard, realBoard, mines, row-1, col-1);
                }
            }
            // position 8
            if(isValid (row-1, col) == true){
                if(isMine(row-1, col, realBoard) == true){
                    playGame(myBoard, realBoard, mines, row-1, col);
                }
            }
            // position 9
            if(isValid (row-1, col+1) == true){
                if(isMine(row-1, col+1, realBoard) == true){
                    playGame(myBoard, realBoard, mines, row-1, col+1);
                }
            }
            // position 4
            if(isValid (row, col-1) == true){
                if(isMine(row, col-1, realBoard) == true){
                    playGame(myBoard, realBoard, mines, row, col-1);
                }
            }
            // position 6
            if(isValid (row, col+1) == true){
                if(isMine(row, col+1, realBoard) == true){
                    playGame(myBoard, realBoard, mines, row, col+1);
                }
            }
            // position 1
            if(isValid (row+1, col-1) == true){
                if(isMine(row+1, col-1, realBoard) == true){
                    playGame(myBoard, realBoard, mines, row+1, col-1);
                }
            }
            // position 2
            if(isValid (row+1, col) == true){
                if(isMine(row+1, col, realBoard) == true){
                    playGame(myBoard, realBoard, mines, row+1, col);
                }
            }
            // position 3
            if(isValid (row+1, col+1) == true){
                if(isMine(row+1, col+1, realBoard) == true){
                    playGame(myBoard, realBoard, mines, row+1, col+1);
                }
            }
        }
        // no mine so game is not over
        return false;
    }
}

// randomly place mines on board
void setMines(int mines[][2], char realBoard[][10]){
    bool mark[100];

    memset(mark, false, sizeof(mark));

    for(int i = 0; i < totalMines; ){
        int random = rand() % (100);
        int x = random / 10;
        int y = random % 10;

        //place mine if no mine has already been placed on this tile
        if(mark[random] == false){
            //row and column index
            mines[i][0] = x;
            mines[i][1] = y;

            //place mine
            realBoard[mines[i][0]][mines[i][1]] = '*';
            mark[random] = true;
            i++; //increment only after a mine has been successfully placed
        }
    }
    return;
}

void init(char realBoard[][10], char myBoard[][10]){
    //use random number to create unique config
    srand(time(NULL));

    //assign tiles
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            //upon start no tiles have mines
            //added after first move is made
            myBoard[i][j] = realBoard[i][j] = '-';
        }
    }
    return;
}

//function to play minesweeper
void minesweeper_game(){
    // used to check if game should continue
    bool gameOver = false;
    int row, col;
    int maxMoves = 10 * 10 - totalMines;
    // initalize boards
    char realBoard[10][10], myBoard[10][10];

    // initalize number of mines
    int mines[totalMines][2];

    // set up boards
    init(realBoard, myBoard);
    setMines(mines, realBoard);

    int moveCount = 0; //check if first move has been made

    //core while loop of game
    while(gameOver  == false){

        //update and print board to user
        //updateBoard(myBoard);

        //if left click user is slecting tile
        if(leftClick){
            row = click[0];
            col = click[1];
            if(moveCount == 0){
                TARGET: if(isMine(row, col, realBoard) == true){
                    //if first move was mine, remove it and move it to next avaliable location
                    for(int i = 0; i<10; i++){
                        for(int j = 0; j < 10; j++){
                            if(realBoard[i][j] != '*'){
                                realBoard[i][j] = '*';
                                realBoard[row][col] = '-';
                                goto TARGET;
                            }
                        }
                    }
                }
            }


            moveCount++;
            //get if tile/surroundings are mine
            gameOver = playGame(myBoard, realBoard, mines, row, col);

            //Game is won -- display victory
            if((gameOver == false) && (moveCount == maxMoves)){
                //victory display
                gameOver = true;
            }
            //set left click as false since click has been handled
            leftClick = false;
        }
        //if right click, place flag
        if(rightClick){
            row = click [0];
            col = click [1];
            // add flag variable to tile associated with row and col
            //button[row][col].flagged = true;

            rightClick = false;
        }
    }
}
*/

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MinesweeperStartingPage startPage;
    startPage.setFixedSize(400, 300); // Set window size to 400x300 pixels
    startPage.show();

    return app.exec();
}


