#ifndef PACMAN_MODEL_TESTING_FRUITSCOLLECTORMOCK_HPP
#define PACMAN_MODEL_TESTING_FRUITSCOLLECTORMOCK_HPP


#include <gmock/gmock.h>

#include <Model/IFruitsCollector.hpp>


namespace Pacman
{
namespace Model
{
namespace Testing
{


class FruitsCollectorMock : public IFruitsCollector
{
public:
    MOCK_METHOD1(collectFruit, void(std::shared_ptr<IFruit>));
    MOCK_CONST_METHOD0(drawFruits, void());
    MOCK_METHOD0(reset, void());
};


} // namespace Testing
} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_TESTING_FRUITSCOLLECTORMOCK_HPP
