# C Coureswork1 Maze Solving Robot 

### What does the program do?
This project creates a robot and a manually generated maze. By including the graphics library, the robot is animated to solve the maze when the program is run. The robot is able to solve any randomly generated maze given that the start and exit is at the edge of the maze. The program is unable to generate random mazes.

### Techniques utilized in the writing of the program
The robot is created as a structre. It contains a direction to identify which way the robot faces, and the top left (x,y) coordinate of the robot. The robot is then passed into turn_right(), turn_left(), move_forward() functions as a pointer so the the variables in the robot structre can be changed according to its movements. For turning, the foreground is cleared and robot is simply drawn in the direction it turned to. So if robot faces east and turns right, the foreground is cleared and draw_robot_south() function is called. To move the robot forward the (x,y) coordinates of the robot is incremented according to the direction the robot is facing. All of the robots movement are coded independent of the maze. The robot checks whether it can move solely in the can_move_forward() function. According to the robot's direction, it checks the block in front of it's nose and returns true if the block ahead is a white or finish block.

### Algorithm used to solve the maze
The robot always clings to the left hand side of the wall. So the robot turns left whenever it can. If it can't turn left it checks if it can move forward. If it can't move forward it checks whether it can move to the right. It turns around if it can't do any of the above and turns back. The robot is able to solve any maze given that exit is at the edge of the maze. ![Screenshot from 2022-11-07 15-46-48](https://user-images.githubusercontent.com/114501016/200353348-4288875d-2804-42c2-b4c5-6f7ae827819f.png)

### To change the maze and run the program 
To change the maze change the pattern global variable manually.
Compile : gcc understandablerobot.c graphics.c

Run : ./a.out | java -jar drawapp-2.0.jar
