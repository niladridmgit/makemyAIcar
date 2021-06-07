## Jetson Nano L4T 32.5.1 aarch64
$ sudo apt update && \
  sudo apt install -y python3-dev protobuf-compiler python3-pip git make libssl-dev
$ sudo pip3 install pip --upgrade
$ sudo pip3 install \
numpy-1.19.4.whl \
opencv_contrib_python-4.5.2.52.whl \
mediapipe-0.8.5.whl
$ sudo pip3 install opencv-python dataclasses

## Reference

https://github.com/PINTO0309/mediapipe-bin
