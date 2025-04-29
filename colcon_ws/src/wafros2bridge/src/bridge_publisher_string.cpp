#include "bridge_publisher_string.hpp"
#include "bridge_node.hpp"
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <string>


BridgePublisherString::BridgePublisherString(std::string name, int buff, BridgeNode node):
    BridgePublisher()
{
    publisher = node.get()->create_publisher<std_msgs::msg::String>(name, buff);
}

void BridgePublisherString::publish(std::string msg)
{
    std_msgs::msg::String ros_msg;
    ros_msg.data = msg;
    publisher->publish(ros_msg);
}

