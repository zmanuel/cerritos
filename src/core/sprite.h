/*
 * Cerritos
 * Copyright 2021 by Dave Fancella, Anthony Fancella
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a 
 * copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included 
 * in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 * 
 */

#ifndef SPRITE__H
#define SPRITE__H

// Includes and forward declarations go here
#include "rect.h"
#include "surface.h"
#include "window.h"
#include "types.h"
#include "object.h"


namespace cerritos {

class Sprite {
public:
    int m_Fps;
    int m_CurrentFrame;
    
    Rect* m_Rect;
    Surface* m_Surface;
    List<Surface*> m_Frames;
    
    Window* m_Window;
    
    Sprite(Window* window, int x, int y, int w, int h, int fps);
    ~Sprite();
    
    void Draw();
    void addFrame(String pathToFrame);
    void Update(Timestep* timestep);
};
    
} // namespace cerritos

#endif // SPRITE__H


