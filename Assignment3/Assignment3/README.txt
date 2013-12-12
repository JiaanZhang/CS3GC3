Name : Wenqiang Chen with (Brandon Da Silva - 1057434)
student # : 1155437
Platform : windows 7
IDE : Eclipse IDE for C/C++ Developers with MinGW compiler

Instruction for compiling :
make project and import all the files to run. if library is not found then right click the project, properties -> c/c++ general -> Paths and Symbols -> Libraries, then add "freeglut" "glu32" and "opengl32", given that freeglut is installed


Commands : 
 'w' 's'  -- Move camera about z-axis                                              
 'a' 'd'  -- Move camera about y-axis                                              
 'SPACE'  -- Pauses the program                                                    
 'ESC'/'q'-- Terminates the program                                                
 'r'      -- Resets the program                                                    
 'm'      -- Apply the material to the object the mouse is over                    
 'x'      -- Saving the current scene to a text file                               
 'c'      -- Loads a previously saved scene                                        
 shift + 1-- Draw a cube                                                           
 shift + 2-- Draw a sphere                                                         
 shift + 3-- Draw a teapot                                                         
 shift + 4-- Draw a cone                                                           
 shift + 5-- Draw a torus                                                          
 '1'      -- Change material to greenPlastic                                       
 '2'      -- Change material to yellowPlastic                                      
 '3'      -- Change material to purplePlastic                                      
 '4'      -- Change material to goldMat                                            
 '5'      -- Change material to silverMat                                          
 LMB      -- Selects an object to manipulate                                       
 RMB      -- Deletes an object the ray intersects                                  
OBJECT INTERACTION
 '+/-'    -- Increase/decrease size                                                
 'shift + w' 'shift + s'  -- Move object about z-axis                                              
 'shift + a' 'shift + d'  -- Move object about x-axis                                              
 'up' 'down'  -- Move object about z-axis                                              
 'left' 'right'  -- Move object about x-axis                                              
LIGHT SOURCE CONTROLS
 'y'      -- Toggle which light to manipulate                                      
 't' 'g'  -- Move selected light along x-axis                                      
 'f' 'h'  -- Move selected light along z-axis                                      
 '6' '7'  -- Move selected light along y-axis                                      
CAMERA CONTROLS (extra)
 'z'      -- Toggle extra camera movement feature                                  
 'i' 'k'  -- Move camera forward and backward                                      
 'j' 'l'  -- Move camera left and right                                            
 mouse    -- Mouse movement to control direction of camera through space    


extra features:
     raySphere test to select light source
    camera movement