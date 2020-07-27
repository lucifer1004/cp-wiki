module.exports = {
  themeConfig: {
    nav: [
      {
        text: '首页',
        link: '/',
      },
      {
        text: '数据结构',
        link: '/data-structures/',
      },
      {
        text: '黑话',
        link: '/jargon/',
      },
    ],
    sidebar: 'auto',
  },
  markdown: {
    lineNumbers: true,
    extendMarkdown: md => {
      md.use(require('@iktakahiro/markdown-it-katex'));
      md.use(require('markdown-it-container'), 'spoiler', {
        validate: params => {
          return params.trim().match(/^spoiler\s+(.*)$/);
        },
        render: (tokens, idx) => {
          var m = tokens[idx].info.trim().match(/^spoiler\s+(.*)$/);
          if (tokens[idx].nesting === 1) {
            return (
              '<details><summary>' + md.utils.escapeHtml(m[1]) + '</summary>\n'
            );
          } else {
            return '</details>\n';
          }
        },
      });
    },
  },
};
