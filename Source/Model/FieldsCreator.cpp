#include <memory>

#include <Model/BigCoinField.hpp>
#include <Model/CoinField.hpp>
#include <Model/EmptyField.hpp>
#include <Model/FruitField.hpp>
#include <Model/FieldsCreator.hpp>
#include <Model/WallField.hpp>


namespace Pacman
{
namespace Model
{


FieldsData FieldsCreator::create()
{
    std::vector<std::vector<std::shared_ptr<IField>>> fields;

    typedef CoinField C;
    typedef BigCoinField B;
    typedef FruitField F;
    typedef EmptyField E;
    typedef WallField W;

//    fields.push_back(createRow< 0, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W>());
//    fields.push_back(createRow< 1, W, C, C, C, C, C, C, C, C, C, C, C, C, W, C, C, C, C, C, C, C, C, C, C, C, C, W>());
//    fields.push_back(createRow< 2, W, C, W, W, W, W, C, W, W, W, W, W, C, W, C, W, W, W, W, W, C, W, W, W, W, C, W>());
//    fields.push_back(createRow< 3, W, B, W, W, W, W, C, W, W, W, W, W, C, W, C, W, W, W, W, W, C, W, W, W, W, B, W>());
//    fields.push_back(createRow< 4, W, C, W, W, W, W, C, W, W, W, W, W, C, W, C, W, W, W, W, W, C, W, W, W, W, C, W>());
//    fields.push_back(createRow< 5, W, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, W>());
//    fields.push_back(createRow< 6, W, C, W, W, W, W, C, W, W, C, W, W, W, W, W, W, W, C, W, W, C, W, W, W, W, C, W>());
//    fields.push_back(createRow< 7, W, C, W, W, W, W, C, W, W, C, W, W, W, W, W, W, W, C, W, W, C, W, W, W, W, C, W>());
//    fields.push_back(createRow< 8, W, C, C, C, C, C, C, W, W, C, C, C, C, W, C, C, C, C, W, W, C, C, C, C, C, C, W>());
//    fields.push_back(createRow< 9, W, W, W, W, W, W, C, W, W, W, W, W, E, W, E, W, W, W, W, W, C, W, W, W, W, W, W>());
//    fields.push_back(createRow<10, E, E, E, E, E, W, C, W, W, W, W, W, E, W, E, W, W, W, W, W, C, W, E, E, E, E, E>());
//    fields.push_back(createRow<11, E, E, E, E, E, W, C, W, W, E, E, E, E, E, E, E, E, E, W, W, C, W, E, E, E, E, E>());
//    fields.push_back(createRow<12, E, E, E, E, E, W, C, W, W, E, W, W, W, E, W, W, W, E, W, W, C, W, E, E, E, E, E>());
//    fields.push_back(createRow<13, W, W, W, W, W, W, C, E, E, E, W, W, W, E, W, W, W, E, E, E, C, W, W, W, W, W, W>());
//    fields.push_back(createRow<14, E, E, E, E, E, E, C, W, W, E, E, E, E, F, E, E, E, E, W, W, C, E, E, E, E, E, E>());
//    fields.push_back(createRow<15, W, W, W, W, W, W, C, E, E, E, W, W, W, E, W, W, W, E, E, E, C, W, W, W, W, W, W>());
//    fields.push_back(createRow<16, E, E, E, E, E, W, C, W, W, E, W, W, W, E, W, W, W, E, W, W, C, W, E, E, E, E, E>());
//    fields.push_back(createRow<17, E, E, E, E, E, W, C, W, W, E, E, E, E, E, E, E, E, E, W, W, C, W, E, E, E, E, E>());
//    fields.push_back(createRow<18, E, E, E, E, E, W, C, W, W, E, W, W, W, W, W, W, W, E, W, W, C, W, E, E, E, E, E>());
//    fields.push_back(createRow<19, W, W, W, W, W, W, C, W, W, E, W, W, W, W, W, W, W, E, W, W, C, W, W, W, W, W, W>());
//    fields.push_back(createRow<20, W, C, C, C, C, C, C, C, C, C, C, C, C, W, C, C, C, C, C, C, C, C, C, C, C, C, W>());
//    fields.push_back(createRow<21, W, C, W, W, W, W, C, W, W, W, W, W, C, W, C, W, W, W, W, W, C, W, W, W, W, C, W>());
//    fields.push_back(createRow<22, W, C, W, W, W, W, C, W, W, W, W, W, C, W, C, W, W, W, W, W, C, W, W, W, W, C, W>());
//    fields.push_back(createRow<23, W, B, C, C, W, W, C, C, C, C, C, C, C, E, C, C, C, C, C, C, C, W, W, C, C, B, W>());
//    fields.push_back(createRow<24, W, W, W, C, W, W, C, W, W, C, W, W, W, W, W, W, W, C, W, W, C, W, W, C, W, W, W>());
//    fields.push_back(createRow<25, W, W, W, C, W, W, C, W, W, C, W, W, W, W, W, W, W, C, W, W, C, W, W, C, W, W, W>());
//    fields.push_back(createRow<26, W, C, C, C, C, C, C, W, W, C, C, C, C, W, C, C, C, C, W, W, C, C, C, C, C, C, W>());
//    fields.push_back(createRow<27, W, C, W, W, W, W, W, W, W, W, W, W, C, W, C, W, W, W, W, W, W, W, W, W, W, C, W>());
//    fields.push_back(createRow<28, W, C, W, W, W, W, W, W, W, W, W, W, C, W, C, W, W, W, W, W, W, W, W, W, W, C, W>());
//    fields.push_back(createRow<29, W, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, W>());
//    fields.push_back(createRow<30, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W>());
//
//    const unsigned long pacsStartingRow = 23;
//    const unsigned long pacsStartingColumn = 13;
//    const unsigned long ghostsStartingRow = 14;
//    const unsigned long ghostsStartingColumn = 13;
//    const unsigned long fruitFieldRow = 14;
//    const unsigned long fruitFieldColumn = 13;
//    const unsigned coinsToCollect = 242;

    fields.push_back(createRow< 0, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W>());
    fields.push_back(createRow< 1, W, C, C, C, C, C, C, C, C, C, C, C, C, W, W, C, C, C, C, C, C, C, C, C, C, W, C, C, C, C, C, C, C, C, C, C, W, W, C, C, C, C, C, C, C, C, C, C, C, C, W>());
    fields.push_back(createRow< 2, W, C, W, W, W, W, C, W, W, W, W, W, C, W, W, C, W, W, W, W, W, W, W, W, C, W, C, W, W, W, W, W, W, W, W, C, W, W, C, W, W, W, W, W, C, W, W, W, W, C, W>());
    fields.push_back(createRow< 3, W, B, W, W, W, W, C, W, W, W, W, W, C, W, W, C, W, W, W, W, W, W, W, W, C, W, C, W, W, W, W, W, W, W, W, C, W, W, C, W, W, W, W, W, C, W, W, W, W, B, W>());
    fields.push_back(createRow< 4, W, C, W, W, W, W, C, W, W, W, W, W, C, W, W, C, W, W, W, W, W, W, W, W, C, W, C, W, W, W, W, W, W, W, W, C, W, W, C, W, W, W, W, W, C, W, W, W, W, C, W>());
    fields.push_back(createRow< 5, W, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, W>());
    fields.push_back(createRow< 6, W, C, W, W, W, W, C, W, W, C, W, W, W, W, W, W, W, W, C, W, W, C, W, W, W, W, W, W, W, C, W, W, C, W, W, W, W, W, W, W, W, C, W, W, C, W, W, W, W, C, W>());
    fields.push_back(createRow< 7, W, C, W, W, W, W, C, W, W, C, W, W, W, W, W, W, W, W, C, W, W, C, W, W, W, W, W, W, W, C, W, W, C, W, W, W, W, W, W, W, W, C, W, W, C, W, W, W, W, C, W>());
    fields.push_back(createRow< 8, W, C, C, C, C, C, C, W, W, C, C, C, C, W, W, C, C, C, C, W, W, C, C, C, C, W, C, C, C, C, W, W, C, C, C, C, W, W, C, C, C, C, W, W, C, C, C, C, C, C, W>());
    fields.push_back(createRow< 9, W, W, W, W, W, W, C, W, W, C, W, W, C, W, W, C, W, W, W, W, W, W, W, W, C, W, C, W, W, W, W, W, W, W, W, C, W, W, C, W, W, C, W, W, C, W, W, W, W, W, W>());
    fields.push_back(createRow<10, E, E, E, E, E, W, C, W, W, C, W, W, C, W, W, C, W, W, W, W, W, W, W, W, C, W, C, W, W, W, W, W, W, W, W, C, W, W, C, W, W, C, W, W, C, W, E, E, E, E, E>());
    fields.push_back(createRow<11, E, E, E, E, E, W, C, W, W, C, W, W, C, C, C, C, C, C, C, W, W, E, E, E, E, E, E, E, E, E, W, W, C, C, C, C, C, C, C, W, W, C, W, W, C, W, E, E, E, E, E>());
    fields.push_back(createRow<12, E, E, E, E, E, W, C, W, W, C, W, W, C, W, W, W, W, W, C, W, W, E, W, W, W, E, W, W, W, E, W, W, C, W, W, W, W, W, C, W, W, C, W, W, C, W, E, E, E, E, E>());
    fields.push_back(createRow<13, W, W, W, W, W, W, C, W, W, C, W, W, C, W, W, W, W, W, C, W, W, E, W, W, W, E, W, W, W, E, W, W, C, W, W, W, W, W, C, W, W, C, W, W, C, W, W, W, W, W, W>());
    fields.push_back(createRow<14, E, E, E, E, E, E, C, C, C, C, C, C, C, W, W, C, C, C, C, C, C, E, E, E, E, F, E, E, E, E, C, C, C, C, C, C, W, W, C, C, C, C, C, C, C, E, E, E, E, E, E>());
    fields.push_back(createRow<15, W, W, W, W, W, W, C, W, W, C, W, W, W, W, W, C, W, W, W, W, W, E, W, W, W, E, W, W, W, E, W, W, W, W, W, C, W, W, W, W, W, C, W, W, C, W, W, W, W, W, W>());
    fields.push_back(createRow<16, E, E, E, E, E, W, C, W, W, C, W, W, W, W, W, C, W, W, W, W, W, E, W, W, W, E, W, W, W, E, W, W, W, W, W, C, W, W, W, W, W, C, W, W, C, W, E, E, E, E, E>());
    fields.push_back(createRow<17, E, E, E, E, E, W, C, W, W, C, C, C, C, C, C, C, C, C, C, W, W, E, E, E, E, E, E, E, E, E, W, W, C, C, C, C, C, C, C, C, C, C, W, W, C, W, E, E, E, E, E>());
    fields.push_back(createRow<18, E, E, E, E, E, W, C, W, W, C, W, W, W, W, W, W, W, W, C, W, W, C, W, W, W, W, W, W, W, C, W, W, C, W, W, W, W, W, W, W, W, C, W, W, C, W, E, E, E, E, E>());
    fields.push_back(createRow<19, W, W, W, W, W, W, C, W, W, C, W, W, W, W, W, W, W, W, C, W, W, C, W, W, W, W, W, W, W, C, W, W, C, W, W, W, W, W, W, W, W, C, W, W, C, W, W, W, W, W, W>());
    fields.push_back(createRow<20, W, C, C, C, C, C, C, C, C, C, C, C, C, W, W, C, C, C, C, C, C, C, C, C, C, W, C, C, C, C, C, C, C, C, C, C, W, W, C, C, C, C, C, C, C, C, C, C, C, C, W>());
    fields.push_back(createRow<21, W, C, W, W, W, W, C, W, W, W, W, W, C, W, W, C, W, W, W, W, W, W, W, W, C, W, C, W, W, W, W, W, W, W, W, C, W, W, C, W, W, W, W, W, C, W, W, W, W, C, W>());
    fields.push_back(createRow<22, W, C, W, W, W, W, C, W, W, W, W, W, C, W, W, C, W, W, W, W, W, W, W, W, C, W, C, W, W, W, W, W, W, W, W, C, W, W, C, W, W, W, W, W, C, W, W, W, W, C, W>());
    fields.push_back(createRow<23, W, B, C, C, W, W, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, W, W, C, C, B, W>());
    fields.push_back(createRow<24, W, W, W, C, W, W, C, W, W, C, W, W, W, W, W, W, W, W, C, W, W, C, W, W, W, W, W, W, W, C, W, W, C, W, W, W, W, W, W, W, W, C, W, W, C, W, W, C, W, W, W>());
    fields.push_back(createRow<25, W, W, W, C, W, W, C, W, W, C, W, W, W, W, W, W, W, W, C, W, W, C, W, W, W, W, W, W, W, C, W, W, C, W, W, W, W, W, W, W, W, C, W, W, C, W, W, C, W, W, W>());
    fields.push_back(createRow<26, W, C, C, C, C, C, C, W, W, C, C, C, C, W, W, C, C, C, C, W, W, C, C, C, C, W, C, C, C, C, W, W, C, C, C, C, W, W, C, C, C, C, W, W, C, C, C, C, C, C, W>());
    fields.push_back(createRow<27, W, C, W, W, W, W, W, W, W, W, W, W, C, W, W, C, W, W, W, W, W, W, W, W, C, W, C, W, W, W, W, W, W, W, W, C, W, W, C, W, W, W, W, W, W, W, W, W, W, C, W>());
    fields.push_back(createRow<28, W, C, W, W, W, W, W, W, W, W, W, W, C, W, W, C, W, W, W, W, W, W, W, W, C, W, C, W, W, W, W, W, W, W, W, C, W, W, C, W, W, W, W, W, W, W, W, W, W, C, W>());
    fields.push_back(createRow<29, W, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, W>());
    fields.push_back(createRow<30, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W>());

    const unsigned long pacsStartingRow = 23;
    const unsigned long pacsStartingColumn = 25;
    const unsigned long ghostsStartingRow = 14;
    const unsigned long ghostsStartingColumn = 25;
    const unsigned long fruitFieldRow = 14;
    const unsigned long fruitFieldColumn = 25;
    const unsigned coinsToCollect = 539;

    return FieldsData(
            std::move(fields),
            pacsStartingRow,
            pacsStartingColumn,
            ghostsStartingRow,
            ghostsStartingColumn,
            fruitFieldRow,
            fruitFieldColumn,
            coinsToCollect);
}


template<unsigned Row, class... Fields>
std::vector<std::shared_ptr<IField>> FieldsCreator::createRow()
{
    std::vector<std::shared_ptr<IField>> row;
    createRow<Row, 0u, Fields...>(row);
    return row;
}


template<unsigned Row, unsigned Col, class Field, class... Fields>
void FieldsCreator::createRow(
        std::vector<std::shared_ptr<IField>>& row,
        typename std::enable_if<(sizeof...(Fields) > 0)>::type*)
{
    row.push_back(std::make_shared<Field>(Row, Col));
    createRow<Row, Col + 1, Fields...>(row);
}


template<unsigned Row, unsigned Col, class Field, class... Fields>
void FieldsCreator::createRow(
        std::vector<std::shared_ptr<IField>>& row,
        typename std::enable_if<(sizeof...(Fields) == 0)>::type*)
{
    row.push_back(std::make_shared<Field>(Row, Col));
}


} // namespace Model
} // namespace Pacman
