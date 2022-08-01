#include "eg8_direct_arpara_camera.h"

#include <arpara_camera.h>
#include <iostream>
#include <fstream>

using namespace DirectShowCamera;

void eg8_arpara_camera()
{
    // Get a empty camera
    ArparaCamera camera = ArparaCamera();

    // Get available camera list
    std::cout << "Start to list the available cameras..." << std::endl;
    std::vector<DirectShowCameraDevice> cameraDeivceList = camera.getDirectShowArparaCameras();
    for (int i = 0; i < cameraDeivceList.size(); i++) {
        std::cout << cameraDeivceList[i] << std::endl;
    }
    if (cameraDeivceList.size() == 0)
    {
        std::cout << "no arpara camera found, exiting" << std::endl;
    } else
    {
        DirectShowCameraDevice &device = cameraDeivceList[0];
        // Get supported formats
        std::cout << "DirectShowCameraDevice supported formats " << std::endl;
        auto formats = device.getDirectShowVideoFormats();
        for(auto& format: formats)
        {
	        std::cout << format << std::endl;
        }

        // select a format
        DirectShowVideoFormat format = formats[formats.size() - 1];
        std::cout << "selected format " << format << std::endl;
        // Open the first camera in the biggest resolution
        std::cout << "Open the first camera..." << std::endl;
       
        bool success = camera.open(device, &format, false);
        if (!success)
        {
            std::cerr << "failed to open camera" << std::endl;
        }
        std::cout << "show DirectShow properties" << std::string(*camera.getDirectShowProperties()) << std::endl;
        // Get exposure in second
        double exposureTime = camera.getExposure();
        if (exposureTime > 0.0)
        {
            std::cout << "Exposure: " + std::to_string(exposureTime) + "s" << std::endl;

        }
        else
        {
            std::cout << "This device doesn't support exposure time" << std::endl;
        }


        // Reset all properties to default
        //std::cout << "Reset properties to default..." << std::endl;
        //camera.resetProperties();
        {
            camera.startCapture();
            // Wait for 1 second
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            cv::Mat frame;
            while (true)
            {
                frame = camera.getMat();
                cv::imshow("frame", frame);
                char key = cv::waitKey(1);
                if (key == 'q')
                {
                    break;
                }else if (key == 's')
                {
	                std::fstream ofile("640_481_gray.bin", std::ios::out | std::ios::binary);
                    ofile.write(reinterpret_cast<char*>(frame.data), frame.total() * frame.elemSize());
                    ofile.close();
                }
            }
        }
    }

    camera.stopCapture();
    // Close the camera.
    camera.close();
    
}