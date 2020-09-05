---
lang: en-US
published: 2020-09-05T03:48:47.170Z
keywords:
  - Node.js
  - JavaScript
description:
  content: Writing a Node.js script for automated blog generation.
---

# Shortcut for blog creation

Today I wrote a script to automatically generate a template blog. I expected it to be easy. It was easy, but not that easy as I had thought. The problem was to convert Chinese characters to Pinyin for filename. Luckily, I found the library [tiny-pinyin](https://github.com/creeperyang/pinyin) which handles this swiftly.

Currently, the CLI is very simple. I could have added things like `chalk` to beautify the UI, but I do not care about that too much. After all, there are few other users, if not none, using this project to write their notes and blogs.

## Some thoughts

With the time spent on this site increasing, I found more and more custom feature requirements. Vuepress is great because it offers both powerful defaults and extreme flexibility. I can write Vue and Node.js directly if neither defaults nor existing plugins can meet my needs.

<Utterances />
