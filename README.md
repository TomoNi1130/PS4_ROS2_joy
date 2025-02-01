# ros2-jazzy-joy

このパッケージは、PS4コントローラーを使用して、RobotとPilot間で通信を行うROS2パッケージです。Pilot側とRobot側に分かれており、各側に対応したLaunchファイルがある。

## 概要

- **Pilot側**:
  - `/dev/input/js0`からのPS4コントローラー信号を受け取り、メッセージをRobot側に送信する。

- **Robot側**:
  - Pilot側から送られたメッセージを受け取り、対応するシリアル信号を`/dev/ttyACM0`に送信する。

## シリアル対応表

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
colcon build --packages-select ros2-jazzy-joy
