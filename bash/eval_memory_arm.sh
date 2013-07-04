echo "#Kernel memory usage :"
#For Vivaldi Kernel v2.4
StartHex=`cat /proc/iomem | grep "Kernel code" |awk -F"-| " '{print $3}'`
#For Bach Kernel v2.6
#StartHex=`cat /proc/iomem | grep "Kernel text" |awk -F"-| " '{print $3}'`
EndHex=`cat /proc/iomem | grep "Kernel data" |awk -F"-| " '{print $4}'`
let Start=0x$StartHex
let End=0x$EndHex
K_size=`expr \( $End - $Start \) / 1024`
echo $K_size

echo -e "#Kernel modules memory usage :"
Modules_prog=`lsmod > module_size; cat module_size |awk '{printf("%d + ",$2)}' |sed -e 's/+[^+]*$//'`; rm module_size;
M_size_inByte=`expr $Modules_prog`
M_size=`expr $M_size_inByte / 1024`
echo $M_size

echo -e "#Process VmSize memory usage :"
Process_prog=`ps |egrep -v " ps | telnetd |vencslave.1" > process_size; cat process_size | awk '{print $3,$4,$5}' | sort | uniq |awk '{printf("%d + ",$1)}' |sed -e 's/+[^+]*$//'`;
rm process_size;
P_size=`expr $Process_prog`
echo $P_size

echo -e "Total memory usage =>"
expr $K_size + $M_size + $P_size

#show free info for comparison
free

