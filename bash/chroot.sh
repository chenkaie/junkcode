#/bin/bash
#開始建立資料夾，請先設定chroot的路徑
chroot_path="/home/chroot"
echo "chroot開始設定，預設路徑/home/chroot" &&
dirlist="$chroot_path $chroot_path/dev $chroot_path/bin $chroot_path/home $chroot_path/lib $chroot_path/etc $chroot_path/usr/lib $chroot_path/usr/bin $chroot_path/proc $chroot_path/dev/pts"
for dir in $dirlist
do
mkdir -p $dir && echo "$dir 資料夾已經建立"
done

#若有需要其他指令讓使用者使用，在下列加入，會自動複製指令與需要的函式庫到chroot環境
cmdlist="/bin/bash /bin/ls /bin/cp /bin/mkdir /bin/mv /bin/rm /bin/rmdir"
#函式庫判斷1
lib_1=`ldd $cmdlist | awk '{ print $1 }' | grep "/lib" | sort | uniq`
#函式庫判斷2
lib_2=`ldd $cmdlist | awk '{ print $3 }' | grep "/lib" | sort | uniq`
#開始複製執行檔
for i in $cmdlist
do
    cp -a $i $chroot_path/bin/ && echo "$i 指令複製完成"
done
#開始複製函式庫1
for j in $lib_1
do
cp -f $j $chroot_path/lib/ && echo "$j 函式庫複製完成"
done
#開始複製函式庫2
for k in $lib_2
do
cp -f $k $chroot_path/lib/ && echo "$k 函式庫複製完成"
done

#其餘設定，一些必要的設定
echo "開始其餘設定"
cd $chroot_path/bin &&
ln -s bash sh &&
#/dev/null和/dev/zero不能用複製的
cd $chroot_path/dev && mknod zero c 13 12 && mknod null c 13 12 && mknod ptmx c 5 2 &&
cp -f /etc/passwd /home/chroot/etc/ &&
cp -f /etc/group /home/chroot/etc/ &&
cp -f /usr/bin/groups $chroot_path/bin/group &&
cp -f /usr/bin/id $chroot_path/bin/id &&
cp "/lib/libnss_files.so.2" $chroot_path/lib &&
cp "/lib/libnss_compat.so.2" $chroot_path/lib &&
#下面兩筆要有才有辦法遠端ssh登入
mount proc $chroot_path/proc -t proc &&
mount devpts $chroot_path/dev/pts -t devpts &&
#簡單的環境變數PS1 & Color tty
echo "簡單的環境變數PS1 & Color tty"
echo "export PS1=\"\n\033[0;36m\u\033[0m \033[1;34m\w\033[0m\n$ \"" > $chroot_path/etc/profile &&
echo "alias ls='ls --color=tty'" >> $chroot_path/etc/profile &&
echo "設定完成"
