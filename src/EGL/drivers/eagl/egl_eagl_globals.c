/**************************************************************************
 * MIT LICENSE
 *
 * Copyright (c) 2013-2014, David Andreoletti <http://davidandreoletti.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 **************************************************************************/

#include "EGL/drivers/eagl/egl_eagl_globals.h"
#include "eglmutex.h"

static _EGL_DECLARE_MUTEX(_eaglGlobalMutex);
struct EAGL_egl_global _eaglGlobal = {
    &_eaglGlobalMutex,
    true
};

bool isContextLost(struct EAGL_egl_global* global) {
    _eglLockMutex(&_eaglGlobalMutex);
    bool result = global->foregroundApplication;
    _eglUnlockMutex(&_eaglGlobalMutex);
    return result;
}

void setContextLost(struct EAGL_egl_global* global, bool value) {
    _eglLockMutex(&_eaglGlobalMutex);
    global->foregroundApplication = value;
    _eglUnlockMutex(&_eaglGlobalMutex);
}
