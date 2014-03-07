#include <memory>
#include <utility>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <Model/Board.hpp>

#include <Mocks/Model/FieldMock.hpp>
#include <Mocks/Model/PacMock.hpp>
#include <Mocks/Presentation/BoardGraphicControllerMock.hpp>


namespace GT = testing;


namespace Pacman
{
namespace Model
{
namespace Testing
{


struct BoardTester : public GT::Test
{
    BoardTester()
    {
        std::vector<std::vector<std::shared_ptr<IField>>> fields(2);
        fields[0].push_back(fieldMock00);
        fields[0].push_back(fieldMock01);
        fields[0].push_back(fieldMock02);
        fields[1].push_back(fieldMock10);
        fields[1].push_back(fieldMock11);
        fields[1].push_back(fieldMock12);

        board = std::make_unique<Board>(std::move(fields), boardGraphicControllerMock);
    }

    // mocks:
    std::shared_ptr<Presentation::Testing::BoardGraphicControllerMock> boardGraphicControllerMock =
            std::make_shared<GT::StrictMock<Presentation::Testing::BoardGraphicControllerMock>>();

    std::shared_ptr<FieldMock> fieldMock00 = std::make_shared<GT::StrictMock<FieldMock>>();
    std::shared_ptr<FieldMock> fieldMock01 = std::make_shared<GT::StrictMock<FieldMock>>();
    std::shared_ptr<FieldMock> fieldMock02 = std::make_shared<GT::StrictMock<FieldMock>>();
    std::shared_ptr<FieldMock> fieldMock10 = std::make_shared<GT::StrictMock<FieldMock>>();
    std::shared_ptr<FieldMock> fieldMock11 = std::make_shared<GT::StrictMock<FieldMock>>();
    std::shared_ptr<FieldMock> fieldMock12 = std::make_shared<GT::StrictMock<FieldMock>>();

    // tested class:
    std::unique_ptr<Board> board;
};


MATCHER_P(HasMemoryAddress, address, "") { return &arg == address; }


TEST_F(BoardTester, getsBoardSizes)
{
    // when
    unsigned long rows = board->getNumOfRows();
    unsigned long cols = board->getNumOfColumns();

    // then
    EXPECT_EQ(2u, rows);
    EXPECT_EQ(3u, cols);
}


TEST_F(BoardTester, drawsBoard)
{
    // expect
    EXPECT_CALL(*fieldMock00, draw(HasMemoryAddress(boardGraphicControllerMock.get())));
    EXPECT_CALL(*fieldMock01, draw(HasMemoryAddress(boardGraphicControllerMock.get())));
    EXPECT_CALL(*fieldMock02, draw(HasMemoryAddress(boardGraphicControllerMock.get())));
    EXPECT_CALL(*fieldMock10, draw(HasMemoryAddress(boardGraphicControllerMock.get())));
    EXPECT_CALL(*fieldMock11, draw(HasMemoryAddress(boardGraphicControllerMock.get())));
    EXPECT_CALL(*fieldMock12, draw(HasMemoryAddress(boardGraphicControllerMock.get())));

    // when and then
    board->draw();
}


TEST_F(BoardTester, checksFieldVisitability)
{
    // given
    const unsigned row = 0;
    const unsigned column = 2;

    // expect
    EXPECT_CALL(*fieldMock02, isVisitable()).WillOnce(GT::Return(true));

    // when
    const bool visitable = board->isVisitable(row, column);

    // then
    EXPECT_TRUE(visitable);
}


TEST_F(BoardTester, checksFieldUnvisitability)
{
    // given
    const unsigned row = 1;
    const unsigned column = 1;

    // expect
    EXPECT_CALL(*fieldMock11, isVisitable()).WillOnce(GT::Return(false));

    // when
    const bool visitable = board->isVisitable(row, column);

    // then
    EXPECT_FALSE(visitable);
}


TEST_F(BoardTester, visitsField)
{
    // given
    const unsigned row = 0;
    const unsigned column = 2;
    GT::StrictMock<PacMock> pacMock;

    // expect
    EXPECT_CALL(*fieldMock02, visit(HasMemoryAddress(&pacMock)));

    // when and then
    board->visit(row, column, pacMock);
}


TEST_F(BoardTester, checksIfTwoSameFieldsAreInTheSameHole)
{
    // given
    const unsigned field11Row = 1;
    const unsigned field11Column = 1;

    // expect
    EXPECT_CALL(*fieldMock11, isVisitable())
            .Times(2)
            .WillRepeatedly(GT::Return(true));

    // when and then
    EXPECT_TRUE(board->areInTheSameHole(field11Row, field11Column, field11Row, field11Column));
}


TEST_F(BoardTester, checksIfTwoFieldsInTheSameRowAreInTheSameHole)
{
    // given
    const unsigned field00Row = 0;
    const unsigned field00Column = 0;

    const unsigned field02Row = 0;
    const unsigned field02Column = 2;

    // expect
    EXPECT_CALL(*fieldMock00, isVisitable()).WillOnce(GT::Return(true));
    EXPECT_CALL(*fieldMock02, isVisitable()).WillOnce(GT::Return(true));
    EXPECT_CALL(*fieldMock01, isVisitable()).WillOnce(GT::Return(true));

    // when and then
    EXPECT_TRUE(board->areInTheSameHole(field00Row, field00Column, field02Row, field02Column));

    // expect
    EXPECT_CALL(*fieldMock00, isVisitable()).WillOnce(GT::Return(true));
    EXPECT_CALL(*fieldMock02, isVisitable()).WillOnce(GT::Return(true));
    EXPECT_CALL(*fieldMock01, isVisitable()).WillOnce(GT::Return(false)); // wall between the two fields

    // when and then
    EXPECT_FALSE(board->areInTheSameHole(field00Row, field00Column, field02Row, field02Column));
}


TEST_F(BoardTester, checksIfTwoFieldsInTheSameColumnAreInTheSameHole)
{
    // given
    const unsigned field00Row = 0;
    const unsigned field00Column = 0;

    const unsigned field10Row = 1;
    const unsigned field10Column = 0;

    // expect
    EXPECT_CALL(*fieldMock00, isVisitable()).WillOnce(GT::Return(true));
    EXPECT_CALL(*fieldMock10, isVisitable()).WillOnce(GT::Return(true));

    // when and then
    EXPECT_TRUE(board->areInTheSameHole(field00Row, field00Column, field10Row, field10Column));
}


TEST_F(BoardTester, checksIfTwoFieldsWithDifferentRowsAndColumnsAreInTheSameHole)
{
    // given
    const unsigned field00Row = 0;
    const unsigned field00Column = 0;

    const unsigned field11Row = 1;
    const unsigned field11Column = 1;

    // expect
    EXPECT_CALL(*fieldMock00, isVisitable()).WillOnce(GT::Return(true));
    EXPECT_CALL(*fieldMock11, isVisitable()).WillOnce(GT::Return(true));

    // when and then
    EXPECT_FALSE(board->areInTheSameHole(field00Row, field00Column, field11Row, field11Column));
}


TEST_F(BoardTester, resetsBoard)
{
    // expect
    EXPECT_CALL(*fieldMock00, reset());
    EXPECT_CALL(*fieldMock01, reset());
    EXPECT_CALL(*fieldMock02, reset());
    EXPECT_CALL(*fieldMock10, reset());
    EXPECT_CALL(*fieldMock11, reset());
    EXPECT_CALL(*fieldMock12, reset());

    // when and then
    board->reset();
}


} // namespace Testing
} // namespace Model
} // namespace Pacman
