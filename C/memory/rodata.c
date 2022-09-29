
const char *ro_date = "111111111122222222223333333333444444444455555555555666666666";
const char *ro_data1 = "11111111112222222222333333333344444444445555555555566666666";
int main()
{
    return 0;
}

/*
cyd@blue: (main)~/gitlearn/C/memory$ readelf -SW out/rodata | grep -E ".bss|.rodata|.data|.text|Name"
  [Nr] Name              Type            Address          Off    Size   ES Flg Lk Inf Al
  [14] .text             PROGBITS        0000000000001040 001040 000175 00  AX  0   0 16
  [16] .rodata           PROGBITS        0000000000002000 002000 000045 00   A  0   0  8
  [23] .data             PROGBITS        0000000000004000 003000 000020 00  WA  0   0  8
  [24] .bss              NOBITS          0000000000004020 003020 000008 00  WA  0   0  1
*/
