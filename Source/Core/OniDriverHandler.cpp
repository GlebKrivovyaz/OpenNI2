/*****************************************************************************
*                                                                            *
*  OpenNI 2.x Alpha                                                          *
*  Copyright (C) 2012 PrimeSense Ltd.                                        *
*                                                                            *
*  This file is part of OpenNI.                                              *
*                                                                            *
*  Licensed under the Apache License, Version 2.0 (the "License");           *
*  you may not use this file except in compliance with the License.          *
*  You may obtain a copy of the License at                                   *
*                                                                            *
*      http://www.apache.org/licenses/LICENSE-2.0                            *
*                                                                            *
*  Unless required by applicable law or agreed to in writing, software       *
*  distributed under the License is distributed on an "AS IS" BASIS,         *
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  *
*  See the License for the specific language governing permissions and       *
*  limitations under the License.                                            *
*                                                                            *
*****************************************************************************/
#include "OniDriverHandler.h"
#include "OniDriverHeaders.h"
#include "XnLib.h"
#include <dlfcn.h>
#include <XnLog.h>

#define __GNU_SOURCE

#define OniGetProcAddress(function)																\
{																								\
	rc = xnOSGetProcAddress(m_libHandle, XN_STRINGIFY(function), (XnFarProc*)&funcs.function);	\
	if (rc != ONI_STATUS_OK)																	\
	{																							\
		xnLogWarning("DriverHandler", "LibraryHandler: Couldn't find function %s in %s. Stopping", XN_STRINGIFY(function), library);	\
		errorLogger.Append("LibraryHandler: Couldn't find function %s in %s. Stopping", XN_STRINGIFY(function), library);		\
		return;																					\
	}																							\
}

ONI_NAMESPACE_IMPLEMENTATION_BEGIN

DriverHandler::DriverHandler(const char* library, xnl::ErrorLogger& errorLogger)
{
	m_valid = false;
	xnLogInfo("DriverHandler", "LibraryHandler: Loading library %s", library);
	xnOSMemSet(&funcs, 0, sizeof(funcs));

	bool isStatic = false;
	// extension of .a indicates a static object
	if (library[strlen(library) - 1] == 'a') {
		isStatic = true;
	}

	if (isStatic) {

    xnLogInfo("DriverHandler", "Detected Static library build for lib %s.", library);

		m_libHandle = NULL;

		if (!(strcmp("libPS1080.a", library))) {

			funcs.oniDriverCreate                                 = &XnOniDriveroniDriverCreate;
			funcs.oniDriverDestroy                                = &XnOniDriveroniDriverDestroy;
			funcs.oniDriverInitialize                             = &XnOniDriveroniDriverInitialize;
			funcs.oniDriverTryDevice                              = &XnOniDriveroniDriverTryDevice;
			funcs.oniDriverDeviceOpen                             = &XnOniDriveroniDriverDeviceOpen;
			funcs.oniDriverDeviceClose                            = &XnOniDriveroniDriverDeviceClose;
			funcs.oniDriverDeviceGetSensorInfoList                = &XnOniDriveroniDriverDeviceGetSensorInfoList;
			funcs.oniDriverDeviceCreateStream                     = &XnOniDriveroniDriverDeviceCreateStream;
			funcs.oniDriverDeviceDestroyStream                    = &XnOniDriveroniDriverDeviceDestroyStream;
			funcs.oniDriverDeviceSetProperty                      = &XnOniDriveroniDriverDeviceSetProperty;
			funcs.oniDriverDeviceGetProperty                      = &XnOniDriveroniDriverDeviceGetProperty;
			funcs.oniDriverDeviceIsPropertySupported              = &XnOniDriveroniDriverDeviceIsPropertySupported;
			funcs.oniDriverDeviceSetPropertyChangedCallback       = &XnOniDriveroniDriverDeviceSetPropertyChangedCallback;
			funcs.oniDriverDeviceNotifyAllProperties              = &XnOniDriveroniDriverDeviceNotifyAllProperties;
			funcs.oniDriverDeviceInvoke                           = &XnOniDriveroniDriverDeviceInvoke;
			funcs.oniDriverDeviceIsCommandSupported               = &XnOniDriveroniDriverDeviceIsCommandSupported;
			funcs.oniDriverDeviceIsImageRegistrationModeSupported = &XnOniDriveroniDriverDeviceIsImageRegistrationModeSupported;
			funcs.oniDriverDeviceTryManualTrigger                 = &XnOniDriveroniDriverDeviceTryManualTrigger;
			funcs.oniDriverStreamSetServices                      = &XnOniDriveroniDriverStreamSetServices;
			funcs.oniDriverStreamSetProperty                      = &XnOniDriveroniDriverStreamSetProperty;
			funcs.oniDriverStreamGetProperty                      = &XnOniDriveroniDriverStreamGetProperty;
			funcs.oniDriverStreamIsPropertySupported              = &XnOniDriveroniDriverStreamIsPropertySupported;
			funcs.oniDriverStreamSetPropertyChangedCallback       = &XnOniDriveroniDriverStreamSetPropertyChangedCallback;
			funcs.oniDriverStreamNotifyAllProperties              = &XnOniDriveroniDriverStreamNotifyAllProperties;
			funcs.oniDriverStreamInvoke                           = &XnOniDriveroniDriverStreamInvoke;
			funcs.oniDriverStreamIsCommandSupported               = &XnOniDriveroniDriverStreamIsCommandSupported;
			funcs.oniDriverStreamStart                            = &XnOniDriveroniDriverStreamStart;
			funcs.oniDriverStreamStop                             = &XnOniDriveroniDriverStreamStop;
			funcs.oniDriverStreamGetRequiredFrameSize             = &XnOniDriveroniDriverStreamGetRequiredFrameSize;
			funcs.oniDriverStreamSetNewFrameCallback              = &XnOniDriveroniDriverStreamSetNewFrameCallback;
			funcs.oniDriverStreamConvertDepthToColorCoordinates   = &XnOniDriveroniDriverStreamConvertDepthToColorCoordinates;
			funcs.oniDriverEnableFrameSync                        = &XnOniDriveroniDriverEnableFrameSync;
			funcs.oniDriverDisableFrameSync                       = &XnOniDriveroniDriverDisableFrameSync;

		} else if (!(strcmp("libOniFile.a", library))) {

			funcs.oniDriverCreate                                 = &PlayerDriveroniDriverCreate;
			funcs.oniDriverDestroy                                = &PlayerDriveroniDriverDestroy;
			funcs.oniDriverInitialize                             = &PlayerDriveroniDriverInitialize;
			funcs.oniDriverTryDevice                              = &PlayerDriveroniDriverTryDevice;
			funcs.oniDriverDeviceOpen                             = &PlayerDriveroniDriverDeviceOpen;
			funcs.oniDriverDeviceClose                            = &PlayerDriveroniDriverDeviceClose;
			funcs.oniDriverDeviceGetSensorInfoList                = &PlayerDriveroniDriverDeviceGetSensorInfoList;
			funcs.oniDriverDeviceCreateStream                     = &PlayerDriveroniDriverDeviceCreateStream;
			funcs.oniDriverDeviceDestroyStream                    = &PlayerDriveroniDriverDeviceDestroyStream;
			funcs.oniDriverDeviceSetProperty                      = &PlayerDriveroniDriverDeviceSetProperty;
			funcs.oniDriverDeviceGetProperty                      = &PlayerDriveroniDriverDeviceGetProperty;
			funcs.oniDriverDeviceIsPropertySupported              = &PlayerDriveroniDriverDeviceIsPropertySupported;
			funcs.oniDriverDeviceSetPropertyChangedCallback       = &PlayerDriveroniDriverDeviceSetPropertyChangedCallback;
			funcs.oniDriverDeviceNotifyAllProperties              = &PlayerDriveroniDriverDeviceNotifyAllProperties;
			funcs.oniDriverDeviceInvoke                           = &PlayerDriveroniDriverDeviceInvoke;
			funcs.oniDriverDeviceIsCommandSupported               = &PlayerDriveroniDriverDeviceIsCommandSupported;
			funcs.oniDriverDeviceIsImageRegistrationModeSupported = &PlayerDriveroniDriverDeviceIsImageRegistrationModeSupported;
			funcs.oniDriverDeviceTryManualTrigger                 = &PlayerDriveroniDriverDeviceTryManualTrigger;
			funcs.oniDriverStreamSetServices                      = &PlayerDriveroniDriverStreamSetServices;
			funcs.oniDriverStreamSetProperty                      = &PlayerDriveroniDriverStreamSetProperty;
			funcs.oniDriverStreamGetProperty                      = &PlayerDriveroniDriverStreamGetProperty;
			funcs.oniDriverStreamIsPropertySupported              = &PlayerDriveroniDriverStreamIsPropertySupported;
			funcs.oniDriverStreamSetPropertyChangedCallback       = &PlayerDriveroniDriverStreamSetPropertyChangedCallback;
			funcs.oniDriverStreamNotifyAllProperties              = &PlayerDriveroniDriverStreamNotifyAllProperties;
			funcs.oniDriverStreamInvoke                           = &PlayerDriveroniDriverStreamInvoke;
			funcs.oniDriverStreamIsCommandSupported               = &PlayerDriveroniDriverStreamIsCommandSupported;
			funcs.oniDriverStreamStart                            = &PlayerDriveroniDriverStreamStart;
			funcs.oniDriverStreamStop                             = &PlayerDriveroniDriverStreamStop;
			funcs.oniDriverStreamGetRequiredFrameSize             = &PlayerDriveroniDriverStreamGetRequiredFrameSize;
			funcs.oniDriverStreamSetNewFrameCallback              = &PlayerDriveroniDriverStreamSetNewFrameCallback;
			funcs.oniDriverStreamConvertDepthToColorCoordinates   = &PlayerDriveroniDriverStreamConvertDepthToColorCoordinates;
			funcs.oniDriverEnableFrameSync                        = &PlayerDriveroniDriverEnableFrameSync;
			funcs.oniDriverDisableFrameSync                       = &PlayerDriveroniDriverDisableFrameSync;

		} else if (!(strcmp("libPSLink.a", library))) {

			funcs.oniDriverCreate                                 = &LinkOniDriveroniDriverCreate;
			funcs.oniDriverDestroy                                = &LinkOniDriveroniDriverDestroy;
			funcs.oniDriverInitialize                             = &LinkOniDriveroniDriverInitialize;
			funcs.oniDriverTryDevice                              = &LinkOniDriveroniDriverTryDevice;
			funcs.oniDriverDeviceOpen                             = &LinkOniDriveroniDriverDeviceOpen;
			funcs.oniDriverDeviceClose                            = &LinkOniDriveroniDriverDeviceClose;
			funcs.oniDriverDeviceGetSensorInfoList                = &LinkOniDriveroniDriverDeviceGetSensorInfoList;
			funcs.oniDriverDeviceCreateStream                     = &LinkOniDriveroniDriverDeviceCreateStream;
			funcs.oniDriverDeviceDestroyStream                    = &LinkOniDriveroniDriverDeviceDestroyStream;
			funcs.oniDriverDeviceSetProperty                      = &LinkOniDriveroniDriverDeviceSetProperty;
			funcs.oniDriverDeviceGetProperty                      = &LinkOniDriveroniDriverDeviceGetProperty;
			funcs.oniDriverDeviceIsPropertySupported              = &LinkOniDriveroniDriverDeviceIsPropertySupported;
			funcs.oniDriverDeviceSetPropertyChangedCallback       = &LinkOniDriveroniDriverDeviceSetPropertyChangedCallback;
			funcs.oniDriverDeviceNotifyAllProperties              = &LinkOniDriveroniDriverDeviceNotifyAllProperties;
			funcs.oniDriverDeviceInvoke                           = &LinkOniDriveroniDriverDeviceInvoke;
			funcs.oniDriverDeviceIsCommandSupported               = &LinkOniDriveroniDriverDeviceIsCommandSupported;
			funcs.oniDriverDeviceIsImageRegistrationModeSupported = &LinkOniDriveroniDriverDeviceIsImageRegistrationModeSupported;
			funcs.oniDriverDeviceTryManualTrigger                 = &LinkOniDriveroniDriverDeviceTryManualTrigger;
			funcs.oniDriverStreamSetServices                      = &LinkOniDriveroniDriverStreamSetServices;
			funcs.oniDriverStreamSetProperty                      = &LinkOniDriveroniDriverStreamSetProperty;
			funcs.oniDriverStreamGetProperty                      = &LinkOniDriveroniDriverStreamGetProperty;
			funcs.oniDriverStreamIsPropertySupported              = &LinkOniDriveroniDriverStreamIsPropertySupported;
			funcs.oniDriverStreamSetPropertyChangedCallback       = &LinkOniDriveroniDriverStreamSetPropertyChangedCallback;
			funcs.oniDriverStreamNotifyAllProperties              = &LinkOniDriveroniDriverStreamNotifyAllProperties;
			funcs.oniDriverStreamInvoke                           = &LinkOniDriveroniDriverStreamInvoke;
			funcs.oniDriverStreamIsCommandSupported               = &LinkOniDriveroniDriverStreamIsCommandSupported;
			funcs.oniDriverStreamStart                            = &LinkOniDriveroniDriverStreamStart;
			funcs.oniDriverStreamStop                             = &LinkOniDriveroniDriverStreamStop;
			funcs.oniDriverStreamGetRequiredFrameSize             = &LinkOniDriveroniDriverStreamGetRequiredFrameSize;
			funcs.oniDriverStreamSetNewFrameCallback              = &LinkOniDriveroniDriverStreamSetNewFrameCallback;
			funcs.oniDriverStreamConvertDepthToColorCoordinates   = &LinkOniDriveroniDriverStreamConvertDepthToColorCoordinates;
			funcs.oniDriverEnableFrameSync                        = &LinkOniDriveroniDriverEnableFrameSync;
			funcs.oniDriverDisableFrameSync                       = &LinkOniDriveroniDriverDisableFrameSync;

		} else if (!(strcmp("libDummyDevice.a", library))) {

			// funcs.oniDriverCreate                                 = &OzDriveroniDriverCreate;
			// funcs.oniDriverDestroy                                = &OzDriveroniDriverDestroy;
			// funcs.oniDriverInitialize                             = &OzDriveroniDriverInitialize;
			// funcs.oniDriverTryDevice                              = &OzDriveroniDriverTryDevice;
			// funcs.oniDriverDeviceOpen                             = &OzDriveroniDriverDeviceOpen;
			// funcs.oniDriverDeviceClose                            = &OzDriveroniDriverDeviceClose;
			// funcs.oniDriverDeviceGetSensorInfoList                = &OzDriveroniDriverDeviceGetSensorInfoList;
			// funcs.oniDriverDeviceCreateStream                     = &OzDriveroniDriverDeviceCreateStream;
			// funcs.oniDriverDeviceDestroyStream                    = &OzDriveroniDriverDeviceDestroyStream;
			// funcs.oniDriverDeviceSetProperty                      = &OzDriveroniDriverDeviceSetProperty;
			// funcs.oniDriverDeviceGetProperty                      = &OzDriveroniDriverDeviceGetProperty;
			// funcs.oniDriverDeviceIsPropertySupported              = &OzDriveroniDriverDeviceIsPropertySupported;
			// funcs.oniDriverDeviceSetPropertyChangedCallback       = &OzDriveroniDriverDeviceSetPropertyChangedCallback;
			// funcs.oniDriverDeviceNotifyAllProperties              = &OzDriveroniDriverDeviceNotifyAllProperties;
			// funcs.oniDriverDeviceInvoke                           = &OzDriveroniDriverDeviceInvoke;
			// funcs.oniDriverDeviceIsCommandSupported               = &OzDriveroniDriverDeviceIsCommandSupported;
			// funcs.oniDriverDeviceIsImageRegistrationModeSupported = &OzDriveroniDriverDeviceIsImageRegistrationModeSupported;
			// funcs.oniDriverDeviceTryManualTrigger                 = &OzDriveroniDriverDeviceTryManualTrigger;
			// funcs.oniDriverStreamSetServices                      = &OzDriveroniDriverStreamSetServices;
			// funcs.oniDriverStreamSetProperty                      = &OzDriveroniDriverStreamSetProperty;
			// funcs.oniDriverStreamGetProperty                      = &OzDriveroniDriverStreamGetProperty;
			// funcs.oniDriverStreamIsPropertySupported              = &OzDriveroniDriverStreamIsPropertySupported;
			// funcs.oniDriverStreamSetPropertyChangedCallback       = &OzDriveroniDriverStreamSetPropertyChangedCallback;
			// funcs.oniDriverStreamNotifyAllProperties              = &OzDriveroniDriverStreamNotifyAllProperties;
			// funcs.oniDriverStreamInvoke                           = &OzDriveroniDriverStreamInvoke;
			// funcs.oniDriverStreamIsCommandSupported               = &OzDriveroniDriverStreamIsCommandSupported;
			// funcs.oniDriverStreamStart                            = &OzDriveroniDriverStreamStart;
			// funcs.oniDriverStreamStop                             = &OzDriveroniDriverStreamStop;
			// funcs.oniDriverStreamGetRequiredFrameSize             = &OzDriveroniDriverStreamGetRequiredFrameSize;
			// funcs.oniDriverStreamSetNewFrameCallback              = &OzDriveroniDriverStreamSetNewFrameCallback;
			// funcs.oniDriverStreamConvertDepthToColorCoordinates   = &OzDriveroniDriverStreamConvertDepthToColorCoordinates;
			// funcs.oniDriverEnableFrameSync                        = &OzDriveroniDriverEnableFrameSync;
			// funcs.oniDriverDisableFrameSync                       = &OzDriveroniDriverDisableFrameSync;

		} else {
			errorLogger.Append("LibraryHandler: Couldn't load library %s", library);
			return;
		}

	} else {

		XnStatus rc = xnOSLoadLibrary(library, &m_libHandle);
		if (rc != XN_STATUS_OK)
		{
			errorLogger.Append("LibraryHandler: Couldn't load library %s", library);
			return;
		}

		OniGetProcAddress(oniDriverCreate);
		OniGetProcAddress(oniDriverDestroy);
		OniGetProcAddress(oniDriverInitialize);
		OniGetProcAddress(oniDriverTryDevice);

		OniGetProcAddress(oniDriverDeviceOpen);
		OniGetProcAddress(oniDriverDeviceClose);
		OniGetProcAddress(oniDriverDeviceGetSensorInfoList);

		OniGetProcAddress(oniDriverDeviceCreateStream);
		OniGetProcAddress(oniDriverDeviceDestroyStream);
		OniGetProcAddress(oniDriverDeviceSetProperty);
		OniGetProcAddress(oniDriverDeviceGetProperty);
		OniGetProcAddress(oniDriverDeviceIsPropertySupported);
		OniGetProcAddress(oniDriverDeviceSetPropertyChangedCallback);
		OniGetProcAddress(oniDriverDeviceNotifyAllProperties);
		OniGetProcAddress(oniDriverDeviceInvoke);
		OniGetProcAddress(oniDriverDeviceIsCommandSupported);
		OniGetProcAddress(oniDriverDeviceIsImageRegistrationModeSupported);
		OniGetProcAddress(oniDriverDeviceTryManualTrigger);

		OniGetProcAddress(oniDriverStreamSetServices);
		OniGetProcAddress(oniDriverStreamSetProperty);
		OniGetProcAddress(oniDriverStreamGetProperty);
		OniGetProcAddress(oniDriverStreamIsPropertySupported);
		OniGetProcAddress(oniDriverStreamSetPropertyChangedCallback);
		OniGetProcAddress(oniDriverStreamNotifyAllProperties);
		OniGetProcAddress(oniDriverStreamInvoke);
		OniGetProcAddress(oniDriverStreamIsCommandSupported);
		OniGetProcAddress(oniDriverStreamStart);
		OniGetProcAddress(oniDriverStreamStop);
		OniGetProcAddress(oniDriverStreamGetRequiredFrameSize);
		OniGetProcAddress(oniDriverStreamSetNewFrameCallback);
		OniGetProcAddress(oniDriverStreamConvertDepthToColorCoordinates);

		OniGetProcAddress(oniDriverEnableFrameSync);
		OniGetProcAddress(oniDriverDisableFrameSync);
	}

	m_valid = true;
}

DriverHandler::~DriverHandler()
{
	if (m_valid && m_libHandle)
	{
		xnOSFreeLibrary(m_libHandle);
		m_libHandle = NULL;
	}
	m_valid = false;
}

ONI_NAMESPACE_IMPLEMENTATION_END
