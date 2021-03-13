
const int a = 1103515245;
const int c = 12345;
int
rand(int ticks, int max){ 
  return (((ticks * a) + c)%max);
}