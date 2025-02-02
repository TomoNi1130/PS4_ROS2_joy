from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import ExecuteProcess

def generate_launch_description():
      ld = LaunchDescription()

      serial_talker = Node(
            package='joy_controller_pkg',
            executable='serial_talker',
            name='serial_talker',
            namespace='controller_signal_load'
      )

      msg_show = ExecuteProcess(
            cmd = ['gnome-terminal','--geometry=10x22', '--', 'bash', '-c','cd ~/Documents/ROS2/test_ws && . install/setup.bash && ros2 topic echo controller_signal_load/controller_data; exec bash'],
            output = 'screen',
      )
      
      ld.add_action(serial_talker)
      ld.add_action(msg_show)

      return ld