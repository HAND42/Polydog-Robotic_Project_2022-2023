# SESSION 12 OUTCOME REPORT
## Date: 14/02/2023
## Main event of the session: Converting the 3D model of the Polydog to an URDF file (Part 2) .
During this session i tried to convert the 3D model of the polydog to an urdf file and in this session report, I will elaborate on the steps required to convert a 3D model of a robot on Onshape to a URDF file using the Onshape-to-Robot plugin on Ubuntu. This conversion will allow us to simulate the robot's motion and control it through Isaac Sim.  

## Step 1: Create an API Key in Onshape  
The first step is to create an API key in Onshape. We need this key to allow the Onshape-to-Robot plugin to access the 3D model of the robot directly and extract the necessary information. To create an API key, we need to go to the Onshape Developer Portal (https://dev-portal.onshape.com/) and create an account if we don't have one. Once we log in, we can create a new API key by following the instructions provided.
You should store your API key in environment variables using this commands in the terminal:  
`Vi keys`        
then copy that:    
export ONSHAPE_API=https://cad.onshape.com  
export ONSHAPE_ACCESS_KEY=Your_Access_Key  
export ONSHAPE_SECRET_KEY=Your_Secret_Key  
After that you should write this command :     
`Source Keys`

## Step 2: Install Onshape-to-Robot Plugin on Ubuntu  
you can install onshape-to-robot using this command:  
`pip install onshape-to-robot`   
After that you should clone the repository:  
`git clone git@github.com:Rhoban/onshape-to-robot.git `   
and install the dependencies:  
`pip install numpy pybullet requests commentjson colorama numpy-stl` 

## Step 3: Import the 3D Model  
After installing the plugin, we can import the 3D model of the robot into the Onshape-to-Robot plugin. We need to create a directory where we want to store the files, and in this directory, we need to create a configuration file. This file tells the plugin how to import the 3D model. We used these commands:  
`mkdir polydog`    
`vi polydog/config.json`  
and then you paste this:  
`{`  
`    "documentId": "document-id",`  
`    "outputFormat": "urdf"`  
`}`     
the document-id is the number (XXXXXXXXX) you can find in Onshape URL:
https://cad.onshape.com/documents/XXXXXXXXX/w/YYYYYYYY/e/ZZZZZZZZ  

## Step 4: Run the Plugin  
After importing the 3D model, we can run the Onshape-to-Robot plugin to convert the 3D model to a URDF file. We use this command:  
`onshape-to-robot polydog` (the name of the directory)   
![Alt text](S12/Capture%20d%E2%80%99%C3%A9cran%202023-02-18%20023003.png)  
![Alt text](S12/Capture%20d%E2%80%99%C3%A9cran%202023-02-18%20023102.png)  
As you can see the URDF file is ready, we just need to check how the import went using pyBullet. PyBullet is a physics engine that come with the onshape-to-robot pluging, it is used simulating and testing the behavior of robots and other mechanical systems. It is an open-source software developed by the Robotics and AI Lab at the University of Massachusetts, Amherst, and is widely used in research and industry. The combination of Onshape-to-Robot and PyBullet allows for a streamlined process of designing and testing robots, which can save time and reduce costs.  
We use this command to run pyBullet:  
`Onshape-to-robot-bullet polydog`  (the name of the directory)  
Here is the results:  
![Alt text](S12/Capture%20d%E2%80%99%C3%A9cran%202023-02-20%20011327.png)  
As you can see, the software only imported one servo motor, the reason why it did that is still not clear to me.