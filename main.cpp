#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <alpr.h>

int main(int argc, char **argv) {
//     std::cout << "Hello, world!" << std::endl;
    cv::Rect roi_region;
     // Initialize the library using United States style license plates.
    // You can use other countries/regions as well (for example: "eu", "au", or "kr")
    alpr::Alpr openalpr("us", "../config/openalpr.conf");

    // Optionally specify the top N possible plates to return (with confidences).  Default is 10
    openalpr.setTopN(20);

    // Optionally, provide the library with a region for pattern matching.  This improves accuracy by
    // comparing the plate text with the regional pattern.
    openalpr.setDefaultRegion("md");

    // Make sure the library loaded before continuing.
    // For example, it could fail if the config/runtime_data is not found
    if (openalpr.isLoaded() == false)
    {
        std::cerr << "Error loading OpenALPR" << std::endl;
        return 1;
    }

    // Recognize an image file.  You could alternatively provide the image bytes in-memory.
    alpr::AlprResults results = openalpr.recognize("/home/buqing2009/Pictures/p3.jpg");
    std::cout << results.img_height << "," << results.img_width << std::endl;
    
    alpr::AlprPlate best_plate;
     alpr::AlprPlateResult plate;
    alpr::AlprCoordinate p1,p2,p3,p4;
    cv::namedWindow("show_pic", cv::WINDOW_AUTOSIZE);
    cv::Mat img = cv::imread("/home/buqing2009/Pictures/p3.jpg");
    cv::Point2d cvp1,cvp2;
    // Iterate through the results.  There may be multiple plates in an image,
    // and each plate return sthe top N candidates.
    for (int i = 0; i < results.plates.size(); i++)
    {
        plate = results.plates[i];
      
      
//       std::cout << "plate" << i << ": " << plate.topNPlates.size() << " results" << std::endl;

//         for (int k = 0; k < plate.topNPlates.size(); k++)
//         {
           best_plate  = plate.bestPlate;
           p1 = plate.plate_points[0];
           p2 = plate.plate_points[1];
           p3 = plate.plate_points[2];
           p4 = plate.plate_points[3];
          
          std::cout << "    - " << best_plate.characters << "\t confidence: " << best_plate.overall_confidence;
          std::cout << "\t pattern_match: " << best_plate.matches_template << std::endl;
          
          cvp1.x = p1.x;
          cvp1.y = p1.y;
          cvp2.x = p3.x;
          cvp2.y = p3.y;
          cv::rectangle(img,cvp1,cvp2,cv::Scalar(0,0,255),3,8,0);
          
//         }
       
    }
    

    cv::imshow("show_pic", img);
    cv::waitKey();
    return 0;
}
