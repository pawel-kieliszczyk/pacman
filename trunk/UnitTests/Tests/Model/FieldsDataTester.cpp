#include <memory>
#include <utility>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <Model/FieldsData.hpp>

#include <Mocks/Model/FieldMock.hpp>


namespace GT = testing;


namespace Pacman
{
namespace Model
{
namespace Testing
{


struct FieldsDataTester : public GT::Test
{
    FieldsDataTester()
    {
        std::vector<std::vector<std::shared_ptr<IField>>> fields{{fieldMock00}, {fieldMock10}};

        fieldsData = std::make_unique<FieldsData>(
                std::move(fields),
                pacsStartingRow,
                pacsStartingColumn,
                ghostsStartingRow,
                ghostsStartingColumn,
                fruitFieldRow,
                fruitFieldColumn,
                coinsToCollect);
    }

    const unsigned long pacsStartingRow = 1;
    const unsigned long pacsStartingColumn = 0;
    const unsigned long ghostsStartingRow = 0;
    const unsigned long ghostsStartingColumn = 1;
    const unsigned long fruitFieldRow = 1;
    const unsigned long fruitFieldColumn = 0;
    const unsigned coinsToCollect = 2;

    //mocks:
    std::shared_ptr<FieldMock> fieldMock00 =
            std::make_shared<GT::NiceMock<FieldMock>>();
    std::shared_ptr<FieldAndFruitVisibilityManagerMock> fieldMock10 =
            std::make_shared<GT::NiceMock<FieldAndFruitVisibilityManagerMock>>();

    // tested class:
    std::unique_ptr<FieldsData> fieldsData;
};


TEST_F(FieldsDataTester, getsFieldsData)
{
    std::vector<std::vector<std::shared_ptr<IField>>> fields = fieldsData->getFields();

    EXPECT_EQ(fields[0][0].get(), fieldMock00.get());
    EXPECT_EQ(fields[1][0].get(), fieldMock10.get());

    EXPECT_EQ(pacsStartingRow, fieldsData->getPacsStartingRow());
    EXPECT_EQ(pacsStartingColumn, fieldsData->getPacsStartingColumn());

    EXPECT_EQ(ghostsStartingRow, fieldsData->getGhostsStartingRow());
    EXPECT_EQ(ghostsStartingColumn, fieldsData->getGhostsStartingColumn());

    EXPECT_EQ(fieldMock10.get(), std::dynamic_pointer_cast<FieldAndFruitVisibilityManagerMock>(fieldsData->getFruitField()).get());

    EXPECT_EQ(coinsToCollect, fieldsData->getNumOfCoinsToCollect());
}


} // namespace Testing
} // namespace Model
} // namespace Pacman
