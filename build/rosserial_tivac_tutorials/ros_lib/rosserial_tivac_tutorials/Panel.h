#ifndef _ROS_rosserial_tivac_tutorials_Panel_h
#define _ROS_rosserial_tivac_tutorials_Panel_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/String.h"
#include "std_msgs/Bool.h"

namespace rosserial_tivac_tutorials
{

  class Panel : public ros::Msg
  {
    public:
      typedef std_msgs::String _panel_location_type;
      _panel_location_type panel_location;
      typedef std_msgs::Bool _btn1_type;
      _btn1_type btn1;
      typedef std_msgs::Bool _btn2_type;
      _btn2_type btn2;
      typedef std_msgs::Bool _btn3_type;
      _btn3_type btn3;
      typedef std_msgs::Bool _btn4_type;
      _btn4_type btn4;
      enum { PANEL_SUPPLY_STATUS_UNKNOWN =  0 };
      enum { PANEL_SUPPLY_STATUS_GOOD =  1 };
      enum { PANEL_SUPPLY_STATUS_OVERHEAT =  2 };
      enum { PANEL_SUPPLY_STATUS_OVERVOLTAGE =  3 };
      enum { PANEL_SUPPLY_STATUS_REVERSEVOLTAGE =  4 };

    Panel():
      panel_location(),
      btn1(),
      btn2(),
      btn3(),
      btn4()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->panel_location.serialize(outbuffer + offset);
      offset += this->btn1.serialize(outbuffer + offset);
      offset += this->btn2.serialize(outbuffer + offset);
      offset += this->btn3.serialize(outbuffer + offset);
      offset += this->btn4.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->panel_location.deserialize(inbuffer + offset);
      offset += this->btn1.deserialize(inbuffer + offset);
      offset += this->btn2.deserialize(inbuffer + offset);
      offset += this->btn3.deserialize(inbuffer + offset);
      offset += this->btn4.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "rosserial_tivac_tutorials/Panel"; };
    const char * getMD5(){ return "e0220b097b0a0dfac944b58072469424"; };

  };

}
#endif