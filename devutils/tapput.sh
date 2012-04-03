#!/bin/bash

# Defaults
PROG="/ProgramFiles"
AUTO="$PROG/AutoStart"
USER="guest"
PASS="0000"

usage() {
    echo "Usage: `basename $0`" '[-options] host *.tap'
    echo "Options (-? to list all options):"
    echo "-u <USER> default=\"$USER\""
    echo "-p <PASSWORD> default=\"$PASS\""
    echo "-n (put tap files in \"$PROG\" dir rather than \"$AUTO\")"
    exit 1
}

# Process command line options
DIR=$AUTO
while getopts u:p:n? c; do
    case $c in
    u) USER=$OPTARG;;
    p) PASS=$OPTARG;;
    n) DIR=$PROG;;
    ?) usage;;
    esac
done

shift $((OPTIND - 1))

# Check usage
if [ $# -lt 2 ]; then
    usage
fi

HOST=$1
shift

echo "Copying \"$*\" to $HOST:$DIR/ .."

# For old SD TF5000 series:
#exec ncftpput -W "site turbo 0" $HOST "$DIR" $*

exec ncftpput -u $USER -p $PASS $HOST "$DIR" $*
