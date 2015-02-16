mount -t nfs -o tcp,nolock 172.16.5.32:/home /home
for x in `ps |grep venc | awk '{print $1}'`; do /home/kent.chen/Project/PlatMozart3/busybox-1.12.4_VVTK/chrt -o -p 0 $x; done

