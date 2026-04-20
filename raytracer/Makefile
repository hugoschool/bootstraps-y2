CXX	:=	clang++
CXXFLAGS	:=	-Wall -Wextra -std=c++20

raytracer:	main.o Point3D.o Camera.o Ray.o Rectangle3D.o Sphere.o Vector3D.o
	$(CXX) $(CXXFLAGS) -o $@ $^
