#ifndef PACMAN_MODEL_TESTING_COINSCOLLECTORMOCK_HPP
#define PACMAN_MODEL_TESTING_COINSCOLLECTORMOCK_HPP


#include <gmock/gmock.h>

#include <Model/ICoinsCollector.hpp>


namespace Pacman
{
namespace Model
{
namespace Testing
{


class CoinsCollectorMock : public ICoinsCollector
{
public:
    MOCK_METHOD0(collectNextCoin, void());
    MOCK_CONST_METHOD0(allCoinsCollected, bool());
    MOCK_METHOD0(reset, void());
};


} // namespace Testing
} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_TESTING_COINSCOLLECTORMOCK_HPP
