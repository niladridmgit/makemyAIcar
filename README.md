# makemyAIcar V2

## Below components used:
1. <del>Raspberry Pi 4 (2GB)</del> due to performance issue decided to go with **Jetson nano 4GB - B01**
2. <del>Raspberry Pi 4 Aluminum Heat Sink Case with Double Fans  [LINK](https://www.amazon.in/REES52-Raspberry-Armor-Aluminium-Heatsink/dp/B07X5XXKTZ/ref=sr_1_1?dchild=1&keywords=Raspberry+Pi+4+Aluminum+Heat+Sink+Case&qid=1620661429&sr=8-1)</del> this is not compatible with jetson nano so added **4 Sqcm 5v colling fan**
3. <del>32gb SanDisk Extreme</del> upgraded to **USB SSD 256 gb** 
5. Raspberry Pi Camera V2 and IMX219-77 8MP Camera with 77° FOV
6. Car Chassis Transparent 4Wd  [LINK](https://www.amazon.in/gp/product/B01MT9Z9QB/ref=ppx_yo_dt_b_asin_title_o01_s00?ie=UTF8&psc=1) 
7. <del>8Ybj-48 Dc 5V 4 Phase 5 Wire Stepper Motor With Uln2003 Driver  [LINK](https://www.amazon.in/gp/product/B072T8QT62/ref=ppx_yo_dt_b_asin_title_o09_s00?ie=UTF8&psc=1)</del>
8. hc sr04 ultrasonic sensor
9. Mi Pocket Power Bank Pro 10000mAh 
10. Arduino Uno
11. DC motor arduino l293d shield
12. pca9685 servo driver
13. Expansion shield for Arduino Nano  [LINK](https://www.amazon.in/Robodo-Electronics-AR28-Expansion-Arduino/dp/B0787JNN4S/ref=sr_1_2?dchild=1&keywords=Expansion+shield+for+Arduino+Nano&qid=1620661683&sr=8-2)
14. sg90 servo
15. 3d Printed parts
16. <del>tp-link dual band Wireless adapter [LINK](https://www.amazon.in/TP-Link-Archer-T2U-Wireless-Adapter/dp/B00K11UIV4)</del>

Raspberry pi 4 (2gb) has more power full and newer cpu (Broadcom BCM2711 quad-core 64-bit ARM Cortex-A72 CPU @ 1.5 GHz) compare to Jetson nano (quad-core ARM Cortex-A57 64-bit @ 1.42 GHz) but Jetson nano has power full gpu **NVIDIA Maxwell architecture with 128 NVIDIA CUDA® cores** good enough to process object detection at 30fps
for more details about Jetson Nano 4gb see here [LINK](https://developer.nvidia.com/embedded/jetson-nano-developer-kit)

We need TensorRT-accelerated deep learning networks for image recognition, object detection with localization (i.e. bounding boxes), and semantic segmentation. This inferencing library is intended to be run on the Jetson, and includes support for both C++ and Python. Various pre-trained DNN models are automatically downloaded to get you up and running quickly. 

follow the guideline mention below link to install required packages

**https://github.com/dusty-nv/jetson-inference/blob/master/docs/building-repo-2.md**

Prerequisite:

## **Install OpenCV 4.5.2** 

**https://qengineering.eu/install-opencv-4.5-on-jetson-nano.html**

### Check for updates
$ sudo apt-get update
$ sudo apt-get upgrade
### Install nano
$ sudo apt-get install nano
### Install dphys-swapfile
$ sudo apt-get install dphys-swapfile
### Give the required memory size
$ sudo nano /etc/dphys-swapfile
### Reboot 
$ sudo reboot.

### Reveal the CUDA location
$ sudo sh -c "echo '/usr/local/cuda/lib64' >> /etc/ld.so.conf.d/nvidia-tegra.conf"
$ sudo ldconfig
### Third-party libraries
$ sudo apt-get install build-essential cmake git unzip pkg-config

$ sudo apt-get install libjpeg-dev libpng-dev libtiff-dev

$ sudo apt-get install libavcodec-dev libavformat-dev libswscale-dev

$ sudo apt-get install libgtk2.0-dev libcanberra-gtk*

$ sudo apt-get install python3-dev python3-numpy python3-pip

$ sudo apt-get install libxvidcore-dev libx264-dev libgtk-3-dev

$ sudo apt-get install libtbb2 libtbb-dev libdc1394-22-dev

$ sudo apt-get install libv4l-dev v4l-utils

$ sudo apt-get install libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev

$ sudo apt-get install libavresample-dev libvorbis-dev libxine2-dev

$ sudo apt-get install libfaac-dev libmp3lame-dev libtheora-dev

$ sudo apt-get install libopencore-amrnb-dev libopencore-amrwb-dev

$ sudo apt-get install libopenblas-dev libatlas-base-dev libblas-dev

$ sudo apt-get install liblapack-dev libeigen3-dev gfortran

$ sudo apt-get install libhdf5-dev protobuf-compiler

$ sudo apt-get install libprotobuf-dev libgoogle-glog-dev libgflags-dev


### Download the latest version
$ cd ~

$ wget -O opencv.zip https://github.com/opencv/opencv/archive/4.5.2.zip

$ wget -O opencv_contrib.zip https://github.com/opencv/opencv_contrib/archive/4.5.2.zip

### Unpack
$ unzip opencv.zip

$ unzip opencv_contrib.zip

### Administration to make live easier later on
$ mv opencv-4.5.2 opencv

$ mv opencv_contrib-4.5.2 opencv_contrib

### Clean up the zip files
$ rm opencv.zip

$ rm opencv_contrib.zip


$ cd ~/opencv

$ mkdir build

$ cd build


$ cmake -D CMAKE_BUILD_TYPE=RELEASE \
-D CMAKE_INSTALL_PREFIX=/usr \
-D OPENCV_EXTRA_MODULES_PATH=~/opencv_contrib/modules \
-D EIGEN_INCLUDE_PATH=/usr/include/eigen3 \
-D WITH_OPENCL=OFF \
-D WITH_CUDA=ON \
-D CUDA_ARCH_BIN=5.3 \
-D CUDA_ARCH_PTX="" \
-D WITH_CUDNN=ON \
-D WITH_CUBLAS=ON \
-D ENABLE_FAST_MATH=ON \
-D CUDA_FAST_MATH=ON \
-D OPENCV_DNN_CUDA=ON \
-D ENABLE_NEON=ON \
-D WITH_QT=OFF \
-D WITH_OPENMP=ON \
-D WITH_OPENGL=ON \
-D BUILD_TIFF=ON \
-D WITH_FFMPEG=ON \
-D WITH_GSTREAMER=ON \
-D WITH_TBB=ON \
-D BUILD_TBB=ON \
-D BUILD_TESTS=OFF \
-D WITH_EIGEN=ON \
-D WITH_V4L=ON \
-D WITH_LIBV4L=ON \
-D OPENCV_ENABLE_NONFREE=ON \
-D INSTALL_C_EXAMPLES=OFF \
-D INSTALL_PYTHON_EXAMPLES=OFF \
-D BUILD_opencv_python3=TRUE \
-D OPENCV_GENERATE_PKGCONFIG=ON \
-D BUILD_EXAMPLES=OFF ..

$ make -j4

$ sudo rm -r /usr/include/opencv4/opencv2

$ sudo make install

$ sudo ldconfig

### Cleaning (frees 300 MB)
$ make clean

$ sudo apt-get update

### Remove the dphys-swapfile now
$ sudo /etc/init.d/dphys-swapfile stop

$ sudo apt-get remove --purge dphys-swapfile


### Save an additional 275 MB
$ sudo rm -rf ~/opencv

$ sudo rm -rf ~/opencv_contrib

$ sudo -H pip install -U jetson-stats

$ sudo reboot

### Start the app with the simple command
$ jtop

## **Install GStreamer**

https://gstreamer.freedesktop.org/download/

MinGW 64-bit -> 1.18.4 runtime installer

edit environment variable and add  gstreamer bin path F:\gstreamer\1.0\mingw_x86_64\bin

in command line Terminal Execute->

gst-launch-1.0 -v udpsrc port=1234 caps = "application/x-rtp, media=(string)video, clock-rate=(int)90000, encoding-name=(string)H264, payload=(int)96" ! rtph264depay ! decodebin ! videoconvert ! autovideosink

## **OprnCV with Jetson Utility**

sudo nano .bashrc

add below lines

export LD_PRELOAD = /usr/lib/aarch64-linux-gnu/libgomp.so.1

export DISPLAY=:0.0

## **Serial Port Permission**

sudo usermod -a -G dialout $USER

## **In Progress**

## **Earlier design**
![alt text](https://github.com/niladridmgit/makemyAIcar/blob/main/images/makemyAIcar_1.jpg)

## **New design**
![alt text](https://github.com/niladridmgit/makemyAIcar/blob/main/images/jetson_nano_build_bench_test4.jpg)

### **Assembly**
![alt text](https://github.com/niladridmgit/makemyAIcar/blob/main/images/Assembly.png)

![alt text](https://github.com/niladridmgit/makemyAIcar/blob/main/images/jetson_nano_2gb.jpg)

![alt text](https://github.com/niladridmgit/makemyAIcar/blob/main/images/jetson_nano_build_bench_test4.jpg)

![alt text](https://github.com/niladridmgit/makemyAIcar/blob/main/images/jetson_nano_build_Top_view.jpg)

![alt text](https://github.com/niladridmgit/makemyAIcar/blob/main/images/jetson_nano_build_Bottom_view.jpg)

![alt text](https://github.com/niladridmgit/makemyAIcar/blob/main/images/3d_printed_stepper_mount_1.jpg)

![alt text](https://github.com/niladridmgit/makemyAIcar/blob/main/images/free_wheel.jpg)

![alt text](https://github.com/niladridmgit/makemyAIcar/blob/main/images/3p_printed_RPI_CAM_V2_mount1.png)

![alt text](https://github.com/niladridmgit/makemyAIcar/blob/main/images/3p_printed_RPI_CAM_V2_mount2.png)

![alt text](https://github.com/niladridmgit/makemyAIcar/blob/main/images/3p_printed_RPI_CAM_V2_mount3.png)

![alt text](https://github.com/niladridmgit/makemyAIcar/blob/main/images/3p_printed_RPI_CAM_V2_mount4.png)

![alt text](https://github.com/niladridmgit/makemyAIcar/blob/main/images/jetson_nano_build_bench_test3.jpg)

![alt text](https://github.com/niladridmgit/makemyAIcar/blob/main/images/jetson_nano_build_bench_test1.jpg)

