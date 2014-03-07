#ifndef PACMAN_MODEL_BIGCOINFIELD_HPP
#define PACMAN_MODEL_BIGCOINFIELD_HPP


#include <Model/FieldBase.hpp>


namespace Pacman
{
namespace Model
{


class BigCoinField : public FieldBase
{
public:
    BigCoinField(unsigned row, unsigned col);

    bool isVisitable() const override;
    void visit(IPac& pac) override;
    void draw(Presentation::IBoardGraphicController& graphicController) const override;
    void reset() override;

private:
    bool visited;
};


} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_BIGCOINFIELD_HPP
