import time
import SH1106 #OLED
from PIL import Image
from PIL import ImageDraw
from PIL import ImageFont
from utils import get_ip_address
import subprocess


oled = SH1106.SH1106()
image = Image.new('1', (oled.width, oled.height), "BLACK")
draw = ImageDraw.Draw(image)
x = 0
font10 = ImageFont.truetype('/home/jetbot/jetbot/jetbot/apps/Font.ttc', 10)

while True:
    # Shell scripts for system monitoring from here : https://unix.stackexchange.com/questions/119126/command-to-display-memory-usage-disk-usage-and-cpu-load
    cmd = "top -bn1 | grep load | awk '{printf \"CPU Load: %.2f\", $(NF-2)}'"
    CPU = subprocess.check_output(cmd, shell = True )
    cmd = "free -m | awk 'NR==2{printf \"Mem: %s/%sMB %.2f%%\", $3,$2,$3*100/$2 }'"
    MemUsage = subprocess.check_output(cmd, shell = True )
    cmd = "df -h | awk '$NF==\"/\"{printf \"Disk: %d/%dGB %s\", $3,$2,$5}'"
    Disk = subprocess.check_output(cmd, shell = True )
    #print("eth0: " + str(get_ip_address('wlan0')))
    
    draw.rectangle((0, 0, 128, 64), fill = 0)
    draw.text((0, 0), "wlan0: " + str(get_ip_address('wlan0')), font = font10, fill = 1)
    draw.text((0, 15), str(MemUsage.decode('utf-8')), font = font10, fill = 1)
    draw.text((0, 30), str(Disk.decode('utf-8')), font = font10, fill = 1)
    draw.text((0, 45), "niladri.dm.rsb@gmail.com", font = font10, fill = 1)
    oled.display(image)
    time.sleep(3)
