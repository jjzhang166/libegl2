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

#include "EGL/drivers/eagl/opengles/opengles_ios.h"
#include "EGL/drivers/eagl/opengles/opengles1_ios.h"
#include "EGL/drivers/eagl/opengles/opengles2_ios.h"
#include <stddef.h>

void opengles_api_init(__OpenGLESAPI* api, _OpenGLESAPIVersion version) {
    if (api == NULL) {return;}
    switch (version) {
        case OPENGL_ES_1_1:
            api->majorVersion = 1;
            opengles1_api_init(api);
            break;
        case OPENGL_ES_2_0:
            api->majorVersion = 2;
            opengles2_api_init(api);
            break;
        case OPENGL_ES_3_0:
            api->majorVersion = 3;
            opengles2_api_init(api);
            break;
        default:
            break;
    }
}
