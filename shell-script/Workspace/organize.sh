#!/bin/bash

sub_dir=$1
target_dir=$2
test_dir=$3
ans_dir=$4

if [[ ! -e "$sub_dir" ]]; then
  echo "Error, submission directory doesn't exist"
fi
if [[ ! -e "$test_dir" ]]; then
  echo "Error, test directory doesn't exist"
fi
if [[ ! -e "$ans_dir" ]]; then
  echo "Error, answer directory doesn't exist"
fi

# create dirs and file(s)
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

get_lang(){
  case $1 in
    c)
      echo "C"
      ;;
    java)
      echo "Java"
      ;;
    py)
      echo "Python"
      ;;
  esac
}

rename(){
  name=$(basename "$1")
  dir=$(dirname "$1")
  case "$2" in
    c)
      if [[ "$name" != "main.c" ]]; then
        mv "$1" "$dir"/main.c
      fi
      ;;
    py)
      if [[ "$name" != "main.py" ]]; then
        mv "$1" "$dir"/main.py
      fi
      ;;
    java)
      if [[ "$name" != "Main.java" ]]; then
        mv "$1" "$dir"/Main.java
      fi
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
        lang=$(get_lang $ext)
        mkdir "$target_dir"/$lang/$roll
        cp "$f" "$target_dir"/$lang/$roll
        rename "$target_dir"/$lang/$roll/* $ext
        rm -rf "$target_dir"/temp
        break
        ;;
      *)
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

for d in "$target_dir"/C/*; do
  gcc "$d"/main.c -o "$d"/main.out
  matched=0
  n=0
  for test in "$test_dir"/*; do
    i=$(get_test_no "$test")
    "$d"/main.out < "$test" > "$d"/out$i.txt
    matched=$((matched + $(match "$d" $i)))
    n=$((n + 1))
  done
  unmatched=$((n - matched))
done

for d in "$target_dir"/Java/*; do
  javac "$d"/Main.java
  matched=0
  n=0
  for test in "$test_dir"/*; do
    i=$(get_test_no "$test")
    java -cp "$d" Main < "$test" > "$d"/out$i.txt
    matched=$((matched + $(match "$d" $i)))
    n=$((n + 1))
  done
  unmatched=$((n - matched))
done

for d in "$target_dir"/Python/*; do
  matched=0
  n=0
  for test in "$test_dir"/*; do
    i=$(get_test_no "$test")
    python3 "$d"/main.py < "$test" > "$d"/out$i.txt
    matched=$((matched + $(match "$d" $i)))
    n=$((n + 1))
  done
  unmatched=$((n - matched))
done

for d in "$target_dir"/*/*; do
  roll=${d##*/}
  lang=${d%/*}
  lang=${lang##*/}
  matched=0
  n=0
  for test in "$test_dir"/*; do
    i=$(get_test_no "$test")
    matched=$((matched + $(match "$d" $i)))
    n=$((n + 1))
  done
  unmatched=$((n - matched))
  echo $roll, $lang, $matched, $unmatched >> "$target_dir"/result.csv
done
  
