#!/bin/bash

#
# balance-push - Push content from the master server (localhost) 
#   to multiple front- and back-end servers, in parallel.
#

# $FRONT_END lists the servers that receive the front-end (e.g. static content) updates.
#
FRONT_END=$(cat /usr/local/etc/servers.front)

# $BACK_END lists the hosts that receive the full back-end (e.g. everything) updates.
#
BACK_END=$(cat /usr/local/etc/servers.back)

# $TARGET specifies the filesystem root on the remote host to push to.
#   Normally, you want this to be /, unless you're doing testing.
#
TARGET=/

# $EXCLUDE specifies the prefix of the per-mode rsync exclude files.
#   For example, if your exclude files are /usr/local/etc/balance.front and
#   /usr/local/etc/balance.back, set this to "/usr/local/etc/balance". The 
#   per-mode extensions will be added.
#
EXCLUDE=/usr/local/etc/balance

# $LOCK_DIR specifies a path to put the lock files in.
#
LOCK_DIR=/var/tmp

######## Ignore the shell functions behind the curtain. ########

PATH=/bin:/usr/bin:/usr/local/bin

lock () {
    local lockfile="$LOCK_DIR/balance.$1.lock"
    if [ -f $lockfile ]; then
	if kill -0 $(cat $lockfile); then
	    echo "$0 appears to be already running on $1."
	    echo "Please check $lockfile if you think this is in error."
	    exit 1
        else
	    echo "$0 appears to have completed for $1 without cleaning up its lockfile."
	fi
    fi
    echo $$ > $lockfile
}

unlock () {
    rm -f $LOCK_DIR/balance.$1.lock
}

push_files () {
    local mode=$1 host=$2
    
    if [ ! "$mode" -o ! -r "$EXCLUDE.$mode" ]; then
	echo "$0 $$: mode unset for $host!"
	return
    fi

    if [ ! "$host" ]; then
	echo "$0 $$: host unset for push $mode!"
	return
    fi

    lock $host

    rsync --archive --rsh=ssh --delete --ignore-errors --whole-file \
    	--exclude-from="$EXCLUDE.$mode" / ${host}:${TARGET}

    unlock $host
}

push_tier () {
    local mode=$1 host_list=$2

    for host in $host_list; do
	$SHELL -c "push_files $mode $host" &
    done
}

export -f lock unlock push_files
export TARGET EXCLUDE LOCK_DIR PATH

[ "$FRONT_END" ] && push_tier front "$FRONT_END"
[ "$BACK_END"  ] && push_tier back  "$BACK_END"

#
# Fin.
#
