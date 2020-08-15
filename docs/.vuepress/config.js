module.exports = {
  title: "CP Wiki",
  themeConfig: {
    nav: [
      {
        text: "首页",
        link: "/",
      },
      {
        text: "代数",
        link: "/algebra/",
      },
      {
        text: "数据结构",
        link: "/data-structure/",
      },
      {
        text: "几何",
        link: "/geometry/",
      },
      {
        text: "题解",
        link: "/editorial/",
      },
      {
        text: "黑话",
        link: "/jargon/",
      },
    ],
    sidebar: "auto",
  },
  markdown: {
    lineNumbers: true,
    extendMarkdown: (md) => {
      md.use(require("@iktakahiro/markdown-it-katex"));
      md.use(require("markdown-it-container"), "spoiler", {
        validate: (params) => {
          return params.trim().match(/^spoiler\s+(.*)$/);
        },
        render: (tokens, idx) => {
          var m = tokens[idx].info.trim().match(/^spoiler\s+(.*)$/);
          if (tokens[idx].nesting === 1) {
            return (
              "<details><summary>" + md.utils.escapeHtml(m[1]) + "</summary>\n"
            );
          } else {
            return "</details>\n";
          }
        },
      });
    },
  },
  plugins: [
    "@vuepress/google-analytics",
    {
      "ga": "G-86WYJ60C5M",
    },
  ],
};
