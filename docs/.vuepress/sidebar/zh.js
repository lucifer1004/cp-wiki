module.exports = {
  '/basic/': ['enumerate/', 'binary-search/', 'ternary-search/'],
  '/algebra/': ['binary-exponentiation/', 'fast-fourier-transform/'],
  '/data-structure/': [
    {
      title: '基础数据结构',
      collapsable: false,
      children: ['stack/', 'queue/'],
    },
    {
      title: '进阶数据结构',
      collapsable: false,
      children: ['disjoint-union/', 'segment-tree/'],
    },
  ],
  '/graph-theory/': [''],
  '/geometry/': ['basic/'],
  '/string/': ['prefix-function/', 'trie/', 'aho-corasick/'],
  '/combinatorics/': ['inclusion-exclusion/'],
  '/tutorial/kick-start/': [
    '',
    {
      title: '2020',
      collapsable: true,
      children: ['2020E/', '2020D/'],
    },
    {
      title: '2019',
      collapsable: true,
      children: ['2019G/', '2019F/', '2019D/', '2019C/'],
    },
  ],
  '/tutorial/atcoder/': [
    '',
    {
      title: 'AtCoder Beginner Contest',
      collapsable: true,
      children: ['ABC177/', 'ABC176/', 'ABC175/', 'ABC174/'],
    },
  ],
  '/tutorial/codeforces/': [
    '',
    {
      title: 'Regular Round',
      collapsable: true,
      children: ['1396/'],
    },
    {
      title: 'Div.2 Round',
      collapsable: true,
      children: ['1401/', '1393/', '1388/'],
    },
    {
      title: 'Educational Round',
      collapsable: true,
      children: ['1400/', '1398/', '1389/'],
    },
    {
      title: 'Div.3 Round',
      collapsable: true,
      children: ['1399/'],
    },
  ],
  '/blog/': null,
  '/': 'auto',
};
