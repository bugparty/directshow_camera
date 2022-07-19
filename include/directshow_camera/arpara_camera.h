#pragma once
#include "uvc_camera.h"
namespace DirectShowCamera
{
	class ArparaCamera : public UVCCamera {
		using UVCCamera::UVCCamera;
	public:
		~ArparaCamera(){}
		std::vector<CameraDevice> getArparaCameras();
	};
	
}