const { getSubfolders, range } = require('../utils');

module.exports = {
  '/en/tutorial/kick-start/': [
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
  '/en/tutorial/atcoder/': [
    '',
    {
      title: 'AtCoder Beginner Contest',
      collapsable: true,
      children: [
        'ABC195/',
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
  '/en/tutorial/codeforces/': [
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
  '/en/tutorial/advent-of-code/': [
    '',
    {
      title: 'Hints',
      collapsable: true,
      children: range(2015, 2021, '', true),
    },
  ],
  '/en/tutorial/uoj/': ['', ...getSubfolders('en/tutorial/uoj')],
  '/en/blog/': null,
  '/': 'auto',
};
