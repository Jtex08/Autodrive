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

