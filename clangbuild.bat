@echo off
cd src
clang main.cpp algo.cpp TruthTable.cpp EvalType.cpp -o ..\build\main.exe
cd..
@echo on