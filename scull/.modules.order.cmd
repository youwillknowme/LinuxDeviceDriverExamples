cmd_/home/xdx/LinuxDeviceDriverExamples/scull/modules.order := {   echo /home/xdx/LinuxDeviceDriverExamples/scull/scull.ko; :; } | awk '!x[$$0]++' - > /home/xdx/LinuxDeviceDriverExamples/scull/modules.order