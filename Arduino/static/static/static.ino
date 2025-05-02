
int global_1 = 1;
const int global_3 = 3;
static const int global_4 = 4;
static int global_2 = 2;

struct Globals {
  int struct_global_1 = 1;
  // In standard C++, this line should generate a compiler error because:
  //   Non-static const members must be initialized in the constructor, not inside the struct/class definition.
  const int struct_global_3 = 3;
  static const int struct_global_4 = 4;
  // The only line thaat resultss in a compiling error!
  static int struct_global_2 = 2;
};

void setup()
{
    
}

void loop()
{
    
}
