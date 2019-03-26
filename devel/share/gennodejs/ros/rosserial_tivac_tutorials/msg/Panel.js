// Auto-generated. Do not edit!

// (in-package rosserial_tivac_tutorials.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class Panel {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.panel_location = null;
      this.btn1 = null;
      this.btn2 = null;
      this.btn3 = null;
      this.btn4 = null;
    }
    else {
      if (initObj.hasOwnProperty('panel_location')) {
        this.panel_location = initObj.panel_location
      }
      else {
        this.panel_location = new std_msgs.msg.String();
      }
      if (initObj.hasOwnProperty('btn1')) {
        this.btn1 = initObj.btn1
      }
      else {
        this.btn1 = new std_msgs.msg.Bool();
      }
      if (initObj.hasOwnProperty('btn2')) {
        this.btn2 = initObj.btn2
      }
      else {
        this.btn2 = new std_msgs.msg.Bool();
      }
      if (initObj.hasOwnProperty('btn3')) {
        this.btn3 = initObj.btn3
      }
      else {
        this.btn3 = new std_msgs.msg.Bool();
      }
      if (initObj.hasOwnProperty('btn4')) {
        this.btn4 = initObj.btn4
      }
      else {
        this.btn4 = new std_msgs.msg.Bool();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Panel
    // Serialize message field [panel_location]
    bufferOffset = std_msgs.msg.String.serialize(obj.panel_location, buffer, bufferOffset);
    // Serialize message field [btn1]
    bufferOffset = std_msgs.msg.Bool.serialize(obj.btn1, buffer, bufferOffset);
    // Serialize message field [btn2]
    bufferOffset = std_msgs.msg.Bool.serialize(obj.btn2, buffer, bufferOffset);
    // Serialize message field [btn3]
    bufferOffset = std_msgs.msg.Bool.serialize(obj.btn3, buffer, bufferOffset);
    // Serialize message field [btn4]
    bufferOffset = std_msgs.msg.Bool.serialize(obj.btn4, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Panel
    let len;
    let data = new Panel(null);
    // Deserialize message field [panel_location]
    data.panel_location = std_msgs.msg.String.deserialize(buffer, bufferOffset);
    // Deserialize message field [btn1]
    data.btn1 = std_msgs.msg.Bool.deserialize(buffer, bufferOffset);
    // Deserialize message field [btn2]
    data.btn2 = std_msgs.msg.Bool.deserialize(buffer, bufferOffset);
    // Deserialize message field [btn3]
    data.btn3 = std_msgs.msg.Bool.deserialize(buffer, bufferOffset);
    // Deserialize message field [btn4]
    data.btn4 = std_msgs.msg.Bool.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.String.getMessageSize(object.panel_location);
    return length + 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'rosserial_tivac_tutorials/Panel';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'e0220b097b0a0dfac944b58072469424';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    #Panel Identification
    std_msgs/String panel_location
    
    # Power supply status constants
    uint8 PANEL_SUPPLY_STATUS_UNKNOWN = 0
    uint8 PANEL_SUPPLY_STATUS_GOOD = 1
    uint8 PANEL_SUPPLY_STATUS_OVERHEAT = 2
    uint8 PANEL_SUPPLY_STATUS_OVERVOLTAGE = 3
    uint8 PANEL_SUPPLY_STATUS_REVERSEVOLTAGE = 4
    
    #Button Status
    std_msgs/Bool btn1
    std_msgs/Bool btn2
    std_msgs/Bool btn3
    std_msgs/Bool btn4
    
    
    ================================================================================
    MSG: std_msgs/String
    string data
    
    ================================================================================
    MSG: std_msgs/Bool
    bool data
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Panel(null);
    if (msg.panel_location !== undefined) {
      resolved.panel_location = std_msgs.msg.String.Resolve(msg.panel_location)
    }
    else {
      resolved.panel_location = new std_msgs.msg.String()
    }

    if (msg.btn1 !== undefined) {
      resolved.btn1 = std_msgs.msg.Bool.Resolve(msg.btn1)
    }
    else {
      resolved.btn1 = new std_msgs.msg.Bool()
    }

    if (msg.btn2 !== undefined) {
      resolved.btn2 = std_msgs.msg.Bool.Resolve(msg.btn2)
    }
    else {
      resolved.btn2 = new std_msgs.msg.Bool()
    }

    if (msg.btn3 !== undefined) {
      resolved.btn3 = std_msgs.msg.Bool.Resolve(msg.btn3)
    }
    else {
      resolved.btn3 = new std_msgs.msg.Bool()
    }

    if (msg.btn4 !== undefined) {
      resolved.btn4 = std_msgs.msg.Bool.Resolve(msg.btn4)
    }
    else {
      resolved.btn4 = new std_msgs.msg.Bool()
    }

    return resolved;
    }
};

// Constants for message
Panel.Constants = {
  PANEL_SUPPLY_STATUS_UNKNOWN: 0,
  PANEL_SUPPLY_STATUS_GOOD: 1,
  PANEL_SUPPLY_STATUS_OVERHEAT: 2,
  PANEL_SUPPLY_STATUS_OVERVOLTAGE: 3,
  PANEL_SUPPLY_STATUS_REVERSEVOLTAGE: 4,
}

module.exports = Panel;
