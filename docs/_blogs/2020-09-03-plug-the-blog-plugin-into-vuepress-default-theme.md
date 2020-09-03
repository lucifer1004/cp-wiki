---
lang: en-US
published: 2020-09-03
keywords:
  - Vue
  - Vuepress
  - Tutorial
description:
  content: How to use @vuepress/plugin-blog together with Vuepress default theme.
---

# Plug the blog plugin into Vuepress default theme

This site is mainly organized like a documentation, so the default theme of [Vuepress](https://vuepress.vuejs.org/ ) works like a charm. However, problems occur when I wanted to add a blog section.

I could not choose [@vuepress/theme-blog](https://vuepress-theme-blog.ulivz.com/) because that would disrupt my current site structure. Then I found the extracted version [@vuepress/plugin-blog](https://vuepress-plugin-blog.ulivz.com/), which is meant to be used as a plugin instead of a theme. However, its integration with the default theme is a pain. The `itemLayout` option worked but the `indexLayout` option did not. I even tried `vuepress eject` in order to figure out how I could make them both work, but concluded that it would cost a lot of time which I could not afford.

It was not until I found [Chris Noring](https://softchris.github.io/)'s blog [Create YOUR next static blog in Vuepress and Vue](https://softchris.github.io/pages/vue-vuepress.html) had I recognized that I could simply build an index page myself. So in the end, I only used the url formatting function of `plugin-blog`, while wrote other logics on my own (with reference to Chris' blog).

And now the work has come to an end. It is still far from satisfactory, but I have figured out how to do it, and will implement more features in the future.

<Utterances />
