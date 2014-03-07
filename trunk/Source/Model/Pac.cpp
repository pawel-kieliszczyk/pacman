#include <Model/Pac.hpp>


namespace Pacman
{
namespace Model
{


Pac::Pac(
        int startingRow_,
        int startingColumn_,
        unsigned moveResolution_,
        Direction startingDirection_,
        std::shared_ptr<IBoard> board_,
        std::shared_ptr<IGameModeManager> gameModeManager_,
        std::shared_ptr<ICoinsCollector> coinsCollector_,
        std::shared_ptr<IFruitsCollector> fruitsCollector_,
        std::shared_ptr<IScoreController> scoreController_,
        std::shared_ptr<Presentation::IPacGraphicController> graphicController_)
    : startingRow(startingRow_),
      startingColumn(startingColumn_),
      startingDirection(startingDirection_),
      row(startingRow_),
      column(startingColumn_),
      numOfRows(board_->getNumOfRows()),
      numOfColumns(board_->getNumOfColumns()),
      step(0u),
      moveResolution(moveResolution_),
      direction(startingDirection),
      board(board_),
      gameModeManager(gameModeManager_),
      coinsCollector(coinsCollector_),
      fruitsCollector(fruitsCollector_),
      scoreController(scoreController_),
      graphicController(graphicController_)
{
    board->visit(static_cast<unsigned>(row), static_cast<unsigned>(column), *this);
    updateNextRowAndColumn();
}


void Pac::setDirection(Direction newDirection)
{
    direction = newDirection;

    if(step == 0)
        updateNextRowAndColumn();
}


void Pac::move()
{
    step = (step + 1) % moveResolution;
    if(step == 0)
    {
        row = normalizedRow(nextRow);
        column = normalizedColumn(nextColumn);

        board->visit(static_cast<unsigned>(row), static_cast<unsigned>(column), *this);

        updateNextRowAndColumn();
    }
}


int Pac::getCurrentRow() const
{
    return row;
}


int Pac::getCurrentColumn() const
{
    return column;
}


double Pac::getCurrentX() const
{
    double x = column;

    if(nextColumn == column)
        return x;

    if(direction == Direction::Left)
        x -= static_cast<double>(step) / static_cast<double>(moveResolution);

    if(direction == Direction::Right)
        x += static_cast<double>(step) / static_cast<double>(moveResolution);

    return x;
}


double Pac::getCurrentY() const
{
    double y = row;

    if(nextRow == row)
        return y;

    if(direction == Direction::Up)
        y -= static_cast<double>(step) / static_cast<double>(moveResolution);

    if(direction == Direction::Down)
        y += static_cast<double>(step) / static_cast<double>(moveResolution);

    return y;
}


void Pac::eatCoin()
{
    coinsCollector->collectNextCoin();
    scoreController->addCoinScore();
}


void Pac::eatBigCoin()
{
    coinsCollector->collectNextCoin();
    scoreController->addBigCoinScore();
    gameModeManager->activateBigCoinMode();
}


void Pac::eatFruit(std::shared_ptr<IFruit> fruit)
{
    fruitsCollector->collectFruit(fruit);
}


void Pac::draw() const
{
    graphicController->draw(row, column, nextRow, nextColumn, step, moveResolution);
    if(isMovingOutsideBoard())
    {
        int nextRowToDraw = nextRow;
        if(nextRow < 0)
            nextRowToDraw = numOfRows;
        if(nextRow >= static_cast<int>(numOfRows))
            nextRowToDraw = -1;

        int nextColToDraw = nextColumn;
        if(nextColumn < 0)
            nextColToDraw = numOfColumns;
        if(nextColumn >= static_cast<int>(numOfColumns))
            nextColToDraw = -1;

        const int nextRowToDraw2 = normalizedRow(nextRow);
        const int nextColToDraw2 = normalizedColumn(nextColumn);

        graphicController->draw(nextRowToDraw, nextColToDraw, nextRowToDraw2, nextColToDraw2, step, moveResolution);
    }
}


void Pac::reset()
{
    row = startingRow;
    column = startingColumn;
    direction = startingDirection;
    step = 0u;

    board->visit(static_cast<unsigned>(row), static_cast<unsigned>(column), *this);
    updateNextRowAndColumn();
}


int Pac::normalizedRow(int r) const
{
    if(r < 0)
        return numOfRows - 1;

    if(r >= static_cast<int>(numOfRows))
        return 0;

    return r;
}


int Pac::normalizedColumn(int c) const
{
    if(c < 0)
        return numOfColumns - 1;

    if(c >= static_cast<int>(numOfColumns))
        return 0;

    return c;
}


void Pac::updateNextRowAndColumn()
{
    switch(direction)
    {
        case Direction::Up :
            nextRow = row - 1;
            nextColumn = column;
            break;
        case Direction::Down :
            nextRow = row + 1;
            nextColumn = column;
            break;
        case Direction::Left :
            nextRow = row;
            nextColumn = column - 1;
            break;
        case Direction::Right :
            nextRow = row;
            nextColumn = column + 1;
            break;
    }

    const int nextRowToVisit = normalizedRow(nextRow);
    const int nextColumnToVisit = normalizedColumn(nextColumn);

    if(!board->isVisitable(static_cast<const unsigned>(nextRowToVisit), static_cast<const unsigned>(nextColumnToVisit)))
    {
        nextRow = row;
        nextColumn = column;
    }
}


bool Pac::isMovingOutsideBoard() const
{
    return (nextRow < 0 || nextRow >= static_cast<int>(numOfRows) || nextColumn < 0 || nextColumn >= static_cast<int>(numOfColumns));
}


} // namespace Model
} // namespace Pacman
