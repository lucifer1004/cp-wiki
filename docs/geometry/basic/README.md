# 几何基础

## 基础几何要素的表示

### 点

在二维空间中，点可以用二元组$(x,y)$表示；在三维空间中，点可以用三元组$(x,y,z)$来表示。以此类推，可以给出任意维度空间中点的表示，但在CP中，通常只需要考虑二维和三维的情形，只有在一些特殊的数据结构中会涉及到更高维度，比如K-D树和区间树。

点同时也可以看成是从原点开始的向量，因此可以进行加减、数乘、点乘、叉乘等运算。

下面的示例中给出了点的结构体定义，其中定义了加减和数乘运算。

::: details 二维空间中点的结构体定义示例

```cpp
struct point2d {
    ftype x, y;
    point2d() {}
    point2d(ftype x, ftype y): x(x), y(y) {}
    point2d& operator+=(const point2d &t) {
        x += t.x;
        y += t.y;
        return *this;
    }
    point2d& operator-=(const point2d &t) {
        x -= t.x;
        y -= t.y;
        return *this;
    }
    point2d& operator*=(ftype t) {
        x *= t;
        y *= t;
        return *this;
    }
    point2d& operator/=(ftype t) {
        x /= t;
        y /= t;
        return *this;
    }
    point2d operator+(const point2d &t) const {
        return point2d(*this) += t;
    }
    point2d operator-(const point2d &t) const {
        return point2d(*this) -= t;
    }
    point2d operator*(ftype t) const {
        return point2d(*this) *= t;
    }
    point2d operator/(ftype t) const {
        return point2d(*this) /= t;
    }
};
point2d operator*(ftype a, point2d b) {
    return b * a;
}
```

:::

::: details 三维空间中点的结构体定义示例

```cpp
struct point3d {
    ftype x, y, z;
    point3d() {}
    point3d(ftype x, ftype y, ftype z): x(x), y(y), z(z) {}
    point3d& operator+=(const point3d &t) {
        x += t.x;
        y += t.y;
        z += t.z;
        return *this;
    }
    point3d& operator-=(const point3d &t) {
        x -= t.x;
        y -= t.y;
        z -= t.z;
        return *this;
    }
    point3d& operator*=(ftype t) {
        x *= t;
        y *= t;
        z *= t;
        return *this;
    }
    point3d& operator/=(ftype t) {
        x /= t;
        y /= t;
        z /= t;
        return *this;
    }
    point3d operator+(const point3d &t) const {
        return point3d(*this) += t;
    }
    point3d operator-(const point3d &t) const {
        return point3d(*this) -= t;
    }
    point3d operator*(ftype t) const {
        return point3d(*this) *= t;
    }
    point3d operator/(ftype t) const {
        return point3d(*this) /= t;
    }
};
point3d operator*(ftype a, point3d b) {
    return b * a;
}
```

:::

### 线

直线的表示方法很多，以二维空间为例，常见的表示方法有：

- 点斜式：直线上一点和直线斜率（无法表示平行于$y$-轴的直线）
- 两点式：直线上不相同的两点
- 斜截式：直线在$y$-轴上的截距和直线斜率。斜截式是点斜式的特殊情形。
- 截距式：直线在$x$-轴和$y$-轴上的截距。截距式是两点式的特殊情形。
- 参数式：已知直线上一点$\mathbf{a}$和直线方向$\mathbf{d}$，可以用参数方程$\mathbf{r}=\mathbf{a}+t\cdot\mathbf{d}$来表示直线，其中$t\in\mathbb{R}$。

### 面

### 多边形

### 圆形

<Utterances />
