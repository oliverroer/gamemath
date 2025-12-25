
---
Let's expand the left side:
```math
\begin{aligned}
\|a \times b\|
&=
\|
\begin{bmatrix}
    a_y b_z - a_z b_y \\
    a_z b_x - a_x b_z \\
    a_x b_y - a_y b_x
\end{bmatrix}
\|
\newline
&=
\sqrt {
    (a_y b_z - a_z b_y)^2
    +
    (a_z b_x - a_x b_z)^2
    +
    (a_x b_y - a_y b_x)^2
}
\newline
&=
\sqrt {
    a_y^2 b_z^2     - 2 a_y a_z b_y b_z     + a_z^2 b_y^2
    +
    a_z^2 b_x^2     - 2 a_x a_z b_x b_z     + a_x^2 b_z^2

    a_x^2 b_y^2     - 2 a_x a_y b_x b_y     + a_y^2 b_x^2
}
\end{aligned}
```

---

Let's look at the right side:
Let's expand the right side:
```math
\|a\| \|b\| \sin \theta 
```
---

By applying the pythagorean theorem to the unit circle, you can deduce the following identity:
```math
\begin{aligned}
1^2 &= (\sin\theta)^2 + (\cos\theta)^2
\newline
1 &= (\sin\theta)^2 + (\cos\theta)^2
\newline
1 - (\cos\theta)^2 &= (\sin\theta)^2
\newline
\sqrt {1 - (\cos\theta)^2} &= \sin\theta
\end{aligned}
```
---
We can use this to replace $\sin\theta$ like so:

```math
\|a\| \|b\| \sin \theta =  \|a\| \|b\| \sqrt {1 - (\cos\theta)^2}
```
---
Next, we'll use the geometric interpretation of the dot product to arrive at a definition of $\cos\theta$:
```math
\begin{aligned}
a \cdot b &= \|a\| \|b\| \cos\theta
\newline
\frac {a \cdot b} {\|a\| \|b\|} &= \cos\theta
\end{aligned}
```

We can use this to replace $\cos\theta$ like so, and start expanding:

```math
\|a\| \|b\| \sin \theta =  \|a\| \|b\| \sqrt {1 - (\frac {a \cdot b} {\|a\| \|b\|})^2}
```
