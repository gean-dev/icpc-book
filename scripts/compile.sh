mkdir -p build
FILE="$1"
echo "
#include \"../content/Template/template.cpp\"
#include \"../$FILE\"
" >build/temp.cpp
g++-13 -Wall -Wextra -Wfatal-errors -Wconversion -std=c++2a build/temp.cpp && rm a.out build/temp.cpp