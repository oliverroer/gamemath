set quiet

NAME := "gamemath"
BIN := "./bin"
EXE := BIN + "/" + NAME

build:
    mkdir -p {{BIN}}
    gcc {{NAME}}.c -o {{EXE}} -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

run: build
    ./{{EXE}}

clean:
    rm -rf {{BIN}}
