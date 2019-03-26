
(cl:in-package :asdf)

(defsystem "rosserial_tivac_tutorials-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "Buttons" :depends-on ("_package_Buttons"))
    (:file "_package_Buttons" :depends-on ("_package"))
    (:file "Panel" :depends-on ("_package_Panel"))
    (:file "_package_Panel" :depends-on ("_package"))
  ))