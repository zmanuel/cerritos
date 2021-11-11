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

#include <iostream>

#include "backend.h"

#include "application.h"
#include "event.h"

cApplication::cApplication() {
    // Start by setting up the timestep
    unsigned int newTimestep = GetTicks();

    this->firstTimestep = newTimestep;
    
    this->currentTimestep.fromBeginning = 0;
    this->currentTimestep.fromLast = 0;
    
    // Create the event manager
    this->eventManager = new cEventManager();
    
    // Setup miscellaneous stuff
    this->keepRunning = true;
}

void cApplication::setMainWindow(cMainWindow* window) {
    this->mainwindow = window;
}

cMainWindow* cApplication::getMainWindow() {
    return this->mainwindow;
}

bool cApplication::hasEvent() { 
    return this->eventManager->hasEvent();
}

cEvent* cApplication::PollEvent() {
    if(this->hasEvent())
        return this->eventManager->popEvent();
    
    return NULL;
}

const TimeStep cApplication::getTimestep() {
    return this->currentTimestep;
}

void cApplication::BeginUpdate() {
    unsigned int newTimestep;
    
    // update timestep
    newTimestep = SDL_GetTicks();
    
    this->currentTimestep.fromBeginning = newTimestep - this->firstTimestep;
    this->currentTimestep.fromLast = newTimestep - this->lastTimestep;
    
    this->lastTimestep = newTimestep;

    // Get system-specific events from the backend
    PollHardwareEvents(this->eventManager);
    
}

void cApplication::ProcessEvents() {
    // This is the main event processing loop
    while(this->hasEvent() ) {
        cEvent* anEvent = NULL;
        anEvent = this->PollEvent();
        
        switch(anEvent->type) {
            case CER_QuitEvent:
                this->keepRunning = false;
            default:
                this->ProcessOneEvent(anEvent);
                break;
        }
    } 
}

// Process one event.  Default implementation does nothing.
void cApplication::ProcessOneEvent(cEvent* evt) {
    
}

void cApplication::Update() {
}

void cApplication::UpdateView() {
    if(this->mainwindow != NULL) {
        this->mainwindow->Update();
    }
}

void cApplication::UpdateAll() {
    this->BeginUpdate();
    this->ProcessEvents();
    this->Update();
    this->UpdateView();
    this->EndUpdate();
}

void cApplication::EndUpdate() {
    
}