#include "arpara_camera.h"

namespace DirectShowCamera
{
	class DirectShowCameraDevice;
	struct ArparaCameraData
	{
		long timestamp[2];
		unsigned char* buffer;
	};
	class ArparaQuadCamera
	{
	public:
		bool hasQualCamera();
		// Connection
		bool open();
		bool isOpened();
		bool close();
		// Capture
		bool startCapture();
		bool stopCapture();
		bool isCapturing();
		int getWidth();
		int getHeight();
		int getPixelBytes();

		unsigned char* getImage(ArparaCameraData& dataIn);
	private:

		DirectShowCameraDevice* m_upper_ = nullptr;
		DirectShowCameraDevice* m_lower_ = nullptr;
		ArparaCamera m_upper_camera_ ;
		ArparaCamera m_lower_camera_;
	};
}
