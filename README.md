# Flight Simulator

>this game is a simple flight simulator which uses OpenGL to handle the display along with freeglut library. Some features:

  - An open world setup providing a basic mountain view (see: mountain.cpp which spits out triangle meshes to create a mountain scene)
  - The airplane automatically moves forward at a fixed speed. (see: fly.cpp) 
  - Reinforces user controls. example: The user will control the bank and tilt of the airplane through the arrow keys. Pressing the left (right) arrow key will make the plane roll to its left (right). Pressing the up (down) arrow key will cause the airplane to pitch up (down) etc.
  - Magic!

>Basic information:

- PLATFORM: Windows
- OS VERSION: 10 Pro
- BUILD ENVIRONMENT: Visual Studio 2013
- LANGUAGE: C (OpenGL API)
- EXTERNAL LIBRARIES USED: Free GLUT library, GL

>Build instructions:

- How to build?

	_On a Windows machine, follow these steps_:
	- Download Visual Studio 2015 Enterprise (2013 or prior would also be fine!)
	- When installing, make sure c++ is selected
	- Open Visual Studio

- What changes to make to the build configuration?

	- File -> New -> Project (To create a new project) 
	- Templates -> Visual c++ -> Empty Project 
	- Name/Location whatever you want, and then click ok
	- Tools -> NuGet Package Manager -> Package Manager Console (OR IF YOU'RE USING VS 2013) Tools -> Library Package Manager -> Package Manager Console 
	- Type in `Install-Package nupengl.core` without the quotes on the shell right at the bottom of the window to install all required dependencies and essential libraries (GL and freeglut) 

- Final build and finishing:

    - If you're through with the above it's essentially a matter of just importing the source files placed in the __flightSimulator__ folder and hitting the __build and run button__ on visual studio. 

> some functionalities:

- Here's a screenshot of the control screen:

![Alt text](https://raw.githubusercontent.com/javeria2/flightSimulator/master/screens/2.PNG "controls")



>Cockpit view screens:


(![Alt text](https://raw.githubusercontent.com/javeria2/flightSimulator/master/screens/1.PNG "controls")
(![Alt text](https://raw.githubusercontent.com/javeria2/flightSimulator/master/screens/3.PNG "controls")

