#!/bin/bash

make bonus || exit 1
export LC_ALL=C
clear

g_options=('a' 'r' 'l' 't' 'R' 'g' 'd' 'u' 'f')
g_flags="valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --track-fds=yes"
g_flags=""

generate_options()
{
	local combinations=("")

	for opt in "${g_options[@]}"; do
		local current_length=${#combinations[@]}
		for ((i=0; i<current_length; i++)); do
			combinations+=("${combinations[i]}$opt")
		done
	done

	local formatted=()
	for combo in "${combinations[@]}"; do
		if [ -z "$combo" ]; then
			formatted+=("")
		else
			formatted+=("-$combo")
		fi
	done

	printf '%s\n' "${formatted[@]}"
}

g_ret=0
g_dir=tester/logs_bonus

rm -rf $g_dir
mkdir -p $g_dir

n()
{
	local	dir

	if [[ "$1" == -* ]]; then
		dir=$g_dir/$1
	else
		dir=$g_dir/default
	fi

	mkdir -p $dir

	echo "Testing: $@"

	$g_flags ./ft_ls_bonus "$@" 2>>$g_dir/valgrind.txt > $dir/ft_ls.txt
	local ft_ls_ret=$?

	ls -1 "$@" 2>/dev/null > $dir/ls.txt
	local ls_ret=$?

	if [ $ls_ret -ne $ft_ls_ret ]; then
		echo "❌ Return values differents (ls:$ls_ret | ft_ls:$ft_ls_ret)"
		let "g_ret+=1"
	fi

	if diff $dir/ls.txt $dir/ft_ls.txt > $dir/diff.txt; then
		echo "Success ✅"
		rm -rf $dir
	else
		echo "Fail ❌ (see $dir/diff.txt)"
		let "g_ret+=1"
	fi
}

mapfile -t options < <(generate_options)
size=${#options[@]}

for opt in "${options[@]}"; do
	n $opt "$@"
done

if [ "$g_ret" -eq 0 ]; then
	echo "✅ All tests passed successfully, congratulations ! ($size combinations tested)"
	exit 0
elif [ "$g_ret" -eq 1 ]; then
	echo "❌" $g_ret "test failed /" $size
else
	echo "❌" $g_ret "tests failed /" $size
fi

exit 1