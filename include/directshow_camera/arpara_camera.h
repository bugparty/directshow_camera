#pragma once
#include "uvc_camera.h"
namespace DirectShowCamera
{
	class ArparaCamera : public UVCCamera {
		using UVCCamera::UVCCamera;
	public:
		~ArparaCamera()
		{
			if(mGrayBuffer != nullptr)
			{
				delete[]mGrayBuffer;
			}
#ifdef HAS_OPENCV
			if(mMatDstBuffer != nullptr)
			{
				delete [] mMatDstBuffer;
			}
#endif
		}
		std::vector<CameraDevice> getArparaCameras();
		
		std::vector<DirectShowCameraDevice> getDirectShowArparaCameras();
		unsigned char* getCameraGrayImage(bool onlyGetNewFrame = false);
#ifdef HAS_OPENCV
		cv::Mat getMat(bool onlyGetNewMat = false);
#endif

	protected:
		unsigned char* mYuyBuffer = nullptr;
		unsigned char* mGrayBuffer = nullptr;
		int mGreyBufferSize = 0;
		bool allocateImageBuffer();
#ifdef HAS_OPENCV
		
		bool allocateMatBuffer();
		unsigned char* mMatDstBuffer = nullptr;
		int mMatDstBufferSize = 0;
#endif
	};
	
}