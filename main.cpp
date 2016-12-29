/*
*  main.cpp
*  test OpenALPR
*
*  Created by Bu Qing on 12/29/2016.
*
*/
#include <iostream>
#include <ctype.h>  
#include <string> 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/tracking/tracking.hpp>
#include <alpr.h>

const char* keys =  
{   
    "{ help h usage ? |      | print this message   }"
    "{ c country | us | choose country for licence plate}"  
    "{ tn topN |20 | specify the top N possible plates to return}"  
    "{ dr defaultRegion | md | provide the library with a region for pattern matching}"  
    "{ i image path | ../p3.jpg | image path to input}"
};  



int main(int argc, char **argv) {
    
    cv::CommandLineParser parser(argc, argv, keys);
    
    if (parser.has("help"))
    {
        parser.printMessage();
        return 0;
    }

    std::string country = parser.get<std::string>("c");
    int topN = parser.get<int>("tn");
    std::string defaultRegion = parser.get<std::string>("dr");
    std::string image_path = parser.get<std::string>("i");
    
    cv::Rect roi_region;  
     // Initialize the library using United States style license plates.
    // You can use other countries/regions as well (for example: "eu", "au", or "kr")
    alpr::Alpr openalpr(country, "../config/openalpr.conf");
    

    // Optionally specify the top N possible plates to return (with confidences).  Default is 10
    openalpr.setTopN(topN);

    // Optionally, provide the library with a region for pattern matching.  This improves accuracy by
    // comparing the plate text with the regional pattern.
    openalpr.setDefaultRegion(defaultRegion);

    // Make sure the library loaded before continuing.
    // For example, it could fail if the config/runtime_data is not found
    if (openalpr.isLoaded() == false)
    {
        std::cerr << "Error loading OpenALPR" << std::endl;
        return 1;
    }

    // Recognize an image file.  You could alternatively provide the image bytes in-memory.
    alpr::AlprResults results = openalpr.recognize(image_path);
    std::cout << results.img_height << "," << results.img_width << std::endl;
    
    alpr::AlprPlate best_plate;
     alpr::AlprPlateResult plate;
    alpr::AlprCoordinate p1,p2,p3,p4;
    cv::namedWindow("show_pic", cv::WINDOW_AUTOSIZE);
    cv::Mat img = cv::imread(image_path);
    cv::Point2d cvp1,cvp2;
    // Iterate through the results.  There may be multiple plates in an image,
    // and each plate return sthe top N candidates.
    for (int i = 0; i < results.plates.size(); i++)
    {
        plate = results.plates[i];
      
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
       
    }
    
    while(1){
        cv::imshow("show_pic", img);
        if(cv::waitKey() == 'q'){
            break;
        }
    }
    return 0;
}
