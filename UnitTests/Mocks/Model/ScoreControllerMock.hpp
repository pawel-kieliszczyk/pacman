#ifndef PACMAN_MODEL_TESTING_SCORECONTROLLERMOCK_HPP
#define PACMAN_MODEL_TESTING_SCORECONTROLLERMOCK_HPP


#include <gmock/gmock.h>

#include <Model/IScoreController.hpp>


namespace Pacman
{
namespace Model
{
namespace Testing
{


class ScoreControllerMock : public IScoreController
{
public:
    MOCK_METHOD0(addCoinScore, void());
    MOCK_METHOD0(addBigCoinScore, void());
    MOCK_METHOD0(addGhostScore, void());
    MOCK_CONST_METHOD0(drawScore, void());
    MOCK_METHOD0(reset, void());
};


} // namespace Testing
} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_TESTING_SCORECONTROLLERMOCK_HPP
