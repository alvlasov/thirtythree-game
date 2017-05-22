#ifndef QUADTREE_H_INCLUDED
#define QUADTREE_H_INCLUDED

#include <vector>
#include <memory>
#include <limits>
#include <stack>

#include <SFML/Graphics.hpp>

#include "Logger.h"
#include "GameObjects/GameObject.h"

namespace thirtythree {

class Drawer;
class QuadTree {
public:

    typedef std::shared_ptr<GameObject> ObjectPtr;

    QuadTree(sf::FloatRect boundary, Drawer *drawer);
    ~QuadTree();

    bool Insert(ObjectPtr &object);
    void Subdivide();
    void Prune();
    sf::FloatRect GetBoundary() { return boundary_; }
    int GetObjectsCount() { return objects_in_node_.size(); }
    bool IsLeaf() { return is_leaf_; }

    //std::vector<ObjectPtr> FindCollisionCandidates()

    ObjectPtr FindNearestNeighbor(ObjectPtr &object,
                                  float distance = std::numeric_limits<float>::max(),
                                  bool visualise = false);
    std::vector<ObjectPtr>& AccessObjects() { return objects_in_node_; }

    int GetLeavesNumber();

    std::vector<QuadTree*> GetChildren() {
        return {north_west_, north_east_, south_west_, south_east_};
    }


private:
    static const int node_capacity_ = 3;

    sf::FloatRect boundary_;

    QuadTree *north_west_;
    QuadTree *north_east_;
    QuadTree *south_west_;
    QuadTree *south_east_;

    std::vector<ObjectPtr> objects_in_node_;

    bool is_leaf_;

    Drawer *drawer_;

};

} // namespace thirtythree

#endif // QUADTREE_H_INCLUDED
