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

#import <Cocoa/Cocoa.h>
#import <OpenGL/OpenGL.h>

#import "MyGLView.h"
#import "MyWindow.h"
#import "create_window.h"

NSWindow*
createWindow(NSView* contentView) {
    unsigned int styleMask = NSTitledWindowMask
                           | NSClosableWindowMask;

    MyWindow* window = [[MyWindow alloc]
                        initWithContentRect:[contentView frame]
                        styleMask:styleMask
                        backing:NSBackingStoreBuffered
                        defer:NO];
    [window autorelease];
    [window setTitle:@"a title"];
    [window setContentView:contentView];
    [window makeFirstResponder:contentView];
    [window center];
    [window makeKeyAndOrderFront:nil];

    return window;
}
