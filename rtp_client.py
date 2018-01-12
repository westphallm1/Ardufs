"""
Radio Tranfer Protocol.py
Client for the Arduino radio tranfer protocol.
"""
import serial
import time
import os

class SerialEcho(object):
    EMPTY_BUFFSTR = "No bytes on buffer"
    def __init__(self,tty,null_zero=True):
        self.ser = serial.Serial(tty,timeout=3)
        self.null_zero = null_zero
        self.polling = False

    def send_chars(self,chars,use_end=True):
        self.ser.write(chars.encode('ascii'))
        if(use_end and self.null_zero):
            self.ser.write('\0'.encode('ascii'))

    def recieve_chars(self):
        if(self.ser.in_waiting):
            return self.ser.read(self.ser.in_waiting)
        return b''

    def close(self):
        self.ser.close()

def get_file_from(ser,fname):
    """Transfer a local file using the format:
    <Header Message> OK <File Content> OK <Footer Message> OK
    """
    out_str = bytearray()
    for content in "header","file","footer":
        while not(b"OK" in out_str):
            chars = ser.recieve_chars()
            if chars:
                out_str += chars
        header_split = out_str.index(b"OK")
        if content=="file":
            with open(fname,"wb") as f:
                f.write(out_str[:header_split])
        else:
            print(out_str[:header_split].decode('ascii'),end='')
        out_str = out_str[header_split+2:]

def main(device):
    ser = SerialEcho(device)
    first = False
    mode = 'print'
    while(True):
        if(first):
            cmd = "login"
            first = False
        else:
            try:
                cmd = input("")
            except EOFError:
                cmd = "EOF"

        cmd_words = cmd.split()
        if cmd=="exit":
            return
        if cmd_words[0]=="send":
            mode = "send"
            dest = os.path.split(cmd_words[1])[1]
            
        elif cmd_words[0]=="get":
            mode = "get"
        else:
            mode = "print"

        ser.send_chars(cmd)
        out_str = ''
        time.sleep(.1)
        if mode=='send':
            get_file_from(ser,dest)
        else:
            while not("OK" in out_str):
                chars = ser.recieve_chars().decode('ascii')
                if chars:
                    out_str += chars
            print(out_str[:-2],end='')


    ser.close()        
if __name__ == '__main__':
    import sys
    main(sys.argv[1])
