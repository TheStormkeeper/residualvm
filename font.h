// Residual - Virtual machine to run LucasArts' 3D adventure games
// Copyright (C) 2003-2005 The ScummVM-Residual Team (www.scummvm.org)
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA

#ifndef FONT_H
#define FONT_H

#include "bits.h"
#include "resource.h"

#include <list>

class Font : public Resource {
public:
	Font(const char *filename, const char *data, int len);
	~Font();

	uint32 getCharWidth(char c) { return _charHeaders[_charIndex[c]].width; }
	uint32 getCharHeight(char c) { return _charHeaders[_charIndex[c]].height; }
	uint32 getCharLogicalWidth(char c) { return _charHeaders[_charIndex[c]].startingCol; }
	uint32 getCharStartingCol(char c) { return _charHeaders[_charIndex[c]].startingCol; }
	uint32 getCharStartingLine(char c) { return _charHeaders[_charIndex[c]].startingLine; }
	const byte *getCharData(char c) { return _fontData + (_charHeaders[_charIndex[c]].offset); }

	static const uint8 Font::emerFont[][13];
private:

	struct CharHeader {
		uint32 offset;
		uint32 unknown;
		uint8  logicalWidth;
		uint8  startingCol;
		uint8  startingLine;
		uint32 width;
		uint32 height;
	};

	uint32 _numChars;
	uint32 _dataSize;
	uint32 _maxCharWidth, _maxCharHeight;
	uint32 _unknownHeader1, _unknownHeader2;
	uint32 _firstChar, _lastChar;
	uint16 *_charIndex;
	CharHeader *_charHeaders;
	byte *_fontData;
};

#endif
