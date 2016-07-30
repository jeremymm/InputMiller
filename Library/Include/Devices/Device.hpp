//***************************************************************************//
// Device Class Interface
//
// Created Sept 27, 2006
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

#ifndef MST_INPUT_DEVICE_HPP
#define MST_INPUT_DEVICE_HPP

//***************************************************************************//
#include "InputMiller.hpp"
//***************************************************************************//

//***************************************************************************//
namespace MST
{
  //*************************************************************************//
  // This class is the base class for all input devices
  class Device
  {
  private:
    //***********************************************************************//
    //***********************************************************************//
  public:
    //***********************************************************************//
    //-----------------------------------------------------------------------//
    Device();
    virtual ~Device();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // All input devices need these methods. The implemenation of the devices
    // in Devices.cpp currently does nothing
    virtual bool Initialize(IDirectInput8* pDirectInput, HWND hMainWindow);
    virtual bool Uninitalize();

    virtual void Poll();
    //-----------------------------------------------------------------------//
    //***********************************************************************//
  }; // End of class Device
  //*************************************************************************//
} // End of namespace MST
//***************************************************************************//

#endif MST_INPUT_DEVICE_HPP
