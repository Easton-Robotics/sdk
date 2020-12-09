#pragma once
#include "v8stdint.h"
#include <vector>

#define PropertyBuilderByName(type, name, access_permission)\
    access_permission:\
        type m_##name;\
    public:\
    inline void set##name(type v) {\
        m_##name = v;\
    }\
    inline type get##name() {\
        return m_##name;\
}\


#if !defined(_countof)
#define _countof(_Array) (int)(sizeof(_Array) / sizeof(_Array[0]))
#endif

#ifndef M_PI
#define M_PI 3.1415926
#endif

#define DEG2RAD(x) ((x)*M_PI/180.)
#define SUNNOISEINTENSITY 0xff
#define GLASSNOISEINTENSITY 0xfe

#define LIDAR_CMD_STOP                      0x65
#define LIDAR_CMD_SCAN                      0x60
#define LIDAR_CMD_FORCE_SCAN                0x61
#define LIDAR_CMD_RESET                     0x80
#define LIDAR_CMD_FORCE_STOP                0x00
#define LIDAR_CMD_GET_EAI                   0x55
#define LIDAR_CMD_GET_DEVICE_INFO           0x90
#define LIDAR_CMD_GET_DEVICE_HEALTH         0x92
#define LIDAR_ANS_TYPE_DEVINFO              0x4
#define LIDAR_ANS_TYPE_DEVHEALTH            0x6
#define LIDAR_CMD_SYNC_BYTE                 0xA5
#define LIDAR_CMDFLAG_HAS_PAYLOAD           0x80
#define LIDAR_ANS_SYNC_BYTE1                0xA5
#define LIDAR_ANS_SYNC_BYTE2                0x5A
#define LIDAR_ANS_TYPE_MEASUREMENT          0x81
#define LIDAR_RESP_MEASUREMENT_SYNCBIT        (0x1<<0)
#define LIDAR_RESP_MEASUREMENT_QUALITY_SHIFT  2
#define LIDAR_RESP_MEASUREMENT_CHECKBIT       (0x1<<0)
#define LIDAR_RESP_MEASUREMENT_ANGLE_SHIFT    1
#define LIDAR_RESP_MEASUREMENT_DISTANCE_SHIFT  2
#define LIDAR_RESP_MEASUREMENT_ANGLE_SAMPLE_SHIFT 8

#define LIDAR_CMD_RUN_POSITIVE             0x06
#define LIDAR_CMD_RUN_INVERSION            0x07
#define LIDAR_CMD_SET_AIMSPEED_ADDMIC      0x09
#define LIDAR_CMD_SET_AIMSPEED_DISMIC      0x0A
#define LIDAR_CMD_SET_AIMSPEED_ADD         0x0B
#define LIDAR_CMD_SET_AIMSPEED_DIS         0x0C
#define LIDAR_CMD_GET_AIMSPEED             0x0D

#define LIDAR_CMD_SET_SAMPLING_RATE        0xD0
#define LIDAR_CMD_GET_SAMPLING_RATE        0xD1
#define LIDAR_STATUS_OK                    0x0
#define LIDAR_STATUS_WARNING               0x1
#define LIDAR_STATUS_ERROR                 0x2

#define LIDAR_CMD_ENABLE_LOW_POWER         0x01
#define LIDAR_CMD_DISABLE_LOW_POWER        0x02
#define LIDAR_CMD_STATE_MODEL_MOTOR        0x05
#define LIDAR_CMD_ENABLE_CONST_FREQ        0x0E
#define LIDAR_CMD_DISABLE_CONST_FREQ       0x0F

#define LIDAR_CMD_GET_OFFSET_ANGLE          0x93
#define LIDAR_CMD_GET_RIB_OFFSET_ANGLE      0x94
#define LIDAR_CMD_SET_LOW_EXPOSURE          0x95
#define LIDAR_CMD_ADD_EXPOSURE       	    0x96
#define LIDAR_CMD_DIS_EXPOSURE       	    0x97


#define LIDAR_CMD_SET_HEART_BEAT        0xD9
#define LIDAR_CMD_SET_SETPOINTSFORONERINGFLAG  0xae

#define LIDAR_CMD_ENTER_TEXT 0xfa
#define LIDAR_CMD_EXIT 0x40

#define PackageSampleMaxLngth 0x100
typedef enum {
  CT_Normal = 0,
  CT_RingStart  = 1,
  CT_Tail,
} CT;
#define Node_Default_Quality (10)
#define Node_Sync 1
#define Node_NotSync 2
#define PackagePaidBytes 10
#define PH 0x55AA

#if defined(_WIN32)
#pragma pack(1)
#endif

struct node_info {
  uint8_t    sync_flag;  //sync flag
  uint16_t   sync_quality;//!intensity
  uint16_t   angle_q6_checkbit; //!angle
  uint16_t   distance_q; //! distance
  uint64_t   stamp; //! timestamp
  uint8_t    scan_frequence;//! scan frequency
  uint8_t    debugInfo;///< debug information
  uint8_t    index;///< package index
  uint8_t    error_package;///< error package state
} __attribute__((packed)) ;

struct PackageNode {
  uint8_t PakageSampleQuality;
  uint16_t PakageSampleDistance;
} __attribute__((packed));

struct node_package {
  uint16_t  package_Head;
  uint8_t   package_CT;
  uint8_t   nowPackageNum;
  uint16_t  packageFirstSampleAngle;
  uint16_t  packageLastSampleAngle;
  uint16_t  checkSum;
  PackageNode  packageSample[PackageSampleMaxLngth];
} __attribute__((packed)) ;

struct node_packages {
  uint16_t  package_Head;
  uint8_t   package_CT;
  uint8_t   nowPackageNum;
  uint16_t  packageFirstSampleAngle;
  uint16_t  packageLastSampleAngle;
  uint16_t  checkSum;
  uint16_t  packageSampleDistance[PackageSampleMaxLngth];
} __attribute__((packed)) ;


struct device_info {
  uint8_t   model; ///< lidar model
  uint16_t  firmware_version; ///< Firmware Major Version
  uint8_t   hardware_version; ///< Firmware Minjor Version
  uint8_t   serialnum[16];    ///< serial number
} __attribute__((packed)) ;

struct device_health {
  uint8_t   status; ///< health status
  uint16_t  error_code; ///< error code
} __attribute__((packed))  ;

struct sampling_rate {
  uint8_t rate;	///< sampling frequency
} __attribute__((packed))  ;

struct scan_frequency {
  uint32_t frequency;	///< scanning frequency
} __attribute__((packed))  ;

struct scan_rotation {
  uint8_t rotation;
} __attribute__((packed))  ;

struct scan_exposure {
  uint8_t exposure;	///<
} __attribute__((packed))  ;

struct scan_heart_beat {
  uint8_t enable;	///<
} __attribute__((packed));

struct scan_points {
  uint8_t flag;
} __attribute__((packed))  ;

struct function_state {
  uint8_t state;
} __attribute__((packed))  ;

struct offset_angle {
  int32_t angle;
} __attribute__((packed))  ;

struct rib_offset_angle {
  offset_angle angle[16];
} __attribute__((packed))  ;

struct cmd_packet {
  uint8_t syncByte;
  uint8_t cmd_flag;
  uint8_t size;
  uint8_t data;
} __attribute__((packed)) ;

struct lidar_ans_header {
  uint8_t  syncByte1;
  uint8_t  syncByte2;
  uint32_t size: 30;
  uint32_t subType: 2;
  uint8_t  type;
} __attribute__((packed));

#if defined(_WIN32)
#pragma pack()
#endif

struct LaserPoint {
  //angle[°]
  float angle;
  //range[m]
  float distance;
  float intensity;
//  uint64_t stamp;
  uint64_t stamp;
  LaserPoint &operator = (const LaserPoint &data) {
    this->angle = data.angle;
    this->distance = data.distance;
    this->intensity = data.intensity;
    this->stamp = data.stamp;
    return *this;
  }
};

//! A struct for returning configuration from the YDLIDAR
struct LaserConfig {
  //! Start angle for the laser scan [rad].  0 is forward and angles are measured clockwise when viewing YDLIDAR from the top.
  float min_angle;
  //! Stop angle for the laser scan [rad].   0 is forward and angles are measured clockwise when viewing YDLIDAR from the top.
  float max_angle;
  //! Scan resoltuion [s]
  float time_increment;
  //! Time between scans[s]
  float scan_time;
  //! Minimum range [m]
  float min_range;
  //! Maximum range [m]
  float max_range;
  int sequence;
  LaserConfig &operator = (const LaserConfig &data) {
    this->min_angle = data.min_angle;
    this->max_angle = data.max_angle;
    this->time_increment = data.time_increment;
    this->scan_time = data.scan_time;
    this->min_range = data.min_range;
    this->max_range = data.max_range;
    this->sequence = data.sequence;
    return *this;
  }
};

struct LaserScan {
  //! Array of laser data point
  std::vector<LaserPoint> data;
  //! System time when first range was measured in nanoseconds
  uint64_t system_time_stamp;
  //! Configuration of scan
  LaserConfig config;
  LaserScan &operator = (const LaserScan &data) {
    this->data = data.data;
    this->system_time_stamp = data.system_time_stamp;
    this->config = data.config;
    return *this;
  }
};

struct LaserDebug {
  uint8_t     W3F4CusMajor_W4F0CusMinor;
  uint8_t     W4F3Model_W3F0DebugInfTranVer;
  uint8_t     W3F4HardwareVer_W4F0FirewareMajor;
  uint8_t     W7F0FirewareMinor;
  uint8_t     W3F4BoradHardVer_W4F0Moth;
  uint8_t     W2F5Output2K4K5K_W5F0Date;
  uint8_t     W1F6GNoise_W1F5SNoise_W1F4MotorCtl_W4F0SnYear;
  uint8_t     W7F0SnNumH;
  uint8_t     W7F0SnNumL;
  uint8_t     W7F0Health;
  uint8_t     W3F4CusHardVer_W4F0CusSoftVer;
  uint8_t     W7F0LaserCurrent;
  uint8_t     MaxDebugIndex;
  LaserDebug &operator = (const LaserDebug &other) {
    this->W3F4CusMajor_W4F0CusMinor = other.W3F4CusMajor_W4F0CusMinor;
    this->W4F3Model_W3F0DebugInfTranVer = other.W4F3Model_W3F0DebugInfTranVer;
    this->W3F4HardwareVer_W4F0FirewareMajor =
      other.W3F4HardwareVer_W4F0FirewareMajor;
    this->W7F0FirewareMinor = other.W7F0FirewareMinor;
    this->W3F4BoradHardVer_W4F0Moth = other.W3F4BoradHardVer_W4F0Moth;
    this->W2F5Output2K4K5K_W5F0Date = other.W2F5Output2K4K5K_W5F0Date;
    this->W1F6GNoise_W1F5SNoise_W1F4MotorCtl_W4F0SnYear =
      other.W1F6GNoise_W1F5SNoise_W1F4MotorCtl_W4F0SnYear;
    this->W7F0SnNumH = other.W7F0SnNumH;
    this->W7F0SnNumL = other.W7F0SnNumL;
    this->W7F0Health = other.W7F0Health;
    this->W3F4CusHardVer_W4F0CusSoftVer = other.W3F4CusHardVer_W4F0CusSoftVer;
    this->W7F0LaserCurrent = other.W7F0LaserCurrent;
    this->MaxDebugIndex = other.MaxDebugIndex;
    return *this;
  }
};

/** The numeric version information struct.  */
typedef struct {
  uint8_t  hardware;   /**< Hardware version*/
  uint16_t firmware;      /**< Firmware Version */
  uint8_t  sn[16];     /**< serial number*/
} LidarVersion;
