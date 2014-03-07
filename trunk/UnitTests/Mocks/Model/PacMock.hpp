#ifndef PACMAN_MODEL_TESTING_PACMOCK_HPP
#define PACMAN_MODEL_TESTING_PACMOCK_HPP


#include <gmock/gmock.h>

#include <Model/IPac.hpp>


namespace Pacman
{
namespace Model
{
namespace Testing
{


class PacMock : public IPac
{
public:
    MOCK_METHOD1(setDirection, void(Direction));
    MOCK_METHOD0(move, void());
    MOCK_CONST_METHOD0(getCurrentRow, int());
    MOCK_CONST_METHOD0(getCurrentColumn, int());
    MOCK_CONST_METHOD0(getCurrentX, double());
    MOCK_CONST_METHOD0(getCurrentY, double());
    MOCK_METHOD0(eatCoin, void());
    MOCK_METHOD0(eatBigCoin, void());
    MOCK_METHOD1(eatFruit, void(std::shared_ptr<IFruit>));
    MOCK_CONST_METHOD0(draw, void());
    MOCK_METHOD0(reset, void());
};


} // namespace Testing
} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_TESTING_PACMOCK_HPP
