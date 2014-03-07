#ifndef PACMAN_MODEL_FIELDSDATA_HPP
#define PACMAN_MODEL_FIELDSDATA_HPP


#include <memory>
#include <vector>

#include <Model/IField.hpp>
#include <Model/IFruitVisibilityManager.hpp>


namespace Pacman
{
namespace Model
{


class FieldsData
{
public:
    FieldsData(
            std::vector<std::vector<std::shared_ptr<IField>>>&& fields_,
            unsigned long pacsStartingRow_,
            unsigned long pacsStartingColumn_,
            unsigned long ghostsStartingRow_,
            unsigned long ghostsStartingColumn_,
            unsigned long fruitFieldRow_,
            unsigned long fruitFieldColumn_,
            unsigned coinsToCollect_);

    std::vector<std::vector<std::shared_ptr<IField>>> getFields();

    unsigned long getPacsStartingRow();
    unsigned long getPacsStartingColumn();

    unsigned long getGhostsStartingRow();
    unsigned long getGhostsStartingColumn();

    std::shared_ptr<IFruitVisibilityManager> getFruitField();

    unsigned getNumOfCoinsToCollect();

private:
    std::vector<std::vector<std::shared_ptr<IField>>> fields;
    const unsigned long pacsStartingRow;
    const unsigned long pacsStartingColumn;
    const unsigned long ghostsStartingRow;
    const unsigned long ghostsStartingColumn;
    std::shared_ptr<IFruitVisibilityManager> fruitField;
    const unsigned coinsToCollect;
};


} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_FIELDSDATA_HPP
