import serial
import threading

#class serialTimer(threading.Timer):
    #def run(self):
        #while not self.finished.wait(self.interval):
            #self.function(*self.args, **self.kwargs)

class rpiVoice:
    def __init__(self):
        self.running = False
        self.port = '/dev/ttyTHS1'
        self.baudrate = 115200
        self.parity = serial.PARITY_NONE
        self.stopbits = serial.STOPBITS_ONE
        self.bytesize = serial.EIGHTBITS
        self.timeout=1
        self.ser = serial.Serial(
            port=self.port,
            baudrate=self.baudrate,
            parity=self.parity,
            stopbits=self.stopbits,
            bytesize=self.bytesize,
            timeout=self.timeout
        )

    def start(self, var):
        if self.running:
            print('Rpi Voice is already running')
            return None
        # create a thread to read the Rpi Voice
        self.running=True
        self.read_thread = threading.Thread(target=self.readSerial, args=[var])
        self.read_thread.start()
        return self

    def readSerial(self,var):
        while self.running:
            try:
                self.reading = self.ser.readline()
                self.readcmd = self.reading.decode('utf-8')
                self.readcmd = self.readcmd.strip('\n')
                if len(self.readcmd) >0:
                    print(self.readcmd)
                    var[0]=self.readcmd
                    self.ser.flushInput()
                    self.ser.flushOutput()
            except RuntimeError:
                print("Fail")
    
    #def start_reading(self):
        #self.serial_timer=serialTimer(1.0,self.update_fps_stats)
        #self.serial_timer.start()

    def sendText(self, text = "Running"):
        self.ser.write((text).encode())
        self.ser.flushInput()
        self.ser.flushOutput()