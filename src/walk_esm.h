#ifndef WALK_ESM_H
#define WALK_ESM_H

#define TYPE_SHARE(type, buf) do { if (strcmp((buf), "GRUP") == 0) (type) = GRUP; else if (strcmp((buf), "TES4") == 0) (type) = TES4; \
else if(strcmp((buf), "DIAL") == 0) (type) = DIAL; else (type) = OTHER; } while(0)
enum HEAD_NAME { GRUP, TES4, DIAL, OTHER};

void walk_esmend();
void stepp_strategy(int type, int idx, void *stream);
void walk_esmset(char *filename, int flag);

#endif //!WALK_ESM_H
