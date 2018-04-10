#ifndef __GRAPHIC_H_
#define __GRAPHIC_H_
#define __G_R (1 << 2)
#define __G_G (1 << 1)
#define __G_B (1)

#define G_BLACK (0)
#define G_BLUE (__G_B)
#define G_GREEN (__G_G)
#define G_CYAN (__G_B | __G_G)
#define G_RED (__G_R)
#define G_PINKISH (__G_R | __G_B)
#define G_BROWN (__G_G | __G_R)
#define G_WHITE (__G_G | __G_B | __G_R)

#define TO_FN(X) (X)
#define TO_BG(X) (X << 4)

#define G_FLASH (1 << 7)
#define G_DARK (1 << 3)

#define G_BG_BLACK (TO_BG(G_BLACK))
#define G_BG_WHITE (TO_BG(G_WHITE))

#define G_FN_BLACK (TO_FN(G_BLACK))
#define G_FN_WHITE (TO_FN(G_WHITE))


#define G_DEFAULT (TO_FN(G_WHITE) | TO_BG(G_BLACK))
#define G_DEFAULT_DARK (G_DEFAULT | G_DARK)
#endif