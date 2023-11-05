#include "SAT.hh"
#include <math.h>
#include <iostream>
#include <limits>

typedef std::vector<sf::Vector2f> vv2f;
typedef std::pair<sf::Vector2f, sf::Vector2f> pv2f;

const float PI = 3.14159265359f;

float deg_to_rad(float f) {
    return f * PI/180.0f;
}

const std::vector<sf::Vector2f> SAT::get_edges(const std::vector<sf::Vector2f>& coords) {
    std::vector<sf::Vector2f> edges(coords.size());
    //std::cout << "edges" << std::endl;

    for  (long unsigned int i = 0; i < edges.size() - 1; ++i) {
        edges[i].x = coords[i+1].x - coords[i].x;
        edges[i].y = coords[i+1].y - coords[i].y;
        //std::cout << edges[i].x << ' ' << edges[i].y << std::endl;

    }

    edges[edges.size()-1] = coords[0] - coords[coords.size() - 1];
    
    return edges;
}

const std::vector<sf::Vector2f> SAT::get_global_coords(const sf::Shape& s) {
    float alpha = deg_to_rad(s.getRotation());

    std::vector<sf::Vector2f> global_coords(s.getPointCount());

    sf::Vector2f center = s.getOrigin();

    
    //std::cout << "coords" << std::endl;

    for (long unsigned int i = 0; i < global_coords.size(); ++i) {
        sf::Vector2f vtex = s.getPoint(i);
        
        float px = vtex.x - center.x;
        float py = vtex.y - center.y;

        global_coords[i].x = center.x + px*cos(alpha) - py*sin(alpha);
        global_coords[i].y = center.y + px*sin(alpha) + py*cos(alpha);

        global_coords[i] += s.getPosition();
    }

    return global_coords;
}




const bool SAT::collides(const sf::Shape& shape1,const sf::Shape& shape2, sf::RenderWindow& w) {
    std::vector<sf::Vector2f> coords_shape1 = get_global_coords(shape1);
    std::vector<sf::Vector2f> coords_shape2 = get_global_coords(shape2);
    
    
    std::vector<sf::Vector2f> edges_shape1 = get_edges(coords_shape1);
    std::vector<sf::Vector2f> edges_shape2 = get_edges(coords_shape2);

    std::vector<sf::Vector2f> union_set(edges_shape1.size() + edges_shape2.size());

    for (long unsigned int i = 0; i < edges_shape1.size(); ++i) {
        union_set[i] = sf::Vector2f(-edges_shape1[i].y, edges_shape1[i].x);
    }
    for (long unsigned int i = 0; i < edges_shape2.size(); ++i) {
        union_set[i + edges_shape1.size()] = sf::Vector2f(-edges_shape2[i].y, edges_shape2[i].x);
    }
     
    for (long unsigned int i = 0; i < union_set.size(); ++i) {
        float min1 = std::numeric_limits<float>::max();
        float max1 = std::numeric_limits<float>::min();
        for (long unsigned int j = 0; j < coords_shape1.size(); ++j) {
            float projected_coord = coords_shape1[j].x*union_set[i].x + coords_shape1[j].y*union_set[i].y; 
            min1 = std::min(min1, projected_coord);
            max1 = std::max(max1, projected_coord);
        }

        float min2 = std::numeric_limits<float>::max();
        float max2 = std::numeric_limits<float>::min();
        for (long unsigned int j = 0; j < coords_shape2.size(); ++j) {
            float projected_coord = coords_shape2[j].x*union_set[i].x + coords_shape2[j].y*union_set[i].y; 
            min2 = std::min(min2, projected_coord);
            max2 = std::max(max2, projected_coord);
        }

        if (max1 < min2 or max2 < min1) return false;
    }
    return true;

}
