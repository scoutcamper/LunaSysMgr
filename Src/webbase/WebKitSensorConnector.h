/* @@@LICENSE
*
*      Copyright (c) 2011-2012 Hewlett-Packard Development Company, L.P.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
* LICENSE@@@ */




#ifndef WEBKITSENSORCONNECTOR_H_
#define WEBKITSENSORCONNECTOR_H_

#include "Common.h"

#include <glib.h>
#include <string>
#include "palmwebtypes.h"

#if defined (TARGET_DEVICE)
    #include "hal/HALSensorConnector.h"
#endif

class WebKitSensorConnector
        #if defined (TARGET_DEVICE)
            : public HALConnectorObserver
        #endif
{
public:
    /**
     * creates a HAL Sensor Connector object
     *
     * @param aType     - Type of the sensor to be created
     * @param aDataCB   - Data Callback function
     * @param aErrCB    - Error Callback function
     * @param pUserData - User data - Ownership of this pointer is not transferred during this API.
     */
    static WebKitSensorConnector* createSensor(Palm::SensorType aType, Palm::fnSensorDataCallback aDataCB, Palm::fnSensorErrorCallback aErrCB, void *pUserData);

    ~WebKitSensorConnector();

    /**
     * Function turns the sensor ON
     */
    bool on();

    /**
     * Function turns the sensor OFF
     */
    bool off();

    /**
     * Sets the sensor report rate
     */
    bool setRate(Palm::SensorRate aRate);

    /**
     * Gets the supported sensors in a json Array List
     */
    static std::string getSupportedSensors();

#if defined (TARGET_DEVICE)
    /**
     * Map the WebKit Sensor Type to HAL Sensor Type
     */
    static HALConnectorBase::Sensor WebKitToHAL(Palm::SensorType aSensorType);

    /**
     * Map the Webkit Sensor report rate to HAL Sensor report rate
     */
    static HALConnectorBase::SensorReportRate WebKitToHAL(Palm::SensorRate aRate);
#endif

protected:
    /**
     * Function calls the Error callback
     */
    void CallErrorCB(std::string aMsg);

#if defined (TARGET_DEVICE)
    /**
     * Function gets called whenever there is some data
     * available from HAL.
     *
     * @param[in]   - aSensorType - Sensor which has got some data to report
     */
    virtual void HALDataAvailable (HALConnectorBase::Sensor aSensorType);
#endif

private:
    /**
     * Constructor constructs a HAL Sensor Connector object
     *
     * @param aSensorType   - Type of the sensor to be created
     * @param aDataCB       - Data Callback function
     * @param aErrCB        - Error Callback function
     * @param pUserData     - User data - Ownership of this pointer is not transferred.
     */
    WebKitSensorConnector(Palm::SensorType aSensorType, Palm::fnSensorDataCallback aDataCB, Palm::fnSensorErrorCallback aErrCB, void *pUserData);

#if defined (TARGET_DEVICE)
    //Data
    HALConnectorBase*               m_Sensor;
    HALConnectorBase::Sensor        m_HALSensorType;
#endif

    Palm::SensorType                m_PalmSensorType;
    Palm::fnSensorDataCallback      m_DataCB;
    Palm::fnSensorErrorCallback     m_ErrCB;
    void*                           m_UserData;
};


#endif /* WEBKITSENSORCONNECTOR_H_ */
