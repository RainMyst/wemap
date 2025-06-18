#ifndef MYREAD_H
#define MYREAD_H
#define READ(fp, out, nbyte) do {if (fread(out, 1, nbyte, fp) != nbyte) { fprintf(stderr, "READ error\n"); exit(1); } } while(0)
#define LSEEK(fp, size, flag) do {if (fseek(fp, size, flag) == -1) { fprintf(stderr, "LSEEK error\n"); exit(1); } } while (0)
#endif //!MYREAD_H

