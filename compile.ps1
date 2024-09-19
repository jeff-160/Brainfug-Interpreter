echo Compiling...; 
g++ 'main.cpp' -o 'main'
if ($?) {echo Running...; .\\'main'}