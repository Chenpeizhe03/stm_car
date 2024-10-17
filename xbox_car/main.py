from myserial import mySerial
import time
from multiprocessing import Process, Array
from myserial import read_serial
from xbox import read_xbox


def main():

    xbox_pack = Array('i', [0 for i in range(30)])

    p1=Process(target=read_serial,args=("/dev/ttyACM0", 30, xbox_pack, )) 
    p2=Process(target=read_xbox,args=(0.1, xbox_pack, )) 
    p1.start()
    p2.start()


if __name__ == "__main__":
    main()