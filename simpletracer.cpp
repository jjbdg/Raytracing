// Simple Raytracer

#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

#include "vector3.h"
#include "types.h"

const unint32_t MAXSIZE = 255;
const double halfCircle = M_PI / 180;

Scene sceneInit (std::string inputFile) {
    Scene scene;

    std::ifstream inputStream;
    inputStream.open(inputFile);
   

    if(!inputStream.is_open()){
		std::cout << "Could not open input file: " << inputFile << std::endl;
        exit(-1);
	}

    while(!inputStream.eof()) {
        std::string keyword = "";
        std::getline(inputStream, keyword, ' ');

        if(keyword.size()-1 == 0) {continue;}

        if(keyword == "imsize") {
            inputStream >> scene.imwidth >> scene.imheight;

            	if(scene.imwidth < 0 || scene.imheight < 0){
                    std::cout << "Error: Invalid width of height value (must be an int >= 0)" << std::endl;
                    exit(-1);
                }
                else if(scene.imwidth != scene.imheight){
                    std::cout << "Aspect Ration is not 1:1" << std::endl;
                    exit(-1);
                }
            std::cout << "imsize: " << scene.imwidth << " " << scene.imheight << std::endl;
        }
        else if (keyword == "eye") {
            inputStream >> scene.eye.x >> scene.eye.y >> scene.eye.z;
            std::cout << "eye: " << scene.eye.x << " " << scene.eye.y << " " << scene.eye.z << std::endl; 
        }
        else if (keyword == "viewdir") {
            inputStream >> scene.viewDir.x >> scene.viewDir.y >> scene.viewDir.z;
            std::cout << "viewdir: " << scene.viewDir.x << " " << scene.viewDir.y << " " << scene.viewDir.z << std::endl;
        }
        else if (keyword == "updir") {
            inputStream >> scene.upDir.x >> scene.upDir.y >> scene.upDir.z;
            std::cout << "updir: " << scene.upDir.x << " " << scene.upDir.y << " " << scene.upDir.z << std::endl;
        }
        else if (keyword == "vfov") {
            inputStream >> scene.vfov;
            std::cout << "vfov: " << scene.vfov << std::endl;
        }
        else if (keyword == "bkgcolor") {
            inputStream >> scene.bkgcolor;
            std::cout << "bkgcolor: " << scene.bkgcolor << std::endl;
        }
        else if (keyword == "sphere") {
            inputStream >> scene.s.position.x >> scene.s.position.y >> scene.position.z >> scene.s.radius;
            std::cout << "sphere: " << scene.s.position.x << scene.s.position.y << scene.position.z << scene.s.radius << std:endl;
        }
        else if (keyword == "mtlcolor") {
            inputStream >> scene.s.mtlColor.r >> scene.s.mtlColor.g >> scene.s.mtlColor.b;
            std::cout << "mtlcolor: " << scene.s.mtlColor.r << scene.s.mtlColor.g << scene.s.mtlColor.b;
        }

        std::getline(inputStream, keyword, '\n');
    }

    //s safety first
    inputStream.close();
    return scene;
}

ViewWindow viewWindowInit (Scene s) {
    ViewWindow vw;

    Vector3 u, v, w; // coordinate system
    u = s.viewDir.crossProduct(s.upDir);
    u.normalize();
    v = u.crossProduct(s.viewDir);
    v.normalize();
    w = s.viewDir.scalarMultiply(-1);
    w.normalize();

    int d = 5;
    double aspectRatio = s.imwidth / s.imheight;
    vw.height = 2 * d *  * tan((s.vfov/2)*halfCircle);
    vw.width = vw.height * aspectRatio;

    Vector3 n = s.viewDir.magnitude();

    vw.ul = s.eye + n.scalarMultiply(d) - u.scalarMultiply(vw.width/2) + v.scalarMultiply(vw.height/2);
    vw.ur = s.eye + n.scalarMultiply(d) + u.scalarMultiply(vw.width/2) + v.scalarMultiply(vw.height/2);
    vw.ll = s.eye + n.scalarMultiply(d) - u.scalarMultiply(vw.width/2) - v.scalarMultiply(vw.height/2);
    vw.lr = s.eye + n.scalarMultiply(d) + u.scalarMultiply(vw.width/2) - v.scalarMultiply(vw.height/2);
    
    vw.deltaH = (vw.ur - vw.ul) / (s.imwidth - 1);
    vw.deltaV = (vw.ll - vw.ul) / (s.imheight - 1);
    
    vw.deltaCH = (vw.ur - vw.ul) / (2 * s.imwidth);
    vw.deltaCV = (vw.ll - vw.ul) / (2 * s.imheight);

    return vw;
}

// check for intersection point for the ray and the object
Color traceRay (Ray ray, Sphere sphere, Color bkgcolor) {
    // (x0 - xc) + (y0 - yc) + (z0 - zc)
    Vector3 knot_center = ray.position - sphere.center;
    double a = 1;
    double b = 2 * ray.direction.dotProduct(knot_cente);
    double c = (knot_center).dotProduct(knot_cente) - pow(sphere.radius, 2);

    // B * B - 4*a*c
    double discriminant = sqrt(b*b - 4*a*c);
    
    if(discriminant > 0.0){
        double t1 = (-b - discriminant) / 2.0;
        double t2 = (-b + discriminant) / 2.0;
        return shadeRay(sphere);
    }

    // once we find the min distance -- there's an intersection
    // return the 
    return bkgcolor;
}

Color shadeRay (Sphere sphere) {
    return sphere.mtlColor;
} // arg = param list

int main (int argc, char *argv[]) {
    std::ofstream outputStream(outputFile, std::ios::out | std::ios::binary);

    if (argc<2 || argc>3) {
        std::cout << "Error: Invalid number of arguments" << std::endl;
        return -1;
    }

    std::string inputFile = (std::string) argv[1];
    std::string outputFile = "deguz033scene.ppm";
    if (argc == 3) {
        outputFile = (std::string) argv[2];
    } 

    Scene s = sceneInit(inputFile);

    // init output image
    outputStream << "P6\n"
				  << s.imwidth << " "
				  << s.imheight << "\n"
				  << MAXSIZE << "\n";
    
    // init pixel arry for output image
    // preliminary calculations
//     ViewWindow vw = viewWindowInit(s);

//     // creating rays to send through viewing window
//     for (int x=0; x < s.imwidth; x++){
//         for (int y=0; y < s.imheight; y++){
//             // mapping between pixels in the image and points in the viewing window
//             Vector3 currentPosition = ul + (vw.deltaH * x) + (vw.deltaV * y) + vw.deltaCH + vw.deltaCV;
            
//             Ray ray;
//             ray.position = eye;
//             // defined by starting point and point where it intersects viewing window
//             ray.direction = (currentPosition - ray.position).normalize();

//             // set each pixel originally as bkgcolor
//             image[x][y] = s.bkgcolor;
//             image[x][y] = traceRay(ray, sphere);
//         }
//     }    Color image[s.imwidth][s.imheight];

    // safety is sexy
    outputStream.close();
    return 0;
}