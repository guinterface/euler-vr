#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEBeacon.h>
#include <BLEAdvertising.h>

void setup() {
  Serial.begin(115200);
  BLEDevice::init("ESP32_Beacon");

  BLEBeacon oBeacon = BLEBeacon();
  oBeacon.setManufacturerId(0x004C); // Apple's manufacturer ID
  oBeacon.setProximityUUID(BLEUUID("e2c56db5-dffb-48d2-b060-d0f5a71096e0")); // Replace with your UUID
  oBeacon.setMajor(1); // Replace with unique major
  oBeacon.setMinor(1); // Replace with unique minor
  oBeacon.setSignalPower(-59);

  BLEAdvertisementData oAdvertisementData = BLEAdvertisementData();
  BLEAdvertisementData oScanResponseData = BLEAdvertisementData();

  oAdvertisementData.setFlags(0x04); // BR_EDR_NOT_SUPPORTED
  std::string strServiceData = "";
  strServiceData += (char)0x02;      // Length
  strServiceData += (char)0x15;      // iBeacon indicator
  strServiceData += oBeacon.getData();
  oAdvertisementData.addData(strServiceData);

  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->setAdvertisementData(oAdvertisementData);
  pAdvertising->setScanResponseData(oScanResponseData);
  pAdvertising->setAdvertisementType(ADV_TYPE_NONCONN_IND);
  pAdvertising->start();
}

void loop() {
  delay(1000);
}
