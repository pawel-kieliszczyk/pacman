#include <algorithm>
#include <cassert>
#include <iterator>

#include <Model/Ghost.hpp>


namespace Pacman
{
namespace Model
{


Ghost::Ghost(
        int startingRow_,
        int startingColumn_,
        unsigned moveResolution_,
        Color color_,
        std::shared_ptr<IBoard> board_,
        std::shared_ptr<IPac> pac_,
        std::shared_ptr<IGameModeManager> gameModeManager_,
        std::shared_ptr<IRandomDirectionSelector> randomDirectionSelector_,
        std::shared_ptr<Presentation::IGhostGraphicController> graphicController_)
    : startingRow(startingRow_),
      startingColumn(startingColumn_),
      row(startingRow_),
      column(startingColumn_),
      numOfRows(board_->getNumOfRows()),
      numOfColumns(board_->getNumOfColumns()),
      step(0u),
      moveResolution(moveResolution_),
      color(color_),
      board(board_),
      pac(pac_),
      gameModeManager(gameModeManager_),
      randomDirectionSelector(randomDirectionSelector_),
      graphicController(graphicController_)
{
    const int pacsRow = pac->getCurrentRow();
    const int pacsColumn = pac->getCurrentColumn();

    const bool seesPac = board->areInTheSameHole(row, column, pacsRow, pacsColumn);
    if(seesPac)
    {
        direction = directionToPac(pacsRow, pacsColumn);
    }
    else
    {
        std::vector<Direction> directions = getDirectionsToVisitableNeighbourFields();
        direction = randomDirectionSelector->selectDirection(directions);
    }

    updateNextRowAndColumn();
}


void Ghost::move()
{
    step = (step + 1) % moveResolution;
    if(step == 0)
    {
        row = normalizedRow(nextRow);
        column = normalizedColumn(nextColumn);
        const int pacsRow = pac->getCurrentRow();
        const int pacsColumn = pac->getCurrentColumn();

        const bool seesPac = board->areInTheSameHole(row, column, pacsRow, pacsColumn);
        if(seesPac)
        {
            const GameMode mode = gameModeManager->getGameMode();
            if(mode == GameMode::BigCoin || mode == GameMode::BigCoinLastSeconds)
            {
                Direction toPac = directionToPac(pacsRow, pacsColumn);
                std::vector<Direction> directionsToRunAway;

                switch(toPac)
                {
                    case Direction::Up :
                        if(board->isVisitable(row + 1, column))
                            directionsToRunAway.push_back(Direction::Down);
                        if(board->isVisitable(row, column - 1))
                            directionsToRunAway.push_back(Direction::Left);
                        if(board->isVisitable(row, column + 1))
                            directionsToRunAway.push_back(Direction::Right);
                        break;
                    case Direction::Down :
                        if(board->isVisitable(row - 1, column))
                            directionsToRunAway.push_back(Direction::Up);
                        if(board->isVisitable(row, column - 1))
                            directionsToRunAway.push_back(Direction::Left);
                        if(board->isVisitable(row, column + 1))
                            directionsToRunAway.push_back(Direction::Right);
                        break;
                    case Direction::Left :
                        if(board->isVisitable(row - 1, column))
                            directionsToRunAway.push_back(Direction::Up);
                        if(board->isVisitable(row + 1, column))
                            directionsToRunAway.push_back(Direction::Down);
                        if(board->isVisitable(row, column + 1))
                            directionsToRunAway.push_back(Direction::Right);
                        break;
                    case Direction::Right :
                        if(board->isVisitable(row - 1, column))
                            directionsToRunAway.push_back(Direction::Up);
                        if(board->isVisitable(row + 1, column))
                            directionsToRunAway.push_back(Direction::Down);
                        if(board->isVisitable(row, column - 1))
                            directionsToRunAway.push_back(Direction::Left);
                        break;
                }

                if(directionsToRunAway.empty())
                    directionsToRunAway.push_back(toPac);

                direction = randomDirectionSelector->selectDirection(directionsToRunAway);
            }
            else
            {
                direction = directionToPac(pacsRow, pacsColumn);
            }
        }
        else
        {
            std::vector<Direction> directions = getDirectionsToVisitableNeighbourFields();

            // if we can continue going toward current direction, disable turning back:
            if(std::find(std::begin(directions), std::end(directions), direction) != std::end(directions))
            {
                const Direction oppositeDirection = opposite(direction);
                auto oppositeDirectionIt = std::find(std::begin(directions), std::end(directions), oppositeDirection);

                assert(oppositeDirectionIt != directions.end());
                directions.erase(oppositeDirectionIt);
            }

            direction = randomDirectionSelector->selectDirection(directions);
        }

        updateNextRowAndColumn();
    }
}


double Ghost::getCurrentX() const
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


double Ghost::getCurrentY() const
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


void Ghost::draw() const
{
    draw(row, column, nextRow, nextColumn, step, moveResolution);
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

        draw(nextRowToDraw, nextColToDraw, nextRowToDraw2, nextColToDraw2, step, moveResolution);
    }
}


void Ghost::reset()
{
    row = startingRow;
    column = startingColumn;
    step = 0u;

    std::vector<Direction> directions = getDirectionsToVisitableNeighbourFields();
    direction = randomDirectionSelector->selectDirection(directions);

    updateNextRowAndColumn();
}


int Ghost::normalizedRow(int r) const
{
    if(r < 0)
        return numOfRows - 1;

    if(r >= static_cast<int>(numOfRows))
        return 0;

    return r;
}


int Ghost::normalizedColumn(int c) const
{
    if(c < 0)
        return numOfColumns - 1;

    if(c >= static_cast<int>(numOfColumns))
        return 0;

    return c;
}


Direction Ghost::opposite(Direction d) const
{
    switch(d)
    {
        case Direction::Up :
            return Direction::Down;
        case Direction::Down :
            return Direction::Up;
        case Direction::Left :
            return Direction::Right;
        case Direction::Right :
            return Direction::Left;
    }
}


Direction Ghost::directionToPac(int pacsRow, int pacsColumn) const
{
    assert((row == pacsRow) || (column == pacsColumn));

    if(row == pacsRow)
    {
        if(pacsColumn < column)
        {
            // Pac is on the left
            return Direction::Left;
        }

        // Pac must be on the right
        return Direction::Right;
    }

    assert(column == pacsColumn);

    if(pacsRow < row)
    {
        // Pac is above
        return Direction::Up;
    }

    // Pac must be below
    return Direction::Down;
}


std::vector<Direction> Ghost::getDirectionsToVisitableNeighbourFields() const
{
    std::vector<Direction> directions;

    if(board->isVisitable(static_cast<const unsigned>(normalizedRow(row - 1)), static_cast<const unsigned>(normalizedColumn(column))))
        directions.push_back(Direction::Up);

    if(board->isVisitable(static_cast<const unsigned>(normalizedRow(row + 1)), static_cast<const unsigned>(normalizedColumn(column))))
        directions.push_back(Direction::Down);

    if(board->isVisitable(static_cast<const unsigned>(normalizedRow(row)), static_cast<const unsigned>(normalizedColumn(column - 1))))
        directions.push_back(Direction::Left);

    if(board->isVisitable(static_cast<const unsigned>(normalizedRow(row)), static_cast<const unsigned>(normalizedColumn(column + 1))))
        directions.push_back(Direction::Right);

    return directions;
}


bool Ghost::isMovingOutsideBoard() const
{
    return (nextRow < 0 || nextRow >= static_cast<int>(numOfRows) || nextColumn < 0 || nextColumn >= static_cast<int>(numOfColumns));
}


void Ghost::updateNextRowAndColumn()
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
}


void Ghost::draw(
        int fromRow,
        int fromColumn,
        int toRow,
        int toColumn,
        unsigned step,
        unsigned resolution) const
{
    const GameMode mode = gameModeManager->getGameMode();

    switch(mode)
    {
        case GameMode::Normal :
            graphicController->drawNormalGhost(fromRow, fromColumn, toRow, toColumn, step, resolution, color);
            break;
        case GameMode::BigCoin :
            graphicController->drawScaredGhost(fromRow, fromColumn, toRow, toColumn, step, resolution, color);
            break;
        case GameMode::BigCoinLastSeconds :
            graphicController->drawLastSecondsScaredGhost(fromRow, fromColumn, toRow, toColumn, step, resolution, color);
            break;
    }
}


} // namespace Model
} // namespace Pacman
