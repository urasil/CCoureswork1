#include <stdio.h>
#include "graphics.h"
#define SIZE 12
const int CANVAS_SIZE = 600, wait_time = 300, north = 0, east = 1, south = 2, west = 3;
const int square_size = CANVAS_SIZE / SIZE,  white_block = 1, finish_block = 2, start_block = 3;
// const int pattern[SIZE][SIZE]={
//                             {0,0,0,0,0,0,0,0,0,0,0}, 
//                             {3,1,1,1,1,1,0,1,1,1,0},
//                             {0,1,0,0,0,0,0,1,0,1,0},
//                             {0,1,1,1,1,1,0,1,0,1,0},
//                             {0,1,0,0,0,1,0,1,0,1,0},  
//                             {0,1,0,1,0,1,1,1,0,1,0},
//                             {0,1,0,1,0,0,0,0,0,1,0},
//                             {0,1,0,1,1,1,0,1,0,1,0},
//                             {0,1,0,1,0,1,0,1,0,1,0},
//                             {0,1,1,1,0,1,0,1,1,1,0},
//                             {0,0,0,0,0,0,0,0,0,2,0} };
const int pattern[SIZE][SIZE]={
                            {0,0,0,0,0,0,0,0,0,0,0,0}, 
                            {3,1,1,0,1,1,1,0,1,0,0,0},
                            {0,0,1,0,1,0,1,0,1,1,1,0},
                            {0,0,1,0,1,1,1,1,1,0,0,0},
                            {0,0,1,0,1,0,0,0,1,0,1,0},  
                            {0,0,1,1,1,0,0,1,1,1,1,0},
                            {0,0,1,0,1,1,1,1,0,1,0,0},
                            {0,1,1,0,1,0,1,0,0,1,0,0},
                            {0,1,0,0,1,0,0,0,0,1,1,0},
                            {0,1,1,1,1,1,1,0,1,1,0,0},
                            {0,0,1,0,0,0,0,1,1,0,0,0},
                            {0,0,0,0,0,0,0,0,2,0,0,0} };

void background_maze(){
    background();
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if (pattern[i][j] == 2){
                setColour(red);
                fillRect(j*square_size, i*square_size, square_size, square_size);}
            if(pattern[i][j] == 3){
                setColour(yellow);
                fillRect(j*square_size, i*square_size, square_size, square_size);}
            if(pattern[i][j] == 0) fillRect(j*square_size, i*square_size, square_size, square_size);
            else{
                setColour(black);
                drawRect(j*square_size, i*square_size, square_size, square_size);}
        }
    }
}

struct robot
{
    int direction; //(0 NORTH), (1 EAST), (2 SOUTH), (3 WEST)
    int x;
    int y;
};

//*Draws the robot in every direction to represent it visually when it is rotated*//
void draw_robot_east(int x, int y)
{
    foreground();
    clear();
    int x_coor[3] = {x, x, x + square_size};
    int y_coor[3] = {y, y + square_size, y + square_size/2}; 
    setColour(green);
    fillPolygon(3, x_coor, y_coor);
}

void draw_robot_west(int x, int y)
{
    foreground();
    clear();
    int x_coor[3] = {x + square_size, x + square_size, x};
    int y_coor[3] = {y, y + square_size, y + square_size/2};
    setColour(green);
    fillPolygon(3, x_coor, y_coor);
    
}

void draw_robot_north(int x, int y)
{
    foreground();
    clear();
    int x_coor[3] = {x + square_size/2, x, x + square_size};
    int y_coor[3] = {y, y + square_size, y + square_size};
    setColour(green);
    fillPolygon(3, x_coor, y_coor);
    
}

void draw_robot_south(int x, int y)
{
    foreground();
    clear();
    int x_coor[3] = {x, x + square_size, x + square_size/2};
    int y_coor[3] = {y, y, y + square_size};
    setColour(green);
    fillPolygon(3, x_coor, y_coor);
    
}

void turn_right(struct robot *robot)
{   
    if( (robot->direction == north) ) 
    {
        draw_robot_east(robot->x, robot->y);     
        robot->direction += 1;  
    }

    else if( (robot->direction ==  east) )
    {
        draw_robot_south(robot->x, robot->y);     
        robot->direction += 1;  
    }   
    else if( (robot->direction ==  south) ) 
    {
        draw_robot_west(robot->x, robot->y);     
        robot->direction += 1;  
    }   
    else if( (robot->direction ==  west) ) 
    {
        draw_robot_north(robot->x, robot->y);     
        robot->direction = 0;  
    }   
}

void turn_left(struct robot *robot)
{
    if( (robot->direction == north) ) 
    {
        draw_robot_west(robot->x, robot->y);     
        robot->direction = 3;  
    }

    else if( (robot->direction ==  east) ) 
    {
        draw_robot_north(robot->x, robot->y);     
        robot->direction -= 1;  
    }   
    else if( (robot->direction ==  south) )
    {
        draw_robot_east(robot->x, robot->y);     
        robot->direction -= 1;  
    }   
    else if( (robot->direction ==  west) ) 
    {
        draw_robot_south(robot->x, robot->y);     
        robot->direction -= 1; 
    }   
}

void move_forward(struct robot *robot)
{
    if(robot->direction == north)
    {
        robot->y -= square_size;
        draw_robot_north(robot->x, robot->y);
        
    }
    else if(robot->direction == east)
    {
        robot->x += square_size;
        draw_robot_east(robot->x, robot->y);
    }
    else if(robot->direction == south)
    {
        robot->y += square_size;
        draw_robot_south(robot->x, robot->y);
    }
    else if(robot->direction == west)
    {
        robot->x -= square_size;
        draw_robot_west(robot->x, robot->y);
    }
    sleep(wait_time);
}

//*Check whether the block in front of the block we are currently at is white or black*//
//*Return true if block is white or the finish block, false if its black*//
int can_move_forward(struct robot *robot) 
{
    if(robot->direction == north)
    {
        if(pattern[(robot->y - square_size) / square_size][robot->x / square_size] == white_block
        || pattern[(robot->y - square_size) / square_size][robot->x / square_size] == finish_block)
        {
            return 1;
        }
    }
    else if(robot->direction == east)
    {
        if(pattern[(robot->y) / square_size][(robot->x + square_size) / square_size] == white_block
        || pattern[(robot->y) / square_size][(robot->x + square_size) / square_size] == finish_block)
        {
            return 1;
        }
    }
    else if(robot->direction == south)
    {
        if(pattern[(robot->y +square_size) / square_size][robot->x / square_size] == white_block
        || pattern[(robot->y +square_size) / square_size][robot->x / square_size] == finish_block)
        {
            return 1;
        }
    }
    else if(robot->direction == west)
    {
        if(pattern[robot->y / square_size][(robot->x - square_size) / square_size] == white_block
        || pattern[robot->y / square_size][(robot->x - square_size) / square_size] == finish_block)
        {
            return 1;
        }
    }
    return 0;
}

int at_marker(struct robot *robot)
{
    if(pattern[robot->y / square_size][robot->x / square_size] == finish_block)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//*Robot always clings on to the left hand wall, which are black blocks, which eventually leads the robot to find the finish block*//
void path_finding(struct robot *robot)
{
    while(!at_marker(robot))
    {
        turn_left(robot);
        if(can_move_forward(robot))
        {
           move_forward(robot);  
        }
        else
        {
            turn_right(robot);
            if(can_move_forward(robot))
            {
                move_forward(robot);
            }
            else
            {
                turn_right(robot);
                if(can_move_forward(robot))
                {
                    move_forward(robot);
                }
                else
                {
                    turn_right(robot);
                    move_forward(robot);  
                }
            }          
        }
    }drawString("Maze successfully completed", CANVAS_SIZE/2 -100 , CANVAS_SIZE/2 -100);
}

int main(void)
{
    struct robot robo = {1,0,square_size};
    int maze[SIZE][SIZE] = {{0}};
    setWindowSize(CANVAS_SIZE,CANVAS_SIZE);
    background_maze();
    path_finding(&robo);

    return 0;
}