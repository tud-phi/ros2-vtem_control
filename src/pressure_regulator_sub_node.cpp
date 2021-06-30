#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "vtem_control/msg/input_pressures.hpp"
using std::placeholders::_1;

class InputPressuresSubscriber : public rclcpp::Node
{
public:
  InputPressuresSubscriber()
  : Node("minimal_subscriber")
  {
    // VTEM input pressures topic
    this->declare_parameter<std::string>("vtem_input_pressures_topic", "vtem_input_pressures");
    this->get_parameter("vtem_input_pressures_topic", vtem_input_pressures_topic_);

    subscription_ = this->create_subscription<vtem_control::msg::InputPressures>(
      vtem_input_pressures_topic_.c_str(), 10, std::bind(&InputPressuresSubscriber::topic_callback, this, _1));
  }

private:
  void topic_callback(const vtem_control::msg::InputPressures::SharedPtr msg) const
  {
    RCLCPP_INFO(this->get_logger(), "I received msg: '%s'");
  }
  rclcpp::Subscription<vtem_control::msg::InputPressures>::SharedPtr subscription_;
  std::string vtem_input_pressures_topic_;
};

int main(int argc, char * argv[])
{
  printf("hello world vtem_control package\n");
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<InputPressuresSubscriber>());
  rclcpp::shutdown();
  return 0;
}