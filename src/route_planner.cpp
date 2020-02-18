#include "route_planner.h"
#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model) {
    // Convert inputs to percentage:
    start_x *= 0.01;
    start_y *= 0.01;
    end_x *= 0.01;
    end_y *= 0.01;
    start_node = &m_Model.FindClosestNode(start_x, start_y);
    end_node = &m_Model.FindClosestNode(end_x, end_y);

    // TODO 2: Use the m_Model.FindClosestNode method to find the closest nodes to the starting and ending coordinates.
    // Store the nodes you find in the RoutePlanner's start_node and end_node attributes.

}


// TODO 3: Implement the CalculateHValue method.
// Tips:
// - You can use the distance to the end_node for the h value.
// - Node objects have a distance method to determine the distance to another node.

float RoutePlanner::CalculateHValue(RouteModel::Node const *node) {
    float h_value = node->distance(*end_node);
}


// TODO 4: Complete the AddNeighbors method to expand the current node by adding all unvisited neighbors to the open list.
// Tips:
// - Use the FindNeighbors() method of the current_node to populate current_node.neighbors vector with all the neighbors.
// - For each node in current_node.neighbors, set the parent, the h_value, the g_value. 
// - Use CalculateHValue below to implement the h-Value calculation.
// - For each node in current_node.neighbors, add the neighbor to open_list and set the node's visited attribute to true.

void RoutePlanner::AddNeighbors(RouteModel::Node *current_node) {
    current_node->FindNeighbors();
    std::vector<RouteModel::Node *> neighbors = current_node->neighbors;

    for( auto &current_neighbor: neighbors) {
        current_neighbor->parent = current_node;
        current_neighbor->h_value = this->CalculateHValue(current_neighbor);
        current_neighbor->g_value = current_neighbor->distance(*start_node);
        current_neighbor->sum_g_h = current_neighbor->h_value + current_neighbor->g_value;
        this->open_list.push_back(current_neighbor);
        current_neighbor->visited = true;

    }
}

bool Compare (RouteModel::Node* node1, RouteModel::Node* node2) {
    float f1 = node1->g_value + node1->h_value;
    float f2 = node2->g_value + node2->h_value;
    return f1 > f2;
}

// TODO 5: Complete the NextNode method to sort the open list and return the next node.
// Tips:
// - Sort the open_list according to the sum of the h value and g value.
// - Create a pointer to the node in the list with the lowest sum.
// - Remove that node from the open_list.
// - Return the pointer.

RouteModel::Node *RoutePlanner::NextNode() {
    // RouteModel::Node* start = open_list[0];
    // RouteModel::Node* end = open_list[open_list.size()];
    // std::sort(open_list.begin(), open_list.end(), [](const auto &_1st, const auto &_2nd) {
    //     return _1st->sum_g_h < _2nd->sum_g_h;
    // });;
    std::sort((this->open_list).begin(), (this->open_list).end(), Compare);
    // for( auto &current_open_node: this->open_list) {
    //     std::cout << "current_open_node: " << current_open_node->h_value + current_open_node->g_value << "\n";
    // }
    // RouteModel::Node* first_node_in_sorted_list = open_list[0];
    // open_list.erase(open_list.begin());
    // for( auto &current_open_node: this->open_list) {
    //     std::cout << "current_open_node: " << current_open_node->h_value + current_open_node->g_value << "\n";
    // }
    RouteModel::Node * lowest_sum = (this->open_list).back();
    (this->open_list).pop_back();

    return lowest_sum;
}

    


// TODO 6: Complete the ConstructFinalPath method to return the final path found from your A* search.
// Tips:
// - This method should take the current (final) node as an argument and iteratively follow the 
//   chain of parents of nodes until the starting node is found.
// - For each node in the chain, add the distance from the node to its parent to the distance variable.
// - The returned vector should be in the correct order: the start node should be the first element
//   of the vector, the end node should be the last element.

std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node) {
    // Create path_found vector
    distance = 0.0f;
    std::vector<RouteModel::Node> path_found;
    path_found.push_back(*current_node);
    while (current_node != this->start_node) {

        distance = distance + current_node->distance(*(current_node->parent));
        path_found.push_back(*(current_node->parent));
        current_node = current_node->parent;
    }
    // RouteModel::Node parent_node = *(current_node->parent); 
    //  while (current_node != nullptr) {
    //     if (current_node->parent != nullptr) {
    //         distance += current_node->distance(*(current_node->parent));
    //     }
    //      path_found.push_back(*current_node);

    //     current_node = current_node->parent;
    //  }
    std::reverse(path_found.begin(), path_found.end());
    distance *= m_Model.MetricScale(); // Multiply the distance by the scale of the map to get meters.
    return path_found;

}


// TODO 7: Write the A* Search algorithm here.
// Tips:
// - Use the AddNeighbors method to add all of the neighbors of the current node to the open_list.
// - Use the NextNode() method to sort the open_list and return the next node.
// - When the search has reached the end_node, use the ConstructFinalPath method to return the final path that was found.
// - Store the final path in the m_Model.path attribute before the method exits. This path will then be displayed on the map tile.

void RoutePlanner::AStarSearch() {
    RouteModel::Node *current_node = nullptr;

    // TODO: Implement your solution here.
    start_node->visited = true;
    open_list.emplace_back(start_node);
    while (!open_list.empty()) {
        current_node = NextNode();
        std::cout << "--- next_node " << current_node->sum_g_h << "\n";
        if (current_node->distance(*end_node) == 0) {
            RoutePlanner::m_Model.path = this->ConstructFinalPath(current_node);
            // std::cout << "final path: " << final_path.size() << "\n";
            return;
        }
    AddNeighbors(current_node);
    }


}