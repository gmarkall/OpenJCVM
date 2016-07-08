#ifndef _native_h_
#define _native_h_

//This is only used for indicating the next natives ID.
#define NEXT_AVAILABLE_NATIVE_ID 4

typedef void (*NativeFunction)(void);

extern NativeFunction natives[100];

#endif
