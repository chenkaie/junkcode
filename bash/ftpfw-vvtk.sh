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
FWUPDIR="/mnt/ramdisk"
 
# login to remote server
ftp -n -i $SERVER <<EOF
user $USERNAME 
binary
hash
cd $FWUPDIR
put $FILE1 ftpfw.flash.pkg
quit
EOF

expect << EOF
set timeout 400
spawn telnet $1
expect "*login:"
send "root\r"
expect "*#"
send "cd $FWUPDIR\r"
expect "*#"
send "firmunpack *.flash.pkg\r"
expect "*#"
send "tar -zxvf setup.tar.gz\r"
expect "*#"
send "cat setup/flashpartition\r"
expect "*#"
send "echo \"This is an upgradable firmware.\"\r"
expect "*#"
send "exit"
exit
EOF
