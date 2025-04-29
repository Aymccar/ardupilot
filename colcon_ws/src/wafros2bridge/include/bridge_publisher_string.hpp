#pragma once 
#include "bridge_node.hpp"
#include "bridge_publisher.hpp"

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <string>

class BridgePublisherString : public BridgePublisher{
public:
    BridgePublisherString(std::string name, int buff, BridgeNode node);
    void publish(std::string msg);

private:
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher;
};
