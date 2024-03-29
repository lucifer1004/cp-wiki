const { getSubfolders, range } = require('../utils');

module.exports = {
  '/basic/': [
    '',
    'enumerate/',
    'sorting/',
    'binary-search/',
    'ternary-search/',
    'breadth-first-search/',
    'small-to-large/',
    'invariant/',
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
  '/miscellaneous/': ['', ...getSubfolders('miscellaneous')],
  '/tutorial/kick-start/': [
    '',
    {
      title: '2022',
      collapsable: true,
      children: ['2022A/'],
    },
    {
      title: '2021',
      collapsable: true,
      children: ['2021B/', '2021A/'],
    },
    {
      title: '2020',
      collapsable: true,
      children: ['2020H/', '2020F/', '2020E/', '2020D/'],
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
        'ABC191/',
        'ABC190/',
        'ABC189/',
        'ABC188/',
        'ABC187/',
        'ABC186/',
        'ABC185/',
        'ABC184/',
        'ABC183/',
        'ABC182/',
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
      children: ['1437/', '1400/', '1398/', '1389/'],
    },
    {
      title: 'Div.3 Round',
      collapsable: true,
      children: ['1409/', '1399/'],
    },
  ],
  '/tutorial/advent-of-code/': [
    '',
    {
      title: '提示',
      collapsable: true,
      children: range(2015, 2021, '', true),
    },
  ],
  '/tutorial/leetcode/': [
    '',
    {
      title: '周赛（329~）',
      collapsable: true,
      children: range(329, 329, 'WC', true),
    },
    {
      title: '周赛（301~303）',
      collapsable: true,
      children: range(301, 303, 'WC', true),
    },
    {
      title: '周赛（251~300）',
      collapsable: true,
      children: range(251, 300, 'WC', true),
    },
    {
      title: '周赛（201~250）',
      collapsable: true,
      children: range(201, 250, 'WC', true),
    },
    {
      title: '周赛（~200）',
      collapsable: true,
      children: range(192, 200, 'WC', true),
    },
    {
      title: '双周赛',
      collapsable: true,
      children: range(28, 84, 'BC', true),
    },
    {
      title: '其他比赛',
      collapsable: true,
      children: ['2021-fall-solo/', '2022-spring-cnunionpay/', '2022-spring-solo/'],
    },
  ],
  '/blog/': null,
  '/': 'auto',
};
