#!/usr/bin/env bash

EOC="\e[0m"
BOLD="\e[1m"
RED="\e[91m"
GREEN="\e[92m"
YELLOW="\e[93m"
DBLUE="\e[94m"
PURPLE="\e[95m"
CYAN="\e[96m"
DGREY="\e[1;90m"

include_path="../"
srcs="srcs"

CC="clang++"
CFLAGS="-Wall -Wextra -Werror -std=c++98"
# CFLAGS+=" -fsanitize=address -g3"

ft_compile_output="/dev/null"
std_compile_output="/dev/null"

function pheader () {
printf "${EOC}${BOLD}${DBLUE}\
# ****************************************************************************** #
#                                                                                #
#                                :::   :::   :::                                 #
#                              :+:+: :+:+:  :+: :+:                              #
#                            +:+ +:+:+ +:+ +:+                                   #
#                           +#+  +:+  +#+ +#+ +#+                                #
#                          +#+       +#+ +#+ #+#                                 #
#                         #+#       #+# #+# #+#                                  #
#                        ###       ### ### ###  containers_test                  #
#                                                                                #
# ****************************************************************************** #
${EOC}"
}

compile () {
	# 1=file 2=define used {ft/std} 3=output_file 4?=compile_log
	macro_name=$(echo "USING_${2}" | awk '{ print toupper($0) }')	# USING_STD or USING_FT
	compile_cmd="$CC $CFLAGS -o ${3} -I./$include_path -D ${macro_name} ${1}"
	if [ -n "$4" ]; then	# "$4"에 뭔가가 지정되어 있다면 true
		compile_cmd+=" &>${4}"	# stdout, stderr 를 /dev/null로 (https://stackoverflow.com/questions/24793069/what-does-do-in-bash)
	fi
	eval "${compile_cmd}"
	return $?
}

getEmoji () {
	# 1=integer
	emoji='';
	case $1 in
		0) emoji="${GREEN}✅";;
		1) emoji="${RED}❌";;
		2) emoji="${YELLOW}⚠️ ";;
	esac
	printf "${BOLD}${emoji}${EOC}"
}

getYN () {
	# 1=integer
	res='';
	case $1 in
		0) res="Y";;
		1) res="N";;
	esac
	printf "${res}"
}

printRes () {
	# 1=file 2=compile 3=bin 4=output 5=std_compile
	printf "%-35s: COMPILE: %s | RET: %s | OUT: %s | STD: [%s]\n" \
		"$1" "$(getEmoji $2)" "$(getEmoji $3)" "$(getEmoji $4)" "$(getYN $5)"
}

# If diff_file empty, return 0 -> ok
# If diff is about max_size, return 2 -> warning
# Else, diff is something really important, return 1 -> error
compare_output () {
	# 1=diff_file
	if ! [ -s $1 ]; then	# -s : true if not empty file
		return 0	# empty file!
	fi
	# <<-의 -는 왜있는지 모르겟넹~ 무시되는거 같음
	regex=$(cat <<- EOF			
	^[0-9]*c[0-9]*
	< max_size: [0-9]*
	---
	> max_size: [0-9]*$
	EOF
	)
	cat $1 | grep -v -E -q "$regex"	# 그 패턴에 속하지 않는것, egrep으로 확장해 쓰겠다, 출력않고 조용이 실행
	[ "$?" -eq "0" ] && return 1 || return 2;	# 뭔가 찾았다는건 diff가 남아있다는 거(1), 그게아님 max_size차이(2)
}

isEq () {
	[ $1 -eq $2 ] && echo 0 || echo 1
}

cmp_one () {
	# 1=path/to/file (srcs/map/bounds.cpp)

	deepdir="deepthought"; logdir="logs"
	mkdir -p $deepdir $logdir
	container=$(echo $1 | cut -d "/" -f 2)	# map
	file=$(echo $1 | cut -d "/" -f 3)	# bounds.cpp
	testname=$(echo $file | cut -d "." -f 1)	# bounds
	ft_bin="ft.$container.out"; ft_log="$logdir/ft.$testname.$container.log"
	std_bin="std.$container.out"; std_log="$logdir/std.$testname.$container.log"
	diff_file="$deepdir/$testname.$container.diff"

	clean_trailing_files () {
		rm -f $ft_bin $std_bin
		[ -s "$diff_file" ] || rm -f $diff_file $ft_log $std_log &>/dev/null	# -s : 파일이 비어있지 않으면 참
		rmdir $deepdir $logdir &>/dev/null
	}

	# Launch async compilations for ft/std binaries
	# echo $!
	compile "$1" "ft"  "$ft_bin"  $ft_compile_output & ft_pid=$!;	 # $! : 마지막으로 실행한 백그라운드 프로세스 ID
	compile "$1" "std" "$std_bin" $std_compile_output & std_pid=$!;		# & - 앞의 명령어를 백그라운드로 돌리고 동시에 뒤의 명령어를 실행

	wait ${ft_pid}; ft_ret=$?;
	wait ${std_pid}; std_ret=$?;
	same_compilation=$(isEq $ft_ret $std_ret)
	std_compile=$std_ret

	> $ft_log; > $std_log;
	# Starting async binaries execution (if compilation succeeded)
	if [ ${ft_ret} -eq 0 ]; then
		./${ft_bin} &>${ft_log} &
		ft_pid=$!;
	fi
	if [ ${std_ret} -eq 0 ]; then
		./${std_bin} &>${std_log} &
		std_pid=$!;
	fi

	# Waiting binaries execution (if compilation succeeded)
	if [ "${ft_ret}" -eq 0 ]; then
		wait ${ft_pid}; ft_ret=$?;
	fi
	if [ "${std_ret}" -eq 0 ]; then
		wait ${std_pid}; std_ret=$?;
	fi
	same_bin=$(isEq $ft_ret $std_ret)

	diff $std_log $ft_log 2>/dev/null 1>"$diff_file";
	compare_output $diff_file
	same_output=$?

	printRes "$container/$file" $same_compilation $same_bin $same_output $std_compile
	clean_trailing_files
}

do_test () {
	# 1=container_name
	test_files=$(find "${srcs}/${1}" -type f -name '*.cpp' | sort)	# $0은 스크립트 명이고, ${1}이 첫번째 인수임

	for file in ${test_files[@]}; do
		cmp_one "${file}"
	done
}

function main () {
	pheader
	containers=(vector map stack set)
	# containers=(vector list map stack queue deque multimap set multiset)
	if [ $# -ne 0 ]; then	# $# 스크립트에 전달된 인수갯수 (-ne : not equal)
		containers=($@);	# $*와 유사하지만, "$1", ..."$N"이다. 비교할거-> $* : 모든 위치 매개변수들로 구성된 단일 문자열
							# 이라는 설명보다, $*: 모든인수를 모아서 하나로 처리, $@: 모든인수를 각각 처리.
	fi

	for container in ${containers[@]}; do
		printf "%40s\n" $container
		do_test $container 2>/dev/null
	done
}
