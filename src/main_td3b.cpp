#include "Countdown.h"

int main (int argc, char **argv) {
  Countdown countdown(10);
  countdown.start(1000);

  return 0;
}