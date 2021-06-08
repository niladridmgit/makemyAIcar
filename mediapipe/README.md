## Jetson Nano L4T 32.5.1 aarch64
```
$ sudo apt update && \
  sudo apt install -y python3-dev protobuf-compiler python3-pip git make libssl-dev
$ sudo pip3 install pip --upgrade
$ sudo pip3 install \
numpy-1.19.4-cp36-none-manylinux2014_aarch64.whl \
mediapipe-0.8.5_cuda102-cp36-cp36m-linux_aarch64.whl
$ sudo pip3 install opencv-python dataclasses
```


