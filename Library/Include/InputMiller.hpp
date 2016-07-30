//***************************************************************************//
// Input Miller Base Class Interface
//
// Created Aug 27, 2006
// By: Jeremy Michael Miller
//
// Copyright (c) 2006-2016 Jeremy Michael Miller. 
// Author: = "Jeremy Michael Miller"
// Copyright: = "Copyright 2006-2016, Input Miller,  All rights reserved."
// Credits = ["Jeremy Michael Miller"]
// License: "Fair use v0.9"
// Version: "0.0.1"
// Maintainer: "Jeremy Michael Miller"
// Email: "maybe_later@mst.dnsalias.net"
// Status: "Alpha"
//***************************************************************************//

#ifndef MST_INPUT_HPP
#define MST_INPUT_HPP

//***************************************************************************//
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <vector>
//***************************************************************************//

// Define the current version of this library
#define MST_INPUT_VERSION 0.002F

//***************************************************************************//
namespace MST
{
  //*************************************************************************//
  // Singleton -- there can only be one Input object to manage all input devices
  class Input 
  {
  private:
    //***********************************************************************//
    //-----------------------------------------------------------------------//
    // Pointer to directinput 8
    IDirectInput8* mpDirectInput;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // This vector holds all the devices that will be polled with this classes
    // memeber function void Poll(); is called
    std::vector<class Device*> mvDevices;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // Singleton requirements
    static Input* mpInstance;
    Input();
    //-----------------------------------------------------------------------//
    //***********************************************************************//
  public:
    //***********************************************************************//
    //-----------------------------------------------------------------------//
    // Destructor
    // Note this destructor is not virtual. Do not derive from this class
    ~Input();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // Singleton access function
    static class Input* Instance() 
    {
      if(mpInstance == nullptr) 
        mpInstance = new Input();

      return mpInstance;
    }
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // This method will initialize all devices is the mvDevices vector. In the 
    // case that devices are already initialized this method will uninitialize 
    // those devices.
    // Parameter 1: This is the current instance of the application that using 
    //              this library/class.
    // Parameter 2: This is handle to the window the application is running in
    // Return Value: This method will return true if and only if all devices
    //               initialized in the mvDevices vector return true
    bool Initialize(HINSTANCE hApplicationIntance, HWND hMainWindow);
    // This method will release the DirectInput interface and uninitialize all 
    // devices in the mvDevices vector
    void Uninitialize();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // This method gives public access to the keyboard object so the state of the 
    // keyboard can be attained
    // Return Value: A constant pointer to this class's keyboard device
    const class Keyboard* GetKeyboard() { return reinterpret_cast<class Keyboard*>(this->mvDevices[0]); }
    // This method gives public access to the mouse object so the state of the 
    // mouse can be attained
    // Return Value: A constant pointer to this class's mouse device
    const class Mouse*    GetMouse()    { return reinterpret_cast<class Mouse*>(this->mvDevices[1]); }
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // This method should be called once per program loop by the user of this 
    // library.  This method will update all the devices in the mvDevices vector
    // TODO: Consider making this concurrent and running it at a constant rate.
    void Poll();
    //-----------------------------------------------------------------------//
    //***********************************************************************//
  }; // End of class Input
  //*************************************************************************//

} // End of namespace MST
//***************************************************************************//

#endif MST_INPUT_HPP