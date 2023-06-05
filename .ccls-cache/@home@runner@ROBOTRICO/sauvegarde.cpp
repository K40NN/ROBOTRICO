#include <iostream>
#include <random>
#include <vector>
/*#include
#include      // For file input and output
#include      // for getline
#include      // for the system command
#include       // For the letter checking functions, e.g. toupper( )
#include*/

using namespace std;

/* ------------------------------------------------
   reedProg6.cpp

   Program #6: Ricochet Robots with undo
   Class: CS 141
   Author: Dale Reed
   Lab: Tues 5am
   System:  C++ Mac Xcode

   Grading Rubric:
   55 points for execution (feedback given automatically through Zylabs)
   45 points for programming style
      (15 points) Linked list node declaration is separate from code otherwise
   used to play the game from the previous version (15 points) Linked list code
   is clearly commented (15 points) Appropriate data structures are used to
   implement the linked list, as discussed and illustrated in class
   ------------------------------------------------
*/
/*

// Global data structure for board
const int BOARD_EDGE = 16;
const int BOARD_SIZE = BOARD_EDGE * BOARD_EDGE;
const int NUMBER_OF_ROBOTS = 4;

// declare constants to later use instead of numbers to select values from
theBoard const int NUMBER_OF_ELEMENTS = 5;   // Number of elements for each
piece, enumerated below const int PIECE = 0;    // to reference the character,
such as in: theBoard[ i][ PIECE] const int LEFT = 1;     // to reference the
left wall character, such as in: theBoard[ i][ LEFT] const int ABOVE = 2;    //
to reference the above wall character, such as in: theBoard[ i][ ABOVE] const
int RIGHT = 3;    // to reference the right wall character, such as in:
theBoard[ i][ RIGHT] const int BELOW = 4;    // to reference the below wall
character, such as in: theBoard[ i][ BELOW]

class Board
{

public:
    Board(int goalRobot = 2, char destinationLetter = 'M');
    void readFromFile();
    void display();
    void displayObjective();
    void clearDestinationPieces();
    //void moveRobot(int moveCount);

    void moveRobot(int robot, char directionLetter);
    void moveRobotUp(int robot);
    void moveRobotRight(int robot);
    void moveRobotLeft(int robot);
    void moveRobotDown(int robot);

    int getRobotAt( int index) const;
    int getNumberOfDestinationPieces() const;
    int getNumberOfRobots() const;
    int getGoalRobot() const;
    char getDestinationLetter() const;

    void setGoalRobot(int robot);
    void setDestinationLetter(char destination);

    bool isOver() const;
    bool isOccupied(int position) const;

private:
    // theBoard itself is represented by a one-dimensional array.
    // The other entries are used to keep track of walls.  Each row
    // in theBoard array will contain the character to be displayed,
    // followed by any "walls" to be displayed around the displayed
    // character.  For instance the first couple of entries are be:
    //
    //       PIECE   LEFT ABOVE RIGHT BELOW
    //      ---0---  --1-  --2-  --3-  --4-
    //    0    .       |     _
    //    1    .             _
    //   ...
    //   255   .                   |     _
    //
    char theBoard[ BOARD_SIZE][ NUMBER_OF_ELEMENTS];
    // Declare the 4 robots, which will store the board position of where they
are found
    // Robots are displayed using values 1-4.  We declare 5 robots, though we
will never use
    // the 0th robot in the array, so that we can use the robot digit itself as
the index. int theRobots[ NUMBER_OF_ROBOTS + 1];
    // Number of destination pieces. Value comes from the data file.
    int numberOfDestinationPieces;
    int goalRobot;                  // the robot that needs to reach the goal
    char destinationLetter;         // the goal letter

};

Board::Board(int goal, char destination)
{
    // default values
    goalRobot = goal;
    destinationLetter = destination;

    numberOfDestinationPieces = 0;

    for (int j = 0; j <= NUMBER_OF_ROBOTS; j++){
        theRobots[j] = 0;
    }


    for( int i = 0; i < BOARD_SIZE; i++) {
        theBoard[ i][ PIECE] = '.';    // Set each playing piece default
        // set the default wall values to be blank
        theBoard[ i][  LEFT] = ' ';
        theBoard[ i][ ABOVE] = ' ';
        theBoard[ i][ RIGHT] = ' ';
        theBoard[ i][ BELOW] = ' ';

        // reset the edge pieces
        // reset the left wall if piece is on left edge
        if( (i % BOARD_EDGE) == 0) {
            theBoard[ i][  LEFT] = '|';
        }
        // reset the above wall if piece is on top edge
        if( i < BOARD_EDGE) {
            theBoard[ i][ ABOVE] = '-';
        }
        // reset the right wall if piece is on right edge
        if( ((i+1) % BOARD_EDGE) == 0) {
            theBoard[ i][ RIGHT] = '|';
        }
        // reset the below wall if piece is on bottom edge
        if( i >= (BOARD_SIZE - BOARD_EDGE) ) {
            theBoard[ i][ BELOW] = '-';
        }
    }//end for( int i...

}//end Board()

//-------------------------------------------------------------------------------------
// Display the Board
//
void Board::display()
{
    // display the top edge
    cout << "  ----------------------------------------------------------------
" << endl;

    // display the "body" of the board
    for( int i = 0; i< BOARD_SIZE; i++) {
        // Figure out what character should be displayed to the left.  It will
        // be a wall if the current spot has a left wall, or if the spot to the
        // left has a right wall.

        char leftCharacter = theBoard[ i][ LEFT];   // set left display char
        // See if the piece to the left has a right wall.  Don't do this for the
        // first piece on the board, since it has no left neighbor.
        if ( (i>0) && (theBoard[ i-1][ RIGHT] != ' ')) {
            leftCharacter = theBoard[ i-1][ RIGHT];
        }

        char piece = theBoard[ i][ PIECE];
        // Check if the piece contains a robot
        for (int j = 1; j <= NUMBER_OF_ROBOTS; j++){
            if (theRobots[j] == i) {
                piece = (char)('0'+j);
            }
        }
        cout << " " << leftCharacter << " " << piece;

        // see if we're at the end of a row
        if( ((i+1) % BOARD_EDGE) == 0) {
            // we are at the end of a row, so display right wall and go to next
line cout << "  " << theBoard[ i][ RIGHT] << endl;
            // Now display any walls immediately below the line of pieces just
displayed
            // Backup our index counter j to the beginning of this line again,
to find any
            // walls displayed below this line.  Don't do it for the bottom row
though. if( i < BOARD_SIZE - BOARD_EDGE) {

                cout << " |";       // display the left boundary
                for( int j=i-BOARD_EDGE+1; j<(i+1); j++) {
                    // Set the character to be displayed.  This is a wall if the
                    // current spot has a wall below, or if the spot below has a
wall
                    // above.
                    char belowCharacter = theBoard[ j][ BELOW];
                    // Only check the square below if we're NOT on the bottom
row if ( (j<(BOARD_SIZE - BOARD_EDGE)) &&      // verify not on bottom row
                        (theBoard[ j+16][ ABOVE] != ' ')) {    // piece below
has wall above belowCharacter = theBoard[ j+16][ ABOVE];
                    }
                    for( int i=0; i<3; i++) {
                       cout << belowCharacter;        // display the character
                    }
                    // display extra spaces, if we're not at the end of a row
                    if( ((j+1) % BOARD_EDGE) != 0) {
                        cout << " ";
                    }
                }//end for( int j...
                cout << " |" << endl;       // display the right boundary
            }//end if( i< BOARD_SIZE...

        }//end if( ((i+1...

    }//end for( int i=0;...

    // display the bottom edge
    cout << "  ----------------------------------------------------------------
" << endl; cout << endl;
}//end display()

//-------------------------------------------------------------------------------------
// readFromFile() - Read from data file, updating board accordingly
//
void Board::readFromFile()
{
    int numberOfSpecialSquares;  // Read from file, denotes number of pieces
with some kind of wall string inputLine;            // Input line from file int
pieceNumber;             // pieceNumber for each square defined in data file
    char c;

    ifstream inStream;           // declare an input file stream
    inStream.open("board.txt");  // Open input file, associating the actual file
name with "inStream" if ( inStream.fail() ) { cout << "Input file opening
failed.  Exiting...\n\n"; return;
    }

    // Read from file one line at a time.  First read the top three data file
lines which are documentation. getline( inStream, inputLine); getline( inStream,
inputLine); getline( inStream, inputLine);

    inStream >> numberOfDestinationPieces;      // read how many destination
pieces there are inStream >> numberOfSpecialSquares;         // number of square
with walls around them somewhere inStream.get( c);                           //
Get rid of return character at end of current line
                                                // to get ready for reading a
line at a time below

    // process the special squares, updating the board
    for( int i=0; i         getline( inStream, inputLine);
        char *pInputLine = &inputLine[0];
        // Extract the piece number from the input line array
        sscanf( pInputLine, "%d", &pieceNumber);
        // Advance the inputLine pointer to the space after the number
        pInputLine = strchr( pInputLine, ' ');

        // Read the information on whether or not there is each of the potential
4 walls.
        // The four values read correspond in order to the pieces on all four
sides,
        // which are defined as global constants for the values LEFT=1, ABOVE=2,
RIGHT=3, BELOW=4 for( int position=1; position<=4; position++) { pInputLine++;
// advance to next character to be read sscanf( pInputLine, " %c", &c); // Read
the next potential wall character
            // Convert it to a blank if it was '0'.  '0' was left in input file
to make it easier to read. if( c=='0') { c = ' ';
            }
            theBoard[ pieceNumber][ position] = c;
        }
        pInputLine++;

        // See if there is a piece letter still to be read on this input line.
        // Do this by finding the end of the line, and seeing the length of the
string
        // after that.
        // An inputline sample for piece 18 would be:
        // 18 00|- A
        if( strlen( pInputLine) > 0) {
            sscanf( pInputLine, " %c", &theBoard[ pieceNumber][ PIECE]);
        }

    }//end for( int i...

    // At the end of the data file read the information on the location of the
robots, updating the board. char junk[80];           // used to read and discard
input file information
    // Loop starts counting from 1 (rather than 0), since we ignore the 0th
position
    // of the robots array, so that robot numbers correspond to what is shown
    // on the board.
    for( int i=1; i<=NUMBER_OF_ROBOTS; i++) {
        inStream >> theRobots[ i];
        inStream.getline( junk, '\n');    // discard rest of line, which is
color information, if using graphics
    }

    inStream.close();         // close the input file stream
}//end readFromFile()

int  Board::getRobotAt( int index) const
{
    return theRobots[ index];
}

int Board::getNumberOfDestinationPieces() const {
    return numberOfDestinationPieces;
}

int Board::getNumberOfRobots() const {
    return NUMBER_OF_ROBOTS;
}

int Board::getGoalRobot() const {
    return goalRobot;
}

char Board::getDestinationLetter() const {
    return destinationLetter;
}

void Board::setGoalRobot(int robot)
{
    goalRobot = robot;
}

void Board::setDestinationLetter(char destination)
{
    destinationLetter = destination;
}

//-------------------------------------------------------------------------------------
// isOver() Returns true if the goal Robot
// gets to the destinationLetter's position on the board
//
bool Board::isOver() const {
    int robotPosition = theRobots[ goalRobot];
    return theBoard[ robotPosition][ PIECE] == destinationLetter;
}

//-------------------------------------------------------------------------------------
// Returns true is the position on the board is already occupied by any robot
//
bool Board::isOccupied(int position) const {
    for (int j = 1; j <= NUMBER_OF_ROBOTS; j++) {
        if (theRobots[j] == position) {
            return true;
        }
    }
    return false;
}

//-------------------------------------------------------------------------------------
// clearDestinationPieces() - Removes all destination pieces from the board
except
// for a single destinationLetter
//
void Board::clearDestinationPieces() {
    for( int i = 0; i < BOARD_SIZE; i++) {
        if ( isupper(theBoard[ i][ PIECE]) && theBoard[ i][ PIECE] !=
destinationLetter) { theBoard[ i][ PIECE] = '.'; // reset to the default
        }
    }
}

void Board::displayObjective() {
    cout << "Move robot " << goalRobot << " to square " << destinationLetter <<
endl;
}

//-------------------------------------------------------------------------------------
// Get the user input for the robot and direction
// and move that robot in given direction
//
void Board::moveRobot(int robot, char direction) {
    // call the appropriate function to move the robot
    // in the given direction
    switch (direction) {
        case 'U':
            moveRobotUp(robot);
            break;
        case 'R':
            moveRobotRight(robot);
            break;
        case 'L':
            moveRobotLeft(robot);
            break;
        case 'D':
            moveRobotDown(robot);
            break;
        default:
            // cannot really get there
            cout << "*** Error. Unexpected direction encountered" << endl;
            exit(-1);
            break;

    }

} // end moveRobot

void Board::moveRobotUp(int robot) {
    int robotPosition = theRobots[robot];
    // loop until the top edge
    while (robotPosition - BOARD_EDGE >= 0) {

        // another robot occupies this position
        if (isOccupied(robotPosition - BOARD_EDGE))
            break;
        // a below side wall encountered
        if (theBoard[robotPosition][ ABOVE] == '-' || theBoard[robotPosition -
BOARD_EDGE][ BELOW] == '-') break; robotPosition -= BOARD_EDGE;
    }
    theRobots[robot] = robotPosition;
}

void Board::moveRobotRight(int robot) {
    int robotPosition = theRobots[robot];
    // loop until the right edge
    while ((robotPosition + 1) % BOARD_EDGE > 0) {

        // another robot occupies this position
        if (isOccupied(robotPosition + 1))
            break;
        // a right side wall encountered
        if (theBoard[robotPosition][ RIGHT] == '|' || theBoard[robotPosition +
1][ LEFT] == '|') break; robotPosition += 1;
    }
    theRobots[robot] = robotPosition;
}

void Board::moveRobotLeft(int robot) {
    int robotPosition = theRobots[robot];
    // loop until the left edge
    while ((robotPosition - 1) % BOARD_EDGE < theRobots[robot] % BOARD_EDGE) {

        // another robot occupies this position
        if (isOccupied(robotPosition - 1))
            break;
        // a right side wall encountered
        if (theBoard[robotPosition][ LEFT] == '|' || theBoard[robotPosition -
1][ RIGHT] == '|') break; robotPosition -= 1;
    }
    theRobots[robot] = robotPosition;
}

void Board::moveRobotDown(int robot) {
    int robotPosition = theRobots[robot];
    // loop until the bottom edge
    while (robotPosition + BOARD_EDGE < BOARD_SIZE) {

        // another robot occupies this position
        if (isOccupied(robotPosition + BOARD_EDGE))
            break;
        // a below side wall encountered
        if (theBoard[robotPosition][ BELOW] == '-' || theBoard[robotPosition +
BOARD_EDGE][ ABOVE] == '-') break; robotPosition += BOARD_EDGE;
    }
    theRobots[robot] = robotPosition;
}

struct Node
{
    int moveNumber;
    Board board;
    struct Node *next;

};

class LinkedList
{

public:

    LinkedList();
    Node *getHead() const;
    void addNodeToList(Node *node);
    void displayList();
    bool deleteNodeFromList();

private:

    Node *pHead;

};

LinkedList::LinkedList()
{
    pHead = NULL;
}

Node *LinkedList::getHead() const
{
    return pHead;
}

void LinkedList::addNodeToList(Node *node)
{
    node->next = pHead;
    pHead = node;
}

void LinkedList::displayList()
{
    Node *current = pHead;
    cout << "List: ";
    while (current != NULL)
    {
        cout << current->moveNumber;
        current = current->next;
        if (current == NULL)
            cout << endl;
        else
            cout << "->";
    }
    cout << "   Robots: ";
    for (int i = 1; i <= pHead->board.getNumberOfRobots(); i++)
    {
        cout << pHead->board.getRobotAt(i) << " ";
    }
    cout << endl;
}

bool LinkedList::deleteNodeFromList()
{
    if (pHead == NULL || pHead->next == NULL)
        return false;
    pHead = pHead->next;

    return true;
}

//-------------------------------------------------------------------------------------
void displayIdentifyingInformationAndInstructions()
{
    // Display identifying information
    cout << "Author: Dale Reed                    " << endl
         << "Program 6: RicoRobots in C++         " << endl
         << "TA: Billie Joe Armstrong, T 6:00 AM  " << endl
         << "March 22, 2018                       " << endl;

    // Display Instructions
    cout << "Welcome to Ricochet Robots                                     " <<
endl
         << "(\'Ricochet Robot\' is a registered trademark of Hans im GlÃ¼ck "
<< endl
         << "Munich, Germany, 1999. The game was created by Alex Randolph.) " <<
endl
         << endl
         << "The object of the game is to get the designated numbered robot " <<
endl
         << "to the indicated letter position.                              " <<
endl
         << "The numbered squares are all robots.  They unfortunately have  " <<
endl
         << "no brakes, and so will continue in whatever direction they are " <<
endl
         << "moving until they encountar an obstacle.                       " <<
endl
         << "For each move enter the robot number and the desired direction." <<
endl
         << "For instance entering                                          " <<
endl
         << "   1 U " << endl
         << "would move the #1 robot up as far as it can go.                " <<
endl
         << "The first letter of input is the robot number (1 - 4),         " <<
endl
         << "and the second letter is the direction:                        " <<
endl
         << "  (L=left, U=up, R=right, D=down)                              " <<
endl
         << "Enter x to exit.  Have fun!                                    " <<
endl
         <<  endl;
}//end displayIdentifyingInformationAndInstructions()

//-------------------------------------------------------------------------------------
// Asks the user to enter the game objective, i.e.
// the goal robot number and the destination letter
//
void getObjective(Board board, int &goalRobot, char &destinationLetter) {

    char goal;                      // a character for user input type
                                    // (goal robot and destination letter)
    bool haveInput = false;

    srand(time(NULL)); // seed rand num generator

    while (!haveInput) {            // loop until the user enters a valid choice
        cout << "Enter 'r' for random robot and goal, 'd' for default or 's' to
select: "; cin >> goal; // get user input goal = tolower(goal);

        if (goal == 'x') {
            exit(-1);
        }
        if (goal == 's')
        {
            board.display();
            bool haveGoal = false;
            while (!haveGoal) {
                cout << "Please enter the goal robot number and the destination
letter: "; cin >> goalRobot >> destinationLetter; destinationLetter =
toupper(destinationLetter); int destinationIndex = destinationLetter - 'A'; if
(goalRobot > 0 && goalRobot <= board.getNumberOfRobots() && destinationIndex >=
0 && destinationIndex < board.getNumberOfDestinationPieces()) { haveGoal = true;
                }
                else {
                    if (!(goalRobot > 0 && goalRobot <=
board.getNumberOfRobots())) cout << "*** Error. Invalid Robot Number. Retry
Input" << endl; else { cout << "*** Error. Invalid Destination Letter. Retry
Input" << endl;
                    }
                }
            }
        }
        else if (goal == 'r')
        {
            goalRobot = 1 + rand() % board.getNumberOfRobots(); // we do not use
0th robot destinationLetter = 'A' + rand() %
board.getNumberOfDestinationPieces();
        }
        else if (goal == 'd')
        {
            goalRobot = 2;
            destinationLetter = 'M';
        }

        if (goal == 'd' || goal == 's' || goal == 'r'){
            haveInput = true;
        }
    }


} // end setObjective

bool getInstaructionDisplayFlag() {
    char value = 0;
    while (!(value == 'f' || value == 't')) {
        cout << "Enter T for true or F for false to indicate if boards and
instructions will be displayed: "; cin >> value; value = tolower(value);
    }

    return value == 't';
}
//-------------------------------------------------------------------------------------
// Returns true if the direction is one of U, D, R, L characters
//
bool isValidDirection(char direction) {
    return direction == 'U' || direction == 'R' || direction == 'D' || direction
== 'L';
}

//-------------------------------------------------------------------------------------
// main() - main part of program, that drives everything else
//
int main()
{
    bool haveInput;
    int robot;
    char command, destinationLetter, directionLetter;
    Board board;
    Node *node;
    LinkedList history;

    displayIdentifyingInformationAndInstructions();
    board.readFromFile();

    bool displayFlag = getInstaructionDisplayFlag();
    getObjective(board, robot, destinationLetter);
    board.setGoalRobot(robot);
    board.setDestinationLetter(destinationLetter);
    board.clearDestinationPieces();
    int moveCount = 1;

    node = new Node;
    node->moveNumber = moveCount;
    node->board = board;
    node->next = NULL;
    history.addNodeToList(node);
    while (!board.isOver()) {
        if (displayFlag) {
            system("cls");
            board.displayObjective();
            board.display();
        }
        haveInput = false;
        while (!haveInput) {

            cout << moveCount << ". ";
            history.displayList();
            cout << "   Enter robot to move and direction (e.g. 2 r), x to exit
or b to backup: "; cin >> command; if (command == 'x') { // early exit cout <<
"Exiting program..." << endl; exit(-1);
            }
            if (command == 'b') { // undo a move
                haveInput = true;
                if (history.deleteNodeFromList()) {
                    cout << "* Undoing move *" << endl;
                    node = history.getHead();
                    moveCount = node->moveNumber;
                    board = node->board;
                }
                else {
                    cout << "*** You cannot undo past the beginning of the game.
Please retry. ***" << endl;
                }

            }
            else {
                robot = command - '0'; // convert char to int

                cin >> directionLetter;
                directionLetter = toupper(directionLetter);

                if (robot > 0 && robot <= board.getNumberOfRobots() &&
isValidDirection(directionLetter)) { haveInput = true; board.moveRobot(robot,
directionLetter); moveCount += 1; node = new Node; node->moveNumber = moveCount;
                    node->board = board;
                    node->next = NULL;
                    history.addNodeToList(node);
                }
                else {
                    if (!(robot > 0 && robot <= board.getNumberOfRobots()))
                        cout << "*** Error. Invalid Robot Number. Retry Input"
<< endl; else { cout << "*** Error. Invalid Direction. Retry Input" << endl;
                    }
                }
            }

        }

    }

    if (displayFlag) {
        board.displayObjective();
        board.display();
    }
    cout << "Great Job! You did it in only " << moveCount << " moves" << endl;

}//end main()

*/