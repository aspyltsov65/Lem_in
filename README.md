# Lem_in
This project is meant to make you code an ant farm manager. You must move your ant colony from one point to another in the least amount of time. Through this project, you will explore graph traversal algorithms: your program will have to choose the paths and moves to be taken by the ants.

## Compile and run
```
git clone https://github.com/aspyltsov65/Lem_in.git
cd Lem_in
```
```
make
./lem-in < map_6
```
Testing maps located in `lem-in_maps` directory

## Map example & explanation
```
5
##start
start 0 1
##end
end 1 0
0 0 0
1 1 1
2 2 2
3 3 3
4 4 4
5 5 5
6 6 6
start-0
0-1
1-2
2-3
2-4
2-5
1-6
6-end
```
Map consist of:

1. Ants amount/number
   - Number must be only positive number.
2. Comments:
   - "##start" and "##end" are provided to show the start and end room.
   - Any other comments we shouldn't be taken into account.
3. Rooms:
   - All rooms defined as: [room name][x_coord][y_coord]
   - Room name cannot start with "L" or space.
   - Room's coordinates always will be integers and cannot be identical.
4. Links:
   - Links defines as: [room_name1]-[room_name2]

## Output example
```
L1-0
L1-1 L2-0
L1-6 L2-1 L3-0
L1-end L2-6 L3-1 L4-0
L2-end L3-6 L4-1 L5-0
L3-end L4-6 L5-1
L4-end L5-6
L5-end
```

# Author
- Anastasiia Pyltsova [GitHub Page](https://github.com/aspyltsov65)
