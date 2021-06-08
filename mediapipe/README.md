## Jetson Nano L4T 32.5.1 aarch64
```
$ sudo apt update && \
  sudo apt install -y python3-dev protobuf-compiler python3-pip git make libssl-dev
$ sudo pip3 install pip --upgrade
$ sudo pip3 install \
numpy-1.19.4.whl \
opencv_contrib_python-4.5.2.52.whl \
mediapipe-0.8.5.whl
$ sudo pip3 install opencv-python dataclasses
```
### now your CSI camera using gstreamer_pipeline might not work so just remove opencv_contrib_python-4.5.2.52 by executing below command

**$ sudo pip3 uninstall opencv_contrib_python-4.5.2.52.whl**

## Reference

https://github.com/PINTO0309/mediapipe-bin
```
$ sudo apt update && \
  sudo apt install -y python3-dev protobuf-compiler python3-pip git make libssl-dev
$ sudo pip3 install pip --upgrade
$ git clone https://github.com/PINTO0309/mediapipe-bin && cd mediapipe-bin
$ ./v0.8.5/numpy119x/mediapipe-0.8.5_cuda102-cp36-cp36m-linux_aarch64_numpy119x_jetsonnano_L4T32.5.1_download.sh
$ sudo pip3 install \
numpy-1.19.4-cp36-none-manylinux2014_aarch64.whl \
opencv_contrib_python-4.5.2.52-cp36-none-linux_aarch64.whl \
mediapipe-0.8.5_cuda102-cp36-none-linux_aarch64.whl
$ sudo pip3 install opencv-python dataclasses
```
