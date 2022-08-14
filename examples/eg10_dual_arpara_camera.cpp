#include "eg10_dual_arpara_camera.h"

#include <arpara_camera.h>
#include <filesystem>
#include <iostream>
#include <fstream>

#include "arpara_quad_camera.h"

using namespace DirectShowCamera;

void eg10_dual_camera()
{
    // Get a empty camera
    ArparaQuadCamera camera = ArparaQuadCamera();

    // Check if arapra quad camera exists
    std::cout << "is arapra quad camera exist: " << (camera.hasQualCamera() ? "exist" : "no exist") << std::endl;
    
    if(camera.open())
    {
	    std::cout << "open camera success" << std::endl;
    }else
    {
	    std::cout << "open camera failed" << std::endl;
        return;
    }


	
    ArparaCameraData data;
    data.buffer = new unsigned char[camera.getWidth() * camera.getHeight() * camera.getPixelBytes()];
    camera.startCapture();
    // Wait for 1 second
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    cv::Mat frame;
    while (true)
    {
        frame = cv::Mat(camera.getHeight(), camera.getWidth(), CV_8UC1, camera.getImage(data));
        cv::imshow("frame", frame);
        char key = cv::waitKey(1);
        if (key == 'q')
        {
            break;
        }else if (key == 's')
        {
            std::fstream ofile("960_1280_gray.bin", std::ios::out | std::ios::binary);
            ofile.write(reinterpret_cast<char*>(frame.data), frame.total() * frame.elemSize());
            ofile.close();
            std::cout << "file saved to" << std::filesystem::current_path().string() + "\\960_1280_gray.bin" << std::endl;
        }}
        
    
    
    camera.stopCapture();
    // Close the camera.
    if (camera.close())
    {
        std::cout << "close camera success" << std::endl;
    }
    else
    {
        std::cout << "close camera failed" << std::endl;
        return;
    }

    
}