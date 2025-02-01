
#include "rclcpp/rclcpp.hpp"
#include "test_interface/msg/controller.hpp"

#include <boost/asio.hpp>
#include <array>

using namespace boost::asio;

using std::placeholders::_1;

class serial_talker : public rclcpp::Node
{
public:
    serial_talker() : Node("serial_talker"), io(), serial(io, "/dev/ttyACM0")
    {
        serial.set_option(serial_port_base::baud_rate(115200));                     // ボーレート設定
        subscription_ = this->create_subscription<test_interface::msg::Controller>( // CHANGE
            "controller_data", 10, std::bind(&serial_talker::topic_callback, this, _1));
    }

private:
    io_service io;
    serial_port serial;
    void topic_callback(const test_interface::msg::Controller::UniquePtr msg)
    {
        boost::system::error_code ec;

        std::string message = std::to_string(msg->lx) + ":" + std::to_string(msg->ly) + ":" + std::to_string(msg->rx) + ":" + std::to_string(msg->ry) + "|";
        boost::asio::write(serial, buffer(message), ec);
        RCLCPP_INFO(this->get_logger(), "send:%s", message.c_str());

        for (size_t i = 0; i < msg->buttons.size(); i++)
        {
            if (msg->buttons[i])
            {
                std::string message = keys[i] + "pressing" + "|";
                boost::asio::write(serial, buffer(message), ec);
            }
        }
        if (ec)
        {
            RCLCPP_ERROR(this->get_logger(), "Error writing to serial port: %s", ec.message().c_str());
        }
    }

    std::array<std::string, 15> keys = {"cross", "circle", "triangle", "square", "L1", "R1", "L2", "R2", "SHARE", "OPTIONS", "PS", "left", "right", "up", "down"};
    /*
    keys[0] = "cross";
    keys[1] = "circle";
    keys[2] = "triangle";
    keys[3] = "square";
    keys[4] = "L1";
    keys[5] = "R1";
    keys[6] = "L2";
    keys[7] = "R2";
    keys[8] = "SHARE";
    keys[9] = "OPTIONS";
    keys[10] = "PS";
    keys[11] = "left";
    keys[12] = "right";
    keys[13] = "up";
    keys[14] = "down";
    */
    rclcpp::Subscription<test_interface::msg::Controller>::SharedPtr subscription_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<serial_talker>());
    rclcpp::shutdown();
    return 0;
}