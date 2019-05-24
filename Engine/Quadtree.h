#ifndef QUADTREE_H_INCLUDED
#define QUADTREE_H_INCLUDED

#include <vector>
#include <memory>
#include <limits>
#include <stack>

#include <SFML/Graphics.hpp>

#include "Logger.h"
#include "GameObjects/GameObject.h"
#include "Utility.h"

namespace thirtythree {

class Drawer;
class QuadTree {
public:

    QuadTree(Box boundary, Drawer *drawer);
    ~QuadTree();

    bool Insert(GameObject *object);
    void Subdivide();
    void Prune();
    Box GetBoundary() { return boundary_; }
    int GetObjectsCount() { return objects_in_node_.size(); }
    bool IsLeaf() { return is_leaf_; }

    GameObject* FindNearestNeighbor(GameObject* object,
                                    float distance = std::numeric_limits<float>::max(),
                                    bool visualise = false);
    std::vector<GameObject*>& AccessObjects() { return objects_in_node_; }

    int GetLeavesNumber();

    std::vector<QuadTree*> GetChildren() {
        return {north_west_, north_east_, south_west_, south_east_};
    }


private:
    static const int node_capacity_ = 3;

    Box boundary_;

    QuadTree *north_west_;
    QuadTree *north_east_;
    QuadTree *south_west_;
    QuadTree *south_east_;

    std::vector<GameObject*> objects_in_node_;

    bool is_leaf_;

    Drawer *drawer_;

};

} // namespace thirtythree

#endif // QUADTREE_H_INCLUDED
