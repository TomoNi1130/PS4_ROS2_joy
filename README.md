# PS4_ROS2_joy

このパッケージは、PS4コントローラー用にros2-jazzy-joyを使用して、コントローラーの信号をシリアルにするROS2パッケージ。Pilot側とRobot側に分かれており、各側に対応したLaunchファイルがある。

## 概要

- **Pilot側**:
  - `/dev/input/js0`からのPS4コントローラー信号を受け取り、メッセージをRobot側に送信する。

- **Robot側**:
  - Pilot側から送られたメッセージを受け取り、対応するシリアル信号を`/dev/ttyACM0`に送信する。

## シリアル対応表
**stick**:
シリアルメッセージ = "n;" + {L-x} + ":" + {L-y} + ":" + {R-x} + ":" + {R-y} + "|"

-1 =< {LR-xy}　=< 1

**button**:

シリアルメッセージ　= {シリアルメッセージ}　+ ":p" + "|" or + ":no_p" + "|"
| 押されているボタン | シリアルメッセージ |
|--------------------|--------------------|
| `X`                | `cr`               |
| `O`                | `ci`               |
| `▲`                | `tri`              |
| `■`                | `sq`               |
| `L1`               | `L1`               |
| `R1`               | `R1`               |
| `L2`               | `L2`               |
| `R2`               | `R2`               |
| `SHARE`            | `SH`               |
| `OPTION`           | `OP`               |
| `PS`               | `PS`               |
| `←`                | `l`                |
| `→`                | `r`                |
| `↑`                | `u`                |
| `↓`                | `d`                |

## 使用方法

```bash
# パッケージのインストール
sudo apt install joystick
sudo apt install jstest-gtk
sudo apt install ros-jazzy-joy*

#ワークスペース内で
colcon build
. install/setup

#コントローラーを接続（確認　ls /dev/input/js0 ）
ros2 launch joy_controller_pkg Pilot.launch.py
##or
#シリアルを接続
ros2 launch joy_controller_pkg Robot.launch.py
```
