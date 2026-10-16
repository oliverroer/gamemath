## 3.1 Why have multiple coordinate spaces?

It makes certain things easier to describe, e.g.
describing coordinates relative to a local space, rather
than an absolute world space.

For example, when positioning text in an application,
I don't want to describe it in screen coordinates.
I also don't want to describe it in window coordinates.
I'd prefer to describe it in a coordinate system that is
local to the element in which I'm positioning the text.
This way, I don't have to take into account that the
that the text is rendered inside a window that may be moved around. The local coordinate can stay the same, while the screen coordinates can change.

In certain cases, using a local coordinate system can
also help us avoid working with very large numbers.

Imagine a game with a huge world, as you travel further
out in this world, your coordinate values keep increasing. With this increase, you also lose precision (if you are using floats). Some of these precision issues can be avoided by using smaller local coordinate spaces.

## 3.2 Coordinate spaces

**world space**

    The exact position of an object in the world. In real life, this could be equivalent to latitude and longitude.

    Directions are given in absolute terms such as "north", "east", "south", "west", "up" and "down".

**object space**

    Also known as *model space* or *body space*.

    Think of a 3D model. Points in the model operate on a local coordinate system. The soles of the feet might be at y=0, and the toes a bit "forward".

    Directions are given in relative terms, such as "forward", "back", "left", "right", "above", "below".

**camera space**

    In camera space, coordinates describe how objects are positioned relative to the camera.

    The $x$-axis describes whether they are left or right of the center.

    The $y$-axis describes whether they are up or down relative to the center.

    The $z$-axis describes how far the are in front of behind of the camera.

**upright space**

    Aka *center of mass coordinates* or *intertial space*.

    "Halfway" between world and object space.

    The axis are parallel with world space, but the origin is the same as object space.


To convert from object space to world space, you can first apply a rotation to take you to upright space, then a translation to take you to world space.

To convert from world to object space, you can do the opposite, first translating to take you to upright space, then rotate to take you to object space.

## On the benefits of different coordinate spaces

Certain operations are much easier to describe in one space over the other.

For example, moving an object "forward" or rotating it is much more easily done in local space, compared to world space.

To know whether one object is north of another, it is easier to use global space.

## Robot example

The robot has been modeled in "object" space.
We move it into the desired position in world space,
by rotating it clockwise $120\degree$ and translating it 18 ft east and 10 ft north.


