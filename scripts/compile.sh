mkdir -p build
FILE="$1"
echo "
#include \"../$FILE\"
int main() {}
" >build/temp.cpp
cat build/temp.cpp
cat ../content/Template/template.cpp
g++-13 -Wall -Wextra -Wfatal-errors -Wconversion -std=c++2a build/temp.cpp && rm a.out build/temp.cpp