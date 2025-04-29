#pragma once
#include<rclcpp/rclcpp.hpp>
#include <string>


class BridgeNode {
public :
    BridgeNode(std::string name);
    rclcpp::Node::SharedPtr get(){return node;};

private :
    rclcpp::Node::SharedPtr node;
};
