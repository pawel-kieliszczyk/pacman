#ifndef PACMAN_MODEL_TESTING_FIELDMOCK_HPP
#define PACMAN_MODEL_TESTING_FIELDMOCK_HPP


#include <gmock/gmock.h>

#include <Model/IField.hpp>
#include <Model/IFruitVisibilityManager.hpp>


namespace Pacman
{
namespace Model
{
namespace Testing
{


class FieldMock : public IField
{
public:
    MOCK_CONST_METHOD0(isVisitable, bool());
    MOCK_METHOD1(visit, void(IPac&));
    MOCK_CONST_METHOD1(draw, void(Presentation::IBoardGraphicController&));
    MOCK_METHOD0(reset, void());
};


class FieldAndFruitVisibilityManagerMock : public IField, public IFruitVisibilityManager
{
public:
    MOCK_CONST_METHOD0(isVisitable, bool());
    MOCK_METHOD1(visit, void(IPac&));
    MOCK_CONST_METHOD1(draw, void(Presentation::IBoardGraphicController&));
    MOCK_METHOD0(reset, void());

    MOCK_METHOD1(showFruit, void(std::shared_ptr<IFruit>));
    MOCK_METHOD0(hideFruit, void());
};


} // namespace Testing
} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_TESTING_FIELDMOCK_HPP
