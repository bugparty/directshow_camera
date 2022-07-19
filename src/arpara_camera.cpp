#include "arpara_camera.h"
namespace DirectShowCamera
{

	std::vector<CameraDevice> ArparaCamera::getArparaCameras() {
		auto cameras = UVCCamera::getCameras();
		std::vector<CameraDevice> arparaCameras;
		for(auto& camera: cameras)
		{
			if (camera.getFriendlyName().find("OV580")!= std::string::npos)
			{
				arparaCameras.push_back(camera);
			}
		}
		return arparaCameras;
	}
}