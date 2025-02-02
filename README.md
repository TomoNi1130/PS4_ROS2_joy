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

シリアルメッセージ　= {シリアルメッセージ}　+ "pressing" + "|" or + "no_pressing" + "|"
| 押されているボタン | シリアルメッセージ |
|--------------------|--------------------|
| `X`                | `cross`            |
| `O`                | `circle`           |
| `▲`                | `triangle`         |
| `■`                | `square`           |
| `L1`               | `L1`               |
| `R1`               | `R1`               |
| `L2`               | `L2`               |
| `R2`               | `R2`               |
| `SHARE`            | `SHARE`            |
| `OPTION`           | `OPTION`           |
| `PS`               | `PS`               |
| `←`                | `left`             |
| `→`                | `right`            |
| `↑`                | `up`               |
| `↓`                | `down`             |

## 使用方法

```bash
# パッケージのインストール
sudo apt install ros-jazzy-joy*

#ワークスペース内で
colcon build --packages-select ros2-jazzy-joy
. install/setup

#コントローラーを接続（確認　ls /dev/input/js0 ）
ros2 launch {pkg_name} Pilot.launch.py
##or
#シリアルを接続
ros2 launch {pkg_name} Robot.launch.py
```
