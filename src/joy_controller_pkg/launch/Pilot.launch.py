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

      ExecuteProcess(
            cmd=['ros2','run','joy_linux', 'joy_linux_node'],  # 実行するコマンド
            output='screen',  # コマンドの出力をターミナルに表示
        )
      
      ld.add_action(controller_listener)

      return ld