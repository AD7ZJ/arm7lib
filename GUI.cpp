/***************************************************************************
 *                                                                         *
 *  This program is free software; you can redistribute it and/or modify   *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation; either version 2 of the License, or      *
 *  (at your option) any later version.                                    *
 *                                                                         *
 *  This program is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with this program; if not, write to the Free Software            *
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111 USA    *
 *                                                                         *
 ***************************************************************************
 *                                                                         *
 *               (c) Copyright, 1997-2012, ANSR                            *
 *                                                                         *
 ***************************************************************************
 *                                                                         *
 * Filename:     GUI.cpp                                                   *
 *                                                                         *
 ***************************************************************************/

#include "armlib.h"

/**
 *  Constructor.
 */
GUI::GUI()
{
    this->base = NULL;
    this->font = NULL;
    this->alignment = Left;
}

/**
 *  Register the HAL (Hardware Abstraction Layer) specific to the desired
 *  display controller.
 *
 *  @param base pointer to base GUI class
 */
void GUI::RegisterHAL(GUIBase *base)
{
    this->base = base;
}

/**
 *  Draw a bitmap image starting the specified (x, y) coordinates.
 *
 *  @param x pixel index in the range 0 to sizeX - 1
 *  @param y pixel index in the range 0 to sizeY - 1
 *  @param bitmap pointer to the bitmap image array
 */
void GUI::Bitmap(uint32_t x, uint32_t y, const uint16_t *bitmap)
{
    uint32_t i, pixels, width, height;

    // The first two words of the bitmap array are the width and height of the image.
    width = *bitmap++;
    height = *bitmap++;

    // Total number of pixels in the bitmap array.
    pixels = width * height;

    // Create a display window.
    this->base->Window(x, y, width, height);

    // Transfer the bitmap image.
    this->base->StartWrite();

    for (i = 0; i < pixels; ++i)
        this->base->WritePixel (static_cast <uint32_t> (*bitmap++));

    this->base->StopWrite();
}

/**
 * Clear the screen by setting all the pixels to black.
 */
void GUI::ClearScreen()
{
    uint32_t i, pixels;

    this->base->Window(0, 0, this->base->sizeX, this->base->sizeY);

    this->base->StartWrite();

    pixels = this->base->sizeX * this->base->sizeY;

    for (i = 0; i < pixels; ++i)
        this->base->WritePixel (ColorBlack);

    this->base->StopWrite();
}

/**
 * Set the current text font.
 *
 * @param font pointer to the font definition structure
 */
void GUI::SetFont(const FONT_DEF *font)
{
    this->font = font;
}

/**
 * Set the text alignment to left, center, or right positioning.
 *
 * @param alignment enumerated type that specifies the desired text position
 */
void GUI::SetAlignment(Alignment alignment)
{
    this->alignment = alignment;
}

/**
 * Draws a solid rectangle with an upper, left-hand corner at (x, y)
 * that is sx pixels wide and sy pixels high with the specified fill
 * color.
 *
 * @param x upper left hand X coordinate window position
 * @param y upper left hand Y coordinate window position
 * @param sx width of window in pixels
 * @param sy height of window in pixels
 * @param fillColor rectangle fill color
 */
void GUI::Rectangle(uint32_t x, uint32_t y, uint32_t sx, uint32_t sy, Color fillColor)
{
    uint32_t i, pixels;

    // Set the display window.
    this->base->Window(x, y, sx, sy);

    // Total pixels to write.
    pixels = sx * sy;

    // Write the pixels with the same size.
    this->base->StartWrite();

    for (i = 0; i < pixels; ++i)
        this->base->WritePixel (fillColor);

    this->base->StopWrite();
}

/**
 * Display the desired text using the current font in the window with an uppper,
 * left-hand corner at (x, y) that is x pixels wide and y pixels high.
 *
 * @param x upper left hand X coordinate window position
 * @param y upper left hand Y coordinate window position
 * @param fgColor text foreground color
 * @param bgColor text background color
 * @param text pointer to NULL terminate text string
 */
void GUI::Text(uint32_t x, uint32_t y, Color fgColor, Color bgColor, const char *text, ...)
{
    char buffer[80], *textBuffer;
    va_list argList;
    const char *textAlignment;
    uint32_t i, j, index, width, height, bitmap, bitmapIndex;
    int32_t xCursor;

    // If the font hasn't been set, just exit rather than crash.
    if (this->font == NULL)
        return;

    // Create the output string.
    va_start (argList, text);
    vsnprintf (buffer, sizeof(buffer), text, argList);
    va_end (argList);

    // Pointer to the output string we will use to display the text.
    textBuffer = buffer;

    // Adjust the X axis position.
    xCursor = x;

    switch (this->alignment)
    {
        case Left:
            break;

        // TODO Complete this case.
        case Center:
            break;

        case Right:
            // Adjust the
            textAlignment = buffer;

            while (*textAlignment != 0)
                xCursor -= font->width_table[font->mapping_table[static_cast<uint8_t> (*textAlignment++)]];

                // Don't past the left-hand display margin.
                if (xCursor < 0)
                    xCursor = 0;
            break;
    } // END switch

    x = xCursor;

    // Display each character in the string.
    while (*textBuffer != 0 && x < this->base->sizeX)
    {
        // Index into the display array.
        index = font->mapping_table[static_cast<uint8_t> (*textBuffer++)];

        // Index to the Glyph bitmaps.
        bitmapIndex = font->offset_table[index];

        width = font->black_width_table[index];

        // If the height is zero, then each character has it's own height value.
        if (font->glyph_height == 0)
            height = font->black_height_table[index];
        else
            height= font->glyph_height;

        // Set the window where the character is written.
        this->base->Window(x, y, (font->width_table[index] > width ? font->width_table[index] : width), height);

        // Start writing to the display memory.
        this->base->StartWrite();

        // Write each line of the character.
        for (i = 0; i < height; ++i)
        {
            bitmap = font->glyph_table[bitmapIndex++];

            for (j = 0; j < width; ++j)
            {
                // Get the next 8-bits of the Glyph.
                if (j == 8 || j == 16)
                    bitmap = font->glyph_table[bitmapIndex++];

                if ((bitmap & 0x80) == 0x80)
                    this->base->WritePixel(fgColor);
                else
                    this->base->WritePixel(bgColor);

                bitmap = bitmap << 1;
            } // END for j

            while (j++ < font->width_table[index])
                this->base->WritePixel(bgColor);

        } // END for i

        // End writing to the display memory for this character.
        this->base->StopWrite();

        // Move the x-axis location.
        x += font->width_table[index];
    } // END while
}

