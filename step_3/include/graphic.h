/**
 * @file
 * @brief macro for graphic
 * @see stdio.h
 * 
 * define adequate macro for full control of color that used in text mod in terminal.
 */
#ifndef __GRAPHIC_H_
#define __GRAPHIC_H_
#define __G_R (1 << 2) ///< red
#define __G_G (1 << 1) ///< green
#define __G_B (1) ///< blue

#define G_BLACK (0)
#define G_BLUE (__G_B)
#define G_GREEN (__G_G)
#define G_CYAN (__G_B | __G_G)
#define G_RED (__G_R)
#define G_PINKISH (__G_R | __G_B)
#define G_BROWN (__G_G | __G_R)
#define G_WHITE (__G_G | __G_B | __G_R)

#define TO_FN(X) (X) ///< make defined color into describing font
#define TO_BG(X) (X << 4) ///< make defined color into describing background

#define G_FLASH (1 << 7) ///< whether font is Flash
#define G_DARK (1 << 3) ///< whether font is light

#define G_BG_BLACK (TO_BG(G_BLACK)) ///< Graphic library BackGround Black
#define G_BG_WHITE (TO_BG(G_WHITE)) ///< Graphic library BackGround White

#define G_FN_BLACK (TO_FN(G_BLACK)) ///< Graphic library FoNt black
#define G_FN_WHITE (TO_FN(G_WHITE)) ///< Graphic library FoNt white


#define G_DEFAULT (TO_FN(G_WHITE) | TO_BG(G_BLACK))
#define G_DEFAULT_DARK (G_DEFAULT | G_DARK)
#endif