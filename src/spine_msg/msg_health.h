#ifndef _ROS_spine_msg_msg_health_h
#define _ROS_spine_msg_msg_health_h

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

  class msg_health : public ros::Msg
  {
    public:
      typedef uint8_t _state_type;
      _state_type state;
      typedef int8_t _bat_temp_type;
      _bat_temp_type bat_temp;
      typedef uint8_t _bat_percent_type;
      _bat_percent_type bat_percent;

    msg_health():
      state(0),
      bat_temp(0),
      bat_percent(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->state >> (8 * 0)) & 0xFF;
      offset += sizeof(this->state);
      union {
        int8_t real;
        uint8_t base;
      } u_bat_temp;
      u_bat_temp.real = this->bat_temp;
      *(outbuffer + offset + 0) = (u_bat_temp.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->bat_temp);
      *(outbuffer + offset + 0) = (this->bat_percent >> (8 * 0)) & 0xFF;
      offset += sizeof(this->bat_percent);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      this->state =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->state);
      union {
        int8_t real;
        uint8_t base;
      } u_bat_temp;
      u_bat_temp.base = 0;
      u_bat_temp.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->bat_temp = u_bat_temp.real;
      offset += sizeof(this->bat_temp);
      this->bat_percent =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->bat_percent);
     return offset;
    }

    virtual const char * getType() override { return "spine_msg/msg_health"; };
    virtual const char * getMD5() override { return "c4ced81031851a2e82ee647c114b7fbc"; };

  };

}
#endif
