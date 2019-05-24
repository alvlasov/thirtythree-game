#include "QuadTree.h"
#include "Drawer.h"
namespace thirtythree {

QuadTree::QuadTree(Box boundary, Drawer *drawer)
    : boundary_ (boundary),
      north_west_ (nullptr),
      north_east_ (nullptr),
      south_west_ (nullptr),
      south_east_ (nullptr),
      is_leaf_ (true),
      drawer_ (drawer) {
    objects_in_node_.reserve(node_capacity_);
}

QuadTree::~QuadTree() {
    if (north_west_ != nullptr) delete north_west_;
    if (north_east_ != nullptr) delete north_east_;
    if (south_west_ != nullptr) delete south_west_;
    if (south_east_ != nullptr) delete south_east_;
}


bool QuadTree::Insert(GameObject *object) {

    Box object_boundary = object->GetBoundary();
    if (!boundary_.Intersection(object_boundary)) return false;

    if (is_leaf_) {
        if (objects_in_node_.size() < node_capacity_) {
            objects_in_node_.push_back(object);
            return true;
        } else {
            Subdivide();
        }
    }

    bool added_somewhere = north_west_->Insert(object) ||
                           north_east_->Insert(object) ||
                           south_west_->Insert(object) ||
                           south_east_->Insert(object);
    if (added_somewhere) return true;

    return false;
}

void QuadTree::Subdivide() {
    float half_width = (boundary_.max.x - boundary_.min.x) / 2;
    float half_height = (boundary_.max.y - boundary_.min.y) / 2;
    Box north_west({boundary_.min.x + half_width, boundary_.min.y},
                   {boundary_.max.x, boundary_.max.y - half_height});
    north_west_ = new QuadTree(north_west, drawer_);
    Box north_east({boundary_.min.x, boundary_.min.y},
                   {boundary_.max.x - half_width, boundary_.max.y - half_height});
    north_east_ = new QuadTree(north_east, drawer_);
    Box south_west({boundary_.min.x + half_width, boundary_.min.y + half_height},
                   {boundary_.max.x, boundary_.max.y});
    south_west_ = new QuadTree(south_west, drawer_);
    Box south_east({boundary_.min.x, boundary_.min.y + half_height},
                   {boundary_.max.x - half_width, boundary_.max.y});
    south_east_ = new QuadTree(south_east, drawer_);
    for (GameObject *obj : objects_in_node_) {
        north_west_->Insert(obj);
        north_east_->Insert(obj);
        south_west_->Insert(obj);
        south_east_->Insert(obj);
    }
    objects_in_node_.clear();
    is_leaf_ = false;
}

void QuadTree::Prune() {
    if (north_west_ != nullptr) delete north_west_;
    if (north_east_ != nullptr) delete north_east_;
    if (south_west_ != nullptr) delete south_west_;
    if (south_east_ != nullptr) delete south_east_;
    objects_in_node_.clear();
    is_leaf_ = true;
}

GameObject* QuadTree::FindNearestNeighbor(GameObject *object, float max_distance, bool visualise) {
    float distance = max_distance;
    auto pos = object->GetPos();
    float object_radius = object->GetRadius();
    GameObject *nearest = nullptr;
    std::stack<QuadTree*> trees;
    trees.push(this);
    sf::Color tree_color(0, 0, 0, 10);
    Box search_area({pos.x - distance / 2, pos.y - distance / 2},
                    {pos.x + distance / 2, pos.y - distance / 2});
    while (!trees.empty()) {
        search_area.min = {pos.x - distance / 2, pos.y - distance / 2};
        search_area.max = {pos.x + distance / 2, pos.y + distance / 2};
        auto tree = trees.top();
        if (!tree->IsLeaf()) {
            auto children = tree->GetChildren();
            trees.pop();
            for (auto& child : children) {
                Box boundary = child->GetBoundary();
                if (search_area.Intersection(boundary)) {
                    trees.push(child);
                }
            }
        } else {
            Box boundary = tree->GetBoundary();
            if (search_area.Intersection(boundary)) {
                if (object->GetType() == PLAYER && visualise == true) {
                    tree_color = tree_color + sf::Color(0, 0, 0, 30);
                    drawer_->VisualizeQuadTree(*tree, tree_color);
                }
                std::vector<GameObject*>& leaf_objs = tree->AccessObjects();
                for (auto& leaf_obj : leaf_objs) {
                    if (!leaf_obj->IsDead()) {
                        auto leaf_obj_pos = leaf_obj->GetPos();
                        float leaf_obj_radius = leaf_obj->GetRadius();
                        float new_distance = length(pos - leaf_obj_pos) - (leaf_obj_radius + object_radius);
                        if (new_distance < distance && leaf_obj != object) {
                            nearest = leaf_obj;
                            distance = new_distance;
                        }
                    }
                }
            }
            trees.pop();
        }
    }
    if (object->GetType() == PLAYER && visualise == true) {
        if (nearest != nullptr) {
            Drawer::Text neighbor_info("NN", 40, nearest->GetPos(), true, true);
            drawer_->DrawText(neighbor_info);
        }
        Drawer::Text bound1_text("BOUND1", 40, {pos.x - max_distance / 2, pos.y - max_distance / 2}, true, true);
        drawer_->DrawText(bound1_text);
        Drawer::Text bound2_text("BOUND2", 40, {pos.x + max_distance / 2, pos.y + max_distance / 2}, true, true);
        drawer_->DrawText(bound2_text);
    }
    return nearest;
}

int QuadTree::GetLeavesNumber() {
    int count = 0;
    std::stack<QuadTree*> trees;
    trees.push(this);
    while (!trees.empty()) {
        auto tree = trees.top();
        if (!tree->IsLeaf()) {
            auto children = tree->GetChildren();
            trees.pop();
            for (auto& child : children) {
                trees.push(child);
            }
        } else {
            count++;
            trees.pop();
        }
    }
    return count;
}

}
