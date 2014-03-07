#ifndef PACMAN_MODEL_GAMECONTROLLEREVENTS_HPP
#define PACMAN_MODEL_GAMECONTROLLEREVENTS_HPP


namespace Pacman
{
namespace Model
{


/**
 * Specifies all key types possible in the game.
 */
enum class Key
{
    UpArrow,
    DownArrow,
    LeftArrow,
    RightArrow,
    P,
    Return,
    Escape
};


class KeyPressed
{
public:
    KeyPressed(Key key_);
    Key getKey() const;

private:
    const Key key;
};


class MoveRequested {};


class DrawRequested {};


// equality operators:
bool operator==(const KeyPressed&, const KeyPressed&);
bool operator==(const MoveRequested&, const MoveRequested&);
bool operator==(const DrawRequested&, const DrawRequested&);


} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_GAMECONTROLLEREVENTS_HPP
