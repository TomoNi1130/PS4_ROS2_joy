from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import ExecuteProcess

def generate_launch_description():
      ld = LaunchDescription()

      controller_listener = Node(
            package='joy_controller_pkg',
            executable='listener',
            name='listener',
            namespace='controller_signal_load'
      )

      jstest = ExecuteProcess(
            cmd = ['gnome-terminal','--geometry=174x5', '--', 'bash', '-c','jstest /dev/input/js0; exec bash'],
            # output = 'screen',
      )

      controller_conection = Node(
            package='joy_linux',
            executable='joy_linux_node',
            name='joy_node',
            namespace='controller_signal_load'
        )
      
      ld.add_action(controller_listener)
      ld.add_action(jstest)
      ld.add_action(controller_conection)

      return ld