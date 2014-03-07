#ifndef PACMAN_PRESENTATION_GHOSTGRAPHICCONTROLLER_HPP
#define PACMAN_PRESENTATION_GHOSTGRAPHICCONTROLLER_HPP


#include <memory>
#include <vector>

#include <cinder/Color.h>
#include <cinder/Vector.h>

#include <Model/Color.hpp>
#include <Model/Direction.hpp>
#include <Presentation/IDirectionCalculator.hpp>
#include <Presentation/IGhostGraphicController.hpp>


namespace Pacman
{
namespace Presentation
{


namespace Detail
{


class GhostSkeletonFactory
{
public:
    static std::vector<ci::Vec2f> create(const float ghostSize);
};


class ColorConverter
{
public:
    static ci::Color toBodyColor(Model::Color color);
    static ci::Color toBorderColor(Model::Color color);
    static ci::Color toEyeColor(Model::Color color);
    static ci::Color toPupilOfEyeColor(Model::Color color);
};


} // namespace Detail


class GhostGraphicController : public IGhostGraphicController
{
public:
    GhostGraphicController(
            unsigned fieldSize_,
            unsigned horizontalOffset_,
            float ghostSizeScale,
            std::shared_ptr<IDirectionCalculator> directionCalculator_);

    void drawNormalGhost(
            int fromRow,
            int fromColumn,
            int toRow,
            int toColumn,
            unsigned step,
            unsigned resolution,
            Model::Color color) override;

    void drawScaredGhost(
            int fromRow,
            int fromColumn,
            int toRow,
            int toColumn,
            unsigned step,
            unsigned resolution,
            Model::Color color) override;

    void drawLastSecondsScaredGhost(
            int fromRow,
            int fromColumn,
            int toRow,
            int toColumn,
            unsigned step,
            unsigned resolution,
            Model::Color color) override;

private:
    enum class EyeState
    {
        Dynamic,
        Static
    };

    void drawGhost(
            int fromRow,
            int fromColumn,
            int toRow,
            int toColumn,
            unsigned step,
            unsigned resolution,
            Model::Color color,
            EyeState eyeState);

    void calculateDirection(
            int fromRow,
            int fromColumn,
            int toRow,
            int toColumn);

    ci::Vec2f calculateGhostsPosition(
            int fromRow,
            int fromColumn,
            int toRow,
            int toColumn,
            unsigned step,
            unsigned resolution) const;

    std::vector<ci::Vec2f> createGhostsBorderPoints(const ci::Vec2f& position) const;

    void alignPupilsOfEyesToDirection(ci::Vec2f& leftPupil, ci::Vec2f& rightPupil, float pupilRadius) const;

    void drawGhostsBody(const std::vector<ci::Vec2f>& points, const ci::Vec2f& center, Model::Color ghostColor);

    void drawGhostsEyes(const ci::Vec2f& center, Model::Color ghostColor, EyeState eyeState);

    void drawGhostsBorder(const std::vector<ci::Vec2f>& points, Model::Color ghostColor);

    const unsigned fieldSize;
    const unsigned horizontalOffset;

    std::shared_ptr<IDirectionCalculator> directionCalculator;

    const float ghostSize;
    const std::vector<ci::Vec2f> ghostSkeleton;

    Model::Direction direction;
};


} // namespace Presentation
} // namespace Pacman


#endif // PACMAN_PRESENTATION_GHOSTGRAPHICCONTROLLER_HPP
