##Jan israel charrez gomez
import serial
import serial.tools.list_ports
import psutil
import time
import pandas as pd
import datetime

ports = serial.tools.list_ports.comports()
port = None
if len(ports) > 1:
    print("\n".join([f"{x}: {ports[x]}" for x in range(len(ports))]))
    port = ports[int(input("Select a port: "))]
elif len(ports) == 1:
    port = ports[0]
else:
    print("No serial ports found")
    exit()

m5stick = serial.Serial(port.name,115200)
last_read_time = time.time()
event_log = []

while m5stick.is_open:
    try:
        cpu = psutil.cpu_percent()
        memory = psutil.virtual_memory()
        battery = psutil.sensors_battery()
        info_device = [cpu, memory.percent, battery.percent]
        if m5stick.in_waiting > 0:
            event_code = m5stick.read(1)
            if event_code[0] == 0x01 or event_code == 0x02:
                event_log = []
                continue
            if event_code[0] == 0xFF:
                break
            else:
                event_log.append((datetime.datetime.now().timestamp(), event_code[0], info_device[0], info_device[1], info_device[2]))
    except Exception as e:
        print(e)
        break

m5stick.close()
event_log = pd.DataFrame(event_log,columns=["timestamp","value", "cpu_usage", "memory_usage", "battery"])
event_log.to_csv(f'event_log_{datetime.datetime.now().timestamp()}.csv',index=False)
