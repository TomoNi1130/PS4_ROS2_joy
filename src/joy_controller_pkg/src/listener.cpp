#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

#include <sensor_msgs/msg/joy.hpp>
#include <test_interface/msg/controller.hpp>

using std::placeholders::_1;

class Joy_Sub : public rclcpp::Node
{
public:
    Joy_Sub()
        : Node("Joy_Subscriver")
    {
        rclcpp::QoS qos(10);
        qos.reliable();    // 信頼性の高い通信
        qos.keep_last(10); // 最後の10メッセージを保持

        subscription_ =
            this->create_subscription<sensor_msgs::msg::Joy>("joy", 10, std::bind(&Joy_Sub::topic_callback, this, _1));
        publisher_ = this->create_publisher<test_interface::msg::Controller>("controller_data", 10);
    }

private:
    void topic_callback(sensor_msgs::msg::Joy::UniquePtr msg)
    {
        auto message = test_interface::msg::Controller();
        RCLCPP_INFO(this->get_logger(), "送ってるぜ");

        message.lx = msg->axes[0];
        message.ly = msg->axes[1];
        message.rx = msg->axes[3];
        message.ry = msg->axes[4];
        message.buttons[0] = msg->buttons[0];
        message.buttons[1] = msg->buttons[1];
        message.buttons[2] = msg->buttons[2];
        message.buttons[3] = msg->buttons[3];
        message.buttons[4] = msg->buttons[4];
        message.buttons[5] = msg->buttons[5];
        message.buttons[6] = msg->buttons[6];
        message.buttons[7] = msg->buttons[7];
        message.buttons[8] = msg->buttons[8];
        message.buttons[9] = msg->buttons[9];
        message.buttons[10] = msg->buttons[10];
        if (msg->axes[6] == 1)
            message.buttons[11] = true;
        if (msg->axes[6] == -1)
            message.buttons[12] = true;
        if (msg->axes[7] == 1)
            message.buttons[13] = true;
        if (msg->axes[7] == -1)
            message.buttons[14] = true;
        message.buttons[11] = msg->buttons[15];
        message.buttons[12] = msg->buttons[16];
        this->publisher_->publish(message);
    }
    rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr subscription_;
    rclcpp::Publisher<test_interface::msg::Controller>::SharedPtr publisher_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Joy_Sub>());
    rclcpp::shutdown();
    return 0;
}