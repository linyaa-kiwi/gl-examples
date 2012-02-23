// Copyright 2012 Chad Versace <chad@chad-versace.us>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#import "MyGLView.h"

#import <OpenGL/OpenGL.h>
#import <OpenGL/gl.h>

static const int kSpaceKey = 49;

@implementation MyGLView

    @synthesize glContext = _glContext;

    - (id) init {
        [NSException raise:@"NotImplementedError" format:nil];
        return nil;
    }

    - (id) initWithFrame:(NSRect)rect glContext:(NSOpenGLContext*)ctx {
        self = [super initWithFrame:rect];
        if (self == nil)
            return nil;
        _glContext = ctx;
        return self;
    }

    - (BOOL) isOpaque {
        return YES;
    }

    - (BOOL) canBecomeKeyView {
        return YES;
    }

    - (BOOL) acceptsFirstResponder {
        return YES;
    }

    - (void) mouseDown:(NSEvent*)event {
        [self drawRect:[self frame]];
    }

    - (void) keyDown:(NSEvent*)event {
        if ([event keyCode] == kSpaceKey) {
            [self drawRect:[self frame]];
        }
        else {
            [super keyDown:event];
        }
    }

    - (void) drawRect:(NSRect)bounds {
        static int i = 0;
        i = ++i % 3;

        switch (i) {
            case 0: glClearColor(1, 0, 0, 1); break;
            case 1: glClearColor(0, 1, 0, 1); break;
            case 2: glClearColor(0, 0, 1, 1); break;
        }

        glClear(GL_COLOR_BUFFER_BIT);
        [_glContext flushBuffer];
    }
@end
