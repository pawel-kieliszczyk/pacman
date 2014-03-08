#ifndef PACMAN_CONFIGURATION_HPP
#define PACMAN_CONFIGURATION_HPP


namespace Pacman
{

struct Configuration
{
    // TODO: calculate game size based on user's screen resolution
    const unsigned FIELD_SIZE = 24u;
    const unsigned HORIZONTAL_MARGIN = 100u;
    const unsigned MOVE_RESOLUTION = 14u;
    const unsigned BIG_COIN_MODE_DURATION = MOVE_RESOLUTION * 10u;
    const unsigned BIG_COIN_LAST_SECONDS_MODE_DURATION = MOVE_RESOLUTION * 4u;

    const unsigned long MIN_SHOWN_FRUIT_DURATION = MOVE_RESOLUTION * 30u;
    const unsigned long MAX_SHOWN_FRUIT_DURATION = MIN_SHOWN_FRUIT_DURATION;
    const unsigned long MIN_HIDDEN_FRUIT_DURATION = MOVE_RESOLUTION * 30u;
    const unsigned long MAX_HIDDEN_FRUIT_DURATION = MOVE_RESOLUTION * 60u;

    const unsigned COIN_SCORE = 10u;
    const unsigned BIG_COIN_SCORE = 50u;
    const unsigned GHOST_SCORE = 100u;

    const unsigned NUMBER_OF_PACS_LIFES = 3u;

    const float PAC_SIZE_SCALE = 1.2f;
    const float GHOST_SIZE_SCALE = PAC_SIZE_SCALE;

    const double DISTANCE_TO_COLLISION = 0.5;

    const float PACS_LIFE_SIZE = PAC_SIZE_SCALE * FIELD_SIZE;
    const float FRUIT_SIZE = FIELD_SIZE;
};

} // namespace Pacman


#endif // PACMAN_CONFIGURATION_HPP
