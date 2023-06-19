#!/bin/bash
sub_dir=$1
target_dir=$2
test_dir=$3
ans_dir=$4
n_test=0
verbose=false
exec=true
exts=("c" "java" "py")
langs=("C" "Java" "Python")
filenames=("main.c" "Main.java" "main.py")

for arg in "$@"; do
  if [[ $arg = "-v" ]]; then
      verbose=true
  else if [[ $arg = "-noexecute" ]]; then
      exec=false
  fi
done

if [[ ! -e "$sub_dir" ]]; then
  echo "Error, submission directory doesn't exist"
fi
if [[ ! -e "$test_dir" ]]; then
  echo "Error, test directory doesn't exist"
fi
if [[ ! -e "$ans_dir" ]]; then
  echo "Error, answer directory doesn't exist"
fi

if [[ ! -e "$target_dir" ]]; then
  mkdir "$target_dir"
fi

for p in "C" "Python" "Java"; do
  f="$target_dir"/$p
  if [[ ! -e "$f" ]]; then
    mkdir "$f"
  fi
done
echo "student_id,type,matched,not_matched" > "$target_dir"/result.csv

for test in "$test_dir"/*; do
  n_test=$((n_test + 1))
done

if $verbose; then
  echo Found $n_test test files
fi

get_lang(){
  case $1 in
    c|C)
      echo 0
      ;;
    java|Java)
      echo 1
      ;;
    py|Python)
      echo 2
      ;;
  esac
}

compile(){
  case "$2" in
    0)
      gcc "$1"/main.c -o "$1"/main.out
      ;;
    1)
      javac "$1"/Main.java
      ;;
  esac          
}

run(){
  case $2 in
    0)
      "$1"/main.out < "$3" > "$4"
      ;;
    1)
      java -cp "$1" Main < "$3" > "$4"
      ;;
    2)
      python3 "$1"/main.py < "$3" > "$4"
      ;;
  esac
}

get_test_no(){
  t=${1%.txt}
  i=${t##*test}
  echo $i
}

process(){
  file=$1
  t=${file%.zip}
  roll=${t: -7}
  unzip -jqq "$file" -d "$target_dir"/temp
  for f in "$target_dir"/temp/*; do
    ext=${f##*.}
    case "$ext" in 
      c|py|java)
        l=$(get_lang $ext)
        lang=${langs[$l]}
        mkdir "$target_dir"/$lang/$roll
        cp "$f" "$target_dir"/$lang/$roll/${filenames[$l]}
        rm -rf "$target_dir"/temp
        break
        ;;
    esac
  done
}

match(){
  ans="$ans_dir"/ans"$2".txt
  if [[ $(diff "$1"/out"$2".txt "$ans") = "" ]]; then
    echo 1
  else
    echo 0
  fi
}

for f in "$sub_dir"/*.zip; do
  process "$f"
done

if $exec; then
  for d in "$target_dir"/*/*; do
    roll=${d##*/}
    lang=${d%/*}
    lang=${lang##*/}
    l=$(get_lang $lang)
    matched=0
    compile "$d" $l
    for test in "$test_dir"/*; do
      i=$(get_test_no "$test")
      run "$d" $lang "$test" "$d"/out$i.txt
      matched=$((matched + $(match "$d" $i)))
    done
    unmatched=$((n_test - matched))
    echo $roll, $lang, $matched, $unmatched >> "$target_dir"/result.csv
  done
fi
