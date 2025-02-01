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
