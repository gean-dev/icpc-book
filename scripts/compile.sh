mkdir -p build
FILE="$1"
echo "
#include \"../content/template/Header.hpp\"
#include \"../$FILE\"
int main() {}
" >build/temp.cpp
g++ -Wall -Wextra -Wfatal-errors -Wconversion -std=c++2a build/temp.cpp -o a.out && rm a.out build/temp.cpp
