import serial
from multiprocessing import Lock
from xbox import xbox
import time 

def show_xbox_pack(xbox_pack):
    for i in range(24):
        print(xbox_pack[i],end='')
        print(' ',end='')
    print(' ')

def read_serial(port,buffer_rx_len, xbox_pack):
    myserial = mySerial(port=port, baudrate=115200, timeout= 0.01, buff_rx_len=buffer_rx_len)
    global xbox
    xbox_pack[0] = 0
    while True:
        try:
            myserial.read()
        except:
            myserial.ser.close()
            while True:  
                try:  
                    # 尝试打开串行端口  
                    myserial = mySerial(port=port, baudrate=115200, timeout= 0.01, buff_rx_len=buffer_rx_len)
                    print(f"成功连接到串行端口 {port}")  
                    break
                except serial.SerialException as e:  
                    print(f"连接到 {port} 失败: {e}")  
                    # 等待一段时间后重试  
                    time.sleep(5) 

        lock.acquire()
        # print(str(xbox_pack[0]))
        str_tx = ''
        if xbox_pack[0] == 85:
            # print(str(xbox_pack[0])[2:])
            for i in range(24):
                a = '0x{:02X}'.format(xbox_pack[i])
                str_tx = str_tx + a[2:]
                
            
            try:
                myserial.write_byte(str_tx)
            except:
                myserial.ser.close()
                while True:  
                    try:  
                        # 尝试打开串行端口  
                        myserial = mySerial(port=port, baudrate=115200, timeout= 0.01, buff_rx_len=buffer_rx_len)
                        print(f"成功连接到串行端口 {port}")  
                        break
                    except serial.SerialException as e:  
                        print(f"连接到 {port} 失败: {e}")  
                        # 等待一段时间后重试  
                        time.sleep(5) 
            print(str_tx)
            xbox_pack[0] = 0

        lock.release()
        # print(xbox_pack[0] )
        # myserial.write(xbox.data_pack)



lock = Lock()
class mySerial:
    def __init__(self, port, baudrate, timeout, buff_rx_len):

        # self.ser = serial.Serial(port=port, baudrate=baudrate, timeout=timeout)
        while True:  
            try:  
                # 尝试打开串行端口  
                self.ser = serial.Serial(port, baudrate, timeout=timeout)  
                print(f"成功连接到串行端口 {port}")  
                break
            except serial.SerialException as e:  
                print(f"连接到 {port} 失败: {e}")  
                # 等待一段时间后重试  
                time.sleep(5) 

        self.buff_rx_len = buff_rx_len
        self.arr_p = 0
        self.arr_rx=[0 for i in range(buff_rx_len)]
        self.end = [str('0d'), str('0a')]

    def write(self, data):
        
        write_len = self.ser.write(data.encode('utf-8'))
        
        return write_len
    
    def write_byte(self, data):
        data = bytes.fromhex(data)
        write_len = self.ser.write(data)
        
        return write_len
    
    def read(self):
        com_input = self.ser.read(1)

        if com_input:   # 如果读取结果非空，则输出
            lock.acquire()
            com_input = com_input.hex()     #转为16进制字符串
            self.data_analysis(com_input)
            lock.release()
    
    def data_analysis(self, data):
        if self.arr_p >= self.buff_rx_len:         
            self.arr_p = 0;                        

        self.arr_rx[self.arr_p] = data;   
        if data ==self.end[1]:               #帧尾
            print('接收到：')
            for num in self.arr_rx:
                if num!= 0: 
                    print(num + ' ', end='')
            print(' ')

        self.arr_p += 1;    # 数组指针自增   
