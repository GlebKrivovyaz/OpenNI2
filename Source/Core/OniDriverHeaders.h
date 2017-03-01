#ifndef __ONI_HEADERS_
#define __ONI_HEADERS_

typedef void (ONI_CALLBACK_TYPE* OniDriverDeviceConnected)(const OniDeviceInfo*, void* pCookie);
typedef void (ONI_CALLBACK_TYPE* OniDriverDeviceDisconnected)(const OniDeviceInfo*, void* pCookie);
typedef void (ONI_CALLBACK_TYPE* OniDriverDeviceStateChanged)(const OniDeviceInfo*, OniDeviceState, void* pCookie);

typedef void (ONI_CALLBACK_TYPE* OniDriverNewFrame)(void* streamHandle, OniFrame*, void* pCookie);
typedef void (ONI_CALLBACK_TYPE* OniDriverPropertyChanged)(void* sender, int propertyId, const void* data, int dataSize, void* pCookie);

extern "C" {

//
// PS1080
// 

// As Driver
void (ONI_C_DECL XnOniDriveroniDriverCreate)(OniDriverServices* driverServices);
void (ONI_C_DECL XnOniDriveroniDriverDestroy)();
OniStatus (ONI_C_DECL XnOniDriveroniDriverInitialize)(OniDriverDeviceConnected connectedCallback, OniDriverDeviceDisconnected disconnectedCallback,
                                              OniDriverDeviceStateChanged deviceStateChangedCallback, void* pCookie);
void (ONI_C_DECL XnOniDriveroniDriverRun)();

OniStatus (ONI_C_DECL XnOniDriveroniDriverTryDevice)(const char* uri);

// As Device
void* (ONI_C_DECL XnOniDriveroniDriverDeviceOpen)(const char* uri, const char* mode);
void (ONI_C_DECL XnOniDriveroniDriverDeviceClose)(void* deviceHandle);

OniStatus (ONI_C_DECL XnOniDriveroniDriverDeviceGetSensorInfoList)(void* deviceHandle, OniSensorInfo** pSensors, int* numSensors);

void* (ONI_C_DECL XnOniDriveroniDriverDeviceCreateStream)(void* deviceHandle, OniSensorType sensorType);
void (ONI_C_DECL XnOniDriveroniDriverDeviceDestroyStream)(void* deviceHandle, void* streamHandle);

OniStatus (ONI_C_DECL XnOniDriveroniDriverDeviceSetProperty)(void* deviceHandle, int propertyId, const void* data, int dataSize);
OniStatus (ONI_C_DECL XnOniDriveroniDriverDeviceGetProperty)(void* deviceHandle, int propertyId, void* data, int* pDataSize);
OniBool (ONI_C_DECL XnOniDriveroniDriverDeviceIsPropertySupported)(void* deviceHandle, int propertyId);
void (ONI_C_DECL XnOniDriveroniDriverDeviceSetPropertyChangedCallback)(void* deviceHandle, OniDriverPropertyChanged handler, void* pCookie);
void (ONI_C_DECL XnOniDriveroniDriverDeviceNotifyAllProperties)(void* deviceHandle);
OniStatus (ONI_C_DECL XnOniDriveroniDriverDeviceInvoke)(void* deviceHandle, int commandId, const void* data, int dataSize);
OniBool (ONI_C_DECL XnOniDriveroniDriverDeviceIsCommandSupported)(void* deviceHandle, int commandId);
OniStatus (ONI_C_DECL XnOniDriveroniDriverDeviceTryManualTrigger)(void* deviceHandle);
OniBool (ONI_C_DECL XnOniDriveroniDriverDeviceIsImageRegistrationModeSupported)(void* deviceHandle, OniImageRegistrationMode mode);

// As Stream
void (ONI_C_DECL XnOniDriveroniDriverStreamSetServices)(void* streamHandle, OniStreamServices* pServices);
OniStatus (ONI_C_DECL XnOniDriveroniDriverStreamSetProperty)(void* streamHandle, int propertyId, const void* data, int dataSize);
OniStatus (ONI_C_DECL XnOniDriveroniDriverStreamGetProperty)(void* streamHandle, int propertyId, void* data, int* pDataSize);
OniBool (ONI_C_DECL XnOniDriveroniDriverStreamIsPropertySupported)(void* streamHandle, int propertyId);
void (ONI_C_DECL XnOniDriveroniDriverStreamSetPropertyChangedCallback)(void* streamHandle, OniDriverPropertyChanged handler, void* pCookie);
void (ONI_C_DECL XnOniDriveroniDriverStreamNotifyAllProperties)(void* streamHandle);
OniStatus (ONI_C_DECL XnOniDriveroniDriverStreamInvoke)(void* streamHandle, int commandId, const void* data, int dataSize);
OniBool (ONI_C_DECL XnOniDriveroniDriverStreamIsCommandSupported)(void* streamHandle, int commandId);

OniStatus (ONI_C_DECL XnOniDriveroniDriverStreamStart)(void* streamHandle);
void (ONI_C_DECL XnOniDriveroniDriverStreamStop)(void* streamHandle);

int (ONI_C_DECL XnOniDriveroniDriverStreamGetRequiredFrameSize)(void* streamHandle);

void (ONI_C_DECL XnOniDriveroniDriverStreamSetNewFrameCallback)(void* streamHandle, OniDriverNewFrame handler, void* pCookie);
OniStatus (ONI_C_DECL XnOniDriveroniDriverStreamConvertDepthToColorCoordinates)(void* depthStreamHandle, void* colorStreamHandle, int depthX, int depthY, OniDepthPixel depthZ, int* pColorX, int* pColorY);

void* (ONI_C_DECL XnOniDriveroniDriverEnableFrameSync)(void** pStreamHandles, int streamCount);
void (ONI_C_DECL XnOniDriveroniDriverDisableFrameSync)(void* frameSyncGroup);

//
// PSlibOniFile
// 

// As Driver
void (ONI_C_DECL PlayerDriveroniDriverCreate)(OniDriverServices* driverServices);
void (ONI_C_DECL PlayerDriveroniDriverDestroy)();
OniStatus (ONI_C_DECL PlayerDriveroniDriverInitialize)(OniDriverDeviceConnected connectedCallback, OniDriverDeviceDisconnected disconnectedCallback,
                                              OniDriverDeviceStateChanged deviceStateChangedCallback, void* pCookie);
void (ONI_C_DECL PlayerDriveroniDriverRun)();

OniStatus (ONI_C_DECL PlayerDriveroniDriverTryDevice)(const char* uri);

// As Device
void* (ONI_C_DECL PlayerDriveroniDriverDeviceOpen)(const char* uri, const char* mode);
void (ONI_C_DECL PlayerDriveroniDriverDeviceClose)(void* deviceHandle);

OniStatus (ONI_C_DECL PlayerDriveroniDriverDeviceGetSensorInfoList)(void* deviceHandle, OniSensorInfo** pSensors, int* numSensors);

void* (ONI_C_DECL PlayerDriveroniDriverDeviceCreateStream)(void* deviceHandle, OniSensorType sensorType);
void (ONI_C_DECL PlayerDriveroniDriverDeviceDestroyStream)(void* deviceHandle, void* streamHandle);

OniStatus (ONI_C_DECL PlayerDriveroniDriverDeviceSetProperty)(void* deviceHandle, int propertyId, const void* data, int dataSize);
OniStatus (ONI_C_DECL PlayerDriveroniDriverDeviceGetProperty)(void* deviceHandle, int propertyId, void* data, int* pDataSize);
OniBool (ONI_C_DECL PlayerDriveroniDriverDeviceIsPropertySupported)(void* deviceHandle, int propertyId);
void (ONI_C_DECL PlayerDriveroniDriverDeviceSetPropertyChangedCallback)(void* deviceHandle, OniDriverPropertyChanged handler, void* pCookie);
void (ONI_C_DECL PlayerDriveroniDriverDeviceNotifyAllProperties)(void* deviceHandle);
OniStatus (ONI_C_DECL PlayerDriveroniDriverDeviceInvoke)(void* deviceHandle, int commandId, const void* data, int dataSize);
OniBool (ONI_C_DECL PlayerDriveroniDriverDeviceIsCommandSupported)(void* deviceHandle, int commandId);
OniStatus (ONI_C_DECL PlayerDriveroniDriverDeviceTryManualTrigger)(void* deviceHandle);
OniBool (ONI_C_DECL PlayerDriveroniDriverDeviceIsImageRegistrationModeSupported)(void* deviceHandle, OniImageRegistrationMode mode);

// As Stream
void (ONI_C_DECL PlayerDriveroniDriverStreamSetServices)(void* streamHandle, OniStreamServices* pServices);
OniStatus (ONI_C_DECL PlayerDriveroniDriverStreamSetProperty)(void* streamHandle, int propertyId, const void* data, int dataSize);
OniStatus (ONI_C_DECL PlayerDriveroniDriverStreamGetProperty)(void* streamHandle, int propertyId, void* data, int* pDataSize);
OniBool (ONI_C_DECL PlayerDriveroniDriverStreamIsPropertySupported)(void* streamHandle, int propertyId);
void (ONI_C_DECL PlayerDriveroniDriverStreamSetPropertyChangedCallback)(void* streamHandle, OniDriverPropertyChanged handler, void* pCookie);
void (ONI_C_DECL PlayerDriveroniDriverStreamNotifyAllProperties)(void* streamHandle);
OniStatus (ONI_C_DECL PlayerDriveroniDriverStreamInvoke)(void* streamHandle, int commandId, const void* data, int dataSize);
OniBool (ONI_C_DECL PlayerDriveroniDriverStreamIsCommandSupported)(void* streamHandle, int commandId);

OniStatus (ONI_C_DECL PlayerDriveroniDriverStreamStart)(void* streamHandle);
void (ONI_C_DECL PlayerDriveroniDriverStreamStop)(void* streamHandle);

int (ONI_C_DECL PlayerDriveroniDriverStreamGetRequiredFrameSize)(void* streamHandle);

void (ONI_C_DECL PlayerDriveroniDriverStreamSetNewFrameCallback)(void* streamHandle, OniDriverNewFrame handler, void* pCookie);
OniStatus (ONI_C_DECL PlayerDriveroniDriverStreamConvertDepthToColorCoordinates)(void* depthStreamHandle, void* colorStreamHandle, int depthX, int depthY, OniDepthPixel depthZ, int* pColorX, int* pColorY);

void* (ONI_C_DECL PlayerDriveroniDriverEnableFrameSync)(void** pStreamHandles, int streamCount);
void (ONI_C_DECL PlayerDriveroniDriverDisableFrameSync)(void* frameSyncGroup);

//
// libPSLink
// 

// As Driver
void (ONI_C_DECL LinkOniDriveroniDriverCreate)(OniDriverServices* driverServices);
void (ONI_C_DECL LinkOniDriveroniDriverDestroy)();
OniStatus (ONI_C_DECL LinkOniDriveroniDriverInitialize)(OniDriverDeviceConnected connectedCallback, OniDriverDeviceDisconnected disconnectedCallback,
                                              OniDriverDeviceStateChanged deviceStateChangedCallback, void* pCookie);
void (ONI_C_DECL LinkOniDriveroniDriverRun)();

OniStatus (ONI_C_DECL LinkOniDriveroniDriverTryDevice)(const char* uri);

// As Device
void* (ONI_C_DECL LinkOniDriveroniDriverDeviceOpen)(const char* uri, const char* mode);
void (ONI_C_DECL LinkOniDriveroniDriverDeviceClose)(void* deviceHandle);

OniStatus (ONI_C_DECL LinkOniDriveroniDriverDeviceGetSensorInfoList)(void* deviceHandle, OniSensorInfo** pSensors, int* numSensors);

void* (ONI_C_DECL LinkOniDriveroniDriverDeviceCreateStream)(void* deviceHandle, OniSensorType sensorType);
void (ONI_C_DECL LinkOniDriveroniDriverDeviceDestroyStream)(void* deviceHandle, void* streamHandle);

OniStatus (ONI_C_DECL LinkOniDriveroniDriverDeviceSetProperty)(void* deviceHandle, int propertyId, const void* data, int dataSize);
OniStatus (ONI_C_DECL LinkOniDriveroniDriverDeviceGetProperty)(void* deviceHandle, int propertyId, void* data, int* pDataSize);
OniBool (ONI_C_DECL LinkOniDriveroniDriverDeviceIsPropertySupported)(void* deviceHandle, int propertyId);
void (ONI_C_DECL LinkOniDriveroniDriverDeviceSetPropertyChangedCallback)(void* deviceHandle, OniDriverPropertyChanged handler, void* pCookie);
void (ONI_C_DECL LinkOniDriveroniDriverDeviceNotifyAllProperties)(void* deviceHandle);
OniStatus (ONI_C_DECL LinkOniDriveroniDriverDeviceInvoke)(void* deviceHandle, int commandId, const void* data, int dataSize);
OniBool (ONI_C_DECL LinkOniDriveroniDriverDeviceIsCommandSupported)(void* deviceHandle, int commandId);
OniStatus (ONI_C_DECL LinkOniDriveroniDriverDeviceTryManualTrigger)(void* deviceHandle);
OniBool (ONI_C_DECL LinkOniDriveroniDriverDeviceIsImageRegistrationModeSupported)(void* deviceHandle, OniImageRegistrationMode mode);

// As Stream
void (ONI_C_DECL LinkOniDriveroniDriverStreamSetServices)(void* streamHandle, OniStreamServices* pServices);
OniStatus (ONI_C_DECL LinkOniDriveroniDriverStreamSetProperty)(void* streamHandle, int propertyId, const void* data, int dataSize);
OniStatus (ONI_C_DECL LinkOniDriveroniDriverStreamGetProperty)(void* streamHandle, int propertyId, void* data, int* pDataSize);
OniBool (ONI_C_DECL LinkOniDriveroniDriverStreamIsPropertySupported)(void* streamHandle, int propertyId);
void (ONI_C_DECL LinkOniDriveroniDriverStreamSetPropertyChangedCallback)(void* streamHandle, OniDriverPropertyChanged handler, void* pCookie);
void (ONI_C_DECL LinkOniDriveroniDriverStreamNotifyAllProperties)(void* streamHandle);
OniStatus (ONI_C_DECL LinkOniDriveroniDriverStreamInvoke)(void* streamHandle, int commandId, const void* data, int dataSize);
OniBool (ONI_C_DECL LinkOniDriveroniDriverStreamIsCommandSupported)(void* streamHandle, int commandId);

OniStatus (ONI_C_DECL LinkOniDriveroniDriverStreamStart)(void* streamHandle);
void (ONI_C_DECL LinkOniDriveroniDriverStreamStop)(void* streamHandle);

int (ONI_C_DECL LinkOniDriveroniDriverStreamGetRequiredFrameSize)(void* streamHandle);

void (ONI_C_DECL LinkOniDriveroniDriverStreamSetNewFrameCallback)(void* streamHandle, OniDriverNewFrame handler, void* pCookie);
OniStatus (ONI_C_DECL LinkOniDriveroniDriverStreamConvertDepthToColorCoordinates)(void* depthStreamHandle, void* colorStreamHandle, int depthX, int depthY, OniDepthPixel depthZ, int* pColorX, int* pColorY);

void* (ONI_C_DECL LinkOniDriveroniDriverEnableFrameSync)(void** pStreamHandles, int streamCount);
void (ONI_C_DECL LinkOniDriveroniDriverDisableFrameSync)(void* frameSyncGroup);

//
// libDummyDevice
// 

// As Driver
void (ONI_C_DECL OzDriveroniDriverCreate)(OniDriverServices* driverServices);
void (ONI_C_DECL OzDriveroniDriverDestroy)();
OniStatus (ONI_C_DECL OzDriveroniDriverInitialize)(OniDriverDeviceConnected connectedCallback, OniDriverDeviceDisconnected disconnectedCallback,
                                              OniDriverDeviceStateChanged deviceStateChangedCallback, void* pCookie);
void (ONI_C_DECL OzDriveroniDriverRun)();

OniStatus (ONI_C_DECL OzDriveroniDriverTryDevice)(const char* uri);

// As Device
void* (ONI_C_DECL OzDriveroniDriverDeviceOpen)(const char* uri, const char* mode);
void (ONI_C_DECL OzDriveroniDriverDeviceClose)(void* deviceHandle);

OniStatus (ONI_C_DECL OzDriveroniDriverDeviceGetSensorInfoList)(void* deviceHandle, OniSensorInfo** pSensors, int* numSensors);

void* (ONI_C_DECL OzDriveroniDriverDeviceCreateStream)(void* deviceHandle, OniSensorType sensorType);
void (ONI_C_DECL OzDriveroniDriverDeviceDestroyStream)(void* deviceHandle, void* streamHandle);

OniStatus (ONI_C_DECL OzDriveroniDriverDeviceSetProperty)(void* deviceHandle, int propertyId, const void* data, int dataSize);
OniStatus (ONI_C_DECL OzDriveroniDriverDeviceGetProperty)(void* deviceHandle, int propertyId, void* data, int* pDataSize);
OniBool (ONI_C_DECL OzDriveroniDriverDeviceIsPropertySupported)(void* deviceHandle, int propertyId);
void (ONI_C_DECL OzDriveroniDriverDeviceSetPropertyChangedCallback)(void* deviceHandle, OniDriverPropertyChanged handler, void* pCookie);
void (ONI_C_DECL OzDriveroniDriverDeviceNotifyAllProperties)(void* deviceHandle);
OniStatus (ONI_C_DECL OzDriveroniDriverDeviceInvoke)(void* deviceHandle, int commandId, const void* data, int dataSize);
OniBool (ONI_C_DECL OzDriveroniDriverDeviceIsCommandSupported)(void* deviceHandle, int commandId);
OniStatus (ONI_C_DECL OzDriveroniDriverDeviceTryManualTrigger)(void* deviceHandle);
OniBool (ONI_C_DECL OzDriveroniDriverDeviceIsImageRegistrationModeSupported)(void* deviceHandle, OniImageRegistrationMode mode);

// As Stream
void (ONI_C_DECL OzDriveroniDriverStreamSetServices)(void* streamHandle, OniStreamServices* pServices);
OniStatus (ONI_C_DECL OzDriveroniDriverStreamSetProperty)(void* streamHandle, int propertyId, const void* data, int dataSize);
OniStatus (ONI_C_DECL OzDriveroniDriverStreamGetProperty)(void* streamHandle, int propertyId, void* data, int* pDataSize);
OniBool (ONI_C_DECL OzDriveroniDriverStreamIsPropertySupported)(void* streamHandle, int propertyId);
void (ONI_C_DECL OzDriveroniDriverStreamSetPropertyChangedCallback)(void* streamHandle, OniDriverPropertyChanged handler, void* pCookie);
void (ONI_C_DECL OzDriveroniDriverStreamNotifyAllProperties)(void* streamHandle);
OniStatus (ONI_C_DECL OzDriveroniDriverStreamInvoke)(void* streamHandle, int commandId, const void* data, int dataSize);
OniBool (ONI_C_DECL OzDriveroniDriverStreamIsCommandSupported)(void* streamHandle, int commandId);

OniStatus (ONI_C_DECL OzDriveroniDriverStreamStart)(void* streamHandle);
void (ONI_C_DECL OzDriveroniDriverStreamStop)(void* streamHandle);

int (ONI_C_DECL OzDriveroniDriverStreamGetRequiredFrameSize)(void* streamHandle);

void (ONI_C_DECL OzDriveroniDriverStreamSetNewFrameCallback)(void* streamHandle, OniDriverNewFrame handler, void* pCookie);
OniStatus (ONI_C_DECL OzDriveroniDriverStreamConvertDepthToColorCoordinates)(void* depthStreamHandle, void* colorStreamHandle, int depthX, int depthY, OniDepthPixel depthZ, int* pColorX, int* pColorY);

void* (ONI_C_DECL OzDriveroniDriverEnableFrameSync)(void** pStreamHandles, int streamCount);
void (ONI_C_DECL OzDriveroniDriverDisableFrameSync)(void* frameSyncGroup);

}

#endif
