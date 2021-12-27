/*
 * Projects
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

// This is an adaptation of the hello.cpp example that shows how to
// handle events using the Application object.

#include <iostream>
#include <stdio.h>
// Include the cerritos header file.  This brings in pretty much everything.
#include "cerritos.h"

using namespace cerritos;

class spMainWindow : public cMainWindow {
public:
    Sprite* m_sprite;
    
    int mousex;
    int mousey;
    
    void onMouseMotion(MouseMotionEvent* evt) {
        m_sprite->setPosition(evt->posx, evt->posy);
    }
    
    void setSprite(Sprite* sprite) {
        m_sprite = sprite;
    }
    
    void Update(const Timestep timestep) {
//        std::cout << mousex << ", " << m_sprite->m_Rect->position.x << ", " << mousey << ", " << m_sprite->m_Rect->position.y << "\n";
        
        m_sprite->Update(timestep);
    }
    
    void Render(const Timestep timestep) {
        m_sprite->Draw();
    }
    
    void onKeydown(KeydownEvent* evt) {
        switch (evt->mKey) {
            case K_0:
                m_sprite->m_Mode = 0;
                break;
                
            case K_1:
                m_sprite->m_Mode = 1;
                break;
            case K_a:
                m_sprite->m_Mode = 999;
                break;
        }
    }
        
};

int main( int argc, char* args[] ) {
    // This is a handy way to initialize cerritos and get a default
    // application object.  Typically, more complex games need more than
    // a default application object.
    Application* theApp;
    spMainWindow* theWindow;
    Sprite* theSprite;

    cInit();
        
    theApp = new Application(argc, args);

    theWindow = new spMainWindow();
    
    theSprite = new Sprite(theWindow->getWindow(), 0, 0, 64, 64, 10);
    
    std::vector<String> dancing = {"/home/pi/Projects/cerritos/assets/boimlerdance00.bmp",
                                  "/home/pi/Projects/cerritos/assets/boimlerdance01.bmp",
                                  "/home/pi/Projects/cerritos/assets/boimlerdance02.bmp",
                                  "/home/pi/Projects/cerritos/assets/boimlerdance01.bmp" };
                                  
    std::vector<String> walking = {"/home/pi/Projects/cerritos/assets/boimlerdance10.bmp",
                                   "/home/pi/Projects/cerritos/assets/boimlerdance11.bmp",
                                   "/home/pi/Projects/cerritos/assets/boimlerdance12.bmp",
                                   "/home/pi/Projects/cerritos/assets/boimlerdance13.bmp",
                                   "/home/pi/Projects/cerritos/assets/boimlerdance14.bmp",
                                   "/home/pi/Projects/cerritos/assets/boimlerdance12.bmp" };
    
    theSprite->addSpriteMode(0, dancing);
    theSprite->setDefaultMode(1);
    
    theSprite->m_Mode = 2;
    
    theSprite->addSpriteMode(1, walking);
    
    theApp->setMainWindow(theWindow);
    theWindow->setTitle("Sprite Test");

    theWindow->setSprite(theSprite);
    // This is your game loop.
    theApp->loop();
    // Close up cerritos before quitting.  This makes sure we don't leave
    // any devices open or whatever.  Most modern operating systems don't
    // have those problems anymore, but this helps avoid segfaults.
    cClose();
}

