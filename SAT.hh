#ifndef SAT_HH
#define SAT_HH

#include <SFML/Graphics.hpp>
#include <vector>

class SAT {
    private:
        const static std::vector<sf::Vector2f> get_global_coords(const sf::Shape& s);
        const static std::vector<sf::Vector2f>
            get_edges(const std::vector<sf::Vector2f>& coords);

    public:
    const static bool collides(const sf::Shape& shape1, const sf::Shape& shape2, sf::RenderWindow& w);
};

#endif
