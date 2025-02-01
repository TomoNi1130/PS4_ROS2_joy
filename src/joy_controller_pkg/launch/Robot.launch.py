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
      
      rqt = ExecuteProcess(
            cmd=['rqt'],  # 実行するコマンド
            output='screen',  # コマンドの出力をターミナルに表示
        )
      
      topic_tester = ExecuteProcess(
            cmd=['gnome-terminal', '--','ros2','topic','echo', 'controller_data'],  # 実行するコマンド
            output='screen',  # コマンドの出力をターミナルに表示
        )
      
      ld.add_action(serial_talker)
      ld.add_action(rqt)
      ld.add_action(topic_tester)

      return ld