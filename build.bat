@echo off

SET RAYLIB_INCLUDE=".\include"
SET RAYLIB_A=".\lib\libraylib.a"
SET NAME=gamemath
zig cc -o %NAME%.exe %NAME%.c -I"%RAYLIB_INCLUDE%" "%RAYLIB_A%" -lopengl32 -lgdi32 -lwinmm
