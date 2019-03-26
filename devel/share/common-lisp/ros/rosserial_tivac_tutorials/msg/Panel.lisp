; Auto-generated. Do not edit!


(cl:in-package rosserial_tivac_tutorials-msg)


;//! \htmlinclude Panel.msg.html

(cl:defclass <Panel> (roslisp-msg-protocol:ros-message)
  ((panel_location
    :reader panel_location
    :initarg :panel_location
    :type std_msgs-msg:String
    :initform (cl:make-instance 'std_msgs-msg:String))
   (btn1
    :reader btn1
    :initarg :btn1
    :type std_msgs-msg:Bool
    :initform (cl:make-instance 'std_msgs-msg:Bool))
   (btn2
    :reader btn2
    :initarg :btn2
    :type std_msgs-msg:Bool
    :initform (cl:make-instance 'std_msgs-msg:Bool))
   (btn3
    :reader btn3
    :initarg :btn3
    :type std_msgs-msg:Bool
    :initform (cl:make-instance 'std_msgs-msg:Bool))
   (btn4
    :reader btn4
    :initarg :btn4
    :type std_msgs-msg:Bool
    :initform (cl:make-instance 'std_msgs-msg:Bool)))
)

(cl:defclass Panel (<Panel>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Panel>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Panel)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name rosserial_tivac_tutorials-msg:<Panel> is deprecated: use rosserial_tivac_tutorials-msg:Panel instead.")))

(cl:ensure-generic-function 'panel_location-val :lambda-list '(m))
(cl:defmethod panel_location-val ((m <Panel>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader rosserial_tivac_tutorials-msg:panel_location-val is deprecated.  Use rosserial_tivac_tutorials-msg:panel_location instead.")
  (panel_location m))

(cl:ensure-generic-function 'btn1-val :lambda-list '(m))
(cl:defmethod btn1-val ((m <Panel>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader rosserial_tivac_tutorials-msg:btn1-val is deprecated.  Use rosserial_tivac_tutorials-msg:btn1 instead.")
  (btn1 m))

(cl:ensure-generic-function 'btn2-val :lambda-list '(m))
(cl:defmethod btn2-val ((m <Panel>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader rosserial_tivac_tutorials-msg:btn2-val is deprecated.  Use rosserial_tivac_tutorials-msg:btn2 instead.")
  (btn2 m))

(cl:ensure-generic-function 'btn3-val :lambda-list '(m))
(cl:defmethod btn3-val ((m <Panel>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader rosserial_tivac_tutorials-msg:btn3-val is deprecated.  Use rosserial_tivac_tutorials-msg:btn3 instead.")
  (btn3 m))

(cl:ensure-generic-function 'btn4-val :lambda-list '(m))
(cl:defmethod btn4-val ((m <Panel>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader rosserial_tivac_tutorials-msg:btn4-val is deprecated.  Use rosserial_tivac_tutorials-msg:btn4 instead.")
  (btn4 m))
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql '<Panel>)))
    "Constants for message type '<Panel>"
  '((:PANEL_SUPPLY_STATUS_UNKNOWN . 0)
    (:PANEL_SUPPLY_STATUS_GOOD . 1)
    (:PANEL_SUPPLY_STATUS_OVERHEAT . 2)
    (:PANEL_SUPPLY_STATUS_OVERVOLTAGE . 3)
    (:PANEL_SUPPLY_STATUS_REVERSEVOLTAGE . 4))
)
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql 'Panel)))
    "Constants for message type 'Panel"
  '((:PANEL_SUPPLY_STATUS_UNKNOWN . 0)
    (:PANEL_SUPPLY_STATUS_GOOD . 1)
    (:PANEL_SUPPLY_STATUS_OVERHEAT . 2)
    (:PANEL_SUPPLY_STATUS_OVERVOLTAGE . 3)
    (:PANEL_SUPPLY_STATUS_REVERSEVOLTAGE . 4))
)
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Panel>) ostream)
  "Serializes a message object of type '<Panel>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'panel_location) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'btn1) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'btn2) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'btn3) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'btn4) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Panel>) istream)
  "Deserializes a message object of type '<Panel>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'panel_location) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'btn1) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'btn2) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'btn3) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'btn4) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Panel>)))
  "Returns string type for a message object of type '<Panel>"
  "rosserial_tivac_tutorials/Panel")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Panel)))
  "Returns string type for a message object of type 'Panel"
  "rosserial_tivac_tutorials/Panel")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Panel>)))
  "Returns md5sum for a message object of type '<Panel>"
  "e0220b097b0a0dfac944b58072469424")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Panel)))
  "Returns md5sum for a message object of type 'Panel"
  "e0220b097b0a0dfac944b58072469424")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Panel>)))
  "Returns full string definition for message of type '<Panel>"
  (cl:format cl:nil "#Panel Identification~%std_msgs/String panel_location~%~%# Power supply status constants~%uint8 PANEL_SUPPLY_STATUS_UNKNOWN = 0~%uint8 PANEL_SUPPLY_STATUS_GOOD = 1~%uint8 PANEL_SUPPLY_STATUS_OVERHEAT = 2~%uint8 PANEL_SUPPLY_STATUS_OVERVOLTAGE = 3~%uint8 PANEL_SUPPLY_STATUS_REVERSEVOLTAGE = 4~%~%#Button Status~%std_msgs/Bool btn1~%std_msgs/Bool btn2~%std_msgs/Bool btn3~%std_msgs/Bool btn4~%~%~%================================================================================~%MSG: std_msgs/String~%string data~%~%================================================================================~%MSG: std_msgs/Bool~%bool data~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Panel)))
  "Returns full string definition for message of type 'Panel"
  (cl:format cl:nil "#Panel Identification~%std_msgs/String panel_location~%~%# Power supply status constants~%uint8 PANEL_SUPPLY_STATUS_UNKNOWN = 0~%uint8 PANEL_SUPPLY_STATUS_GOOD = 1~%uint8 PANEL_SUPPLY_STATUS_OVERHEAT = 2~%uint8 PANEL_SUPPLY_STATUS_OVERVOLTAGE = 3~%uint8 PANEL_SUPPLY_STATUS_REVERSEVOLTAGE = 4~%~%#Button Status~%std_msgs/Bool btn1~%std_msgs/Bool btn2~%std_msgs/Bool btn3~%std_msgs/Bool btn4~%~%~%================================================================================~%MSG: std_msgs/String~%string data~%~%================================================================================~%MSG: std_msgs/Bool~%bool data~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Panel>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'panel_location))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'btn1))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'btn2))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'btn3))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'btn4))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Panel>))
  "Converts a ROS message object to a list"
  (cl:list 'Panel
    (cl:cons ':panel_location (panel_location msg))
    (cl:cons ':btn1 (btn1 msg))
    (cl:cons ':btn2 (btn2 msg))
    (cl:cons ':btn3 (btn3 msg))
    (cl:cons ':btn4 (btn4 msg))
))
