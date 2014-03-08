#include <memory>
#include <utility>

#include <Model/FieldsData.hpp>


namespace Pacman
{
namespace Model
{


FieldsData::FieldsData(
            std::vector<std::vector<std::shared_ptr<IField>>>&& fields_,
            unsigned long pacsStartingRow_,
            unsigned long pacsStartingColumn_,
            unsigned long ghostsStartingRow_,
            unsigned long ghostsStartingColumn_,
            unsigned long fruitFieldRow_,
            unsigned long fruitFieldColumn_,
            unsigned coinsToCollect_)
    : fields(fields_),
      pacsStartingRow(pacsStartingRow_),
      pacsStartingColumn(pacsStartingColumn_),
      ghostsStartingRow(ghostsStartingRow_),
      ghostsStartingColumn(ghostsStartingColumn_),
      fruitField(std::dynamic_pointer_cast<IFruitVisibilityManager>(fields[fruitFieldRow_][fruitFieldColumn_])),
      coinsToCollect(coinsToCollect_)
{
}


std::vector<std::vector<std::shared_ptr<IField>>> FieldsData::getFields()
{
    return std::move(fields);
}


unsigned long FieldsData::getPacsStartingRow()
{
    return pacsStartingRow;
}


unsigned long FieldsData::getPacsStartingColumn()
{
    return pacsStartingColumn;
}


unsigned long FieldsData::getGhostsStartingRow()
{
    return ghostsStartingRow;
}


unsigned long FieldsData::getGhostsStartingColumn()
{
    return ghostsStartingColumn;
}


std::shared_ptr<IFruitVisibilityManager> FieldsData::getFruitField()
{
    return fruitField;
}


unsigned FieldsData::getNumOfCoinsToCollect()
{
    return coinsToCollect;
}


} // namespace Model
} // namespace Pacman
