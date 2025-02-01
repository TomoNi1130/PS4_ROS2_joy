PS4controller用に作った ros2-jazzy-joy を使ったパッケージ

Pilot側とRobot側に分かれており、それぞれに対応したlunchファイルがある。

Pilot側
/dev/input/js0　のコントローラーからの信号を受け取り、Robot側に送る。

Robot側
送られたメッセージに応じて　/dev/ttyACM0　にシリアルを送る。

シリアル対応表 : 押されている場合 {key} + :pressing + |
pressed_button -> {key}
             X -> cross
             O -> circle
             ▲ -> triangle
             ■ -> square
            L1 -> L1
            R1 -> R1
            L2 -> L2
            R2 -> R2
         SHARE -> SHARE
        OPTION -> OPTION
            PS -> PS
            ←　-> left
            →　-> right
            ↑　-> up
            ↓　-> down
# ros2-jazzy-joy

このパッケージは、PS4コントローラーを使用して、RobotとPilot間で通信を行うROS2パッケージです。Pilot側とRobot側に分かれており、各側に対応したLaunchファイルを提供します。

## 概要

- **Pilot側**:
  - `/dev/input/js0`からのPS4コントローラー信号を受け取ります。
  - 受け取った信号をRobot側に送信します。

- **Robot側**:
  - Pilot側から送られたメッセージを受け取り、対応するシリアル信号を`/dev/ttyACM0`に送信します。

## シリアル対応表

受け取ったボタン入力に応じて、以下のようにシリアルデータが送信されます。

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

### 1. インストール

ROS2環境を整えた後、次のコマンドを使用してパッケージをインストールします：

```bash
# パッケージのインストール
colcon build --packages-select ros2-jazzy-joy
