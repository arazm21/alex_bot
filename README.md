# alex_robot

## how to run code

before you begin, make a dev_ws directory in home, in dev_ws create src, clone the repo there. install all of the packages in requirements.txt. if some fail, it is ok.

### simulate movement in gazebo and rviz2

get to src directory and in one command window run

`colcon build --symlink-install`
`source install/setup.bash` (instead of this you can run
>`echo "source /path/to/your/ros2_ws/install/setup.bash" >> ~/.bashrc`
>`source ~/.bashrc`

once)
`ros2 launch alex_bot launch_sim.launch.py`

in another run

`rviz2 -d ABSPATH`

next, i will make it so that mapping beggins automatically. until then, we need the following
