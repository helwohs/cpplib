#!/bin/bash

cd "$(dirname "${BASH_SOURCE[0]#./}")/.."

LIB_DIR="$PWD"

CXX="${CXX:-"g++-7"}"
CXXFLAGS="-std=c++17 -pedantic -Wall -Wextra -O3"
DEFINE=""
INCLUDE="-I $LIB_DIR/include"
CPPFLAGS="$DEFINE $INCLUDE"

exit_code=0
tempfile="$(mktemp)"

function dfs {
    echo "Testing $1..."
    for sample in *.cpp; do
        [[ -f $sample ]] || continue

        printf "Compiling ${sample%.*}... "
        if $CXX $CXXFLAGS $CPPFLAGS $sample -o "${sample%.*}.out" &> "$tempfile"; then
            printf "\033[0;32mOK\033[0m\n"
        else
            printf "\033[0;31mFAILED\033[0m\n"
            # cat "$tempfile"
            exit_code=1
            continue
        fi

        for stdin_file in ${sample%.*}_*.stdin; do
            [[ -e $stdin_file ]] || break

            stdout_file="${stdin_file%.*}.stdout"

            printf "Testing ${stdin_file%.*}... "
            if "./${sample%.*}.out" < "$stdin_file" | diff - "$stdout_file" -BZ > "$tempfile"; then
                printf "\033[0;32mOK\033[0m\n"
            else
                printf "\033[0;31mFAILED\033[0m\n"
                # cat "$tempfile"
                exit_code=1
            fi
        done

        rm -f "${sample%.*}.out"
    done

    for file in *; do
        [[ -d $file ]] || continue

        cd "$file"
        dfs "$1/$file"
        cd ..
    done
}

cd "$LIB_DIR/test/cpplib"
dfs "cpplib"

rm "$tempfile"
exit $exit_code
