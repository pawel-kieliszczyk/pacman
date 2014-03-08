#ifndef PACMAN_MODEL_TESTING_BOARDMOCK_HPP
#define PACMAN_MODEL_TESTING_BOARDMOCK_HPP


#include <gmock/gmock.h>

#include <Model/IBoard.hpp>


namespace Pacman
{
namespace Model
{
namespace Testing
{


class BoardMock : public IBoard
{
public:
    MOCK_CONST_METHOD0(getNumOfRows, unsigned long());
    MOCK_CONST_METHOD0(getNumOfColumns, unsigned long());
    MOCK_CONST_METHOD2(isVisitable, bool(unsigned, unsigned));
    MOCK_METHOD3(visit, void(unsigned, unsigned, IPac&));
    MOCK_CONST_METHOD4(areInTheSameHole, bool(unsigned, unsigned, unsigned, unsigned));
    MOCK_CONST_METHOD0(draw, void());
    MOCK_METHOD0(reset, void());
};


} // namespace Testing
} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_TESTING_BOARDMOCK_HPP
