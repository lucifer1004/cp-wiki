const { getSubfolders, range } = require('../utils');

module.exports = {
  '/basic/': [
    '',
    'enumerate/',
    'binary-search/',
    'ternary-search/',
    'breadth-first-search/',
  ],
  '/algebra/': ['', ...getSubfolders('algebra')],
  '/data-structure/': [
    {
      title: '基础数据结构',
      collapsable: false,
      children: ['stack/', 'queue/'],
    },
    {
      title: '进阶数据结构',
      collapsable: false,
      children: [
        'balanced-binary-search-tree/',
        'disjoint-sets-union/',
        'segment-tree/',
      ],
    },
  ],
  '/graph-theory/': ['', ...getSubfolders('graph-theory')],
  '/dynamic-programming/': ['', ...getSubfolders('dynamic-programming')],
  '/geometry/': ['', ...getSubfolders('geometry')],
  '/string/': ['', ...getSubfolders('string')],
  '/combinatorics/': ['', ...getSubfolders('combinatorics')],
  '/tutorial/kick-start/': [
    '',
    {
      title: '2020',
      collapsable: true,
      children: ['2020F/', '2020E/', '2020D/'],
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
      children: [
        'ABC179/',
        'ABC178/',
        'ABC177/',
        'ABC176/',
        'ABC175/',
        'ABC174/',
      ],
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
      children: ['1407/', '1401/', '1393/', '1388/'],
    },
    {
      title: 'Educational Round',
      collapsable: true,
      children: ['1400/', '1398/', '1389/'],
    },
    {
      title: 'Div.3 Round',
      collapsable: true,
      children: ['1409/', '1399/'],
    },
  ],
  '/tutorial/leetcode/': [
    '',
    {
      title: '周赛',
      collapsable: true,
      children: range(193, 212, 'WC', true),
    },
    {
      title: '双周赛',
      collapsable: true,
      children: range(29, 37, 'BC', true),
    },
  ],
  '/blog/': null,
  '/': 'auto',
};
