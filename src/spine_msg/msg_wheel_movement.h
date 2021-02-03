#ifndef _ROS_spine_msg_msg_wheel_movement_h
#define _ROS_spine_msg_msg_wheel_movement_h

#include <stdint.h>
#ifdef __MACH__
	#include "String.h"
#else
	#include "string.h"
#endif
#include <stdlib.h>
#include "ros/msg.h"

namespace spine_msg
{

  class msg_wheel_movement : public ros::Msg
  {
    public:
      typedef uint32_t _timestamp_type;
      _timestamp_type timestamp;
      typedef int16_t _distance_type;
      _distance_type distance;

    msg_wheel_movement():
      timestamp(0),
      distance(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->timestamp >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->timestamp >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->timestamp >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->timestamp >> (8 * 3)) & 0xFF;
      offset += sizeof(this->timestamp);
      union {
        int16_t real;
        uint16_t base;
      } u_distance;
      u_distance.real = this->distance;
      *(outbuffer + offset + 0) = (u_distance.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_distance.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->distance);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      this->timestamp =  ((uint32_t) (*(inbuffer + offset)));
      this->timestamp |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->timestamp |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->timestamp |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->timestamp);
      union {
        int16_t real;
        uint16_t base;
      } u_distance;
      u_distance.base = 0;
      u_distance.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_distance.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->distance = u_distance.real;
      offset += sizeof(this->distance);
     return offset;
    }

    virtual const char * getType() override { return "spine_msg/msg_wheel_movement"; };
    virtual const char * getMD5() override { return "eac8ba147736abf30c2e84d08500c9ba"; };

  };

}
#endif
