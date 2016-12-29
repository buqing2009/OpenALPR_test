# OpenALPR_test
This is the demo project to show how to use openalpr library 

#Dependence
[OpenALPR](https://github.com/openalpr/openalpr)
[OpenCV](https://github.com/opencv/opencv)
#Installation
```
mkidr build
cd build
cmake ..
make 
```

#How to use
```
./test_openalpr -i=<image_path>
```

advance setting
```
Usage: test_openalpr [params] 

	-?, -h, --help, --usage (value:true)
		print this message
	-c, --country (value:us)
		choose country for licence plate
	--defaultRegion, --dr (value:md)
		provide the library with a region for pattern matching
	-i, --image, --path (value:../p3.jpg)
		image path to input
	--tn, --topN (value:20)
		specify the top N possible plates to return
```
