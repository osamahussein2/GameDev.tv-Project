#include "raylib.h"

int main()
{
    bool equal{4 == 9}; // false
    bool notEqual{4 != 9}; // true
    bool less{4 < 9}; // true
    bool greater{4 > 9};  // false
    bool lessEqual{4 <= 9}; // true
    bool greaterEqual{ 4 >= 9};  // false

    int width;
    width = 350;

    InitWindow(width, 200, "Osama's Window");
}