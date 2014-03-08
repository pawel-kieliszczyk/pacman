#ifndef PACMAN_MODEL_BOARD_HPP
#define PACMAN_MODEL_BOARD_HPP


#include <memory>
#include <vector>

#include <Model/IBoard.hpp>
#include <Model/IField.hpp>
#include <Presentation/IBoardGraphicController.hpp>


namespace Pacman
{
namespace Model
{


class Board : public IBoard
{
public:
    Board(
            std::vector<std::vector<std::shared_ptr<IField>>>&& fields_,
            std::shared_ptr<Presentation::IBoardGraphicController> graphicController_);

    unsigned long getNumOfRows() const override;
    unsigned long getNumOfColumns() const override;

    bool isVisitable(unsigned row, unsigned column) const override;
    void visit(unsigned row, unsigned column, IPac& pac) override;

    bool areInTheSameHole(unsigned row1, unsigned column1, unsigned row2, unsigned column2) const override;

    void draw() const override;

    void reset() override;

private:
    std::vector<std::vector<std::shared_ptr<IField>>> fields;
    std::shared_ptr<Presentation::IBoardGraphicController> graphicController;

    unsigned long rows;
    unsigned long columns;
};


} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_BOARD_HPP
