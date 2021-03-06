# fdf
#### my 42 nickname - chermist
> Code written in norminette code style(github.com/sabrusrin/norme)  

Graphic programming project, FdF proposes to represent the mesh in "wire of a field" in 3D.

In this project I will discovered the basics of graphic programming, and in particular how to place points in space, 
how to join them with segments and most importantly how to observe the scene from a particular viewpoint. 
I also discovered my first graphic library: miniLibX. This library was developed internally(in ecole42) and includes 
the minimum necessary to open a window, light a pixel and deal with events linked to this window: keyboard and mouse.
This project introduced me to “events” programming.

##### For visualisation I used a minilibx(ecole42 graphic library) that gives a functions to create/destroy/clear window, to put a pixel to the window I created and to work with keyboard/mouse events.

Use make to build project on macos.  

### FUNCTIONALITY

```
PRESS KEY EVENTS:
x - draw lines
d - dots
i - isometric projection 
p - parallel projection
r - reset
c - colorize
key_left - move left
key_right - move right
key_up - move up
key_down - move down
key_plus - zoom in
key_minus - zoom out
numpad_plus - increase altitude
numpad_minus - decrease altitude


e.g.

./fdf ./test_maps/mars.fdf

./fdf ./test_maps/42.fdf

./fdf ./test_maps/pyramide.fdf

./fdf ./test_maps/100-6.fdf

./fdf ./test_maps/julia.fdf
```

#### If you want to build project on linux machine, follow these steps:
```
1) Update/upgrade your system:
  apt-get update
  apt-get upgrade

2) Install the following packages:
  apt-get install libx11-dev
  apt-get install libxext-dev

3) ./configure
4) Use make command: make linux
Hope it will work :)
```

![world](https://raw.githubusercontent.com/sabrusrin/fdf/master/images/world.png)
![42](https://raw.githubusercontent.com/sabrusrin/fdf/master/images/42.png)
