# SESSION 9 OUTCOME REPORT
## Date: 21/01/2022
## Main event of the session: Progress in the code of Inverse Kinematics.  
The session began with a presentation given by my partner Hugo and me , in which we explained to our professors our progress and accomplishments during the first semester. The presentation covered the goals we set at the beginning of the semester, the methods and techniques we used to achieve them, and the results we obtained. Our professors provided feedback and suggestions for improvement. Following the presentation, the rest of the session was spent working on the inverse kinematic code:  
`void kinematics (int leg, float x, float y, float z) {`  
  `// *** TRANSLATION AXIS ***`  
  `float roll;`  
  `float pitch;`  
  `float yaw;`  
  `// moving the foot sideways on the end plane`  
  `#define hipOffset 76.5`  
  `float lengthY;`  
  `float hipAngle1a;`  
  `float hipAngle1b;`  
  `float hipAngle1;`  
  `float hipAngle1Degrees;`  
  `float hipHyp;`  
    
  `// moving the foot forwards or backwardes in the side plane`  
  `float shoulderAngle2;`  
  `float shoulderAngle2Degrees;`  
  `float z2;`      
  `// side plane of individual leg only`  
  `#define shinLength 125`       
  `#define thighLength 125`  
  `float z3;`  
  `float shoulderAngle1;`  
  `float shoulderAngle1Degrees;`  
  `float shoulderAngle1a;`     
  `float shoulderAngle1b;`  
  `float shoulderAngle1c;`  
  `float shoulderAngle1d;`  
  `float kneeAngle;`    
  `float kneeAngleDegrees;`  
  `// *** ROTATION AXIS`  
  
  `// roll axis`  
  `#define bodyWidth 40      // half the distance from the middle of the body to the hip pivot`    
  `float legDiffRoll;            // differnece in height for each leg`  
  `float bodyDiffRoll;           // how much shorter the 'virtual body' gets`  
  `float footDisplacementRoll;   // where the foot actually is`  
  `float footDisplacementAngleRoll; // smaller angle`  
  `float footWholeAngleRoll;     // whole leg angle`    
  `float hipRollAngle;       // angle for hip when roll axis is in use`  
  `float rollAngle;          // angle in RADIANS that the body rolls`  
  `float zz1a;               // hypotenuse of final triangle`  
  `float zz1;                // new height for leg to pass onto the next bit of code`  
  `float yy1;                // new position for leg to move sideways`  
    `// pitch axis`  
  `#define bodyLength 163.25      // distance from centre of body to shoulder pivot`  
  `float legDiffPitch;            // differnece in height for each leg`  
  `float bodyDiffPitch;           // how much shorter the 'virtual body' gets`  
  `float footDisplacementPitch;   // where the foot actually is`  
  `float footDisplacementAnglePitch; // smaller angle`  
  `float footWholeAnglePitch;     // whole leg angle`  
  `float shoulderPitchAngle;      // angle for hip when roll axis is in use`  
  `float pitchAngle;              // angle in RADIANS that the body rolls`  
  `float zz2a;                    // hypotenuse of final triangle`  
  `float zz2;                     // new height for the leg to pass onto the next bit of code`  
  `float xx1;                     // new position to move the leg fowwards/backwards`  
  
  `// *** yaw calcs ***`   
  
  `float yawAngle;                 // angle in RADIANs for rotation in yaw`  
  `float existingAngle;            // existing angle of leg from centre`  
  `float radius;                   // radius of leg from centre of robot based on x and y from sticks`  
  `float demandYaw;                // demand yaw postion - existing yaw plus the stick yaw `  
  `float xx3;                      // new X coordinate based on demand angle `  
  `float yy3;                      // new Y coordinate based on demand angle`  
  `// convert degrees to radians for the calcs`  
  `yawAngle = (PI/180) * yaw;`  

 `// put in offsets from robot's parameters so we can work out the radius of the foot from the robot's centre`  
  `if (leg == 1) {         // front left leg`  
     `y = y - (bodyWidth+hipOffset);`   
     `x = x - bodyLength;`        
  `}`  
  `else if (leg == 2) {    // front right leg`  
     `y = y + (bodyWidth+hipOffset);`  
     `x = x - bodyLength;`   
  `}`  
  `else if (leg == 3) {    // back left leg`  
     `y = y - (bodyWidth+hipOffset);`   
     `x = x + bodyLength;`  
  `}`  
  `else if (leg == 4) {    // back left leg`  
     `y = y + (bodyWidth+hipOffset);`   
     `x = x + bodyLength;`  
  `}`  

  `//calc existing angle of leg from cetre`  
  `existingAngle = atan(y/x);`     

  `// calc radius from centre`  
  `radius = y/sin(existingAngle);`  

  `//calc demand yaw angle`  
  `demandYaw = existingAngle + yawAngle;`  

  `// calc new X and Y based on demand yaw angle`    
  `xx3 = radius * cos(demandYaw);          // calc new X and Y based on new yaw angle`  
  `yy3 = radius * sin(demandYaw);`  
  `// remove the offsets so we pivot around 0/0 x/y`  
  `if (leg == 1) {         // front left leg`  
     `yy3 = yy3 + (bodyWidth+hipOffset);`   
     `xx3 = xx3 + bodyLength;`        
  `}`  
  `else if (leg == 2) {    // front right leg`  
     `yy3 = yy3 - (bodyWidth+hipOffset);`  
     `xx3 = xx3 + bodyLength;`   
  `}`  
  `else if (leg == 3) {   // back left leg`  
     `yy3 = yy3 + (bodyWidth+hipOffset);`   
     `xx3 = xx3 - bodyLength;`  
  `}`  
  `else if (leg == 4) {    // back left leg`  
     `yy3 = yy3 - (bodyWidth+hipOffset);`   
     `xx3 = xx3 - bodyLength;`  
  `}`  
    
  `// *** pitch calcs ***`  

  `//turn around the pitch for front or back of the robot`  
  `if (leg == 1 || leg == 2) {`  
    `pitch = 0-pitch;`        
  `}`  
  `else if (leg == 3 || leg == 4) {`  
    `pitch = 0+pitch;`  
    `xx3 = xx3*-1;       // switch over x for each end of the robot`  
  `}`  
   `// convert pitch to degrees`  
  `pitchAngle = (PI/180) * pitch;`  

  `//calc top triangle sides`  
  `legDiffPitch = sin(pitchAngle) * bodyLength;`  
  `bodyDiffPitch = cos(pitchAngle) * bodyLength;`  

  `// calc actual height from the ground for each side`  
  `legDiffPitch = z - legDiffPitch;`  
  
  `// calc foot displacement`  
  `footDisplacementPitch = ((bodyDiffPitch - bodyLength)*-1)+xx3;`  
  `//calc smaller displacement angle`  
  `footDisplacementAnglePitch = atan(footDisplacementPitch/legDiffPitch);`  

  `//calc distance from the ground at the displacement angle (the hypotenuse of the final triangle)`  
  `zz2a = legDiffPitch/cos(footDisplacementAnglePitch);`  

  `// calc the whole angle for the leg`  
  `footWholeAnglePitch = footDisplacementAnglePitch + pitchAngle;`  
  
  `//calc actual leg length - the new Z to pass on`  
  `zz2 = cos(footWholeAnglePitch) * zz2a;`  
  
  `//calc new Z to pass on`  
  `xx1 = sin(footWholeAnglePitch) * zz2a;`   
  
  `if (leg == 3 || leg == 4 ){     // switch back X for the back of the robot`  
    `xx1 = xx1 *-1;`  
  `}`  

  `// *** roll calcs ***`  
    
  `//turn around roll angle for each side of the robot`  
  `if (leg == 1 || leg == 3) {`  
    `roll = 0-roll;`  
    `yy3 = yy3*-1;`  
  `}`  
  `else if (leg == 2 || leg == 4) {`  
    `roll = 0+roll;`  
  `}`  
  
  `// convert roll angle to radians`  
  `rollAngle = (PI/180) * roll;    //covert degrees from the stick to radians`  
  
  `// calc the top triangle sides`  
  `legDiffRoll = sin(rollAngle) * bodyWidth;`  
  `bodyDiffRoll = cos(rollAngle) * bodyWidth;`  
  `// calc actual height from the ground for each side`  
  `legDiffRoll = zz2 - legDiffRoll;`              

  `// calc foot displacement`  
  `footDisplacementRoll = (((bodyDiffRoll - bodyWidth)*-1)+hipOffset)-yy3;`

  `//calc smaller displacement angle`  
  `footDisplacementAngleRoll = atan(footDisplacementRoll/legDiffRoll);`  

  `//calc distance from the ground at the displacement angle (the hypotenuse of the final triangle)`  
  `zz1a = legDiffRoll/cos(footDisplacementAngleRoll);`  

  `// calc the whole angle for the leg`  
  `footWholeAngleRoll = footDisplacementAngleRoll + rollAngle;`  

  `//calc actual leg length - the new Z to pass on`  
  `zz1 = cos(footWholeAngleRoll) * zz1a;`  

  `//calc new Y to pass on`  
  `yy1 = (sin(footWholeAngleRoll) * zz1a)-hipOffset;      // take away the offset so we can pivot around zero`  
    
  `// *** TRANSLATION AXIS ***  `  
  
  `// calculate the hip joint and new leg length based on how far the robot moves sideways`  
  `// first triangle`  
  `lengthY = yy1 + hipOffset;                  // calc sideways distance of foot from pivot point centre`  
  `hipAngle1a = atan(lengthY/zz1);             // first angle (that is there at rest due to the offset)`  
  `hipHyp = lengthY/(sin(hipAngle1a));       // hypotenuse from joint pivot to foot`  

  `// second triangle`  
  `hipAngle1b = asin(hipOffset/hipHyp) ;     // calc 'the other angle' in the triangle`  
  `hipAngle1 = (PI - (PI/2) - hipAngle1b) + hipAngle1a;     // calc total hip angle`  
  `hipAngle1 = hipAngle1 - 1.5708;           // take away offset for rest position`  
  `hipAngle1Degrees = ((hipAngle1 * (180/PI)));   // convert to degrees and take off rest position`  
    
  `// calc new leg length to give to the code  below`  
  `z2 = hipOffset/tan(hipAngle1b);           // new leg length`  
  `// ****************`  

`// calculate the shoulder joint offset and new leg length based on now far the foot moves forward/backwards`  
`shoulderAngle2 = atan(xx1/z2);     // calc how much extra to add to the shoulder joint`  
`shoulderAngle2Degrees = shoulderAngle2 * (180/PI);`  
`z3 = z2/cos(shoulderAngle2);     // calc new leg length to feed to the next bit of code below`  

`// ****************`  

`// calculate leg length based on shin/thigh length and knee and shoulder angle`  
`shoulderAngle1a = sq(thighLength) + sq(z3) - sq(shinLength);`  
`shoulderAngle1b = 2 * thighLength * z3;`  
`shoulderAngle1c = shoulderAngle1a / shoulderAngle1b;`  
`shoulderAngle1 = acos(shoulderAngle1c);     // radians`  
`kneeAngle = PI - (shoulderAngle1 *2);       // radians`  

`//calc degrees from angles`  
`shoulderAngle1Degrees = shoulderAngle1 * (180/PI);    // degrees`  
`kneeAngleDegrees = kneeAngle * (180/PI);              // degrees`  

This code calculates the angles and positions of the joints of the robot leg based on input parameters such as the leg number, x, y, and z coordinates of the foot, and roll, pitch, and yaw angles. The function makes use of trigonometry and inverse trigonometry functions to calculate the angles and positions of the joints. The output of the function is the angles of the joints in degrees that we are going to pass on to the next bit of code where we are going to send the angles values to the servo motors.  
At the end of the session, we learned about the existence of the Nvidia Isaac sim, which is a simulation platform developed by Nvidia for robotics research and development. The platform is designed to accelerate the development and deployment of AI-powered robots by providing an easy-to-use, highly realistic simulation environment.We also learned about the various use cases for the Isaac sim, such as training and testing deep learning models for perception and control, and experimenting with different robot designs and configurations, so we decided that we are going to learn it and use it in the future in our project.

  







