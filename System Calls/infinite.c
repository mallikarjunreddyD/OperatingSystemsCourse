int main() {
    int i;
    int pid[10];
    for (i=0;i<10;i++) {
      if ((pid[i] = fork()) == 0) {
        while(1);
      }
    }
}
