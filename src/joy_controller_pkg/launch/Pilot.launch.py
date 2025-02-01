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

      rqt = ExecuteProcess(
            cmd=['rqt'],  # 実行するコマンド
            output='screen',  # コマンドの出力をターミナルに表示
        )
      
      jstest = ExecuteProcess(
            cmd = ['jstest','/dev/input/js0'],
            output = 'screen',
      )

      controller_conection = ExecuteProcess(
            cmd=['ros2','run','joy_linux', 'joy_linux_node'],  # 実行するコマンド
            output='screen',  # コマンドの出力をターミナルに表示
        )
      
      ld.add_action(controller_listener)
      ld.add_action(rqt)
      ld.add_action(jstest)
      ld.add_action(controller_conection)

      return ld