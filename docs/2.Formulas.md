### Negation

```math
\begin{aligned}

-
\begin{bmatrix}
    x &
    y
\end{bmatrix}
&=
\begin{bmatrix}
    -x &
    -y
\end{bmatrix}

\newline

-
\begin{bmatrix}
    x &
    y &
    z
\end{bmatrix}
&=
\begin{bmatrix}
    -x &
    -y &
    -z
\end{bmatrix}

\newline

-
\begin{bmatrix}
    x &
    y &
    z &
    w
\end{bmatrix}
&=
\begin{bmatrix}
    -x &
    -y &
    -z &
    -w
\end{bmatrix}

\end{aligned}
```

### Scalar Multiplication


```math
k
\begin{bmatrix}
    x \\
    y \\
    z
\end{bmatrix}
=
\begin{bmatrix}
    x \\
    y \\
    z
\end{bmatrix}
k
=
\begin{bmatrix}
    kx \\
    ky \\
    kz
\end{bmatrix}
```

### Scalar Division


```math
\frac v k
=
(\frac 1 k)v
=
(\frac 1 k)
\begin{bmatrix}
    v_x \\
    v_y \\
    v_z
\end{bmatrix}
=
\begin{bmatrix}
    (1 / k) v_x \\
    (1 / k) v_y \\
    (1 / k) v_z
\end{bmatrix}
=
\begin{bmatrix}
    v_x / k \\
    v_y / k \\
    v_z / k
\end{bmatrix}
```


### Vector Addition

```math
a + b
= 
\begin{bmatrix}
    a_x \\
    a_y \\
    a_z
\end{bmatrix}
+
\begin{bmatrix}
    b_x \\
    b_y \\
    b_z
\end{bmatrix}
= 
\begin{bmatrix}
    a_x + b_x \\
    a_y + b_y \\
    a_z + b_z
\end{bmatrix}
```

### Vector Addition is Commutative

```math
a + b = b + a
```

### Vector Subtraction is Anticommutative

```math
a - b = - (b-a)
```

### Vector Subtraction

```math
a - b
= 
\begin{bmatrix}
    a_x \\
    a_y \\
    a_z
\end{bmatrix}
-
\begin{bmatrix}
    b_x \\
    b_y \\
    b_z
\end{bmatrix}
= 
\begin{bmatrix}
    a_x - b_x \\
    a_y - b_y \\
    a_z - b_z
\end{bmatrix}
```

### Vector Magnitude

```math
\|v\|
= \sqrt {\sum_{i=1}^{n}{v_i}^2 }
= \sqrt {{v_1}^2 + {v_2}^2 + \cdots + {v_{n-1}}^2 + {v_n}^2}
```

for a 2D vector
```math
\|v\| = \sqrt {{v_x}^2 + {v_y}^2}
```

for a 3D vector
```math
\|v\| = \sqrt {{v_x}^2 + {v_y}^2+ {v_z}^2}
```

### Unit Vectors

```math
\hat v = \frac v {\|v\|}
```

### Dot Product

The dot product of two vectors is the sum of the products of corresponding components, resulting in a scalar:

```math
\begin{bmatrix}
    a_1 \\
    a_2 \\
    \vdots \\
    a_{n-1} \\
    a_n
\end{bmatrix}
\cdot
\begin{bmatrix}
    b_1 \\
    b_2 \\
    \vdots \\
    b_{n-1} \\
    b_n
\end{bmatrix}
=a_1 b_1 + a_2 b_2 + \cdots + a_{n-1} b_{n-1} + a_n b_n
```

This can be expressed succinctly by using the summation notation:
```math
a \cdot b
= \sum_{i=1}^n a_i b_i
```

2D case:
```math
a \cdot b = a_x b_x + a_y b_y
```

3D case:
```math
a \cdot b = a_x b_x + a_y b_y + a_z b_z
```


The dot product of a vector with itself is the square of its length:
```math
\begin{aligned}
v \cdot v &= \|v\|^2 \\
\|v\| &= \sqrt {v \cdot v}
\end{aligned}
```

#### Dot Product as Projection
> The dot product $a \cdot b$ is equal to the signed length of the projection of $b$ onto any line parallel to $a$, multiplied by the length of $a$.


#### Breaking a vector into parallel and perpendicular components

```math
b_{\parallel} = (\hat a \cdot b)\hat a
```

```math
\begin{aligned}
b_{\perp} + b_{\parallel} &= b \\
b_{\perp} &= b - b_{\parallel} \\
b_{\perp} &= b - (\hat a \cdot b)\hat a
\end{aligned}
```

#### Dot Product Relation to Intercepted Angle

```math
a \cdot b = \|a\| \|b\| \cos\theta
```

### Cross Product

```math
\begin{bmatrix}
    x_1 \\
    y_1 \\
    z_1
\end{bmatrix}
\times
\begin{bmatrix}
    x_2 \\
    y_2 \\
    z_2
\end{bmatrix}
=
\begin{bmatrix}
    y_1 z_2 - z_1 y_2 \\
    z_1 x_2 - x_1 z_2 \\
    x_1 y_2 - y_1 x_2
\end{bmatrix}
```

The length of $a \times b$ is equal to the product of the magnitudes of $a$ and $b$ and the sine of the angle between $a$ and $b$:
```math
\|a \times b\| = \|a\| \|b\| \sin\theta
```

