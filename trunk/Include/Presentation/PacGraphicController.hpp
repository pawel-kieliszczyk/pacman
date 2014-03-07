#ifndef PACMAN_PRESENTATION_PACGRAPHICCONTROLLER_HPP
#define PACMAN_PRESENTATION_PACGRAPHICCONTROLLER_HPP


#include <memory>
#include <vector>

#include <cinder/Vector.h>

#include <Model/Direction.hpp>
#include <Presentation/IDirectionCalculator.hpp>
#include <Presentation/IPacGraphicController.hpp>


namespace Pacman
{
namespace Presentation
{


class PacGraphicController : public IPacGraphicController
{
public:
    PacGraphicController(
            unsigned fieldSize_,
            unsigned horizontalOffset_,
            float pacSizeScale,
            std::shared_ptr<IDirectionCalculator> directionCalculator_);

    void draw(
            int fromRow,
            int fromColumn,
            int toRow,
            int toColumn,
            unsigned step,
            unsigned resolution) override;

private:
    void calculateDirection(
            int fromRow,
            int fromColumn,
            int toRow,
            int toColumn);

    void alignAlphaToDirection(float& alpha) const;

    void alignPacsCenterToDirection(ci::Vec2f& center) const;

    std::vector<ci::Vec2f> createPacsSkeleton(
            unsigned step,
            unsigned resolution) const;

    ci::Vec2f calculatePacsPosition(
            int fromRow,
            int fromColumn,
            int toRow,
            int toColumn,
            unsigned step,
            unsigned resolution) const;

    std::vector<ci::Vec2f> createPacsBorderPoints(
            const std::vector<ci::Vec2f>& skeleton,
            const ci::Vec2f& position) const;

    void drawPacsBody(const std::vector<ci::Vec2f>& points);

    void drawPacsBorder(const std::vector<ci::Vec2f>& points);

    const unsigned fieldSize;
    const unsigned horizontalOffset;

    std::shared_ptr<IDirectionCalculator> directionCalculator;

    const float pacSize;

    const float PI;

    Model::Direction direction;
};


} // namespace Presentation
} // namespace Pacman


#endif // PACMAN_PRESENTATION_PACGRAPHICCONTROLLER_HPP
