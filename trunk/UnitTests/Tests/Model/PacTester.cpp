#include <memory>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <Model/Direction.hpp>
#include <Model/Pac.hpp>

#include <Mocks/Model/BoardMock.hpp>
#include <Mocks/Model/CoinsCollectorMock.hpp>
#include <Mocks/Model/FruitMock.hpp>
#include <Mocks/Model/FruitsCollectorMock.hpp>
#include <Mocks/Model/GameModeManagerMock.hpp>
#include <Mocks/Model/ScoreControllerMock.hpp>
#include <Mocks/Presentation/PacGraphicControllerMock.hpp>


namespace GT = testing;


namespace Pacman
{
namespace Model
{
namespace Testing
{


struct PacTester : public GT::Test
{
    PacTester()
    {
        createPacInMovablePosition();
        createPacNotInMovablePosition();
    }

    const int startingRow = 11;
    const int startingColumn = 22;
    const Direction startingDirection = Direction::Up;
    const unsigned moveResolution = 3;

    // mocks:
    std::shared_ptr<BoardMock> boardMock =
            std::make_shared<GT::StrictMock<BoardMock>>();
    std::shared_ptr<GameModeManagerMock> gameModeManagerMock =
            std::make_shared<GT::StrictMock<GameModeManagerMock>>();
    std::shared_ptr<CoinsCollectorMock> coinsCollectorMock =
            std::make_shared<GT::StrictMock<CoinsCollectorMock>>();
    std::shared_ptr<FruitsCollectorMock> fruitsCollectorMock =
            std::make_shared<GT::StrictMock<FruitsCollectorMock>>();
    std::shared_ptr<ScoreControllerMock> scoreControllerMock =
            std::make_shared<GT::StrictMock<ScoreControllerMock>>();
    std::shared_ptr<Presentation::Testing::PacGraphicControllerMock> pacGraphicControllerMock =
            std::make_shared<GT::StrictMock<Presentation::Testing::PacGraphicControllerMock>>();

    // tested class:
    std::unique_ptr<Pac> pacInMovablePosition;
    std::unique_ptr<Pac> pacNotInMovablePosition;

private:
    void createPacInMovablePosition()
    {
        const bool inMovablePosition = true;
        pacInMovablePosition = createPac(inMovablePosition);
    }

    void createPacNotInMovablePosition()
    {
        const bool inMovablePosition = false;
        pacNotInMovablePosition = createPac(inMovablePosition);
    }

    std::unique_ptr<Pac> createPac(bool inMovablePosition)
    {
        EXPECT_CALL(*boardMock, getNumOfRows()).WillOnce(GT::Return(startingRow * 2));
        EXPECT_CALL(*boardMock, getNumOfColumns()).WillOnce(GT::Return(startingColumn * 2));

        EXPECT_CALL(*boardMock, visit(startingRow, startingColumn, GT::_));
        EXPECT_CALL(*boardMock, isVisitable(startingRow - 1, startingColumn)).WillOnce(GT::Return(inMovablePosition));

        return std::unique_ptr<Pac>(new Pac(
                startingRow,
                startingColumn,
                moveResolution,
                startingDirection,
                boardMock,
                gameModeManagerMock,
                coinsCollectorMock,
                fruitsCollectorMock,
                scoreControllerMock,
                pacGraphicControllerMock));
    }
};


MATCHER_P(HasMemoryAddress, address, "") { return &arg == address; }
MATCHER_P(MatchSmartPointers, p, "") { return arg.get() == p.get(); }


TEST_F(PacTester, createsPacInMovablePosition)
{
    // expect
    EXPECT_CALL(*boardMock, getNumOfRows()).WillOnce(GT::Return(startingRow * 2));
    EXPECT_CALL(*boardMock, getNumOfColumns()).WillOnce(GT::Return(startingColumn * 2));

    EXPECT_CALL(*boardMock, visit(startingRow, startingColumn, GT::_));
    EXPECT_CALL(*boardMock, isVisitable(startingRow - 1, startingColumn)).WillOnce(GT::Return(true));

    // when and then
    Pac p(
            startingRow,
            startingColumn,
            moveResolution,
            startingDirection,
            boardMock,
            gameModeManagerMock,
            coinsCollectorMock,
            fruitsCollectorMock,
            scoreControllerMock,
            pacGraphicControllerMock);
}


TEST_F(PacTester, createsPacNotInMovablePosition)
{
    // expect
    EXPECT_CALL(*boardMock, getNumOfRows()).WillOnce(GT::Return(startingRow * 2));
    EXPECT_CALL(*boardMock, getNumOfColumns()).WillOnce(GT::Return(startingColumn * 2));

    EXPECT_CALL(*boardMock, visit(startingRow, startingColumn, GT::_));
    EXPECT_CALL(*boardMock, isVisitable(startingRow - 1, startingColumn)).WillOnce(GT::Return(false));

    // when and then
    Pac p(
            startingRow,
            startingColumn,
            moveResolution,
            startingDirection,
            boardMock,
            gameModeManagerMock,
            coinsCollectorMock,
            fruitsCollectorMock,
            scoreControllerMock,
            pacGraphicControllerMock);
}


TEST_F(PacTester, drawsPacInMovablePosition)
{
    // expect
    const unsigned currentStep = 0;
    const int nextRow = startingRow - 1;
    const int nextColumn = startingColumn;
    EXPECT_CALL(*pacGraphicControllerMock, draw(startingRow, startingColumn, nextRow, nextColumn, currentStep, moveResolution));

    // when and then
    pacInMovablePosition->draw();
}


TEST_F(PacTester, drawsPacNotInMovablePosition)
{
    // expect
    const unsigned currentStep = 0;
    const int nextRow = startingRow;
    const int nextColumn = startingColumn;
    EXPECT_CALL(*pacGraphicControllerMock, draw(startingRow, startingColumn, nextRow, nextColumn, currentStep, moveResolution));

    // when and then
    pacNotInMovablePosition->draw();
}


TEST_F(PacTester, movesPacTowardVisitableField)
{
    // when
    pacInMovablePosition->move();

    // expect
    const unsigned currentStep = 1;
    const int nextRow = startingRow - 1;
    const int nextColumn = startingColumn;
    EXPECT_CALL(*pacGraphicControllerMock, draw(startingRow, startingColumn, nextRow, nextColumn, currentStep, moveResolution));

    // then
    pacInMovablePosition->draw();
}


TEST_F(PacTester, movesPacTowardUnvisitableField)
{
    // when
    pacNotInMovablePosition->move();

    // expect
    const unsigned currentStep = 1;
    const int nextRow = startingRow;
    const int nextColumn = startingColumn;
    EXPECT_CALL(*pacGraphicControllerMock, draw(startingRow, startingColumn, nextRow, nextColumn, currentStep, moveResolution));

    // then
    pacNotInMovablePosition->draw();
}


TEST_F(PacTester, movesPacCompletelyToVisitableField)
{
    // when
    pacInMovablePosition->move();

    // expect
    unsigned currentStep = 1;
    int nextRow = startingRow - 1;
    int nextColumn = startingColumn;
    EXPECT_CALL(*pacGraphicControllerMock, draw(startingRow, startingColumn, nextRow, nextColumn, currentStep, moveResolution));

    // then
    pacInMovablePosition->draw();

    // when
    pacInMovablePosition->move();

    // expect
    ++currentStep;
    EXPECT_CALL(*pacGraphicControllerMock, draw(startingRow, startingColumn, nextRow, nextColumn, currentStep, moveResolution));

    // then
    pacInMovablePosition->draw();

    // expect
    EXPECT_CALL(*boardMock, visit(nextRow, nextColumn, HasMemoryAddress(pacInMovablePosition.get())));
    const int fromRow = nextRow;
    const int fromColumn = nextColumn;
    const int toRow = fromRow - 1;
    const int toColumn = fromColumn;
    EXPECT_CALL(*boardMock, isVisitable(toRow, toColumn)).WillOnce(GT::Return(true));

    // when
    pacInMovablePosition->move();

    // expect
    currentStep = 0; // resolution is 3
    EXPECT_CALL(*pacGraphicControllerMock, draw(fromRow, fromColumn, toRow, toColumn, currentStep, moveResolution));

    // then
    pacInMovablePosition->draw();
}


TEST_F(PacTester, getsPacsCurrentRowAndColumn)
{
    // when and then
    EXPECT_EQ(startingRow, pacInMovablePosition->getCurrentRow());
    EXPECT_EQ(startingColumn, pacInMovablePosition->getCurrentColumn());

    // given
    pacInMovablePosition->move();
    pacInMovablePosition->move();

    const int newRow = startingRow - 1;
    const int newColumn = startingColumn;
    EXPECT_CALL(*boardMock, visit(newRow, newColumn, HasMemoryAddress(pacInMovablePosition.get())));
    EXPECT_CALL(*boardMock, isVisitable(newRow - 1, newColumn)).WillOnce(GT::Return(true));

    pacInMovablePosition->move();

    // when and then
    EXPECT_EQ(newRow, pacInMovablePosition->getCurrentRow());
    EXPECT_EQ(newColumn, pacInMovablePosition->getCurrentColumn());
}


TEST_F(PacTester, getsPacsCurrentXAndYWhenPacIsMovingUp)
{
    // given
    const unsigned long rows = 3;
    const unsigned long cols = 3;

    EXPECT_CALL(*boardMock, getNumOfRows()).WillOnce(GT::Return(rows));
    EXPECT_CALL(*boardMock, getNumOfColumns()).WillOnce(GT::Return(cols));

    EXPECT_CALL(*boardMock, visit(1u, 2u, GT::_));
    EXPECT_CALL(*boardMock, isVisitable(0u, 2u)).WillOnce(GT::Return(true));

    // when
    Pac p(
            1,
            2,
            moveResolution,
            Direction::Up,
            boardMock,
            gameModeManagerMock,
            coinsCollectorMock,
            fruitsCollectorMock,
            scoreControllerMock,
            pacGraphicControllerMock);

    // then
    EXPECT_DOUBLE_EQ(2.0, p.getCurrentX());
    EXPECT_DOUBLE_EQ(1.0, p.getCurrentY());

    // when
    p.move();

    // then
    EXPECT_DOUBLE_EQ(2.0, p.getCurrentX());
    EXPECT_DOUBLE_EQ(2.0 / 3.0, p.getCurrentY());

    // when
    p.move();

    // then
    EXPECT_DOUBLE_EQ(2.0, p.getCurrentX());
    EXPECT_DOUBLE_EQ(1.0 / 3.0, p.getCurrentY());
}


TEST_F(PacTester, getsPacsCurrentXAndYWhenPacIsMovingDown)
{
    // given
    const unsigned long rows = 3;
    const unsigned long cols = 3;

    EXPECT_CALL(*boardMock, getNumOfRows()).WillOnce(GT::Return(rows));
    EXPECT_CALL(*boardMock, getNumOfColumns()).WillOnce(GT::Return(cols));

    EXPECT_CALL(*boardMock, visit(1u, 2u, GT::_));
    EXPECT_CALL(*boardMock, isVisitable(2u, 2u)).WillOnce(GT::Return(true));

    // when
    Pac p(
            1,
            2,
            moveResolution,
            Direction::Down,
            boardMock,
            gameModeManagerMock,
            coinsCollectorMock,
            fruitsCollectorMock,
            scoreControllerMock,
            pacGraphicControllerMock);

    // then
    EXPECT_DOUBLE_EQ(2.0, p.getCurrentX());
    EXPECT_DOUBLE_EQ(1.0, p.getCurrentY());

    // when
    p.move();

    // then
    EXPECT_DOUBLE_EQ(2.0, p.getCurrentX());
    EXPECT_DOUBLE_EQ(4.0 / 3.0, p.getCurrentY());

    // when
    p.move();

    // then
    EXPECT_DOUBLE_EQ(2.0, p.getCurrentX());
    EXPECT_DOUBLE_EQ(5.0 / 3.0, p.getCurrentY());
}


TEST_F(PacTester, getsPacsCurrentXAndYWhenPacIsMovingLeft)
{
    // given
    const unsigned long rows = 3;
    const unsigned long cols = 3;

    EXPECT_CALL(*boardMock, getNumOfRows()).WillOnce(GT::Return(rows));
    EXPECT_CALL(*boardMock, getNumOfColumns()).WillOnce(GT::Return(cols));

    EXPECT_CALL(*boardMock, visit(2u, 1u, GT::_));
    EXPECT_CALL(*boardMock, isVisitable(2u, 0u)).WillOnce(GT::Return(true));

    // when
    Pac p(
            2,
            1,
            moveResolution,
            Direction::Left,
            boardMock,
            gameModeManagerMock,
            coinsCollectorMock,
            fruitsCollectorMock,
            scoreControllerMock,
            pacGraphicControllerMock);

    // then
    EXPECT_DOUBLE_EQ(1.0, p.getCurrentX());
    EXPECT_DOUBLE_EQ(2.0, p.getCurrentY());

    // when
    p.move();

    // then
    EXPECT_DOUBLE_EQ(2.0 / 3.0, p.getCurrentX());
    EXPECT_DOUBLE_EQ(2.0, p.getCurrentY());

    // when
    p.move();

    // then
    EXPECT_DOUBLE_EQ(1.0 / 3.0, p.getCurrentX());
    EXPECT_DOUBLE_EQ(2.0, p.getCurrentY());
}


TEST_F(PacTester, getsPacsCurrentXAndYWhenPacIsMovingRight)
{
    // given
    const unsigned long rows = 3;
    const unsigned long cols = 3;

    EXPECT_CALL(*boardMock, getNumOfRows()).WillOnce(GT::Return(rows));
    EXPECT_CALL(*boardMock, getNumOfColumns()).WillOnce(GT::Return(cols));

    EXPECT_CALL(*boardMock, visit(2u, 1u, GT::_));
    EXPECT_CALL(*boardMock, isVisitable(2u, 2u)).WillOnce(GT::Return(true));

    // when
    Pac p(
            2,
            1,
            moveResolution,
            Direction::Right,
            boardMock,
            gameModeManagerMock,
            coinsCollectorMock,
            fruitsCollectorMock,
            scoreControllerMock,
            pacGraphicControllerMock);

    // then
    EXPECT_DOUBLE_EQ(1.0, p.getCurrentX());
    EXPECT_DOUBLE_EQ(2.0, p.getCurrentY());

    // when
    p.move();

    // then
    EXPECT_DOUBLE_EQ(4.0 / 3.0, p.getCurrentX());
    EXPECT_DOUBLE_EQ(2.0, p.getCurrentY());

    // when
    p.move();

    // then
    EXPECT_DOUBLE_EQ(5.0 / 3.0, p.getCurrentX());
    EXPECT_DOUBLE_EQ(2.0, p.getCurrentY());
}


TEST_F(PacTester, movesPacOutsideLeftBoardsEdge)
{
    // given
    const unsigned long rows = 3;
    const unsigned long cols = 3;
    const Direction startingDirection = Direction::Left;

    // expect
    EXPECT_CALL(*boardMock, getNumOfRows()).WillOnce(GT::Return(rows));
    EXPECT_CALL(*boardMock, getNumOfColumns()).WillOnce(GT::Return(cols));

    EXPECT_CALL(*boardMock, visit(1u, 0u, GT::_));
    EXPECT_CALL(*boardMock, isVisitable(1u, 2u)).WillOnce(GT::Return(true));

    // when and then
    Pac p(
            1,
            0,
            moveResolution,
            startingDirection,
            boardMock,
            gameModeManagerMock,
            coinsCollectorMock,
            fruitsCollectorMock,
            scoreControllerMock,
            pacGraphicControllerMock);

    // given
    p.move();

    // expect
    const unsigned currentStep = 1;
    EXPECT_CALL(*pacGraphicControllerMock, draw(1, 0, 1, -1, currentStep, moveResolution));
    EXPECT_CALL(*pacGraphicControllerMock, draw(1, 3, 1, 2, currentStep, moveResolution));

    // when and then
    p.draw();

    // given
    p.move();

    // expect
    EXPECT_CALL(*boardMock, visit(1, 2, HasMemoryAddress(&p)));
    EXPECT_CALL(*boardMock, isVisitable(1, 1)).WillOnce(GT::Return(true));

    // when and then
    p.move();
}


TEST_F(PacTester, movesPacOutsideRightBoardsEdge)
{
    // given
    const unsigned long rows = 3;
    const unsigned long cols = 3;
    const Direction startingDirection = Direction::Right;

    // expect
    EXPECT_CALL(*boardMock, getNumOfRows()).WillOnce(GT::Return(rows));
    EXPECT_CALL(*boardMock, getNumOfColumns()).WillOnce(GT::Return(cols));

    EXPECT_CALL(*boardMock, visit(1u, 2u, GT::_));
    EXPECT_CALL(*boardMock, isVisitable(1u, 0u)).WillOnce(GT::Return(true));

    // when and then
    Pac p(
            1,
            2,
            moveResolution,
            startingDirection,
            boardMock,
            gameModeManagerMock,
            coinsCollectorMock,
            fruitsCollectorMock,
            scoreControllerMock,
            pacGraphicControllerMock);

    // given
    p.move();

    // expect
    const unsigned currentStep = 1;
    EXPECT_CALL(*pacGraphicControllerMock, draw(1, 2, 1, 3, currentStep, moveResolution));
    EXPECT_CALL(*pacGraphicControllerMock, draw(1, -1, 1, 0, currentStep, moveResolution));

    // when and then
    p.draw();

    // given
    p.move();

    // expect
    EXPECT_CALL(*boardMock, visit(1, 0, HasMemoryAddress(&p)));
    EXPECT_CALL(*boardMock, isVisitable(1, 1)).WillOnce(GT::Return(true));

    // when and then
    p.move();
}


TEST_F(PacTester, movesPacOutsideTopBoardsEdge)
{
    // given
    const unsigned long rows = 3;
    const unsigned long cols = 3;
    const Direction startingDirection = Direction::Up;

    // expect
    EXPECT_CALL(*boardMock, getNumOfRows()).WillOnce(GT::Return(rows));
    EXPECT_CALL(*boardMock, getNumOfColumns()).WillOnce(GT::Return(cols));

    EXPECT_CALL(*boardMock, visit(0u, 1u, GT::_));
    EXPECT_CALL(*boardMock, isVisitable(2u, 1u)).WillOnce(GT::Return(true));

    // when and then
    Pac p(
            0,
            1,
            moveResolution,
            startingDirection,
            boardMock,
            gameModeManagerMock,
            coinsCollectorMock,
            fruitsCollectorMock,
            scoreControllerMock,
            pacGraphicControllerMock);

    // given
    p.move();

    // expect
    const unsigned currentStep = 1;
    EXPECT_CALL(*pacGraphicControllerMock, draw(0, 1, -1, 1, currentStep, moveResolution));
    EXPECT_CALL(*pacGraphicControllerMock, draw(3, 1, 2, 1, currentStep, moveResolution));

    // when and then
    p.draw();

    // given
    p.move();

    // expect
    EXPECT_CALL(*boardMock, visit(2, 1, HasMemoryAddress(&p)));
    EXPECT_CALL(*boardMock, isVisitable(1, 1)).WillOnce(GT::Return(true));

    // when and then
    p.move();
}


TEST_F(PacTester, movesPacOutsideBottomBoardsEdge)
{
    // given
    const unsigned long rows = 3;
    const unsigned long cols = 3;
    const Direction startingDirection = Direction::Down;

    // expect
    EXPECT_CALL(*boardMock, getNumOfRows()).WillOnce(GT::Return(rows));
    EXPECT_CALL(*boardMock, getNumOfColumns()).WillOnce(GT::Return(cols));

    EXPECT_CALL(*boardMock, visit(2u, 1u, GT::_));
    EXPECT_CALL(*boardMock, isVisitable(0u, 1u)).WillOnce(GT::Return(true));

    // when and then
    Pac p(
            2,
            1,
            moveResolution,
            startingDirection,
            boardMock,
            gameModeManagerMock,
            coinsCollectorMock,
            fruitsCollectorMock,
            scoreControllerMock,
            pacGraphicControllerMock);

    // given
    p.move();

    // expect
    const unsigned currentStep = 1;
    EXPECT_CALL(*pacGraphicControllerMock, draw(2, 1, 3, 1, currentStep, moveResolution));
    EXPECT_CALL(*pacGraphicControllerMock, draw(-1, 1, 0, 1, currentStep, moveResolution));

    // when and then
    p.draw();

    // given
    p.move();

    // expect
    EXPECT_CALL(*boardMock, visit(0, 1, HasMemoryAddress(&p)));
    EXPECT_CALL(*boardMock, isVisitable(1, 1)).WillOnce(GT::Return(true));

    // when and then
    p.move();
}


TEST_F(PacTester, changesPacsDirectionToUp)
{
    // given
    const Direction newDirection = Direction::Up;

    // expect
    const int nextRow = startingRow - 1;
    const int nextColumn = startingColumn;
    EXPECT_CALL(*boardMock, isVisitable(nextRow, nextColumn)).WillOnce(GT::Return(true));

    // when
    pacInMovablePosition->setDirection(newDirection);

    // expect
    const unsigned currentStep = 0;
    EXPECT_CALL(*pacGraphicControllerMock, draw(startingRow, startingColumn, nextRow, nextColumn, currentStep, moveResolution));

    // then
    pacInMovablePosition->draw();
}


TEST_F(PacTester, changesPacsDirectionToDown)
{
    // given
    const Direction newDirection = Direction::Down;

    // expect
    const int nextRow = startingRow + 1;
    const int nextColumn = startingColumn;
    EXPECT_CALL(*boardMock, isVisitable(nextRow, nextColumn)).WillOnce(GT::Return(true));

    // when
    pacInMovablePosition->setDirection(newDirection);

    // expect
    const unsigned currentStep = 0;
    EXPECT_CALL(*pacGraphicControllerMock, draw(startingRow, startingColumn, nextRow, nextColumn, currentStep, moveResolution));

    // then
    pacInMovablePosition->draw();
}


TEST_F(PacTester, changesPacsDirectionToLeft)
{
    // given
    const Direction newDirection = Direction::Left;

    // expect
    const int nextRow = startingRow;
    const int nextColumn = startingColumn - 1;
    EXPECT_CALL(*boardMock, isVisitable(nextRow, nextColumn)).WillOnce(GT::Return(true));

    // when
    pacInMovablePosition->setDirection(newDirection);

    // expect
    const unsigned currentStep = 0;
    EXPECT_CALL(*pacGraphicControllerMock, draw(startingRow, startingColumn, nextRow, nextColumn, currentStep, moveResolution));

    // then
    pacInMovablePosition->draw();
}


TEST_F(PacTester, changesPacsDirectionToRight)
{
    // given
    const Direction newDirection = Direction::Right;

    // expect
    const int nextRow = startingRow;
    const int nextColumn = startingColumn + 1;
    EXPECT_CALL(*boardMock, isVisitable(nextRow, nextColumn)).WillOnce(GT::Return(true));

    // when
    pacInMovablePosition->setDirection(newDirection);

    // expect
    const unsigned currentStep = 0;
    EXPECT_CALL(*pacGraphicControllerMock, draw(startingRow, startingColumn, nextRow, nextColumn, currentStep, moveResolution));

    // then
    pacInMovablePosition->draw();
}


TEST_F(PacTester, changesPacsDirectionWhenPacIsMoving)
{
    // when
    pacInMovablePosition->move();

    // when
    const Direction newDirection = Direction::Right;
    pacInMovablePosition->setDirection(newDirection);

    // expect
    const unsigned currentStep = 1;
    int nextRow = startingRow - 1;
    int nextColumn = startingColumn;
    EXPECT_CALL(*pacGraphicControllerMock, draw(startingRow, startingColumn, nextRow, nextColumn, currentStep, moveResolution));

    // then
    pacInMovablePosition->draw();
    pacInMovablePosition->move();

    // expect
    EXPECT_CALL(*boardMock, visit(nextRow, nextColumn, HasMemoryAddress(pacInMovablePosition.get())));
    nextColumn = nextColumn + 1; // we changed direction to right
    EXPECT_CALL(*boardMock, isVisitable(nextRow, nextColumn)).WillOnce(GT::Return(true));

    // when and then
    pacInMovablePosition->move();
}


TEST_F(PacTester, eatsCoin)
{
    // expect
    EXPECT_CALL(*coinsCollectorMock, collectNextCoin());
    EXPECT_CALL(*scoreControllerMock, addCoinScore());

    // when and then
    pacInMovablePosition->eatCoin();
}


TEST_F(PacTester, eatsBigCoin)
{
    // expect
    EXPECT_CALL(*coinsCollectorMock, collectNextCoin());
    EXPECT_CALL(*scoreControllerMock, addBigCoinScore());
    EXPECT_CALL(*gameModeManagerMock, activateBigCoinMode());

    // when and then
    pacInMovablePosition->eatBigCoin();
}


TEST_F(PacTester, eatsFruit)
{
    // given
    std::shared_ptr<FruitMock> fruitMock(new GT::NiceMock<FruitMock>());

    // expect
    EXPECT_CALL(*fruitsCollectorMock, collectFruit(MatchSmartPointers(fruitMock)));

    // when and then
    pacInMovablePosition->eatFruit(fruitMock);
}


TEST_F(PacTester, resetsPac)
{
    // given
    pacInMovablePosition->move();

    // expect
    EXPECT_CALL(*boardMock, visit(startingRow, startingColumn, HasMemoryAddress(pacInMovablePosition.get())));
    EXPECT_CALL(*boardMock, isVisitable(startingRow - 1, startingColumn)).WillOnce(GT::Return(true));

    // when and then
    pacInMovablePosition->reset();
}


TEST_F(PacTester, resetsAndDrawsPac)
{
    // given
    pacInMovablePosition->move();

    EXPECT_CALL(*boardMock, visit(startingRow, startingColumn, HasMemoryAddress(pacInMovablePosition.get())));
    EXPECT_CALL(*boardMock, isVisitable(startingRow - 1, startingColumn)).WillOnce(GT::Return(true));

    pacInMovablePosition->reset();

    // expect
    const unsigned currentStep = 0;
    const int nextRow = startingRow - 1;
    const int nextColumn = startingColumn;
    EXPECT_CALL(*pacGraphicControllerMock, draw(startingRow, startingColumn, nextRow, nextColumn, currentStep, moveResolution));

    // when and then
    pacInMovablePosition->draw();
}


} // namespace Testing
} // namespace Model
} // namespace Model
