module.exports = {
  title: "CP Wiki",
  locales: {
    "/": {
      lang: "zh-CN",
      description: "lucifer1004的CP笔记",
    },
    "/en/": {
      lang: "en-US",
      description: "lucifer1004's CP notes",
    },
  },
  themeConfig: {
    repo: "lucifer1004/cp-wiki",
    locales: {
      "/": {
        editLinkText: "在 GitHub 上编辑此页",
        lastUpdated: "上次更新",
        selectText: "选择语言 | Language",
        ariaLabel: "选择语言",
        label: "🇨🇳 简体中文",
        nav: require("./nav/zh"),
        sidebar: require("./sidebar/zh"),
      },
      "/en/": {
        editLinkText: "Edit this page on GitHub",
        lastUpdated: "Last Updated",
        selectText: "Language",
        ariaLabel: "Select language",
        label: "🇬🇧 English",
        nav: require("./nav/en"),
        sidebar: "auto",
      },
    },
    editLinks: true,
    docsDir: "docs",
    smoothScroll: true,
  },
  markdown: {
    lineNumbers: true,
    extendMarkdown: (md) => {
      md.use(require("@iktakahiro/markdown-it-katex"));
    },
  },
  plugins: [
    ["autometa", {}],
  ],
  extraWatchFiles: [
    ".vuepress/nav/en.js",
    ".vuepress/nav/zh.js",
    ".vuepress/sidebar/en.js",
    ".vuepress/sidebar/zh.js",
  ],
};
