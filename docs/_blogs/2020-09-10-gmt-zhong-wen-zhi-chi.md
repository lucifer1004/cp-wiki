---
lang: zh-CN
published: 2020-09-10T00:42:00.013Z
keywords:
  - GMT
  - GhostScript
description:
  content: 如何让GMT正确地输出中文
---

# GMT中文支持

[GMT中文手册](https://docs.gmt-china.org/latest/chinese/)中的相关内容是比较齐全的，但遗憾的是没有一个总括性的介绍，不能做到“授人以渔”。

GMT的中文支持总体上可以分为两步：

1. 找到`GhostScript`的`cidfmap`文件，在其中定义中文字体的别名和路径等信息。这一步可参考[手册](https://docs.gmt-china.org/latest/chinese/custom-fonts/#windows)。
2. 配置GMT的额外字体。这一步可参考[手册](https://docs.gmt-china.org/latest/chinese/linux/#gmt)。

实际操作中，第一步更可能遇到麻烦。因为不同系统、不同环境的`cidfmap`文件的位置是不同的。

手册中介绍的是`Cent OS 7`的配置方法，下面再补充几种。

## Mac下通过`homebrew`安装`GMT`

### Mac的字体文件位置

```txt
/Users/${USERNAME}/Library/Fonts
```

### `homebrew`安装的`GhostScript`的`cidfmap`文件位置

```txt
/usr/local/Cellar/ghostscript/${GS_VERSION}/share/ghostscript/${GS_VERSION}/Resource/Init/cidfmap
```

修改`cidfmap`文件，就可以加入需要的字体，然后再参考手册中的方法，给GMT增加对应的字体即可。

## Ubuntu下通过`Anaconda`安装`GMT`

### `Anaconda`安装的`GMT`可执行文件位置

```txt
${ANACONDA_HOME}/envs/${GMT_ENV}/bin/gmt
```

### `Anaconda`安装的`GhostScript`的`cidfmap`文件位置

```txt
${ANACONDA_HOME}/envs/${GMT_ENV}/share/ghostscript/${GS_VERSION}/Resource/Init/cidfmap
```

用Mac的方式，直接修改`cidfmap`文件并不能生效。原因不明。

## Ubuntu下通过`linuxbrew`安装`GMT`

目前版本的`linuxbrew`安装不上`GDAL`，所以无法安装`GMT`。但可以通过软链接的方式，使用`Anaconda`安装的`GMT`。

### `linuxbrew`安装的`GhostScript`的`cidfmap`文件位置

```txt
$/home/linuxbrew/.linuxbrew/Cellar/ghostscript/${GS_VERSION}/share/ghostscript/${GS_VERSION}/Resource/Init/cidfmap
```

使用`linuxbrew`安装的`GhostScript`和`Anaconda`安装的`GMT`，不需要设置`cidfmap`，就可以支持宋体、仿宋和黑体，但不能支持楷体。原因不明。

## 小结

虽然目前仍然有很多不明晰的地方，但Mac和Ubuntu两个环境下GMT的中文支持都算是实现了。还没有弄清楚的地方，以后再慢慢研究。

<Utterances />
