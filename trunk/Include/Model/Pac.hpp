#ifndef PACMAN_MODEL_PAC_HPP
#define PACMAN_MODEL_PAC_HPP


#include <memory>

#include <Model/Direction.hpp>
#include <Model/IBoard.hpp>
#include <Model/ICoinsCollector.hpp>
#include <Model/IFruitsCollector.hpp>
#include <Model/IGameModeManager.hpp>
#include <Model/IPac.hpp>
#include <Model/IScoreController.hpp>
#include <Presentation/IPacGraphicController.hpp>


namespace Pacman
{
namespace Model
{


class Pac : public IPac
{
public:
    Pac(
            int startingRow_,
            int startingColumn_,
            unsigned moveResolution_,
            Direction startingDirection_,
            std::shared_ptr<IBoard> board_,
            std::shared_ptr<IGameModeManager> gameModeManager_,
            std::shared_ptr<ICoinsCollector> coinsCollector_,
            std::shared_ptr<IFruitsCollector> fruitsCollector_,
            std::shared_ptr<IScoreController> scoreController_,
            std::shared_ptr<Presentation::IPacGraphicController> graphicController_);

    void setDirection(Direction newDirection) override;
    void move() override;

    int getCurrentRow() const override;
    int getCurrentColumn() const override;

    double getCurrentX() const override;
    double getCurrentY() const override;

    void eatCoin() override;
    void eatBigCoin() override;
    void eatFruit(std::shared_ptr<IFruit> fruit) override;

    void draw() const override;

    void reset() override;

private:
    int normalizedRow(int r) const;
    int normalizedColumn(int c) const;

    void updateNextRowAndColumn();
    bool isMovingOutsideBoard() const;

    const int startingRow;
    const int startingColumn;
    const Direction startingDirection;

    int row;
    int column;
    int nextRow;
    int nextColumn;

    const unsigned long numOfRows;
    const unsigned long numOfColumns;

    unsigned step;
    const unsigned moveResolution;

    Direction direction;

    std::shared_ptr<IBoard> board;
    std::shared_ptr<IGameModeManager> gameModeManager;
    std::shared_ptr<ICoinsCollector> coinsCollector;
    std::shared_ptr<IFruitsCollector> fruitsCollector;
    std::shared_ptr<IScoreController> scoreController;
    std::shared_ptr<Presentation::IPacGraphicController> graphicController;
};


} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_PAC_HPP
