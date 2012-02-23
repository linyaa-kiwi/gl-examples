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

#import "MyWindow.h"

static const int kEscapeKey = 53;

@implementation MyWindow

    - (void) close {
        [NSApp terminate:self];

        // If the app refused to terminate, this window should still close.
        [super close];
    }

    - (BOOL) acceptsFirstResponder {
        return YES;
    }

    - (void) keyDown:(NSEvent*)event {
        if ([event keyCode] == kEscapeKey) {
            [self close];
        }
        else {
            [super keyDown:event];
        }
    }
@end
