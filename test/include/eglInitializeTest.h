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

#ifndef TEST_INCLUDE_EGLINITIALIZETEST_H_
#define TEST_INCLUDE_EGLINITIALIZETEST_H_

#include "eglTest.h"
#include "eglPlatformHarness.h"

#include <stdlib.h>
#include <string.h>


static void test_eglInitialize(EGLDisplay dpy, EGLBoolean* eglInitializeBoolResult, EGLint eglInitializeCMP0, EGLint expectedEglInitializeBoolResult, EGLint expectedEglInitializeError, EGLint* eglInitializeMajorVersion, EGLint  eglInitializeCMP1, EGLint* expectedEglInitializeMajorVersion, EGLint* eglInitializeMinorVersion, EGLint eglInitializeCMP2, EGLint* expectedEglInitializeMinorVersion) {

    *eglInitializeBoolResult = eglInitialize(dpy, eglInitializeMajorVersion, eglInitializeMinorVersion);
    test_compare_EGLBoolean(*eglInitializeBoolResult, eglInitializeCMP0, expectedEglInitializeBoolResult);
    test_compare_EGLint(eglGetError(), EQUAL, expectedEglInitializeError);
    if (expectedEglInitializeMajorVersion != NULL) {
        test_compare_EGLint(*(eglInitializeMajorVersion), eglInitializeCMP1, *expectedEglInitializeMajorVersion);
    }
    if (expectedEglInitializeMinorVersion != NULL) {
        test_compare_EGLint(*(eglInitializeMinorVersion), eglInitializeCMP2, *expectedEglInitializeMinorVersion);
    }
}

static void test_eglInitialize2(EGLDisplay dpy, EGLBoolean* eglInitializeBoolResult, EGLint eglInitializeCMP0, EGLBoolean expectedEglInitializeBoolResult, EGLint expectedEglInitializeError) {
    
    test_eglInitialize(dpy, eglInitializeBoolResult, eglInitializeCMP0, expectedEglInitializeBoolResult, expectedEglInitializeError, NULL, IGNORE, NULL, NULL, IGNORE, NULL);
}

void eglInitialize_0(TestPlatform* p) {
    // EGL_TRUE is returned on success, and major and minor are updated
    // with the major and minor version numbers of the EGL implementation
    EGLDisplay dpy;
    test_eglGetDisplay(&dpy, VALID_NATIVE_DISPLAY, EGL_SUCCESS, NOT_EQUAL, EGL_NO_DISPLAY);
    test_eglInitialize(dpy, ADDRESS(LAST_BOOL_RESULT), EQUAL, EGL_TRUE, EGL_SUCCESS, MAJOR_VERSION, EQUAL, MAJOR_VERSION_EXPECTED, MINOR_VERSION, EQUAL, MINOR_VERSION_EXPECTED);
}

void eglInitialize_1(TestPlatform* p) {
    // major and minor are not updated if they are specified as NULL.
    EGLDisplay dpy;
    EGLint* ma = NULL;
    EGLint* mi = NULL;
    test_eglGetDisplay(&dpy, VALID_NATIVE_DISPLAY, EGL_SUCCESS, NOT_EQUAL, EGL_NO_DISPLAY);
    test_eglInitialize(dpy, ADDRESS(LAST_BOOL_RESULT), EQUAL, EGL_TRUE, EGL_SUCCESS, ma, EQUAL, ma, mi, EQUAL, mi);
}

void eglInitialize_2(TestPlatform* p) {
    // An EGL_BAD_DISPLAY error is generated if the dpy argument
    // does not refer to a valid EGLDisplay
    // EGL_FALSE is returned on failure and major and minor
    // are not updated.
    EGLDisplay dpy;
    test_eglGetDisplay(&dpy, VALID_NATIVE_DISPLAY, EGL_SUCCESS, NOT_EQUAL, EGL_NO_DISPLAY);
    test_eglInitialize(INVALID_NATIVE_DISPLAY, ADDRESS(LAST_BOOL_RESULT), EQUAL, EGL_FALSE, EGL_BAD_DISPLAY, MAJOR_VERSION, EQUAL, MAJOR_VERSION_DEFAULT, MINOR_VERSION, EQUAL, MINOR_VERSION_DEFAULT);
}

void eglInitialize_3(TestPlatform* p) {
    // An EGL_NOT_INITIALIZED error is generated if EGL cannot
    // be initialized for an otherwise valid dpy.
    EGLDisplay dpy;
    EGLint* ma = NULL;
    EGLint* mi = NULL;
    test_eglGetDisplay(&dpy, VALID_NATIVE_DISPLAY, EGL_SUCCESS, NOT_EQUAL, EGL_NO_DISPLAY);
    test_eglInitialize(dpy, ADDRESS(LAST_BOOL_RESULT), EQUAL, EGL_FALSE, EGL_NOT_INITIALIZED, ma, EQUAL, ma, mi, EQUAL, mi);
}

void eglInitialize_4(TestPlatform* p) {
    // Initializing an already-initialized display is allowed, but the
    // only effect of such a call is to return EGL_TRUE and update
    // the EGL version numbers.
    EGLDisplay dpy;
    EGLint* ma = NULL;
    EGLint* mi = NULL;
    test_eglGetDisplay(&dpy, VALID_NATIVE_DISPLAY, EGL_SUCCESS, NOT_EQUAL, EGL_NO_DISPLAY);
    test_eglInitialize(dpy, ADDRESS(LAST_BOOL_RESULT), EQUAL, EGL_TRUE, EGL_SUCCESS, ma, EQUAL, ma, mi, EQUAL, mi);
    test_eglInitialize(dpy, ADDRESS(LAST_BOOL_RESULT), EQUAL, EGL_TRUE, EGL_SUCCESS, MAJOR_VERSION, EQUAL, MAJOR_VERSION_EXPECTED, MINOR_VERSION, EQUAL, MINOR_VERSION_EXPECTED);
}

/*
 * Runs all eglInitialize unit tests
 * @param p
 */
void run_eglInitialize_unit_tests(TestPlatform* p) {
    TEST_CASE_SETUP(p)
    eglInitialize_0(p);
    TEST_CASE_TEARDOWN(p)
    TEST_CASE_SETUP(p)
    eglInitialize_1(p);
    TEST_CASE_TEARDOWN(p)
    TEST_CASE_SETUP(p)
    eglInitialize_2(p);
    TEST_CASE_TEARDOWN(p)
    TEST_CASE_SETUP(p)
    // NOT PASSED - Hard to test scenario - eglInitialize_3(p);
    TEST_CASE_TEARDOWN(p)
    TEST_CASE_SETUP(p)
    eglInitialize_4(p);
    TEST_CASE_TEARDOWN(p)
} 

#endif  // TEST_INCLUDE_EGLINITIALIZETEST_H_
