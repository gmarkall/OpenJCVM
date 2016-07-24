/**
 * Copyright 2008 - present Oliver Lusing / Louis Liu
 *
 * This file is part of OpenJCVM; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation version 2.
 *
 * You should have received a copy of the GNU General Public License along with
 * OpenJCVM; see the file COPYING. If not, see <http://www.gnu.org/licenses/>.
 **/

#ifndef _native_h_
#define _native_h_

//This is only used for indicating the next natives ID.
#define NEXT_AVAILABLE_NATIVE_ID 4

typedef void (*NativeFunction)(void);

extern NativeFunction natives[100];

#endif
