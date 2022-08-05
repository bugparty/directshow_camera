#include <regex>
#include "arpara_quad_camera.h"
#include "arpara_camera.h"
namespace DirectShowCamera
{

	bool ArparaQuadCamera::hasQualCamera()
	{
		ArparaCamera camera;
		std::vector<DirectShowCameraDevice> cameraDeivceList = camera.getDirectShowArparaCameras();
		
		return cameraDeivceList.size() == 2 && cameraDeivceList[0].getUsbInterfaceNumber() == cameraDeivceList[1].getUsbInterfaceNumber();
	}
	;

	bool ArparaQuadCamera::open()
	{
		if (!hasQualCamera())
		{
			return false;
		}
		ArparaCamera camera;
		std::vector<DirectShowCameraDevice> cameraDeivceList = camera.getDirectShowArparaCameras();
		m_lower_ = new DirectShowCameraDevice(std::move(cameraDeivceList[0]));
		m_upper_ = new DirectShowCameraDevice(std::move(cameraDeivceList[1]));
		auto formats_upper = m_upper_->getDirectShowVideoFormats();
		DirectShowVideoFormat format_upper = formats_upper[formats_upper.size() - 1];
		auto formats_lower = m_upper_->getDirectShowVideoFormats();
		DirectShowVideoFormat format_lower = formats_lower[formats_lower.size() - 1];
		bool success = m_upper_camera_.open(*m_upper_,&format_upper, false);
		if (!success)
		{
			return false;
		}
		success = m_lower_camera_.open(*m_lower_, &format_lower, false);
		return success;
	}

	bool ArparaQuadCamera::isOpened()
	{
		return m_lower_camera_.isOpened() && m_upper_camera_.isOpened();
	}

	bool ArparaQuadCamera::close()
	{
		bool success1 = m_lower_camera_.close();
		bool success2 = m_upper_camera_.close();
		return success1 && success2;
	}

	bool ArparaQuadCamera::startCapture()
	{
		return m_lower_camera_.startCapture() && m_upper_camera_.startCapture();
	}

	bool ArparaQuadCamera::stopCapture()
	{
		return m_lower_camera_.stopCapture() && m_upper_camera_.stopCapture();
	}

	bool ArparaQuadCamera::isCapturing()
	{
		return m_lower_camera_.isCapturing() || m_upper_camera_.isCapturing();
	}

	int ArparaQuadCamera::getWidth()
	{
		return 1280;
	}

	int ArparaQuadCamera::getHeight()
	{
		return 480 * 2;
	}

	int ArparaQuadCamera::getPixelBytes()
	{
		return 1;
	}

	unsigned char*  ArparaQuadCamera::getImage(ArparaCameraData& dataIn)
	{
		dataIn.timestamp[0] = 0;
		memcpy(dataIn.buffer, m_lower_camera_.getCameraGrayImage(false), 1280*480);
		dataIn.timestamp[1] = 0;
		memcpy(dataIn.buffer+1280*480, m_upper_camera_.getCameraGrayImage(false), 1280 * 480);
		return dataIn.buffer;
	}
}
