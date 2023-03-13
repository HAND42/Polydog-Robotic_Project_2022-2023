# SESSION 13 OUTCOME REPORT
## Date: 28/02/2023
## Main event of the session: Converting the 3D model of the Polydog to an URDF file (Part 3) .  
During this session, I continued working on converting the 3D model of the Polydog, into an URDF file. Last time I encountered a problem where only one servo motor was being imported when I ran pybullet. I realized that this was because I had not announced which assembly the program should import. Without announcing an assembly name, pybullet was importing a random assembly, which was why only the assembly of the servomotor was being imported.  
To fix this issue, I went back to the JSON file and made sure to specify which assembly should be imported.  
![Alt text](S13/S13/Capture%20d%E2%80%99%C3%A9cran%202023-03-12%20135255.png)
 After making the necessary changes, I was able to import the entire robot and generate its URDF file.  
Once the URDF file was generated, I wanted to make sure that it worked properly. I ran pybullet to check if the URDF file was working correctly, and I was pleased to see that the entire robot was displayed.  
![Alt text](S13/S13/Capture%20d%E2%80%99%C3%A9cran%202023-03-12%20111701.png)  
![Alt text](S13/S13/Capture%20d%E2%80%99%C3%A9cran%202023-03-12%20111749.png)  
![Alt text](S13/S13/Capture%20d%E2%80%99%C3%A9cran%202023-03-12%20111845.png)    
Here is an extract from the URDF file (it has 1790  line):  
![Alt text](S13/S13/Capture%20d%E2%80%99%C3%A9cran%202023-03-12%20114546.png)  
The structure of a URDF file consists of a hierarchy of elements that represent the different components of the robot. The following are some of the key elements in a URDF file:  

Link: A link is a rigid body that makes up the robot. Each link has a name and may have a visual and collision element associated with it.  

Joint: A joint connects two links and defines their relative motion. Joints can be classified into various types, such as revolute, prismatic, and fixed.  

Origin: The origin defines the position and orientation of a link or joint with respect to the robot's coordinate system.  

Geometry: The geometry element defines the shape of the link or collision model. The shape can be specified as a box, cylinder, sphere, mesh, or other primitive shapes.  

Material: The material element defines the visual properties of a link, such as its color and transparency.  

Inertial: The inertial element defines the mass, moment of inertia, and center of mass of the link.  

Visual: The visual element defines the appearance of the link, such as its color and texture. This element is optional and can be omitted if the robot's appearance is not important.  

Collision: The collision element defines the shape of the link used for collision detection. This element is optional and can be omitted if the robot does not need to perform collision detection.  

Mesh filename: This element specifies the path to a mesh file that is used to represent the robot's geometry.  

The link and joint elements are the most fundamental components of a URDF file. The link element defines the physical properties of the robot, such as its mass, moments of inertia, and geometry. The joint element defines the kinematic properties of the robot, such as the type of joint and its motion range.

In the next session, we will work on importing the URDF file into ISAAC SIM and setting up the simulation environment. We are excited to see the Polydog robot come to life in the virtual world and continue making progress on this project.