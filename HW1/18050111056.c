#include <hellomake.h>

int main() {
int main(int argc, char *argv[]) {
  // call a function in another file
  myPrintHelloMake();

  int numRow = atoi(argv[1]);
  int numCol = atoi(argv[2]);

  char * filename = argv[3];

  myMatrixVectorMul(numRow, numCol, filename);

  return(0);
}
