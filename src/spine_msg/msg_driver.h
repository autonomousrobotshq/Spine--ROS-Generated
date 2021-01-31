#ifndef _ROS_spine_msg_msg_driver_h
#define _ROS_spine_msg_msg_driver_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace spine_msg
{

  class msg_driver : public ros::Msg
  {
    public:
      typedef uint8_t _status_type;
      _status_type status;

    msg_driver():
      status(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->status >> (8 * 0)) & 0xFF;
      offset += sizeof(this->status);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      this->status =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->status);
     return offset;
    }

    virtual const char * getType() override { return "spine_msg/msg_driver"; };
    virtual const char * getMD5() override { return "284aa12dd9e9e760802ac9f38036ea5e"; };

  };

}
#endif
