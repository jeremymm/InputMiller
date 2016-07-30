//***************************************************************************//
// Input Base Class Implementation
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

//***************************************************************************//
#include <Windows.h>
//***************************************************************************//

//***************************************************************************//
#include "InputMiller.hpp" 
#include "Devices\Device.hpp"
#include "Devices\Keyboard.hpp"
#include "Devices\Mouse.hpp"
//***************************************************************************//

//***************************************************************************//
namespace MST
{
  //*************************************************************************//
  // Static pointer for singleton design pattern
  class Input* Input::mpInstance = nullptr;
  //*************************************************************************//

  //*************************************************************************//
  // Private constructor for singleton design pattern
  Input::Input()
  {
    // set the pointer to the DirectINput interface to null so the we know when
    // or if its needs to be created
    mpDirectInput = nullptr;
    
    //-----------------------------------------------------------------------//
    // Create a keyboard device and add it to the devices vector
    class Device* pDevice = new Keyboard();
    this->mvDevices.push_back(pDevice);
    //-----------------------------------------------------------------------//
    
    //-----------------------------------------------------------------------//
    // Create a mouse device and add it to the devices vector
    pDevice = new Mouse();
    this->mvDevices.push_back(pDevice);
    //-----------------------------------------------------------------------//
  } // End of Input::Input()
  //*************************************************************************//

  //*************************************************************************//
  // Destructor
  Input::~Input()
  {
    //-----------------------------------------------------------------------//
    // Uninitialize all devices in the device vector
    this->Uninitialize();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // Delete all devices in the device vector and clear the vector
    for(int i = 0; i < mvDevices.size(); i++)
    {
      delete mvDevices[i];
    }
    // This call is not really needed
    mvDevices.clear();
    //-----------------------------------------------------------------------//
  } // End of Input::~Input()
  //*************************************************************************//

  //*************************************************************************//
  // Public
  // This method will initialize all devices is the mvDevices vector. In the 
  // case that devices are already initialized this method will uninitialize 
  // those devices.
  // Parameter 1: This is the current instance of the application that using 
  //              this library/class.
  // Parameter 2: This is handle to the window the application is running in
  // Return Value: This method will return true if and only if all devices
  //               initialized in the mvDevices vector return true
  bool Input::Initialize(HINSTANCE hApplicationIntance, HWND hMainWindow)
  {      
    //-----------------------------------------------------------------------//
    // Create and set a bool to hold the return value for this method
    bool bReturnValue = true;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // Uninitialize in devices they may already be initialized
    this->Uninitialize();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // Create the interface to DirectInput
    long lResult = DirectInput8Create(hApplicationIntance,
                       DIRECTINPUT_VERSION,
                       IID_IDirectInput8,
                       reinterpret_cast<void**>(&mpDirectInput),
                       0);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // If we successfully created an interface to DirectInput...
    if(lResult == DI_OK)
    {
      //---------------------------------------------------------------------//
      // ... initialize all devices in the device vector.  If any of those 
      // devices return false set the return bool to false 
      for(int i = 0; i < mvDevices.size(); i++)
      {
        if(!mvDevices[i]->Initialize(mpDirectInput, hMainWindow) && bReturnValue)
          bReturnValue = false;
      }
      //---------------------------------------------------------------------//

      //---------------------------------------------------------------------//
      // All done. Return a bool that is true if all devices successfully 
      // initialized
      return bReturnValue;
      //---------------------------------------------------------------------//
    }
    //-----------------------------------------------------------------------//
    else // ... otherwise return false
      return false;
    //-----------------------------------------------------------------------//
  } // End of bool Input::Initialize(HINSTANCE hApplicationIntance, HWND hMainWindow)
  //*************************************************************************//

  //*************************************************************************//
  // Public
  // This method will release the DirectInput interface and uninitialize all 
  // devices in the mvDevices vector
  void Input::Uninitialize()
  {
    //-----------------------------------------------------------------------//
    // If we created the interface to DirectInput we need to delete it
    if(this->mpDirectInput)
      mpDirectInput->Release();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // Unintialize all devices in the device vector
    for(int i = 0; i < mvDevices.size(); i++)
    {
      mvDevices[i]->Uninitalize();
    }
    //-----------------------------------------------------------------------//
  } // End of void Input::Uninitialize()
  //*************************************************************************//

  //*************************************************************************//
  // Public
  // This method should be called once per program loop by the user of this 
  // library.  This method will update all the devices in the mvDevices vector
  // TODO: Consider making this concurrent and running it at a constant rate.
  void Input::Poll()
  {
    //-----------------------------------------------------------------------//
    // Poll all devices in the device vector
    for(int i = 0; i < mvDevices.size(); i++)
    {
      mvDevices[i]->Poll();
    }
    //-----------------------------------------------------------------------//
  } // End of void Input::Poll()
  //*************************************************************************//
} // End of namespace MST
//***************************************************************************//