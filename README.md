# makemyAIcar

## Below components used:
1. <del>Raspberry Pi 4 (2GB)</del> due to performance issue desided to go with **Jetson nano 2GB**
2. <del>Raspberry Pi 4 Aluminum Heat Sink Case with Double Fans  [LINK](https://www.amazon.in/REES52-Raspberry-Armor-Aluminium-Heatsink/dp/B07X5XXKTZ/ref=sr_1_1?dchild=1&keywords=Raspberry+Pi+4+Aluminum+Heat+Sink+Case&qid=1620661429&sr=8-1)</del> this is not compatible with jetson nano so added **4 qcm 5v colling fan**
3. <del>32gb SanDisk Extreme</del> upgraded to **64gb SanDisk Extreme** 
5. Raspberry Pi CAmera V2
6. Car Chassis Transparent 4Wd  [LINK](https://www.amazon.in/gp/product/B01MT9Z9QB/ref=ppx_yo_dt_b_asin_title_o01_s00?ie=UTF8&psc=1) 
7. 8Ybj-48 Dc 5V 4 Phase 5 Wire Stepper Motor With Uln2003 Driver  [LINK](https://www.amazon.in/gp/product/B072T8QT62/ref=ppx_yo_dt_b_asin_title_o09_s00?ie=UTF8&psc=1)
8. hc sr04 ultrasonic sensor
9. Mi Pocket Power Bank Pro 10000mAh 
10. Arduino nano
11. Expansion shield for Arduino Nano  [LINK](https://www.amazon.in/Robodo-Electronics-AR28-Expansion-Arduino/dp/B0787JNN4S/ref=sr_1_2?dchild=1&keywords=Expansion+shield+for+Arduino+Nano&qid=1620661683&sr=8-2)
12. sg90 servo
13. 3d Printed parts
14. tp-link dual band Wireless adapter [LINK](https://www.amazon.in/TP-Link-Archer-T2U-Wireless-Adapter/dp/B00K11UIV4)

Raspberry pi 4 (2gb) has more power full and newer cpu (Broadcom BCM2711 quad-core 64-bit ARM Cortex-A72 CPU @ 1.5 GHz) compare to Jetson nano (quad-core ARM Cortex-A57 64-bit @ 1.42 GHz) but Jetson nano has power full gpu **NVIDIA Maxwell architecture with 128 NVIDIA CUDA® cores** good enough to process object detection at 30fps
for more details about Jetson Nano 2gb see here [LINK](https://developer.nvidia.com/embedded/jetson-nano-2gb-developer-kit)

We need TensorRT-accelerated deep learning networks for image recognition, object detection with localization (i.e. bounding boxes), and semantic segmentation. This inferencing library is intended to be run on the Jetson, and includes support for both C++ and Python. Various pre-trained DNN models are automatically downloaded to get you up and running quickly. 

follow the guideline mention below link to install required packages

**https://github.com/dusty-nv/jetson-inference/blob/master/docs/building-repo-2.md**

## **In Progress**

## **Earlier design**
![alt text](https://github.com/niladridmgit/makemyAIcar/blob/main/images/makemyAIcar_1.jpg)

## **New design**
![alt text](https://github.com/niladridmgit/makemyAIcar/blob/main/images/jetson_nano_build_bench_test4.jpg)

### **Assembly**
![alt text](https://github.com/niladridmgit/makemyAIcar/blob/main/images/Assembly.jpg)

