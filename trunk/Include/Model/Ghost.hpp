#ifndef PACMAN_MODEL_GHOST_HPP
#define PACMAN_MODEL_GHOST_HPP


#include <memory>
#include <vector>

#include <Model/Color.hpp>
#include <Model/Direction.hpp>
#include <Model/IBoard.hpp>
#include <Model/IGameModeManager.hpp>
#include <Model/IGhost.hpp>
#include <Model/IPac.hpp>
#include <Model/IRandomDirectionSelector.hpp>
#include <Presentation/IGhostGraphicController.hpp>


namespace Pacman
{
namespace Model
{


class Ghost : public IGhost
{
public:
    Ghost(
            int startingRow_,
            int startingColumn_,
            unsigned moveResolution_,
            Color color_,
            std::shared_ptr<IBoard> board_,
            std::shared_ptr<IPac> pac_,
            std::shared_ptr<IGameModeManager> gameModeManager_,
            std::shared_ptr<IRandomDirectionSelector> randomDirectionSelector_,
            std::shared_ptr<Presentation::IGhostGraphicController> graphicController_);

    void move() override;

    double getCurrentX() const override;
    double getCurrentY() const override;

    void draw() const override;

    void reset() override;

private:
    int normalizedRow(int r) const;
    int normalizedColumn(int c) const;
    Direction opposite(Direction d) const;

    Direction directionToPac(int pacsRow, int pacsColumn) const;
    std::vector<Direction> getDirectionsToVisitableNeighbourFields() const;
    bool isMovingOutsideBoard() const;
    void updateNextRowAndColumn();

    void draw(
            int fromRow,
            int fromColumn,
            int toRow,
            int toColumn,
            unsigned step,
            unsigned resolution) const;

    const int startingRow;
    const int startingColumn;

    int row;
    int column;
    int nextRow;
    int nextColumn;

    const unsigned long numOfRows;
    const unsigned long numOfColumns;

    unsigned step;
    const unsigned moveResolution;

    const Color color;

    Direction direction;

    std::shared_ptr<IBoard> board;
    std::shared_ptr<IPac> pac;
    std::shared_ptr<IGameModeManager> gameModeManager;
    std::shared_ptr<IRandomDirectionSelector> randomDirectionSelector;

    std::shared_ptr<Presentation::IGhostGraphicController> graphicController;
};


} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_GHOST_HPP
