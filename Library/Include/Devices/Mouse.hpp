//***************************************************************************//
// Mouse Class Interface
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

#ifndef MST_INPUT_MOUSE_HPP
#define MST_INPUT_MOUSE_HPP

//***************************************************************************//
#include "Devices\Device.hpp"
//***************************************************************************//

//***************************************************************************//
namespace MST
{
  //*************************************************************************//
  class Mouse : public Device
  {
  private:
    //***********************************************************************//
    //-----------------------------------------------------------------------//
    // These members are used to interface with the mouse using directinput.
    IDirectInputDevice8* mpMouse;
    DIMOUSESTATE2        mMouseState;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // These data members are need to keep track of the mouse position and 
    // any change in the mouse position.
    long mlCurrentPixel_X_Position;
    long mlCurrentPixel_Y_Position;
    long mlPreviousPixel_X_Position;
    long mlPreviousPixel_Y_Position;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // This member is need so that we can determine to location of the window
    // so we can give mouse position data relative to that window location.
    HWND mhMainWindow;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // These data members are needed to help calculate the position of the mouse
    // and to bind the mouse to the window handle defined above.
    long mlWidth;
    long mlHeight;
    long mlUpperLimit;
    long mlLowerLimit;
    long mlLeftLimit;
    long mlRightLimit;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // This method will center the mouse relative to the window.
    void Center();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // This method will should be called every time the windows position has changed
    // so that offsets for the mouse can be updated.
    // Parameter 1: The parameter is the current rectangle of the window.  If no
    //              rectangle is passed to this method, the method will make a windows
    //              call to find the dimensions and location of the window.
    void SetWindowPosition(RECT* pRectangle = NULL);
    //-----------------------------------------------------------------------//
    //***********************************************************************//
  public:
    //***********************************************************************//
    //-----------------------------------------------------------------------//
    // Constructor
    Mouse();
    // Desturctor
    // Note this destructor is not virtual. Do not derive from this class.
    ~Mouse();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // The below method uses a pointer from a the directinput interface to 
    // create and initialize communication with the mouse using directinput.  
    // This method also sets the mouse to be used via windows calls so that 
    // pixel position information can be provided by this class. This method 
    // is required by the Device base class.
    // Parameter 1: An established pointer to a directinput interface.
    // Parameter 2: A valid window handle to which mouse movements need to be tracked
    // Return Value: If the method was unable to setup directinput for the mouse
    //               this method will return false. Otherwise it will return true.
    //               We assume that we can always use the mouse windows calls.
    bool Initialize(IDirectInput8* pDirectInput, HWND hMainWindow) override;
    // The below method will uninitialize and release the mouse from directinput.
    // This method is required by the Device base class.
    // Return Value: This method will return true if the release and uninitialization
    //               was successful. Otherwise it will return false.
    bool Uninitialize();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // The below methods get the delta for their respective basis vector that is
    // reported by direct input.
    // Return Value: The delta/change in position the mouse moved. 
    float Direct_DX() const;
    float Direct_DY() const;
    float Direct_DZ() const;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // The below methods get the delta for their respective basis vector that is
    // reported by windows in units of pixels.
    // Return Value: The delta/change in position the mouse moved in pixels.
    long Pixel_DX_Position() const;
    long Pixel_DY_Position() const;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // The below methods get the relative (to the current windows) position 
    // for their respective basis vector that is reported by windows in units 
    // of pixels.
    // Return Value: The relative in position the mouse moved in pixels
    long Pixel_X_Position() const;
    long Pixel_Y_Position() const;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // This is method is required to poll the mouse and should be called once per
    // program loop.  This method is required by the Device base class.
    void Poll();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // Currently this method does nothing.  A better name would be SetCursorImage
    // TODO: Implement this method
    bool SetCursor(std::string strFileName);
    //-----------------------------------------------------------------------//
    //***********************************************************************//
  }; // End of class Mouse : public Device
  //*************************************************************************//
} // End of namespace MST
//***************************************************************************//

#endif MST_INPUT_MOUSE_HPP
