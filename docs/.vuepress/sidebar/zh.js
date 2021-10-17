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
  '/tutorial/leetcode/': [
    '',
    {
      title: '周赛（261~）',
      collapsable: true,
      children: range(261, 263, 'WC', true),
    },
    {
      title: '周赛（241~260）',
      collapsable: true,
      children: range(241, 260, 'WC', true),
    },
    {
      title: '周赛（221~240）',
      collapsable: true,
      children: range(221, 240, 'WC', true),
    },
    {
      title: '周赛（201~220）',
      collapsable: true,
      children: range(201, 220, 'WC', true),
    },
    {
      title: '周赛（181~200）',
      collapsable: true,
      children: range(192, 200, 'WC', true),
    },
    {
      title: '双周赛',
      collapsable: true,
      children: range(28, 63, 'BC', true),
    },
    {
      title: '力扣杯',
      collapsable: true,
      children: ['2021-fall-solo/'],
    },
  ],
  '/blog/': null,
  '/': 'auto',
};
