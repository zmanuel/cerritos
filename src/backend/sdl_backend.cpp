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

#include "SDL.h"

#include "sdl_backend.h"

#include "event.h"

unsigned int GetTicks() {
    return SDL_GetTicks();
}

void Delay(unsigned int ms) {
    SDL_Delay(ms);
}

int backendInit(unsigned int flags) {
    int successCode;
    
    successCode = SDL_Init(flags);
    if(successCode == -1) {
        std::cout << "SDL_Init: " << SDL_GetError();
        return -1;
    }

    return successCode;
}

void backendClose() {
    SDL_Quit();
}

void PollHardwareEvents(cEventManager* eventManager) {
    // Get SDL events
    SDL_Event event;
    cEvent* newEvent = NULL;
    
    while (SDL_PollEvent(&event)) {
        newEvent = NULL;
        switch (event.type) {
            case SDL_QUIT:
                newEvent = new cQuitEvent(
                    event.quit.timestamp
                );
                break;
            case SDL_WINDOWEVENT:
                newEvent = new cWindowEvent(
                    event.window.timestamp
                );
                break;
            case SDL_SYSWMEVENT:
                newEvent = new cSyswmEvent(
                    event.syswm.timestamp
                );
                break;
            case SDL_KEYDOWN:
                newEvent = new cKeydownEvent(
                    event.key.timestamp
                );
                break;
            case SDL_KEYUP:
                newEvent = new cKeyupEvent(
                    event.key.timestamp
                );
                break;
            case SDL_TEXTEDITING:
                newEvent = new cTextEditingEvent(
                    event.edit.timestamp
                );
                break;
            case SDL_TEXTINPUT:
                newEvent = new cTextInputEvent(
                    event.text.timestamp
                );
                break;
            case SDL_KEYMAPCHANGED:
                newEvent = new cKeymapchangedEvent;
                break;
            case SDL_MOUSEBUTTONDOWN:
                newEvent = new cMouseButtondownEvent(
                    event.button.timestamp
                );
                break;
            case SDL_MOUSEMOTION:
                newEvent = new cMouseMotionEvent(
                    event.motion.timestamp, event.motion.windowID, event.motion.x, event.motion.y
                );
                break;
            case SDL_MOUSEBUTTONUP:
                newEvent = new cMouseButtonupEvent(
                    event.button.timestamp
                );
                break;
            case SDL_MOUSEWHEEL:
                newEvent = new cMouseWheelEvent(
                    event.wheel.timestamp
                );
                break;
            case SDL_JOYAXISMOTION:
                newEvent = new cJoyAxisMotionEvent(
                    event.jaxis.timestamp
                );
                break;
            case SDL_JOYBALLMOTION:
                newEvent = new cJoyBallMotionEvent(
                    event.jball.timestamp
                );
                break;
            case SDL_JOYHATMOTION:
                newEvent = new cJoyHatMotionEvent(
                    event.jhat.timestamp
                );
                break;
            case SDL_JOYBUTTONDOWN:
                newEvent = new cJoyButtondownEvent(
                    event.jbutton.timestamp
                );
                break;
            case SDL_JOYBUTTONUP:
                newEvent = new cJoyButtonupEvent(
                    event.jbutton.timestamp
                );
                break;
            case SDL_JOYDEVICEADDED:
                newEvent = new cJoyDeviceAddedEvent(
                    event.jdevice.timestamp
                );
                break;
            case SDL_JOYDEVICEREMOVED:
                newEvent = new cJoyDeviceRemovedEvent(
                    event.jdevice.timestamp
                );
                break;
            case SDL_CONTROLLERAXISMOTION:
                newEvent = new cControllerAxisMotionEvent(
                    event.caxis.timestamp
                );
                break;
            case SDL_CONTROLLERBUTTONDOWN:
                newEvent = new cControllerButtondownEvent(
                    event.cbutton.timestamp
                );
                break;
            case SDL_CONTROLLERBUTTONUP:
                newEvent = new cControllerButtonupEvent(
                    event.cbutton.timestamp
                );
                break;
            case SDL_CONTROLLERDEVICEADDED:
                newEvent = new cControllerDeviceAddedEvent(
                    event.cdevice.timestamp
                );
                break;
            case SDL_CONTROLLERDEVICEREMOVED:
                newEvent = new cControllerDeviceRemovedEvent(
                    event.cdevice.timestamp
                );
                break;
            case SDL_CONTROLLERDEVICEREMAPPED:
                newEvent = new cControllerDeviceRemappedEvent(
                    event.cdevice.timestamp
                );
                break;
            case SDL_FINGERDOWN:
                newEvent = new cFingerdownEvent(
                    event.tfinger.timestamp
                );
                break;
            case SDL_FINGERUP:
                newEvent = new cFingerupEvent(
                    event.tfinger.timestamp
                );
                break;
            case SDL_FINGERMOTION:
                newEvent = new cFingerMotionEvent(
                    event.tfinger.timestamp
                );
                break;
            case SDL_DOLLARGESTURE:
                newEvent = new cDollarGestureEvent(
                    event.dgesture.timestamp
                );
                break;
            case SDL_DOLLARRECORD:
                newEvent = new cDollarRecordEvent(
                    event.dgesture.timestamp
                );
                break;
            case SDL_MULTIGESTURE:
                newEvent = new cMultiGestureEvent(
                    event.mgesture.timestamp
                );
                break;
            case SDL_CLIPBOARDUPDATE:
                newEvent = new cClipboardUpdateEvent;
                break;
            case SDL_DROPFILE:
                newEvent = new cDropFileEvent(
                    event.drop.timestamp
                );
                break;
            case SDL_DROPTEXT:
                newEvent = new cDropTextEvent(
                    event.drop.timestamp
                );
                break;
            case SDL_DROPBEGIN:
                newEvent = new cDropBeginEvent(
                    event.drop.timestamp
                );
                break;
            case SDL_DROPCOMPLETE:
                newEvent = new cDropCompleteEvent(
                    event.drop.timestamp
                );
                break;
            case SDL_AUDIODEVICEADDED:
                newEvent = new cAudioDeviceAddedEvent(
                    event.adevice.timestamp
                );
                break;
            case SDL_AUDIODEVICEREMOVED:
                newEvent = new cAudioDeviceRemovedEvent(
                    event.adevice.timestamp
                );
                break;
            case SDL_RENDER_TARGETS_RESET:
                newEvent = new cRenderTargetsResetEvent;
                break;
            case SDL_RENDER_DEVICE_RESET:
                newEvent = new cRenderDeviceResetEvent;
                break;
            default:
                // std::cout << "Unhandled Event!" << std::endl;
                break;
        }
        if(newEvent != NULL)
            eventManager->addEvent( (cEvent*) newEvent);
    }
}


