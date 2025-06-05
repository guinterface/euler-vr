def rssi_to_distance(rssi, tx_power=-59, n=2.0):
    return 10 ** ((tx_power - rssi) / (10 * n))
