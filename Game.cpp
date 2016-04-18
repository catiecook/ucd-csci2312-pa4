//
// Created by Catie Cook on 4/7/16.
//
#include <set>
#include <sstream>
#include <iomanip>
#include "Game.h"
#include "Simple.h"
#include "Strategic.h"
#include "Food.h"
#include "Advantage.h"

namespace Gaming {
    // ~~~~~~~~~~ CONSTANTS ~~~~~~~~~~~~~~~~~

    const unsigned int Game::NUM_INIT_AGENT_FACTOR = 4;
    const unsigned int Game::NUM_INIT_RESOURCE_FACTOR = 2;
    const unsigned int Game::MIN_WIDTH = 3;
    const unsigned int Game::MIN_HEIGHT = 3;
    const double Game::STARTING_AGENT_ENERGY = 20;
    const double Game::STARTING_RESOURCE_CAPACITY = 10;

    PositionRandomizer Game::__posRandomizer = PositionRandomizer();


//     bool __verbose = true;

//~~~~~~~~~~~~ PRIVATE MEMBERS ~~~~~~~~~~~~

    void Game::populate()
    {

        std::default_random_engine gen;
        std::uniform_int_distribution<int> d(0, __width * __height);

        __numInitAgents = (__width * __height) / NUM_INIT_AGENT_FACTOR;
        __numInitResources = (__width * __height) / NUM_INIT_RESOURCE_FACTOR;
        unsigned int numStrategic = __numInitAgents / 2;
        unsigned int numSimple = __numInitAgents - numStrategic;
        unsigned int numAdvantages = __numInitResources / 4;
        unsigned int numFoods = __numInitResources - numAdvantages;

        while (numStrategic > 0)
        {
            int i = d(gen); // random index in the grid vector
            if (__grid[i] == nullptr) { // is position empty
                Position pos(i / __width, i % __width);
                __grid[i] = new Strategic(*this, pos, Game::STARTING_AGENT_ENERGY);
                numStrategic --;
            }
        }

        while(numSimple > 0)
        {
            int i = d(gen);
            if(__grid[i] == nullptr)
            {
                Position pos(i / __width, i % __width);
                __grid[i] = new Simple(*this, pos, Game::STARTING_AGENT_ENERGY);
                numSimple--;
            }
        }

        while(numAdvantages > 0)
        {
            int i = d(gen);
            if(__grid[i] == nullptr)
            {
                Position pos(i / __width, i % __width);
                __grid[i] = new Advantage(*this, pos, Game::STARTING_RESOURCE_CAPACITY);
                numAdvantages--;
            }
        }

        while(numFoods > 0)
        {
            int i = d(gen);
            if(__grid[i] == nullptr)
            {
                Position pos(i / __width, i % __width);
                __grid[i] = new Food(*this, pos, Game::STARTING_RESOURCE_CAPACITY);
                numFoods--;
            }
        }

    }

// ~~~~~~~~~ CONSTRUCTORS ~~~~~~~~~~~~

    Game::Game() : __numInitAgents(0),__numInitResources(0),
                   __width(3), __height(3), __grid(__width * __height, nullptr), __round(0),
                   __status(NOT_STARTED), __verbose(false)
    {

        for (unsigned i = 0; i < (__width * __height); ++i)
        {
            __grid.push_back(nullptr);
        }

    }

    Game::Game(unsigned width, unsigned height, bool manual) : __width(width), __height(height)
    {
//        if ((width >= __width || height >= __height))
//        {
//            throw OutOfBoundsEx(__width, __height, width, height);
//        }

        if (width < MIN_WIDTH || height < MIN_HEIGHT)
        {
            throw InsufficientDimensionsEx(MIN_WIDTH, MIN_HEIGHT, width, height);
        }

        __status = NOT_STARTED;
        __verbose = false;
        __round = 0;


//counter to add variables

        for (unsigned i = 0; i < (__width * __height); i++) {
            __grid.push_back(nullptr);
        }

        if (!manual) //if there is nothing, put something there with populate
        {
            populate();
        }


    }

    Game::Game(const Game &another) : __numInitAgents(another.getNumAgents()), __numInitResources(another.getNumResources()), __width(another.__width),
                                      __height(another.__height), __grid(__width * __height, nullptr), __round(another.__round),
                                      __status(another.__status), __verbose(another.__verbose)
        {
            for(int i = 0; i <= another.__grid.size(); ++i)
            {
                __grid[i] = another.__grid[i];
            }
        }


    Game::~Game()
    {
        if(__grid.size() > 0)
        {
            for(int i = 0; i < __grid.size(); ++i)
            {
                __grid[i] = nullptr;
            }
        }

    }

// ~~~~~~~~~~~~ GETTERS/SETTERS ~~~~~~~~~~~~~~

    unsigned int Game::getNumPieces() const //using the auto keyword to do all of the push-backs
    {
        unsigned int numberOfPieces = 0;
        for (auto it = __grid.begin(); it != __grid.end(); ++it)
        {
            if (*it != nullptr)
                numberOfPieces++;
        }

        return numberOfPieces;
    }

    unsigned int Game::getNumAgents() const {
        unsigned int numAgents = 0;
        for (auto it = __grid.begin(); it != __grid.end(); ++it)
        {
            if (*it != nullptr)
                numAgents++;
        }

        return numAgents;
    }


    unsigned int Game::getNumSimple() const
    {

        unsigned int numAgents = 0;
        for (auto it = __grid.begin(); it != __grid.end(); ++it)
        {
            Agent *agent = dynamic_cast<Strategic*>(*it);
            if (agent) numAgents ++;

//            if (*it != nullptr)
//                numAgents++;
        }

        return numAgents;
    }


    unsigned int Game::getNumStrategic() const
    {
        unsigned int numStrat = 0;
        for (auto it = __grid.begin(); it != __grid.end(); ++it)
        {
            Agent *agent = dynamic_cast<Strategic*>(*it);
            if (agent) numStrat ++;
        }

        return numStrat;

    }

    unsigned int Game::getNumResources() const
    {
        unsigned int numResources = 0;
        for (auto it = __grid.begin(); it != __grid.end(); ++it)
        {
            Resource *resource = dynamic_cast<Resource*>(*it);
            if (resource) numResources ++;
        }

        return numResources;
    }

    const Piece *Game::getPiece(unsigned int x, unsigned int y) const
    {
// Insert all the exceptions

        if (y >= __height || x >= __width)
        {
            throw OutOfBoundsEx(__width, __height, x, y);
        }

        Piece* point = nullptr;
        for (auto it = __grid.begin(); it != __grid.end(); ++it)
        {
            if(*it != nullptr && (*it)->getPosition().x == x && (*it)->getPosition().y == y)
                point = *it;
        }
//        if (__grid[y + (x * __width)] == nullptr)
//        {
//            throw PositionEmptyEx(x, y);
//        }

        return point;

    }


// ~~~~~~~~~~~~~ GRID POPULATION METHODS ~~~~~~~~~~~~~~~ *Pretty much figured one out and ran with it for the rest


    void Game::addSimple(const Position &position)
    {
        if (__grid[position.x + (position.y * __width)])
        {
            throw PositionNonemptyEx(position.x, position.y);
        }
        if ((position.x >= __width || position.y >= __height))
        {
            throw OutOfBoundsEx(__width, __height, position.x, position.y);
        }

        __grid[position.x + (position.y * __width)] = new Simple(*this, position, Game::STARTING_AGENT_ENERGY);
    }

    void Game::addSimple(const Position &position, double energy) //same as above but with designated energy
    {
        unsigned int count = __grid.size();
        addSimple(position);

        if(count != __grid.size())
        {
            Agent* agent = dynamic_cast<Agent*>(__grid[position.x + (position.y * __width)]);
            if(agent)
            {
                double i = agent->getEnergy();
                agent->addEnergy(energy - i);
            }
        }
    }

    void Game::addSimple(unsigned x, unsigned y)
    {

        Position p(x,y);
        addSimple(p);

    }

    void Game::addSimple(unsigned x, unsigned y, double energy) //same as above but with designated energy
    {

        Position p(x,y);
        addSimple(p, energy);


    }

    void Game::addStrategic(const Position &position, Strategy *s)
    {

        int count = position.x + (position.y * __width);


        if ((position.x >= __width || position.y >= __height))
        {
            throw OutOfBoundsEx(__width, __height, position.x, position.y);
        }

        __grid[count] = new Strategic(*this, position, Game::STARTING_AGENT_ENERGY, s);

    }

    void Game::addStrategic(unsigned x, unsigned y, Strategy *s)
    {
        unsigned int count = x + (y * __width);

        if (__grid[x + (y * __width)])
        {
            throw PositionNonemptyEx(x, y);
        }

        __grid[count] = new Strategic(*this, Position(x, y), Game::STARTING_AGENT_ENERGY, s);
    }

    void Game::addFood(const Position &position)
    {
        unsigned int count = position.x + (position.y * __width);

        if ((position.x >= __width || position.y >= __height))
        {
            throw OutOfBoundsEx(__width, __height, position.x, position.y);
        }

        __grid[count] = new Food(*this, position, Game::STARTING_AGENT_ENERGY);
    }

    void Game::addFood(unsigned x, unsigned y)
    {
        Position p(x,y);
        addFood(p);
    }

    void Game::addAdvantage(const Position &position)
    {
        unsigned int count = position.x + (position.y * __width);

        if ((position.x >= __width || position.y >= __height))
        {
            throw OutOfBoundsEx(__width, __height, position.x, position.y);
        }

        __grid[count] = new Advantage(*this, position, Game::STARTING_RESOURCE_CAPACITY);
    }


    void Game::addAdvantage(unsigned x, unsigned y)
    {
        Position p(x, y);
        addAdvantage(p);
    }

    const Surroundings Game::getSurroundings(const Position &pos) const
    {
        Gaming::Surroundings surround;

        for (int i = 0; i < 9; i++)
        {
            surround.array[i] = EMPTY;
        }
        for (int row = -1; row <= 1; ++row)
        {
            for (int col = -1; col <= 1; ++col)
            {
                if (pos.x + row >= 0 && pos.x + row < __height
                    && pos.y + col >= 0 && pos.y + col < __width)
                {
                    // if inside bounds of game
                    unsigned int index = pos.y + col + ((pos.x + row) * __width);

                    if (__grid[index])
                        surround.array[col + 1 + ((row + 1) * 3)] = __grid[index]->getType();
                }

                else
                {
                    // if outside bounds of game
                    surround.array[col + 1 + ((row + 1) * 3)] = INACCESSIBLE;
                }
            }
        }
        surround.array[4] = Gaming::SELF;

        return surround;
    }

// ~~~~~~~~~~~~~~ GAMEPLAY METHODS ~~~~~~~~~~~~~~

        const ActionType Game::reachSurroundings(const Position &from, const Position &to)
        {

            ActionType ac;

            unsigned int x, y;
            x = (to.x - from.x);
            y = (to.y - from.y);



            if(x == -1 && y == -1)
            {
                ac = NW;
            }
            else if(x == -1 && y == 0)
            {
                ac = N;
            }
            else if(x == -1 && y == 1)
            {
                ac = NE;
            }
            else if(x == 0 && y == -1)
            {
                ac = W;
            }
            else if(x == 0 && y == 1)
            {
                ac = E;
            }
            else if(x == 1 && y == -1)
            {
                ac = SW;
            }
            else if(x == 1 && y == 0)
            {
                ac = S;
            }
            else if(x == 1 && y == 1)
            {
                ac = SE;
            }
            else
                ac = STAY;

            return ac;
            }




        bool Game::isLegal(const ActionType &ac, const Position &pos) const
        {
            bool __isLegal = false;

            Position position(pos);

            int x, y;
            x = position.x;
            y = position.y;

           // x++, y++;

            switch (ac)
            {
                case E:
                    x++;
                    break;
                case NE:
                    x++;
                    y--;
                    break;
                case N:
                    y--;
                    break;
                case W:
                    x--;
                    break;
                case NW:
                    y--;
                    x--;
                    break;
                case S:
                    y++;
                    break;
                case SE:
                    y++;
                    x++;
                    break;
                case SW:
                    y++;
                    x--;
                    break;

                default: std::cout << "SOMETHING DOESNT WORK HERE" << std::endl;
            }

//return status of __isLegal

            return __isLegal;
        }

        const Position Game::move(const Position &pos, const ActionType &ac) const  //assumes legal, use function above

        {
            if (isLegal(ac, pos))
            {
                int x = pos.x;
                int y = pos.y;

                switch (ac)
                {
                    case E:
                        x++;
                        break;
                    case NE:
                        x++;
                        y--;
                        break;
                    case N:
                        y--;
                        break;
                    case W:
                        x--;
                        break;
                    case NW:
                        y--;
                        x--;
                        break;
                    case S:
                        y++;
                        break;
                    case SE:
                        y++;
                        x++;
                        break;
                    case SW:
                        y++;
                        x--;
                        break;

                    default: STAY;
                }

                // Position position((unsigned)x, (unsigned)y);
                // return position;
            }

            return pos;
        }

/*
 * Go through all the Piece-s that are still viable and on the grid (this doesn't change between rounds) and:
If a Piece has not taken a turn, give it a turn. Use Piece::getTurned().
Call the Piece::setTurned(true) to avoid giving a moving Piece more than one turn per round (e.g. if it happens to move to a grid position you haven't covered in the current round).
Perform the turn and implement all the consequences of the turn (e.g. interaction with another Piece).
Delete any Piece-s which interacted and, as a result, became unviable.
Go through all the Piece-s that are still viable and on the grid after the current round, and:
Call the polymorphic Piece::age().
Call the Piece::setTurned(false) to reset the turn for the next round.
Delete any Piece-s which have aged to zero.
Some guidelines for implementing Game::round():

Do it incrementally and use the tests to build in more and more detail.
It might be intuitive that you cycle through the Game grid for each round, but it is much better to cycle through a std::set of all the currently occupied positions of the grid. Cycling through the grid won't be able to handle some of the finer cases. Cycling through the set, if done correctly, will ensure a fair turn for all the Pieces.
Notice that a Piece might become unviable before its turn comes (e.g. a Resource gets consumed by an Agent that moves ahead of it, or an Agent gets challenged by another, and one or both die as a result).
Notice that a Piece might move to a new position, either through an interaction or through a move to a previously free position. In the first case, the position was already occupied, so it is still in the set. In the second case, the position was empty, so needs to be added to the set.

 */
        void Game::round()
        {
            std::set<Piece*> pieces;
            for (auto it = __grid.begin(); it != __grid.end(); )
            {

            }

        }

        void Game::play(bool verbose)
        {
            __verbose = verbose;
            __status = PLAYING;

            std::cout << *this;

            while (__status != OVER)
            {
                round();

                if (verbose) std::cout << *this;
            }

            if (!verbose) std::cout << *this;
        }

// ~~~~~~~~~ FRIEND OPERATOR ~~~~~~~~~~~~~

        std::ostream &operator<<(std::ostream &os, const Game &game)
        {
            os << "Round " << game.getRound() << "/n";
            for(int i = 0; i < game.__height; ++i)
            {
                for (int l = 0; l < game.__width; ++l)
                {
                    for(auto it = game.__grid.begin(); it != game.__grid.end(); ++it)
                    {
                        if(*it != nullptr)
                        {
                            Position pos(i, l);
                            Position piecePos = (*it)->getPosition();

                            if (piecePos.x == pos.x && piecePos.y == pos.y)
                            {
                                os << "[" << std::setw(6) << *(*it) << "]";
                            }
                        }
                        else
                            os << "[" << std::string(6, ' ') << "]";
                    }
                }

                os << "/n";
            }

            switch(game.getStatus())
            {
                case Game::NOT_STARTED: os << "Not Started./n";
                    break;
                case Game::PLAYING: os << "Playing.../n";
                    break;
                case Game::OVER: os << "Over!/n";
                    break;
                default: os << "SHIT" << std::endl;
            }

            return os;

        }

    }



