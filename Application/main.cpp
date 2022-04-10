#include "Printer.h"
#include "hello.h"

int main(int argc, char **argv) {
  printHelloWorld();

  Printer p = Printer();
  p.Print("hello");
}
