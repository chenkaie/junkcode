#!/bin/sh
# from Cisco PSBU
if [ $# -lt 2 ]
then
  echo "Usage: ftpfw <camera ip> <ftp_img_name>"
  exit 1;
fi

USERNAME="root"
PASSWORD=""
SERVER=$1
 
# local directory to pickup *.tar.gz file
#FILE="civs-ipc-6000-*.bin"
FILE1=$2
 
# remote server directory to upload backup
FWUPDIR="/tmp"
 
# login to remote server
ftp -n -i $SERVER <<EOF
user $USERNAME 
binary
cd $FWUPDIR
put $FILE1
quit
EOF

expect << EOF
set timeout 400
spawn telnet $1
expect "*login:"
send "root\r"
expect "*#"
send "cd /tmp\r"
expect "*#"
send "tar -xf ftp_img_*.tar\r"
expect #
send "mv megabloks* image.bin\r"
expect "*#"
send "mv u-boot* uboot.bin\r"
expect "*#"
send "chmod a+x /tmp/imageUpgrade\r"
expect "*#"
send "/tmp/imageUpgrade /tmp/image.bin\r"
expect "*#"
send "echo \"Staring upgrade. Please wait for 4-5 minutes\"\r"
expect "*#"
send "exit"
exit
EOF
