
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream> // We added this for debugging purposes
#include <map>
using namespace std; // ?

class GameManager;
class Player;

class Board
{
private:
    int size;
    int windowWidth;
    int windowHeight;
    int cellSize;
    std::vector<std::vector<sf::Color>> cells;

public:
    friend class GameManager;
    friend class Player;
    std::vector<std::vector<int>> track_highlighted;
    Board(int size, int windowWidth, int windowHeight) : size(size), windowWidth(windowWidth), windowHeight(windowHeight)
    {
        cellSize = windowWidth / size;
        cells.resize(size, std::vector<sf::Color>(size, sf::Color::White));

        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                if ((i == 4 && j == 3) || (i == 4 && j == 5) || (i == 5 && j == 4) || (i == 3 && j == 4))
                {
                    cells[i][j] = sf::Color::Black;
                }
                else if ((i + j) % 2 == 0)
                {
                    cells[i][j] = sf::Color(218, 151, 96);
                }
                else
                {
                    cells[i][j] = sf::Color(64, 21, 13);
                }
            }
        }
        cells[0][0] = sf::Color::Red;
        cells[0][size - 1] = sf::Color::Blue;
        cells[size - 1][0] = sf::Color::Green;
        cells[size - 1][size - 1] = sf::Color::Yellow;
        cells[size / 2][size / 2] = sf::Color(252, 255, 227);
    }

    void draw(sf::RenderWindow& window)
    {
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
                cell.setPosition(i * cellSize, j * cellSize);
                cell.setFillColor(cells[i][j]);
                window.draw(cell);
            }
        }
    }

    // Highlight a cell at the specified row and column
    void highlightSquare(int row, int col, sf::Color cl)
    {
        // cout << "HighlightSquare\n";
        if (row >= 0 && row < size && col >= 0 && col < size)
        {
            // Setting a different color to indicate highlighting.
            cells[row][col] = cl;
        }
    }

    int getSize() const
    {
        return size;
    }
};

//***************************Class Piece**************************

// Piece is an abstract base class representing a generic game piece.
// It contains common attributes and methods shared by all types of pieces.

class Piece
{ // Khaas aapke liye banai gayi abstract class
protected:
    sf::Texture texture;
    sf::Sprite sprite;
    // sprite and texture kya hoti... Isko jananne ke liye
    // you should read the the word document... Aise hi nahi bheja hai...
    int playerID;
    bool aliveStatus; // Flag to indicate if the piece is alive or dead
    char pieceID = '\0';
    std::string imgAdd;

public:
    Piece(int playerID, string imgAdd) : playerID(playerID), imgAdd(imgAdd), aliveStatus(true) {}
    // Humara pyare pure virtual functions
    virtual bool isValidMove(int newRow, int newCol) const = 0;
    virtual bool canCapture(int newRow, int newCol) const = 0;
    void setImgAdd(string imgAdd)
    {
        texture.loadFromFile(imgAdd);
        sprite.setTexture(texture);
    }
    string getImgAdd()
    {
        return imgAdd;
    }
    char getPieceID() const
    {
        return pieceID;
    }
    char getPlayerID() const
    {
        return playerID;
    }
    void setPlayerID(char id)
    {
        playerID = id;
    }
    void setPosition(float x, float y)
    {
        sprite.setPosition(x, y);
    }
    sf::Vector2f getPosition() const // Added getPosition() member function
    {
        return sprite.getPosition();
    }
    void draw(sf::RenderWindow& window) const
    {
        window.draw(sprite);
    }
    bool isAlive() const
    {
        return aliveStatus; // To know whether the piece is alive or not
    }

    void markAsDead()
    {
        aliveStatus = false; // He is no more on the board...
    }
};
//******************************************************************

//***************************Class Commander**************************

// Commander is a derived class representing the Commander piece.
// We have overridden the isValidMove and canCapture methods to implement
// the specific movement and capturing rules as we have described.

class Commander : public Piece
{

    // While writing the path name instead of using \ use this \\ bcoz \ something ka
    //  kuch toh ho jaata hai, string main (pata chale toh share with me also).
public:
    Commander(int playerID, std::string imgAdd) : Piece(playerID, imgAdd)
    {
        pieceID = 'c';
        // Loading commander texture from file
        texture.loadFromFile(imgAdd);
        // Mr. Best in the Biz, please share the the commander image also so that it can be placed here.
        sprite.setTexture(texture);
    }

    // Overriding is sometimes life threatning but...
    // Let's overriding isValidMove for Commander

    bool isValidMove(int newRow, int newCol) const override
    {
        // Commander should move only one step diagonally.
        int rowDiff = abs(newRow - sprite.getPosition().y / 100);
        int colDiff = abs(newCol - sprite.getPosition().x / 100);
        return (rowDiff == 1 && colDiff == 1);
    }

    // Overriding canCapture for Commander
    bool canCapture(int newRow, int newCol) const override
    {
        // Checking if the target position is within one step in any direction.
        int rowDiff = abs(newRow - sprite.getPosition().y / 100);
        int colDiff = abs(newCol - sprite.getPosition().x / 100);
        return (rowDiff <= 1 && colDiff <= 1);
    }
};
//******************************************************************

//***************************Class Rifleman**************************
class Rifleman : public Piece
{

public:
    Rifleman(int playerID, std::string imgAdd) : Piece(playerID, imgAdd)
    {
        pieceID = 'r';
        // Loadddddddddddddddddiiiiiiiiiiiiing Rifleman texture from file
        texture.loadFromFile(imgAdd);
        sprite.setTexture(texture);
    }

    // I'm a rider (Overiding isValidMove for Rifleman)
    bool isValidMove(int newRow, int newCol) const override
    {
        // Rifleman can move one step either forward, backward, leftward, or rightward
        int rowDiff = abs(newRow - sprite.getPosition().y / 100); // Hint: Straight lines
        int colDiff = abs(newCol - sprite.getPosition().x / 100);
        return ((rowDiff == 1 && colDiff == 0) || (rowDiff == 0 && colDiff == 1));
    }

    // I'm an Overrider of canCapture for Rifleman
    bool canCapture(int newRow, int newCol) const override
    {
        // Rifleman can capture at positions where it can move (Ohoooo...).
        return isValidMove(newRow, newCol);
    }
};
//******************************************************************

//***************************Class Sniper**************************
class Sniper : public Piece
{

public:
    Sniper(int playerID, std::string imgAdd) : Piece(playerID, imgAdd)
    {
        pieceID = 's';
        // Sniper ki photu
        texture.loadFromFile(imgAdd);
        sprite.setTexture(texture);
    }
    bool isValidMove(int newRow, int newCol) const override
    {
        // Ctrl +C + ctrl +V Commander's can capture code
        int rowDiff = abs(newRow - sprite.getPosition().y / 100);
        int colDiff = abs(newCol - sprite.getPosition().x / 100);
        return (rowDiff <= 1 && colDiff <= 1);
    }

    bool canCapture(int newRow, int newCol) const override
    {

        // Calculate the row and column differences
        int rowDiff = abs(newRow - sprite.getPosition().y / 100);
        int colDiff = abs(newCol - sprite.getPosition().x / 100);
        // Check if the target position is within a radius of three blocks
        // and is in diagonal direction i.e., rowDiff and colDiff are both non-zero
        //  (If yes then patt se headshot).
        return (rowDiff <= 2 && colDiff <= 2 && rowDiff == colDiff);
    }
};
//***************************************** 1*************************

//***************************Class Tank**************************
class Tank : public Piece
{

public:
    Tank(int playerID, std::string imgAdd) : Piece(playerID, imgAdd)
    {
        pieceID = 't';
        // Tank ki photu
        texture.loadFromFile(imgAdd);
        sprite.setTexture(texture);
    }

    // Overriding isValidMove for Tank
    bool isValidMove(int newRow, int newCol) const override
    {
        // Tank can move either one or two steps in only left, right, upward, or downward direction
        // cout << "new(row, col)" << sprite.getPosition().y / 100 << " " << sprite.getPosition().x / 100 << "(row,col): " << newRow << " " << newCol << endl;
        int rowDiff = abs(newRow - sprite.getPosition().y / 100);
        int colDiff = abs(newCol - sprite.getPosition().x / 100);
        // cout << "rowDiff: " << rowDiff << " colDiff: " << colDiff << endl;
        return ((rowDiff == 0 && colDiff <= 2) || (colDiff == 0 && rowDiff <= 2));
    }

    // Override canCapture for Tank
    bool canCapture(int newRow, int newCol) const override
    {
        // Tank can capture opponent's piece within a radius of two blocks without moving
        // Telling himself He won't go there
        // Oh, but I know that I won't care
        // Tryna wash away all the blood I've spilt
        int rowDiff = abs(newRow - sprite.getPosition().y / 100);
        int colDiff = abs(newCol - sprite.getPosition().x / 100);
        /*return (rowDiff <= 2 && colDiff <= 2);*/
        return ((rowDiff == 0 && colDiff <= 2) || (colDiff == 0 && rowDiff <= 2));
    }
};
//******************************************************************

class Player
{
private:
    char playerID;               // Unique ID for the player
    sf::Color color;             // Color of the player's pieces
    bool inGame;                 // Flag to indicate if the player is still in the game
    std::vector<Piece*> pieces; // Collection of pieces owned by the player
    bool pieceSelected = false;
    Piece* selectedPiece = nullptr;

public:
    Player(char id, sf::Color col) : playerID(id), color(col), inGame(true) {}

    // Function to check which player is eliminated and by whom by reaching headquarter
    char headquarterCheck(GameManager* g, int row, int col);

    // Method to add a piece to the player's collection
    void addPiece(Piece* piece)
    {
        pieces.push_back(piece);
    }
    // Function to check oppenent pieces
    bool check_opponent(map<Player*, std::vector<Player*>>& opponentsMap, GameManager* g, int row, int col, bool toKill);

    // Getter method for player's color
    sf::Color getColor() const
    {
        return color;
    }
    std::vector<Piece*>& getPieces() { return pieces; }

    // Method to handle player's turn
    void handleTurn(GameManager* g, Board& board, sf::RenderWindow& window, sf::Event& event, std::map<Player*, std::vector<Player*>>& opponentsMap);

    // Setter method to mark the player as out of the game
    void markAsOutOfGame()
    {
        inGame = false;
    }

    // Getter method to check if the player is in the game
    bool isInGame() const
    {
        return inGame;
    }
    char getPlayerID() const
    {
        return playerID;
    }
    void display(sf::RenderWindow& window)
    {
        for (auto p : pieces)
        {
            if (p->isAlive())
            {
                p->draw(window);
            }
        }
    }
    bool isSelfCheck(int i, int j)
    {
        for (auto p : pieces)
        {
            if (p->isAlive())
            {
                int x = p->getPosition().y / 100;
                int y = p->getPosition().x / 100;

                if (i == x && j == y)
                    return false;
            }
        }
        return true;
    }
};

// Function to display a message on the screen
static void displayMessage(sf::RenderWindow& window, const std::string& message)
{
    sf::Font font;
    if (!font.loadFromFile("assets\\Fonts\\Redressed-Regular.ttf"))
    {
        // Handle error: unable to load font
        return;
    }

    sf::Text text;
    text.setFont(font);
    text.setString(message);
    text.setCharacterSize(72);
    text.setFillColor(sf::Color::Cyan);
    text.setPosition(0, 0); // Adjust position as needed

    window.clear();
    window.draw(text);
    window.display();
}

class GameManager
{
private:
    static std::vector<Player*> players; // Store all players in the game
    static Player* currentPlayer;
    Board board;
    static std::map<Player*, std::vector<Player*>> opponentsMap; // Store opponents for each player
    sf::RenderWindow& window;
    int winningFlag = 0;
    string wonnedPlayer;

public:
    map<char, bool> playerAlive;
    map<char, bool>& getLivePlayer()
    {
        return playerAlive;
    }
    void setFlag(int f)
    {
        winningFlag = f;
    }

    // Function to handover pieces to another class
    bool transferPieces(char pID1, char pID2)
    {
        Player* p1{};
        Player* p2{};
        int n = players.size();
        int positionOfP2 = -1;
        // Searching for p1(occupier) and p2(to be out).
        for (int i = 0; i < n; i++)
        {
            if (players[i]->getPlayerID() == pID1)
            {
                p1 = players[i];
            }
            if (players[i]->getPlayerID() == pID2)
            {
                p2 = players[i];
                positionOfP2 = i;
                // cout << "Found at index i= " << i << endl;
            }
        }
        // Note:  fill constructor
        //         string v(size_t n, char c);
        //         Fills the string v with n consecutive copies of character c.

        switch (pID2)
        {
        case 'r':
            board.highlightSquare(0, 0, sf::Color(218, 151, 96));
            break;
        case 'b':
            board.highlightSquare(0, 8, sf::Color(218, 151, 96));
            break;
        case 'y':
            board.highlightSquare(0, 8, sf::Color(218, 151, 96));
            break;
        case 'g':
            board.highlightSquare(0, 8, sf::Color(218, 151, 96));
            break;
        default:
            break;
        }

        for (auto piece : p2->getPieces())
        {

            if (piece->getPieceID() != 'c')
            {
                string playerColor(1, p1->getPlayerID());
                string pieceType(1, piece->getPieceID());

                string imgAdd = "assets\\images\\" + playerColor + pieceType + ".png";
                // cout << imgAdd << endl;
                piece->setImgAdd(imgAdd);
                piece->setPlayerID(p1->getPlayerID());
                p1->addPiece(piece);
            }
        }

        if (positionOfP2 != -1)
        {
            auto it = players.begin() + positionOfP2;
            players.erase(it);
            // cout << "Erasing player2: " << endl;
        }

        opponentsMap.erase(p2);
        for (auto& it : opponentsMap)
        {
            auto i = std::find(it.second.begin(), it.second.end(), p2);
            if (i != it.second.end())
            {
                it.second.erase(i);
            }
        }
        if (players.size() == 1)
        {
            wonnedPlayer = getWonnedPlayer(pID1);
            winningFlag = 1;
            return true;
            // return true to declare the last player winner
        }
        return false;
        // return false if didn't ends
    }

    void setWinner(string& w)
    {
        wonnedPlayer = w;
    }
    GameManager(sf::RenderWindow& window, int boardSize, int windowWidth, int windowHeight)
        : window(window), board(boardSize, windowWidth, windowHeight)
    {
        playerAlive['r'] = true;
        playerAlive['b'] = true;
        playerAlive['g'] = true;
        playerAlive['y'] = true;
    }
    string getWonnedPlayer(char pid)
    {
        string winner = "";
        switch (pid)
        {
        case 'r':
            winner += "Red Player";
            break;
        case 'b':
            winner += "Blue Player";
            break;
        case 'y':
            winner += "Yellow Player";
            break;
        case 'g':
            winner += "Green Player";
            break;
        default:
            break;
        }
        return winner;
    }

    void winning(sf::RenderWindow& window) const
    {
        string winStr = wonnedPlayer + " has won the match.";

        displayMessage(window, winStr);
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
    }

    void addPlayer(Player* player)
    {
        players.push_back(player);
        // Initialize empty opponent list for the new player
        opponentsMap[player] = std::vector<Player*>();
    }

    void startGame()
    {
        // cout << "size of vector:" << players.size() << endl;
        for (auto Player1 : players)
        {
            for (auto Player2 : players)
            {
                if (Player1->getPlayerID() != Player2->getPlayerID())
                {
                    opponentsMap[Player1].push_back(Player2);
                }
            }
        }
        currentPlayer = players[0]; // Set the first player as the current player
        while (window.isOpen())
        {
            if (winningFlag == 0)
            {
                handleEvents();
                render();
            }
            else
            {
                winning(window);
            }
        }
    }
    static Player* getCurrentPlayer()
    {
        return currentPlayer;
    }

    static std::vector<Player*>& getOpponents(Player* player)
    {
        return opponentsMap[player];
    }

    void handleEvents()
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                // std:://cout << "(x,y): " << mousePos.x << " " << mousePos.y << std::endl; //......................remove
                // board.handleMouseClick(mousePos);
            }
            // Delegate handling turn to the current player
            currentPlayer->handleTurn(this, board, window, event, opponentsMap);
        }
    }
    // Function to transfer turn to the next player in anti-clockwise order
    static void transferTurn()
    {
        // Find the index of the current player in the list
        auto it = std::find(players.begin(), players.end(), currentPlayer);
        if (it != players.end())
        {
            // Move to the next player (wrap around if at the end of the list)
            ++it;
            // //cout << "Update the current player" <<endl;
            if (it == players.end())
            {
                it = players.begin(); //
                // //cout << "Wrap around if reached the end" << endl;
            }
            currentPlayer = *it;
        }
    }

    void render()
    {
        window.clear();
        board.draw(window);
        for (auto p : players)
            p->display(window);
        window.display();
    }
};

char Player::headquarterCheck(GameManager* g, int row, int col)
{
    map<char, bool>& alivePlayer = g->playerAlive;
    if (selectedPiece->getPlayerID() == 'r')
    {
        char occupied = '\0';

        if (row == 0 && col == 800 && alivePlayer['g'])
        {
            occupied = 'g';
            g->getLivePlayer()['g'] = false;
        }
        else if (row == 800 && col == 0 && alivePlayer['b'])
        {
            occupied = 'b';
            g->getLivePlayer()['b'] = false;
        }
        else if (row == 800 && col == 800 && alivePlayer['y'])
        {
            occupied = 'y';
            g->getLivePlayer()['y'] = false;
        }
        return occupied;
    }
    if (selectedPiece->getPlayerID() == 'b')
    {
        char occupied = '\0';

        if (row == 0 && col == 0 && alivePlayer['r'])
        {
            occupied = 'r';
            g->getLivePlayer()['r'] = false;
        }
        else if (row == 800 && col == 0 && alivePlayer['b'])
        {
            occupied = 'b';
            g->getLivePlayer()['b'] = false;
        }
        else if (row == 800 && col == 800 && alivePlayer['y'])
        {
            occupied = 'y';
            g->getLivePlayer()['y'] = false;
        }
        return occupied;
    }
    if (selectedPiece->getPlayerID() == 'y')
    {
        char occupied = '\0';

        if (row == 0 && col == 800 && alivePlayer['g'])
        {
            occupied = 'g';
            g->getLivePlayer()['g'] = false;
        }
        else if (row == 800 && col == 0 && alivePlayer['b'])
        {
            occupied = 'b';
            g->getLivePlayer()['b'] = false;
        }
        else if (row == 0 && col == 0 && alivePlayer['r'])
        {
            occupied = 'r';
            g->getLivePlayer()['r'] = false;
        }
        return occupied;
    }
    if (selectedPiece->getPlayerID() == 'g')
    {
        char occupied = '\0';

        if (row == 0 && col == 800 && alivePlayer['g'])
        {
            occupied = 'g';
            g->getLivePlayer()['g'] = false;
        }
        else if (row == 0 && col == 0 && alivePlayer['r'])
        {
            occupied = 'r';
            g->getLivePlayer()['r'] = false;
        }
        else if (row == 800 && col == 800 && alivePlayer['y'])
        {
            occupied = 'y';
            g->getLivePlayer()['y'] = false;
        }
        return occupied;
    }
    return '\0';
}

bool Player::check_opponent(map<Player*, std::vector<Player*>>& opponentsMap, GameManager* g, int row, int col, bool toKill)
{
    // //cout << "(row,col): " << row << " " << col << endl;
    vector<Player*> opponents = opponentsMap[this];
    // //cout << "Size of opponents: " << opponents.size() << endl;
    for (Player* opponent : opponents)
    {
        vector<Piece*>& oponentPlayer = opponent->getPieces();
        auto it = oponentPlayer.begin();
        auto end = oponentPlayer.end();
        for (; it != end; it++)
        {
            // //cout << "piece->getPosition().x: " << (*it)->getPosition().x << "piece->getPosition().y: " << (*it)->getPosition().y << endl;
            if ((*it)->getPosition().x == col && (*it)->getPosition().y == row)
            {
                // removing the opponent piece which has been killed.
                if (toKill)
                {
                    char p = (*it)->getPieceID();
                    char p2ID = (*it)->getPlayerID();
                    (*it)->markAsDead();
                    oponentPlayer.erase(it);
                    if (p == 'c')
                    {
                        g->getLivePlayer()[p2ID] = false;
                        g->transferPieces((g->getCurrentPlayer())->getPlayerID(), p2ID);
                    }
                }
                return true;
            }
        }
    }
    return false;
}

void Player::handleTurn(GameManager* g, Board& board, sf::RenderWindow& window, sf::Event& event, std::map<Player*, std::vector<Player*>>& opponentsMap)
{
    sf::Vector2i clickPosition; // Even though a mouse click represents
    // a single point in space, using a vector makes it easier to work with
    // the coordinates as a cohesive unit, especially when dealing with other
    // vector-based operations or functions.

    // Check if it's the current player's turn
    if (this != GameManager::getCurrentPlayer())
    {
        return; // Exit the function if it's not the player's turn
    }

    // Loop until the player selects a valid piece and makes a move
    // while (window.pollEvent(event))
    //{
    // //cout << "Entered (turnHandler)\n";

    if (event.type == sf::Event::Closed)
    {
        window.close();
    }
    if (event.type == sf::Event::MouseButtonPressed)
    {
        // cout << "....................................................." << endl;
        clickPosition = sf::Mouse::getPosition(window);
        // cout << "from handle turn (x,y)=" << clickPosition.x << " " << clickPosition.y << endl;
        int row = (clickPosition.y / 100) * 100;
        int col = (clickPosition.x / 100) * 100;
        // cout << "from handle turn (row, col)=" << row << " " << col << endl;

        if (!pieceSelected)
        {
            for (auto& square : board.track_highlighted)
            {
                int j = square[1];
                int i = square[0];

                if ((i + j) % 2 == 0)
                {
                    board.cells[i][j] = sf::Color(218, 151, 96);
                    board.cells[0][0] = sf::Color::Red;
                    board.cells[0][9 - 1] = sf::Color::Blue;
                    board.cells[9 - 1][0] = sf::Color::Green;
                    board.cells[9 - 1][9 - 1] = sf::Color::Yellow;
                    board.cells[9 / 2][9 / 2] = sf::Color(252, 255, 227);
                }
                else if ((i + j) % 2 != 0)
                {
                    board.cells[i][j] = sf::Color(64, 21, 13);
                    board.cells[0][0] = sf::Color::Red;
                    board.cells[0][9 - 1] = sf::Color::Blue;
                    board.cells[9 - 1][0] = sf::Color::Green;
                    board.cells[9 - 1][9 - 1] = sf::Color::Yellow;
                    board.cells[9 / 2][9 / 2] = sf::Color(252, 255, 227);
                }
            }

            for (Piece* piece : pieces)
            {
                // //cout << "Pices (x,y)=" << piece->getPosition().x << " " << piece->getPosition().y << endl;
                if (piece->getPosition().x == col && piece->getPosition().y == row)
                {
                    selectedPiece = piece;
                    pieceSelected = true;
                    break;
                }
            }
            if (!pieceSelected)
            {
                // cout << "checking........\n";
                for (auto& p : board.track_highlighted)
                {
                    if (p[0] * 100 == col && p[1] * 100 == row)
                    {
                        bool opponentCheck = check_opponent(opponentsMap, g, row, col, true);

                        if (opponentCheck && (selectedPiece->getPieceID() == 's' || selectedPiece->getPieceID() == 't'))
                        {
                        }
                        else
                        {
                            bool isValid = selectedPiece->isValidMove(row / 100, col / 100);
                            // cout << "isValid: " << isValid << endl;
                            if (!isValid && selectedPiece->getPieceID() == 's')
                            {
                                // cout << "condition1" << endl;
                            }
                            else
                            {

                                // cout << " Checking that selected piece reaches the other players headquarter" << endl;
                                selectedPiece->setPosition(col, row);
                                if (selectedPiece->getPieceID() == 'c')
                                {
                                    // opponent which should be out now.
                                    char to_be_out = headquarterCheck(g, row, col);

                                    // cout << "selected piece" << selectedPiece->getPieceID() << "to_be_out" << to_be_out << endl;
                                    if (to_be_out)
                                    {
                                        // g->getLivePlayer()[to_be_out] = false;
                                        bool gameCheck = g->transferPieces(selectedPiece->getPlayerID(), to_be_out);
                                        // cout << "gamecheck " << gameCheck << endl;
                                        if (gameCheck)
                                        {
                                            return;
                                        }
                                    }
                                }
                            }
                            if (row == 400 && col == 400 && selectedPiece->getPieceID() == 'c')
                            {

                                string winner = g->getWonnedPlayer(selectedPiece->getPlayerID());

                                g->setWinner(winner);
                                g->setFlag(1);
                                return;
                            }
                        }
                        GameManager::transferTurn();
                    }
                }
            }
            board.track_highlighted.clear();
        }
    }
    if (pieceSelected)
    {
        int col = (selectedPiece->getPosition().x / 100) * 100;
        int row = (selectedPiece->getPosition().y / 100) * 100;
        board.draw(window);
        for (int i = 0; i < board.getSize(); ++i)
        {
            for (int j = 0; j < board.getSize(); ++j)
            {
                if ((i == 3 && j == 4) || (i == 4 && j == 3) || (i == 5 && j == 4) || (i == 4 && j == 5))
                {
                    continue;
                }
                bool opponentCheck = check_opponent(opponentsMap, g, j * 100, i * 100, false);
                // cout << "opponentCheck  " << opponentCheck << endl;
                bool isValid = selectedPiece->isValidMove(j, i);
                bool isCanCapture = selectedPiece->canCapture(j, i);
                // cout << "(i,j):" << i << " " << j << " isValid:" << isValid << " isSelfCheck:" << isSelfCheck(i, j) << endl;
                if (isValid && isSelfCheck(j, i) && !opponentCheck)
                {

                    board.highlightSquare(i, j, sf::Color::Cyan);
                    // cout << "Pushing for highlighted: " << i << " " << j << endl;
                    board.track_highlighted.push_back({ i, j });
                }
                else if (isCanCapture && opponentCheck)
                {
                    // cout << "isCanCapture " << isCanCapture << "i,j =" << i << " " << j << endl;
                    board.highlightSquare(i, j, sf::Color(255, 0, 0, 200));
                    // cout << "Pushing for highlighted: " << i << " " << j << endl;
                    board.track_highlighted.push_back({ i, j });
                }
            }
        }
        pieceSelected = false;
    }

    //}
}

Player* r = new Player('r', sf::Color::Red);
Player* b = new Player('b', sf::Color::Blue);
Player* g = new Player('g', sf::Color::Green);
Player* y = new Player('y', sf::Color::Yellow);

// Initialize GameManager's static member variables
std::vector<Player*> GameManager::players = {}; // { r, b, g, y };
std::map<Player*, std::vector<Player*>> GameManager::opponentsMap;
Player* GameManager::currentPlayer = nullptr;

// The Purpose of a text is to get a reply within minutes I mean if I wanted
//  //to wait I'd send them a letter through a pigeon instead, which would have
//  //travelled through the whole Pacific Ocean and reached them.
// I waited for days and they didn't replied. But later on they helped.
//  Without there help I wouldn't have been able to do it.

sf::RenderWindow window(sf::VideoMode(900, 900), "QuattroRealm");

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~main() function~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main()
{

    const int windowWidth = 900;
    const int windowHeight = 900;
    const int boardSize = 9;

    Board board(boardSize, windowWidth, windowHeight);

    GameManager gameManager(window, boardSize, windowWidth, windowHeight);

    //.......................................Red..................................................

    // Create pieces for each player
    Commander* rCommander = new Commander(r->getPlayerID(), "assets\\images\\rc.png");
    Rifleman* rRifleman1 = new Rifleman(r->getPlayerID(), "assets\\images\\rr.png");
    Rifleman* rRifleman2 = new Rifleman(r->getPlayerID(), "assets\\images\\rr.png");
    Rifleman* rRifleman3 = new Rifleman(r->getPlayerID(), "assets\\images\\rr.png");
    Sniper* rSniper1 = new Sniper(r->getPlayerID(), "assets\\images\\rs.png");
    Sniper* rSniper2 = new Sniper(r->getPlayerID(), "assets\\images\\rs.png");
    Sniper* rSniper3 = new Sniper(r->getPlayerID(), "assets\\images\\rs.png");
    Tank* rTank1 = new Tank(r->getPlayerID(), "assets\\images\\rt.png");
    Tank* rTank2 = new Tank(r->getPlayerID(), "assets\\images\\rt.png");
    // Add pieces to the player
    rCommander->setPosition(0, 0);
    rRifleman1->setPosition(200, 100);
    rRifleman2->setPosition(100, 200);
    rRifleman3->setPosition(200, 200);
    rSniper1->setPosition(100, 0);
    rSniper2->setPosition(0, 100);
    rSniper3->setPosition(100, 100);
    rTank1->setPosition(200, 0);
    rTank2->setPosition(0, 200);
    r->addPiece(rCommander);
    r->addPiece(rRifleman1);
    r->addPiece(rRifleman2);
    r->addPiece(rRifleman3);
    r->addPiece(rSniper1);
    r->addPiece(rSniper2);
    r->addPiece(rSniper3);
    r->addPiece(rTank1);
    r->addPiece(rTank2);

    //.......................................Blue..................................................
    Commander* bCommander = new Commander(b->getPlayerID(), "assets\\images\\bc.png");
    Rifleman* bRifleman1 = new Rifleman(b->getPlayerID(), "assets\\images\\br.png");
    Rifleman* bRifleman2 = new Rifleman(b->getPlayerID(), "assets\\images\\br.png");
    Rifleman* bRifleman3 = new Rifleman(b->getPlayerID(), "assets\\images\\br.png");
    Sniper* bSniper1 = new Sniper(b->getPlayerID(), "assets\\images\\bs.png");
    Sniper* bSniper2 = new Sniper(b->getPlayerID(), "assets\\images\\bs.png");
    Sniper* bSniper3 = new Sniper(b->getPlayerID(), "assets\\images\\bs.png");
    Tank* bTank1 = new Tank(b->getPlayerID(), "assets\\images\\bt.png");
    Tank* bTank2 = new Tank(b->getPlayerID(), "assets\\images\\bt.png");
    // Add pieces to the player
    bCommander->setPosition(0, 800);
    bRifleman1->setPosition(100, 600);
    bRifleman2->setPosition(200, 600);
    bRifleman3->setPosition(200, 700);
    bSniper1->setPosition(0, 700);
    bSniper2->setPosition(100, 700);
    bSniper3->setPosition(100, 800);
    bTank1->setPosition(0, 600);
    bTank2->setPosition(200, 800);
    b->addPiece(bCommander);
    b->addPiece(bRifleman1);
    b->addPiece(bRifleman2);
    b->addPiece(bRifleman3);
    b->addPiece(bSniper1);
    b->addPiece(bSniper2);
    b->addPiece(bSniper3);
    b->addPiece(bTank1);
    b->addPiece(bTank2);
    //.......................................Yellow..................................................
    Commander* yCommander = new Commander(y->getPlayerID(), "assets\\images\\yc.png");
    Rifleman* yRifleman1 = new Rifleman(y->getPlayerID(), "assets\\images\\yr.png");
    Rifleman* yRifleman2 = new Rifleman(y->getPlayerID(), "assets\\images\\yr.png");
    Rifleman* yRifleman3 = new Rifleman(y->getPlayerID(), "assets\\images\\yr.png");
    Sniper* ySniper1 = new Sniper(y->getPlayerID(), "assets\\images\\ys.png");
    Sniper* ySniper2 = new Sniper(y->getPlayerID(), "assets\\images\\ys.png");
    Sniper* ySniper3 = new Sniper(y->getPlayerID(), "assets\\images\\ys.png");
    Tank* yTank1 = new Tank(y->getPlayerID(), "assets\\images\\yt.png");
    Tank* yTank2 = new Tank(y->getPlayerID(), "assets\\images\\yt.png");
    // Add pieces to the player
    yCommander->setPosition(800, 800);
    yRifleman1->setPosition(600, 600);
    yRifleman2->setPosition(600, 700);
    yRifleman3->setPosition(700, 600);
    ySniper1->setPosition(700, 800);
    ySniper2->setPosition(800, 700);
    ySniper3->setPosition(700, 700);
    yTank1->setPosition(600, 800);
    yTank2->setPosition(800, 600);
    y->addPiece(yCommander);
    y->addPiece(yRifleman1);
    y->addPiece(yRifleman2);
    y->addPiece(yRifleman3);
    y->addPiece(ySniper1);
    y->addPiece(ySniper2);
    y->addPiece(ySniper3);
    y->addPiece(yTank1);
    y->addPiece(yTank2);

    //.......................................Green..................................................
    Commander* gCommander = new Commander(g->getPlayerID(), "assets\\images\\gc.png");
    Rifleman* gRifleman1 = new Rifleman(g->getPlayerID(), "assets\\images\\gr.png");
    Rifleman* gRifleman2 = new Rifleman(g->getPlayerID(), "assets\\images\\gr.png");
    Rifleman* gRifleman3 = new Rifleman(g->getPlayerID(), "assets\\images\\gr.png");
    Sniper* gSniper1 = new Sniper(g->getPlayerID(), "assets\\images\\gs.png");
    Sniper* gSniper2 = new Sniper(g->getPlayerID(), "assets\\images\\gs.png");
    Sniper* gSniper3 = new Sniper(g->getPlayerID(), "assets\\images\\gs.png");
    Tank* gTank1 = new Tank(g->getPlayerID(), "assets\\images\\gt.png");
    Tank* gTank2 = new Tank(g->getPlayerID(), "assets\\images\\gt.png");
    // Add pieces to the player
    gCommander->setPosition(800, 0);
    gRifleman1->setPosition(600, 100);
    gRifleman2->setPosition(600, 200);
    gRifleman3->setPosition(700, 200);
    gSniper1->setPosition(800, 100);
    gSniper2->setPosition(700, 100);
    gSniper3->setPosition(700, 0);
    gTank1->setPosition(600, 0);
    gTank2->setPosition(800, 200);
    g->addPiece(gCommander);
    g->addPiece(gRifleman1);
    g->addPiece(gRifleman2);
    g->addPiece(gRifleman3);
    g->addPiece(gSniper1);
    g->addPiece(gSniper2);
    g->addPiece(gSniper3);
    g->addPiece(gTank1);
    g->addPiece(gTank2);

    // Add players to the game manager
    gameManager.addPlayer(r);
    gameManager.addPlayer(b);
    gameManager.addPlayer(y);
    gameManager.addPlayer(g);

    gameManager.startGame();
    // Start the game

    return 0;
}
