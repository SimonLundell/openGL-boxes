Follow these steps to run the program (on linux)

1. mkdir build && cd build
2. cmake ..
3. make
4. ./my_box

The program will render 3 boxes:
- First box is built with normal constructor
- Second/third boxes are copies of first box and placed on a relative position from the first box
- Move around with W/A/S/D keys and look around with the mouse