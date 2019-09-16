// krnl.c

const char* text = "Welcome to the C- kernel.";

void kmain(){
  int i,j;
  char* p;

  // Clear
  p = (char*)0xb8000, j = 0;
  while(j < 80 * 25 * 2)
    p[j] = ' ', p[j+1] = 0x03, j += 2;

  // Write
  i = j = 0;
  while(text[j])
    p[i] = text[j], p[i+1] = 0x03, ++j, i += 2;
}
