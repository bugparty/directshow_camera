#include "ds_camera_device.h"

#include <regex>

namespace DirectShowCamera
{

    /**
     * @brief Constructor
     * 
     * @param friendlyName Friendly Name
     * @param description Description
     * @param devicePath Device Path
     * @param videoFormats Video Formats
     */
    DirectShowCameraDevice::DirectShowCameraDevice(std::string friendlyName, std::string description, std::string devicePath, std::vector<DirectShowVideoFormat> videoFormats)
    {
        m_videoFormats = videoFormats;
        m_friendlyName = friendlyName;
        m_description = description;
        m_devicePath = devicePath;    
    }

    DirectShowCameraDevice::DirectShowCameraDevice(const DirectShowCameraDevice& other)
    {
        m_videoFormats = other.m_videoFormats;
        m_friendlyName = other.m_friendlyName;
        m_description = other.m_description;
        m_devicePath = other.m_devicePath;
        if (other.parsedDevicePath)
        {
            parsedDevicePath = other.parsedDevicePath;
            m_vid = other.m_vid;
            m_pid = other.m_pid;
            m_usbInterfaceNumber = other.m_usbInterfaceNumber;
        }
    }
    DirectShowCameraDevice::DirectShowCameraDevice(DirectShowCameraDevice&& other)
    {
        m_videoFormats = std::move(other.m_videoFormats);
        m_friendlyName = std::move(other.m_friendlyName);
        m_description = std::move(other.m_description);
        m_devicePath = std::move(other.m_devicePath);
        if (other.parsedDevicePath)
        {
            parsedDevicePath = other.parsedDevicePath;
            m_vid = std::move(other.m_vid);
            m_pid = std::move(other.m_pid);
            m_usbInterfaceNumber = other.m_usbInterfaceNumber;
        }
    }
#pragma region Getter

    /**
     * @brief Get the supported DirectShowVideoFormats
     * 
     * @return Return the the supported DirectShowVideoFormats 
     */
    std::vector<DirectShowVideoFormat> DirectShowCameraDevice::getDirectShowVideoFormats()
    {
        return m_videoFormats;
    }

    /**
     * @brief Get the camera friendly name
     * 
     * @return Return the camera friendly name
     */
    std::string DirectShowCameraDevice::getFriendlyName()
    {
        return this->m_friendlyName;
    }

    /**
     * @brief Get the camera description
     * 
     * @return Return the camera description
     */
    std::string DirectShowCameraDevice::getDescription()
    {
        return this->m_description;
    }

    /**
     * @brief Get the device path
     * 
     * @return Return the device path
     */
    std::string DirectShowCameraDevice::getDevicePath()
    {
        return this->m_devicePath;
    }

    std::string DirectShowCameraDevice::getVid()
    {
        parseDevicePath();
        return m_vid;
    }

    void DirectShowCameraDevice::parseDevicePath()
    {
	    std::lock_guard<std::mutex> lock(parseDevicePathMutex);
	    if (!parsedDevicePath)
	    {
		    parseDevicePathImpl();
		    parsedDevicePath = true;
	    }
    }

    std::string DirectShowCameraDevice::getPid()
    {
        parseDevicePath();
        return m_pid;
    }

    int DirectShowCameraDevice::getUsbInterfaceNumber()
    {
        parseDevicePath();
        return m_usbInterfaceNumber;
    }

    void DirectShowCameraDevice::parseDevicePathImpl()
    {
        std::regex regex(R"(^\\\\\?\\usb#vid_(\w{4})&pid_(\w{4})&mi_(\d{2}).*)", std::regex_constants::ECMAScript);
        std::smatch match;
        std::regex_search(m_devicePath, match, regex);
        if (match.size() == 4)
        {
            m_isUnderUsbCompositeDevice = true;
	        m_vid = match[1].str();
            m_pid = match[2].str();
            m_usbInterfaceNumber = std::stoi(match[3].str());
        }
		else
		{
			m_isUnderUsbCompositeDevice = false;
		}
    }

#pragma endregion Getter and Setter

}
