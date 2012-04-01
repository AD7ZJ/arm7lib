#include "Tahoma_10_n_nnnn_0_nh.h"

#include <stdio.h>


const fuint8  font_Tahoma_10_n_nnnn_0_nh_width_table[];
const fuint8  font_Tahoma_10_n_nnnn_0_nh_black_width_table[];
const fint8   font_Tahoma_10_n_nnnn_0_nh_origin_x_table[];
const fuint8  font_Tahoma_10_n_nnnn_0_nh_glyph_table[];
#ifdef FONTGEN_USE_MAPPING_TABLE
const fuint8  font_Tahoma_10_n_nnnn_0_nh_mapping_table[];
#endif
#ifdef FONTGEN_USE_EXTENDED_MAPPING_TABLE
const fuint16 font_Tahoma_10_n_nnnn_0_nh_extended_mapping_table[];
#endif
#ifdef FONTGEN_USE_PRECALCULATED_OFFSETS
const fuint16 font_Tahoma_10_n_nnnn_0_nh_offset_table[];
#endif


/*
   Unicode to current codepage codes:
   ----------------------------------
   User requested to care current codepage of Windows. So, unicode character 
   codes are converted to the codes which is used by the current code page 
   (windows-1252: ANSI Latin 1; Western European (Windows) ) whenever possible. 
   
   This conversion is quite helpful when your codepage is different than the
   standart ASCII code table, and using those characters in your strings in 
   your IDE which is not in the ASCII code table.
   
   Consider you're using MS Windows for Turkey, with the current codepage
   'windows-1254: ANSI Turkish; Turkish (Windows)'; and want to use the Turkish
   characters on your LCD interface. 
   
   Consider the 'I' character with a dot above. Its unicode code is 0x0130.
   Its code in the windows1254 codepage is 0xDD. When I create a string with
   this character in it, the IDE will put 0xDD for the character. When you 
   address the FontGen tables with 0xDD, you'll reach to a wrong or invalid glyph.
   
   When the 'care codepage' option is checked, FontGen will use 0xDD instead of 
   0x0130 for all occurences of this character. This will fix the problem 
   described above.
 */
   

 
const FONT_DEF Tahoma_10_n_nnnn_0_nh = {
#ifdef FONTGEN_HAVE_VERSION
   4, 	/* Version of the image definition format */
#ifdef FONTGEN_FIT_TO_16BIT_BOUNDARY
   0, 	/* filler for 16 bit boundary alignment   */
#endif
#endif
   16, 	/* glyph_height */
   0, 	/* glyph_width (this font has variable width for each glyph.)
      	   Check the below array for the width of the glyphs */
   (fuint8 *)font_Tahoma_10_n_nnnn_0_nh_width_table,
   NULL, /* black height table */
   (fuint8 *)font_Tahoma_10_n_nnnn_0_nh_black_width_table, /* black width table */
   NULL, /* origin Y table */
   (fint8  *)font_Tahoma_10_n_nnnn_0_nh_origin_x_table, /* origin X table */
#ifdef FONTGEN_HAVE_MINMAX_Y
   0, /* minimum origin Y over all characters in this character set */
   16, /* maximum ending point of black area (origin_y + black_height) over all characters in this character set */
#endif
#ifdef FONTGEN_HAVE_MINMAX_X
   -1, /* minimum origin X over all characters in this character set */
   11, /* maximum ending point of black area (origin_x + black_width) over all characters in this character set */
#endif
   (fuint8 *)font_Tahoma_10_n_nnnn_0_nh_glyph_table,
#ifdef FONTGEN_HAVE_MAPPING_TABLE 
#ifdef FONTGEN_USE_MAPPING_TABLE 
   (fuint8 *)font_Tahoma_10_n_nnnn_0_nh_mapping_table,
#else
   NULL,
#endif
#endif 
#ifdef FONTGEN_HAVE_EXTENDED_MAPPING_TABLE 
#ifdef FONTGEN_USE_EXTENDED_MAPPING_TABLE 
   (fuint16 *)font_Tahoma_10_n_nnnn_0_nh_extended_mapping_table,
#else
   NULL,
#endif
#endif 
#ifdef FONTGEN_HAVE_PRECALCULATED_OFFSETS
#ifdef FONTGEN_USE_PRECALCULATED_OFFSETS 
   (fuint16 *)font_Tahoma_10_n_nnnn_0_nh_offset_table,
#else 
   NULL, 
#endif 
#endif 
   96, 	/* number of glyphs in this font definition */
#ifdef FONTGEN_HAVE_FONT_DETAILS
   10, 	/* font size */
#endif
   0, 	/* rotation / 90 */
   1, 	/* color depth in bits */
#ifdef FONTGEN_HAVE_FONT_DETAILS
   0, 	/* bold? */
   0, 	/* italic? */
   0, 	/* underline? */
   0, 	/* strikeout? */
   0, 	/* flipX? */
   0, 	/* flipY? */
   0  	/* reverse? */
#endif
};



/* Following table provides the width information in pixels for each character
   selected.
   
   You should index this array with the index of the char in your character set.
   This can be calculated with a simple mathematical expression if you have such
   a simple expression, or you can use the mapping table for this purpose.
   
   To find the width of a glyph in font_Tahoma_10_n_nnnn_0_nh_width_table[],
   use the following expression:
   	font_Tahoma_10_n_nnnn_0_nh_width_table[font_Tahoma_10_n_nnnn_0_nh_offset_table[c]]
   where 'c' is the variable holding the character you're interested in
   
   This table is produced only for the variable width fonts. For the fixed width
   fonts, you should use the width information in FONT_DEF struct.
 */
const fuint8 font_Tahoma_10_n_nnnn_0_nh_width_table[] = {
/*		width  char hexcode*/
/*		=====  ==== =======*/
		 4, /* ' ' 0x0020*/
		 4, /* '!' 0x0021*/
		 5, /* '"' 0x0022*/
		 9, /* '#' 0x0023*/
		 7, /* '$' 0x0024*/
		12, /* '%' 0x0025*/
		 9, /* '&' 0x0026*/
		 3, /* ''' 0x0027*/
		 5, /* '(' 0x0028*/
		 5, /* ')' 0x0029*/
		 8, /* '*' 0x002A*/
		 8, /* '+' 0x002B*/
		 4, /* ',' 0x002C*/
		 5, /* '-' 0x002D*/
		 4, /* '.' 0x002E*/
		 5, /* '/' 0x002F*/
		 7, /* '0' 0x0030*/
		 7, /* '1' 0x0031*/
		 7, /* '2' 0x0032*/
		 7, /* '3' 0x0033*/
		 7, /* '4' 0x0034*/
		 7, /* '5' 0x0035*/
		 7, /* '6' 0x0036*/
		 7, /* '7' 0x0037*/
		 7, /* '8' 0x0038*/
		 7, /* '9' 0x0039*/
		 5, /* ':' 0x003A*/
		 5, /* ';' 0x003B*/
		 9, /* '<' 0x003C*/
		 9, /* '=' 0x003D*/
		 9, /* '>' 0x003E*/
		 6, /* '?' 0x003F*/
		12, /* '@' 0x0040*/
		 8, /* 'A' 0x0041*/
		 7, /* 'B' 0x0042*/
		 8, /* 'C' 0x0043*/
		 8, /* 'D' 0x0044*/
		 7, /* 'E' 0x0045*/
		 7, /* 'F' 0x0046*/
		 8, /* 'G' 0x0047*/
		 8, /* 'H' 0x0048*/
		 4, /* 'I' 0x0049*/
		 5, /* 'J' 0x004A*/
		 7, /* 'K' 0x004B*/
		 6, /* 'L' 0x004C*/
		10, /* 'M' 0x004D*/
		 8, /* 'N' 0x004E*/
		 9, /* 'O' 0x004F*/
		 7, /* 'P' 0x0050*/
		 9, /* 'Q' 0x0051*/
		 8, /* 'R' 0x0052*/
		 8, /* 'S' 0x0053*/
		 8, /* 'T' 0x0054*/
		 8, /* 'U' 0x0055*/
		 8, /* 'V' 0x0056*/
		12, /* 'W' 0x0057*/
		 8, /* 'X' 0x0058*/
		 7, /* 'Y' 0x0059*/
		 7, /* 'Z' 0x005A*/
		 5, /* '[' 0x005B*/
		 5, /* '\' 0x005C*/
		 5, /* ']' 0x005D*/
		 9, /* '^' 0x005E*/
		 7, /* '_' 0x005F*/
		 7, /* '`' 0x0060*/
		 7, /* 'a' 0x0061*/
		 7, /* 'b' 0x0062*/
		 6, /* 'c' 0x0063*/
		 7, /* 'd' 0x0064*/
		 7, /* 'e' 0x0065*/
		 4, /* 'f' 0x0066*/
		 7, /* 'g' 0x0067*/
		 7, /* 'h' 0x0068*/
		 3, /* 'i' 0x0069*/
		 4, /* 'j' 0x006A*/
		 6, /* 'k' 0x006B*/
		 3, /* 'l' 0x006C*/
		11, /* 'm' 0x006D*/
		 7, /* 'n' 0x006E*/
		 7, /* 'o' 0x006F*/
		 7, /* 'p' 0x0070*/
		 7, /* 'q' 0x0071*/
		 5, /* 'r' 0x0072*/
		 6, /* 's' 0x0073*/
		 4, /* 't' 0x0074*/
		 7, /* 'u' 0x0075*/
		 6, /* 'v' 0x0076*/
		10, /* 'w' 0x0077*/
		 6, /* 'x' 0x0078*/
		 6, /* 'y' 0x0079*/
		 6, /* 'z' 0x007A*/
		 6, /* '{' 0x007B*/
		 6, /* '|' 0x007C*/
		 6, /* '}' 0x007D*/
		 6, /* '�' 0x00B0*/
		 8, /* '�' 0x00B1*/
};








/* Following is the one dimensional flat array to hold the font information.
   
   Each byte holds the color information for the successive pixels.
   If the color_depth=1, then each byte will hold the color info (or set/reset)
   for 8 pixels. 
   
   Even it is a one-dimensional array, the representation is in matrix format,
   where each line is holding the color information of a line of the glyph.
   
   The starting offset of a given glyph can be calculated by code using the
   width and height information of the all characters before the given character.
   Or array font_Tahoma_10_n_nnnn_0_nh_offset_table[] can be used for this purpose.
 */
const fuint8 font_Tahoma_10_n_nnnn_0_nh_glyph_table[] = {
		/* char: ' ' hexcode: 0x0020 glyph_width: 4 black_width: 1 origin_x: 0 */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		
		/* char: '!' hexcode: 0x0021 glyph_width: 4 black_width: 1 origin_x: 1 */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x80, 	/*  [*]  */
		0x80, 	/*  [*]  */
		0x80, 	/*  [*]  */
		0x80, 	/*  [*]  */
		0x80, 	/*  [*]  */
		0x80, 	/*  [*]  */
		0x00, 	/*  [ ]  */
		0x80, 	/*  [*]  */
		0x80, 	/*  [*]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		
		/* char: '"' hexcode: 0x0022 glyph_width: 5 black_width: 3 origin_x: 1 */
		0x00, 	/*  [   ]  */
		0x00, 	/*  [   ]  */
		0x00, 	/*  [   ]  */
		0xA0, 	/*  [* *]  */
		0xA0, 	/*  [* *]  */
		0xA0, 	/*  [* *]  */
		0xA0, 	/*  [* *]  */
		0x00, 	/*  [   ]  */
		0x00, 	/*  [   ]  */
		0x00, 	/*  [   ]  */
		0x00, 	/*  [   ]  */
		0x00, 	/*  [   ]  */
		0x00, 	/*  [   ]  */
		0x00, 	/*  [   ]  */
		0x00, 	/*  [   ]  */
		0x00, 	/*  [   ]  */
		
		/* char: '#' hexcode: 0x0023 glyph_width: 9 black_width: 7 origin_x: 1 */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x14, 	/*  [   * * ]  */
		0x14, 	/*  [   * * ]  */
		0x7E, 	/*  [ ******]  */
		0x28, 	/*  [  * *  ]  */
		0x28, 	/*  [  * *  ]  */
		0xFC, 	/*  [****** ]  */
		0x28, 	/*  [  * *  ]  */
		0x50, 	/*  [ * *   ]  */
		0x50, 	/*  [ * *   ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		
		/* char: '$' hexcode: 0x0024 glyph_width: 7 black_width: 6 origin_x: 0 */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x20, 	/*  [  *   ]  */
		0x20, 	/*  [  *   ]  */
		0x7C, 	/*  [ *****]  */
		0xA0, 	/*  [* *   ]  */
		0xA0, 	/*  [* *   ]  */
		0x60, 	/*  [ **   ]  */
		0x38, 	/*  [  *** ]  */
		0x24, 	/*  [  *  *]  */
		0x24, 	/*  [  *  *]  */
		0xF8, 	/*  [***** ]  */
		0x20, 	/*  [  *   ]  */
		0x20, 	/*  [  *   ]  */
		0x00, 	/*  [      ]  */
		
		/* char: '%' hexcode: 0x0025 glyph_width: 12 black_width: 10 origin_x: 1 */
		0x00, 0x00, 	/*  [          ]  */
		0x00, 0x00, 	/*  [          ]  */
		0x00, 0x00, 	/*  [          ]  */
		0x00, 0x00, 	/*  [          ]  */
		0x61, 0x00, 	/*  [ **    *  ]  */
		0x92, 0x00, 	/*  [*  *  *   ]  */
		0x92, 0x00, 	/*  [*  *  *   ]  */
		0x94, 0x00, 	/*  [*  * *    ]  */
		0x69, 0x80, 	/*  [ ** *  ** ]  */
		0x0A, 0x40, 	/*  [    * *  *]  */
		0x12, 0x40, 	/*  [   *  *  *]  */
		0x12, 0x40, 	/*  [   *  *  *]  */
		0x21, 0x80, 	/*  [  *    ** ]  */
		0x00, 0x00, 	/*  [          ]  */
		0x00, 0x00, 	/*  [          ]  */
		0x00, 0x00, 	/*  [          ]  */
		
		/* char: '&' hexcode: 0x0026 glyph_width: 9 black_width: 9 origin_x: 0 */
		0x00, 0x00, 	/*  [         ]  */
		0x00, 0x00, 	/*  [         ]  */
		0x00, 0x00, 	/*  [         ]  */
		0x00, 0x00, 	/*  [         ]  */
		0x78, 0x00, 	/*  [ ****    ]  */
		0x84, 0x00, 	/*  [*    *   ]  */
		0x84, 0x00, 	/*  [*    *   ]  */
		0x48, 0x00, 	/*  [ *  *    ]  */
		0x72, 0x00, 	/*  [ ***  *  ]  */
		0x8A, 0x00, 	/*  [*   * *  ]  */
		0x86, 0x00, 	/*  [*    **  ]  */
		0x86, 0x00, 	/*  [*    **  ]  */
		0x79, 0x00, 	/*  [ ****  * ]  */
		0x00, 0x00, 	/*  [         ]  */
		0x00, 0x00, 	/*  [         ]  */
		0x00, 0x00, 	/*  [         ]  */
		
		/* char: ''' hexcode: 0x0027 glyph_width: 3 black_width: 1 origin_x: 1 */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x80, 	/*  [*]  */
		0x80, 	/*  [*]  */
		0x80, 	/*  [*]  */
		0x80, 	/*  [*]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		
		/* char: '(' hexcode: 0x0028 glyph_width: 5 black_width: 4 origin_x: 1 */
		0x00, 	/*  [    ]  */
		0x00, 	/*  [    ]  */
		0x00, 	/*  [    ]  */
		0x10, 	/*  [   *]  */
		0x20, 	/*  [  * ]  */
		0x40, 	/*  [ *  ]  */
		0x40, 	/*  [ *  ]  */
		0x80, 	/*  [*   ]  */
		0x80, 	/*  [*   ]  */
		0x80, 	/*  [*   ]  */
		0x80, 	/*  [*   ]  */
		0x80, 	/*  [*   ]  */
		0x40, 	/*  [ *  ]  */
		0x40, 	/*  [ *  ]  */
		0x20, 	/*  [  * ]  */
		0x10, 	/*  [   *]  */
		
		/* char: ')' hexcode: 0x0029 glyph_width: 5 black_width: 4 origin_x: 0 */
		0x00, 	/*  [    ]  */
		0x00, 	/*  [    ]  */
		0x00, 	/*  [    ]  */
		0x80, 	/*  [*   ]  */
		0x40, 	/*  [ *  ]  */
		0x20, 	/*  [  * ]  */
		0x20, 	/*  [  * ]  */
		0x10, 	/*  [   *]  */
		0x10, 	/*  [   *]  */
		0x10, 	/*  [   *]  */
		0x10, 	/*  [   *]  */
		0x10, 	/*  [   *]  */
		0x20, 	/*  [  * ]  */
		0x20, 	/*  [  * ]  */
		0x40, 	/*  [ *  ]  */
		0x80, 	/*  [*   ]  */
		
		/* char: '*' hexcode: 0x002A glyph_width: 8 black_width: 5 origin_x: 1 */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x20, 	/*  [  *  ]  */
		0xA8, 	/*  [* * *]  */
		0x70, 	/*  [ *** ]  */
		0xA8, 	/*  [* * *]  */
		0x20, 	/*  [  *  ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		
		/* char: '+' hexcode: 0x002B glyph_width: 8 black_width: 7 origin_x: 0 */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x10, 	/*  [   *   ]  */
		0x10, 	/*  [   *   ]  */
		0x10, 	/*  [   *   ]  */
		0xFE, 	/*  [*******]  */
		0x10, 	/*  [   *   ]  */
		0x10, 	/*  [   *   ]  */
		0x10, 	/*  [   *   ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		
		/* char: ',' hexcode: 0x002C glyph_width: 4 black_width: 3 origin_x: 0 */
		0x00, 	/*  [   ]  */
		0x00, 	/*  [   ]  */
		0x00, 	/*  [   ]  */
		0x00, 	/*  [   ]  */
		0x00, 	/*  [   ]  */
		0x00, 	/*  [   ]  */
		0x00, 	/*  [   ]  */
		0x00, 	/*  [   ]  */
		0x00, 	/*  [   ]  */
		0x00, 	/*  [   ]  */
		0x00, 	/*  [   ]  */
		0x40, 	/*  [ * ]  */
		0x40, 	/*  [ * ]  */
		0x40, 	/*  [ * ]  */
		0x80, 	/*  [*  ]  */
		0x00, 	/*  [   ]  */
		
		/* char: '-' hexcode: 0x002D glyph_width: 5 black_width: 4 origin_x: 0 */
		0x00, 	/*  [    ]  */
		0x00, 	/*  [    ]  */
		0x00, 	/*  [    ]  */
		0x00, 	/*  [    ]  */
		0x00, 	/*  [    ]  */
		0x00, 	/*  [    ]  */
		0x00, 	/*  [    ]  */
		0x00, 	/*  [    ]  */
		0xF0, 	/*  [****]  */
		0x00, 	/*  [    ]  */
		0x00, 	/*  [    ]  */
		0x00, 	/*  [    ]  */
		0x00, 	/*  [    ]  */
		0x00, 	/*  [    ]  */
		0x00, 	/*  [    ]  */
		0x00, 	/*  [    ]  */
		
		/* char: '.' hexcode: 0x002E glyph_width: 4 black_width: 1 origin_x: 1 */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x80, 	/*  [*]  */
		0x80, 	/*  [*]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		
		/* char: '/' hexcode: 0x002F glyph_width: 5 black_width: 5 origin_x: 0 */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x08, 	/*  [    *]  */
		0x08, 	/*  [    *]  */
		0x10, 	/*  [   * ]  */
		0x10, 	/*  [   * ]  */
		0x10, 	/*  [   * ]  */
		0x20, 	/*  [  *  ]  */
		0x20, 	/*  [  *  ]  */
		0x40, 	/*  [ *   ]  */
		0x40, 	/*  [ *   ]  */
		0x40, 	/*  [ *   ]  */
		0x80, 	/*  [*    ]  */
		0x80, 	/*  [*    ]  */
		0x00, 	/*  [     ]  */
		
		/* char: '0' hexcode: 0x0030 glyph_width: 7 black_width: 6 origin_x: 0 */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x78, 	/*  [ **** ]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0x78, 	/*  [ **** ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		
		/* char: '1' hexcode: 0x0031 glyph_width: 7 black_width: 5 origin_x: 1 */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x20, 	/*  [  *  ]  */
		0xE0, 	/*  [***  ]  */
		0x20, 	/*  [  *  ]  */
		0x20, 	/*  [  *  ]  */
		0x20, 	/*  [  *  ]  */
		0x20, 	/*  [  *  ]  */
		0x20, 	/*  [  *  ]  */
		0x20, 	/*  [  *  ]  */
		0xF8, 	/*  [*****]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		
		/* char: '2' hexcode: 0x0032 glyph_width: 7 black_width: 6 origin_x: 0 */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x78, 	/*  [ **** ]  */
		0x84, 	/*  [*    *]  */
		0x04, 	/*  [     *]  */
		0x04, 	/*  [     *]  */
		0x08, 	/*  [    * ]  */
		0x30, 	/*  [  **  ]  */
		0x40, 	/*  [ *    ]  */
		0x80, 	/*  [*     ]  */
		0xFC, 	/*  [******]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		
		/* char: '3' hexcode: 0x0033 glyph_width: 7 black_width: 6 origin_x: 0 */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x78, 	/*  [ **** ]  */
		0x84, 	/*  [*    *]  */
		0x04, 	/*  [     *]  */
		0x04, 	/*  [     *]  */
		0x38, 	/*  [  *** ]  */
		0x04, 	/*  [     *]  */
		0x04, 	/*  [     *]  */
		0x84, 	/*  [*    *]  */
		0x78, 	/*  [ **** ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		
		/* char: '4' hexcode: 0x0034 glyph_width: 7 black_width: 6 origin_x: 0 */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x08, 	/*  [    * ]  */
		0x18, 	/*  [   ** ]  */
		0x28, 	/*  [  * * ]  */
		0x48, 	/*  [ *  * ]  */
		0x88, 	/*  [*   * ]  */
		0xFC, 	/*  [******]  */
		0x08, 	/*  [    * ]  */
		0x08, 	/*  [    * ]  */
		0x08, 	/*  [    * ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		
		/* char: '5' hexcode: 0x0035 glyph_width: 7 black_width: 6 origin_x: 0 */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0xFC, 	/*  [******]  */
		0x80, 	/*  [*     ]  */
		0x80, 	/*  [*     ]  */
		0xF8, 	/*  [***** ]  */
		0x04, 	/*  [     *]  */
		0x04, 	/*  [     *]  */
		0x04, 	/*  [     *]  */
		0x84, 	/*  [*    *]  */
		0x78, 	/*  [ **** ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		
		/* char: '6' hexcode: 0x0036 glyph_width: 7 black_width: 6 origin_x: 0 */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x38, 	/*  [  *** ]  */
		0x40, 	/*  [ *    ]  */
		0x80, 	/*  [*     ]  */
		0xF8, 	/*  [***** ]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0x78, 	/*  [ **** ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		
		/* char: '7' hexcode: 0x0037 glyph_width: 7 black_width: 6 origin_x: 0 */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0xFC, 	/*  [******]  */
		0x04, 	/*  [     *]  */
		0x08, 	/*  [    * ]  */
		0x08, 	/*  [    * ]  */
		0x10, 	/*  [   *  ]  */
		0x10, 	/*  [   *  ]  */
		0x20, 	/*  [  *   ]  */
		0x20, 	/*  [  *   ]  */
		0x40, 	/*  [ *    ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		
		/* char: '8' hexcode: 0x0038 glyph_width: 7 black_width: 6 origin_x: 0 */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x78, 	/*  [ **** ]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0x78, 	/*  [ **** ]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0x78, 	/*  [ **** ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		
		/* char: '9' hexcode: 0x0039 glyph_width: 7 black_width: 6 origin_x: 0 */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x78, 	/*  [ **** ]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0x7C, 	/*  [ *****]  */
		0x04, 	/*  [     *]  */
		0x08, 	/*  [    * ]  */
		0x70, 	/*  [ ***  ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		
		/* char: ':' hexcode: 0x003A glyph_width: 5 black_width: 1 origin_x: 2 */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x80, 	/*  [*]  */
		0x80, 	/*  [*]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x80, 	/*  [*]  */
		0x80, 	/*  [*]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		
		/* char: ';' hexcode: 0x003B glyph_width: 5 black_width: 2 origin_x: 1 */
		0x00, 	/*  [  ]  */
		0x00, 	/*  [  ]  */
		0x00, 	/*  [  ]  */
		0x00, 	/*  [  ]  */
		0x00, 	/*  [  ]  */
		0x00, 	/*  [  ]  */
		0x40, 	/*  [ *]  */
		0x40, 	/*  [ *]  */
		0x00, 	/*  [  ]  */
		0x00, 	/*  [  ]  */
		0x00, 	/*  [  ]  */
		0x40, 	/*  [ *]  */
		0x40, 	/*  [ *]  */
		0x40, 	/*  [ *]  */
		0x80, 	/*  [* ]  */
		0x00, 	/*  [  ]  */
		
		/* char: '<' hexcode: 0x003C glyph_width: 9 black_width: 7 origin_x: 1 */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x02, 	/*  [      *]  */
		0x0C, 	/*  [    ** ]  */
		0x30, 	/*  [  **   ]  */
		0xC0, 	/*  [**     ]  */
		0x30, 	/*  [  **   ]  */
		0x0C, 	/*  [    ** ]  */
		0x02, 	/*  [      *]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		
		/* char: '=' hexcode: 0x003D glyph_width: 9 black_width: 7 origin_x: 1 */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0xFE, 	/*  [*******]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0xFE, 	/*  [*******]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		
		/* char: '>' hexcode: 0x003E glyph_width: 9 black_width: 7 origin_x: 1 */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x80, 	/*  [*      ]  */
		0x60, 	/*  [ **    ]  */
		0x18, 	/*  [   **  ]  */
		0x06, 	/*  [     **]  */
		0x18, 	/*  [   **  ]  */
		0x60, 	/*  [ **    ]  */
		0x80, 	/*  [*      ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		
		/* char: '?' hexcode: 0x003F glyph_width: 6 black_width: 5 origin_x: 0 */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x70, 	/*  [ *** ]  */
		0x88, 	/*  [*   *]  */
		0x08, 	/*  [    *]  */
		0x10, 	/*  [   * ]  */
		0x20, 	/*  [  *  ]  */
		0x40, 	/*  [ *   ]  */
		0x00, 	/*  [     ]  */
		0x40, 	/*  [ *   ]  */
		0x40, 	/*  [ *   ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		
		/* char: '@' hexcode: 0x0040 glyph_width: 12 black_width: 11 origin_x: 0 */
		0x00, 0x00, 	/*  [           ]  */
		0x00, 0x00, 	/*  [           ]  */
		0x00, 0x00, 	/*  [           ]  */
		0x00, 0x00, 	/*  [           ]  */
		0x1F, 0x00, 	/*  [   *****   ]  */
		0x60, 0xC0, 	/*  [ **     ** ]  */
		0x4F, 0x40, 	/*  [ *  **** * ]  */
		0x91, 0x20, 	/*  [*  *   *  *]  */
		0x91, 0x20, 	/*  [*  *   *  *]  */
		0x91, 0x20, 	/*  [*  *   *  *]  */
		0x91, 0x20, 	/*  [*  *   *  *]  */
		0x4F, 0xC0, 	/*  [ *  ****** ]  */
		0x60, 0x00, 	/*  [ **        ]  */
		0x1F, 0x00, 	/*  [   *****   ]  */
		0x00, 0x00, 	/*  [           ]  */
		0x00, 0x00, 	/*  [           ]  */
		
		/* char: 'A' hexcode: 0x0041 glyph_width: 8 black_width: 7 origin_x: 0 */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x10, 	/*  [   *   ]  */
		0x10, 	/*  [   *   ]  */
		0x28, 	/*  [  * *  ]  */
		0x28, 	/*  [  * *  ]  */
		0x44, 	/*  [ *   * ]  */
		0x44, 	/*  [ *   * ]  */
		0x7C, 	/*  [ ***** ]  */
		0x82, 	/*  [*     *]  */
		0x82, 	/*  [*     *]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		
		/* char: 'B' hexcode: 0x0042 glyph_width: 7 black_width: 6 origin_x: 0 */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0xF0, 	/*  [****  ]  */
		0x88, 	/*  [*   * ]  */
		0x88, 	/*  [*   * ]  */
		0x88, 	/*  [*   * ]  */
		0xF8, 	/*  [***** ]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0xF8, 	/*  [***** ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		
		/* char: 'C' hexcode: 0x0043 glyph_width: 8 black_width: 7 origin_x: 0 */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x3C, 	/*  [  **** ]  */
		0x42, 	/*  [ *    *]  */
		0x80, 	/*  [*      ]  */
		0x80, 	/*  [*      ]  */
		0x80, 	/*  [*      ]  */
		0x80, 	/*  [*      ]  */
		0x80, 	/*  [*      ]  */
		0x42, 	/*  [ *    *]  */
		0x3C, 	/*  [  **** ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		
		/* char: 'D' hexcode: 0x0044 glyph_width: 8 black_width: 7 origin_x: 0 */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0xF8, 	/*  [*****  ]  */
		0x84, 	/*  [*    * ]  */
		0x82, 	/*  [*     *]  */
		0x82, 	/*  [*     *]  */
		0x82, 	/*  [*     *]  */
		0x82, 	/*  [*     *]  */
		0x82, 	/*  [*     *]  */
		0x84, 	/*  [*    * ]  */
		0xF8, 	/*  [*****  ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		
		/* char: 'E' hexcode: 0x0045 glyph_width: 7 black_width: 6 origin_x: 0 */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0xFC, 	/*  [******]  */
		0x80, 	/*  [*     ]  */
		0x80, 	/*  [*     ]  */
		0x80, 	/*  [*     ]  */
		0xFC, 	/*  [******]  */
		0x80, 	/*  [*     ]  */
		0x80, 	/*  [*     ]  */
		0x80, 	/*  [*     ]  */
		0xFC, 	/*  [******]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		
		/* char: 'F' hexcode: 0x0046 glyph_width: 7 black_width: 6 origin_x: 0 */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0xFC, 	/*  [******]  */
		0x80, 	/*  [*     ]  */
		0x80, 	/*  [*     ]  */
		0x80, 	/*  [*     ]  */
		0xFC, 	/*  [******]  */
		0x80, 	/*  [*     ]  */
		0x80, 	/*  [*     ]  */
		0x80, 	/*  [*     ]  */
		0x80, 	/*  [*     ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		
		/* char: 'G' hexcode: 0x0047 glyph_width: 8 black_width: 7 origin_x: 0 */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x3C, 	/*  [  **** ]  */
		0x42, 	/*  [ *    *]  */
		0x80, 	/*  [*      ]  */
		0x80, 	/*  [*      ]  */
		0x80, 	/*  [*      ]  */
		0x8E, 	/*  [*   ***]  */
		0x82, 	/*  [*     *]  */
		0x42, 	/*  [ *    *]  */
		0x3E, 	/*  [  *****]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		
		/* char: 'H' hexcode: 0x0048 glyph_width: 8 black_width: 7 origin_x: 0 */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x82, 	/*  [*     *]  */
		0x82, 	/*  [*     *]  */
		0x82, 	/*  [*     *]  */
		0x82, 	/*  [*     *]  */
		0xFE, 	/*  [*******]  */
		0x82, 	/*  [*     *]  */
		0x82, 	/*  [*     *]  */
		0x82, 	/*  [*     *]  */
		0x82, 	/*  [*     *]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		
		/* char: 'I' hexcode: 0x0049 glyph_width: 4 black_width: 3 origin_x: 0 */
		0x00, 	/*  [   ]  */
		0x00, 	/*  [   ]  */
		0x00, 	/*  [   ]  */
		0x00, 	/*  [   ]  */
		0xE0, 	/*  [***]  */
		0x40, 	/*  [ * ]  */
		0x40, 	/*  [ * ]  */
		0x40, 	/*  [ * ]  */
		0x40, 	/*  [ * ]  */
		0x40, 	/*  [ * ]  */
		0x40, 	/*  [ * ]  */
		0x40, 	/*  [ * ]  */
		0xE0, 	/*  [***]  */
		0x00, 	/*  [   ]  */
		0x00, 	/*  [   ]  */
		0x00, 	/*  [   ]  */
		
		/* char: 'J' hexcode: 0x004A glyph_width: 5 black_width: 4 origin_x: 0 */
		0x00, 	/*  [    ]  */
		0x00, 	/*  [    ]  */
		0x00, 	/*  [    ]  */
		0x00, 	/*  [    ]  */
		0x70, 	/*  [ ***]  */
		0x10, 	/*  [   *]  */
		0x10, 	/*  [   *]  */
		0x10, 	/*  [   *]  */
		0x10, 	/*  [   *]  */
		0x10, 	/*  [   *]  */
		0x10, 	/*  [   *]  */
		0x10, 	/*  [   *]  */
		0xE0, 	/*  [*** ]  */
		0x00, 	/*  [    ]  */
		0x00, 	/*  [    ]  */
		0x00, 	/*  [    ]  */
		
		/* char: 'K' hexcode: 0x004B glyph_width: 7 black_width: 6 origin_x: 0 */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x84, 	/*  [*    *]  */
		0x88, 	/*  [*   * ]  */
		0x90, 	/*  [*  *  ]  */
		0xA0, 	/*  [* *   ]  */
		0xC0, 	/*  [**    ]  */
		0xA0, 	/*  [* *   ]  */
		0x90, 	/*  [*  *  ]  */
		0x88, 	/*  [*   * ]  */
		0x84, 	/*  [*    *]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		
		/* char: 'L' hexcode: 0x004C glyph_width: 6 black_width: 5 origin_x: 0 */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x80, 	/*  [*    ]  */
		0x80, 	/*  [*    ]  */
		0x80, 	/*  [*    ]  */
		0x80, 	/*  [*    ]  */
		0x80, 	/*  [*    ]  */
		0x80, 	/*  [*    ]  */
		0x80, 	/*  [*    ]  */
		0x80, 	/*  [*    ]  */
		0xF8, 	/*  [*****]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		
		/* char: 'M' hexcode: 0x004D glyph_width: 10 black_width: 9 origin_x: 0 */
		0x00, 0x00, 	/*  [         ]  */
		0x00, 0x00, 	/*  [         ]  */
		0x00, 0x00, 	/*  [         ]  */
		0x00, 0x00, 	/*  [         ]  */
		0xC1, 0x80, 	/*  [**     **]  */
		0xC1, 0x80, 	/*  [**     **]  */
		0xA2, 0x80, 	/*  [* *   * *]  */
		0xA2, 0x80, 	/*  [* *   * *]  */
		0x94, 0x80, 	/*  [*  * *  *]  */
		0x94, 0x80, 	/*  [*  * *  *]  */
		0x88, 0x80, 	/*  [*   *   *]  */
		0x88, 0x80, 	/*  [*   *   *]  */
		0x80, 0x80, 	/*  [*       *]  */
		0x00, 0x00, 	/*  [         ]  */
		0x00, 0x00, 	/*  [         ]  */
		0x00, 0x00, 	/*  [         ]  */
		
		/* char: 'N' hexcode: 0x004E glyph_width: 8 black_width: 7 origin_x: 0 */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0xC2, 	/*  [**    *]  */
		0xC2, 	/*  [**    *]  */
		0xA2, 	/*  [* *   *]  */
		0xA2, 	/*  [* *   *]  */
		0x92, 	/*  [*  *  *]  */
		0x8A, 	/*  [*   * *]  */
		0x8A, 	/*  [*   * *]  */
		0x86, 	/*  [*    **]  */
		0x86, 	/*  [*    **]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		
		/* char: 'O' hexcode: 0x004F glyph_width: 9 black_width: 8 origin_x: 0 */
		0x00, 	/*  [        ]  */
		0x00, 	/*  [        ]  */
		0x00, 	/*  [        ]  */
		0x00, 	/*  [        ]  */
		0x3C, 	/*  [  ****  ]  */
		0x42, 	/*  [ *    * ]  */
		0x81, 	/*  [*      *]  */
		0x81, 	/*  [*      *]  */
		0x81, 	/*  [*      *]  */
		0x81, 	/*  [*      *]  */
		0x81, 	/*  [*      *]  */
		0x42, 	/*  [ *    * ]  */
		0x3C, 	/*  [  ****  ]  */
		0x00, 	/*  [        ]  */
		0x00, 	/*  [        ]  */
		0x00, 	/*  [        ]  */
		
		/* char: 'P' hexcode: 0x0050 glyph_width: 7 black_width: 6 origin_x: 0 */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0xF8, 	/*  [***** ]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0xF8, 	/*  [***** ]  */
		0x80, 	/*  [*     ]  */
		0x80, 	/*  [*     ]  */
		0x80, 	/*  [*     ]  */
		0x80, 	/*  [*     ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		
		/* char: 'Q' hexcode: 0x0051 glyph_width: 9 black_width: 8 origin_x: 0 */
		0x00, 	/*  [        ]  */
		0x00, 	/*  [        ]  */
		0x00, 	/*  [        ]  */
		0x00, 	/*  [        ]  */
		0x3C, 	/*  [  ****  ]  */
		0x42, 	/*  [ *    * ]  */
		0x81, 	/*  [*      *]  */
		0x81, 	/*  [*      *]  */
		0x81, 	/*  [*      *]  */
		0x81, 	/*  [*      *]  */
		0x81, 	/*  [*      *]  */
		0x42, 	/*  [ *    * ]  */
		0x3C, 	/*  [  ****  ]  */
		0x08, 	/*  [    *   ]  */
		0x07, 	/*  [     ***]  */
		0x00, 	/*  [        ]  */
		
		/* char: 'R' hexcode: 0x0052 glyph_width: 8 black_width: 7 origin_x: 0 */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0xF8, 	/*  [*****  ]  */
		0x84, 	/*  [*    * ]  */
		0x84, 	/*  [*    * ]  */
		0x84, 	/*  [*    * ]  */
		0xF8, 	/*  [*****  ]  */
		0x90, 	/*  [*  *   ]  */
		0x88, 	/*  [*   *  ]  */
		0x84, 	/*  [*    * ]  */
		0x82, 	/*  [*     *]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		
		/* char: 'S' hexcode: 0x0053 glyph_width: 8 black_width: 7 origin_x: 0 */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x7C, 	/*  [ ***** ]  */
		0x82, 	/*  [*     *]  */
		0x80, 	/*  [*      ]  */
		0x80, 	/*  [*      ]  */
		0x7C, 	/*  [ ***** ]  */
		0x02, 	/*  [      *]  */
		0x02, 	/*  [      *]  */
		0x82, 	/*  [*     *]  */
		0x7C, 	/*  [ ***** ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		
		/* char: 'T' hexcode: 0x0054 glyph_width: 8 black_width: 7 origin_x: 0 */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0xFE, 	/*  [*******]  */
		0x10, 	/*  [   *   ]  */
		0x10, 	/*  [   *   ]  */
		0x10, 	/*  [   *   ]  */
		0x10, 	/*  [   *   ]  */
		0x10, 	/*  [   *   ]  */
		0x10, 	/*  [   *   ]  */
		0x10, 	/*  [   *   ]  */
		0x10, 	/*  [   *   ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		
		/* char: 'U' hexcode: 0x0055 glyph_width: 8 black_width: 7 origin_x: 0 */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x82, 	/*  [*     *]  */
		0x82, 	/*  [*     *]  */
		0x82, 	/*  [*     *]  */
		0x82, 	/*  [*     *]  */
		0x82, 	/*  [*     *]  */
		0x82, 	/*  [*     *]  */
		0x82, 	/*  [*     *]  */
		0x44, 	/*  [ *   * ]  */
		0x38, 	/*  [  ***  ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		
		/* char: 'V' hexcode: 0x0056 glyph_width: 8 black_width: 9 origin_x: -1 */
		0x00, 0x00, 	/*  [         ]  */
		0x00, 0x00, 	/*  [         ]  */
		0x00, 0x00, 	/*  [         ]  */
		0x00, 0x00, 	/*  [         ]  */
		0x41, 0x00, 	/*  [ *     * ]  */
		0x41, 0x00, 	/*  [ *     * ]  */
		0x41, 0x00, 	/*  [ *     * ]  */
		0x22, 0x00, 	/*  [  *   *  ]  */
		0x22, 0x00, 	/*  [  *   *  ]  */
		0x14, 0x00, 	/*  [   * *   ]  */
		0x14, 0x00, 	/*  [   * *   ]  */
		0x08, 0x00, 	/*  [    *    ]  */
		0x08, 0x00, 	/*  [    *    ]  */
		0x00, 0x00, 	/*  [         ]  */
		0x00, 0x00, 	/*  [         ]  */
		0x00, 0x00, 	/*  [         ]  */
		
		/* char: 'W' hexcode: 0x0057 glyph_width: 12 black_width: 11 origin_x: 0 */
		0x00, 0x00, 	/*  [           ]  */
		0x00, 0x00, 	/*  [           ]  */
		0x00, 0x00, 	/*  [           ]  */
		0x00, 0x00, 	/*  [           ]  */
		0x84, 0x20, 	/*  [*    *    *]  */
		0x84, 0x20, 	/*  [*    *    *]  */
		0x8A, 0x20, 	/*  [*   * *   *]  */
		0x8A, 0x20, 	/*  [*   * *   *]  */
		0x4A, 0x40, 	/*  [ *  * *  * ]  */
		0x51, 0x40, 	/*  [ * *   * * ]  */
		0x51, 0x40, 	/*  [ * *   * * ]  */
		0x51, 0x40, 	/*  [ * *   * * ]  */
		0x20, 0x80, 	/*  [  *     *  ]  */
		0x00, 0x00, 	/*  [           ]  */
		0x00, 0x00, 	/*  [           ]  */
		0x00, 0x00, 	/*  [           ]  */
		
		/* char: 'X' hexcode: 0x0058 glyph_width: 8 black_width: 7 origin_x: 0 */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x82, 	/*  [*     *]  */
		0x44, 	/*  [ *   * ]  */
		0x28, 	/*  [  * *  ]  */
		0x28, 	/*  [  * *  ]  */
		0x10, 	/*  [   *   ]  */
		0x28, 	/*  [  * *  ]  */
		0x28, 	/*  [  * *  ]  */
		0x44, 	/*  [ *   * ]  */
		0x82, 	/*  [*     *]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		
		/* char: 'Y' hexcode: 0x0059 glyph_width: 7 black_width: 7 origin_x: 0 */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x82, 	/*  [*     *]  */
		0x44, 	/*  [ *   * ]  */
		0x44, 	/*  [ *   * ]  */
		0x28, 	/*  [  * *  ]  */
		0x10, 	/*  [   *   ]  */
		0x10, 	/*  [   *   ]  */
		0x10, 	/*  [   *   ]  */
		0x10, 	/*  [   *   ]  */
		0x10, 	/*  [   *   ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		
		/* char: 'Z' hexcode: 0x005A glyph_width: 7 black_width: 6 origin_x: 0 */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0xFC, 	/*  [******]  */
		0x04, 	/*  [     *]  */
		0x08, 	/*  [    * ]  */
		0x10, 	/*  [   *  ]  */
		0x20, 	/*  [  *   ]  */
		0x20, 	/*  [  *   ]  */
		0x40, 	/*  [ *    ]  */
		0x80, 	/*  [*     ]  */
		0xFC, 	/*  [******]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		
		/* char: '[' hexcode: 0x005B glyph_width: 5 black_width: 3 origin_x: 1 */
		0x00, 	/*  [   ]  */
		0x00, 	/*  [   ]  */
		0x00, 	/*  [   ]  */
		0xE0, 	/*  [***]  */
		0x80, 	/*  [*  ]  */
		0x80, 	/*  [*  ]  */
		0x80, 	/*  [*  ]  */
		0x80, 	/*  [*  ]  */
		0x80, 	/*  [*  ]  */
		0x80, 	/*  [*  ]  */
		0x80, 	/*  [*  ]  */
		0x80, 	/*  [*  ]  */
		0x80, 	/*  [*  ]  */
		0x80, 	/*  [*  ]  */
		0xE0, 	/*  [***]  */
		0x00, 	/*  [   ]  */
		
		/* char: '\' hexcode: 0x005C glyph_width: 5 black_width: 5 origin_x: 0 */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x80, 	/*  [*    ]  */
		0x80, 	/*  [*    ]  */
		0x40, 	/*  [ *   ]  */
		0x40, 	/*  [ *   ]  */
		0x40, 	/*  [ *   ]  */
		0x20, 	/*  [  *  ]  */
		0x20, 	/*  [  *  ]  */
		0x10, 	/*  [   * ]  */
		0x10, 	/*  [   * ]  */
		0x10, 	/*  [   * ]  */
		0x08, 	/*  [    *]  */
		0x08, 	/*  [    *]  */
		0x00, 	/*  [     ]  */
		
		/* char: ']' hexcode: 0x005D glyph_width: 5 black_width: 3 origin_x: 1 */
		0x00, 	/*  [   ]  */
		0x00, 	/*  [   ]  */
		0x00, 	/*  [   ]  */
		0xE0, 	/*  [***]  */
		0x20, 	/*  [  *]  */
		0x20, 	/*  [  *]  */
		0x20, 	/*  [  *]  */
		0x20, 	/*  [  *]  */
		0x20, 	/*  [  *]  */
		0x20, 	/*  [  *]  */
		0x20, 	/*  [  *]  */
		0x20, 	/*  [  *]  */
		0x20, 	/*  [  *]  */
		0x20, 	/*  [  *]  */
		0xE0, 	/*  [***]  */
		0x00, 	/*  [   ]  */
		
		/* char: '^' hexcode: 0x005E glyph_width: 9 black_width: 8 origin_x: 1 */
		0x00, 	/*  [        ]  */
		0x00, 	/*  [        ]  */
		0x00, 	/*  [        ]  */
		0x00, 	/*  [        ]  */
		0x18, 	/*  [   **   ]  */
		0x24, 	/*  [  *  *  ]  */
		0x42, 	/*  [ *    * ]  */
		0x81, 	/*  [*      *]  */
		0x00, 	/*  [        ]  */
		0x00, 	/*  [        ]  */
		0x00, 	/*  [        ]  */
		0x00, 	/*  [        ]  */
		0x00, 	/*  [        ]  */
		0x00, 	/*  [        ]  */
		0x00, 	/*  [        ]  */
		0x00, 	/*  [        ]  */
		
		/* char: '_' hexcode: 0x005F glyph_width: 7 black_width: 7 origin_x: 0 */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0xFE, 	/*  [*******]  */
		0x00, 	/*  [       ]  */
		
		/* char: '`' hexcode: 0x0060 glyph_width: 7 black_width: 3 origin_x: 2 */
		0x00, 	/*  [   ]  */
		0x00, 	/*  [   ]  */
		0x00, 	/*  [   ]  */
		0x40, 	/*  [ * ]  */
		0x20, 	/*  [  *]  */
		0x00, 	/*  [   ]  */
		0x00, 	/*  [   ]  */
		0x00, 	/*  [   ]  */
		0x00, 	/*  [   ]  */
		0x00, 	/*  [   ]  */
		0x00, 	/*  [   ]  */
		0x00, 	/*  [   ]  */
		0x00, 	/*  [   ]  */
		0x00, 	/*  [   ]  */
		0x00, 	/*  [   ]  */
		0x00, 	/*  [   ]  */
		
		/* char: 'a' hexcode: 0x0061 glyph_width: 7 black_width: 6 origin_x: 0 */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x78, 	/*  [ **** ]  */
		0x04, 	/*  [     *]  */
		0x04, 	/*  [     *]  */
		0x7C, 	/*  [ *****]  */
		0x84, 	/*  [*    *]  */
		0x8C, 	/*  [*   **]  */
		0x74, 	/*  [ *** *]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		
		/* char: 'b' hexcode: 0x0062 glyph_width: 7 black_width: 6 origin_x: 0 */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x80, 	/*  [*     ]  */
		0x80, 	/*  [*     ]  */
		0x80, 	/*  [*     ]  */
		0xB8, 	/*  [* *** ]  */
		0xC4, 	/*  [**   *]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0xF8, 	/*  [***** ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		
		/* char: 'c' hexcode: 0x0063 glyph_width: 6 black_width: 5 origin_x: 0 */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x78, 	/*  [ ****]  */
		0x80, 	/*  [*    ]  */
		0x80, 	/*  [*    ]  */
		0x80, 	/*  [*    ]  */
		0x80, 	/*  [*    ]  */
		0x80, 	/*  [*    ]  */
		0x78, 	/*  [ ****]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		
		/* char: 'd' hexcode: 0x0064 glyph_width: 7 black_width: 6 origin_x: 0 */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x04, 	/*  [     *]  */
		0x04, 	/*  [     *]  */
		0x04, 	/*  [     *]  */
		0x7C, 	/*  [ *****]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0x8C, 	/*  [*   **]  */
		0x74, 	/*  [ *** *]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		
		/* char: 'e' hexcode: 0x0065 glyph_width: 7 black_width: 6 origin_x: 0 */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x78, 	/*  [ **** ]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0xFC, 	/*  [******]  */
		0x80, 	/*  [*     ]  */
		0x84, 	/*  [*    *]  */
		0x78, 	/*  [ **** ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		
		/* char: 'f' hexcode: 0x0066 glyph_width: 4 black_width: 5 origin_x: 0 */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x38, 	/*  [  ***]  */
		0x40, 	/*  [ *   ]  */
		0x40, 	/*  [ *   ]  */
		0xF0, 	/*  [**** ]  */
		0x40, 	/*  [ *   ]  */
		0x40, 	/*  [ *   ]  */
		0x40, 	/*  [ *   ]  */
		0x40, 	/*  [ *   ]  */
		0x40, 	/*  [ *   ]  */
		0x40, 	/*  [ *   ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		
		/* char: 'g' hexcode: 0x0067 glyph_width: 7 black_width: 6 origin_x: 0 */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x7C, 	/*  [ *****]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0x8C, 	/*  [*   **]  */
		0x74, 	/*  [ *** *]  */
		0x04, 	/*  [     *]  */
		0x04, 	/*  [     *]  */
		0x78, 	/*  [ **** ]  */
		
		/* char: 'h' hexcode: 0x0068 glyph_width: 7 black_width: 6 origin_x: 0 */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x80, 	/*  [*     ]  */
		0x80, 	/*  [*     ]  */
		0x80, 	/*  [*     ]  */
		0xB8, 	/*  [* *** ]  */
		0xC4, 	/*  [**   *]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		
		/* char: 'i' hexcode: 0x0069 glyph_width: 3 black_width: 1 origin_x: 1 */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x80, 	/*  [*]  */
		0x00, 	/*  [ ]  */
		0x80, 	/*  [*]  */
		0x80, 	/*  [*]  */
		0x80, 	/*  [*]  */
		0x80, 	/*  [*]  */
		0x80, 	/*  [*]  */
		0x80, 	/*  [*]  */
		0x80, 	/*  [*]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		
		/* char: 'j' hexcode: 0x006A glyph_width: 4 black_width: 3 origin_x: 0 */
		0x00, 	/*  [   ]  */
		0x00, 	/*  [   ]  */
		0x00, 	/*  [   ]  */
		0x00, 	/*  [   ]  */
		0x20, 	/*  [  *]  */
		0x00, 	/*  [   ]  */
		0x60, 	/*  [ **]  */
		0x20, 	/*  [  *]  */
		0x20, 	/*  [  *]  */
		0x20, 	/*  [  *]  */
		0x20, 	/*  [  *]  */
		0x20, 	/*  [  *]  */
		0x20, 	/*  [  *]  */
		0x20, 	/*  [  *]  */
		0x20, 	/*  [  *]  */
		0xC0, 	/*  [** ]  */
		
		/* char: 'k' hexcode: 0x006B glyph_width: 6 black_width: 6 origin_x: 0 */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x80, 	/*  [*     ]  */
		0x80, 	/*  [*     ]  */
		0x80, 	/*  [*     ]  */
		0x88, 	/*  [*   * ]  */
		0x90, 	/*  [*  *  ]  */
		0xA0, 	/*  [* *   ]  */
		0xC0, 	/*  [**    ]  */
		0xA0, 	/*  [* *   ]  */
		0x90, 	/*  [*  *  ]  */
		0x88, 	/*  [*   * ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		
		/* char: 'l' hexcode: 0x006C glyph_width: 3 black_width: 1 origin_x: 1 */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x80, 	/*  [*]  */
		0x80, 	/*  [*]  */
		0x80, 	/*  [*]  */
		0x80, 	/*  [*]  */
		0x80, 	/*  [*]  */
		0x80, 	/*  [*]  */
		0x80, 	/*  [*]  */
		0x80, 	/*  [*]  */
		0x80, 	/*  [*]  */
		0x80, 	/*  [*]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		
		/* char: 'm' hexcode: 0x006D glyph_width: 11 black_width: 9 origin_x: 1 */
		0x00, 0x00, 	/*  [         ]  */
		0x00, 0x00, 	/*  [         ]  */
		0x00, 0x00, 	/*  [         ]  */
		0x00, 0x00, 	/*  [         ]  */
		0x00, 0x00, 	/*  [         ]  */
		0x00, 0x00, 	/*  [         ]  */
		0xB3, 0x00, 	/*  [* **  ** ]  */
		0xCC, 0x80, 	/*  [**  **  *]  */
		0x88, 0x80, 	/*  [*   *   *]  */
		0x88, 0x80, 	/*  [*   *   *]  */
		0x88, 0x80, 	/*  [*   *   *]  */
		0x88, 0x80, 	/*  [*   *   *]  */
		0x88, 0x80, 	/*  [*   *   *]  */
		0x00, 0x00, 	/*  [         ]  */
		0x00, 0x00, 	/*  [         ]  */
		0x00, 0x00, 	/*  [         ]  */
		
		/* char: 'n' hexcode: 0x006E glyph_width: 7 black_width: 6 origin_x: 0 */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0xB8, 	/*  [* *** ]  */
		0xC4, 	/*  [**   *]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		
		/* char: 'o' hexcode: 0x006F glyph_width: 7 black_width: 6 origin_x: 0 */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x78, 	/*  [ **** ]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0x78, 	/*  [ **** ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		
		/* char: 'p' hexcode: 0x0070 glyph_width: 7 black_width: 6 origin_x: 0 */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0xB8, 	/*  [* *** ]  */
		0xC4, 	/*  [**   *]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0xF8, 	/*  [***** ]  */
		0x80, 	/*  [*     ]  */
		0x80, 	/*  [*     ]  */
		0x80, 	/*  [*     ]  */
		
		/* char: 'q' hexcode: 0x0071 glyph_width: 7 black_width: 6 origin_x: 0 */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x7C, 	/*  [ *****]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0x8C, 	/*  [*   **]  */
		0x74, 	/*  [ *** *]  */
		0x04, 	/*  [     *]  */
		0x04, 	/*  [     *]  */
		0x04, 	/*  [     *]  */
		
		/* char: 'r' hexcode: 0x0072 glyph_width: 5 black_width: 4 origin_x: 0 */
		0x00, 	/*  [    ]  */
		0x00, 	/*  [    ]  */
		0x00, 	/*  [    ]  */
		0x00, 	/*  [    ]  */
		0x00, 	/*  [    ]  */
		0x00, 	/*  [    ]  */
		0xB0, 	/*  [* **]  */
		0xC0, 	/*  [**  ]  */
		0x80, 	/*  [*   ]  */
		0x80, 	/*  [*   ]  */
		0x80, 	/*  [*   ]  */
		0x80, 	/*  [*   ]  */
		0x80, 	/*  [*   ]  */
		0x00, 	/*  [    ]  */
		0x00, 	/*  [    ]  */
		0x00, 	/*  [    ]  */
		
		/* char: 's' hexcode: 0x0073 glyph_width: 6 black_width: 5 origin_x: 0 */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x70, 	/*  [ *** ]  */
		0x88, 	/*  [*   *]  */
		0x80, 	/*  [*    ]  */
		0x70, 	/*  [ *** ]  */
		0x08, 	/*  [    *]  */
		0x88, 	/*  [*   *]  */
		0x70, 	/*  [ *** ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		
		/* char: 't' hexcode: 0x0074 glyph_width: 4 black_width: 4 origin_x: 0 */
		0x00, 	/*  [    ]  */
		0x00, 	/*  [    ]  */
		0x00, 	/*  [    ]  */
		0x00, 	/*  [    ]  */
		0x40, 	/*  [ *  ]  */
		0x40, 	/*  [ *  ]  */
		0xF0, 	/*  [****]  */
		0x40, 	/*  [ *  ]  */
		0x40, 	/*  [ *  ]  */
		0x40, 	/*  [ *  ]  */
		0x40, 	/*  [ *  ]  */
		0x40, 	/*  [ *  ]  */
		0x30, 	/*  [  **]  */
		0x00, 	/*  [    ]  */
		0x00, 	/*  [    ]  */
		0x00, 	/*  [    ]  */
		
		/* char: 'u' hexcode: 0x0075 glyph_width: 7 black_width: 6 origin_x: 0 */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0x84, 	/*  [*    *]  */
		0x8C, 	/*  [*   **]  */
		0x74, 	/*  [ *** *]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		0x00, 	/*  [      ]  */
		
		/* char: 'v' hexcode: 0x0076 glyph_width: 6 black_width: 5 origin_x: 0 */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x88, 	/*  [*   *]  */
		0x88, 	/*  [*   *]  */
		0x50, 	/*  [ * * ]  */
		0x50, 	/*  [ * * ]  */
		0x50, 	/*  [ * * ]  */
		0x20, 	/*  [  *  ]  */
		0x20, 	/*  [  *  ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		
		/* char: 'w' hexcode: 0x0077 glyph_width: 10 black_width: 9 origin_x: 0 */
		0x00, 0x00, 	/*  [         ]  */
		0x00, 0x00, 	/*  [         ]  */
		0x00, 0x00, 	/*  [         ]  */
		0x00, 0x00, 	/*  [         ]  */
		0x00, 0x00, 	/*  [         ]  */
		0x00, 0x00, 	/*  [         ]  */
		0x88, 0x80, 	/*  [*   *   *]  */
		0x88, 0x80, 	/*  [*   *   *]  */
		0x55, 0x00, 	/*  [ * * * * ]  */
		0x55, 0x00, 	/*  [ * * * * ]  */
		0x55, 0x00, 	/*  [ * * * * ]  */
		0x22, 0x00, 	/*  [  *   *  ]  */
		0x22, 0x00, 	/*  [  *   *  ]  */
		0x00, 0x00, 	/*  [         ]  */
		0x00, 0x00, 	/*  [         ]  */
		0x00, 0x00, 	/*  [         ]  */
		
		/* char: 'x' hexcode: 0x0078 glyph_width: 6 black_width: 5 origin_x: 0 */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x88, 	/*  [*   *]  */
		0x50, 	/*  [ * * ]  */
		0x50, 	/*  [ * * ]  */
		0x20, 	/*  [  *  ]  */
		0x50, 	/*  [ * * ]  */
		0x50, 	/*  [ * * ]  */
		0x88, 	/*  [*   *]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		
		/* char: 'y' hexcode: 0x0079 glyph_width: 6 black_width: 5 origin_x: 0 */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x88, 	/*  [*   *]  */
		0x88, 	/*  [*   *]  */
		0x50, 	/*  [ * * ]  */
		0x50, 	/*  [ * * ]  */
		0x50, 	/*  [ * * ]  */
		0x20, 	/*  [  *  ]  */
		0x20, 	/*  [  *  ]  */
		0x20, 	/*  [  *  ]  */
		0x40, 	/*  [ *   ]  */
		0x40, 	/*  [ *   ]  */
		
		/* char: 'z' hexcode: 0x007A glyph_width: 6 black_width: 5 origin_x: 0 */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0xF8, 	/*  [*****]  */
		0x08, 	/*  [    *]  */
		0x10, 	/*  [   * ]  */
		0x20, 	/*  [  *  ]  */
		0x40, 	/*  [ *   ]  */
		0x80, 	/*  [*    ]  */
		0xF8, 	/*  [*****]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		
		/* char: '{' hexcode: 0x007B glyph_width: 6 black_width: 5 origin_x: 0 */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x18, 	/*  [   **]  */
		0x20, 	/*  [  *  ]  */
		0x20, 	/*  [  *  ]  */
		0x20, 	/*  [  *  ]  */
		0x20, 	/*  [  *  ]  */
		0x20, 	/*  [  *  ]  */
		0xC0, 	/*  [**   ]  */
		0x20, 	/*  [  *  ]  */
		0x20, 	/*  [  *  ]  */
		0x20, 	/*  [  *  ]  */
		0x20, 	/*  [  *  ]  */
		0x18, 	/*  [   **]  */
		0x00, 	/*  [     ]  */
		
		/* char: '|' hexcode: 0x007C glyph_width: 6 black_width: 1 origin_x: 2 */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x00, 	/*  [ ]  */
		0x80, 	/*  [*]  */
		0x80, 	/*  [*]  */
		0x80, 	/*  [*]  */
		0x80, 	/*  [*]  */
		0x80, 	/*  [*]  */
		0x80, 	/*  [*]  */
		0x80, 	/*  [*]  */
		0x80, 	/*  [*]  */
		0x80, 	/*  [*]  */
		0x80, 	/*  [*]  */
		0x80, 	/*  [*]  */
		0x80, 	/*  [*]  */
		0x00, 	/*  [ ]  */
		
		/* char: '}' hexcode: 0x007D glyph_width: 6 black_width: 5 origin_x: 0 */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0xC0, 	/*  [**   ]  */
		0x20, 	/*  [  *  ]  */
		0x20, 	/*  [  *  ]  */
		0x20, 	/*  [  *  ]  */
		0x20, 	/*  [  *  ]  */
		0x20, 	/*  [  *  ]  */
		0x18, 	/*  [   **]  */
		0x20, 	/*  [  *  ]  */
		0x20, 	/*  [  *  ]  */
		0x20, 	/*  [  *  ]  */
		0x20, 	/*  [  *  ]  */
		0xC0, 	/*  [**   ]  */
		0x00, 	/*  [     ]  */
		
		/* char: '�' hexcode: 0x00B0 glyph_width: 6 black_width: 5 origin_x: 0 */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x70, 	/*  [ *** ]  */
		0x88, 	/*  [*   *]  */
		0x88, 	/*  [*   *]  */
		0x88, 	/*  [*   *]  */
		0x70, 	/*  [ *** ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		0x00, 	/*  [     ]  */
		
		/* char: '�' hexcode: 0x00B1 glyph_width: 8 black_width: 7 origin_x: 0 */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x10, 	/*  [   *   ]  */
		0x10, 	/*  [   *   ]  */
		0x10, 	/*  [   *   ]  */
		0xFE, 	/*  [*******]  */
		0x10, 	/*  [   *   ]  */
		0x10, 	/*  [   *   ]  */
		0x10, 	/*  [   *   ]  */
		0xFE, 	/*  [*******]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		0x00, 	/*  [       ]  */
		
};


/* Following is the array holding the width of each glyph's black area. 
   While the width of the black area is generally less than the width of the 
   glyphs, it can be greater than it also. Glyph for char 'f' (Time New Roman Italic) 
   is such a case. In the compact horizontal mode, only the black area is 
   dumped to the font definition file. 
 */
const fuint8 font_Tahoma_10_n_nnnn_0_nh_black_width_table[] = {
/*		black_width     char  hexcode*/
/*		===========     ====  =======*/
		  1,          /* ' '  0x0020 */
		  1,          /* '!'  0x0021 */
		  3,          /* '"'  0x0022 */
		  7,          /* '#'  0x0023 */
		  6,          /* '$'  0x0024 */
		 10,          /* '%'  0x0025 */
		  9,          /* '&'  0x0026 */
		  1,          /* '''  0x0027 */
		  4,          /* '('  0x0028 */
		  4,          /* ')'  0x0029 */
		  5,          /* '*'  0x002A */
		  7,          /* '+'  0x002B */
		  3,          /* ','  0x002C */
		  4,          /* '-'  0x002D */
		  1,          /* '.'  0x002E */
		  5,          /* '/'  0x002F */
		  6,          /* '0'  0x0030 */
		  5,          /* '1'  0x0031 */
		  6,          /* '2'  0x0032 */
		  6,          /* '3'  0x0033 */
		  6,          /* '4'  0x0034 */
		  6,          /* '5'  0x0035 */
		  6,          /* '6'  0x0036 */
		  6,          /* '7'  0x0037 */
		  6,          /* '8'  0x0038 */
		  6,          /* '9'  0x0039 */
		  1,          /* ':'  0x003A */
		  2,          /* ';'  0x003B */
		  7,          /* '<'  0x003C */
		  7,          /* '='  0x003D */
		  7,          /* '>'  0x003E */
		  5,          /* '?'  0x003F */
		 11,          /* '@'  0x0040 */
		  7,          /* 'A'  0x0041 */
		  6,          /* 'B'  0x0042 */
		  7,          /* 'C'  0x0043 */
		  7,          /* 'D'  0x0044 */
		  6,          /* 'E'  0x0045 */
		  6,          /* 'F'  0x0046 */
		  7,          /* 'G'  0x0047 */
		  7,          /* 'H'  0x0048 */
		  3,          /* 'I'  0x0049 */
		  4,          /* 'J'  0x004A */
		  6,          /* 'K'  0x004B */
		  5,          /* 'L'  0x004C */
		  9,          /* 'M'  0x004D */
		  7,          /* 'N'  0x004E */
		  8,          /* 'O'  0x004F */
		  6,          /* 'P'  0x0050 */
		  8,          /* 'Q'  0x0051 */
		  7,          /* 'R'  0x0052 */
		  7,          /* 'S'  0x0053 */
		  7,          /* 'T'  0x0054 */
		  7,          /* 'U'  0x0055 */
		  9,          /* 'V'  0x0056 */
		 11,          /* 'W'  0x0057 */
		  7,          /* 'X'  0x0058 */
		  7,          /* 'Y'  0x0059 */
		  6,          /* 'Z'  0x005A */
		  3,          /* '['  0x005B */
		  5,          /* '\'  0x005C */
		  3,          /* ']'  0x005D */
		  8,          /* '^'  0x005E */
		  7,          /* '_'  0x005F */
		  3,          /* '`'  0x0060 */
		  6,          /* 'a'  0x0061 */
		  6,          /* 'b'  0x0062 */
		  5,          /* 'c'  0x0063 */
		  6,          /* 'd'  0x0064 */
		  6,          /* 'e'  0x0065 */
		  5,          /* 'f'  0x0066 */
		  6,          /* 'g'  0x0067 */
		  6,          /* 'h'  0x0068 */
		  1,          /* 'i'  0x0069 */
		  3,          /* 'j'  0x006A */
		  6,          /* 'k'  0x006B */
		  1,          /* 'l'  0x006C */
		  9,          /* 'm'  0x006D */
		  6,          /* 'n'  0x006E */
		  6,          /* 'o'  0x006F */
		  6,          /* 'p'  0x0070 */
		  6,          /* 'q'  0x0071 */
		  4,          /* 'r'  0x0072 */
		  5,          /* 's'  0x0073 */
		  4,          /* 't'  0x0074 */
		  6,          /* 'u'  0x0075 */
		  5,          /* 'v'  0x0076 */
		  9,          /* 'w'  0x0077 */
		  5,          /* 'x'  0x0078 */
		  5,          /* 'y'  0x0079 */
		  5,          /* 'z'  0x007A */
		  5,          /* '{'  0x007B */
		  1,          /* '|'  0x007C */
		  5,          /* '}'  0x007D */
		  5,          /* '�'  0x00B0 */
		  7,          /* '�'  0x00B1 */
};


/* Following is the array holding the X part of the origin point (top-left) for 
   the black area of the glyph. While this value is positive in general 
   (meaning that we have empty columns at the left of the glyph), it can be 
   negative for some cases. This is called as overhang. The overhang is 
   the part of the ink of a glyph that extends beyond the advance width of 
   the glyph. Most glyphs (such as 'H') have no overhang, as there is a 
   little white space on either side to separate them from adjacent glyphs. 
   An example of a glyph with overhang is the italic 'f' for Times New Roman.
   
   Another example for overhang is some non-latin language glyphs like Devanagari. 
   For Devanagari, some glyphs (like 0x0941) are printed above or below of 
   the previous glpyh printed, which means they have 0 advance width at all. 
 */
const fint8 font_Tahoma_10_n_nnnn_0_nh_origin_x_table[] = {
/*		origin_x     char  hexcode*/
/*		========     ====  =======*/
		  0,       /* ' '  0x0020 */
		  1,       /* '!'  0x0021 */
		  1,       /* '"'  0x0022 */
		  1,       /* '#'  0x0023 */
		  0,       /* '$'  0x0024 */
		  1,       /* '%'  0x0025 */
		  0,       /* '&'  0x0026 */
		  1,       /* '''  0x0027 */
		  1,       /* '('  0x0028 */
		  0,       /* ')'  0x0029 */
		  1,       /* '*'  0x002A */
		  0,       /* '+'  0x002B */
		  0,       /* ','  0x002C */
		  0,       /* '-'  0x002D */
		  1,       /* '.'  0x002E */
		  0,       /* '/'  0x002F */
		  0,       /* '0'  0x0030 */
		  1,       /* '1'  0x0031 */
		  0,       /* '2'  0x0032 */
		  0,       /* '3'  0x0033 */
		  0,       /* '4'  0x0034 */
		  0,       /* '5'  0x0035 */
		  0,       /* '6'  0x0036 */
		  0,       /* '7'  0x0037 */
		  0,       /* '8'  0x0038 */
		  0,       /* '9'  0x0039 */
		  2,       /* ':'  0x003A */
		  1,       /* ';'  0x003B */
		  1,       /* '<'  0x003C */
		  1,       /* '='  0x003D */
		  1,       /* '>'  0x003E */
		  0,       /* '?'  0x003F */
		  0,       /* '@'  0x0040 */
		  0,       /* 'A'  0x0041 */
		  0,       /* 'B'  0x0042 */
		  0,       /* 'C'  0x0043 */
		  0,       /* 'D'  0x0044 */
		  0,       /* 'E'  0x0045 */
		  0,       /* 'F'  0x0046 */
		  0,       /* 'G'  0x0047 */
		  0,       /* 'H'  0x0048 */
		  0,       /* 'I'  0x0049 */
		  0,       /* 'J'  0x004A */
		  0,       /* 'K'  0x004B */
		  0,       /* 'L'  0x004C */
		  0,       /* 'M'  0x004D */
		  0,       /* 'N'  0x004E */
		  0,       /* 'O'  0x004F */
		  0,       /* 'P'  0x0050 */
		  0,       /* 'Q'  0x0051 */
		  0,       /* 'R'  0x0052 */
		  0,       /* 'S'  0x0053 */
		  0,       /* 'T'  0x0054 */
		  0,       /* 'U'  0x0055 */
		 -1,       /* 'V'  0x0056 */
		  0,       /* 'W'  0x0057 */
		  0,       /* 'X'  0x0058 */
		  0,       /* 'Y'  0x0059 */
		  0,       /* 'Z'  0x005A */
		  1,       /* '['  0x005B */
		  0,       /* '\'  0x005C */
		  1,       /* ']'  0x005D */
		  1,       /* '^'  0x005E */
		  0,       /* '_'  0x005F */
		  2,       /* '`'  0x0060 */
		  0,       /* 'a'  0x0061 */
		  0,       /* 'b'  0x0062 */
		  0,       /* 'c'  0x0063 */
		  0,       /* 'd'  0x0064 */
		  0,       /* 'e'  0x0065 */
		  0,       /* 'f'  0x0066 */
		  0,       /* 'g'  0x0067 */
		  0,       /* 'h'  0x0068 */
		  1,       /* 'i'  0x0069 */
		  0,       /* 'j'  0x006A */
		  0,       /* 'k'  0x006B */
		  1,       /* 'l'  0x006C */
		  1,       /* 'm'  0x006D */
		  0,       /* 'n'  0x006E */
		  0,       /* 'o'  0x006F */
		  0,       /* 'p'  0x0070 */
		  0,       /* 'q'  0x0071 */
		  0,       /* 'r'  0x0072 */
		  0,       /* 's'  0x0073 */
		  0,       /* 't'  0x0074 */
		  0,       /* 'u'  0x0075 */
		  0,       /* 'v'  0x0076 */
		  0,       /* 'w'  0x0077 */
		  0,       /* 'x'  0x0078 */
		  0,       /* 'y'  0x0079 */
		  0,       /* 'z'  0x007A */
		  0,       /* '{'  0x007B */
		  2,       /* '|'  0x007C */
		  0,       /* '}'  0x007D */
		  0,       /* '�'  0x00B0 */
		  0,       /* '�'  0x00B1 */
};


#ifdef FONTGEN_USE_PRECALCULATED_OFFSETS
/* Following array provides the starting offset of each glyph in the 
   font_Tahoma_10_n_nnnn_0_nh_glyph_table[].
   
   These offsets can be calculated by code on the micro, but it will require
   some realtime. Using precalculated offsets will work faster, but will require
   more code space.
   
   If you prefer to reduce code size, undefine FONTGEN_USE_PRECALCULATED_OFFSETS.
   If you prefer the code to work faster, define FONTGEN_USE_PRECALCULATED_OFFSETS.
   
   You should index this array with the index of the char in your character set.
   This can be calculated with a simple mathematical expression if you have such
   a simple expression, or you can use the mapping table for this purpose.
   
   To find the starting offset of the glyph in font_Tahoma_10_n_nnnn_0_nh_glyph_table[],
   use the following expression:
   	font_Tahoma_10_n_nnnn_0_nh_glyph_table[font_Tahoma_10_n_nnnn_0_nh_offset_table[c]]
   where 'c' is the variable holding the character you're interested in
 */
const fuint16 font_Tahoma_10_n_nnnn_0_nh_offset_table[] = {
/*		offset  char hexcode*/
/*		======  ==== =======*/
		   0, /* ' ' 0x0020 */
		  16, /* '!' 0x0021 */
		  32, /* '"' 0x0022 */
		  48, /* '#' 0x0023 */
		  64, /* '$' 0x0024 */
		  80, /* '%' 0x0025 */
		 112, /* '&' 0x0026 */
		 144, /* ''' 0x0027 */
		 160, /* '(' 0x0028 */
		 176, /* ')' 0x0029 */
		 192, /* '*' 0x002A */
		 208, /* '+' 0x002B */
		 224, /* ',' 0x002C */
		 240, /* '-' 0x002D */
		 256, /* '.' 0x002E */
		 272, /* '/' 0x002F */
		 288, /* '0' 0x0030 */
		 304, /* '1' 0x0031 */
		 320, /* '2' 0x0032 */
		 336, /* '3' 0x0033 */
		 352, /* '4' 0x0034 */
		 368, /* '5' 0x0035 */
		 384, /* '6' 0x0036 */
		 400, /* '7' 0x0037 */
		 416, /* '8' 0x0038 */
		 432, /* '9' 0x0039 */
		 448, /* ':' 0x003A */
		 464, /* ';' 0x003B */
		 480, /* '<' 0x003C */
		 496, /* '=' 0x003D */
		 512, /* '>' 0x003E */
		 528, /* '?' 0x003F */
		 544, /* '@' 0x0040 */
		 576, /* 'A' 0x0041 */
		 592, /* 'B' 0x0042 */
		 608, /* 'C' 0x0043 */
		 624, /* 'D' 0x0044 */
		 640, /* 'E' 0x0045 */
		 656, /* 'F' 0x0046 */
		 672, /* 'G' 0x0047 */
		 688, /* 'H' 0x0048 */
		 704, /* 'I' 0x0049 */
		 720, /* 'J' 0x004A */
		 736, /* 'K' 0x004B */
		 752, /* 'L' 0x004C */
		 768, /* 'M' 0x004D */
		 800, /* 'N' 0x004E */
		 816, /* 'O' 0x004F */
		 832, /* 'P' 0x0050 */
		 848, /* 'Q' 0x0051 */
		 864, /* 'R' 0x0052 */
		 880, /* 'S' 0x0053 */
		 896, /* 'T' 0x0054 */
		 912, /* 'U' 0x0055 */
		 928, /* 'V' 0x0056 */
		 960, /* 'W' 0x0057 */
		 992, /* 'X' 0x0058 */
		1008, /* 'Y' 0x0059 */
		1024, /* 'Z' 0x005A */
		1040, /* '[' 0x005B */
		1056, /* '\' 0x005C */
		1072, /* ']' 0x005D */
		1088, /* '^' 0x005E */
		1104, /* '_' 0x005F */
		1120, /* '`' 0x0060 */
		1136, /* 'a' 0x0061 */
		1152, /* 'b' 0x0062 */
		1168, /* 'c' 0x0063 */
		1184, /* 'd' 0x0064 */
		1200, /* 'e' 0x0065 */
		1216, /* 'f' 0x0066 */
		1232, /* 'g' 0x0067 */
		1248, /* 'h' 0x0068 */
		1264, /* 'i' 0x0069 */
		1280, /* 'j' 0x006A */
		1296, /* 'k' 0x006B */
		1312, /* 'l' 0x006C */
		1328, /* 'm' 0x006D */
		1360, /* 'n' 0x006E */
		1376, /* 'o' 0x006F */
		1392, /* 'p' 0x0070 */
		1408, /* 'q' 0x0071 */
		1424, /* 'r' 0x0072 */
		1440, /* 's' 0x0073 */
		1456, /* 't' 0x0074 */
		1472, /* 'u' 0x0075 */
		1488, /* 'v' 0x0076 */
		1504, /* 'w' 0x0077 */
		1536, /* 'x' 0x0078 */
		1552, /* 'y' 0x0079 */
		1568, /* 'z' 0x007A */
		1584, /* '{' 0x007B */
		1600, /* '|' 0x007C */
		1616, /* '}' 0x007D */
		1632, /* '�' 0x00B0 */
		1648, /* '�' 0x00B1 */
};
#endif


#ifdef FONTGEN_USE_MAPPING_TABLE
/* Following array provides the mapping for the characters in the ASCII 
   character set to your character set.
   
   Consider you've selected characters A-Z, 0-9 to produce the font definition for.
   With this selection, in the offset, detail and width tables, the first entry 
   will be for the character 'A', since it is your first char. And the 26. entry
   will be for the char '0'.
   
   In the micro, you'll need to address these tables at run time; therefore you'll
   need the mapping of ASCII character set to your character set. If you can find
   a simple mathematical expression for this mapping, you can use that. For the
   above character set, you can use the following mathematical expression for
   this mapping:
   	offset(c): (c>'A')?(c-'A'):(c-'0'+'Z'-'A'+1)
   
   If you do not have such a mathematical expression of you do not want to get tied
   to such an expression, you can use the following mapping table.
   
   This table is indexed with the ASCII character set, and returns the index 
   for your character set. If you do not have the given ASCII char in your charset
   it will return 0 always. This means that if you try to print a char 
   which you have not prepared the font for, you'll print the first char in your
   charset.
   
   If you want to find the offset for char 'A', use the following code:
   	font_Tahoma_10_n_nnnn_0_nh_offset_table[font_Tahoma_10_n_nnnn_0_nh_mapping_table['A']]
   
   If you do not want to use this mapping table, undefine FONTGEN_USE_MAPPING_TABLE
   to reduce the code size
   
   If you're generating multiple font definition files for the same character set
   to use in the same project, a single mapping file is adequate for all those
   definition files. You can remove all others to save space, but you need to
   update the other font definition files to point to the only one mapping table.
   

   Note for unicode version:
   =========================
      If you're generating font definition for the characters from a single
      code page, you can use the mapping table as following:
         font_Tahoma_10_n_nnnn_0_nh_offset_table[font_Tahoma_10_n_nnnn_0_nh_mapping_table[unicode_glpyh & 0x00FF]]
      
      If you're generating font definition for the glpyhs from different code
      pages, there is a risk of collision in the mapping table. Consider that
      you're using chars 0x0612 and 0x0712. Both of these glpyhs would map to
      slot 0x12.
      
      If you're generating font definition for more than 256 glpyhs, extend the
      mapping table by hand.
      
      If there is a risk of collision because of using glyphs from different
      code pages, check the mapping table manually to fix the collision.
      
      If you do not want to make manual changes, you can use the 
      font_Tahoma_10_n_nnnn_0_nh_extended_mapping table below.
 */
const fuint8 font_Tahoma_10_n_nnnn_0_nh_mapping_table[] = {
/*		map  hexcode decimal char ('.' is printed for the unprintable characters) */
/*		===  ======= ======= ==== */
		  0, /* 00 -   0    - '.' */
		  0, /* 01 -   1    - '.' */
		  0, /* 02 -   2    - '.' */
		  0, /* 03 -   3    - '.' */
		  0, /* 04 -   4    - '.' */
		  0, /* 05 -   5    - '.' */
		  0, /* 06 -   6    - '.' */
		  0, /* 07 -   7    - '.' */
		  0, /* 08 -   8    - '.' */
		  0, /* 09 -   9    - '.' */
		  0, /* 0A -  10    - '.' */
		  0, /* 0B -  11    - '.' */
		  0, /* 0C -  12    - '.' */
		  0, /* 0D -  13    - '.' */
		  0, /* 0E -  14    - '.' */
		  0, /* 0F -  15    - '.' */
		  0, /* 10 -  16    - '.' */
		  0, /* 11 -  17    - '.' */
		  0, /* 12 -  18    - '.' */
		  0, /* 13 -  19    - '.' */
		  0, /* 14 -  20    - '.' */
		  0, /* 15 -  21    - '.' */
		  0, /* 16 -  22    - '.' */
		  0, /* 17 -  23    - '.' */
		  0, /* 18 -  24    - '.' */
		  0, /* 19 -  25    - '.' */
		  0, /* 1A -  26    - '.' */
		  0, /* 1B -  27    - '.' */
		  0, /* 1C -  28    - '.' */
		  0, /* 1D -  29    - '.' */
		  0, /* 1E -  30    - '.' */
		  0, /* 1F -  31    - '.' */
		  0, /* 20 -  32    - ' ' */
		  1, /* 21 -  33    - '!' */
		  2, /* 22 -  34    - '"' */
		  3, /* 23 -  35    - '#' */
		  4, /* 24 -  36    - '$' */
		  5, /* 25 -  37    - '%' */
		  6, /* 26 -  38    - '&' */
		  7, /* 27 -  39    - ''' */
		  8, /* 28 -  40    - '(' */
		  9, /* 29 -  41    - ')' */
		 10, /* 2A -  42    - '*' */
		 11, /* 2B -  43    - '+' */
		 12, /* 2C -  44    - ',' */
		 13, /* 2D -  45    - '-' */
		 14, /* 2E -  46    - '.' */
		 15, /* 2F -  47    - '/' */
		 16, /* 30 -  48    - '0' */
		 17, /* 31 -  49    - '1' */
		 18, /* 32 -  50    - '2' */
		 19, /* 33 -  51    - '3' */
		 20, /* 34 -  52    - '4' */
		 21, /* 35 -  53    - '5' */
		 22, /* 36 -  54    - '6' */
		 23, /* 37 -  55    - '7' */
		 24, /* 38 -  56    - '8' */
		 25, /* 39 -  57    - '9' */
		 26, /* 3A -  58    - ':' */
		 27, /* 3B -  59    - ';' */
		 28, /* 3C -  60    - '<' */
		 29, /* 3D -  61    - '=' */
		 30, /* 3E -  62    - '>' */
		 31, /* 3F -  63    - '?' */
		 32, /* 40 -  64    - '@' */
		 33, /* 41 -  65    - 'A' */
		 34, /* 42 -  66    - 'B' */
		 35, /* 43 -  67    - 'C' */
		 36, /* 44 -  68    - 'D' */
		 37, /* 45 -  69    - 'E' */
		 38, /* 46 -  70    - 'F' */
		 39, /* 47 -  71    - 'G' */
		 40, /* 48 -  72    - 'H' */
		 41, /* 49 -  73    - 'I' */
		 42, /* 4A -  74    - 'J' */
		 43, /* 4B -  75    - 'K' */
		 44, /* 4C -  76    - 'L' */
		 45, /* 4D -  77    - 'M' */
		 46, /* 4E -  78    - 'N' */
		 47, /* 4F -  79    - 'O' */
		 48, /* 50 -  80    - 'P' */
		 49, /* 51 -  81    - 'Q' */
		 50, /* 52 -  82    - 'R' */
		 51, /* 53 -  83    - 'S' */
		 52, /* 54 -  84    - 'T' */
		 53, /* 55 -  85    - 'U' */
		 54, /* 56 -  86    - 'V' */
		 55, /* 57 -  87    - 'W' */
		 56, /* 58 -  88    - 'X' */
		 57, /* 59 -  89    - 'Y' */
		 58, /* 5A -  90    - 'Z' */
		 59, /* 5B -  91    - '[' */
		 60, /* 5C -  92    - '\' */
		 61, /* 5D -  93    - ']' */
		 62, /* 5E -  94    - '^' */
		 63, /* 5F -  95    - '_' */
		 64, /* 60 -  96    - '`' */
		 65, /* 61 -  97    - 'a' */
		 66, /* 62 -  98    - 'b' */
		 67, /* 63 -  99    - 'c' */
		 68, /* 64 - 100    - 'd' */
		 69, /* 65 - 101    - 'e' */
		 70, /* 66 - 102    - 'f' */
		 71, /* 67 - 103    - 'g' */
		 72, /* 68 - 104    - 'h' */
		 73, /* 69 - 105    - 'i' */
		 74, /* 6A - 106    - 'j' */
		 75, /* 6B - 107    - 'k' */
		 76, /* 6C - 108    - 'l' */
		 77, /* 6D - 109    - 'm' */
		 78, /* 6E - 110    - 'n' */
		 79, /* 6F - 111    - 'o' */
		 80, /* 70 - 112    - 'p' */
		 81, /* 71 - 113    - 'q' */
		 82, /* 72 - 114    - 'r' */
		 83, /* 73 - 115    - 's' */
		 84, /* 74 - 116    - 't' */
		 85, /* 75 - 117    - 'u' */
		 86, /* 76 - 118    - 'v' */
		 87, /* 77 - 119    - 'w' */
		 88, /* 78 - 120    - 'x' */
		 89, /* 79 - 121    - 'y' */
		 90, /* 7A - 122    - 'z' */
		 91, /* 7B - 123    - '{' */
		 92, /* 7C - 124    - '|' */
		 93, /* 7D - 125    - '}' */
		  0, /* 7E - 126    - '~' */
		  0, /* 7F - 127    - '' */
		  0, /* 80 - 128    - '�' */
		  0, /* 81 - 129    - '�' */
		  0, /* 82 - 130    - '�' */
		  0, /* 83 - 131    - '�' */
		  0, /* 84 - 132    - '�' */
		  0, /* 85 - 133    - '�' */
		  0, /* 86 - 134    - '�' */
		  0, /* 87 - 135    - '�' */
		  0, /* 88 - 136    - '�' */
		  0, /* 89 - 137    - '�' */
		  0, /* 8A - 138    - '�' */
		  0, /* 8B - 139    - '�' */
		  0, /* 8C - 140    - '�' */
		  0, /* 8D - 141    - '�' */
		  0, /* 8E - 142    - '�' */
		  0, /* 8F - 143    - '�' */
		  0, /* 90 - 144    - '�' */
		  0, /* 91 - 145    - '�' */
		  0, /* 92 - 146    - '�' */
		  0, /* 93 - 147    - '�' */
		  0, /* 94 - 148    - '�' */
		  0, /* 95 - 149    - '�' */
		  0, /* 96 - 150    - '�' */
		  0, /* 97 - 151    - '�' */
		  0, /* 98 - 152    - '�' */
		  0, /* 99 - 153    - '�' */
		  0, /* 9A - 154    - '�' */
		  0, /* 9B - 155    - '�' */
		  0, /* 9C - 156    - '�' */
		  0, /* 9D - 157    - '�' */
		  0, /* 9E - 158    - '�' */
		  0, /* 9F - 159    - '�' */
		  0, /* A0 - 160    - '�' */
		  0, /* A1 - 161    - '�' */
		  0, /* A2 - 162    - '�' */
		  0, /* A3 - 163    - '�' */
		  0, /* A4 - 164    - '�' */
		  0, /* A5 - 165    - '�' */
		  0, /* A6 - 166    - '�' */
		  0, /* A7 - 167    - '�' */
		  0, /* A8 - 168    - '�' */
		  0, /* A9 - 169    - '�' */
		  0, /* AA - 170    - '�' */
		  0, /* AB - 171    - '�' */
		  0, /* AC - 172    - '�' */
		  0, /* AD - 173    - '�' */
		  0, /* AE - 174    - '�' */
		  0, /* AF - 175    - '�' */
		 94, /* B0 - 176    - '�' */
		 95, /* B1 - 177    - '�' */
		  0, /* B2 - 178    - '�' */
		  0, /* B3 - 179    - '�' */
		  0, /* B4 - 180    - '�' */
		  0, /* B5 - 181    - '�' */
		  0, /* B6 - 182    - '�' */
		  0, /* B7 - 183    - '�' */
		  0, /* B8 - 184    - '�' */
		  0, /* B9 - 185    - '�' */
		  0, /* BA - 186    - '�' */
		  0, /* BB - 187    - '�' */
		  0, /* BC - 188    - '�' */
		  0, /* BD - 189    - '�' */
		  0, /* BE - 190    - '�' */
		  0, /* BF - 191    - '�' */
		  0, /* C0 - 192    - '�' */
		  0, /* C1 - 193    - '�' */
		  0, /* C2 - 194    - '�' */
		  0, /* C3 - 195    - '�' */
		  0, /* C4 - 196    - '�' */
		  0, /* C5 - 197    - '�' */
		  0, /* C6 - 198    - '�' */
		  0, /* C7 - 199    - '�' */
		  0, /* C8 - 200    - '�' */
		  0, /* C9 - 201    - '�' */
		  0, /* CA - 202    - '�' */
		  0, /* CB - 203    - '�' */
		  0, /* CC - 204    - '�' */
		  0, /* CD - 205    - '�' */
		  0, /* CE - 206    - '�' */
		  0, /* CF - 207    - '�' */
		  0, /* D0 - 208    - '�' */
		  0, /* D1 - 209    - '�' */
		  0, /* D2 - 210    - '�' */
		  0, /* D3 - 211    - '�' */
		  0, /* D4 - 212    - '�' */
		  0, /* D5 - 213    - '�' */
		  0, /* D6 - 214    - '�' */
		  0, /* D7 - 215    - '�' */
		  0, /* D8 - 216    - '�' */
		  0, /* D9 - 217    - '�' */
		  0, /* DA - 218    - '�' */
		  0, /* DB - 219    - '�' */
		  0, /* DC - 220    - '�' */
		  0, /* DD - 221    - '�' */
		  0, /* DE - 222    - '�' */
		  0, /* DF - 223    - '�' */
		  0, /* E0 - 224    - '�' */
		  0, /* E1 - 225    - '�' */
		  0, /* E2 - 226    - '�' */
		  0, /* E3 - 227    - '�' */
		  0, /* E4 - 228    - '�' */
		  0, /* E5 - 229    - '�' */
		  0, /* E6 - 230    - '�' */
		  0, /* E7 - 231    - '�' */
		  0, /* E8 - 232    - '�' */
		  0, /* E9 - 233    - '�' */
		  0, /* EA - 234    - '�' */
		  0, /* EB - 235    - '�' */
		  0, /* EC - 236    - '�' */
		  0, /* ED - 237    - '�' */
		  0, /* EE - 238    - '�' */
		  0, /* EF - 239    - '�' */
		  0, /* F0 - 240    - '�' */
		  0, /* F1 - 241    - '�' */
		  0, /* F2 - 242    - '�' */
		  0, /* F3 - 243    - '�' */
		  0, /* F4 - 244    - '�' */
		  0, /* F5 - 245    - '�' */
		  0, /* F6 - 246    - '�' */
		  0, /* F7 - 247    - '�' */
		  0, /* F8 - 248    - '�' */
		  0, /* F9 - 249    - '�' */
		  0, /* FA - 250    - '�' */
		  0, /* FB - 251    - '�' */
		  0, /* FC - 252    - '�' */
		  0, /* FD - 253    - '�' */
		  0, /* FE - 254    - '�' */
		  0, /* FF - 255    - '�' */
};
#endif


#ifdef FONTGEN_USE_EXTENDED_MAPPING_TABLE
/* Following table lists all the glpyhs, which the font definition is generated
   for. It is for use as an alternative mapping table for the collision problem
   and too many glpyhs problems described in the comments for the 
   font_Tahoma_10_n_nnnn_0_nh_mapping_table[].
   
   Each slot holds the hex code for a glpyh. The index of this glyph in the
   font_Tahoma_10_n_nnnn_0_nh_extended_mapping_table[] is the index to use 
   for the other tables.
   
   For the mapping, you need to perform a sequential search on this table as
   summarised below:
   
      // a sample binary search on the extended mapping table.
      // will find the mapping at most log2(glyphs) steps since
      // the font definition tables are sorted by glyph code
      unsigned int getIndex(unsigned int glpyh)
      {
         unsigned int left = 0, right = glyphs; 
         while (left <= right) {
            unsigned int mid = (right + left) / 2;
            unsigned int tmp = font_Tahoma_10_n_nnnn_0_nh_extended_mapping_table[mid];
            if (tmp == glyph)
               return mid;
            if (glyph < tmp)
               right = mid - 1;
            else 
               left = mid + 1;
         }
         return 0;   // not found, return the first glyph
      }
      
      width = font_Tahoma_10_n_nnnn_0_nh_width_table[getIndex(glyph)];
   
   *** Using font_Tahoma_10_n_nnnn_0_nh_mapping_table[] works faster, so use it whenever possible.
 */
const fuint16 font_Tahoma_10_n_nnnn_0_nh_extended_mapping_table[] = {
/*		glyph    decimal char ('.' is printed for the unprintable characters) */
/*		=====    ======= ==== */
		0x0020, /*  32   ' ' */
		0x0021, /*  33   '!' */
		0x0022, /*  34   '"' */
		0x0023, /*  35   '#' */
		0x0024, /*  36   '$' */
		0x0025, /*  37   '%' */
		0x0026, /*  38   '&' */
		0x0027, /*  39   ''' */
		0x0028, /*  40   '(' */
		0x0029, /*  41   ')' */
		0x002A, /*  42   '*' */
		0x002B, /*  43   '+' */
		0x002C, /*  44   ',' */
		0x002D, /*  45   '-' */
		0x002E, /*  46   '.' */
		0x002F, /*  47   '/' */
		0x0030, /*  48   '0' */
		0x0031, /*  49   '1' */
		0x0032, /*  50   '2' */
		0x0033, /*  51   '3' */
		0x0034, /*  52   '4' */
		0x0035, /*  53   '5' */
		0x0036, /*  54   '6' */
		0x0037, /*  55   '7' */
		0x0038, /*  56   '8' */
		0x0039, /*  57   '9' */
		0x003A, /*  58   ':' */
		0x003B, /*  59   ';' */
		0x003C, /*  60   '<' */
		0x003D, /*  61   '=' */
		0x003E, /*  62   '>' */
		0x003F, /*  63   '?' */
		0x0040, /*  64   '@' */
		0x0041, /*  65   'A' */
		0x0042, /*  66   'B' */
		0x0043, /*  67   'C' */
		0x0044, /*  68   'D' */
		0x0045, /*  69   'E' */
		0x0046, /*  70   'F' */
		0x0047, /*  71   'G' */
		0x0048, /*  72   'H' */
		0x0049, /*  73   'I' */
		0x004A, /*  74   'J' */
		0x004B, /*  75   'K' */
		0x004C, /*  76   'L' */
		0x004D, /*  77   'M' */
		0x004E, /*  78   'N' */
		0x004F, /*  79   'O' */
		0x0050, /*  80   'P' */
		0x0051, /*  81   'Q' */
		0x0052, /*  82   'R' */
		0x0053, /*  83   'S' */
		0x0054, /*  84   'T' */
		0x0055, /*  85   'U' */
		0x0056, /*  86   'V' */
		0x0057, /*  87   'W' */
		0x0058, /*  88   'X' */
		0x0059, /*  89   'Y' */
		0x005A, /*  90   'Z' */
		0x005B, /*  91   '[' */
		0x005C, /*  92   '\' */
		0x005D, /*  93   ']' */
		0x005E, /*  94   '^' */
		0x005F, /*  95   '_' */
		0x0060, /*  96   '`' */
		0x0061, /*  97   'a' */
		0x0062, /*  98   'b' */
		0x0063, /*  99   'c' */
		0x0064, /* 100   'd' */
		0x0065, /* 101   'e' */
		0x0066, /* 102   'f' */
		0x0067, /* 103   'g' */
		0x0068, /* 104   'h' */
		0x0069, /* 105   'i' */
		0x006A, /* 106   'j' */
		0x006B, /* 107   'k' */
		0x006C, /* 108   'l' */
		0x006D, /* 109   'm' */
		0x006E, /* 110   'n' */
		0x006F, /* 111   'o' */
		0x0070, /* 112   'p' */
		0x0071, /* 113   'q' */
		0x0072, /* 114   'r' */
		0x0073, /* 115   's' */
		0x0074, /* 116   't' */
		0x0075, /* 117   'u' */
		0x0076, /* 118   'v' */
		0x0077, /* 119   'w' */
		0x0078, /* 120   'x' */
		0x0079, /* 121   'y' */
		0x007A, /* 122   'z' */
		0x007B, /* 123   '{' */
		0x007C, /* 124   '|' */
		0x007D, /* 125   '}' */
		0x00B0, /* 176   '�' */
		0x00B1, /* 177   '�' */
};
#endif
