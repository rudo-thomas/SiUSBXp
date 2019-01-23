#ifndef SIUSBXP_H_INCLUDED
#define SIUSBXP_H_INCLUDED
/**************************************************************************
 *   SiUSBXp.h                                                            *
 *                                                                        *
 *   This library provides an API compatible with SiUSBXp.dll supplied    *
 *   with SiLabs USBXpress, except that this library has a libusb         *
 *   back-end and is therefore cross-platform (including Linux).          *
 *   This library has been proven to function correctly with .NET         *
 *   applications running under MONO.                                     *
 *   This implementation is incomplete, however the most commonly used    *
 *   functions are implemented.                                           *
 *                                                                        *
 *   Home Page:                                                           *
 *   http://www.etheus.net/SiUSBXp_Linux_Driver                           *
 *                                                                        *
 *   Compile with:                                                        *
 *   gcc -shared -lusb -o libSiUSBXp.so SiUSBXp.c -Wall -fPIC             *
 *                                                                        *
 *   Copyright (C) 2010 Craig Shelley <craig@microtron.org.uk>            *
 *   This program is free software; you can redistribute it and/or modify *
 *   it under the terms of the GNU General Public License as published by *
 *   the Free Software Foundation; either version 2, or (at your option)  *
 *   any later version.                                                   *
 *                                                                        *
 *   This program is distributed in the hope that it will be useful,      *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
 *   GNU General Public License for more details.                         *
 *                                                                        *
 *   You should have received a copy of the GNU General Public License    *
 *   along with this program; if not, write to the Free Software          *
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.            *
 *                                                                        *
 *   Credits:                                                             *
 *   Many thanks to Michael Heubeck for all of the testing, debugging     * 
 *   feedback, and for the original project idea.                         *
 *                                                                        *
 *   Version History:                                                     *
 *               2019-01       Additional cosmetic work by                *
 *                             Rudo Thomas <rudo.thomas@gmail.com>        *
 *   0.01        2010-10-20    Initial release                            *
 *                             Craig Shelley <craig@microtron.org.uk>     *
 *                                                                        *
 **************************************************************************/


/*Return codes*/
#define		SI_SUCCESS                      0x00
#define		SI_DEVICE_NOT_FOUND             0xFF
#define		SI_INVALID_HANDLE               0x01
#define		SI_READ_ERROR                   0x02
#define		SI_RX_QUEUE_NOT_READY           0x03
#define		SI_WRITE_ERROR                  0x04
#define		SI_RESET_ERROR                  0x05
#define		SI_INVALID_PARAMETER            0x06
#define		SI_INVALID_REQUEST_LENGTH       0x07
#define		SI_DEVICE_IO_FAILED             0x08
#define		SI_INVALID_BAUDRATE             0x09
#define		SI_FUNCTION_NOT_SUPPORTED       0x0a
#define		SI_GLOBAL_DATA_ERROR            0x0b
#define		SI_SYSTEM_ERROR_CODE            0x0c
#define		SI_READ_TIMED_OUT               0x0d
#define		SI_WRITE_TIMED_OUT              0x0e
#define		SI_IO_PENDING                   0x0f

/*GetProductString() function flags*/
#define		SI_RETURN_SERIAL_NUMBER         0x00
#define		SI_RETURN_DESCRIPTION           0x01
#define		SI_RETURN_LINK_NAME             0x02
#define		SI_RETURN_VID                   0x03
#define		SI_RETURN_PID                   0x04

/*RX Queue status flags*/
#define		SI_RX_NO_OVERRUN                0x00
#define		SI_RX_EMPTY                     0x00
#define		SI_RX_OVERRUN                   0x01
#define		SI_RX_READY                     0x02

/*Buffer size limits*/
#define		SI_MAX_DEVICE_STRLEN            256
#define		SI_MAX_READ_SIZE                4096*16
#define		SI_MAX_WRITE_SIZE               4096


struct SI_Private;

int SI_GetNumDevices(int *NumDevices);
int SI_GetProductString(int DeviceNum, char * DeviceString, int Flags);
int SI_Open(int DeviceNum, struct SI_Private ** pHandle);
int SI_Close(struct SI_Private * Handle);
int SI_Read(struct SI_Private * Handle, char * Buffer, int BytesToRead, int * BytesReturned, void * o);
int SI_Write(struct SI_Private * Handle, char * Buffer, int BytesToWrite, int * BytesWritten, void * o);
int SI_ResetDevice(struct SI_Private * Handle);
int SI_DeviceIOControl(struct SI_Private * Handle, int IoControlCode, char * InBuffer, int BytesToRead, char * OutBuffer, int BytesToWrite);
int SI_FlushBuffers(struct SI_Private * Handle, char FlushTransmit, char FlushReceive);
int SI_SetTimeouts(int ReadTimeout, int WriteTimeout);
int SI_GetTimeouts(int *ReadTimeout, int *WriteTimeout);
int SI_CheckRXQueue(struct SI_Private * Handle, int *NumBytesInQueue, int *QueueStatus);

#endif
