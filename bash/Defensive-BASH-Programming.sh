#!/bin/bash
#Ref: http://www.kfirlavi.com/blog/2012/11/14/defensive-bash-programming 

# Immutable global variables

readonly PROGNAME=$(basename $0)
readonly ARGS="$@"

echo $PROGNAME
echo $ARGS

# Everything is local

change_owner_of_files() {
    local user=$1; shift
    local group=$1; shift
    local files=$@
    local i

    for i in $files
    do
        chown $user:$group $i
    done
}

# main()

main() {
    local files="/tmp/a /tmp/b"
    local i

    for i in $files
    do
        change_owner_of_file kfir users $i
    done
}

# Everything is a function
emporary_files() {
    local dir=$1

    ls $dir \
        | grep pid \
        | grep -v daemon
}

main() {
    local files=$(temporary_files /tmp)
}

# Debugging functions
# bash -x my_prog.sh

temporary_files() {
    local dir=$1

    set -x
    ls $dir \
        | grep pid \
        | grep -v daemon
    set +x
}

# Printing function name and its arguments:
temporary_files() {
    echo $FUNCNAME $@
    local dir=$1

    ls $dir \
        | grep pid \
        | grep -v daemon
}

# Code clarity
is_empty() {
    local var=$1

    [[ -z $var ]]
}

is_not_empty() {
    local var=$1

    [[ -n $var ]]
}

is_file() {
    local file=$1

    [[ -f $file ]]
}

is_dir() {
    local dir=$1

    [[ -d $dir ]]
}

main() {
    local dir=/tmp

    is_empty $dir \
        && do_something...

    is_not_empty $dir \
        && do_something...

    is_file $dir \
        && do_something...

    is_dir $dir \
        && do_something...
}

# Each line does just one thing
temporary_files() {
    local dir=$1

    ls $dir \
        | grep pid \
        | grep -v daemon
}

print_dir_if_not_empty() {
    local dir=$1

    is_empty $dir \
        && echo "dir is empty" \
        || echo "dir=$dir"
}

# Printing usage
usage() {
    echo "this prog does:..."
    echo "flags:"
    echo "-h print help"
}

## Here Document:
usage() {
    cat <<- EOF
	usage: $PROGNAME options
	
	Program deletes files from filesystems to release space. 
	It gets config file that define fileystem paths to work on, and whitelist rules to 
	keep certain files.
	
	OPTIONS:
	   -c --config              configuration file containing the rules. use --help-config to see the syntax.
	   -n --pretend             do not really delete, just how what you are going to do.
	   -t --test                run unit test to check the program
	   -v --verbose             Verbose. You can specify more then one -v to have more verbose
	   -x --debug               debug
	   -h --help                show this help
	      --help-config         configuration help
	
	
	Examples:
	   Run all tests:
	   $PROGNAME --test all
	
	   Run specific test:
	   $PROGNAME --test test_string.sh
	
	   Run:
	   $PROGNAME --config /path/to/config/$PROGNAME.conf
	
	   Just show what you are going to do:
	   $PROGNAME -vn -c /path/to/config/$PROGNAME.conf
    EOF
}

# Command line arguments
cmdline() {
    # got this idea from here:
    # http://kirk.webfinish.com/2009/10/bash-shell-script-to-use-getopts-with-gnu-style-long-positional-parameters/
    local arg=
    for arg
    do
        local delim=""
        case "$arg" in
            #translate --gnu-long-options to -g (short options)
            --config)         args="${args}-c ";;
            --pretend)        args="${args}-n ";;
            --test)           args="${args}-t ";;
            --help-config)    usage_config && exit 0;;
            --help)           args="${args}-h ";;
            --verbose)        args="${args}-v ";;
            --debug)          args="${args}-x ";;
            #pass through anything else
            *) [[ "${arg:0:1}" == "-" ]] || delim="\""
                args="${args}${delim}${arg}${delim} ";;
        esac
    done

    #Reset the positional parameters to the short options
    eval set -- $args

    while getopts "nvhxt:c:" OPTION
    do
         case $OPTION in
         v)
             readonly VERBOSE=1
             ;;
         h)
             usage
             exit 0
             ;;
         x)
             readonly DEBUG='-x'
             set -x
             ;;
         t)
             RUN_TESTS=$OPTARG
             verbose VINFO "Running tests"
             ;;
         c)
             readonly CONFIG_FILE=$OPTARG
             ;;
         n)
             readonly PRETEND=1
             ;;
        esac
    done

    if [[ $recursive_testing || -z $RUN_TESTS ]]; then
        [[ ! -f $CONFIG_FILE ]] \
            && eexit "You must provide --config file"
    fi
    return 0
}

# Unit Testing


