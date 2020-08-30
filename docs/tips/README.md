# 小贴士

## 网站平台（算法类）

### [OI-wiki](https://oi-wiki.org/)

国人维护的最大规模编程竞赛知识站点。

### [CP Algorithms](https://cp-algorithms.com/)

主要内容为[E-Maxx](http://e-maxx.ru/algo/)的英文翻译，也有部分原创内容。

## 网站平台（竞赛类）

### [Codeforces](https://codeforces.com/)

目前全球范围内每次比赛参加人数最多的竞赛平台。除了比赛和题库外，在博客和讨论区也有非常多高质量的内容。全球顶尖的CP高手基本都在上面出没。

主要的竞赛种类包括Global Round（所有人都计分）、Regular Round（分Div.1和Div.2两组进行）、Div.2 Only、Educational Round和Div.3 Round等。此外，还有一些不计分的镜像赛，以及在[Gym](https://codeforces.com/gyms)中举办的练习赛。

近来，Codeforces又开放了[EDU](https://codeforces.com/edu/courses)板块，教学内容和配套练习的质量较高，目前内容还比较少，正在陆续添加中。

网站设在俄罗斯，如果访问缓慢，可以尝试使用国人制作的[镜像1](https://codeforces.ml)或[镜像2](https://codeforc.es)。另外，在比赛期间，会临时开放比赛专用的[比赛服1](httsp://m1.codeforces.com)、[比赛服2](httsp://m2.codeforces.com)和[比赛服3](httsp://m3.codeforces.com)。

### [AtCoder](https://atcoder.com)

建立在日本的一个新兴竞赛平台。竞赛分为Beginner、Regular、Grand三个级别。Beginner的前两题一般非常水，除此之外，其他题目的质量较高。

### [TopCoder](https://arena.topcoder.com/)

老牌竞赛平台，举办经典赛事TCO（TopCoder Open）。近年来重心转向远程工作和更宽泛的软件开发。

### [Google](https://codingcompetitions.withgoogle.com/)

Google每年举办三种类型的编程竞赛。

- [Kick Start](https://codingcompetitions.withgoogle.com/kickstart)为新手入门级，也是Google面试的敲门砖，每年举办八轮。
- [Code Jam](https://codingcompetitions.withgoogle.com/codejam)是Google的王牌赛事，也是最重要的赛事，分为资格赛、A轮、B轮、C轮和决赛。决赛每年有25个名额。
- [Hash Code](https://codingcompetitions.withgoogle.com/hashcode)是一项团队赛，与一般编程竞赛不同，赛题一般为没有最优答案的优化问题。分为资格赛和决赛两轮。

### [洛谷](https://www.luogu.com.cn/)

国内竞赛和OJ平台。

### [牛客竞赛](https://ac.nowcoder.com/acm/home)

国内竞赛和OJ平台，商业性较强。

### [Leetcode](https://leetcode.com)

原本是一个求职刷题的网站，国服叫[力扣](https://leetcode-cn.com)。近几年来，长期举办周赛（固定在北京时间每周日的上午十点半开始），最近又增加了双周赛（每两周一次，北京时间周六的晚上十点半开始）。

赛题质量波动较大，总体难度低于其他平台。比较适合新手。

## 网站平台（OJ类）

### [SPOJ](https://www.spoj.com/)

### [UVa Online Judge](https://onlinejudge.org/)

老牌OJ，不过评测系统不是十分友好。知名的[CP Book](https://cpbook.net/)里基本都是用UVa题目作为例题和练习题。

### [Kattis](https://open.kattis.com/)

### [POJ](http://poj.org/)

国内最老牌的OJ之一，由北京大学主办。目前界面和系统已经比较陈旧。

### [HDOJ](http://acm.hdu.edu.cn/)

国内老牌OJ，由杭州电子科技大学主办。过去办比赛较多，现在主要负责举办每年的百度之星。

### [LibreOJ](https://loj.ac/)

国内OJ平台。

### [Comet OJ](https://www.cometoj.com/)

国内OJ平台。

### [AcWing](https://www.acwing.com/)

由yxc（闫学灿）创办的OJ平台。

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

<Utterances />
