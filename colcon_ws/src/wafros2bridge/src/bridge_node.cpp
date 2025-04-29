#include "bridge_node.hpp"
#include <string>

BridgeNode::BridgeNode(std::string name){
    node = std::make_shared<rclcpp::Node>(name);
}

