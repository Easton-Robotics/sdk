
#include "CYdLidar.h"
#include <iostream>
#include <string>
#include <signal.h>
#include <memory>
#include <regex>
using namespace std;
using namespace ydlidar;
CYdLidar laser;

#if defined(_MSC_VER)
#pragma comment(lib, "ydlidar_driver.lib")
#endif

int main(int argc, char *argv[]) {
  printf(" YDLIDAR C++ TEST\n");
  std::string port;
  int baudrate;
  std::string intensity;
  ydlidar::init(argc, argv);

  std::map<std::string, std::string> ports =
    ydlidar::YDlidarDriver::lidarPortList();
  std::map<std::string, std::string>::iterator it;

  if (ports.size() == 1) {
    it = ports.begin();
    port = it->second;
  } else {
    int id = 0;

    for (it = ports.begin(); it != ports.end(); it++) {
      printf("%d. %s\n", id, it->first.c_str());
      id++;
    }

    if (ports.empty()) {
      printf("Not Lidar was detected. Please enter the lidar serial port:");
      std::cin >> port;
    } else {
      while (ydlidar::ok()) {
        printf("Please select the lidar port:");
        std::string number;
        std::cin >> number;

        if ((size_t)atoi(number.c_str()) >= ports.size()) {
          continue;
        }

        it = ports.begin();
        id = atoi(number.c_str());

        while (id) {
          id--;
          it++;
        }

        port = it->second;
        break;
      }
    }
  }

  std::vector<unsigned int> baudrateList;
  baudrateList.push_back(115200);
  baudrateList.push_back(153600);

  for (unsigned int i = 0; i < baudrateList.size(); i ++) {
    printf("%u. %u\n", i, baudrateList[i]);
  }

  while (ydlidar::ok()) {
    printf("Please enter the lidar serial baud rate:");
    std::string index;
    std::cin >> index;

    if (atoi(index.c_str()) >= baudrateList.size()) {
      printf("Invalid serial number, Please re-select\n");
      continue;
    }

    baudrate = baudrateList[atoi(index.c_str())];
    break;

  }


  int intensities  = 0;
  printf("0. false\n");
  printf("1. true\n");

  while (ydlidar::ok()) {
    printf("Please enter the lidar intensity:");
    std::cin >> intensity;

    if (atoi(intensity.c_str()) >= 2) {
      printf("Invalid serial number, Please re-select\n");
      continue;
    }

    intensities = atoi(intensity.c_str());
    break;
  }

  if (!ydlidar::ok()) {
    return 0;
  }

  laser.setSerialPort(port);
  laser.setSerialBaudrate(baudrate);
  laser.setIntensities(intensities);//intensity
  laser.setAutoReconnect(true);//hot plug
  laser.setEnableDebug(false);
  laser.setSingleChannel(true);//单通道雷达
  //unit: °C
  laser.setMaxAngle(180);
  laser.setMinAngle(-180);

  //unit: m
  laser.setMinRange(0.1);
  laser.setMaxRange(12.0);
  bool ret = laser.initialize();

  while (ret && ydlidar::ok()) {
    bool hardError;
    node_info nodes[2048];
    size_t count = _countof(nodes);

    if (laser.doProcessSimple(nodes, count, hardError)) {
      uint64_t start_time = nodes[0].stamp;
      uint64_t end_time = nodes[count - 1].stamp;

      if (laser.ascendScanData(nodes, count)) {
        fprintf(stdout, "Scan received: %lu ranges in %f(%f) HZ\n", count,
                1e9 / double(end_time - start_time), nodes[0].scan_frequence / 10.0);
        fflush(stdout);
      } else {
        fprintf(stderr, "ascend Scan data failed\n");
        fflush(stderr);
      }

    } else {
      fprintf(stderr, "get Scan Data failed\n");
      fflush(stderr);
    }
  }


  laser.turnOff();
  laser.disconnecting();

  return 0;


}
