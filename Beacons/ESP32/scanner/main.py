from bluepy.btle import Scanner
import math

def calculate_distance(rssi, tx_power=-59):
    if rssi == 0:
        return -1.0
    ratio = rssi * 1.0 / tx_power
    if ratio < 1.0:
        return math.pow(ratio, 10)
    else:
        distance = 0.89976 * math.pow(ratio, 7.7095) + 0.111
        return distance

scanner = Scanner()
devices = scanner.scan(5.0)  # Scan for 5 seconds

for dev in devices:
    for (adtype, desc, value) in dev.getScanData():
        if desc == 'Manufacturer':
            rssi = dev.rssi
            distance = calculate_distance(rssi)
            print(f"Device {dev.addr}, RSSI={rssi} dB, Estimated distance={distance:.2f} m")
