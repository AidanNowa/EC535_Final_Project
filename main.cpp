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
        this->setFixedSize(500, 400);
        this->setStyleSheet("background-color: rgb(210, 210, 210);");
        QHBoxLayout * mainlayout = new QHBoxLayout(this);
        QVBoxLayout * lcdlayout= new QVBoxLayout();

        lcdTimer = new QLCDNumber(this); //timer will increase until 999
        lcdTimer->setSegmentStyle(QLCDNumber::Flat); // Set the segment style to filled
        timer = new QTimer(this);
        lcdTimer->setDigitCount(3);
        timer->setInterval(1000);
        lcdTimer->display(0);
        connect(timer, &QTimer::timeout, this, &Minesweeper::updateTimerDisplay);
        timer->start();
        lcdlayout->addWidget(lcdTimer);

        restart = new QPushButton();
        restart->setFixedSize(40,40);
        QPixmap restartpixmap("/Users/macbookair/Desktop/EC535/test/Images/smile.png");
        QIcon RestartButtonIcon(restartpixmap);
        restart->setIcon(RestartButtonIcon);
        restart->setIconSize(QSize(40,50));
        connect(restart, &QPushButton::clicked, this, &Minesweeper::RestartButtonClicked); //if leftclicked
        lcdlayout->addWidget(restart, 0, Qt::AlignCenter);


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
        if(hiddenBoard[row][col]->getflipstatus() == true || hiddenBoard[row][col]->getflagstatus() == true){

            return false;
        }
        hiddenBoard[row][col]->setfliptrue();
        moveCount++;
        qDebug() << "past base case";
        int count = countAdjMines(row, col);
        qDebug() << "count " << count;
        if(count == 0){
            QPixmap pixmap("/Users/macbookair/Desktop/EC535/test/Images/blank.png");
            QIcon ButtonIcon(pixmap);
            hiddenBoard[row][col]->setIcon(ButtonIcon);
            hiddenBoard[row][col]->setIconSize(QSize(28, 30));
        }
        else if(count == 1){
            QPixmap pixmap("/Users/macbookair/Desktop/EC535/test/Images/1.png");
            QIcon ButtonIcon(pixmap);
            hiddenBoard[row][col]->setIcon(ButtonIcon);
            hiddenBoard[row][col]->setIconSize(QSize(28, 30));
        }
        else if(count == 2){
            QPixmap pixmap("/Users/macbookair/Desktop/EC535/test/Images/2.png");
            QIcon ButtonIcon(pixmap);
            hiddenBoard[row][col]->setIcon(ButtonIcon);
            hiddenBoard[row][col]->setIconSize(QSize(28, 30));
        }
        else if(count == 3){
            QPixmap pixmap("/Users/macbookair/Desktop/EC535/test/Images/3.png");
            QIcon ButtonIcon(pixmap);
            hiddenBoard[row][col]->setIcon(ButtonIcon);
            hiddenBoard[row][col]->setIconSize(QSize(28, 30));
        }
        else if(count == 4){
            QPixmap pixmap("/Users/macbookair/Desktop/EC535/test/Images/4.png");
            QIcon ButtonIcon(pixmap);
            hiddenBoard[row][col]->setIcon(ButtonIcon);
            hiddenBoard[row][col]->setIconSize(QSize(28, 30));
        }
        else if(count == 5){
            QPixmap pixmap("/Users/macbookair/Desktop/EC535/test/Images/5.png");
            QIcon ButtonIcon(pixmap);
            hiddenBoard[row][col]->setIcon(ButtonIcon);
            hiddenBoard[row][col]->setIconSize(QSize(28, 30));

        }
        else if(count == 6){
            QPixmap pixmap("/Users/macbookair/Desktop/EC535/test/Images/6.png");
            QIcon ButtonIcon(pixmap);
            hiddenBoard[row][col]->setIcon(ButtonIcon);
            hiddenBoard[row][col]->setIconSize(QSize(28, 30));

        }
        else if(count == 7){
            QPixmap pixmap("/Users/macbookair/Desktop/EC535/test/Images/7.png");
            QIcon ButtonIcon(pixmap);
            hiddenBoard[row][col]->setIcon(ButtonIcon);
            hiddenBoard[row][col]->setIconSize(QSize(28, 30));

        }
        else if(count == 8){
            QPixmap pixmap("/Users/macbookair/Desktop/EC535/test/Images/8.png");
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
        timer->stop();
        qDebug() << "Game Over";
        QPixmap restartpixmap("/Users/macbookair/Desktop/EC535/test/Images/dead.png");
        QIcon RestartButtonIcon(restartpixmap);
        restart->setIcon(RestartButtonIcon);
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 10; j++){
                hiddenBoard[i][j]->setfliptrue();
                hiddenBoard[i][j]->setflagfalse();
                if(hiddenBoard[i][j]->getminestatus() == true){
                    QPixmap pixmap("/Users/macbookair/Desktop/EC535/test/Images/mine.png");
                    QIcon ButtonIcon(pixmap);
                    hiddenBoard[i][j]->setIcon(ButtonIcon);
                    hiddenBoard[i][j]->setIconSize(QSize(28, 30));
                }
            }
        }
    }
    void victory(){
        timer->stop();
        qDebug() << "Victory";
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 10; j++){
                hiddenBoard[i][j]->setfliptrue();
                hiddenBoard[i][j]->setflagfalse();
                if(hiddenBoard[i][j]->getminestatus() == true){
                    QPixmap pixmap("/Users/macbookair/Desktop/EC535/test/Images/success.png");
                    QIcon ButtonIcon(pixmap);
                    hiddenBoard[i][j]->setIcon(ButtonIcon);
                    hiddenBoard[i][j]->setIconSize(QSize(28, 30));
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

    void RestartButtonClicked(){
        Minesweeper *minesweeper = new Minesweeper;
        minesweeper->show();
        close();
    }

    void onButtonLeftClicked() {
        MyButton *button = qobject_cast<MyButton *>(sender());
        int i = button->property("row").toInt();
        int j = button->property("col").toInt();
        if(!button->getflagstatus()){
            if (QGuiApplication::keyboardModifiers() == Qt::NoModifier) {
                sweep(i, j);
            }
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
            QPixmap pixmap("/Users/macbookair/Desktop/EC535/test/Images/flag.png"); //set flag

            QIcon ButtonIcon(pixmap);
            button->setIcon(ButtonIcon);
            button->setIconSize(QSize(28, 30));
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
    int maxMoves = numRows * numCols - numMines;
    MyButton *hiddenBoard[10][10];
    int mines[10][2]; //stores (x,y) coordinates of all mines

    QGridLayout *gridlayout;
    QTimer *timer;
    QLCDNumber *mineCounter;
    QLCDNumber *lcdTimer;
    QPushButton *restart;
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

private slots:
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


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MinesweeperStartingPage startPage;
    startPage.setFixedSize(400, 300); // Set window size to 400x300 pixels
    startPage.show();

    return app.exec();
}


