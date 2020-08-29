# 小贴士

## 实用工具

### [cf-tool](https://github.com/xalanq/cf-tool)

一款用于Codeforces比赛和练习的命令行工具。

### [CP Editor](https://cpeditor.org/)

一款基于Qt的IDE，集成了多项CP相关的功能（测试用例抓取，快速测试，快速提交等）。

### [cf-predictor](https://cf-predictor-frontend.herokuapp.com/)

根据实时排名预测Codeforces Rating变化。

## 编译运行相关

建议参考OJ平台的编译命令，比如[Codeforces](https://codeforces.com/blog/entry/79)的（Windows环境）。

### C++打开栈空间

- Windows环境，编译时加入`-Wl,--stack=268435456`选项（设置系统栈空间为256 MB）。
- Linux/Mac环境，编译时加入`-Wl,-stack_size,0x10000000,-stack_addr,0xc0000000`选项（设置系统栈空间为256 MB）。
  - Linux环境也可以在当前终端环境中执行`ulimit -s unlimited`，之后在本终端中运行的程序不受栈空间限制（该命令对Mac无效）
  - Mac环境建议使用`homebrew`方式安装的`g++`（注意其调用方式为`g++-v`，`v`代表版本号），不要使用Mac自带的`g++`命令。

### Java设置堆栈大小

编译时加入`-Xss256M`选项可以将堆栈大小设置为256 MB。

### Python设置最大递归深度

```python
import sys

sys.setrecursionlimit(10000)
```

理论上来说可以设置为任意值，但实际上会受到Python版本和系统环境的限制，未必能达到设置值。最好的办法，还是在可以预料到递归深度太深时，放弃使用递归，或者放弃Python。
