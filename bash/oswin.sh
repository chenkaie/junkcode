echo '>>>>>>> Test "$@"'
for thing in "$@"; do
	echo $thing
done

echo '>>>>>>> Test "$@", after expansion'
for thing in "$1" "$2" "$3"; do
	echo $thing
done

echo '>>>>>>> Test $@'
for thing in $@; do
	echo $thing
done

echo '>>>>>>> Test $@, after expansion'
for thing in $1 $2 $3; do
	echo $thing
done
