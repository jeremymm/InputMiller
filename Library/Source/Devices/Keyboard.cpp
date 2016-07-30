//***************************************************************************//
// Keyboard Class Implementation
//
// Created Sept 13, 2006
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
#include "Devices\Keyboard.hpp"
//***************************************************************************//

//***************************************************************************//
namespace MST
{
  //*************************************************************************//
  Keyboard::Keyboard()
  {
  }
  //*************************************************************************//

  //*************************************************************************//
  Keyboard::~Keyboard()
  {
  }
  //*************************************************************************//

  //*************************************************************************//
  // Public
  // The below method uses a pointer from a the directinput interface to 
  // create and initialize communication with the keyboard using directinput.  
  // This method also sets cooperation level for the window. This method 
  // is required by the Device base class.
  // Parameter 1: An established pointer to a directinput interface.
  // Parameter 2: A valid window handle so we know when the windows is in focus
  //              and therefore know if we should capture the state of the device.
  // Return Value: If the method was unable to setup directinput for the mouse
  //               this method will return false. Otherwise it will return true.
  //               We assume that we can always use the mouse windows calls.
  bool Keyboard::Initialize(IDirectInput8* pDirectInput, HWND hMainWindow)
  {
    //-----------------------------------------------------------------------//
    // Clear the current state of the keyboard
    memset(mcaKeyBoardState, 0L, sizeof(mcaKeyBoardState));
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // Create device
    pDirectInput->CreateDevice(GUID_SysKeyboard, &mpKeyBoard, 0);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // Set Data Format
    mpKeyBoard->SetDataFormat(&c_dfDIKeyboard);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // Set cooperation level
    mpKeyBoard->SetCooperativeLevel(hMainWindow, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // Aquire Device
    long lResult = mpKeyBoard->Acquire();
    if(lResult == DI_OK)
      return true;
    return false;
    //-----------------------------------------------------------------------//
  } // End of bool Keyboard::Initialize(IDirectInput8* pDirectInput, HWND hMainWindow)
  //*************************************************************************//

  //*************************************************************************//
  // The below method will uninitialize and release the keyboard from directinput.
  // This method is required by the Device base class.
  // Return Value: This method will return true if the release and uninitialization
  //               was sucessful. Otherwise it will return false.
  bool Keyboard::Uninitialize()
  {
    //-----------------------------------------------------------------------//
    // If the we attained a valid pointer for the keyboard via directinput...
    if(this->mpKeyBoard)
    {
      //---------------------------------------------------------------------//
      // ... release the keyboard.
      long lResult = this->mpKeyBoard->Unacquire();
      this->mpKeyBoard->Release();
      //---------------------------------------------------------------------//

      //---------------------------------------------------------------------//
      // If we sucessfully released the keyboard return true. Otherwise return false.
      if(lResult == DI_OK)
        return true;
      //---------------------------------------------------------------------//
    }
    //-----------------------------------------------------------------------//
       
    //-----------------------------------------------------------------------//
    // We can only get here if we failed to release the keyboard from directinput.
    // In that case return false.
    return false;
    //-----------------------------------------------------------------------//
  } // End of bool Keyboard::Uninitialize()
  //*************************************************************************//

  //*************************************************************************//
  // This is method is required to poll the mouse and should be called once per
  // program loop.  This method is required by the Device base class.
  void Keyboard::Poll()
  {
    //-----------------------------------------------------------------------//
    // Attempt to get the state of the device and update this objects array of 
    // keys.
    long lResult = this->mpKeyBoard->GetDeviceState(sizeof(mcaKeyBoardState),
      reinterpret_cast<void**>(&mcaKeyBoardState));
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    //DIDEVICEOBJECTDATA rgdod[10]; 
    //DWORD dwItems = 10; 
    //long hres = this->mpKeyBoard->GetDeviceData( 
    //  sizeof(DIDEVICEOBJECTDATA), 
    //  rgdod, 
     // &dwItems, 
     // 0); 
    //if (SUCCEEDED(hres)) { 
      // dwItems = Number of elements read (could be zero).
     // if (hres == DI_BUFFEROVERFLOW) { 
        // Buffer had overflowed. 
      //} 
    //} 
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // If the attempt to get the state failed or we have otherwise lost the 
    // the keyboard device then try to reacquire it.
    if(lResult != DI_OK)
    {
      memset(mcaKeyBoardState, 0L, sizeof(mcaKeyBoardState));
      mpKeyBoard->Acquire();
    }
    //-----------------------------------------------------------------------//
  } // End of void Keyboard::Poll()
  //*************************************************************************//
}
//***************************************************************************//


