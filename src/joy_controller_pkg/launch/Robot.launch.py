from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
      ld = LaunchDescription()

      serial_talker = Node(
            package='joy_controller_pkg',
            executable='serial_talker',
            name='serial_talker',
            namespace='controller_signal_load'
      )
      
      ld.add_action(serial_talker)

      return ld