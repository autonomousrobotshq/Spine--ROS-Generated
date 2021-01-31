#ifndef _ROS_spine_msg_msg_imu_h
#define _ROS_spine_msg_msg_imu_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace spine_msg
{

  class msg_imu : public ros::Msg
  {
    public:
      typedef uint16_t _angle_type;
      _angle_type angle;
      typedef int16_t _accel_x_type;
      _accel_x_type accel_x;
      typedef int16_t _accel_y_type;
      _accel_y_type accel_y;
      typedef int16_t _accel_z_type;
      _accel_z_type accel_z;
      typedef int16_t _mag_x_type;
      _mag_x_type mag_x;
      typedef int16_t _mag_y_type;
      _mag_y_type mag_y;
      typedef int16_t _mag_z_type;
      _mag_z_type mag_z;

    msg_imu():
      angle(0),
      accel_x(0),
      accel_y(0),
      accel_z(0),
      mag_x(0),
      mag_y(0),
      mag_z(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->angle >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->angle >> (8 * 1)) & 0xFF;
      offset += sizeof(this->angle);
      union {
        int16_t real;
        uint16_t base;
      } u_accel_x;
      u_accel_x.real = this->accel_x;
      *(outbuffer + offset + 0) = (u_accel_x.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_accel_x.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->accel_x);
      union {
        int16_t real;
        uint16_t base;
      } u_accel_y;
      u_accel_y.real = this->accel_y;
      *(outbuffer + offset + 0) = (u_accel_y.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_accel_y.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->accel_y);
      union {
        int16_t real;
        uint16_t base;
      } u_accel_z;
      u_accel_z.real = this->accel_z;
      *(outbuffer + offset + 0) = (u_accel_z.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_accel_z.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->accel_z);
      union {
        int16_t real;
        uint16_t base;
      } u_mag_x;
      u_mag_x.real = this->mag_x;
      *(outbuffer + offset + 0) = (u_mag_x.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_mag_x.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->mag_x);
      union {
        int16_t real;
        uint16_t base;
      } u_mag_y;
      u_mag_y.real = this->mag_y;
      *(outbuffer + offset + 0) = (u_mag_y.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_mag_y.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->mag_y);
      union {
        int16_t real;
        uint16_t base;
      } u_mag_z;
      u_mag_z.real = this->mag_z;
      *(outbuffer + offset + 0) = (u_mag_z.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_mag_z.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->mag_z);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      this->angle =  ((uint16_t) (*(inbuffer + offset)));
      this->angle |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->angle);
      union {
        int16_t real;
        uint16_t base;
      } u_accel_x;
      u_accel_x.base = 0;
      u_accel_x.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_accel_x.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->accel_x = u_accel_x.real;
      offset += sizeof(this->accel_x);
      union {
        int16_t real;
        uint16_t base;
      } u_accel_y;
      u_accel_y.base = 0;
      u_accel_y.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_accel_y.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->accel_y = u_accel_y.real;
      offset += sizeof(this->accel_y);
      union {
        int16_t real;
        uint16_t base;
      } u_accel_z;
      u_accel_z.base = 0;
      u_accel_z.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_accel_z.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->accel_z = u_accel_z.real;
      offset += sizeof(this->accel_z);
      union {
        int16_t real;
        uint16_t base;
      } u_mag_x;
      u_mag_x.base = 0;
      u_mag_x.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_mag_x.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->mag_x = u_mag_x.real;
      offset += sizeof(this->mag_x);
      union {
        int16_t real;
        uint16_t base;
      } u_mag_y;
      u_mag_y.base = 0;
      u_mag_y.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_mag_y.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->mag_y = u_mag_y.real;
      offset += sizeof(this->mag_y);
      union {
        int16_t real;
        uint16_t base;
      } u_mag_z;
      u_mag_z.base = 0;
      u_mag_z.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_mag_z.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->mag_z = u_mag_z.real;
      offset += sizeof(this->mag_z);
     return offset;
    }

    virtual const char * getType() override { return "spine_msg/msg_imu"; };
    virtual const char * getMD5() override { return "31732126901c99568f513d838ffbbcbd"; };

  };

}
#endif
