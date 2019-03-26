;; Auto-generated. Do not edit!


(when (boundp 'rosserial_tivac_tutorials::Panel)
  (if (not (find-package "ROSSERIAL_TIVAC_TUTORIALS"))
    (make-package "ROSSERIAL_TIVAC_TUTORIALS"))
  (shadow 'Panel (find-package "ROSSERIAL_TIVAC_TUTORIALS")))
(unless (find-package "ROSSERIAL_TIVAC_TUTORIALS::PANEL")
  (make-package "ROSSERIAL_TIVAC_TUTORIALS::PANEL"))

(in-package "ROS")
;;//! \htmlinclude Panel.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(intern "*PANEL_SUPPLY_STATUS_UNKNOWN*" (find-package "ROSSERIAL_TIVAC_TUTORIALS::PANEL"))
(shadow '*PANEL_SUPPLY_STATUS_UNKNOWN* (find-package "ROSSERIAL_TIVAC_TUTORIALS::PANEL"))
(defconstant rosserial_tivac_tutorials::Panel::*PANEL_SUPPLY_STATUS_UNKNOWN* 0)
(intern "*PANEL_SUPPLY_STATUS_GOOD*" (find-package "ROSSERIAL_TIVAC_TUTORIALS::PANEL"))
(shadow '*PANEL_SUPPLY_STATUS_GOOD* (find-package "ROSSERIAL_TIVAC_TUTORIALS::PANEL"))
(defconstant rosserial_tivac_tutorials::Panel::*PANEL_SUPPLY_STATUS_GOOD* 1)
(intern "*PANEL_SUPPLY_STATUS_OVERHEAT*" (find-package "ROSSERIAL_TIVAC_TUTORIALS::PANEL"))
(shadow '*PANEL_SUPPLY_STATUS_OVERHEAT* (find-package "ROSSERIAL_TIVAC_TUTORIALS::PANEL"))
(defconstant rosserial_tivac_tutorials::Panel::*PANEL_SUPPLY_STATUS_OVERHEAT* 2)
(intern "*PANEL_SUPPLY_STATUS_OVERVOLTAGE*" (find-package "ROSSERIAL_TIVAC_TUTORIALS::PANEL"))
(shadow '*PANEL_SUPPLY_STATUS_OVERVOLTAGE* (find-package "ROSSERIAL_TIVAC_TUTORIALS::PANEL"))
(defconstant rosserial_tivac_tutorials::Panel::*PANEL_SUPPLY_STATUS_OVERVOLTAGE* 3)
(intern "*PANEL_SUPPLY_STATUS_REVERSEVOLTAGE*" (find-package "ROSSERIAL_TIVAC_TUTORIALS::PANEL"))
(shadow '*PANEL_SUPPLY_STATUS_REVERSEVOLTAGE* (find-package "ROSSERIAL_TIVAC_TUTORIALS::PANEL"))
(defconstant rosserial_tivac_tutorials::Panel::*PANEL_SUPPLY_STATUS_REVERSEVOLTAGE* 4)
(defclass rosserial_tivac_tutorials::Panel
  :super ros::object
  :slots (_panel_location _btn1 _btn2 _btn3 _btn4 ))

(defmethod rosserial_tivac_tutorials::Panel
  (:init
   (&key
    ((:panel_location __panel_location) (instance std_msgs::String :init))
    ((:btn1 __btn1) (instance std_msgs::Bool :init))
    ((:btn2 __btn2) (instance std_msgs::Bool :init))
    ((:btn3 __btn3) (instance std_msgs::Bool :init))
    ((:btn4 __btn4) (instance std_msgs::Bool :init))
    )
   (send-super :init)
   (setq _panel_location __panel_location)
   (setq _btn1 __btn1)
   (setq _btn2 __btn2)
   (setq _btn3 __btn3)
   (setq _btn4 __btn4)
   self)
  (:panel_location
   (&rest __panel_location)
   (if (keywordp (car __panel_location))
       (send* _panel_location __panel_location)
     (progn
       (if __panel_location (setq _panel_location (car __panel_location)))
       _panel_location)))
  (:btn1
   (&rest __btn1)
   (if (keywordp (car __btn1))
       (send* _btn1 __btn1)
     (progn
       (if __btn1 (setq _btn1 (car __btn1)))
       _btn1)))
  (:btn2
   (&rest __btn2)
   (if (keywordp (car __btn2))
       (send* _btn2 __btn2)
     (progn
       (if __btn2 (setq _btn2 (car __btn2)))
       _btn2)))
  (:btn3
   (&rest __btn3)
   (if (keywordp (car __btn3))
       (send* _btn3 __btn3)
     (progn
       (if __btn3 (setq _btn3 (car __btn3)))
       _btn3)))
  (:btn4
   (&rest __btn4)
   (if (keywordp (car __btn4))
       (send* _btn4 __btn4)
     (progn
       (if __btn4 (setq _btn4 (car __btn4)))
       _btn4)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/String _panel_location
    (send _panel_location :serialization-length)
    ;; std_msgs/Bool _btn1
    (send _btn1 :serialization-length)
    ;; std_msgs/Bool _btn2
    (send _btn2 :serialization-length)
    ;; std_msgs/Bool _btn3
    (send _btn3 :serialization-length)
    ;; std_msgs/Bool _btn4
    (send _btn4 :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/String _panel_location
       (send _panel_location :serialize s)
     ;; std_msgs/Bool _btn1
       (send _btn1 :serialize s)
     ;; std_msgs/Bool _btn2
       (send _btn2 :serialize s)
     ;; std_msgs/Bool _btn3
       (send _btn3 :serialize s)
     ;; std_msgs/Bool _btn4
       (send _btn4 :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/String _panel_location
     (send _panel_location :deserialize buf ptr-) (incf ptr- (send _panel_location :serialization-length))
   ;; std_msgs/Bool _btn1
     (send _btn1 :deserialize buf ptr-) (incf ptr- (send _btn1 :serialization-length))
   ;; std_msgs/Bool _btn2
     (send _btn2 :deserialize buf ptr-) (incf ptr- (send _btn2 :serialization-length))
   ;; std_msgs/Bool _btn3
     (send _btn3 :deserialize buf ptr-) (incf ptr- (send _btn3 :serialization-length))
   ;; std_msgs/Bool _btn4
     (send _btn4 :deserialize buf ptr-) (incf ptr- (send _btn4 :serialization-length))
   ;;
   self)
  )

(setf (get rosserial_tivac_tutorials::Panel :md5sum-) "e0220b097b0a0dfac944b58072469424")
(setf (get rosserial_tivac_tutorials::Panel :datatype-) "rosserial_tivac_tutorials/Panel")
(setf (get rosserial_tivac_tutorials::Panel :definition-)
      "#Panel Identification
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
")



(provide :rosserial_tivac_tutorials/Panel "e0220b097b0a0dfac944b58072469424")


