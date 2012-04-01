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
 * Filename:     GUI.h                                                     *
 *                                                                         *
 ***************************************************************************/

#ifndef GUI_H
#define GUI_H

/**
 *  @defgroup library Generic Library Functions
 *
 *  @{
 */

/**
 *  Base object GUI (Graphical User Interface) methods.  This is a generic set of methods that
 *  interfaces with the hardware specific GUIBase object.
 */
class GUI
{
public:
    GUI();

    /// 16-bit color map that defines that desired TFT LCD color.
    /// http://chaos2.org/misc/rgb.html
    ///
    /// RGB color to 16-bit value mapping.
    ///
    /// R R R R  R G G G  G G G B  B B B B
    typedef enum
    {
        /// Black.
        ColorBlack = 0x0000,

        /// Dark gray.
        ColorDarkGray = 0x7412,

        /// Gray.
        ColorGray = 0xc618,

        /// Light gray.
        ColorLightGray = 0xd69a,

        /// White.
        ColorWhite = 0xffff,


        /// Red.
        ColorRed = 0xf800,

        /// Green.
        ColorGreen = 0x07e0,

        /// Blue.
        ColorBlue = 0x001f,


        /// Yellow.
        ColorYellow = 0xffe0,

        /// Cyan.
        ColorCyan = 0x07ff,

        /// Magenta.
        ColorMagenta = 0xf81f
    } Color;

    /// Text alignment attribute.
    typedef enum
    {
        /// Left justification.
        Left,

        /// Center text.
        Center,

        /// Right justification.
        Right
    } Alignment;

    void Bitmap(uint32_t x, uint32_t y, const uint16_t *bitmap);
    void ClearScreen();
    void Rectangle(uint32_t x, uint32_t y, uint32_t sx, uint32_t sy, Color fillColor);
    void RegisterHAL(GUIBase *base);
    void SetFont(const FONT_DEF *font);
    void SetAlignment(Alignment alignment);
    void Text(uint32_t x, uint32_t y, Color fgColor, Color bgColor, const char *text, ...);

private:
    /// Pointer to the GUI base object that provides abstract methods for each type of hardware.
    GUIBase *base;

    /// Current font definition.
    const FONT_DEF *font;

    /// Current text alignment.
    Alignment alignment;
};

/** @} */

#endif // #ifndef GUI_H
