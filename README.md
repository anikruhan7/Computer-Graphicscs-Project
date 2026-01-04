Project Proposal
University: American International University-Bangladesh (AIUB)
Course: Computer Graphics (Section L)
Faculty: Zishan Ahmed Onik

Project Title:
A Village Scenario Animation: A 2D OpenGL Simulation

Submitted By :
Anik Ruhan (ID: 23-50245-1)
Faysal Ahmed (ID: 23-50731-1)
Nihar Sarkar Tirtho (ID: 23-55293-3)
Kamrul Hasan (ID: 22-49770-3)
Mahmuda Alam (ID: 22-49456-3)

1. Introduction
Computer Graphics is a fundamental field in computer science that focuses on the visual representation of data and environments using computational techniques. The objective of this project, titled A Village Scenario Animation, is to design and implement a dynamic 2D village environment using the C++ programming language and the OpenGL (GLUT) library.
Rather than producing a static scene, the project emphasizes animation, interactivity, and logical behavior. Various real-life elements of a rural village, such as traffic movement, environmental changes, and sound effects, are simulated to create a realistic and engaging visual experience. Through this project, core concepts of 2D rendering, animation, and object-oriented programming are practically demonstrated.

2. Objectives
The major objectives of this project are as follows:
To implement fundamental computer graphics concepts, including geometric primitives and 2D transformations such as translation, scaling, and rotation.
To apply object-oriented programming principles, particularly inheritance and polymorphism, for effective management of graphical objects.
To design and control animated behaviors, including vehicle movement, traffic signal logic, and environmental transitions.
To provide user interaction through keyboard controls for camera manipulation, environment control, and simulation flow.

3. Methodology and Tools
Programming Language: C++
Graphics Library: OpenGL using the GLUT framework
Development Environment: Visual Studio Code and Xcode (macOS-supported audio implementation)
The system is designed using an object-oriented architecture. A centralized Scene manager maintains a collection of abstract GameObject references, allowing different scene elements to be handled uniformly. This design ensures modularity, code reusability, and ease of future expansion.

4. Key Features
A. Environmental Dynamics (Day and Night Cycle)
The background environment transitions smoothly between day and night states.
A moving sun represents daytime, while a moon appears during nighttime.
Trees, grass, and other natural objects automatically adjust their color intensity during the night to simulate reduced lighting conditions.
Bird animations are displayed exclusively during the daytime to enhance realism.
B. Intelligent Traffic System
The scene includes multiple vehicles, such as cars and buses, traveling in opposite directions.
A functional traffic light system alternates between red and green signals.
Vehicles respond to traffic signals by stopping at red lights and resuming movement when green.
Different vehicle categories move at varying speeds to reflect real-world behavior.
C. Architecture and Scenery
Village houses are implemented using inheritance, allowing multiple architectural variations through polymorphism.
Natural elements such as trees, a pond, and road structures are created using OpenGL drawing primitives.
D. Audio and Interaction
Background audio changes automatically based on the time of day, with bird sounds during daytime and cricket sounds at night.
Users can interact with the simulation through sound effects, simulation control, and environmental toggles.

5. User Interaction Controls
The following keyboard controls are implemented in the simulation:
Z / z: Zoom in and zoom out
D: Switch to Day mode
N: Switch to Night mode
Spacebar: Pause or resume the simulation
H: Play vehicle horn sound
O: Reset camera view
Arrow Keys: Pan the camera (Left, Right, Up, Down)

6. Conclusion
A Village Scenario Animation presents a practical application of 2D computer graphics techniques within an interactive environment. By integrating animation, sound, and logical behavior with object-oriented design, the project successfully simulates a simplified rural village scenario.
This project meets the academic objectives of the Computer Graphics course and provides valuable experience in developing structured and interactive graphical applications using OpenGL.
