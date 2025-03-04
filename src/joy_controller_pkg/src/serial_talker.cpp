#include "rclcpp/rclcpp.hpp"
#include "test_interface/msg/controller.hpp"

#include <boost/asio.hpp>
#include <filesystem>
#include <array>
#include <memory>
#include <chrono>
#include <string>

using namespace boost::asio;

using std::placeholders::_1;

class serial_talker : public rclcpp::Node
{
public:
    serial_talker() : Node("serial_talker"), io(), serial(io)
    {

        subscription_ = this->create_subscription<test_interface::msg::Controller>( // CHANGE
            "controller_data", 10, std::bind(&serial_talker::topic_callback, this, _1));
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(100), std::bind(&serial_talker::send_data_periodically, this));

        port_name = find_serial_port();
        if (!port_name.empty())
        {
            serial = boost::asio::serial_port(io, port_name);
            serial.set_option(serial_port_base::baud_rate(115200)); // ボーレート設定
        }
        else
        {
            RCLCPP_ERROR(this->get_logger(), "%sポートが接続されてないやんけ!%s", red.c_str(), reset.c_str());
            rclcpp::shutdown();
            return;
        }
    }

private:
    boost::asio::io_context io;
    boost::asio::serial_port serial;

    std::string joy_msg;
    std::string key_message[17];
    std::string full_msg;

    std::string port_name;

    std::string red = "\033[31m";  // 赤色
    std::string reset = "\033[0m"; // リセット

    void send_data_periodically()
    {
        boost::system::error_code ec;
        boost::asio::write(serial, buffer(joy_msg), ec);
        for (int i = 0; i < 17; i++)
        {
            boost::asio::write(serial, buffer(key_message[i]), ec);
        }
        if (ec)
        {
            RCLCPP_ERROR(this->get_logger(), "Error writing to serial port: %s", ec.message().c_str());
        }
        else
        {
            RCLCPP_INFO(this->get_logger(), "send:%s", joy_msg.c_str());
            for(int i = 0;i < 17;i++)
                RCLCPP_INFO(this->get_logger(), "send:%s", key_message[i].c_str());
        }
    }
    void topic_callback(const test_interface::msg::Controller::UniquePtr msg)
    {

        joy_msg = "n:" + std::to_string(msg->lx) + ":" + std::to_string(msg->ly) + ":" + std::to_string(msg->rx) + ":" + std::to_string(msg->ry) + "|";

        for (int i = 0; i < 17; i++)
        {
            if (msg->buttons[i])
            {
                key_message[i] = keys[i] + ":p" + "|";
            }
            else if (!msg->buttons[i])
            {
                key_message[i] = keys[i] + ":no_p" + "|";
            }
        }
    }

    std::string find_serial_port()
    {
        for (const auto &p : std::filesystem::directory_iterator("/dev"))
        {
            if (p.path().string().find("ttyACM") != std::string::npos)
            {
                return p.path().string();
            }
        }
        return "";
    }

    std::array<std::string, 17> keys = {"cr", "ci", "tri", "sq", "L1", "R1", "L2", "R2", "SH", "OP", "PS", "l", "r", "u", "d", "L3", "R3"};

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
    keys[15] = "L3";
    keys[16] = "R3";
    */
    rclcpp::Subscription<test_interface::msg::Controller>::SharedPtr subscription_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<serial_talker>());
    rclcpp::shutdown();
    return 0;
}
/*
#include "rclcpp/rclcpp.hpp"
#include "test_interface/msg/controller.hpp"

#include <boost/asio.hpp>
#include <filesystem>
#include <array>
#include <memory>
#include <chrono>
#include <string>

using namespace boost::asio;

using std::placeholders::_1;

class serial_talker : public rclcpp::Node
{
public:
    serial_talker() : Node("serial_talker"), io(), serial(io)
    {

        subscription_ = this->create_subscription<test_interface::msg::Controller>( // CHANGE
            "controller_data", 10, std::bind(&serial_talker::topic_callback, this, _1));
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(100),std::bind(&serial_talker::send_data_periodically, this));
    }

private:
    boost::asio::io_context io;
    boost::asio::serial_port serial;

    std::string joy_msg;

    std::string key_message[15];
    std::string full_msg;

    std::string port_name;

    std::string red = "\033[31m";  // 赤色
    std::string reset = "\033[0m"; // リセット

    void send_data_periodically()
    {
        boost::system::error_code ec;
        boost::asio::write(serial, buffer(joy_msg), ec);
        for(int i = 0;i < 15; i++)
        {
            boost::asio::write(serial, buffer(key_message[i]), ec);
        }
        if (ec)
        {
            RCLCPP_ERROR(this->get_logger(), "Error writing to serial port: %s", ec.message().c_str());
        }
        else
        {
            RCLCPP_INFO(this->get_logger(), "send:%s", joy_msg.c_str());
            RCLCPP_INFO(this->get_logger(), "send:%s", key_message[1].c_str());
        }
    }

    // void send_data_periodically()
    // {
    //     boost::system::error_code ec;

    //     // joy_msg と key_message を連結して一度に送信する
    //     full_msg = joy_msg;
    //     for (int i = 0; i < 15; i++) {
    //         full_msg += key_message[i];
    //     }

    //     boost::asio::write(serial, buffer(full_msg), ec);  // まとめて送信
    //     if (ec) {
    //         RCLCPP_ERROR(this->get_logger(), "Error writing to serial port: %s", ec.message().c_str());
    //     } else {
    //         RCLCPP_INFO(this->get_logger(), "Sent data: %s", full_msg.c_str());
    //     }
    // }

     void topic_callback(const test_interface::msg::Controller::UniquePtr msg)
    {

        joy_msg = "n:" + std::to_string(msg->lx) + ":" + std::to_string(msg->ly) + ":" + std::to_string(msg->rx) + ":" + std::to_string(msg->ry) + "|";

        for (int i = 0; i < 15; i++)
        {
            if (msg->buttons[i])
            {
                key_message[i] = keys[i] + ":p" + "|";
            }
            else if (!msg->buttons[i])
            {
                key_message[i] = keys[i] + ":no_p" + "|";
            }
        }

    }

    std::string find_serial_port()
    {
        for (const auto& p : std::filesystem::directory_iterator("/dev"))
        {
            if (p.path().string().find("ttyACM") != std::string::npos)
            {
                return p.path().string();
            }
        }
        return "";
    }

    std::array<std::string, 15> keys = {"cr", "ci", "tri", "sq", "L1", "R1", "L2", "R2", "SH", "OP", "PS", "l", "r", "u", "d"};

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
/*
rclcpp::Subscription<test_interface::msg::Controller>::SharedPtr subscription_;
rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[])
{
rclcpp::init(argc, argv);
rclcpp::spin(std::make_shared<serial_talker>());
rclcpp::shutdown();
return 0;
}
*/