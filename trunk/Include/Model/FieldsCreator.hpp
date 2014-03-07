#ifndef PACMAN_MODEL_FIELDSCREATOR_HPP
#define PACMAN_MODEL_FIELDSCREATOR_HPP


#include <memory>
#include <type_traits>
#include <vector>

#include <Model/FieldsData.hpp>


namespace Pacman
{
namespace Model
{


class FieldsCreator
{
public:
    static FieldsData create();

private:
    template<unsigned Row, class... Fields>
    static std::vector<std::shared_ptr<IField>> createRow();

    template<unsigned Row, unsigned Col, class Field, class... Fields>
    static void createRow(
            std::vector<std::shared_ptr<IField>>& row,
            typename std::enable_if<(sizeof...(Fields) > 0)>::type* = 0);

    template<unsigned Row, unsigned Col, class Field, class... Fields>
    static void createRow(
            std::vector<std::shared_ptr<IField>>& row,
            typename std::enable_if<(sizeof...(Fields) == 0)>::type* = 0);
};


} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_FIELDSCREATOR_HPP
