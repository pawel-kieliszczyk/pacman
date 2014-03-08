#ifndef PACMAN_MODEL_TESTING_FRUITVISIBILITYMANAGERMOCK_HPP
#define PACMAN_MODEL_TESTING_FRUITVISIBILITYMANAGERMOCK_HPP


#include <gmock/gmock.h>

#include <Model/IFruitVisibilityManager.hpp>


namespace Pacman
{
namespace Model
{
namespace Testing
{


class FruitVisibilityManagerMock : public IFruitVisibilityManager
{
public:
    MOCK_METHOD1(showFruit, void(std::shared_ptr<IFruit>));
    MOCK_METHOD0(hideFruit, void());
};


} // namespace Testing
} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_TESTING_FRUITVISIBILITYMANAGERMOCK_HPP
